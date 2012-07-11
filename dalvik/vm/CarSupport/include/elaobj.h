//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __CAR_ELAOBJ_H__
#define __CAR_ELAOBJ_H__

#include <elatypes.h>

#define CONST_VTBL          const

#ifdef __cplusplus
extern "C" {
#endif

typedef interface IInterface IInterface;
typedef interface IInterface SynchronizedIObject;
typedef interface IAspect IAspect;

typedef interface IInterface *PInterface;
typedef interface IAspect *PASPECT;

typedef enum AggregateType
{
    AggrType_AspectAttach = 1,
    AggrType_AspectDetach,
    AggrType_Aggregate,
    AggrType_Unaggregate,
    AggrType_ObjectEnter,
    AggrType_ObjectLeave,
    AggrType_EnteredContext,
    AggrType_LeftContext,
    AggrType_Connect,
    AggrType_Disconnect,
    AggrType_AddConnection,
    AggrType_FriendEnter,
    AggrType_FriendLeave,
    AggrType_ChildConstruct,
    AggrType_ChildDestruct,
    AggrType_ParentAttach,
    AggrType_AspectDetached,
}AggregateType, AggrType;

#ifndef DLLEXP
#ifdef _UNDEFDLLEXP
#define DLLEXP
#else
#define DLLEXP __declspec(dllimport)
#endif
#endif

EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IInterface;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IAspect;

#define BASE_INTERFACE_METHOD_COUNT 4

#ifdef __cplusplus

// mayq, when CARAPI is unfoldered, you will see __stdcall, but __stdcall
// is undefined. so we define it here
#define __stdcall

CAR_INTERFACE("00000000-0000-0000-C000-000000000066")
IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    virtual CARAPI_(_ELASTOS UInt32) AddRef() = 0;

    virtual CARAPI_(_ELASTOS UInt32) Release() = 0;

    virtual CARAPI GetInterfaceID(
            /* [in] */ IInterface *object,
            /* [out] */ _ELASTOS InterfaceID *iid) = 0;
};

CAR_INTERFACE("00000000-0000-0000-C000-000000000068")
IObject : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IObject*) Probe(PInterface pObj)
    {
        return (IObject*)pObj->Probe(EIID_IObject);
    }

    virtual CARAPI Aggregate(
            /* [in] */ AggregateType type,
            /* [in] */ IInterface *object) = 0;

    virtual CARAPI GetDomain(
            /* [out] */ IInterface **object) = 0;

    virtual CARAPI GetClassID(
            /* [out] */ _ELASTOS ClassID *clsid) = 0;
};

struct CCarObject{};

CAR_INTERFACE("00010002-0000-0000-C000-000000000066")
IAspect : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAspect*) Probe(PInterface pObj)
    {
        return (IAspect*)pObj->Probe(EIID_IAspect);
    }

    virtual CARAPI AspectAggregate(
            /* [in] */ AggregateType type,
            /* [in] */ PInterface pObject) = 0;

    virtual CARAPI AspectGetDomain(
            /* [out] */ PInterface *ppObject) = 0;

    virtual CARAPI GetAspectID(
            /* [out] */ _ELASTOS ClassID *clsid) = 0;
};

interface ICallbackSink;

CAR_INTERFACE("00010004-0000-0000-C000-000000000066")
ICallbackConnector : public IInterface
{
    virtual CARAPI AcquireCallbackSink(ICallbackSink **ppICallbackSink) = 0;

    virtual CARAPI CheckCallbackSinkConnection(_ELASTOS Int32 dwEvent) = 0;

    virtual CARAPI DisconnectCallbackSink() = 0;
};

#else // !__cplusplus : C style interface

typedef struct IInterfaceVtbl {
    _ELASTOS PInterface (CARAPICALLTYPE *Probe)(
            PInterface pThis,
            /* [in] */ _ELASTOS REIID riid);

    _ELASTOS UInt32 (CARAPICALLTYPE *AddRef)(
            PInterface pThis);

    _ELASTOS UInt32 (CARAPICALLTYPE *Release)(
            PInterface pThis);
}   IInterfaceVtbl;

interface IInterface {
    CONST_VTBL struct IInterfaceVtbl *v;
};

typedef struct IAspectVtbl
{
    _ELASTOS PInterface (CARAPICALLTYPE *Probe)(
            PInterface pThis,
            /* [in] */ _ELASTOS REIID riid);

    _ELASTOS UInt32 (CARAPICALLTYPE *AddRef)(
            PInterface pThis);

    _ELASTOS UInt32 (CARAPICALLTYPE *Release)(
            PInterface pThis);

    _ELASTOS ECode (CARAPICALLTYPE *AspectAggregate)(
            PASPECT pThis,
            /* [in] */ AggregateType type,
            /* [in] */ PInterface pObject);

    _ELASTOS ECode (CARAPICALLTYPE *AspectGetDomain)(
            PASPECT pThis,
            /* [out] */ PInterface *ppObject);

    _ELASTOS ECode (CARAPICALLTYPE *GetAspectID)(
            PASPECT pThis,
            /* [out] */ _ELASTOS ClassID *clsid);
}   IAspectVtbl;

interface IAspect
{
    CONST_VTBL struct IAspectVtbl *v;
};

#endif // __cplusplus

#ifdef __cplusplus
}   // extern "C"
#endif

#ifdef __cplusplus
// Helper types Small and Big - guarantee that sizeof(Small) < sizeof(Big)
//
template <class T, class U>
struct ConversionHelper
{
    typedef char Small;
    struct Big { char dummy[2]; };
    static Big   Test(...);
    static Small Test(U);
    static T & MakeT();
};
// class template Conversion
// Figures out the conversion relationships between two types
// Invocations (T and U are types):
// exists: returns (at compile time) true if there is an implicit conversion
// from T to U (example: Derived to Base)
// Caveat: might not work if T and U are in a private inheritance hierarchy.
//
template <class T, class U>
struct Conversion
{
    typedef ConversionHelper<T, U> H;
    enum {
        exists = sizeof(typename H::Small) == sizeof((H::Test(H::MakeT())))
    };
};

template <>
struct Conversion<void, CCarObject>
{
    enum {
        exists = FALSE
    };
};
#endif // __cplusplus

#endif // __CAR_ELAOBJ_H__
