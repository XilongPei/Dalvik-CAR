/** @addtogroup SystemRef
  *   @{
  */

//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __ELASYSAPI_H__
#define __ELASYSAPI_H__

#include <elapi.h>

#ifdef __cplusplus

_ELASTOS_NAMESPACE_BEGIN

/**
 * The CSystem class contains several useful class fields and methods.
 *
 * The CSystem class cannot be instantiated.
 */
class CSystem
{
public:
    /**
     * Registers a named service interface in the operation system for incoming requests.
     *
     * @param[in] name The identity of the service interface, should not be null.
     * @param[in] pRunningObject The service interface that will handle requests.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_ALREADY_EXIT,
     * it indicats that the specified name is already exist, you must give a unique name.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI RegisterRunningObject(
        /* [in] */ String name,
        /* [in] */ PInterface pRunningObject)
    {
        return _CSystem_RegisterRunningObject(name, pRunningObject);
    }

    /**
     * Searches for the service that matches the specified name in operation system.
     *
     * @param[in] name The identity of the service interface, should not be null.
     * @param[out] ppRunningObject Pointer to the interface variable that receives the service interface.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST,
     * it indicats that the named service interface does not registered in the operation system.
     */
    STATIC CARAPI FindRunningObject(
        /* [in] */ String name,
        /* [out] */ PInterface *ppRunningObject)
    {
        return _CSystem_FindRunningObject(name, ppRunningObject);
    }

    /**
     * Waits until the specified named service interface is be registered or the time-out interval elapses.
     *
     * @param[in] name The identity of the service interface, should not be null.
     * @param[in] timeout The time-out interval, in milliseconds.
     * @param[out] pResult The result of waiting indicates the reason that cause the function to return.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI WaitForRunningObject(
        /* [in] */ String name,
        /* [in] */ Millisecond32 timeout,
        /* [out] */ WaitResult *pResult)
    {
        return _CSystem_WaitForRunningObject(name, timeout, pResult);
    }

    /**
     * Unregistered the service interface by name.
     *
     * @param[in] name The identity of the service interface, should not be null.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST,
     * it indicats that the named service interface does not registered in the operation system.
     */
    STATIC CARAPI UnregisterRunningObject(
        /* [in] */ String name)
    {
        return _CSystem_UnregisterRunningObject(name);
    }

    /**
     * Gets the machine time (system time), in microseconds.
     *
     * @param[out] pMachineTime The pointer to a SystemTime structure variable that receives the current time.
     * @return The return value is always ::NOERROR.
     */
    STATIC CARAPI GetMachineTime(
        /* [out] */ SystemTime *pMachineTime)
    {
        return _CSystem_GetMachineTime(pMachineTime);
    }

    /**
     * Sets the machine time (system time), in Microseconds.
     *
     * @param[in] machineTime A SystemTime structure variable containing the time to be set.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return For descriptions of the other possible returns, please refer to the \ref CARTypesRef.
     */
    STATIC CARAPI SetMachineTime(
        /* [in] */ SystemTime machineTime)
    {
        return _CSystem_SetMachineTime(machineTime);
    }

    /**
     * Gets the elapsed time from system started.
     *
     * Not implemented.
     */
    STATIC CARAPI_(Millisecond32) GetElapsedTime()
    {
        return _CSystem_GetElapsedTime();
    }

    /**
     * Gets the amount of time, in microseconds, that the system has been idle.
     *
     * Not implemented.
     */
    STATIC CARAPI_(Millisecond32) GetIdleTime()
    {
        return _CSystem_GetIdleTime();
    }

    /**
     * Gets the version information of the current operating system.
     *
     * @return The value of the system version number.
     */
    STATIC CARAPI_(Int32) GetVersion()
    {
        return _CSystem_GetVersion();
    }

    /**
     * Gets total and availabel size of system physical memory.
     *
     * Not implemented.
     */
    STATIC CARAPI GetGlobalMemorySizes(
        /* [out] */ Int32 *pTotalPhysicalMemorySize,
        /* [out] */ Int32 *pAvailablePhysicalMemorySize)
    {
        return _CSystem_GetGlobalMemorySizes(
                    pTotalPhysicalMemorySize,
                    pAvailablePhysicalMemorySize);
    }

    /**
     * Writes debug information to the console.
     *
     * @param[in] message Message to be output to the console.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the message string is NULL.
     */
    STATIC CARAPI DebugPrint(
        /* [in] */ String message)
    {
        return _CSystem_DebugPrint(message);
    }

    /**
     * Not supported.
     */
    STATIC CARAPI GetAllProcesses(
        /* [out] */ IObjectEnumerator **ppProcesses)
    {
        return _CSystem_GetAllProcesses(ppProcesses);
    }

    /**
     * Reboot the operating system.
     *
     * Not implemented.
     */
    STATIC CARAPI Reboot()
    {
        return _CSystem_Reboot();
    }

    /**
     * Creates a system event object for waiting system event.
     *
     * Not implemented.
     */
    STATIC CARAPI CreateSystemEventHandle(
        /* [in] */ SystemEvents interestedEvents,
        /* [out] */ IEvent **ppEvent)
    {
        return _CSystem_CreateSystemEventHandle(interestedEvents, ppEvent);
    }

    /**
     * Waits until one of the specified system events is signaled.
     *
     * Not implemented.
     */
    STATIC CARAPI WaitForAnySystemEvent(
        /* [in] */ SystemEvents interestedEvents)
    {
        return _CSystem_WaitForAnySystemEvent(interestedEvents);
    }

    /**
     * Retrives the current value of the high-resolution performance counter.
     *
     * @param[out] pPerformanceCount The pointer to a variable that receives the current performance counter.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the value of pPerformanceCount parameter is NULL.
     * @return For descriptions of the other possible returns, please refer to the \ref CARTypesRef.
     */
    STATIC CARAPI QueryPerformanceCounter(
        /* [out] */ Int64 *pPerformanceCount)
    {
        return _CSystem_QueryPerformanceCounter(pPerformanceCount);
    }

    /**
     * Retrives the frequency of the high-resolution performance counter.
     *
     * @param[out] pFrequency The pointer to a variable that receives the performance counter frequency.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the value of pFrequency parameter is NULL.
     * @return For descriptions of the other possible returns, please refer to the \ref CARTypesRef.
     */
    STATIC CARAPI QueryPerformanceFrequency (
        /* [out] */ Int64 *pFrequency)
    {
        return _CSystem_QueryPerformanceFrequency(pFrequency);
    }

    /**
     * Retrives the information of the specified disk.
     *
     * Not implemented.
     */
    STATIC CARAPI GetDiskCapacity(
        /* [in] */ String diskDrive,
        /* [out] */ Int64* pCapacityInBytes,
        /* [out] */ Int64* pFreeSpaceInBytes)
    {
        return _CSystem_GetDiskCapacity(diskDrive, pCapacityInBytes, pFreeSpaceInBytes);
    }
};

