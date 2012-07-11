//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __ELASTOS_CONTAINER_H__
#define __ELASTOS_CONTAINER_H__

//
// In this file, there are two simple container implementations, they are
// ObjectContainer and CallbackContextContainer, both of them inherited from
// base class SimpleContainer. They provide six methods: Current,
// MoveNext, Reset, Add, Remove and Dispose.
// In fact, Add, Remove and Dispose are right methods of container, but
// the Current, MoveNext and Reset are more like methods of enumerator,
// we take them together for terse reason.
//
// Using them in multi-threading program is not safe, the synchronizing
// mechanism should be decided by outer codes.
// We don't record reference count of interface in ObjectContainer, the
// counting rules should be decided by outer codes too. A more precise
// definition and implementation of ObjectContainer is suplied with CAR
// aspect class AObjectContainer in elastos.dll.
//

#include <eltypes.h>
#include <linknode.h>

/** @addtogroup BaseTypesRef
  *   @{
  */
class SimpleContainer
{
public:
    SimpleContainer();

    _ELASTOS ECode Current(DLinkNode **);
    _ELASTOS ECode MoveNext();
    _ELASTOS ECode Reset();
    _ELASTOS ECode Add(DLinkNode *);
    _ELASTOS ECode Remove(DLinkNode *);

public:
    DLinkNode  m_head;
    DLinkNode  *m_pCurrent;
};
/** @} */

INLINE SimpleContainer::SimpleContainer()
{
    m_head.Initialize();
    m_pCurrent = &m_head;
}

INLINE _ELASTOS ECode SimpleContainer::Current(DLinkNode **ppNode)
{
    assert(NULL != ppNode);

    if (NULL == m_pCurrent || &m_head == m_pCurrent) {
        return E_INVALID_OPERATION;
    }
    *ppNode = m_pCurrent;
    return NOERROR;
}

INLINE _ELASTOS ECode SimpleContainer::MoveNext()
{
    if (NULL == m_pCurrent) {
        return E_INVALID_OPERATION;
    }
    if (m_pCurrent == m_head.Prev()) {
        m_pCurrent = NULL;
        return S_FALSE;
    }
    m_pCurrent = m_pCurrent->Next();
    return NOERROR;
}

INLINE _ELASTOS ECode SimpleContainer::Reset()
{
    m_pCurrent = &m_head;
    return NOERROR;
}

INLINE _ELASTOS ECode SimpleContainer::Add(DLinkNode *pNode)
{
    m_head.InsertPrev(pNode);
    return NOERROR;
}

INLINE _ELASTOS ECode SimpleContainer::Remove(DLinkNode *pNode)
{
    if (m_pCurrent == pNode) {
        m_pCurrent = m_pCurrent->Prev();
    }
    pNode->Detach();
    return NOERROR;
}

/** @addtogroup BaseTypesRef
  *   @{
  */
struct ObjectNode : public DLinkNode
{
    ObjectNode(PInterface pObj) { m_pObject = pObj; }

    PInterface m_pObject;
};

class ObjectContainer : public SimpleContainer
{
public:
    _ELASTOS ECode Current(PInterface *ppObj);
    _ELASTOS ECode Add(PInterface pObj);
    _ELASTOS ECode Remove(PInterface pObj);
    _ELASTOS ECode Dispose();

    virtual ~ObjectContainer();
};
/** @} */

INLINE ObjectContainer::~ObjectContainer()
{
    this->Dispose();
}

INLINE _ELASTOS ECode ObjectContainer::Dispose()
{
    ObjectNode *pNode;

    pNode = (ObjectNode *)m_head.Next();
    while (&m_head != (DLinkNode *)pNode) {
        pNode->Detach();
        delete pNode;
        pNode = (ObjectNode *)m_head.Next();
    }
    m_pCurrent = NULL;
    return NOERROR;
}

