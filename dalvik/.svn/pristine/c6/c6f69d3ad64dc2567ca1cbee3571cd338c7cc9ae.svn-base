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
 * This version supports 32-bit x86
 */

/*
Function prototype:

void dvmPlatformCARInvoke(void* pCARObejct, int argInfo, int argc,
    const u4* argv, const char* signature, void* func, JValue* pReturn)

The method we are calling has the form:

  ECode func(void* pCARObejct, ..., void* out)	// ECode == int; impossible to has two out or more
    -or-
  ECode func(void* pCARObejct, ...)
  
We receive a collection of 32-bit values which correspond to arguments from
the interpreter (e.g. float occupies one, double occupies two).  It's up to
us to convert these into local calling conventions.
*/

/*
x86 notes:

The native code expects arguments on the stack, pushed from right to left.
This matches what Dalvik is passing here.

EAX, EDX and ECX are scratch.

4-byte alignment is required for long long and double, so we won't pad

Non-FP return types <= 4 bytes come back in EAX
Non-FP return types of 8 bytes come back in EAX:EDX, with lsw in EAX.
Float and double returned on top of FP stack.

*/

    .text
    .global dvmPlatformCARInvoke
    .type   dvmPlatformCARInvoke, @function
/*
 * these offsets are relative to ebp, to understand why 8, 12, ..., refer to:
 * http://unixwiz.net/techtips/win32-callconv-asm.html
 * the calling convention here is __cdecl
 * On entry:
 *  [ 8]  arg0  pCARObejct
 *  [12]  arg1  arg info
 *  [16]  arg2  argc
 *  [20]  arg3  argv
 *  [24]  arg4  short signature
 *  [28]  arg5  func
 *  [32]  arg6  pReturn
 *
 *
 * argInfo (32-bit int) layout:
 *   SRRRZZZZ ZZZZZZZZ AAAAAAAA AAAAAAAA
 *
 *   Z - reserved
 *   S - if set, argInfo hints are invalid
 *   R - return type, must be a pointer(32-bit)
 *   A - size of the variable argument block in 32-bit words
 *
 */
dvmPlatformCARInvoke:
/* Establish the frame pointer, spill & align to 16b */
	// AT&T syntax, not Intel syntax
    pushl    %ebp			// eip is saved atomatically by "call", but ebp is not,
							// so save it manually; registers are 32-bit wide; l represents long;
    movl     %esp,%ebp      // movl src, dest; ebp point to new frame
    pushl    %edi			// save registers which we will use in this function
    pushl    %esi
    pushl    %ebx
    subl     $12,%esp		// why minus 12? coppied from Call386ABI.S, I am sure it's harmless.
/* For 386 ABI, argInfo hints should always be valid.  Abort if not. */
	// valid if the most significant bit of arg info is 0;
    movl     12(%ebp),%ebx	// ebx = arg info;
    testl    %ebx,%ebx		// and
    js       dvmAbort		// jump if < 0
/* Get the size of the variable region and grow (preserving alignment) */
/* algorithm used here is obscure but effective.
 * it calculate how many bytes of stack we should reserve for parameters.
 * the relationship between number of parameters and increment of stack is as below:
 * number of parameters -------------- increment of stack
 *         0            --------------      0
 *        1~4           --------------      16
 *        5~8           --------------      32
 *        others omitted
 * attention: size of stack increases discontiguously and the increment is 16.
 * 			  in the first column, 1 means argv is 1 32-bit wide.
 * 			  in the next column, 16 means we should reserve 16 bytes for argv
 */
	movl     %ebx,%ecx			// ecx = arg info;
    leal     12(,%ecx,4),%ecx	// ecx = ecx*4+12
    andl     $0x0003FFF0,%ecx	// get increment of stack for argv, trick used
    subl     %ecx,%esp			// esp = esp - ecx;
	// "AAAAAAAA AAAAAAAA" of arg info has taken [out] parameter into account,
	// so we don't need to expand stack for pReturn specially.
handleCARObject:
/* Handle pCARObejct */
    movl     8(%ebp),%ecx	// ecx = pCARObejct
	pushl    %ecx			// push pCARObejct
	
/* Now, copy the variable arguments region */
    movl     12(%ebp),%ecx		// ecx = arg info
    andl     $0x0000FFFF,%ecx	// filter for the least significant 16 bits, 
								// it represents size of the variable argument block in 32-bit words
    movl     20(%ebp),%esi		// esi = argv£¬esi points to source
	leal     4(%esp),%edi	// make edi point to destination; esp points to pCARObejct now, 
							// the destination area begins from [esp+4]
    cld		// esi=esi+4; edi=edi+4; per loop
    rep		// ecx-- per loop
    movsd	// move argv[i] from esi to edi, double words per loop
	// push pReturn if exist
	movl     12(%ebp),%ebx	// ebx = arg info;
	sarl      $28,%ebx		// ebx = RRR from arg info
    testl    %ebx,%ebx		// void?
    je       callCARFunc
	movl	 32(%ebp), %ecx	// ecx = pReturn
	movl	 %ecx, (%edi)	// assume last block(4 bytes) of argv is copied into [addr], 
							// edi points to [addr+1] now,
							// put pReturn into [addr+1]~[addr+4]
callCARFunc:
/* Ready to go - call the native code */
    call     *28(%ebp)
// this function's return-type is void, so nothing to do with return value.
cleanUpAndExit:
    leal     -12(%ebp),%esp	// make esp point to the memory unit that holds ebx; 
							// clean stack at the same time
    pop      %ebx			// pop registers in reverse order
    pop      %esi
    pop      %edi
    pop      %ebp			// restore old ebp
    ret
    .size    dvmPlatformCARInvoke, .-dvmPlatformCARInvoke
    .section .note.GNU-stack,"",@progbits

/*
if you can not understand the code above, these materials may help:
1 Intel and AT&T Syntax.
	http://www.imada.sdu.dk/~kslarsen/Courses/dm516-2009-spring/Litteratur/IntelnATT.htm
2 AT&T instrunctin set
	http://www.cppblog.com/Panda/archive/2009/12/08/102799.aspx
3 floating point arithmetic
	http://www.alloc.net/blog/162.html
4 Intel x86 Function-call Conventions - Assembly View
	http://unixwiz.net/techtips/win32-callconv-asm.html
5 lea
	http://www-scm.tees.ac.uk/users/u0000408/Instruct/_LEA.htm
*/