/**
 * The CProcess class represents the process object.
 *
 * This class implements IProcess CAR interfaces.
 */
class CProcess
{
public:
    /**
     * Not supported.
     */
    STATIC CARAPI New(
        /* [in] */ String name,
        /* [in] */ String args,
        /* [out] */ IProcess **ppProcess)
    {
        return _CProcess_New(name, args, ppProcess);
    }

    /**
     * Not supported.
     */
    STATIC CARAPI New(
        /* [out] */ IProcess **ppProcess)
    {
        return _CProcess_NewUnstarted(ppProcess);
    }

    /**
     * Gets current process interface.
     *
     * @return The function never fails, and the return value is the interface of current process object.
     */
    STATIC CARAPI_(IProcess *) GetCurrent()
    {
        return _CProcess_GetCurrent();
    }

    /**
     * Ends current process and all of its threads.
     *
     * @param[in] exitCode Specifies the exit code for the current process and for all its threads.
     * @return The function has no return value.
     */
    STATIC CARAPI_(void) Exit(
        /* [in] */ ExitCode exitCode)
    {
        _CProcess_Exit(exitCode);
    }

    /**
     * Terminates current process and all of its threads.
     *
     * @param[in] exitCode Specifies the exit code for the current process and for all its threads.
     * @return The function has no return value.
     */
    STATIC CARAPI_(void) Terminate(
        /* [in] */ ExitCode exitCode)
    {
        _CProcess_Terminate(exitCode);
    }