INLINE _ELASTOS ECode ObjectContainer::Current(PInterface *ppObj)
{
    _ELASTOS ECode ec;
    ObjectNode *pNode;
    unsigned int p = (unsigned int)&pNode;

    ec = SimpleContainer::Current((DLinkNode **)p);
    if (NOERROR == ec) *ppObj = pNode->m_pObject;
    return ec;
}

INLINE _ELASTOS ECode ObjectContainer::Add(PInterface pObj)
{
    ObjectNode *pNode;

    pNode = new ObjectNode(pObj);
    if (NULL == pNode) return E_OUT_OF_MEMORY;

    return SimpleContainer::Add(pNode);
}

INLINE _ELASTOS ECode ObjectContainer::Remove(PInterface pObj)
{
    ObjectNode *pNode;

    ForEachDLinkNode(ObjectNode *, pNode, &m_head) {
        if (pNode->m_pObject == pObj) {
            SimpleContainer::Remove(pNode);
            delete pNode;
            return NOERROR;
        }
    }
    return S_FALSE;
}

ELAPI _Impl_CallbackSink_GetCallbackContext(
            PInterface *ppCallbackContext);

typedef _ELASTOS Int32 CallbackEventId;

ELAPI _Impl_CallbackSink_CancelCallbackEvents(
            PInterface pCallbackContext,
            PInterface pSender,
            CallbackEventId id,
            _ELASTOS PVoid pHandlerThis,
            _ELASTOS PVoid pHandlerFunc);

//
//  struct DelegateNode
//
struct DelegateNode : public DLinkNode
{
    DelegateNode(PInterface pCallbackContext, _ELASTOS EventHandler delegate)
        : m_pCallbackContext(pCallbackContext), m_delegate(delegate)
    {
        assert(pCallbackContext);
    }

    _ELASTOS ECode CancelCallbackEvents(PInterface pSender, CallbackEventId id)
    {
        return _Impl_CallbackSink_CancelCallbackEvents(
                    m_pCallbackContext, pSender, id,
                    m_delegate.GetThisPtr(),
                    m_delegate.GetFuncPtr());
    }

    IInterface     *m_pCallbackContext;
    _ELASTOS EventHandler  m_delegate;
};

class DelegateContainer : public SimpleContainer
{
public:
    _ELASTOS ECode Current(
            DelegateNode **ppNode);

    _ELASTOS ECode Add(PInterface pCallbackContext, const _ELASTOS EventHandler & delegate);

    _ELASTOS ECode Remove(
            _ELASTOS EventHandler & delegate, PInterface pSender, CallbackEventId id);

    _ELASTOS ECode Dispose(
            PInterface pSender, CallbackEventId id);

    ~DelegateContainer();
};

INLINE DelegateContainer::~DelegateContainer()
{
    DelegateNode *pNode;

    while (!m_head.IsEmpty()) {
        pNode = (DelegateNode *)m_head.First();
        pNode->Detach();
        delete pNode;
    }
    m_pCurrent = NULL;
}

INLINE _ELASTOS ECode DelegateContainer::Dispose(PInterface pSender,
    CallbackEventId id)
{
    DelegateNode *pNode;

    while (!m_head.IsEmpty()) {
        pNode = (DelegateNode *)m_head.First();
        pNode->Detach();
        pNode->CancelCallbackEvents(pSender, id);
        delete pNode;
    }
    m_pCurrent = NULL;
    return NOERROR;
}

INLINE _ELASTOS ECode DelegateContainer::Current(
    DelegateNode **ppNode)
{
    return SimpleContainer::Current((DLinkNode **)ppNode);
}

INLINE _ELASTOS ECode DelegateContainer::Add(
    PInterface pCallbackContext,
    const _ELASTOS EventHandler & delegate)
{
    DelegateNode *pNode;

    assert(pCallbackContext);

    pNode = new DelegateNode(pCallbackContext, delegate);
    if (NULL == pNode) {
        return E_OUT_OF_MEMORY;
    }

    return SimpleContainer::Add(pNode);
}

