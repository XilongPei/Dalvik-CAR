#ifndef __CAR_CJAVACALLBACKINVOCATION_CPP__
#define __CAR_CJAVACALLBACKINVOCATION_CPP__

extern "C" {
#include "jni.h"
}

#include "CJavaCallbackInvocation.h"
#include <unistd.h>
#include <stdlib.h>

class _CSandwichCJavaCallbackInvocation : public CJavaCallbackInvocation
{
public:
    _CSandwichCJavaCallbackInvocation()
    {
    }
    virtual ~_CSandwichCJavaCallbackInvocation()
    {
    }
    void *operator new(size_t size) { return ::operator new(size); }
    void *operator new(size_t size, void* _location) { return _location; }
    void operator delete(void* _location) { ::operator delete(_location); }


public:
    CARAPI Invoke(PVoid, PVoid, ICallbackArgumentList *);


    ECode SandwichEnter(
        Boolean *pbHasTaken,
        pthread_mutex_t **ppOrigLock,
        PInterface *ppCurtCallbackContext);

    ECode SandwichLeave(
        Boolean bHasTaken,
        pthread_mutex_t *pOrigLock,
        PInterface pCurtCallbackContext);

};


_CJavaCallbackInvocation::~_CJavaCallbackInvocation()
{
    this->_Uninitialize_();

    if (_m_dwInitComponent & _InitComponentFlags_InitSyncLock) {
        pthread_mutex_destroy(&_m_syncLock);
        _m_dwInitComponent &= ~_InitComponentFlags_InitSyncLock;
    }

    if (NULL != _m_pAspectLock) {
        pthread_mutex_destroy(_m_pAspectLock);
        delete _m_pAspectLock;
        _m_pAspectLock = NULL;
    }


    if (_m_dwInitComponent & _InitComponentFlags_IncrementDllLockCount) {
    	// implement it or delete it?
        //DecrementDllLockCount();
        _m_dwInitComponent &= ~_InitComponentFlags_IncrementDllLockCount;
    }
}

UInt32 _CJavaCallbackInvocation::AddRef()
{
        Int32 nRef = atomic_inc(&m_cRef);
  
    return (UInt32)nRef;
  }

UInt32 _CJavaCallbackInvocation::Release()
{
        Int32 nRef = atomic_dec(&m_cRef);
  
    if (0 == nRef) {
    
        pthread_mutex_t *pOrigLock = NULL;
        pOrigLock = (pthread_mutex_t *)pthread_getspecific(TL_SEQUENCED_SLOT);
        if (NULL != pOrigLock) {
            pthread_setspecific(TL_SEQUENCED_SLOT, NULL);
            pthread_mutex_unlock((pthread_mutex_t*)pOrigLock);
        }
  
  #ifndef _NO_CJAVACALLBACKINVOCATION_CLASSOBJECT_
        ((CJavaCallbackInvocation*)this)->~CJavaCallbackInvocation();
        free(this);
#else
        delete this;
#endif // _NO_CJAVACALLBACKINVOCATION_CLASSOBJECT_
  
  
        if (NULL != pOrigLock) pthread_mutex_lock((pthread_mutex_t*)pOrigLock);
        pthread_setspecific(TL_SEQUENCED_SLOT, (TLValue)pOrigLock);
      }
      assert(nRef >= 0);
    return nRef;
  }