    /**
     * Sets function that will be executed when current process exits.
     *
     * @param[in] pEntry Function to be called at the process exit.
     * @param[in] pUserData Pointer to context data used by the function.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that pEntry is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI AtExit(
        /* [in] */ PProcessExitRoutine pEntry,
        /* [in] */ PVoid pUserData)
    {
        return _CProcess_AtExit(pEntry, pUserData);
    }

    template <class T>
    STATIC CARAPI AtExit(
        /* [in] */ T * pThis,
        /* [in] */ void (ELAPICALLTYPE T::*pEntry)())
    {
        EventHandler delegate = EventHandler::Make(pThis, *(void **)&pEntry, CallbackType_CPP);
        return _CProcess_AtExit(
                (PProcessExitRoutine)delegate.GetFuncPtr(),
                delegate.GetThisPtr());
    }

    /**
     * Unload the module from current process by module name.
     *
     * @param[in] szDllName A name of module to be unloaded.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the value of szDllName parameter is NULL.
     * @return If the function fails and the return value is ::E_NOT_CAR_DLL,
     * it indicats that the module to be unloaded is not the CAR module.
     * @return If the function fails and the return value is ::E_DLL_CANNOT_UNLOAD_NOW,
     * it indicats that the module can't unload now and try unload it later.
     * @return If the function fails and the return value is ::E_DLL_NOT_LOADED,
     * it indicats failed to unload module.
     */
    STATIC CARAPI FreeUnusedModule(String szDllName)
    {
        return _CProcess_FreeUnusedModule(szDllName);
    }

    /**
     * Unload the unused modules in current process.
     *
     * @param[in] bImmediate Specific whether immediately unload module.
     * @return The function has no return value.
     */
    STATIC CARAPI_(void) FreeUnusedModules()
    {
        _CProcess_FreeUnusedModules(TRUE);
    }

    /**
     * Flushes the instruction cache for the current process.
     *
     * Not implemented.
     */
    STATIC CARAPI FlushInstructionCache(
        /* [in] */ Address baseAddr,
        /* [in] */ MemorySize size)
    {
        return _CProcess_FlushInstructionCache(baseAddr, size);
    }
};

/**
 * The CModule class represents the module object.
 *
 * This class implements IModule CAR interfaces.
 */
class CModule
{
public:
    /**
     * Gets current process module.
     *
     * @param[out] ppModule Pointer to a IModule interface used to manage current process module.
     * @return The function always returns ::NOERROR.
     */
    STATIC CARAPI GetCurrent(
        /* [out] */ IModule **ppModule)
    {
        return _CModule_GetCurrent(ppModule);
    }

    /**
     * Loads module to current process with loading flags.
     *
     * Not implemented.
     */
    STATIC CARAPI Load(
        /* [in] */ String name,
        /* [in] */ ModuleLoadFlags flags,
        /* [out] */ IModule **ppModule)
    {
        return _CModule_Load(name, flags, ppModule);
    }
};

class CMemoryHeap
{
public:
    STATIC CARAPI_(PVoid) Alloc(
        /* [in] */ MemorySize size,
        /* [in] */ Boolean zeroMemory)
    {
        return _CMemoryHeap_Alloc(size, zeroMemory);
    }

    STATIC CARAPI_(PVoid) Realloc(
        /* [in] */ PVoid pMemory,
        /* [in] */ MemorySize size)
    {
        return _CMemoryHeap_Realloc(pMemory, size);
    }

    STATIC CARAPI_(void) Free(
        /* [in] */ PVoid pMemory)
    {
        _CMemoryHeap_Free(pMemory);
    }

    STATIC CARAPI_(Boolean) Trim(
        /* [in] */ MemorySize pad)
    {
        return _CMemoryHeap_Trim(pad);
    }

    STATIC CARAPI GetStatistics(
        /* [out] */ MemorySize *pInUseBytes,
        /* [out] */ MemorySize *pSystemBytes,
        /* [out] */ MemorySize *pMaxSystemBytes)
    {
        return _CMemoryHeap_GetStatistics(
                pInUseBytes, pSystemBytes, pMaxSystemBytes);
    }
};

/**
 * The CVirtualMemory class represents the virtual memory object.
 *
 * This class implements IVirtualMemory CAR interfaces.
 */