INLINE _ELASTOS ECode DelegateContainer::Remove(
    _ELASTOS EventHandler & delegate, PInterface pSender, CallbackEventId id)
{
    DelegateNode *pNode;
    _ELASTOS ECode ec = NOERROR;

    ForEachDLinkNode(DelegateNode *, pNode, &m_head) {
        if (pNode->m_delegate == delegate) {
            SimpleContainer::Remove(pNode);
            ec = pNode->CancelCallbackEvents(pSender, id);
            delete pNode;
            break;
        }
    }

    return ec;
}

//
//  struct CallbackContextNode
//
struct CallbackContextNode : public DLinkNode
{
    CallbackContextNode(PInterface pCallbackContext, _ELASTOS Boolean bOccured)
        : m_pCallbackContext(pCallbackContext), m_bEventOccured(bOccured),
        m_bEmpty(TRUE)
    {
        assert(m_pCallbackContext);

        m_pCallbackContext->AddRef();
    }

    ~CallbackContextNode()
    {
        if (m_pCallbackContext) m_pCallbackContext->Release();
    }

    _ELASTOS ECode MoveNext();

    _ELASTOS ECode Reset();

    _ELASTOS ECode Current(
            _ELASTOS EventHandler **ppDelegate);

    _ELASTOS ECode Add(const _ELASTOS EventHandler & delegate);

    _ELASTOS ECode Remove(
            _ELASTOS EventHandler & delegate, PInterface pSender, CallbackEventId id);

    _ELASTOS ECode Dispose(
            PInterface pSender, CallbackEventId id);

    IInterface     *m_pCallbackContext;
    DelegateContainer m_delegateContainer;
    _ELASTOS Boolean m_bEventOccured;
    _ELASTOS Boolean m_bEmpty;
};

INLINE _ELASTOS ECode CallbackContextNode::MoveNext()
{
    return m_delegateContainer.MoveNext();
}

INLINE _ELASTOS ECode CallbackContextNode::Reset()
{
    return m_delegateContainer.Reset();
}

INLINE _ELASTOS ECode CallbackContextNode::Dispose(PInterface pSender,
    CallbackEventId id)
{
    _ELASTOS ECode ec = m_delegateContainer.Dispose(pSender, id);
    if (FAILED(ec)) return ec;
    DLinkNode::Detach();
    return NOERROR;
}

INLINE _ELASTOS ECode CallbackContextNode::Current(
    _ELASTOS EventHandler **ppDelegate)
{
    _ELASTOS ECode ec;
    DelegateNode *pNode;

    ec = m_delegateContainer.Current(&pNode);
    if (NOERROR == ec) {
        *ppDelegate = &pNode->m_delegate;
    }
    return ec;
}

INLINE _ELASTOS ECode CallbackContextNode::Add(const _ELASTOS EventHandler & delegate)
{
    m_bEmpty = FALSE;
    return m_delegateContainer.Add(m_pCallbackContext, delegate);
}

INLINE _ELASTOS ECode CallbackContextNode::Remove(
    _ELASTOS EventHandler & delegate, PInterface pSender, CallbackEventId id)
{
    _ELASTOS ECode ec = m_delegateContainer.Remove(delegate, pSender, id);
    if (FAILED(ec)) return ec;

    if (m_delegateContainer.m_head.IsEmpty()) {
        m_bEmpty = TRUE;
        DLinkNode::Detach();
    }
    return NOERROR;
}

//
//  class CallbackContextContainer
//
class CallbackContextContainer : public SimpleContainer
{
public:
    _ELASTOS ECode Find(
            PInterface pCallbackContext, CallbackContextNode **ppNode);

    _ELASTOS ECode Current(
            CallbackContextNode **ppNode);

    _ELASTOS ECode Add(PInterface pCallbackContext, const _ELASTOS EventHandler & delegate);

    _ELASTOS ECode Remove(
            PInterface pCallbackContext, _ELASTOS EventHandler & delegate,
            PInterface pSender, CallbackEventId id);

    _ELASTOS ECode Dispose(
            PInterface pCallbackContext, PInterface pSender, CallbackEventId id);

