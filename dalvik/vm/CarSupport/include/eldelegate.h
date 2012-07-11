//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#include <assert.h>

#if !defined(__DELEGATE_H__)
#define __DELEGATE_H__

#if !defined(_openkode)
EXTERN_C void * __cdecl _Impl_Memset(void *, int, size_t);
#else
#define _Impl_Memset memset
#endif

typedef struct tagDelegate
{
    union
    {
        struct
        {
            void *pFunc;
            void *pThis;
        };
        _ELASTOS UInt64 delegate;
    };
} _Delegate;

typedef enum {
    CallbackType_PlainC = 0x00,
    CallbackType_CPP = 0x01,
    CallbackType_CAR = 0x02,
}CallbackType;

#define CallbackTypeMask 0x00000003
#define CallbackPtrMask  0xFFFFFFFC
/*
* The pointer must align at 4-byte boundary, so its lowest 2 bits
* are always 0. So, we can use that 2 bits saving FunctionType
* of _Delegate.pFunc
*
* if ((_Delegate.pFunc & CallbackTypeMask) == 0x00)
*     pFunc is a C style function
* else if ((_Delegate.pFunc & CallbackTypeMask) == 0x01)
*     pFunc is a normal CPP class member method
* else if ((_Delegate.pFunc & CallbackTypeMask) == 0x02)
*     pFunc is a car Class member method
*/

#ifdef __cplusplus
_ELASTOS_NAMESPACE_BEGIN
class EventHandler
{
public:
    EventHandler()
    {
        _Impl_Memset(&m_value, 0, sizeof(_Delegate));
        m_hackDomain = NULL;
        m_pCarObjClient = NULL;
    }

    EventHandler(void *pvFunc)
    {
        m_value.pThis = NULL;
        m_value.pFunc = pvFunc;
        m_hackDomain = NULL;
        m_pCarObjClient = NULL;
    }

    _ELASTOS Boolean operator == (EventHandler & er)
   {
        return ((m_value.pThis == er.m_value.pThis)
               && (GetFuncPtr() == er.GetFuncPtr()));
    }

    _ELASTOS Boolean operator != (EventHandler & er)
    {
        return !(*this == er);
    }

    void *GetThisPtr()
    {
        return m_value.pThis;
    }

    void *GetFuncPtr()
    {
        if (NULL == m_value.pFunc) return NULL;
#ifndef _GNUC
        return (void *)((Elastos::UInt32)m_value.pFunc & CallbackPtrMask);
#else
#if defined(_arm) || defined(_x86)
        // for gnu-arm-pe compiler, it is another story
        // an virtual function's address &Foo::Bar() is the offset of &vptr[0]
        //
        // In gnu-x86 compiler, the value of pointer pointing to virtual function
        // is index * 4 + 1. The code below calculates the true address of
        // function according to pThis and pFunc.
        //
        if ((Elastos::UInt32)m_value.pFunc & 0xFFFFF000) {
            return (void *)((Elastos::UInt32)m_value.pFunc & CallbackPtrMask);
        }
        else {
            m_value.pFunc = (void*)(
                    (int)(*(*(void***)m_value.pThis + ((int)m_value.pFunc >> 2)))
                    | ((int)m_value.pFunc & CallbackTypeMask) );
            return (void *)((Elastos::UInt32)m_value.pFunc & CallbackPtrMask);
        }
#else
        assert(0 && "your compiler is not support yet!\n");
        return NULL;
#endif  //_arm | _x86
#endif // _GNUC
    }

    CallbackType GetFuncType()
    {
        return (CallbackType)(CallbackTypeMask & (_ELASTOS Int32)m_value.pFunc);
    }

    static EventHandler Make(void* pvThis, void* pvFunc)
    {
        return EventHandler(pvThis, pvFunc, CallbackType_PlainC, NULL);
    }

    template <class T>
    static EventHandler Make(T* pvThis, void* pvFunc, CallbackType type)
    {
        assert(((type == CallbackType_CAR)
                                && Conversion<T, CCarObject>::exists)
                                || (type != CallbackType_CAR));
        return EventHandler(pvThis, pvFunc, type, (_IInterface*)pvThis);
    }

private:

    EventHandler(void *pvThis, void *pvFunc, CallbackType type, PInterface pObj)
    {
        m_value.pThis = pvThis;
        m_value.pFunc = pvFunc;
        m_hackDomain = NULL;

        m_value.pFunc = (_ELASTOS PVoid)((_ELASTOS Int32)m_value.pFunc | (CallbackTypeMask & type));
        m_pCarObjClient = pObj;
    }
    _Delegate m_value;

public:
    PInterface m_pCarObjClient;
    // Delete it after we implement domain, initialize it in ctor is enough now
    void* m_hackDomain;
};
_ELASTOS_NAMESPACE_END

#else  // C FileAccessMode
typedef  _Delegate EventHandler;
#endif // __cplusplus

#endif // __DELEGATE_H__