class CVirtualMemory
{
public:
    /**
     * Reserves a region of pages in the virtual address space of the calling process.
     *
     * @param[in] baseAddr The starting address of the region to be allocated.
     * @param[in] size The region size, in bytes.
     * @param[in] flags The flags of memory allocation.
     * @param[in] protection The memory protection for the region of pages to be allocated.
     * @param[out] pBaseAddr Pointer to the base address of the allocated region.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the parameters used to call this function is invalid.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI Alloc(
        /* [in] */ Address baseAddr,
        /* [in] */ MemorySize size,
        /* [in] */ MemoryMapFlags flags,
        /* [in] */ MemoryProtection protection,
        /* [out] */ Address *pBaseAddr)
    {
        return _CVirtualMemory_Alloc(
                baseAddr, size, flags, protection, pBaseAddr);
    }

    /**
     * Retrives virtual infomation about the region in the virtual space of calling process.
     *
     * @param[in] address A virtual address in the region.
     * @param[out] pBaseAddr Pointer to the base address of the region.
     * @param[out] *pSize Pointer to the size of the region.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that pBaseAddr or pSize is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI Query(
        /* [in] */ Address address,
        /* [out] */ Address *pBaseAddr,
        /* [out] */ MemorySize *pSize)
    {
        return _CVirtualMemory_Query(address, pBaseAddr, pSize);
    }

    /**
     * Retrives physical infomation about the region in the virtual space of calling process.
     *
     * Not implemented.
     */
    STATIC CARAPI QueryPhysicalBlock(
        /* [in] */ Address address,
        /* [out] */ Address *pAddress,
        /* [out] */ MemorySize *pSize)
    {
        return _CVirtualMemory_QueryPhysicalBlock(address, pAddress, pSize);
    }

    /**
     * Changes the protection of committed pages in the virtual space of calling process.
     *
     * @param[in] baseAddr The base address of the region, should be page aligned.
     * @param[in] size The size of the region, should alse be page aligned.
     * @param[in] protection The memory protection option.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the value of the size paramter is not a positive number.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI SetProtection(
        /* [in] */ Address baseAddr,
        /* [in] */ MemorySize size,
        /* [in] */ MemoryProtection protection)
    {
        return _CVirtualMemory_SetProtection(baseAddr, size, protection);
    }

    /**
     * Checks whether the region of pages has the specific protection.
     *
     * @param[in] address The virtual address in the region.
     * @param[in] protection The specific protection used to check.
     * @param[out] pIsValid Pointer to the variable that shows whether the region of pages has the specific protection.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that pIsValid is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI CheckProtection(
        /* [in] */ Address address,
        /* [in] */ MemoryProtection protection,
        /* [out] */ Boolean *pIsValid)
    {
        return _CVirtualMemory_CheckProtection(address, protection, pIsValid);
    }

    /**
     * Commits an allocated region of pages in the virtual space of the calling process.
     *
     * @param[in] address The base address of the region.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the value of the address parameter is NULL or not page aligned.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI Commit(
        /* [in] */ Address address)
    {
        return _CVirtualMemory_Commit(address);
    }

    /**
     * Frees the virtual memory.
     *
     * @param[in] baseAddr The base address of the region.
     * @param[in] size The size of the region.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the value of the size paramter is not a positive number.
     */
    STATIC CARAPI Free(
        /* [in] */ Address baseAddr,
        /* [in] */ MemorySize size)
    {
        return _CVirtualMemory_Free(baseAddr, size);
    }

    /**
     * Maps physical space region of pages to virtual space region of pages in calling process.
     *
     * Not implemented.
     */
    STATIC CARAPI IoRemap(
        /* [in] */ Address virtualAddr,
        /* [in] */ MemorySize size,
        /* [in] */ Address physicalAddr,
        /* [in] */ MemoryMapFlags flags,
        /* [in] */ Int32 protection,
        /* [out] */ Address *pVirtualAddr)
    {
        return _CVirtualMemory_IoRemap(
                    virtualAddr,
                    size,
                    physicalAddr,
                    flags,
                    protection,
                    pVirtualAddr);
    }
};

/**
 * The CMutex class represents the mutex object.
 *
 * This class implements IMutex CAR interfaces.
 */
class CMutex
{
public:
    /**
     * Creates the mutex object.
     *
     * @param[out] ppMutex Pointer to the IMutex interface to manage mutex object.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the ppMutex is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI New(
        /* [out] */ IMutex **ppMutex)
    {
        return _CMutex_New(ppMutex);
    }

    /**
     * Creates or opens named mutex object.
     *
     * @param[in] name The name of the mutex object which will be created or opened.
     * @param[out] ppMutex Pointer to the IMutex interface to manage mutex object.
     * @param[out] pAlreadyExists Pointer to the variable which show whether the returned mutex object is already existed.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the ppMutex or the pAlreadyExists is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     * @return If the function fails and the return value is ::E_SERVICE_NAME_TOO_LONG,
     * it indicats that the length of specified mutex name is too long.
     */
    STATIC CARAPI New(
        /* [in] */ String name,
        /* [out] */ IMutex **ppMutex,
        /* [out] */ Boolean *pAlreadyExists)
    {
        return _CMutex_NewWithName(name, ppMutex, pAlreadyExists);
    }
};