    CallbackContextContainer():m_bEventOccured(FALSE) {}

    ~CallbackContextContainer();

public:
    _ELASTOS Boolean  m_bEventOccured;
};

INLINE CallbackContextContainer::~CallbackContextContainer()
{
    DLinkNode *pNode;

    SimpleContainer::Reset();
    assert(m_head.IsEmpty() && "You should call CFoo::RemoveAllCallbacks first.");

    while (SimpleContainer::MoveNext() == NOERROR) {
        if (SimpleContainer::Current(&pNode) != NOERROR) {
            break;
        }
        SimpleContainer::Remove(pNode);
        delete ((CallbackContextNode*)pNode);
    }
    assert(m_head.IsEmpty());
    m_pCurrent = NULL;
}

INLINE _ELASTOS ECode CallbackContextContainer::Find(
    PInterface pCallbackContext, CallbackContextNode **ppNode)
{
    CallbackContextNode *pCurrNode;

    ForEachDLinkNode(CallbackContextNode *, pCurrNode, &m_head) {
        if (pCurrNode->m_pCallbackContext == pCallbackContext) {
            *ppNode = pCurrNode;
            return NOERROR;
        }
    }
    *ppNode = NULL;
    return NOERROR;
}

INLINE _ELASTOS ECode CallbackContextContainer::Dispose(
    PInterface pCallbackContext, PInterface pSender, CallbackEventId id)
{
    CallbackContextNode *pNode;

    pNode = (CallbackContextNode *)m_head.Next();
    while (&m_head != (DLinkNode *)pNode) {
        if (pNode->m_pCallbackContext == pCallbackContext) {
            pNode->Dispose(pSender, id);
            delete pNode;
            break;
        }
        pNode = (CallbackContextNode *)((DLinkNode*)pNode)->Next();
    }
    return NOERROR;
}

INLINE _ELASTOS ECode CallbackContextContainer::Current(
    CallbackContextNode **ppNode)
{
    return SimpleContainer::Current((DLinkNode **)ppNode);
}

INLINE _ELASTOS ECode CallbackContextContainer::Add(
    PInterface pCallbackContext,
    const _ELASTOS EventHandler & delegate)
{
    _ELASTOS Boolean bFound = FALSE;
    CallbackContextNode *pNode;
    _ELASTOS ECode ec;

    if (NULL == pCallbackContext) {
        ec = _Impl_CallbackSink_GetCallbackContext(&pCallbackContext);
        if (FAILED(ec)) return ec;
    }
    else {
        pCallbackContext->AddRef();
    }

    ForEachDLinkNode(CallbackContextNode *, pNode, &m_head) {
        if (pNode->m_pCallbackContext == pCallbackContext) {
            bFound = TRUE;
            break;
        }
    }

    if (!bFound) {
        pNode = new CallbackContextNode(pCallbackContext, FALSE);
        if (NULL == pNode) {
            pCallbackContext->Release();
            return E_OUT_OF_MEMORY;
        }

        ec = SimpleContainer::Add(pNode);
        if (FAILED(ec)) {
            pCallbackContext->Release();
            return ec;
        }
    }

    ec = pNode->Add(delegate);
    pCallbackContext->Release();

    return ec;
}

INLINE _ELASTOS ECode CallbackContextContainer::Remove(
    PInterface pCallbackContext, _ELASTOS EventHandler & delegate,
    PInterface pSender, CallbackEventId id)
{
    assert(pCallbackContext);

    CallbackContextNode *pNode;

    ForEachDLinkNode(CallbackContextNode *, pNode, &m_head) {
        if (pNode->m_pCallbackContext == pCallbackContext) {
            _ELASTOS ECode ec = pNode->Remove(delegate, pSender, id);
            if (FAILED(ec)) return ec;
            if (pNode->m_bEmpty) delete pNode;
            return NOERROR;
        }
    }

    return NOERROR;
}

#endif // __ELASTOS_CONTAINER_H__
