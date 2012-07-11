//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#ifndef __ELASTOS_CRITSEC_H__
#define __ELASTOS_CRITSEC_H__

_ELASTOS_NAMESPACE_BEGIN

class CCriticalSection : public CriticalSection
{
public:

    CCriticalSection()  { event = NULL; }

    ~CCriticalSection() { if (NULL != event) Terminate(); }

    _ELASTOS ECode Initialize()  { return _CCriticalSection_Initialize(this); }

    void Enter()        { _CCriticalSection_Enter(this); }

    _ELASTOS ECode TryEnter(Boolean *pEntered)
    {
        return _CCriticalSection_TryEnter(this, pEntered);
    }

    void Leave()        { _CCriticalSection_Leave(this); }

    void Terminate()    { _CCriticalSection_Terminate(this); }
};

_ELASTOS_NAMESPACE_END

#endif // __ELASTOS_CRITSEC_H__