ECode _CJavaCallbackInvocation::Aggregate(
    AggregateType type, PInterface pObj)
{
    ECode ec = NOERROR;
    IAspect* pAspect = NULL;
    Boolean bHasTaken = TRUE;
    pthread_mutex_t *_pOrigLock_=NULL;
    unsigned int p = (unsigned int)&_pOrigLock_;
    ec = FriendEnter((PVoid*)p);

    if (ec == S_WITHOUT_LOCK) bHasTaken = FALSE;

    switch (type) {
    case AggrType_AspectAttach:
        _AspectLock();
        ec = _AspectAttach((IAspect*)pObj);
        _AspectUnlock();
        goto Exit;
    case AggrType_AspectDetach:
        ec = _AspectDetach((IAspect*)pObj);
        goto Exit;
    case AggrType_AspectDetached:
        pAspect = (IAspect*)pObj->Probe(EIID_IAspect);
        assert(pAspect);
        if (!_m_pAspects.IsEmpty()){
            ObjectNode *pNode = (ObjectNode*)_m_pAspects.Next();
            while (pNode != &_m_pAspects) {
                if (pNode->m_pObject == (IInterface*)pAspect) {
                    pAspect->AspectAggregate(AggrType_AspectDetached, pObj);
                    pNode->Detach();
                    delete pNode;
                    break;
                }
                else {
                    pNode = (ObjectNode*)pNode->Next();
                }
            }
        }
        goto Exit;
    case AggrType_FriendEnter:
        ec = FriendEnter((PVoid *)pObj);
        goto Exit;
    case AggrType_FriendLeave:
        ec = FriendLeave((PVoid)pObj);
        goto Exit;
    case AggrType_EnteredContext:
        ec = OnEnteredContext(pObj);
        goto Exit;
    case AggrType_LeftContext:
        ec = OnLeftContext(pObj);
        goto Exit;
    case AggrType_Unaggregate:
        _AspectLock();

        if (_m_pAspects.IsEmpty()) {
            _AspectUnlock();
            ec = E_CLASS_NO_AGGREGATION;
            goto Exit;
        }
        else {
            ClassID clsid;
            ObjectNode *pNode = (ObjectNode*)_m_pAspects.Next();
            while (pNode != &_m_pAspects) {
                pAspect = (IAspect*)pNode->m_pObject;
                ec = pAspect->GetAspectID(&clsid);
                if (FAILED(ec)) goto Exit;
                if (clsid.clsid == (*(ClassID*)pObj).clsid) {
                    _AspectDetach(pAspect);
                    pAspect->AspectAggregate(AggrType_AspectDetach, (IObject*)this);
                    pNode->Detach();
                    delete pNode;
                    break;
                }
                else {
                    pNode = (ObjectNode*)pNode->Next();
                }
            }
            _AspectUnlock();
            goto Exit;
        }
    default:
        ec = E_INVALID_ARGUMENT;
        break;
    }
Exit:
    if (bHasTaken) FriendLeave(_pOrigLock_);
    return ec;
}

ECode _CJavaCallbackInvocation::GetDomain(
    IInterface** ppObj)
{
    if (ppObj == NULL) return E_INVALID_ARGUMENT;

    if (_m_pDomain == NULL) {
        *ppObj = NULL;
    }
    else {
        _m_pDomain->AddRef();
        *ppObj = _m_pDomain;
    }

    return NOERROR;
}

ECode _CJavaCallbackInvocation::GetClassID(
    _ELASTOS ClassID *pCLSID)
{
    if (NULL == pCLSID) return E_INVALID_ARGUMENT;

    *pCLSID = ECLSID_CJavaCallbackInvocation;
    return NOERROR;
}

PInterface _CJavaCallbackInvocation::Probe(
    _ELASTOS REIID riid)
{

    if (EIID_IInterface == riid) {
        return (_IInterface *)this;
    }
    if (EIID_MUTEX_INFO == riid) {
        return (IInterface *)_m_pAspectLock;
    }
    if (EIID_SUPER_OBJECT == riid) {
        return NULL;
    }
    if (EIID_ICallbackInvocation == riid) {
        return (ICallbackInvocation *)this;
    }
    if (EIID_IObject == riid) {
        return (IObject *)this;
    }
    if (EIID_GENERIC_INFO == riid) {
        return NULL;

    }
    {
        _AspectLock();
        if (!_m_pAspects.IsEmpty()) {
            PInterface pObject = NULL;
            _Impl_SetHelperInfoFlag(HELPER_CHILD_CALL_PARENT, TRUE);
            ObjectNode *pNode = (ObjectNode*)_m_pAspects.Next();
            while (pNode != &_m_pAspects) {
                pObject = pNode->m_pObject->Probe(riid);
                if (NULL != pObject) break;
                else {
                    pNode = (ObjectNode*)pNode->Next();
                }
            }
            _Impl_SetHelperInfoFlag(HELPER_CHILD_CALL_PARENT, FALSE);
            _AspectUnlock();
            if (NULL != pObject) return pObject;
        }
        else {
            _AspectUnlock();
            return NULL;
        }
    }

    return NULL;
}