/**
 * The CCondition class represents the condition object.
 *
 * This class implements ICondition CAR interfaces.
 */
class CCondition
{
public:
    /**
     * Creates condition object.
     *
     * Not implemented.
     */
    STATIC CARAPI New(
        /* [out] */ ICondition **ppCondition)
    {
        return _CCondition_New(ppCondition);
    }

    /**
     * Creates or opens named condition object.
     *
     * Not implemented.
     */
    STATIC CARAPI New(
        /* [in] */ String name,
        /* [out] */ ICondition **ppCondition,
        /* [out] */ Boolean *pAlreadyExists)
    {
        return _CCondition_NewWithName(name, ppCondition, pAlreadyExists);
    }
};

/**
 * The CEvent class represents the event object.
 *
 * This class implements IEvent CAR interfaces.
 */
class CEvent
{
public:
    /**
     * Creates event object.
     *
     * @param[in] manualReset If this parameter is TRUE, user must set event state manually.
     * @param[in] initialState If this parameter is TRUE, the initial state of event object is signaled; otherwise, it's nonsignaled.
     * @param[out] ppEvent Pointer to the IEvent interface to manage event object.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the ppEvent is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI New(
        /* [in] */ Boolean manualReset,
        /* [in] */ EventState initialState,
        /* [out] */ IEvent **ppEvent)
    {
        return _CEvent_New(manualReset, initialState, ppEvent);
    }

    /**
     * Creates or opens named event object.
     *
     * @param[in] name The name of the event object which will be created or opened.
     * @param[in] manualReset If this parameter is TRUE, user must set event state manually.
     * @param[in] initialState If this parameter is TRUE, the initial state of event object is signaled; otherwise, it's nonsignaled.
     * @param[out] ppEvent Pointer to the IEvent interface to manage event object.
     * @param[out] pAlreadyExists Pointer to the variable which show whether the returned event object is already existed.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the ppEvent or the pAlreadyExists is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     * @return If the function fails and the return value is ::E_SERVICE_NAME_TOO_LONG,
     * it indicats that the length of specified event name is too long.
     */
    STATIC CARAPI New(
        /* [in] */ String name,
        /* [in] */ Boolean manualReset,
        /* [in] */ EventState initialState,
        /* [out] */ IEvent **ppEvent,
        /* [out] */ Boolean *pAlreadyExists)
    {
        return _CEvent_NewWithName(
                name, manualReset, initialState, ppEvent, pAlreadyExists);
    }

    /**
     * Waits untile one or all of the specified event objects are in the signaled state.
     *
     * Not implemented.
     */
    STATIC CARAPI WaitForAnyEvents(
        /* [in] */ const BufferOf<IEvent *> & events,
        /* [out] */ WaitResult *pResult,
        /* [out] */ Int32 *pIndex)
    {
        return _CEvent_WaitForAnyEvents(&events, pResult, pIndex);
    }

    /**
     * Waits untile one or all of the specified event objects are in the signaled state or time-out interval elapses.
     *
     * Not implemented.
     */
    STATIC CARAPI TryWaitForAnyEvents(
        /* [in] */ const BufferOf<IEvent *> & events,
        /* [in] */ Millisecond32 timeout,
        /* [out] */ WaitResult *pResult,
        /* [out] */ Int32 *pIndex)
    {
        return _CEvent_TryWaitForAnyEvents(
                &events, timeout, pResult, pIndex);
    }
};

/**
 * The CReaderWriterLock class represents the reader-writer lock object.
 *
 * This class implements IReaderWriterLock CAR interfaces.
 */
class CReaderWriterLock
{
public:
    /**
     * Creates lock object of reading and writing.
     *
     * Not implemented.
     */
    STATIC CARAPI New(
        /* [out] */ IReaderWriterLock **ppRWLock)
    {
        return _CReaderWriterLock_New(ppRWLock);
    }

    /**
     * Creates or opens named lock object of reading and writing.
     *
     * Not implemented.
     */
    STATIC CARAPI New(
        /* [in] */ String name,
        /* [out] */ IReaderWriterLock **ppRWLock,
        /* [out] */ Boolean *pAlreadyExists)
    {
        return _CReaderWriterLock_NewWithName(name, ppRWLock, pAlreadyExists);
    }
};

/**
 * The CSharedMemory class represents the shared memory object.
 *
 * This class implements ISharedMemory CAR interfaces.
 */
