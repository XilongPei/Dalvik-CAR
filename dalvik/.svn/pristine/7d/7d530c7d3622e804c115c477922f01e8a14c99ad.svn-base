/** @addtogroup CARRef
  *   @{
  */

//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __CAR_CARAPI_H__
#define __CAR_CARAPI_H__

#include <eldelegate.h>

#ifdef __cplusplus
extern "C" {
#endif

struct EzMultiQI
{
    const _ELASTOS InterfaceID * pIID;
    PInterface     pObject;
    _ELASTOS ECode     ec;
};
typedef struct EzMultiQI EzMultiQI, *PMULTIQI;
interface IContext;
typedef interface IContext* PContext;

#define CTX_INVALID_DOMAIN          ((PContext)0x0000)
#define CTX_SAME_DOMAIN             ((PContext)0x0001)
#define CTX_DIFF_DOMAIN             ((PContext)0x0002)
#define CTX_DEFAULT                 ((PContext)0x0003)
#define CTX_DIFF_MACHINE            ((PContext)0x0004)
#define CTX_SAME_PROCESS            CTX_SAME_DOMAIN
#define CTX_DIFF_PROCESS            CTX_DIFF_DOMAIN

#define CTX_USER_2_KERN             ((PContext)0x0100)
#define CTX_KERN_2_USER             ((PContext)0x0200)

#define CTX_MAX_NUMBER              ((PContext)0xFFFF)
#define IS_INVALID_CONTEXT(dw)      ((dw == CTX_INVALID_DOMAIN))
#define IS_CTX_NUMBER(dw)           ((!IS_INVALID_CONTEXT(dw)) && \
	                                 ((dw == CTX_SAME_DOMAIN) || \
	                                  (dw == CTX_DIFF_DOMAIN) || \
	                                  (dw == CTX_DEFAULT) || \
	                                  (dw == CTX_DIFF_MACHINE)))

ELAPI _CObject_CreateInstance(
    /* [in] */ _ELASTOS RClassID rclsid,
    /* [in] */ PContext pContext,
    /* [in] */ _ELASTOS REIID riid,
    /* [out] */ PInterface *ppObject);

ELAPI _CObject_CreateInstanceEx(
    /* [in] */ _ELASTOS RClassID rclsid,
    /* [in] */ PContext pContext,
    /* [in] */ _ELASTOS UInt32 cmq,
    /* [out] */ PMULTIQI pResults);

ELAPI _CObject_AcquireClassFactory(
    /* [in] */ _ELASTOS RClassID rclsid,
    /* [in] */ PContext pContext,
    /* [in] */ _ELASTOS REIID iid,
    /* [out] */ PInterface *ppObject);

ELAPI_(_ELASTOS Boolean) _CObject_Compare(
    /* [in] */ PInterface pObjectA,
    /* [in] */ PInterface pObjectB);

ELAPI _CObject_AttachAspect(
    /* [in] */ PInterface pAggregator,
    /* [in] */ _ELASTOS RClassID rAspectClsid);

ELAPI _CObject_DetachAspect(
    /* [in] */ PInterface pAggregator,
    /* [in] */ _ELASTOS RClassID rAspectClsid);

ELAPI _CObject_ReleaseAtProcessExit(
    /* [in] */ PInterface pObject);

ELAPI _CObject_ReleaseAtThreadQuit(
    /* [in] */ PInterface PInterface);

ELAPI _CObject_ReleaseAtAppletFinish(
    /* [in] */ PInterface PInterface);

ELAPI _CObject_EnterContext(
    /* [in] */ PInterface pObj,
    /* [in] */ PContext pCtx);

ELAPI _CObject_LeaveContext(
    /* [in] */ PInterface pObj,
    /* [in] */ PContext pCtx);

typedef interface IModuleMetadata *PMMETADATA;
typedef interface IClassMetadata *PCMETADATA;
typedef interface IInterfaceMetadata *PIMETADATA;
typedef interface ICallbackSink *PCALLBACKSINK;
typedef interface ICallbackRendezvous* PCallbackRendezvous;

ELAPI EzGetModuleMetadata(
    /* [in] */ PInterface pObject,
    /* [out] */ PMMETADATA *ppModuleMetadata);

ELAPI EzGetClassMetadata(
    /* [in] */ PInterface pObject,
    /* [out] */ PCMETADATA *ppClassMetadata);

ELAPI EzGetInterfaceMetadata(
    /* [in] */ PInterface pObject,
    /* [out] */ PIMETADATA *ppIMetadata);

ELAPI _CObject_AcquireCallbackSink(
    /* [in] */ PInterface pObject,
    /* [out] */ PCALLBACKSINK *ppCallbackSink);

ELAPI _CObject_AddCallback(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [in] */ _ELASTOS EventHandler delegate);

ELAPI _CObject_RemoveCallback(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [in] */ _ELASTOS EventHandler delegate);

ELAPI _CObject_RemoveAllCallbacks(
    /* [in] */ PInterface pServerObj);

ELAPI _CObject_AcquireCallbackRendezvous(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [out] */ PCallbackRendezvous* ppCallbackRendezvous);

ELAPI_(_ELASTOS Boolean) _CModule_CanUnloadAllModules();

ELAPI_(_ELASTOS PVoid) _CMemoryHeap_Alloc(_ELASTOS MemorySize size, _ELASTOS Boolean zeroMem);
ELAPI_(_ELASTOS PVoid) _CMemoryHeap_Realloc(_ELASTOS PVoid pMem, _ELASTOS MemorySize size);
ELAPI_(void) _CMemoryHeap_Free(_ELASTOS PVoid pMem);
ELAPI_(_ELASTOS Boolean) _CMemoryHeap_Trim(_ELASTOS MemorySize pad);
ELAPI _CMemoryHeap_GetStatistics(
        _ELASTOS MemorySize *pInUseBytes,
        _ELASTOS MemorySize *pSystemBytes,
        _ELASTOS MemorySize *pMaxSystemBytes);

// APIs for debug purpose
//
ELAPI _DebugHelper_SeedStringFromGuid(_ELASTOS REMuid, wchar_t *);
ELAPI _DebugHelper_NameFromGuid(_ELASTOS REMuid, wchar_t *);
ELAPI _DebugHelper_GuidFromSeedString(const wchar_t *, _ELASTOS PEMuid);

#define _MAX_SEED_LEN   255

#ifdef _win32
ELAPI _QueryFreeThreadedMarshaler(
    /* [in] */ _ELASTOS REIID riid,
    /* [out] */ PInterface *ppObj);
#endif // _win32

#ifdef __cplusplus
}
// extern "C"
#endif

#endif // __CAR_CARAPI_H__
