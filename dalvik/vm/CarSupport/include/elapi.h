/** @addtogroup SystemRef
  *   @{
  *
  * Elastos API is Elastos's core set of application programming interfaces (APIs).
  */

//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __ELAPI_H__
#define __ELAPI_H__

#include <elastos.h>

// EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CAppletHosting;

#ifdef _UNDEFDLLEXP
#include <elasys_server.h>
#else
#include <elasys.h>
#endif

#ifdef _openkode
#include <stdint.h>
#else
#include <elconsole.h>
#endif

ELAPI _CSystem_RegisterServiceManager(
    PInterface pService);

ELAPI _CSystem_GetServiceManager(
    PInterface *ppService);

/**
 * @see CSystem::RegisterRunningObject()
 */
ELAPI _CSystem_RegisterRunningObject(
            _ELASTOS String name,
            PInterface pService);

/**
 * @see CSystem::FindRunningObject()
 */
ELAPI _CSystem_FindRunningObject(
            _ELASTOS String name,
            PInterface *pService);

/**
 * @see CSystem::WaitForRunningObject()
 */
ELAPI _CSystem_WaitForRunningObject(
            _ELASTOS String name,
            _ELASTOS Int32 timeout,
            WaitResult *pResult);

/**
 * @see CSystem::UnregisterRunningObject()
 */
ELAPI _CSystem_UnregisterRunningObject(
            _ELASTOS String name);

/**
 * @see CSystem::GetMachineTime()
 */
ELAPI _CSystem_GetMachineTime(
            _ELASTOS SystemTime *pSystemTime);

/**
 * @see CSystem::SetMachineTime()
 */
ELAPI _CSystem_SetMachineTime(
            _ELASTOS SystemTime systemTime);

/**
 * @see CSystem::GetElapsedTime()
 */
ELAPI_(_ELASTOS Microsecond32) _CSystem_GetElapsedTime();

/**
 * @see CSystem::GetIdleTime()
 */
ELAPI_(_ELASTOS Microsecond32) _CSystem_GetIdleTime();

/**
 * @see CSystem::GetVersion()
 */
ELAPI_(_ELASTOS Int32) _CSystem_GetVersion();

/**
 * @see CSystem::GetGlobalMemorySizes()
 */
ELAPI _CSystem_GetGlobalMemorySizes(
            _ELASTOS Int32 *pTotalPhysicalMemorySize,
            _ELASTOS Int32 *pAvailablePhysicalMemorySize);

/**
 * @see CSystem::DebugPrint()
 */
ELAPI _CSystem_DebugPrint(
            _ELASTOS String string);

/**
 * Not supported.
 */
ELAPI _CSystem_GetAllProcesses(
            IObjectEnumerator **ppProcesses);

/**
 * @see CSystem::Reboot()
 */
ELAPI _CSystem_Reboot();

/**
 * @see CSystem::CreateSystemEventHandle()
 */
ELAPI _CSystem_CreateSystemEventHandle(
        /* [in] */ _ELASTOS SystemEvents interestedEvents,
        /* [out] */ IEvent **ppEvent);

/**
 * @see CSystem::WaitForAnySystemEvent()
 */
ELAPI _CSystem_WaitForAnySystemEvent(
        /* [in] */ _ELASTOS SystemEvents interestedEvents);

/**
 * @see CSystem::QueryPerformanceCounter()
 */
ELAPI _CSystem_QueryPerformanceCounter(
        /* [out] */ _ELASTOS Int64 *pPerformanceCount);

/**
 * @see CSystem::QueryPerformanceFrequency()
 */
ELAPI _CSystem_QueryPerformanceFrequency(
        /* [out] */ _ELASTOS Int64 *pFrequency);

/**
 * @see CSystem::GetDiskCapacity()
 */
ELAPI _CSystem_GetDiskCapacity(
        /* [in] */ _ELASTOS String diskDrive,
        /* [out] */ _ELASTOS Int64* capacityInBytes,
        /* [out] */ _ELASTOS Int64* freeSpaceInBytes);

/**
 * Not supported.
 */
ELAPI _CProcess_New(
            _ELASTOS String name,
            _ELASTOS String args,
            IProcess **ppProcess);

/**
 * Not supported.
 */
ELAPI _CProcess_NewUnstarted(
            IProcess **ppProcess);

