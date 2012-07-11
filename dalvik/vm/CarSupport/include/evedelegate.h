//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __CAR_DEVICEEVENTDISPATCHER_H__
#define __CAR_DEVICEEVENTDISPATCHER_H__

#ifdef __cplusplus

class CDeviceEventHandler
{
public:
    CDeviceEventHandler (_ELASTOS EventHandler ed);
    ~CDeviceEventHandler();
    operator IDeviceEventDispatcher *();
private :
    CDeviceEventHandler() {}
    IDeviceEventDispatcher *m_pIDeviceEventDispatcher;
};

INLINE CDeviceEventHandler :: CDeviceEventHandler(_ELASTOS EventHandler ed)
    :m_pIDeviceEventDispatcher(NULL)
{
#if 0
    _CObject_CreateInstance(ECLSID_CDeviceEventDispatcher, CTX_SAME_DOMAIN,
        EIID_IDeviceEventDispatcher, (PInterface *)&m_pIDeviceEventDispatcher);
#endif
    if (NULL == m_pIDeviceEventDispatcher) return;
    _ELASTOS PVoid pvThis = NULL;
    _ELASTOS PVoid pvFunc = NULL;
    pvThis = ed.GetThisPtr();
    pvFunc = ed.GetFuncPtr();
    m_pIDeviceEventDispatcher->SetEventHandler((_ELASTOS Int32)pvThis,
        (_ELASTOS Int32)pvFunc);
}

INLINE CDeviceEventHandler::~CDeviceEventHandler()
{
    if (m_pIDeviceEventDispatcher) m_pIDeviceEventDispatcher->Release();
}

INLINE CDeviceEventHandler::operator IDeviceEventDispatcher *()
{
    return m_pIDeviceEventDispatcher;
}

#endif //__cplusplus

#endif // __CAR_DEVICEEVENTDISPATCHER_H__
