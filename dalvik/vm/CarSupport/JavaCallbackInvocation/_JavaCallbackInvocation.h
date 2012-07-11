interface ICJavaCallbackInvocationClassObject;
EXTERN_C ELAPI _Impl_AcquireCallbackHandler(PInterface pServerObj, _ELASTOS REIID iid, PInterface *ppHandler);


#ifndef __INTERFACE_ICJavaCallbackInvocationClassObject_DEFINED__
#define __INTERFACE_ICJavaCallbackInvocationClassObject_DEFINED__

CAR_INTERFACE("25BB6022-8312-2409-7290-888330870C13")
ICJavaCallbackInvocationClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICJavaCallbackInvocationClassObject*) Probe(PInterface pObj)
    {
        return (ICJavaCallbackInvocationClassObject*)pObj->Probe(EIID_ICJavaCallbackInvocationClassObject);
    }

    virtual CARAPI CreateObjectWithEnvSelf(
        /* [in] */ _ELASTOS PVoid pParam0,
        /* [in] */ _ELASTOS PVoid pParam1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_ICJavaCallbackInvocationClassObject_DEFINED__