/**
 * @see CProcess::GetCurrent()
 */
ELAPI_(IProcess *) _CProcess_GetCurrent();

/**
 * @see CProcess::Terminate()
 */
ELAPI_(void) _CProcess_Terminate(
            ExitCode exitCode);

/**
 * @see CProcess::Exit()
 */
ELAPI_(void) _CProcess_Exit(
            ExitCode exitCode);

/**
 * @see CProcess::AtExit()
 */
ELAPI _CProcess_AtExit(
            PProcessExitRoutine pEntry,
            _ELASTOS PVoid pUserData);

/**
 * @see CProcess::FreeUnusedModule()
 */
ELAPI _CProcess_FreeUnusedModule(_ELASTOS String szDllName);

/**
 * @see CProcess::FreeUnusedModules()
 */
ELAPI_(void) _CProcess_FreeUnusedModules(_ELASTOS Boolean bImmediate);

/**
 * @see CProcess::FlushInstructionCache()
 */
ELAPI _CProcess_FlushInstructionCache(
        /* [in] */ _ELASTOS Address baseAddr,
        /* [in] */ _ELASTOS MemorySize size);

/**
 * @see CModule::Load()
 */
ELAPI _CModule_Load(
            _ELASTOS String name,
            _ELASTOS ModuleLoadFlags flags,
            IModule **ppModule);

/**
 * @see CModule::GetCurrent()
 */
ELAPI _CModule_GetCurrent(
            IModule **ppIModule);

/**
 * @see CVirtualMemory::Alloc()
 */
ELAPI _CVirtualMemory_Alloc(
            _ELASTOS Address baseAddr,
            _ELASTOS MemorySize size,
            _ELASTOS MemoryMapFlags flags,
            MemoryProtection protect,
            _ELASTOS Address *pBaseAddr);

/**
 * @see CVirtualMemory::Query()
 */
ELAPI _CVirtualMemory_Query(
            _ELASTOS Address vAddress,
            _ELASTOS Address *pBaseAddr,
            _ELASTOS MemorySize *pSize);

/**
 * @see CVirtualMemory::QueryPhysicalBlock()
 */
ELAPI _CVirtualMemory_QueryPhysicalBlock(
            _ELASTOS Address vAddress,
            _ELASTOS Address *pAddress,
            _ELASTOS MemorySize *pSize);

/**
 * @see CVirtualMemory::SetProtection()
 */
ELAPI _CVirtualMemory_SetProtection(
            _ELASTOS Address baseAddr,
            _ELASTOS MemorySize size,
            MemoryProtection protect);

/**
 * @see CVirtualMemory::CheckProtection()
 */
ELAPI _CVirtualMemory_CheckProtection(
            _ELASTOS Address address,
            MemoryProtection protect,
            _ELASTOS Boolean *pIsValid);

/**
 * @see CVirtualMemory::Commit()
 */
ELAPI _CVirtualMemory_Commit(
            _ELASTOS Address address);

/**
 * @see CVirtualMemory::Free()
 */
ELAPI _CVirtualMemory_Free(
            _ELASTOS Address baseAddr,
            _ELASTOS MemorySize size);

/**
 * @see CVirtualMemory::IoRemap()
 */
ELAPI _CVirtualMemory_IoRemap(
            _ELASTOS Address virtualAddr,
            _ELASTOS MemorySize size,
            _ELASTOS Address physicalAddr,
            _ELASTOS MemoryMapFlags flags,
            MemoryProtection protect,
            _ELASTOS Address *pVirtualAddr);

/**
 * @see CMutex::New()
 */
ELAPI _CMutex_New(
        /* [out] */ IMutex **ppMutex);

/**
 * @see CMutex::NewWithName()
 */
ELAPI _CMutex_NewWithName(
        /* [in] */ _ELASTOS String name,
        /* [out] */ IMutex **ppMutex,
        /* [out] */ _ELASTOS Boolean *pAlreadyExists);

/**
 * @see CCondition::New()
 */
ELAPI _CCondition_New(
        /* [out] */ ICondition **ppCondition);

/**
 * @see CCondition::NewWithName()
 */
ELAPI _CCondition_NewWithName(
        /* [in] */ _ELASTOS String name,
        /* [out] */ ICondition **ppCondition,
        /* [out] */ _ELASTOS Boolean *pAlreadyExists);

