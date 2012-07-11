/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * JNI method invocation.  This is used to call a C/C++ JNI method.  The
 * argument list has to be pushed onto the native stack according to
 * local calling conventions.
 *
 * This version supports the "new" ARM EABI.
 */

#include <machine/cpu-features.h>

#ifdef __ARM_EABI__

#ifdef EXTENDED_EABI_DEBUG
# define DBG
#else
# define DBG @
#endif


/*
Function prototype:

void dvmPlatformInvoke(void* pCARObejct, int argInfo, int argc,
    const u4* argv, const char* signature, void* func, JValue* pReturn)

We call the CAR function, the firts argument must be pCARObject(this), and
the out argument is fllowing the in argument, that is
    func(this, arg1, arg2, ... , out)

So we have to make the stack rigth for call a CAR function.

We receive a collection of 32-bit values which correspond to arguments from
the interpreter (e.g. float occupies one, double occupies two).  It's up to
us to convert these into local calling conventions.
*/

/*
ARM EABI notes:

r0-r3 hold first 4 args to a method
r9 is given special treatment in some situations, but not for us
r10 (sl) seems to be generally available
r11 (fp) is used by gcc (unless -fomit-frame-pointer is set)
r12 (ip) is scratch -- not preserved across method calls
r13 (sp) should be managed carefully in case a signal arrives
r14 (lr) must be preserved
r15 (pc) can be tinkered with directly

r0 holds returns of <= 4 bytes
r0-r1 hold returns of 8 bytes, low word in r0

Callee must save/restore r4+ (except r12) if it modifies them.

Stack is "full descending".  Only the arguments that don't fit in the first 4
registers are placed on the stack.  "sp" points at the first stacked argument
(i.e. the 5th arg).

VFP: single-precision results in s0, double-precision results in d0.

In the EABI, "sp" must be 64-bit aligned on entry to a function, and any
64-bit quantities (long long, double) must be 64-bit aligned.  This means
we have to scan the method signature, identify arguments that must be
padded, and fix them up appropriately.
*/

    .text
    .align  2
    .global dvmPlatformCARInvoke
    .type   dvmPlatformCARInvoke, %function

/*
 * On entry:
 *   r0  pCARObejct (this point for CAR function)
 *   r1  arg info
 *   r2  argc (number of 32-bit values in argv)
 *   r3  argv
 *   [sp]     short signature
 *   [sp,#4]  func
 *   [sp,#8]  out
 *
 *
 * argInfo (32-bit int) layout:
 *   SRRRLLLL FFFFFFFF FFFFFFFF FFFFFFFF
 *
 *   S - if set, do things the hard way (scan the signature)
 *   R - return type enumeration, really only important for hardware FP
 *   L - number of double-words of storage required on stack (0-30 words)
 *   F - pad flag -- if set, write a pad word to the stack
 *
 * With this arrangement we can efficiently push up to 24 words of arguments
 * onto the stack.  Anything requiring more than that -- which should happen
 * rarely to never -- can do the slow signature scan.
 *
 * (We could pack the Fs more efficiently -- we know we never push two pads
 * in a row, and the first word can never be a pad -- but there's really
 * no need for it.)
 *
 * TODO: could reduce register-saving overhead for "fast" case, since we
 * don't use a couple of registers.  Another thought is to rearrange the
 * arguments such that r0/r1 get passed in on the stack, allowing us to
 * use r0/r1 freely here and then load them with a single ldm.  Might be
 * faster than saving/restoring other registers so that we can leave r0/r1
 * undisturbed.
 *
 * NOTE: if the called function has more than 4 words of arguments, gdb
 * will not be able to unwind the stack past this method.  The only way
 * around this is to convince gdb to respect an explicit frame pointer.
 */
dvmPlatformCARInvoke:
    .fnstart

    @ Save regs.  Same style as gcc with "-fomit-frame-pointer" -- we don't
    @ disturb "fp" in case somebody else wants it.  Copy "sp" to r4 and use
    @ that to access local vars.
    @
    @ On entry to a function, "sp" must be 64-bit aligned.  This means
    @ we have to adjust sp manually if we push an odd number of regs here
    @ (both here and when exiting).  Easier to just push an even number
    @ of registers.
    mov     ip, sp                      @ ip<- original stack pointer
    .save {r4, r5, r6, r7, r8, r9, ip, lr}
    stmfd   sp!, {r4, r5, r6, r7, r8, r9, ip, lr}

    mov     r4, ip                      @ r4<- original stack pointer

    @ Ensure 64-bit alignment.  EABI guarantees sp is aligned on entry, make
    @ sure we're aligned properly now.
