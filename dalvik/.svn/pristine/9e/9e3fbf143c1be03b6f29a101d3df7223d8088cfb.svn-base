//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================


#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(__ATOMIC_H_)
#define __ATOMIC_H_

#include <elatypes.h>

#if !((defined(_EVC) || defined(_MSVC)) && defined(_arm))

#define InterlockedIncrement(x)             __InterlockedIncrement(x)
#define InterlockedDecrement(x)             __InterlockedDecrement(x)
#define InterlockedExchangeAdd(x, y)        __InterlockedExchangeAdd(x, y)
#define InterlockedExchange(x, y)           __InterlockedExchange(x, y)
#define InterlockedExchangePointer(x, y)    __InterlockedExchangePointer(x, y)
#define InterlockedCompareExchange(x,y,z)   __InterlockedCompareExchange(x,y,z)
#define InterlockedCompareExchangePointer(x, y, z) \
            __InterlockedCompareExchangePointer(x, y, z)

#if defined(_GNUC)

#ifndef __LOCK
#define __LOCK  "lock;"
#endif

#ifdef _arm
EXTERN_C _ELASTOS Int32 __cdecl SWPADD(_ELASTOS PInt32 pAddend,
    _ELASTOS Int32 increment);
EXTERN_C _ELASTOS Int32 __cdecl CMPSWP(_ELASTOS PInt32 pDestination,
    _ELASTOS Int32 exchange, _ELASTOS Int32 comperand);
#endif // _arm

INLINE _ELASTOS Int32 __InterlockedExchangeAdd(_ELASTOS PInt32 plAddend,
    _ELASTOS Int32 lIncrement)
{
    _ELASTOS Int32 lOriginalAddend;

#if defined(_x86)
    ASM(__LOCK
        "xadd   %%eax, (%%edx);"
        :"=a"(lOriginalAddend)
        :"a"(lIncrement), "d"(plAddend));
#elif defined(_arm)
    lOriginalAddend = SWPADD(plAddend, lIncrement);
#elif defined(_mips)
    ASM(
        "move   $14, %2;"
    "1:"
        "ll     $15, (%1);"
        "add    $13, $15, $14;"
        "sc     $13, (%1);"
        "beqz   $13, 1b;"
        "move   %0, $15;"
        :"=&r"(lOriginalAddend), "+&r"(plAddend)
        :"r"(lIncrement)
        :"$15", "$14", "$13");
#else
    $(error Unknown architecture)
#endif

    return lOriginalAddend;
}

INLINE _ELASTOS Int32 __InterlockedExchange(_ELASTOS PInt32 plTarget,
    _ELASTOS Int32 lValue)
{
    _ELASTOS Int32 lOriginalTarget;

#ifdef _x86
    ASM(__LOCK
        "xchg   %%eax, (%%edx);"
        :"=a"(lOriginalTarget)
        :"a"(lValue), "d"(plTarget));
#elif defined(_arm)
    ASM("swp    %0, %1, [%2];"
        :"=&r"(lOriginalTarget)
        :"r"(lValue), "r"(plTarget));
#elif defined(_mips)
    ASM(
        "move   $14, %2;"
    "1:"
        "ll     %0, (%1);"
        "or     $15, $14, $0;"
        "sc     $15, (%1);"
        "beqz   $15, 1b;"
        :"=r&"(lOriginalTarget)
        :"r"(plTarget), "r"(lValue)
        :"$15", "$14");
#else
    $(error Unknown architecture)
#endif

    return lOriginalTarget;
}

