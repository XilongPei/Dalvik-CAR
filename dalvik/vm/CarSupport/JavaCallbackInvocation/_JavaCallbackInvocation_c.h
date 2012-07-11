typedef interface ICJavaCallbackInvocationClassObject ICJavaCallbackInvocationClassObject;

typedef struct ICJavaCallbackInvocationClassObjectVtbl {
    PInterface (CARAPICALLTYPE *Probe)(
            ICJavaCallbackInvocationClassObject *pThis,
            /* [in] */ REIID riid);

    UInt32 (CARAPICALLTYPE *AddRef)(
            ICJavaCallbackInvocationClassObject *pThis);

    UInt32 (CARAPICALLTYPE *Release)(
            ICJavaCallbackInvocationClassObject *pThis);

    ECode (CARAPICALLTYPE *GetInterfaceID)(
            ICJavaCallbackInvocationClassObject *pThis,
            /* [in] */ IInterface *object,
            /* [in] */ InterfaceID *iid);

    ECode (CARAPICALLTYPE *CreateObject)(
            IClassObject *pThis,
            /* [in] */ IInterface * outer,
            /* [in] */ const InterfaceID * riid,
            /* [out] */ IInterface ** object);

    ECode (CARAPICALLTYPE *StayResident)(
            IClassObject *pThis,
            /* [in] */ Boolean bIsStayResident);

    ECode (CARAPICALLTYPE *CreateObjectWithEnvSelf)(
            ICJavaCallbackInvocationClassObject *pThis,
            /* [in] */ PVoid env,
            /* [in] */ PVoid self,
            /* [out] */ IInterface ** newObj);
}   ICJavaCallbackInvocationClassObjectVtbl;

interface ICJavaCallbackInvocationClassObject {
    CONST_VTBL struct ICJavaCallbackInvocationClassObjectVtbl *v;
};