DBG tst     sp, #4                      @ 64-bit aligned?
DBG bne     dvmAbort

    @ Do we have arg padding flags in "argInfo"? (just need to check hi bit)
    teq    r1, #0
    bmi     .Lslow_path

/*pei^_^
  move this work into c program
	//argv[0] is the java class this point, we discard it.
	add r3, r3, #4
	sub r2, r2, #1
*/
	//save argc info for comput the position of out
	add r5, r2, #1  // least possible register index is argc+1, when argc=2, 
					// may put pResult into r3, after considering pad, 
					// r5 may increase.

    /*
     * "Fast" path.
     *
     * Make room on the stack for the arguments and copy them over,
     * inserting pad words when appropriate.
     *
     * Currently:
     *   r0  don't touch
     *   r1  arg info
     *   r2  argc
     *   r3  argv
	 *   r4  original stack pointer
     *   r5-r9 (available)
     */
.Lhave_arg_info:
    @ Expand the stack by the specified amount.  We want to extract the
    @ count of double-words from r1, multiply it by 8, and subtract that
    @ from the stack pointer.
    and     ip, r1, #0x0f000000         @ ip<- doube-words required
    sub     sp, sp, ip, lsr #21         @ shift right 24, then left 3
    mov     r9, sp                      @ r9<- sp  (arg copy dest)

	//r8 hold the argv
	mov r8, r3
	mov r7, r2
	mov r6, r1

	//we load the r1 - r3
	movs 	r6, r6, lsr #1
	ldrcc   r1, [r8], #4
	subcc	r7, r7, #1
	addcs 	r5, r5, #1   
	
	movs 	r6, r6, lsr #1
	ldrcc   r2, [r8], #4 
	subcc	r7, r7, #1
	addcs 	r5, r5, #1   
	
	movs 	r6, r6, lsr #1
	ldrcc   r3, [r8], #4
	subcc	r7, r7, #1
	addcs 	r5, r5, #1

.Lfast_copy_loop:
    @ if (--argc < 0) goto invoke
    subs    r7, r7, #1
    bmi     .Lcopy_done                 @ NOTE: expects original argv in r9

.Lfast_copy_loop2:
    @ Get pad flag into carry bit.  If it's set, we don't pull a value
    @ out of argv.
    movs    r6, r6, lsr #1

    ldrcc   ip, [r8], #4                @ ip = *r8++ (pull from argv)
    strcc   ip, [r9], #4                @ *r9r6, r2++ = ip (write to stack)
    bcc     .Lfast_copy_loop

@DBG movcs   ip, #-3                     @ DEBUG DEBUG - make pad word obvious
@DBG strcs   ip, [r8]                    @ DEBUG DEBUG
    add     r9, r9, #4                  @ if pad, just advance ip without store
    b       .Lfast_copy_loop2           @ don't adjust argc after writing pad