ECode _CJavaCallbackInvocation::GetInterfaceID(
    /* [in] */ IInterface *pObject,
    /* [out] */ InterfaceID *pIID)
{
    if (pIID == NULL) return E_INVALID_ARGUMENT;

    if (pObject == (IInterface*)(ICallbackInvocation*)this) {
        *pIID = EIID_ICallbackInvocation;
    }
    else if (pObject == (IInterface*)(IObject*)this) {
        *pIID = EIID_IObject;
    }
    else {
        return E_INVALID_ARGUMENT;
    }
    return NOERROR;
}

ECode _CJavaCallbackInvocation::_Initialize_()
{
    ECode ec = NOERROR;

    if (FAILED(_m_ecCtor)) return _m_ecCtor;

	// implement it or delete it?
    //IncrementDllLockCount();
    _m_dwInitComponent |= _InitComponentFlags_IncrementDllLockCount;

    _m_pAspectLock = new pthread_mutex_t;
    if(NULL == _m_pAspectLock) return E_OUT_OF_MEMORY;

    {
        pthread_mutexattr_t recursiveAttr;
        pthread_mutexattr_init(&recursiveAttr);
        pthread_mutexattr_settype(&recursiveAttr, PTHREAD_MUTEX_RECURSIVE);
        ec = pthread_mutex_init(_m_pAspectLock, &recursiveAttr);
        pthread_mutexattr_destroy(&recursiveAttr);
        if (ec != 0) {
            delete _m_pAspectLock;
            _m_pAspectLock = NULL;
            return E_FAIL;
        }
    }

    {
        pthread_mutexattr_t recursiveAttr;
        pthread_mutexattr_init(&recursiveAttr);
        pthread_mutexattr_settype(&recursiveAttr, PTHREAD_MUTEX_RECURSIVE);
        ec = pthread_mutex_init(&_m_syncLock, &recursiveAttr);
        pthread_mutexattr_destroy(&recursiveAttr);
        if (ec != 0) {
            return E_FAIL;
        }
    }
    _m_dwInitComponent |= _InitComponentFlags_InitSyncLock;


    return ec;
}

void _CJavaCallbackInvocation::_Uninitialize_()
{
    _AspectLock();
    ClassID clsid;
    ECode ec;

    if (!_m_pAspects.IsEmpty()){
        ObjectNode *pNode = (ObjectNode*)_m_pAspects.Next();
        while (pNode != &_m_pAspects) {
            ec = ((IAspect*)pNode->m_pObject)->GetAspectID(&clsid);
            pNode = (ObjectNode*)pNode->Next();
            if (FAILED(ec)) continue;
			unsigned int p = (unsigned int)&clsid;
            Aggregate(AggrType_Unaggregate, (PInterface)p);
        }
    }
    _AspectUnlock();
}

ECode _CJavaCallbackInvocation::_AspectAttach(IAspect* pAspect)
{
    ECode ec = NOERROR;


    _Impl_EnterProtectedZone();
     ec = this->OnAspectAttaching((PInterface)pAspect);
    _Impl_LeaveProtectedZone();
    if (FAILED(ec)) return ec;

    Boolean found = false;
    ObjectNode *pNode = (ObjectNode*)_m_pAspects.Next();
    IAspect *pAspect1;
    ClassID clsid1, clsid2;
    while (pNode != &_m_pAspects) {
        pAspect1 = (IAspect*)(pNode->m_pObject);
        pAspect1->GetAspectID(&clsid1);
        pAspect->GetAspectID(&clsid2);
        if (clsid1.clsid == clsid2.clsid) {
            found = true;
            break;
        }
        pNode = (ObjectNode*)pNode->Next();
    }

    if (!found) {
        ObjectNode *pNode = new ObjectNode(pAspect);
        _m_pAspects.InsertNext(pNode);
    }
    else {
        return E_DUPLICATE_ASPECT;
    }

    return ec;
}

ECode _CJavaCallbackInvocation::_AspectDetach(IAspect* pAspect)
{
    ECode ec = NOERROR;


    _Impl_EnterProtectedZone();
    this->OnAspectDetaching((PInterface)pAspect);
    _Impl_LeaveProtectedZone();


    return ec;
}

inline ECode _CJavaCallbackInvocation::_AspectLock()
{
    if(NULL != _m_pAspectLock)
        pthread_mutex_lock(_m_pAspectLock);
    return NOERROR;
}