/**
 * @see CEvent::New()
 */
ELAPI _CEvent_New(
        /* [in] */ _ELASTOS Boolean manualReset,
        /* [in] */ _ELASTOS EventState initialState,
        /* [out] */ IEvent **ppEvent);

/**
 * @see CEvent::NewWithName()
 */
ELAPI _CEvent_NewWithName(
        /* [in] */ _ELASTOS String name,
        /* [in] */ _ELASTOS Boolean manualReset,
        /* [in] */ _ELASTOS EventState initialState,
        /* [out] */ IEvent **ppEvent,
        /* [out] */ _ELASTOS Boolean *pAlreadyExists);

#ifdef __cplusplus

/**
 * @see CEvent::WaitForAnyEvents()
 */
ELAPI _CEvent_WaitForAnyEvents(
        /* [in] */ const _ELASTOS BufferOf<IEvent *> * events,
        /* [out] */ WaitResult *pResult,
        /* [out] */ _ELASTOS Int32 *pIndex);

/**
 * @see CEvent::TryWaitForAnyEvents()
 */
ELAPI _CEvent_TryWaitForAnyEvents(
        /* [in] */ const _ELASTOS BufferOf<IEvent *> * events,
        /* [in] */ _ELASTOS Millisecond32 timeout,
        /* [out] */ WaitResult *pResult,
        /* [out] */ _ELASTOS Int32 *pIndex);

#else // !__cplusplus

ELAPI _CEvent_WaitForAnyEvents(
        /* [in] */ const _ELASTOS PCarQuintet events,
        /* [out] */ WaitResult *pResult,
        /* [out] */ _ELASTOS Int32 *pIndex,
        /* [out] */ _ELASTOS EventState *pState);

ELAPI _CEvent_TryWaitForAnyEvents(
        /* [in] */ const _ELASTOS PCarQuintet events,
        /* [in] */ _ELASTOS Millisecond32 timeout,
        /* [out] */ WaitResult *pResult,
        /* [out] */ _ELASTOS Int32 *pIndex,
        /* [out] */ _ELASTOS EventState *pState);

#endif

/**
 * @see CReaderWriterLock::New()
 */
ELAPI _CReaderWriterLock_New(
        /* [out] */ IReaderWriterLock **ppRWLock);

/**
 * @see CReaderWriterLock::NewWithName()
 */
ELAPI _CReaderWriterLock_NewWithName(
        /* [in] */ _ELASTOS String name,
        /* [out] */ IReaderWriterLock **ppRWLock,
        /* [out] */ _ELASTOS Boolean *pAlreadyExists);

/**
 * @see CSharedMemory::New()
 */
ELAPI _CSharedMemory_New(
        /* [in] */ _ELASTOS String name,
        /* [in] */ _ELASTOS MemorySize size,
        /* [in] */ _ELASTOS Boolean reserved,
        /* [out] */ ISharedMemory **ppSharedMemory,
        /* [out] */ _ELASTOS Boolean *pAlreadyExists);

/**
 * @see CActiveTimer::New()
 */
ELAPI _CActiveTimer_New(
    /* [in] */ _ELASTOS Millisecond32 interval,
    /* [in] */ _ELASTOS ECode (ELAPICALLTYPE *pEntry)(_ELASTOS PVoid, IActiveTimer *),
    /* [in] */ _ELASTOS PVoid pUserData,
    /* [out] */ IActiveTimer ** ppActiveTimer);

/**
 * @see CErrorReport::SetString()
 */
ELAPI _CErrorReport_SetString(
        /* [in] */ _ELASTOS String string);

/**
 * @see CErrorReport::SetUrl()
 */
ELAPI _CErrorReport_SetUrl(
        /* [in] */ _ELASTOS String url);

#ifdef _MSVC
#pragma warning( disable : 4190 )
#endif

/**
 * @see CErrorReport::GetString()
 */
ELAPI_(_ELASTOS String) _CErrorReport_GetString();

/**
 * @see CErrorReport::GetUrl()
 */
ELAPI_(_ELASTOS String) _CErrorReport_GetUrl();

/**
 * @see CProfile::GetString()
 */