INLINE _ELASTOS PVoid __InterlockedExchangePointer(_ELASTOS PVoid *ppvTarget,
    _ELASTOS PVoid pvValue)
{
    _ELASTOS PVoid pvOriginalTarget;

#ifdef _x86
    ASM(__LOCK
        "xchg   %%eax, (%%edx);"
        :"=a"(pvOriginalTarget)
        :"a"(pvValue), "d"(ppvTarget));
#elif defined(_arm)
    ASM("swp    %0, %1, [%2];"
        :"=&r"(pvOriginalTarget)
        :"r"(pvValue), "r"(ppvTarget));
#elif defined(_mips)
    ASM(
        "move   $14, %2;"
    "1:"
        "ll     %0, (%1);"
        "or     $15, $14, $0;"
        "sc     $15, (%1);"
        "beqz   $15, 1b;"
        :"=r&"(pvOriginalTarget)
        :"r"(ppvTarget), "r"(pvValue)
        :"$15", "$14");
#else
    $(error Unknown architecture)
#endif

    return pvOriginalTarget;
}

INLINE _ELASTOS Int32 __InterlockedCompareExchange(
    _ELASTOS PInt32 plDestination, _ELASTOS Int32 lExchange,
    _ELASTOS Int32 lComparand)
{
    _ELASTOS Int32 lOriginalDestination;

#ifdef _x86
    ASM(__LOCK
        "cmpxchg    %%ecx, (%%edx);"
        :"=a"(lOriginalDestination)
        :"a"(lComparand), "c"(lExchange), "d"(plDestination));
#elif defined(_arm)
    lOriginalDestination = CMPSWP(plDestination, lExchange, lComparand);
#elif defined(_mips)
    ASM(
        "move   $15, %3;"       // load the lComparand
    "2:"
        "ll     $14, (%1);"     // load the plDestination
        "move   %0, $14;"
        "bne    $15, $14, 1f;"
        "move   $14, %2;"
    "1:"
        "sc     $14, (%1);"
        "beqz   $14, 2b;"
        :"=&r"(lOriginalDestination), "+&r"(plDestination)
        :"r"(lExchange), "r"(lComparand)
        :"$15", "$14");
#else
    $(error Unknown architecture)
#endif

    return lOriginalDestination;
}

INLINE _ELASTOS PVoid __InterlockedCompareExchangePointer(
    _ELASTOS PVoid *ppvDestination, _ELASTOS PVoid pvExchange,
    _ELASTOS PVoid pvComparand)
{
    _ELASTOS PVoid pvOriginalDestination;

#ifdef _x86
    ASM(__LOCK
        "cmpxchg    %%ecx, (%%edx);"
        :"=a"(pvOriginalDestination)
        :"a"(pvComparand), "c"(pvExchange), "d"(ppvDestination));
#elif defined(_arm)
    pvOriginalDestination = (_ELASTOS PVoid)CMPSWP(
        (_ELASTOS PInt32)ppvDestination,
        (_ELASTOS Int32)pvExchange,
        (_ELASTOS Int32)pvComparand);
#elif defined(_mips)
    ASM(
        "move   $15, %3;"       // load the lComparand
    "2:"
        "ll     $14, (%1);"     // load the plDestination
        "move   %0, $14;"
        "bne    $15, $14, 1f;"
        "move   $14, %2;"
    "1:"
        "sc     $14, (%1);"
        "beqz   $14, 2b;"
        :"=r&"(pvOriginalDestination), "+r&"(ppvDestination)
        :"r"(pvExchange), "r"(pvComparand)
        :"$15", "$14");
#else
    $(error Unknown architecture)
#endif

    return pvOriginalDestination;
}

INLINE _ELASTOS Int32 __InterlockedIncrement(_ELASTOS PInt32 plAddend)
{
    _ELASTOS Int32 lOriginalAddend;

#ifdef _x86
    ASM("movl   $1, %%eax;"
        __LOCK
        "xadd   %%eax, (%%edx);"
        "inc    %%eax;"
        :"=a"(lOriginalAddend)
        :"d"(plAddend));
#elif defined(_arm)
    lOriginalAddend = SWPADD(plAddend, 1);
    lOriginalAddend++;
#elif defined(_mips)
    ASM(
    "1:"
        "ll     $14, (%1);"
        "addiu  $14, $14, 1;"
        "move   %0, $14;"
        "sc     $14, (%1);"
        "beqz   $14, 1b;"
        :"=&r"(lOriginalAddend), "+&r"(plAddend)
        ::"$14");
#else
    $(error Unknown architecture)
#endif

    return lOriginalAddend;
}