.Lcopy_done:
    /*
     * Currently:
     *  r0-r3  args (this, arg0, arg1, arg2)
     *  r4  original saved sp
     *  r5  return type (enum DalvikJniReturnType)
     *  r3  original argv
     *
     * The stack copy is complete.  Grab the first two words off of argv
     * and tuck them into r2/r3.  If the first arg is 32-bit and the second
     * arg is 64-bit, then r3 "holds" a pad word and the load is unnecessary
     * but harmless.
     *
     * If there are 0 or 1 arg words in argv, we will be loading uninitialized
     * data into the registers, but since nothing tries to use it it's also
     * harmless (assuming argv[0] and argv[1] point to valid memory, which
     * is a reasonable assumption for Dalvik's interpreted stacks).
     *
     */
	//put the arg to r1-r3
	//ldmia   r3!, {r1-r3}                 @ r1/r2<- argv[0]/argv[1]

    // comput the out position now, anyway r0 is the this point.
	cmp r5, #1
	ldreq     r1, [r4, #8]
	cmp r5, #2
	ldreq     r2, [r4, #8]
	cmp r5, #3
	ldreq     r3, [r4, #8]

	//mov	r3, r6
	//we have to put out to stack
	ldrne   ip, [r4, #8]                @ ip = out
    strne   ip, [r9], #4                @ *r9++ = ip (write to stack)

    @ call the method
    ldr     ip, [r4, #4]                @ func
#ifdef __ARM_HAVE_BLX
    blx     ip
#else
    mov     lr, pc
    bx      ip
#endif


.Lback_from_car_function:    // we will jump here from slow path
    @ We're back, result is in r0 or (for long/double) r0-r1.
    @
    @ In theory, we need to use the "return type" arg to figure out what
    @ we have and how to return it.  However, unless we have an FPU,
    @ all we need to do is copy r0-r1 into the JValue union.
    @
    @ Thought: could redefine DalvikJniReturnType such that single-word
    @ and double-word values occupy different ranges; simple comparison
    @ allows us to choose between str and stm.  Probably not worthwhile.
    @
/*    cmp     r5, #0                      @ DALVIK_JNI_RETURN_VOID?
    ldrne   ip, [r4, #16]               @ pReturn
    @stmneia ip, {r0-r1}                 @ pReturn->j <- r0/r1
	stmneia  ip, {r3-r4}
*/
    @ Restore the registers we saved and return (restores lr into pc, and
    @ the initial stack pointer into sp).
#ifdef __ARM_HAVE_PC_INTERWORK
    ldmdb   r4, {r4, r5, r6, r7, r8, r9, sp, pc}
#else
    ldmdb   r4, {r4, r5, r6, r7, r8, r9, sp, lr}
    bx      lr
#endif
    .fnend



    /*
     * "Slow" path.
     * Walk through the argument list, counting up the number of 32-bit words
     * required to contain it.  Then walk through it a second time, copying
     * values out to the stack.  (We could pre-compute the size to save
     * ourselves a trip, but we'd have to store that somewhere -- this is
     * sufficiently unlikely that it's not worthwhile.)
     *
     * Try not to make any assumptions about the number of args -- I think
     * the class file format allows up to 64K words (need to verify that).
     *
     * Currently:
     *   r0  don't touch
     *   r1  don't touch
     *   r2  (available)
     *   r3  argc
     *   r4  original stack pointer
     *   r5-r8 (available)
     *   r9  argv
     */
.Lno_arg_info:
    mov     r5, r2, lsr #28             @ r5<- return type
    ldr     r6, [r4, #4]                @ r6<- short signature
    mov     r2, #0                      @ r2<- word count, init to zero

.Lcount_loop:
    ldrb    ip, [r6], #1                @ ip<- *signature++
    cmp     ip, #0                      @ end?
    beq     .Lcount_done                @ all done, bail
    add     r2, r2, #1                  @ count++
    cmp     ip, #'D'                    @ look for 'D' or 'J', which are 64-bit
    cmpne   ip, #'J'
    bne     .Lcount_loop

    @ 64-bit value, insert padding if we're not aligned
    tst     r2, #1                      @ odd after initial incr?
    addne   r2, #1                      @ no, add 1 more to cover 64 bits
    addeq   r2, #2                      @ yes, treat prev as pad, incr 2 now
    b       .Lcount_loop
.Lcount_done:

    @ We have the padded-out word count in r2.  We subtract 2 from it
    @ because we don't push the first two arg words on the stack (they're
    @ destined for r2/r3).  Pushing them on and popping them off would be
    @ simpler but slower.
    subs    r2, r2, #2                  @ subtract 2 (for contents of r2/r3)
    movmis  r2, #0                      @ if negative, peg at zero, set Z-flag
    beq     .Lcopy_done                 @ zero args, skip stack copy

DBG tst     sp, #7                      @ DEBUG - make sure sp is aligned now
DBG bne     dvmAbort                    @ DEBUG

    @ Set up to copy from r7 to r8.  We copy from the second arg to the
    @ last arg, which means reading and writing to ascending addresses.
    sub     sp, sp, r2, asl #2          @ sp<- sp - r2*4
    bic     sp, #4                      @ subtract another 4 ifn
    mov     r7, r9                      @ r7<- argv
    mov     r8, sp                      @ r8<- sp

    @ We need to copy words from [r7] to [r8].  We walk forward through
    @ the signature again, "copying" pad words when appropriate, storing
    @ upward into the stack.
    ldr     r6, [r4, #4]                @ r6<- signature
    add     r7, r7, #8                  @ r7<- r7+8 (assume argv 0/1 in r2/r3)

    @ Eat first arg or two, for the stuff that goes into r2/r3.
    ldrb    ip, [r6], #1                @ ip<- *signature++
    cmp     ip, #'D'
    cmpne   ip, #'J'
    beq     .Lstack_copy_loop           @ 64-bit arg fills r2+r3

    @ First arg was 32-bit, check the next
    ldrb    ip, [r6], #1                @ ip<- *signature++
    cmp     r6, #'D'
    cmpne   r6, #'J'
    subeq   r7, #4                      @ r7<- r7-4 (take it back - pad word)
    beq     .Lstack_copy_loop2          @ start with char we already have

    @ Two 32-bit args, fall through and start with next arg

.Lstack_copy_loop:
    ldrb    ip, [r6], #1                @ ip<- *signature++
.Lstack_copy_loop2:
    cmp     ip, #0                      @ end of shorty?
    beq     .Lcopy_done                 @ yes

    cmp     ip, #'D'
    cmpne   ip, #'J'
    beq     .Lcopy64

    @ Copy a 32-bit value.  [r8] is initially at the end of the stack.  We
    @ use "full descending" stacks, so we store into [r8] and incr as we
    @ move toward the end of the arg list.
.Lcopy32:
    ldr     ip, [r7], #4
    str     ip, [r8], #4
    b       .Lstack_copy_loop

.Lcopy64:
    @ Copy a 64-bit value.  If necessary, leave a hole in the stack to
    @ ensure alignment.  We know the [r8] output area is 64-bit aligned,
    @ so we can just mask the address.
    add     r8, r8, #7          @ r8<- (r8+7) & ~7
    ldr     ip, [r7], #4
    bic     r8, r8, #7
    ldr     r2, [r7], #4
    str     ip, [r8], #4
    str     r2, [r8], #4
    b       .Lstack_copy_loop


/*
 * Currently:
 *   r0  don't touch
 *   r1  arg info
 *   r2  argc
 *   r3  argv
 *   r4  original stack pointer
 *   r5-r9 (available)
 *   [sp]     short signature
 *   [sp,#4]  func
 *   [sp,#8]  pReturn
 *
 *
 *  plan:
 *  r0: pointer to car obj, don't touch
 *  r1, r2, r3: to fill with args or pad, before that, can fill with anything
 *  r4  original stack pointer, don't touch
 *  r5: which register is empty, r1, r2 or r3? it's value will be 1, 2 or 3.
 *  r6: signature pointer
 *  r7: when move a word(32-bit) from argv to stack, use it as temp container
 *  r8: argv
 *  r9: stack pointer
 *  ip: hold the current byte of signature
 *  sp: decrease by specific number to reserve space for args, later on, keep still
 */


// todo: i use too many branch to make logic clear, optimize it later
.Lslow_path:

// debug, when i use sp instead of r4, the value of r6 will be wrong, why? r4 != sp?
ldr r6, [r4]     // signature
add r6, r6, #1   // skip the first byte, it represents return type, 
				 // when no [out] parameter exists, it will be 'V'
mov r5, #1       // next empty register is r1
mov r8, r3       // argv

.Lfill_arg_into_reg:
	ldrb    ip, [r6], #1         // ip<- *signature++
    cmp     ip, #0               // end?  do not use #'\0'
    beq     .Lfill_regs_done     // can not goto .Lhandle_arg_out directly, 
								 // cause that will skip the init of counter;

	// sig not end
	cmp     ip, #'D'             // look for 'D' or 'J', which are 64-bit
    cmpne   ip, #'J'
    beq     .Lcheck_r1_for_64
	b       .Lcheck_r1_for_32

	.Lcheck_r1_for_64:
		cmp r5, #1              // r1 empty?
		beq .Lr1_empty_for_64	// true
		b .Lcheck_r2_for_64		// false

		.Lr1_empty_for_64:
			mov  r1, #0           // r1 = pad.  todo: necessary?
			ldr  r2, [r8], #4     // r2 = next 32-bit;
			ldr  r3, [r8], #4     // r3 = next 32-bit;
			add  r5, r5,   #3
			b .Lfill_regs_done 	  // registers all full, no need for loop

		.Lcheck_r2_for_64:
			cmp r5, #2              // r2 empty?
			beq .Lr2_empty_for_64	// true
			b   .Lcheck_r3_for_64	// false

			.Lr2_empty_for_64:
				ldr  r2, [r8], #4   // r2 = next 32-bit;
				ldr  r3, [r8], #4   // r3 = next 32-bit;
				add  r5, r5,   #2
				b .Lfill_regs_done  // registers all full, no need for loop

			.Lcheck_r3_for_64:
				cmp r5, #3              // r3 empty?

				moveq r3, #0            // {r3 = pad; reg = reg + 1; } if true;
				addeq   r5, r5, #1

				// this arg was not consumed, so roll back signature pointer;
				sub r6, r6, #1         //sig--;
				b .Lfill_regs_done     // registers all full, no need for loop

	.Lcheck_r1_for_32:
		cmp r5, #1              // r1 empty?
		beq .Lfill_r1_with_32	// true
		b   .Lcheck_r2_for_32	// false

		.Lfill_r1_with_32:
			ldr  r1, [r8], #4   // r1 = next 32-bit;
			add  r5, r5,   #1
			b .Lfill_arg_into_reg;

		.Lcheck_r2_for_32:
			cmp r5, #2              // r2 empty?
			beq .Lfill_r2_with_32	// true
			b .Lcheck_r3_for_32		// false

			.Lfill_r2_with_32:
				ldr  r2, [r8], #4   // r2 = next 32-bit;
				add  r5, r5,   #1
				b .Lfill_arg_into_reg;

			.Lcheck_r3_for_32:
				cmp r5, #3              // r3 empty?
				beq .Lfill_r3_with_32	// true
				b .Lr3_full_for_32		// false

				.Lfill_r3_with_32:
					ldr  r3, [r8], #4   // r3 = next 32-bit;
					add  r5, r5,   #1
					b .Lfill_regs_done;

				.Lr3_full_for_32:       // actually, this branch will never 
										// be executed. but we still keep it to 
										// make logic simple
					// this arg was not consumed, so roll back signature pointer;
					sub r6, r6, #1         //sig--;
					b .Lfill_regs_done     // registers all full, no need for loop

.Lfill_regs_done:
	mov r7, r6    // save a copy of current signature pointer, 
				  // we will use it later, it points to the type of the arg 
				  // which waits to be filled into stack.

	mov r9, #0    // init word(32-bit) counter
.Lcount_word_loop:
	ldrb    ip, [r6], #1         // ip<- *signature++. attention: go on to use 
								 // the above sig pointer r6
    cmp     ip, #0               // end?  do not use #'\0'
    beq     .Lconsider_arg_out

	cmp     ip, #'D'             // 32 or 64-bit?
    cmpne   ip, #'J'
    bne     .Lencounter_32
	b       .Lencounter_64

	.Lencounter_32:
		add r9, r9, #1           //counter++;
		b .Lcount_word_loop;

	.Lencounter_64:
		tst     r9, #1  // here, r9 is counter, not address, so tst with #1, not #7
		beq     .Lalinged                  // true
		b       .Lnot_alinged			   // false

		.Lalinged:
			add r9, r9, #2                 //counter = counter + 2;
			b .Lcount_word_loop;

		.Lnot_alinged:
			add r9, r9, #3                 //counter = counter + 3;
			b .Lcount_word_loop;

.Lconsider_arg_out:
	// now that we are here, registers are full, we will fill pReturn into stack,
	// so we should take it into account here, right?
	// pReturn is an address, 32-bit, so no alignment is needed. 
	// expand stack by 4 bytes and it's done.
	// what if the function has no [out] parameter?
	// i guess the first byte of sig will be 'V', confirmed.
	ldr 	r6, [sp]     			// fetch first byte of "original" signature;
	ldrb    ip, [r6], #1 			// don't care if r6 changes or not
	cmp     ip, #'V'           	 	// V?

	// debug, when i remove next sentense, all function calls all work. weird!
	// why shouldn't i reserve stack room for pResult?
	// by the way, fast-path reserve no room for pResult too.
	// addne   r9, r9, #1         	 	// add if false

	// expand stack to reserve room for args
	sub		sp, sp, r9, lsl #2   // sp = sp - counter*4;  
							     // sp point to the stack top(lowest address), 
								 // do not move it anymore.
	mov		r9, sp	// r9 is free now, let it point to the next empty room in stack, 
					// we will fill arg into that address;


// put the args left into stack if we have any
.Lfill_arg_into_stack:
	ldrb    ip, [r7], #1         // use the saved signature pointer r7;
	cmp     ip, #0               // end?
	beq     .Lhandle_arg_out
	// not end

	cmp     ip, #'D'             // 32 or 64-bit?
    cmpne   ip, #'J'
    beq     .Lfill_stack_with_64
	b       .Lfill_stack_with_32

	.Lfill_stack_with_64:
		tst     r9, #7                      // last 3 bits are 000(8-byte aligned)?
		beq 	.Lfill_64_directly	        // true

		b 		.Lalign_and_fill_64		    // false

		.Lfill_64_directly:
			// [sp2] <- next 64-bit;
			//  from-pointer + 8;
			//  to-pointer + 8
			ldr   r6, [r8], #4	// r6 is free now, use it as temp container. 
								// go on withe the argv pointer above
			str   r6, [r9], #4	//
			ldr   r6, [r8], #4  // todo: better to move 64-bit by one command
			str   r6, [r9], #4
			b .Lfill_arg_into_stack;

		.Lalign_and_fill_64:
			add	  r9, r9,   #4   // sp+4
			ldr   r6, [r8], #4   // move 64b-bits
			str   r6, [r9], #4
			ldr   r6, [r8], #4
			str   r6, [r9], #4
			b .Lfill_arg_into_stack;

	.Lfill_stack_with_32:
		ldr   r6, [r8], #4
		str   r6, [r9], #4
		b .Lfill_arg_into_stack;


.Lhandle_arg_out:
	// handle pReturn
	ldr 	r6, [r4]     			// sp has changed, use original stack pointer r4
	ldrb    ip, [r6], #1
	cmp     ip, #'V'           	 	// V?
	beq   	.Lcall_car_function     // branch if true
	// not V

	cmp r5, #1              		// r1 empty?
	bne .Lcheck_r2_for_out			// false
		ldreq     r1, [r4, #8]  		// attention: use original stack pointer to get pReturn
		b		 .Lcall_car_function; 	// don't forget to skip the following code

	.Lcheck_r2_for_out:
		cmp r5, #2              		// r2 empty?
		bne .Lcheck_r3_for_out			// false
			ldreq     r2, [r4, #8]
			b		 .Lcall_car_function; 	// don't forget to skip the following code

		.Lcheck_r3_for_out:
			cmp r5, #3              	// r3 empty?
			bne .Lfill_out_into_stack	// false
				ldreq     r3, [r4, #8]
				b		 .Lcall_car_function; 	// don't forget to skip the following code
		.Lfill_out_into_stack:
			ldr   r6, [r4, #8]
			str   r6, [r9], #4
			// no goto needed here.

.Lcall_car_function:
	ldr     ip, [r4, #4]
	blx     ip

	// restore saved registers
	b .Lback_from_car_function


#if 0

/*
 * Spit out a "we were here", preserving all registers.  (The attempt
 * to save ip won't work, but we need to save an even number of
 * registers for EABI 64-bit stack alignment.)
 */
     .macro SQUEAK num
common_squeak\num:
    stmfd   sp!, {r0, r1, r2, r3, ip, lr}
    ldr     r0, strSqueak
    mov     r1, #\num
    bl      printf
#ifdef __ARM_HAVE_PC_INTERWORK
    ldmfd   sp!, {r0, r1, r2, r3, ip, pc}
#else
    ldmfd   sp!, {r0, r1, r2, r3, ip, lr}
    bx      lr
#endif
    .endm

    SQUEAK  0
    SQUEAK  1
    SQUEAK  2
    SQUEAK  3
    SQUEAK  4
    SQUEAK  5

strSqueak:
    .word   .LstrSqueak
.LstrSqueak:
    .asciz  "<%d>"

    .align  2

#endif

#endif /*__ARM_EABI__*/