ELAPI _CProfile_GetString(
        /* [in] */ _ELASTOS String appName,
        /* [in] */ _ELASTOS String keyName,
        /* [out] */ _ELASTOS StringBuf *pReturnedString);

/**
 * @see CProfile::GetInt32()
 */
ELAPI _CProfile_GetInt32(
        /* [in] */ _ELASTOS String appName,
        /* [in] */ _ELASTOS String keyName,
        /* [out] */ _ELASTOS Int32 * pValue);

/**
 * @see CPrivateProfile::GetString()
 */
ELAPI _CPrivateProfile_GetString(
        /* [in] */ _ELASTOS String fileName,
        /* [in] */ _ELASTOS String appName,
        /* [in] */ _ELASTOS String keyName,
        /* [out] */ _ELASTOS StringBuf *pReturnedString);

/**
 * @see CPrivateProfile::GetInt32()
 */
ELAPI _CPrivateProfile_GetInt32(
        /* [in] */ _ELASTOS String fileName,
        /* [in] */ _ELASTOS String appName,
        /* [in] */ _ELASTOS String keyName,
        /* [out] */ _ELASTOS Int32 * pValue);

/**
 * @see CPrivateProfile::SetString()
 */
ELAPI _CPrivateProfile_SetString(
        /* [in] */ _ELASTOS String fileName,
        /* [in] */ _ELASTOS String appName,
        /* [in] */ _ELASTOS String keyName,
        /* [in] */ _ELASTOS String value);

/**
 * Initializes a critical section object.
 *
 * @param[in] pCriticalSection Pointer to the critical section object.
 * @return If the function succeeds, the return value is ::NOERROR.
 * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
 * it indicats not enough space.
 */
ELAPI _CCriticalSection_Initialize(
        /* [in] */ _ELASTOS CriticalSection *pCriticalSection);

/**
 * Waits for ownership of a critical section object.
 *
 * @param[in] pCriticalSection Pointer to the critical section object.
 * @return The function always return ::NOERROR.
 */
ELAPI_(void) _CCriticalSection_Enter(
        /* [in] */ _ELASTOS CriticalSection *pCriticalSection);

/**
 * Attempts to enter a critical section object without blocking.
 *
 * Not implemented.
 */
ELAPI _CCriticalSection_TryEnter(
       /* [in] */ _ELASTOS CriticalSection *pCriticalSection,
       /* [out] */ _ELASTOS Boolean *pEntered);

/**
 * Releases ownership of the specified critical section object.
 *
 * @param[in] pCriticalSection Pointer to the critical section object.
 * @return If the function succeeds, the return value is ::NOERROR.
 * @return If the function fails and the return value is ::E_NOT_OWNER,
 * it indicats that the calling thread does not own the critical section object.
 */
ELAPI_(void) _CCriticalSection_Leave(
        /* [in] */ _ELASTOS CriticalSection *pCriticalSection);

/**
 * Releases all resources used by an unowned critical section object.
 *
 * @param[in] pCriticalSection Pointer to the critical section object.
 * @return The function always return ::NOERROR.
 */
ELAPI_(void) _CCriticalSection_Terminate(
        /* [in] */ _ELASTOS CriticalSection *pCriticalSection);
/** @} */

/** @addtogroup CARRef
  *   @{
  */
ELAPI_(void) _Impl_CallbackSink_FreeCallbackEvent(
            _ELASTOS PVoid pCallbackEvent);

typedef _ELASTOS Int32 CallbackEventId;
typedef _ELASTOS Int32 CallbackEventFlags;

#define CallbackEventFlag_PriorityMask  0x000000FF
#define CallbackEventFlag_Normal        0x00000000
#define CallbackEventFlag_Duplicated    0x00000100
#define CallbackEventFlag_SyncCall      0x00000200
#define CallbackEventFlag_DirectCall    0x00000400

#define CallingStatus_Created       0x01
#define CallingStatus_Running       0x02
#define CallingStatus_Completed     0x03
#define CallingStatus_Cancelled     0x04

typedef _ELASTOS ECode (ELFUNCCALLTYPE *PCallbackEventHandleRoutine)(_ELASTOS PVoid pvThis);

typedef _ELASTOS ECode (ELFUNCCALLTYPE *PCoalesceEventFunc)(_ELASTOS PVoid* ppOld, _ELASTOS PVoid* ppNew);