INLINE _ELASTOS Int32 __InterlockedDecrement(_ELASTOS PInt32 plAddend)
{
    _ELASTOS Int32 lOriginalAddend;

#ifdef _x86
    ASM("movl   $-1, %%eax;"
        __LOCK
        "xadd   %%eax, (%%edx);"
        "dec    %%eax;"
        :"=a"(lOriginalAddend)
        :"d"(plAddend));
#elif defined(_arm)
    lOriginalAddend = SWPADD(plAddend, -1);
    lOriginalAddend--;
#elif defined(_mips)
    ASM(
    "1:"
        "ll     $14, (%1);"
        "addiu  $14, $14, -1;"
        "move   %0, $14;"
        "sc     $14, (%1);"
        "beqz   $14, 1b;"
        :"=r&"(lOriginalAddend), "+r&"(plAddend)
        ::"$14", "$13");
#else
    $(error Unknown architecture)
#endif

    return lOriginalAddend;
}

#else // !defined(_GNUC)

#pragma warning(disable:4035)

#ifdef _mips

#ifdef _XINHAO

#define     FORMAL     1

INLINE _ELASTOS Int32 __InterlockedIncrement(_ELASTOS PInt32 plAddend)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 36;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS Int32 lOriginalAddend;

    ASM(
    "InterlockedIncrement_1:"
        "ll     $14, 0(%1);"
        "addiu  $14, $14, 1;"
        "sw     $14, 0(%0);"
        "sc     $14, 0(%1);"
        "beqz   $14, InterlockedIncrement_1;",
        &lOriginalAddend, plAddend);

    return lOriginalAddend;
#endif
}

INLINE _ELASTOS Int32 __InterlockedDecrement(_ELASTOS PInt32 plAddend)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 37;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS Int32 lOriginalAddend;

    ASM(
    "InterlockedDecrement_1:"
        "ll     $14, (%1);"
        "addiu  $14, $14, -1;"
        "sw     $14, 0(%0);"
        "sc     $14, (%1);"
        "beqz   $14, InterlockedDecrement_1;",
        &lOriginalAddend, plAddend);

    return lOriginalAddend;
#endif
}

INLINE _ELASTOS Int32 __InterlockedExchangeAdd(_ELASTOS PInt32 plAddend,
    _ELASTOS Int32 lIncrement)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 38;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS Int32 lOriginalAddend;

    ASM(
        "move   $14, %2;"
    "InterlockedExchangeAdd_1:"
        "ll     $15, (%1);"
        "add    $13, $15, $14;"
        "sc     $13, (%1);"
        "beqz   $13, InterlockedExchangeAdd_1;"
        "sw     $15, 0(%0);",
        &lOriginalAddend, plAddend, lIncrement);

    return lOriginalAddend;
#endif
}

INLINE _ELASTOS Int32 __InterlockedExchange(_ELASTOS PInt32 plTarget,
    _ELASTOS Int32 lValue)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 39;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS Int32 lOriginalTarget;

    ASM(
        "move   $14, %2;"
    "InterlockedExchange_1:"
        "ll     $13, 0(%1);"
        "or     $15, $14, $0;"
        "sc     $15, (%1);"
        "beqz   $15, InterlockedExchange_1;"
        "sw     $13, 0(%0);",
        &lOriginalTarget, plTarget, lValue);

    return lOriginalTarget;
#endif
}

INLINE _ELASTOS PVoid __InterlockedExchangePointer(
    _ELASTOS PVoid * ppvTarget, _ELASTOS PVoid pvValue)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 40;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS PVoid pvOriginalTarget;

    ASM(
        "move   $14, %2;"
    "InterlockedExchangePointer_1:"
        "ll     $13, (%1);"
        "sw     $13, 0(%0);"
        "or     $15, $14, $0;"
        "sc     $15, (%1);"
        "beqz   $15, InterlockedExchangePointer_1;",
        &pvOriginalTarget, ppvTarget, pvValue);

    return pvOriginalTarget;
