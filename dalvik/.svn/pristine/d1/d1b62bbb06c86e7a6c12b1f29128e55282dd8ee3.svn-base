//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(__INTERLOCKED_H__)
#define __INTERLOCKED_H__

// mayq, _atomic.h -> el_atomic.h
#include <el_atomic.h>

// The Interlocked class provides the mechanism for synchronizing
// access to a variable that is shared by multiple threads.
// The threads of different processes can use this mechanism
// if the variable is in shared memory.
//
class Interlocked                   // class of atomic operations
{
public:
    // increase m_addend by one
    //
    _ELASTOS Int32 Increment();

    // decrease m_addend by one
    //
    _ELASTOS Int32 Decrement();

    // swap m_addend with 'value'
    //
    _ELASTOS Int32 Exchange(_ELASTOS Int32 value);

    // increase m_addend by 'value' amount
    //
    _ELASTOS Int32 ExchangeAdd(_ELASTOS Int32 value);

    // conditional swapping
    //
    _ELASTOS Int32 CompareExchange(_ELASTOS Int32 xchg, _ELASTOS Int32 cmp);

    operator _ELASTOS Int32() const { return m_addend; }  // type conversions

    Interlocked() : m_addend(0) { }

private:
    _ELASTOS Int32 m_addend;
};

//==========================================================================
// Interlocked inline functions
//

// The Interlocked::Increment function atomically increments
// (increases by one) the value of the specified variable.
// The return value is the resulting incremented value.
//
INLINE _ELASTOS Int32 Interlocked::Increment()
{
    return __InterlockedIncrement(&m_addend);
}

// The Interlocked::Decrement function atomically decrements
// (decreases by one) the value of the specified variable.
// The return value is the resulting decremented value.
//
INLINE _ELASTOS Int32 Interlocked::Decrement()
{
    return __InterlockedDecrement(&m_addend);
}

// The Interlocked::Exchange function atomically exchanges a pair of values.
// The function returns the initial value of the specified variable.
//
INLINE _ELASTOS Int32 Interlocked::Exchange(_ELASTOS Int32 value)
{
    return __InterlockedExchange(&m_addend, value);
}

// The Interlocked::ExchangeAdd function performs an atomic addition of
// an increment value to the instance object.  The return value is the
// old value of the object.
//
INLINE _ELASTOS Int32 Interlocked::ExchangeAdd(_ELASTOS Int32 value)
{
    return __InterlockedExchangeAdd(&m_addend, value);
}

// The Interlocked::CompareExchange function performs an atomic comparison
// of the specified values and exchanges the values, based on the outcome of
// the comparison.  Parameter 'cmp' specifies the value to compare to that of
// the instance object.  Parameter 'xchg' specifies the exchange value.
// The return value is the old value of the instance.
//
INLINE _ELASTOS Int32 Interlocked::CompareExchange(
    _ELASTOS Int32 xchg, _ELASTOS Int32 cmp)
{
    return __InterlockedCompareExchange(&m_addend, xchg, cmp);
}

#endif // __INTERLOCKED_H__