#define THREAD_STACK_LIMIT  (0x80000000 - 0x400000)
#ifdef _neptune
#define THREAD_STACK_BASE   0x77D00000
#else
#define THREAD_STACK_BASE   0x60000000
#endif

#ifdef __cplusplus

#include <linknode.h>

// mayq, add, to use atomic_inc and atomic_dec
#include <sys/el_atomics.h>

class _CMapNode : public DLinkNode
{
public:
    _ELASTOS Char8*  m_pstrKey;
    _ELASTOS Char8*  m_pstrValue;
};

ELAPI_(_CMapNode*) _Impl_CMap_AllocNode(_ELASTOS String key, _ELASTOS String value);

ELAPI_(void) _Impl_CMap_FreeNode(_CMapNode* node);

class _EzCallbackEvent : public DLinkNode
{
public:
    _EzCallbackEvent(
        CallbackEventId id,
        CallbackEventFlags flags,
        PInterface pSender,
        PInterface pReceiver,
        _ELASTOS PVoid pDomain,
        _ELASTOS PVoid pCoalesceFunc,
        _ELASTOS PVoid pHandlerThis,
        _ELASTOS PVoid pHandlerFunc,
        _ELASTOS Int32 typeOfFunc,
        ICallbackParcel* pParameters) : m_id(id), m_flags(flags),
            m_pSender(pSender), m_pReceiver(pReceiver), m_pDomain(pDomain),
            m_pCoalesceFunc(pCoalesceFunc),
            m_pHandlerThis(pHandlerThis), m_pHandlerFunc(pHandlerFunc),
            m_typeOfFunc(typeOfFunc), m_ecRet(NOERROR), m_pSyncEvent(NULL),
            m_Status(CallingStatus_Created), m_bCompleted(0),
            m_pParameters(pParameters), m_cRef(0)
    {
        if (m_pSender) m_pSender->AddRef();
        if (m_pParameters) m_pParameters->AddRef();
        AddRef();
    }

    virtual ~_EzCallbackEvent()
    {
        if (m_pSender) m_pSender->Release();
        if (m_pParameters) m_pParameters->Release();
        if (m_pSyncEvent) {
            m_pSyncEvent->Notify();
            m_pSyncEvent->Release();
        }
    }

    _ELASTOS UInt32 AddRef() { return atomic_inc(&m_cRef); }

    _ELASTOS UInt32 Release()
    {
        _ELASTOS Int32 nRef = atomic_dec(&m_cRef);
        if (nRef == 0) _Impl_CallbackSink_FreeCallbackEvent(this);
        return nRef;
    }

public:
    CallbackEventId             m_id;
    CallbackEventFlags          m_flags;
    PInterface                  m_pSender;
    PInterface                  m_pReceiver;
    _ELASTOS PVoid              m_pDomain;
    _ELASTOS PVoid              m_pCoalesceFunc;
    _ELASTOS PVoid              m_pHandlerThis;
    _ELASTOS PVoid              m_pHandlerFunc;
    _ELASTOS Int32              m_typeOfFunc;
    _ELASTOS ECode              m_ecRet;
    IEvent*                     m_pSyncEvent;
    _ELASTOS Int16              m_Status;
    _ELASTOS Int16              m_bCompleted;
    ICallbackParcel*            m_pParameters;
private:
    _ELASTOS Int32              m_cRef;
};

typedef class _EzCallbackEvent  *PCallbackEvent;

class StaticObject : public SingleLinkNode
{
public:
    StaticObject(PInterface pObj):m_pObject(pObj) { }
    ~StaticObject()
    {
        if (m_pObject) m_pObject->Release();
    }

    PInterface m_pObject;
};

typedef class StaticObject *PStaticObject;

#else

typedef _ELASTOS PVoid PCallbackEvent;

#endif // __cplusplus

ELAPI _Impl_CallbackSink_InitCallbackContext(
            PInterface *ppCallbackContext);

ELAPI _Impl_CallbackSink_GetCallbackContext(
            PInterface *ppCallbackContext);

ELAPI _Impl_CallbackSink_AcquireCallbackContext(
            PInterface *ppCallbackContext);

ELAPI_(PCallbackEvent) _Impl_CallbackSink_AllocCallbackEvent(
            _ELASTOS MemorySize size);