#endif
}

INLINE _ELASTOS Int32 __InterlockedCompareExchange(
    _ELASTOS PInt32 plDestination, _ELASTOS Int32 lExchange,
    _ELASTOS Int32 lComparand)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 41;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS Int32 lOriginalDestination;

    ASM(
        "move   t7, %3;"       // load the lComparand
    "InterlockedCompareExchange_2:"
        "ll     t6, (%1);"     // load the plDestination
        "sw     t6, 0(%0);"
        "bne    t7, t6, InterlockedCompareExchange_1;"
        "move   t6, %2;"
    "InterlockedCompareExchange_1:"
        "sc     t6, (%1);"
        "beqz   t6, InterlockedCompareExchange_2;",
        &lOriginalDestination, plDestination,
        lExchange, lComparand);

    return lOriginalDestination;
#endif
}

INLINE _ELASTOS PVoid __InterlockedCompareExchangePointer(
    _ELASTOS PVoid * ppvDestination, _ELASTOS PVoid pvExchange,
    _ELASTOS PVoid pvComparand)
{
#if FORMAL
    ASM(
        "ori     v0, zero, 42;"
        "syscall;"
        "jr     ra;");
#else
    _ELASTOS PVoid pvOriginalDestination;

    ASM(
        "move   $15, %3;"       // load the lComparand
    "InterlockedCompareExchangePointer_2:"
        "ll     $14, (%1);"     // load the plDestination
       "sw      $14, 0(%0);"
        "bne    $15, $14, InterlockedCompareExchangePointer_1;"
        "move   $14, %2;"
    "InterlockedCompareExchangePointer_1:"
        "sc     $14, (%1);"
        "beqz   $14, InterlockedCompareExchangePointer_2;",
        &pvOriginalDestination, ppvDestination,
        pvExchange, pvComparand);

    return pvOriginalDestination;
#endif
}

#else

_ELASTOS Int32 __InterlockedIncrement(_ELASTOS PInt32 plAddend);
_ELASTOS Int32 __InterlockedDecrement(_ELASTOS PInt32 plAddend);
_ELASTOS Int32 __InterlockedExchangeAdd(_ELASTOS PInt32 plAddend,
    _ELASTOS Int32 lIncrement);
_ELASTOS Int32 __InterlockedExchange(_ELASTOS PInt32 plTarget,
    _ELASTOS Int32 lValue);
_ELASTOS PVoid __InterlockedExchangePointer(_ELASTOS PVoid * ppvTarget,
    _ELASTOS PVoid pvValue);
_ELASTOS Int32 __InterlockedCompareExchange(
            _ELASTOS PInt32 plDestination, _ELASTOS Int32 lExchange,
    _ELASTOS Int32 lComparand);
_ELASTOS PVoid __InterlockedCompareExchangePointer(
            _ELASTOS PVoid * ppvDestination, _ELASTOS PVoid pvExchange,
    _ELASTOS PVoid pvComparand);
#endif
#elif defined(_arm)
EXTERN_C _ELASTOS Int32 InterlockedIncrement(_ELASTOS PInt32 pAddend);
EXTERN_C _ELASTOS Int32 InterlockedDecrement(_ELASTOS PInt32 pAddend);
EXTERN_C _ELASTOS Int32 InterlockedExchangeAdd(_ELASTOS PInt32 pAddend,
    _ELASTOS Int32 increment);
EXTERN_C _ELASTOS Int32 InterlockedExchange(_ELASTOS PInt32 pTarget,
    _ELASTOS Int32 value);
EXTERN_C _ELASTOS PVoid InterlockedExchangePointer(_ELASTOS PVoid * pTarget,
    _ELASTOS PVoid value);
EXTERN_C _ELASTOS Int32 InterlockedCompareExchange(
            _ELASTOS PInt32 destination, _ELASTOS Int32 exchange,
    _ELASTOS Int32 comperand);
