
#ifndef __CAR_CJAVACALLBACKINVOCATION_H__
#define __CAR_CJAVACALLBACKINVOCATION_H__

#include "JavaCallbackInvocation_server.h"
#include <container.h>
#include <pthread.h>
//#include <sys/atomics.h>

CARAPI _CJavaCallbackInvocationCreateObject(
        /* [in] */ PVoid pParam0,
        /* [in] */ PVoid pParam1,
        IInterface **);

class CJavaCallbackInvocation;

class _CJavaCallbackInvocation :
    public CCarObject,
    public ICallbackInvocation,
    public IObject
{

public:
    CARAPI_(UInt32) AddRef();
    CARAPI_(UInt32) Release();
    CARAPI_(PInterface) Probe(REIID);
    CARAPI GetInterfaceID(IInterface *object, InterfaceID *pIID);
    CARAPI Aggregate(AggregateType type, PInterface pObj);
    CARAPI GetDomain(IInterface** ppObj);
    CARAPI GetClassID(ClassID* pCLSID);

private:
    CARAPI _Initialize_();
    CARAPI_(void) _Uninitialize_();

public:
    _CJavaCallbackInvocation() :
        _m_pDomain(NULL),
        _m_ecCtor(NOERROR),
        _m_pChild(NULL),
        _m_dwInitComponent(0),
        _m_pAspectLock(NULL),
        m_cRef(0){
        _m_pAspects.Initialize();

        _m_pDomain = (PInterface)pthread_getspecific(TL_DOMAIN_SLOT);
    }
    virtual ~_CJavaCallbackInvocation();
protected:
    virtual _CJavaCallbackInvocation* GetDerivedClassPtr()
    { return this; }
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS PVoid pParam0,/* [in] */ _ELASTOS PVoid pParam1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICJavaCallbackInvocationClassObject* pClassObject;
        unsigned int p = (unsigned int)&pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CJavaCallbackInvocation, __pContext, 
                EIID_ICJavaCallbackInvocationClassObject, (IInterface**)p);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithEnvSelf(pParam0, pParam1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }
    static ECode NewByFriend(
    /* [in] */ PVoid pParam0,
    /* [in] */ PVoid pParam1, CJavaCallbackInvocation **ppParam2);

    CARAPI FriendEnter(PVoid *ppHandle);
    CARAPI FriendLeave(PVoid pHandle);

    ECode _GetCallingProperty(UInt32 *pUAttrib);
public:
    PInterface _m_pDomain;
    ECode _m_ecCtor;
protected:
    virtual CARAPI OnAspectAttaching(PInterface pAspect) { return NOERROR; }
    virtual CARAPI OnAspectDetaching(PInterface pAspect) { return NOERROR; }
    virtual CARAPI OnEnteredContext(PInterface pObject) { return NOERROR; }
    virtual CARAPI OnLeftContext(PInterface pObject) { return NOERROR; }


    CARAPI _AspectAttach(IAspect* pAspect);
    CARAPI _AspectDetach(IAspect* pAspect);

    DLinkNode _m_pAspects;
    IObject* _m_pChild;
    UInt32  _m_dwInitComponent;
    pthread_mutex_t* _m_pAspectLock;

    ECode _AspectLock();
    ECode _AspectUnlock();

    friend CARAPI _CJavaCallbackInvocationCreateObject(
            /* [in] */ PVoid pParam0,
            /* [in] */ PVoid pParam1,
            IInterface **);

    pthread_mutex_t    _m_syncLock;
    void SelfLock()
    {
        pthread_mutex_lock(&_m_syncLock);
    }

    void SelfUnlock()
    {
        pthread_mutex_unlock(&_m_syncLock);
    }

#ifndef _NO_CJAVACALLBACKINVOCATION_CLASSOBJECT_
    void operator delete(void* _location) { ::operator delete(_location); }
#endif // _NO_CJAVACALLBACKINVOCATION_CLASSOBJECT_
    Int32 m_cRef;

private:

    void *operator new(size_t size) throw() { assert(0&&"You should call CFoo::NewByFriend(&pFoo);"); return NULL; }
    void *operator new(size_t size, void* _location) throw() { assert(0&&"You should call CFoo::NewByFriend(&pFoo);"); return NULL; }

    _CJavaCallbackInvocation(const _CJavaCallbackInvocation&) {}
    _CJavaCallbackInvocation& operator=(const _CJavaCallbackInvocation&) { return *this; }
#ifdef _DEBUG
#define CJavaCallbackInvocation_CallbackKeyword_Checking
#endif
};

#endif // __CAR_CJAVACALLBACKINVOCATION_H__