ELAPI _Impl_CallbackSink_GetThreadEvent(
            PInterface pCallbackContext, IEvent** ppEvent);

ELAPI _Impl_CallbackSink_PostCallbackEvent(
            PInterface pCallbackContext,
            PCallbackEvent pCallbackEvent);

ELAPI _Impl_CallbackSink_SendCallbackEvent(
            PInterface pCallbackContext,
            PCallbackEvent pCallbackEvent,
            _ELASTOS Millisecond32 timeOut);

ELAPI _Impl_CallbackSink_WaitForCallbackEvent(
            PInterface pCallbackContext,
            _ELASTOS Millisecond32 msTimeOut,
            WaitResult* pResult,
            _ELASTOS Boolean *pbEventOccured,
            _ELASTOS Flags32 fPriority);

ELAPI _Impl_CallbackSink_CleanupAllCallbacks(
    IInterface *pCallbackContext);

ELAPI _Impl_CallbackSink_CancelPendingAllCallbacks(
            PInterface pCallbackContext,
            PInterface pSender);

ELAPI _Impl_CallbackSink_CancelPendingCallback(
            PInterface pCallbackContext,
            PInterface pSender,
            CallbackEventId id);

ELAPI _Impl_CallbackSink_CancelCallbackEvents(
            PInterface pCallbackContext,
            PInterface pSender,
            CallbackEventId id,
            _ELASTOS PVoid pHandlerThis,
            _ELASTOS PVoid pHandlerFunc);

ELAPI _Impl_CallbackSink_RequestToFinish(
    PInterface pCallbackContext, _ELASTOS Int32 Flag);

ELAPI_(_ELASTOS Int32) _Impl_CallbackSink_GetStatus(
    PInterface pCallbackContext);

ELAPI_(ExitCode) _Impl_CallbackSink_TryToHandleEvents(IInterface* pCallbackContext);

ELAPI _Impl_CCallbackRendezvous_New(
        PInterface pCallbackContext,
        ICallbackSink* pCallbackSink,
        CallbackEventId eventId,
        _ELASTOS Boolean* pbEventFlag,
        _ELASTOS Boolean bNewCallback,
        ICallbackRendezvous** ppICallbackRendezvous);

ELAPI _CHostingManager_Acquire(
        /* [out] */ IHostingManager **ppManager);

ELAPI EzSetModuleGlobalValue(
        /* [in] */ _ELASTOS PVoid value);

ELAPI EzSetModuleGlobalMem(
        /* [in] */ _ELASTOS PVoid pMem);

ELAPI EzSetModuleGlobalObj(
        /* [in] */ PInterface pObj);

ELAPI EzGetModuleGlobalValue(
        /* [out] */ _ELASTOS PVoid *pValue);

ELAPI EzGetModuleGlobalMem(
        /* [out] */ _ELASTOS PVoid *ppMem);

ELAPI EzGetModuleGlobalObj(
        /* [out] */ PInterface *ppObj);

struct KBDStatus;

ELAPI _EzGetVirKey(
        /* [out] */ struct KBDStatus *pVirutalCode);

ELAPI_(int) _Impl_VcodeToAscii(
        /* [in] */ uint8_t uVirtualcode,
        /* [in] */ uint16_t uLedState,
        /* [in] */ uint16_t uKeyboardState);

ELAPI _Impl_GetChar(_ELASTOS UInt32 toRead, _ELASTOS MemoryBuf * pBuf,
    _ELASTOS Boolean bBuffer);

ELAPI _Impl_GetStartInfo(
        /* [out] */ _ELASTOS StringBuf * pCmdName,
        /* [out] */ _ELASTOS StringBuf * pCmdArgs);

ELAPI _EzSetStdDevice(
        /* [in] */ _ELASTOS UInt32 stdDeviceNo,
        /* [in] */ _ELASTOS String fileName);

ELAPI _EzGetStdDevice(
        /* [in] */ _ELASTOS UInt32 stdDeviceNo,
        /* [Out]*/ _ELASTOS Char8** ppFileName);

ELAPI EzNotify(
        /* [in] */ int eType,
        /* [in] */ int nCode,
        /* [in] */ void *pParam);

#ifdef _MSVC
#pragma warning( default : 4190 )
#endif

ELAPI_(_ELASTOS PVoid) GetErrorInfo();