class CSharedMemory
{
public:
    /**
     * Creates or opens a named share memory object.
     *
     * @param[in] name The name of the share memory object.
     * @param[in] size The size of the share memory.
     * @param[in] reserved Reserved parameter, must be TRUE.
     * @param[out] ppSharedMemory Pointer to the ISharedMemory interface used to manage share memory object.
     * @param[out] pAlreadyExists Pointer to the bool variable which shows whether the retrived share memory object is already existed.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the ppSharedMemory or the pAlreadyExists is NULL, or the reserved parameter is FALSE.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     * @return If the function fails and the return value is ::E_SERVICE_NAME_TOO_LONG,
     * it indicats that the length of specified share memory name is too long.
     */
    STATIC CARAPI New(
        /* [in] */ String name,
        /* [in] */ MemorySize size,
        /* [in] */ Boolean reserved,
        /* [out] */ ISharedMemory **ppSharedMemory,
        /* [out] */ Boolean *pAlreadyExists)
    {
        return _CSharedMemory_New(
                name, size, reserved, ppSharedMemory, pAlreadyExists);
    }
};

/**
 * The CActiveTimer class represents the active timer object.
 *
 * This class implements IActiveTimer CAR interfaces.
 */
class CActiveTimer
{
public:
    /**
     * Creates the active timer object.
     * Every new created timer runs in the new thread. The timer call the callback function
     * when every next timer internal elapses.
     *
     * @param[in] interval The interval of the active timer.
     * @param[in] pEntry The callback function of the active timer.
     * @param[in] pUserData The user data pointer for the callback function.
     * @param[out] ppActiveTimer The pointer to the IActiveTimer interface that receives the active timer interface.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that the amount of the timer interval is too short, or the ppActiveTimer pointer is NULL.
     * @return If the function fails and the return value is ::E_OUT_OF_MEMORY,
     * it indicats not enough space.
     */
    STATIC CARAPI New(
        /* [in] */ Millisecond32 interval,
        /* [in] */ ECode (ELAPICALLTYPE *pEntry)(PVoid, IActiveTimer *),
        /* [in] */ PVoid pUserData,
        /* [out] */ IActiveTimer ** ppActiveTimer)
    {
        return _CActiveTimer_New(interval, pEntry, pUserData, ppActiveTimer);
    }

    template <class T>
    STATIC CARAPI New(
        /* [in] */ Millisecond32 interval,
        /* [in] */ T * pThis,
        /* [in] */ ECode (ELAPICALLTYPE T::*pEntry)(IActiveTimer *),
        /* [out] */ IActiveTimer ** ppActiveTimer)
    {
        EventHandler d = EventHandler::Make((void *)pThis, *(void **)&pEntry, CallbackType_CPP);
        return _CActiveTimer_New(
            interval,
            (ECode (ELAPICALLTYPE *)(PVoid, IActiveTimer *))d.GetFuncPtr(),
            d.GetThisPtr(),
            ppActiveTimer);
    }
};

/**
 * The CErrorReport class contains functions for inputting or outputting error information.
 */
class CErrorReport
{
public:
    /**
     * Sets the error information for the calling thread.
     *
     * Not implemented.
     */
    STATIC CARAPI SetString(
        /* [in] */ String string)
    {
        return _CErrorReport_SetString(string);
    }

    /**
     * Sets the the URL of error information for the calling thread.
     *
     * Not implemented.
     */
    STATIC CARAPI SetUrl(
        /* [in] */ String url)
    {
        return _CErrorReport_SetUrl(url);
    }

    /**
     * Gets the error information for the calling thread.
     *
     * Not implemented.
     */
    STATIC CARAPI_(String) GetString()
    {
        return _CErrorReport_GetString();
    }

    /**
     * Gets the the URL of error information for the calling thread.
     *
     * Not implemented.
     */
    STATIC CARAPI_(String) GetUrl()
    {
        return _CErrorReport_GetUrl();
    }
};

/**
 * The CProfile class contains functions for reading or writing system configure file.
 */
class CProfile
{
public:
    /**
     * Gets the string value at a specified key and application name from the file "elastos.cfg".
     *
     * @param[in] appName Specified application name.
     * @param[in] keyName Specified key.
     * @param[out] pReturnedString The pointer to the string buffer that receives the string value.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that appName, keyName or pReturnedString is NULL.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST
     * it indicats that config file, app name or key name does not exist.
     */
    STATIC CARAPI GetString(
        /* [in] */ String appName,
        /* [in] */ String keyName,
        /* [out] */ StringBuf *pReturnedString)
    {
        return _CProfile_GetString(
                appName, keyName, pReturnedString);
    }