inline ECode _CJavaCallbackInvocation::_AspectUnlock()
{
    if(NULL != _m_pAspectLock)
        pthread_mutex_unlock(_m_pAspectLock);
    return NOERROR;
}


#ifndef _NO_CJAVACALLBACKINVOCATION_CLASSOBJECT_

CARAPI _CJavaCallbackInvocationCreateObject(
    /* [in] */ PVoid pParam0,
    /* [in] */ PVoid pParam1,
    IInterface **ppObj)
{
    ECode ec = NOERROR;
    _CSandwichCJavaCallbackInvocation *pObj = NULL;

    void* pLocation = calloc(sizeof(_CSandwichCJavaCallbackInvocation), 1);
    if (!pLocation) {
        ec = E_OUT_OF_MEMORY;
        goto Exit;
    }
    pObj = (_CSandwichCJavaCallbackInvocation *)new(pLocation) _CSandwichCJavaCallbackInvocation;

    atomic_inc(&(((_CSandwichCJavaCallbackInvocation *)pObj)->m_cRef));
    ec = pObj->_Initialize_();
    if (FAILED(ec)) goto Exit;
    ec = pObj->constructor(pParam0,pParam1);
    if (FAILED(ec)) goto Exit;
    *ppObj = (_IInterface*)pObj;
Exit:
    if (FAILED(ec) && pObj) {
        ((_CSandwichCJavaCallbackInvocation*)pObj)->~_CSandwichCJavaCallbackInvocation();
        free(pObj);
    }
    return ec;
}

ECode _CJavaCallbackInvocation::NewByFriend(
    /* [in] */ PVoid pParam0,
    /* [in] */ PVoid pParam1, CJavaCallbackInvocation **ppParam2)
{
    return _CJavaCallbackInvocationCreateObject(
            pParam0,
            pParam1,
            (IInterface**)ppParam2);
}


#endif // _NO_CJAVACALLBACKINVOCATION_CLASSOBJECT_


ECode _CSandwichCJavaCallbackInvocation::SandwichEnter(
    Boolean *pbHasTaken,
    pthread_mutex_t **ppOrigLock,
    PInterface *ppCurtCallbackContext)
{
    ECode ec = NOERROR;
    ec = FriendEnter((PVoid*)ppOrigLock);
    if (ec == S_WITHOUT_LOCK) *pbHasTaken = FALSE;


    return ec;
}

ECode _CSandwichCJavaCallbackInvocation::SandwichLeave(
    Boolean bHasTaken,
    pthread_mutex_t *pOrigLock,
    PInterface pCurtCallbackContext)
{
    if (bHasTaken) FriendLeave(pOrigLock);
    return NOERROR;
}


ECode _CSandwichCJavaCallbackInvocation::Invoke(
    PVoid pParam0,
    PVoid pParam1,
    ICallbackArgumentList * pParam2)
{
    ECode ec = NOERROR;
    Boolean bHasTaken = TRUE;
    pthread_mutex_t *_pOrigLock_= NULL;
    PInterface _pCurtCallbackContext_ = NULL;

    ec = SandwichEnter(&bHasTaken, &_pOrigLock_, &_pCurtCallbackContext_);
    if (FAILED(ec)) return ec;

    ec = CJavaCallbackInvocation::Invoke(pParam0, pParam1, pParam2);

    SandwichLeave(bHasTaken, _pOrigLock_, _pCurtCallbackContext_);

    return ec;
}
/*
* Class is "freethreaded"
*/

ECode _CJavaCallbackInvocation::FriendEnter(PVoid * ppHandle)
{
    ECode ec = NOERROR;
    if (NULL == ppHandle) return E_INVALID_ARGUMENT;
    *ppHandle = (PVoid *)pthread_getspecific(TL_SEQUENCED_SLOT);
    if (NULL != *ppHandle) {
        pthread_setspecific(TL_SEQUENCED_SLOT, NULL);
        pthread_mutex_unlock((pthread_mutex_t*)*ppHandle);
    }
    return ec;
}

ECode _CJavaCallbackInvocation::FriendLeave(PVoid pHandle)
{

    if (NULL != pHandle) pthread_mutex_lock((pthread_mutex_t*)pHandle);
    pthread_setspecific(TL_SEQUENCED_SLOT, (TLValue)pHandle);
    return NOERROR;
}

#endif // __CAR_CJAVACALLBACKINVOCATION_CPP__