ELAPI _CReflector_AcquireModuleInfo(
    /* [in] */ _ELASTOS String name,
    /* [out] */ IModuleInfo **piModuleInfo);

ELAPI _CReflector_AcquireIntrinsicTypeInfo(
    /* [in] */ CarDataType intrinsicType,
    /* [out] */ IDataTypeInfo **ppIntrinsicTypeInfo);

#ifdef __cplusplus
ELAPI _CReflector_AcquireEnumInfo(
    /* [in] */ _ELASTOS String name,
    /* [in] */ const _ELASTOS BufferOf<_ELASTOS String> *pItemNames,
    /* [in] */ const _ELASTOS BufferOf<_ELASTOS Int32> *pItemValues,
    /* [out] */ IEnumInfo **ppEnumInfo);


ELAPI _CReflector_AcquireStructInfo(
    /* [in] */ _ELASTOS String name,
    /* [in] */ const _ELASTOS BufferOf<_ELASTOS String> *pFieldNames,
    /* [in] */ const _ELASTOS BufferOf<IDataTypeInfo *> *pFieldTypeInfos,
    /* [out] */ IStructInfo **ppStructInfo);
#else

ELAPI _CReflector_AcquireEnumInfo(
    /* [in] */ _ELASTOS String name,
    /* [in] */ const _ELASTOS PCarQuintet pItemNames,
    /* [in] */ const _ELASTOS PCarQuintet pItemValues,
    /* [out] */ IEnumInfo **ppEnumInfo);


ELAPI _CReflector_AcquireStructInfo(
    /* [in] */ _ELASTOS String name,
    /* [in] */ const _ELASTOS PCarQuintet pFieldNames,
    /* [in] */ const _ELASTOS PCarQuintet pFieldTypeInfos,
    /* [out] */ IStructInfo **ppStructInfo);
#endif

ELAPI _CReflector_AcquireCppVectorInfo(
    /* [in] */ IDataTypeInfo *pElementTypeInfo,
    /* [in] */ _ELASTOS Int32 length,
    /* [out] */ ICppVectorInfo **ppCppVectorInfo);


ELAPI _CReflector_AcquireCarArrayInfo(
    /* [in] */ CarDataType quintetType,
    /* [in] */ IDataTypeInfo *pElementTypeInfo,
    /* [out] */ ICarArrayInfo **ppCarArrayInfo);

ELAPI _CObject_ReflectModuleInfo(
    /* [in] */ PInterface pObj,
    /* [out] */ IModuleInfo **piModuleInfo);

ELAPI _CObject_ReflectClassInfo(
    /* [in] */ PInterface pObj,
    /* [out] */ IClassInfo **piClassInfo);

ELAPI _CObject_ReflectInterfaceInfo(
    /* [in] */ PInterface pObj,
    /* [out] */ IInterfaceInfo **piInterfaceInfo);

ELAPI _CScheme_Instantiate(
    /* [in] */ _ELASTOS String uri,
    /* [out] */ PInterface *object);

ELAPI _Impl_Scheme_Resolve2Path(_ELASTOS String uri, _ELASTOS StringBuf *fullPath);

ELAPI _ReleaseAtProcessExit(PInterface pObject);

ELAPI_(_ELASTOS Boolean) _Impl_CheckHelperInfoFlag(_ELASTOS Flags32 flag);

ELAPI_(void) _Impl_SetHelperInfoFlag(_ELASTOS Flags32 flag, _ELASTOS Boolean bValue);

ELAPI _Impl_EnterProtectedZone();

ELAPI _Impl_LeaveProtectedZone();

ELAPI _Impl_InsideProtectedZone();


EXTERN_C int    __cdecl _Impl_Memcmp(const void *, const void *, size_t);
EXTERN_C void * __cdecl _Impl_Memset(void *, int, size_t);
EXTERN_C int    __cdecl _Impl_Strcmp(const char* , const char* );

// callback helper api for making parameters
ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassID,
    PInterface *ppServerObj);

ELAPI _Impl_AcquireCallbackHandler(
        PInterface pServerObj,
        _ELASTOS REIID iid,
        PInterface *ppHandler);

ELAPI _CCallbackParcel_New(
    ICallbackParcel **ppObj);

#endif // __ELAPI_H__
/** @} */