    /**
     * Gets the value at a specified key and application name from the file "elastos.cfg".
     *
     * @param[in] appName Specified application name.
     * @param[in] keyName Specified key.
     * @param[out] pValue The pointer to the Int32 that receives the value.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that appName, keyName or pReturnedString is NULL.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST
     * it indicats that config file, app name or key name does not exist.
     */
    STATIC CARAPI GetInt32(
        /* [in] */ String appName,
        /* [in] */ String keyName,
        /* [out] */ Int32 *pValue)
    {
        return _CProfile_GetInt32(appName, keyName, pValue);
    }
};

/**
 * The CProfile class contains functions for reading or writing specified configure file.
 */
class CPrivateProfile
{
public:
    /**
     * Gets the string value at a specified key and application name from the specified file.
     *
     * @param[in] fileName Specified file name.
     * @param[in] appName Specified application name.
     * @param[in] keyName Specified key.
     * @param[out] pReturnedString The pointer to the string buffer that receives the string value.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that appName, keyName or pReturnedString is NULL.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST
     * it indicats that config file, app name or key name does not exist.
     */
    STATIC CARAPI GetString(
        /* [in] */ String fileName,
        /* [in] */ String appName,
        /* [in] */ String keyName,
        /* [out] */ StringBuf *pReturnedString)
    {
        return _CPrivateProfile_GetString(fileName,
                appName, keyName, pReturnedString);
    }

    /**
     * Gets the value at a specified key and application name from the specified file.
     *
     * @param[in] fileName Specified file name.
     * @param[in] appName Specified application name.
     * @param[in] keyName Specified key.
     * @param[out] pValue The pointer to the Int32 that receives the value.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that appName, keyName or pReturnedString is NULL.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST
     * it indicats that config file, app name or key name does not exist.
     */
    STATIC CARAPI GetInt32(
        /* [in] */ String fileName,
        /* [in] */ String appName,
        /* [in] */ String keyName,
        /* [out] */ Int32 *pValue)
    {
        return _CPrivateProfile_GetInt32(fileName, appName, keyName, pValue);
    }

    /**
     * Sets the string value at a specified key and application name from the specified file.
     *
     * @param[in] fileName Specified file name.
     * @param[in] appName Specified application name.
     * @param[in] keyName Specified key.
     * @param[int] value The string that will be set to the file.
     * @return If the function succeeds, the return value is ::NOERROR.
     * @return If the function fails and the return value is ::E_INVALID_ARGUMENT,
     * it indicats that appName, keyName or pReturnedString is NULL.
     * @return If the function fails and the return value is ::E_DOES_NOT_EXIST
     * it indicats that config file, app name or key name does not exist.
     */
    STATIC CARAPI SetString(
        /* [in] */ String fileName,
        /* [in] */ String appName,
        /* [in] */ String keyName,
        /* [in] */ String value)
    {
        return _CPrivateProfile_SetString(fileName,
                appName, keyName, value);
    }
};
/** @} */

/** @addtogroup CARRef
  *   @{
  */
class CReflector
{
public:
    STATIC CARAPI AcquireModuleInfo(
        /* [in] */ String name,
        /* [out] */ IModuleInfo **ppModuleInfo)
    {
        return _CReflector_AcquireModuleInfo(name, ppModuleInfo);
    }

    STATIC CARAPI AcquireIntrinsicTypeInfo(
        /* [in] */ CarDataType intrinsicType,
        /* [out] */ IDataTypeInfo **ppIntrinsicTypeInfo)
    {
        return _CReflector_AcquireIntrinsicTypeInfo(intrinsicType,
            ppIntrinsicTypeInfo);
    }

    STATIC CARAPI AcquireEnumInfo(
        /* [in] */ String name,
        /* [in] */ const BufferOf<String>& itemNames,
        /* [in] */ const BufferOf<Int32>& itemValues,
        /* [out] */ IEnumInfo **ppEnumInfo)
    {
        return _CReflector_AcquireEnumInfo(name, &itemNames, &itemValues,
            ppEnumInfo);
    }

    STATIC CARAPI AcquireCppVectorInfo(
        /* [in] */ IDataTypeInfo *pElementTypeInfo,
        /* [in] */ Int32 length,
        /* [out] */ ICppVectorInfo **ppCppVectorInfo)
    {
        return _CReflector_AcquireCppVectorInfo(pElementTypeInfo, length,
            ppCppVectorInfo);
    }