EXTERN_C _ELASTOS Int32 InterlockedCompareExchangeEx(
            _ELASTOS PInt32 destination, _ELASTOS Int32 exchange,
    _ELASTOS Int32 comperand);
EXTERN_C _ELASTOS PVoid InterlockedCompareExchangePointer(
            _ELASTOS PVoid * pDestination, _ELASTOS PVoid exchange,
    _ELASTOS PVoid comperand);

#define __InterlockedIncrement(x)             InterlockedIncrement(x)
#define __InterlockedDecrement(x)             InterlockedDecrement(x)
#define __InterlockedExchangeAdd(x, y)        InterlockedExchangeAdd(x, y)
#define __InterlockedExchange(x, y)           InterlockedExchange(x, y)
#define __InterlockedExchangePointer(x, y)    InterlockedExchangePointer(x, y)
#define __InterlockedCompareExchange(x,y,z)   InterlockedCompareExchange(x,y,z)
#define __InterlockedCompareExchangeEx(x, y, z) \
            InterlockedCompareExchangeEx(x, y, z)
#define __InterlockedCompareExchangePointer(x, y, z) \
            InterlockedCompareExchangePointer(x, y, z)

#else
/*
 * The InterlockedIncrement function both increments (increases by one)
 * the value of the specified 32-bit variable and checks the resulting value.
 * InterlockedIncrement prevents more than one thread from using
 * the InterlockedDecrement or InterlockedIncrement function to
 * access the same variable simultaneously.
 */
INLINE _ELASTOS Int32 __InterlockedIncrement(_ELASTOS PInt32 plAddend)
{
#if defined(_x86)
    __asm {
        mov     eax,    1
        mov     ecx,    plAddend
        lock    xadd    [ecx], eax
        inc     eax
    }
#else
    $error unknown architecture
#endif
}

/*
 * The InterlockedDecrement function both decrements (decreases by one)
 * the value of the specified 32-bit variable and checks the resulting value.
 * InterlockedDecrement prevents more than one thread from using
 * the InterlockedDecrement or InterlockedIncrement function to
 * access the same variable simultaneously.
 */
INLINE _ELASTOS Int32 __InterlockedDecrement(_ELASTOS PInt32 plAddend)
{
#if defined(_x86)
    __asm {
        mov     eax,    -1
        mov     ecx,    plAddend
        lock    xadd    [ecx], eax
        dec     eax
    }
#else
    $error unknown architecture
#endif
}

/*
 * The InterlockExchangeAdd function performs an atomic addition of
 * an increment value to an addend variable. The function prevents
 * more than one thread from using the same variable simultaneously.
 */
INLINE _ELASTOS Int32 __InterlockedExchangeAdd(_ELASTOS PInt32 plAddend,
    _ELASTOS Int32 lIncrement)
{
#if defined(_x86)
    __asm {
        mov     eax,    lIncrement
        mov     ecx,    plAddend
        lock    xadd    [ecx],    eax
    }
#else
    $error unknown architecture
#endif
}

/*
 * The InterlockedExchange function atomically exchanges
 * a pair of 32-bit values.  The prior value of the _ELASTOS Int32 value
 * pointed to by Target indicates success.
 */
INLINE _ELASTOS Int32 __InterlockedExchange(_ELASTOS PInt32 plTarget,
    _ELASTOS Int32 lValue)
{
#if defined(_x86)
    __asm {
        mov     eax,    lValue
        mov     ecx,    plTarget
        lock    xchg    [ecx],   eax
    }
#else
    $error unknown architecture
#endif
}

/*
 * The InterlockedExchangePointer function atomically exchanges
 * a pair of values. The function prevents more than one thread
 * from using the same variable simultaneously.
 *
 * If you are exchanging pointer values, this function supersedes
 * the InterlockedExchange function.
 */
INLINE _ELASTOS PVoid __InterlockedExchangePointer(
   _ELASTOS PVoid * ppvTarget, _ELASTOS PVoid pvValue)
{
#if defined(_x86)
    __asm {
        mov     eax,    pvValue
        mov     ecx,    ppvTarget
        lock    xchg    [ecx],  eax
    }
#else
    $error unknown architecture
#endif
}

