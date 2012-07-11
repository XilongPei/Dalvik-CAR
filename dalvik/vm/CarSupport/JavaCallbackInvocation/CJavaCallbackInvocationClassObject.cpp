
extern "C" {
#include "jni.h"
}

#include "CJavaCallbackInvocationClassObject.h"
#include "CJavaCallbackInvocation.h"

// we dont't use it actually, so define it here to use internal linkage.
//extern "C" Int32 g_dllLockCount;
Int32 g_dllLockCount = 0; // is 0 right?

extern "C" CJavaCallbackInvocationClassObject _g_CJavaCallbackInvocation_ClsObj;

CJavaCallbackInvocationClassObject _g_CJavaCallbackInvocation_ClsObj;

PInterface CJavaCallbackInvocationClassObject::Probe(
    /* [in] */ _ELASTOS REIID riid)
{
    if (EIID_IInterface == riid) {
        return (_IInterface *)this;
    }
    else if (EIID_IClassObject == riid) {
        return (IClassObject *)this;
    }
    else if (riid == EIID_ICJavaCallbackInvocationClassObject) {
        return (ICJavaCallbackInvocationClassObject *)this;
    }
    else if (EIID_GENERIC_INFO == riid) {
        return NULL;

    }

    return NULL;
}

UInt32 CJavaCallbackInvocationClassObject::AddRef(void)
{
    atomic_inc(&g_dllLockCount);
    return 2;
}

UInt32 CJavaCallbackInvocationClassObject::Release(void)
{
    atomic_dec(&g_dllLockCount);
    return 1;
}

ECode CJavaCallbackInvocationClassObject::GetInterfaceID(
    /* [in] */ IInterface *pObject,
    /* [out] */ InterfaceID *pIID)
{
    if (NULL == pIID) return E_INVALID_ARGUMENT;

    if (pObject == (IInterface *)(IObject *)this) {
        *pIID = EIID_IObject;
    }
    else if (pObject == (IInterface *)(ICJavaCallbackInvocationClassObject *)this) {
        *pIID = EIID_ICJavaCallbackInvocationClassObject;
    }
    else {
        return E_INVALID_ARGUMENT;
    }
    return NOERROR;
}

ECode CJavaCallbackInvocationClassObject::Aggregate(
    /* [in] */ AggregateType type,
    /* [in] */ PInterface pObj)
{
    return E_NOT_IMPLEMENTED;
}

ECode CJavaCallbackInvocationClassObject::GetDomain(
    /* [out] */ PInterface *ppObj)
{
    return E_NOT_IMPLEMENTED;
}

ECode CJavaCallbackInvocationClassObject::GetClassID(
    /* [out] */ ClassID *pCLSID)
{
    if (NULL == pCLSID) return E_INVALID_ARGUMENT;

    *pCLSID = ECLSID_CJavaCallbackInvocationClassObject;
    return NOERROR;
}

ECode CJavaCallbackInvocationClassObject::CreateObject(
    /* [in] */ PInterface pOuter,
    /* [in] */ _ELASTOS REIID riid,
    /* [out] */ PInterface *ppObj)
{
    return E_NO_DEFAULT_CTOR;
}

ECode CJavaCallbackInvocationClassObject::StayResident(
    /* [in] */ Boolean bIsStayResident)
{
    if (bIsStayResident) {
        atomic_inc(&g_dllLockCount);
    }
    else {
        atomic_dec(&g_dllLockCount);
    }
    return NOERROR;
}

ECode CJavaCallbackInvocationClassObject::CreateObjectWithEnvSelf(
    /* [in] */ PVoid pParam0,
    /* [in] */ PVoid pParam1,
    /* [out] */ IInterface ** ppParam2)
{
    return _CJavaCallbackInvocationCreateObject(
            pParam0,
            pParam1,
            ppParam2);
}


