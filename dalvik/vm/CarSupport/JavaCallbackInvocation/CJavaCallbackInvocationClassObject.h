
#ifndef __CAR_CJAVACALLBACKINVOCATIONCLASSOBJECT_H__
#define __CAR_CJAVACALLBACKINVOCATIONCLASSOBJECT_H__

#include "JavaCallbackInvocation_server.h"

class CJavaCallbackInvocationClassObject :
    public IObject,
    public ICJavaCallbackInvocationClassObject
{
public:
    CJavaCallbackInvocationClassObject(): m_cRef(0) {}

    CARAPI_(PInterface) Probe(
        /* [in] */ _ELASTOS REIID riid);

    CARAPI_(UInt32) AddRef();

    CARAPI_(UInt32) Release();

    CARAPI GetInterfaceID(
        /* [in] */ IInterface *pObject,
        /* [out] */ InterfaceID *pIID);

    CARAPI Aggregate(
        /* [in] */ AggrType type,
        /* [in] */ PInterface pObj);

    CARAPI GetDomain(
        /* [out] */ PInterface *ppObj);

    CARAPI GetClassID(
        /* [out] */ _ELASTOS ClassID *pCLSID);

    CARAPI CreateObject(
        /* [in] */ IInterface * pParam0,
        /* [in] */ const InterfaceID & Param1,
        /* [out] */ IInterface ** ppParam2);

    CARAPI StayResident(
        /* [in] */ Boolean Param0);

    CARAPI CreateObjectWithEnvSelf(
        /* [in] */ PVoid pParam0,
        /* [in] */ PVoid pParam1,
        /* [out] */ IInterface ** ppParam2);


private:
    Int32 m_cRef;
};

#endif // __CAR_CJAVACALLBACKINVOCATIONCLASSOBJECT_H__