/*
 * The InterlockedCompareExchange function performs an atomic comparison
 * of the specified values and exchanges the values, based on the outcome
 * of the comparison. The function prevents more than one thread from
 * using the same variable simultaneously.
 *
 * If you are exchanging pointer values, this function has been superseded
 * by the InterlockedCompareExchangePointer function.
 */
INLINE _ELASTOS Int32 __InterlockedCompareExchange(
    _ELASTOS PInt32 plDestination, _ELASTOS Int32 lExchange,
    _ELASTOS Int32 lComparand)
{
#if defined(_x86)
    __asm {
        mov     eax,    lComparand
        mov     ecx,    plDestination
        mov     edx,    lExchange
        lock    cmpxchg [ecx],  edx
    }
#else
    $error unknown architecture
#endif
}

/*
 * The InterlockedCompareExchangePointer function performs an atomic
 * comparison of the specified values parameters and exchanges the
 * values, based on the outcome of the comparison. More than one
 * thread cannot use the same variable simultaneously.
 *
 * If you are exchanging pointer values, this function supersedes
 * the InterlockedCompareExchange function.
 */
INLINE _ELASTOS PVoid __InterlockedCompareExchangePointer(
    _ELASTOS PVoid * ppvDestination, _ELASTOS PVoid pvExchange,
    _ELASTOS PVoid pvComparand)
{
#if defined(_x86)
    __asm {
        mov     eax,    pvComparand
        mov     ecx,    ppvDestination
        mov     edx,    pvExchange
        lock    cmpxchg [ecx],  edx
    }
#else
    $error unknown architecture
#endif
}

#endif
#pragma warning(default:4035)

#endif // defined(_GNUC)

#else // !(defined(_EVC) && defined(_arm))

EXTERN_C _ELASTOS Int32 InterlockedIncrement(_ELASTOS PInt32 pAddend);
EXTERN_C _ELASTOS Int32 InterlockedDecrement(_ELASTOS PInt32 pAddend);
EXTERN_C _ELASTOS Int32 InterlockedExchangeAdd(_ELASTOS PInt32 pAddend,
    _ELASTOS Int32 increment);
EXTERN_C _ELASTOS Int32 InterlockedExchange(_ELASTOS PInt32 pTarget,
    _ELASTOS Int32 value);
EXTERN_C _ELASTOS PVoid InterlockedExchangePointer(_ELASTOS PVoid * pTarget,
    _ELASTOS PVoid value);
EXTERN_C _ELASTOS Int32 InterlockedCompareExchange(
            _ELASTOS PInt32 destination, _ELASTOS Int32 exchange,
    _ELASTOS Int32 comperand);
EXTERN_C _ELASTOS Int32 InterlockedCompareExchangeEx(
            _ELASTOS PInt32 destination, _ELASTOS Int32 exchange,
    _ELASTOS Int32 comperand);
EXTERN_C _ELASTOS PVoid InterlockedCompareExchangePointer(
            _ELASTOS PVoid * pDestination, _ELASTOS PVoid exchange,
    _ELASTOS PVoid comperand);

#define __InterlockedIncrement(x)             InterlockedIncrement(x)
#define __InterlockedDecrement(x)             InterlockedDecrement(x)
#define __InterlockedExchangeAdd(x, y)        InterlockedExchangeAdd(x, y)
#define __InterlockedExchange(x, y)           InterlockedExchange(x, y)
#define __InterlockedExchangePointer(x, y)    InterlockedExchangePointer(x, y)
#define __InterlockedCompareExchange(x,y,z)   InterlockedCompareExchange(x,y,z)
#define __InterlockedCompareExchangeEx(x, y, z) \
            InterlockedCompareExchangeEx(x, y, z)
#define __InterlockedCompareExchangePointer(x, y, z) \
            InterlockedCompareExchangePointer(x, y, z)

#endif // !(defined(_EVC) && defined(_arm))

#endif // __ATOMIC_H_