    STATIC CARAPI AcquireStructInfo(
        /* [in] */ String name,
        /* [in] */ const BufferOf<String>& fieldNames,
        /* [in] */ const BufferOf<IDataTypeInfo *>& fieldTypeInfos,
        /* [out] */ IStructInfo **ppStructInfo)
    {
        return _CReflector_AcquireStructInfo(name, &fieldNames,
            &fieldTypeInfos, ppStructInfo);
    }

    STATIC CARAPI AcquireCarArrayInfo(
        /* [in] */ CarDataType quintetType,
        /* [in] */ IDataTypeInfo *pElementTypeInfo,
        /* [out] */ ICarArrayInfo **ppCarArrayInfo)
    {
        return _CReflector_AcquireCarArrayInfo(quintetType, pElementTypeInfo,
            ppCarArrayInfo);
    }
};

class CObject
{
public:
    STATIC CARAPI_(Boolean) Compare(
        /* [in] */ PInterface pObjectA,
        /* [in] */ PInterface pObjectB)
    {
        return _CObject_Compare(pObjectA, pObjectB);
    }

    STATIC CARAPI ReleaseAtProcessExit(
        /* [in] */ PInterface pObject)
    {
        return _CObject_ReleaseAtProcessExit(pObject);
    }

    STATIC CARAPI ReleaseAtThreadQuit(
        /* [in] */ PInterface pObject)
    {
        return _CObject_ReleaseAtThreadQuit(pObject);
    }

    STATIC CARAPI ReleaseAtAppletFinish(
        /* [in] */ PInterface pObject)
    {
        return _CObject_ReleaseAtAppletFinish(pObject);
    }

    STATIC CARAPI EnterContext(PInterface pObject, PContext pContext)
    {
        return _CObject_EnterContext(pObject, pContext);
    }

    STATIC CARAPI LeaveContext(PInterface pObject, PContext pContext)
    {
        return _CObject_LeaveContext(pObject, pContext);
    }

    STATIC CARAPI EnterContext(PInterface pObject, PInterface pCtxObj)
    {
        PContext pContext = IContext::Probe(pCtxObj);
        if (!pContext) return E_NO_INTERFACE;
        return _CObject_EnterContext(pObject, pContext);
    }

    STATIC CARAPI LeaveContext(PInterface pObject, PInterface pCtxObj)
    {
        PContext pContext = IContext::Probe(pCtxObj);
        if (!pContext) return E_NO_INTERFACE;
        return _CObject_LeaveContext(pObject, pContext);
    }

    STATIC CARAPI CreateInstance(
        RClassID rclsid,
        PContext pContext,
        REIID riid,
        PInterface *ppObj)
    {
        return _CObject_CreateInstance(rclsid, pContext, riid, ppObj);
    }

    STATIC CARAPI CreateInstanceEx(
        RClassID rclsid,
        PContext pContext,
        UInt32 cmq,
        PMULTIQI pResults)
    {
        return _CObject_CreateInstanceEx(rclsid, pContext, cmq, pResults);
    }

    STATIC CARAPI AcquireClassFactory(
        RClassID rclsid,
        PContext pContext,
        REIID iid,
        PInterface *ppObject)
    {
        return _CObject_AcquireClassFactory(rclsid, pContext, iid, ppObject);
    }

    STATIC CARAPI ReflectModuleInfo(
        PInterface pObj,
        IModuleInfo **piModuleInfo)
    {
        return _CObject_ReflectModuleInfo(pObj, piModuleInfo);
    }

    STATIC CARAPI ReflectClassInfo(
        PInterface pObj,
        IClassInfo **piClassInfo)
    {
        return _CObject_ReflectClassInfo(pObj, piClassInfo);
    }

    STATIC CARAPI ReflectInterfaceInfo(
        PInterface pObj,
        IInterfaceInfo **piInterfaceInfo)
    {
        return _CObject_ReflectInterfaceInfo(pObj, piInterfaceInfo);
    }

    STATIC CARAPI Acquire(
        String uri,
        PInterface *object)
    {
        return _CScheme_Instantiate(uri, object);
    }
};



class CCallbackParcel
{
public:
    STATIC CARAPI New(
        /* [out] */ ICallbackParcel ** ppParcel)
    {
        return _CCallbackParcel_New(ppParcel);
    }
};

_ELASTOS_NAMESPACE_END

#endif // __cplusplus

#endif // __ELASYSAPI_H__
/** @} */

