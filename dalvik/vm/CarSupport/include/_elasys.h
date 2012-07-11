interface IProcess;
interface IObjectEnumerator;
interface IModule;
interface IThread;
interface IThreadContext;
interface ISharedMemory;
interface IMemoryTrace;
interface IAppletTaskSpecific;
interface IApplet;
interface JAppletEvents;
interface IHostingManager;
interface IAppletHosting;
interface IMutex;
interface ICondition;
interface IEvent;
interface IReaderWriterLock;
interface IDeviceDriver;
interface IObjectEx;
interface IObjectContainer;
interface ICallbackParcel;
interface ICallbackRendezvous;
interface ICallbackSink;
interface IContext;
interface IAObjectContainerClassObject;
interface IKernel;
interface IStringEnumerator;
interface IBasicFileSystem;
interface IBasicFile;
interface IBasicDirectory;
interface IAbsoluteIO;
interface IFileMonitor;
interface IDiskFileSystem;
interface IDiskManager;
interface ILocaleInfo;
interface IDeviceEventManager;
interface IDeviceEventHandler;
interface IDeviceEventDispatcher;
interface IGrafixEngine;
interface IGrafixLayer;
interface IGrafixObject;
interface IGrafixSurface;
interface IGrafixEventBuffer;
interface IAppletSession;
interface IAppletGUI;
interface JAppletEventsHandler;
interface JAppletPrivateEvents;
interface JAppletPrivateEventsHandler;
interface IAppletTaskStartup;
interface IAppletServices;
interface IAppletSystemSpecific;
interface IActiveTimer;
interface ISocket;
interface ISocketEx;
interface ISocketService;
interface IModuleInfo;
interface IClassInfo;
interface IFunctionInfo;
interface IParamInfo;
interface IMethodInfo;
interface IArgumentList;
interface IDataTypeInfo;
interface ITypeAliasInfo;
interface IConstructorInfo;
interface IInterfaceInfo;
interface ICallbackMethodInfo;
interface ICallbackInvocation;
interface ICallbackArgumentList;
interface IDelegateProxy;
interface IStructInfo;
interface IFieldInfo;
interface IVariable;
interface IVariableOfStruct;
interface IStructSetter;
interface ICppVectorSetter;
interface IStructGetter;
interface ICppVectorGetter;
interface IEnumInfo;
interface IEnumItemInfo;
interface IConstantInfo;
interface IVariableOfCarArray;
interface ICarArraySetter;
interface ICarArrayGetter;
interface IVariableOfStringBuf;
interface IStringBufSetter;
interface IStringBufGetter;
interface ILocalPtrInfo;
interface ICarArrayInfo;
interface IStringBufInfo;
interface ICppVectorInfo;
interface IMediaObject;
interface IConstraint;
interface IDrmManage;
interface IInputStream;
interface IOutputStream;
interface IFileInputStream;
interface IFileOutputStream;
interface IDataInputStream;
interface IDataOutputStream;
interface IStringInputStream;
interface ITextInputStream;
interface ITextOutputStream;
interface IGZipInputStream;
interface IGZipOutputStream;
interface ICFileInputStreamClassObject;
interface ICFileOutputStreamClassObject;
interface ICBufferedInputStreamClassObject;
interface ICBufferedOutputStreamClassObject;
interface ICDataInputStreamClassObject;
interface ICDataOutputStreamClassObject;
interface ICByteArrayInputStreamClassObject;
interface ICByteArrayOutputStreamClassObject;
interface ICStringInputStreamClassObject;
interface ICTextInputStreamClassObject;
interface ICTextOutputStreamClassObject;
interface ICGZipInputStreamClassObject;
interface ICGZipOutputStreamClassObject;
interface IVerifyFile;
interface IScheme;
interface IStream;
interface IStorage;
interface IFile;
interface ITAppletClassObject;
interface JAppletPrivateEventsCallback;
interface JAppletEventsCallback;
EXTERN_C ELAPI _Impl_AcquireCallbackHandler(PInterface pServerObj, _ELASTOS REIID iid, PInterface *ppHandler);

#ifndef __INTERFACE_JAppletEventsHandler_DEFINED__
#define __INTERFACE_JAppletEventsHandler_DEFINED__

CAR_INTERFACE("4C4EF021-9313-3666-D0FD-30A25A7F9CBE")
JAppletEventsHandler : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(JAppletEventsHandler*) Probe(PInterface pObj)
    {
        return (JAppletEventsHandler*)pObj->Probe(EIID_JAppletEventsHandler);
    }

    virtual CARAPI AddStartedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveStartedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireStartedRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddMainCompletedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveMainCompletedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireMainCompletedRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddLayoutReadyCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveLayoutReadyCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireLayoutReadyRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddFinishingCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveFinishingCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireFinishingRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddActivatedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveActivatedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireActivatedRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddDeactivatedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveDeactivatedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireDeactivatedRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddSnoozedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveSnoozedCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireSnoozedRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddWakenupCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveWakenupCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireWakenupRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

    virtual CARAPI AddIdlingCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveIdlingCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireIdlingRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

};

#endif // __INTERFACE_JAppletEventsHandler_DEFINED__
#ifndef __INTERFACE_JAppletPrivateEventsHandler_DEFINED__
#define __INTERFACE_JAppletPrivateEventsHandler_DEFINED__

CAR_INTERFACE("220C7332-9313-350C-58E4-20710345331B")
JAppletPrivateEventsHandler : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(JAppletPrivateEventsHandler*) Probe(PInterface pObj)
    {
        return (JAppletPrivateEventsHandler*)pObj->Probe(EIID_JAppletPrivateEventsHandler);
    }

    virtual CARAPI AddRequestToFinishCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI RemoveRequestToFinishCallback(
        /* [in] */ _ELASTOS EventHandler Param0) = 0;

    virtual CARAPI AcquireRequestToFinishRendezvous(
        /* [out] */ ICallbackRendezvous ** ppParam0) = 0;

};

#endif // __INTERFACE_JAppletPrivateEventsHandler_DEFINED__
#ifndef __INTERFACE_JAppletPrivateEventsCallback_DEFINED__
#define __INTERFACE_JAppletPrivateEventsCallback_DEFINED__

CAR_INTERFACE("2D782C35-9313-350C-58E4-20710345331B")
JAppletPrivateEventsCallback : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(JAppletPrivateEventsCallback*) Probe(PInterface pObj)
    {
        return (JAppletPrivateEventsCallback*)pObj->Probe(EIID_JAppletPrivateEventsCallback);
    }

    virtual CARAPI RequestToFinish(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

};

#endif // __INTERFACE_JAppletPrivateEventsCallback_DEFINED__
#ifndef __INTERFACE_JAppletEventsCallback_DEFINED__
#define __INTERFACE_JAppletEventsCallback_DEFINED__

CAR_INTERFACE("0C586624-9313-3666-E2FC-50AD3F25A217")
JAppletEventsCallback : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(JAppletEventsCallback*) Probe(PInterface pObj)
    {
        return (JAppletEventsCallback*)pObj->Probe(EIID_JAppletEventsCallback);
    }

    virtual CARAPI Started(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI MainCompleted(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS ECode Param1) = 0;

    virtual CARAPI LayoutReady(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Finishing(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Activated(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Deactivated(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Snoozed(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Wakenup(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Idling(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

};

#endif // __INTERFACE_JAppletEventsCallback_DEFINED__

#ifndef __INTERFACE_IProcess_DEFINED__
#define __INTERFACE_IProcess_DEFINED__

CAR_INTERFACE("A059F624-DA52-AA1F-218A-F7E62CA112CD")
IProcess : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IProcess*) Probe(PInterface pObj)
    {
        return (IProcess*)pObj->Probe(EIID_IProcess);
    }

    virtual CARAPI Start(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS String Param1) = 0;

    virtual CARAPI Kill() = 0;

    virtual CARAPI WaitForExit(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI IsAlive(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI SetPriorityRank(
        /* [in] */ ThreadPriorityRank Param0) = 0;

    virtual CARAPI GetPriorityRank(
        /* [out] */ ThreadPriorityRank * pParam0) = 0;

    virtual CARAPI SetThreadPoolCapacity(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetThreadPoolState(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetAllThreads(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI GetAllModules(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI GetModuleByName(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IModule ** ppParam1) = 0;

    virtual CARAPI GetModuleByAddress(
        /* [in] */ _ELASTOS Address Param0,
        /* [out] */ IModule ** ppParam1) = 0;

    virtual CARAPI GetId(
        /* [out] */ ProcessId * pParam0) = 0;

    virtual CARAPI GetStartInfo(
        /* [out] */ _ELASTOS StringBuf * pParam0,
        /* [out] */ _ELASTOS StringBuf * pParam1) = 0;

    virtual CARAPI GetExitCode(
        /* [out] */ ExitCode * pParam0) = 0;

    virtual CARAPI GetStartTime(
        /* [out] */ _ELASTOS SystemTime * pParam0) = 0;

    virtual CARAPI GetExitTime(
        /* [out] */ _ELASTOS SystemTime * pParam0) = 0;

    virtual CARAPI GetProcessorTimes(
        /* [out] */ _ELASTOS Millisecond32 * pParam0,
        /* [out] */ _ELASTOS Millisecond32 * pParam1) = 0;

    virtual CARAPI GetMemorySizes(
        /* [out] */ _ELASTOS MemorySize * pParam0,
        /* [out] */ _ELASTOS MemorySize * pParam1,
        /* [out] */ _ELASTOS MemorySize * pParam2,
        /* [out] */ _ELASTOS MemorySize * pParam3) = 0;

};

#endif // __INTERFACE_IProcess_DEFINED__
#ifndef __INTERFACE_IObjectEnumerator_DEFINED__
#define __INTERFACE_IObjectEnumerator_DEFINED__

CAR_INTERFACE("A73C2635-51D2-3F63-30FD-243A18000000")
IObjectEnumerator : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IObjectEnumerator*) Probe(PInterface pObj)
    {
        return (IObjectEnumerator*)pObj->Probe(EIID_IObjectEnumerator);
    }

    virtual CARAPI Current(
        /* [out] */ IInterface ** ppParam0) = 0;

    virtual CARAPI MoveNext(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI Reset() = 0;

};

#endif // __INTERFACE_IObjectEnumerator_DEFINED__
#ifndef __INTERFACE_IModule_DEFINED__
#define __INTERFACE_IModule_DEFINED__

CAR_INTERFACE("9BE3A231-CE92-E51F-C210-2957EC2B9172")
IModule : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IModule*) Probe(PInterface pObj)
    {
        return (IModule*)pObj->Probe(EIID_IModule);
    }

    virtual CARAPI GetBaseAddress(
        /* [out] */ _ELASTOS Address * pParam0) = 0;

    virtual CARAPI GetEntryPointAddress(
        /* [out] */ _ELASTOS Address * pParam0) = 0;

    virtual CARAPI GetMemorySize(
        /* [out] */ _ELASTOS MemorySize * pParam0) = 0;

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetFullPath(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetProcAddressByName(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Address * pParam1) = 0;

    virtual CARAPI GetProcAddressByOrdinal(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Address * pParam1) = 0;

    virtual CARAPI GetResourceSection(
        /* [out] */ _ELASTOS Address * pParam0) = 0;

    virtual CARAPI GetSectionByName(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Address * pParam1) = 0;

    virtual CARAPI FindResource(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS String Param1,
        /* [out] */ _ELASTOS Address * pParam2,
        /* [out] */ _ELASTOS MemorySize * pParam3) = 0;

};

#endif // __INTERFACE_IModule_DEFINED__
#ifndef __INTERFACE_IThread_DEFINED__
#define __INTERFACE_IThread_DEFINED__

CAR_INTERFACE("4A7B9039-F092-AA1F-6B23-5E58108866B6")
IThread : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IThread*) Probe(PInterface pObj)
    {
        return (IThread*)pObj->Probe(EIID_IThread);
    }

    virtual CARAPI Start() = 0;

    virtual CARAPI Suspend() = 0;

    virtual CARAPI Resume() = 0;

    virtual CARAPI Join(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI Interrupt() = 0;

    virtual CARAPI Abort() = 0;

    virtual CARAPI SetPriority(
        /* [in] */ ThreadPriority Param0) = 0;

    virtual CARAPI GetPriority(
        /* [out] */ ThreadPriority * pParam0) = 0;

    virtual CARAPI GetId(
        /* [out] */ ThreadId * pParam0) = 0;

    virtual CARAPI SetName(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetState(
        /* [out] */ ThreadState * pParam0) = 0;

    virtual CARAPI GetQuitCode(
        /* [out] */ QuitCode * pParam0) = 0;

    virtual CARAPI GetStartTime(
        /* [out] */ _ELASTOS SystemTime * pParam0) = 0;

    virtual CARAPI GetQuitTime(
        /* [out] */ _ELASTOS SystemTime * pParam0) = 0;

    virtual CARAPI GetProcessorTimes(
        /* [out] */ _ELASTOS Millisecond32 * pParam0,
        /* [out] */ _ELASTOS Millisecond32 * pParam1) = 0;

};

#endif // __INTERFACE_IThread_DEFINED__
#ifndef __INTERFACE_IThreadContext_DEFINED__
#define __INTERFACE_IThreadContext_DEFINED__

CAR_INTERFACE("D266323C-F092-3F45-CA2D-D2BCA89C760E")
IThreadContext : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IThreadContext*) Probe(PInterface pObj)
    {
        return (IThreadContext*)pObj->Probe(EIID_IThreadContext);
    }

    virtual CARAPI GetContext(
        /* [out] */ _ELASTOS ArrayOf<_ELASTOS Int32> * pParam0) = 0;

    virtual CARAPI SetContext(
        /* [in] */ const _ELASTOS ArrayOf<_ELASTOS Int32> & Param0) = 0;

    virtual CARAPI GetUserStackTop(
        /* [out] */ _ELASTOS Address * pParam0) = 0;

};

#endif // __INTERFACE_IThreadContext_DEFINED__
#ifndef __INTERFACE_ISharedMemory_DEFINED__
#define __INTERFACE_ISharedMemory_DEFINED__

CAR_INTERFACE("1BF41A27-66D2-3F99-B6A0-DA2CF3C71654")
ISharedMemory : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ISharedMemory*) Probe(PInterface pObj)
    {
        return (ISharedMemory*)pObj->Probe(EIID_ISharedMemory);
    }

    virtual CARAPI Attach(
        /* [in] */ MemoryProtection Param0,
        /* [out] */ _ELASTOS Address * pParam1) = 0;

    virtual CARAPI Detach() = 0;

};

#endif // __INTERFACE_ISharedMemory_DEFINED__
#ifndef __INTERFACE_IMemoryTrace_DEFINED__
#define __INTERFACE_IMemoryTrace_DEFINED__

CAR_INTERFACE("6E623235-CC92-3FE3-341F-B7A2F978A784")
IMemoryTrace : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IMemoryTrace*) Probe(PInterface pObj)
    {
        return (IMemoryTrace*)pObj->Probe(EIID_IMemoryTrace);
    }

    virtual CARAPI SetTraceArgs(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Address Param2) = 0;

    virtual CARAPI SetTraceDebug(
        /* [in] */ _ELASTOS Boolean Param0) = 0;

    virtual CARAPI IsTraceDebug(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

};

#endif // __INTERFACE_IMemoryTrace_DEFINED__
#ifndef __INTERFACE_IAppletTaskSpecific_DEFINED__
#define __INTERFACE_IAppletTaskSpecific_DEFINED__

CAR_INTERFACE("DA6B440E-3292-2FCF-7A77-A4ED72336AB2")
IAppletTaskSpecific : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletTaskSpecific*) Probe(PInterface pObj)
    {
        return (IAppletTaskSpecific*)pObj->Probe(EIID_IAppletTaskSpecific);
    }

    virtual CARAPI Activate() = 0;

    virtual CARAPI Deactivate() = 0;

    virtual CARAPI IsActivated(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI Snooze() = 0;

    virtual CARAPI Wakeup() = 0;

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_IAppletTaskSpecific_DEFINED__
#ifndef __INTERFACE_IApplet_DEFINED__
#define __INTERFACE_IApplet_DEFINED__

CAR_INTERFACE("AA14EE3B-9312-AA1F-B395-4B295C33DBB8")
IApplet : public IAppletTaskSpecific
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IApplet*) Probe(PInterface pObj)
    {
        return (IApplet*)pObj->Probe(EIID_IApplet);
    }

    virtual CARAPI Start(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS String> & Param0) = 0;

    virtual CARAPI Finish(
        /* [in] */ AppletFinish Param0) = 0;

    virtual CARAPI GetMainThread(
        /* [out] */ IThread ** ppParam0) = 0;

    virtual CARAPI SetPriorityRank(
        /* [in] */ ThreadPriorityRank Param0) = 0;

    virtual CARAPI GetPriorityRank(
        /* [out] */ ThreadPriorityRank * pParam0) = 0;

    virtual CARAPI GetAllThreads(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI GetAllForms(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI GetStartTime(
        /* [out] */ _ELASTOS SystemTime * pParam0) = 0;

    virtual CARAPI Idle() = 0;

    virtual CARAPI WaitUntilFinished(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI GetStatus(
        /* [out] */ AppletStatus * pParam0) = 0;

    virtual CARAPI SetCurrentDirectory(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI GetCurrentDirectory(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetCurrentDirectoryInStorage(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS StringBuf * pParam1) = 0;

    virtual CARAPI SetEnvironmentVariable(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS String Param1) = 0;

    virtual CARAPI GetEnvironmentVariable(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS StringBuf * pParam1) = 0;

};

#endif // __INTERFACE_IApplet_DEFINED__
#ifndef __INTERFACE_JAppletEvents_DEFINED__
#define __INTERFACE_JAppletEvents_DEFINED__

CAR_INTERFACE("81F25E22-9313-3666-7EA8-D69F12D10B14")
JAppletEvents : public IInterface
{

    // callback helper method
    static _ELASTOS ECode AddStartedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddStartedCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddStartedCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddStartedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddStartedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveStartedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveStartedCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveStartedCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveStartedCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireStartedRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireStartedRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddMainCompletedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface, _ELASTOS ECode),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddMainCompletedCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddMainCompletedCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface, _ELASTOS ECode))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddMainCompletedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddMainCompletedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveMainCompletedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface, _ELASTOS ECode),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveMainCompletedCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveMainCompletedCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface, _ELASTOS ECode))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveMainCompletedCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireMainCompletedRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireMainCompletedRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddLayoutReadyCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddLayoutReadyCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddLayoutReadyCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddLayoutReadyCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddLayoutReadyCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveLayoutReadyCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveLayoutReadyCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveLayoutReadyCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveLayoutReadyCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireLayoutReadyRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireLayoutReadyRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddFinishingCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddFinishingCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddFinishingCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddFinishingCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddFinishingCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveFinishingCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveFinishingCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveFinishingCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveFinishingCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireFinishingRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireFinishingRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddActivatedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddActivatedCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddActivatedCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddActivatedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddActivatedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveActivatedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveActivatedCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveActivatedCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveActivatedCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireActivatedRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireActivatedRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddDeactivatedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddDeactivatedCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddDeactivatedCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddDeactivatedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddDeactivatedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveDeactivatedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveDeactivatedCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveDeactivatedCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveDeactivatedCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireDeactivatedRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireDeactivatedRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddSnoozedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddSnoozedCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddSnoozedCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddSnoozedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddSnoozedCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveSnoozedCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveSnoozedCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveSnoozedCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveSnoozedCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireSnoozedRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireSnoozedRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddWakenupCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddWakenupCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddWakenupCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddWakenupCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddWakenupCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveWakenupCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveWakenupCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveWakenupCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveWakenupCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireWakenupRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireWakenupRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

    // callback helper method
    static _ELASTOS ECode AddIdlingCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddIdlingCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddIdlingCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddIdlingCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddIdlingCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveIdlingCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveIdlingCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveIdlingCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveIdlingCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireIdlingRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireIdlingRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

};

#endif // __INTERFACE_JAppletEvents_DEFINED__
#ifndef __INTERFACE_IHostingManager_DEFINED__
#define __INTERFACE_IHostingManager_DEFINED__

CAR_INTERFACE("280A283F-0452-3619-6ED4-67F9A35C5314")
IHostingManager : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IHostingManager*) Probe(PInterface pObj)
    {
        return (IHostingManager*)pObj->Probe(EIID_IHostingManager);
    }

    virtual CARAPI GetOne(
        /* [out] */ IAppletHosting ** ppParam0) = 0;

    virtual CARAPI Register(
        /* [in] */ IAppletHosting * pParam0) = 0;

    virtual CARAPI Unregister(
        /* [in] */ IAppletHosting * pParam0) = 0;

};

#endif // __INTERFACE_IHostingManager_DEFINED__
#ifndef __INTERFACE_IAppletHosting_DEFINED__
#define __INTERFACE_IAppletHosting_DEFINED__

CAR_INTERFACE("885F312E-9312-3208-6CDC-A8FFE3D25105")
IAppletHosting : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletHosting*) Probe(PInterface pObj)
    {
        return (IAppletHosting*)pObj->Probe(EIID_IAppletHosting);
    }

    virtual CARAPI CreateObject(
        /* [in] */ const _ELASTOS ClassID & Param0,
        /* [in] */ const _ELASTOS InterfaceID & Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

    virtual CARAPI AcquireClassObject(
        /* [in] */ const _ELASTOS ClassID & Param0,
        /* [in] */ const _ELASTOS InterfaceID & Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

    virtual CARAPI Lock(
        /* [in] */ _ELASTOS Boolean Param0) = 0;

};

#endif // __INTERFACE_IAppletHosting_DEFINED__
#ifndef __INTERFACE_IMutex_DEFINED__
#define __INTERFACE_IMutex_DEFINED__

CAR_INTERFACE("248A1828-D012-201F-9183-9C0EF40748E4")
IMutex : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IMutex*) Probe(PInterface pObj)
    {
        return (IMutex*)pObj->Probe(EIID_IMutex);
    }

    virtual CARAPI Lock(
        /* [out] */ WaitResult * pParam0) = 0;

    virtual CARAPI TryLock(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI Unlock() = 0;

};

#endif // __INTERFACE_IMutex_DEFINED__
#ifndef __INTERFACE_ICondition_DEFINED__
#define __INTERFACE_ICondition_DEFINED__

CAR_INTERFACE("C579232B-A252-E21F-918B-6FDB76090000")
ICondition : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICondition*) Probe(PInterface pObj)
    {
        return (ICondition*)pObj->Probe(EIID_ICondition);
    }

    virtual CARAPI Wait(
        /* [in] */ IMutex * pParam0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI TryWait(
        /* [in] */ IMutex * pParam0,
        /* [in] */ _ELASTOS Millisecond32 Param1,
        /* [out] */ WaitResult * pParam2) = 0;

    virtual CARAPI Pulse() = 0;

    virtual CARAPI PulseAll() = 0;

};

#endif // __INTERFACE_ICondition_DEFINED__
#ifndef __INTERFACE_IEvent_DEFINED__
#define __INTERFACE_IEvent_DEFINED__

CAR_INTERFACE("EAC61D3B-B352-E21F-918B-37CA07000000")
IEvent : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IEvent*) Probe(PInterface pObj)
    {
        return (IEvent*)pObj->Probe(EIID_IEvent);
    }

    virtual CARAPI Wait(
        /* [out] */ WaitResult * pParam0) = 0;

    virtual CARAPI TryWait(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI Notify() = 0;

    virtual CARAPI Clear() = 0;

};

#endif // __INTERFACE_IEvent_DEFINED__
#ifndef __INTERFACE_IReaderWriterLock_DEFINED__
#define __INTERFACE_IReaderWriterLock_DEFINED__

CAR_INTERFACE("4071AC21-5C92-20F3-7FC8-0529173948B9")
IReaderWriterLock : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IReaderWriterLock*) Probe(PInterface pObj)
    {
        return (IReaderWriterLock*)pObj->Probe(EIID_IReaderWriterLock);
    }

    virtual CARAPI ReaderLock(
        /* [out] */ WaitResult * pParam0) = 0;

    virtual CARAPI ReaderTryLock(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI ReaderUnlock() = 0;

    virtual CARAPI UpgradeToWriter(
        /* [out] */ WaitResult * pParam0) = 0;

    virtual CARAPI TryUpgradeToWriter(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI WriterLock(
        /* [out] */ WaitResult * pParam0) = 0;

    virtual CARAPI WriterTryLock(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI WriterUnlock() = 0;

    virtual CARAPI DowngradeFromWriter() = 0;

    virtual CARAPI IsReaderLockHeld(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI IsWriterLockHeld(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

};

#endif // __INTERFACE_IReaderWriterLock_DEFINED__
#ifndef __INTERFACE_IDeviceDriver_DEFINED__
#define __INTERFACE_IDeviceDriver_DEFINED__

CAR_INTERFACE("5DFA1E48-91D2-A0DF-9A6C-ACF1E30C1E22")
IDeviceDriver : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDeviceDriver*) Probe(PInterface pObj)
    {
        return (IDeviceDriver*)pObj->Probe(EIID_IDeviceDriver);
    }

    virtual CARAPI Read(
        /* [in] */ _ELASTOS Int64 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2,
        /* [out] */ IEvent ** ppParam3) = 0;

    virtual CARAPI Write(
        /* [in] */ _ELASTOS Int64 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ IEvent ** ppParam3) = 0;

    virtual CARAPI Control(
        /* [in] */ _ELASTOS Handle32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2,
        /* [out] */ IEvent ** ppParam3) = 0;

};

#endif // __INTERFACE_IDeviceDriver_DEFINED__
#ifndef __INTERFACE_IObjectEx_DEFINED__
#define __INTERFACE_IObjectEx_DEFINED__

CAR_INTERFACE("8A712D2A-51D2-3F68-94D9-28970E50393D")
IObjectEx : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IObjectEx*) Probe(PInterface pObj)
    {
        return (IObjectEx*)pObj->Probe(EIID_IObjectEx);
    }

    virtual CARAPI Equals(
        /* [in] */ IInterface * pParam0) = 0;

    virtual CARAPI GetHashCode(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetClassID(
        /* [out] */ _ELASTOS ClassID * pParam0) = 0;

    virtual CARAPI ToString(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_IObjectEx_DEFINED__
#ifndef __INTERFACE_IObjectContainer_DEFINED__
#define __INTERFACE_IObjectContainer_DEFINED__

CAR_INTERFACE("38D44229-51D2-3F48-8CF4-2D77D458B9A3")
IObjectContainer : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IObjectContainer*) Probe(PInterface pObj)
    {
        return (IObjectContainer*)pObj->Probe(EIID_IObjectContainer);
    }

    virtual CARAPI Add(
        /* [in] */ IInterface * pParam0) = 0;

    virtual CARAPI Remove(
        /* [in] */ IInterface * pParam0) = 0;

    virtual CARAPI GetObjectEnumerator(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI GetObjectCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI Dispose() = 0;

};

#endif // __INTERFACE_IObjectContainer_DEFINED__
#ifndef __INTERFACE_ICallbackParcel_DEFINED__
#define __INTERFACE_ICallbackParcel_DEFINED__

CAR_INTERFACE("D6EAF125-9C52-240C-6A98-40F1E2C7F936")
ICallbackParcel : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICallbackParcel*) Probe(PInterface pObj)
    {
        return (ICallbackParcel*)pObj->Probe(EIID_ICallbackParcel);
    }

    virtual CARAPI WriteByte(
        /* [in] */ _ELASTOS Byte Param0) = 0;

    virtual CARAPI WriteBoolean(
        /* [in] */ _ELASTOS Boolean Param0) = 0;

    virtual CARAPI WriteChar8(
        /* [in] */ _ELASTOS Char8 Param0) = 0;

    virtual CARAPI WriteChar16(
        /* [in] */ _ELASTOS Char16 Param0) = 0;

    virtual CARAPI WriteInt16(
        /* [in] */ _ELASTOS Int16 Param0) = 0;

    virtual CARAPI WriteInt32(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI WriteInt64(
        /* [in] */ _ELASTOS Int64 Param0) = 0;

    virtual CARAPI WriteFloat(
        /* [in] */ _ELASTOS Float Param0) = 0;

    virtual CARAPI WriteDouble(
        /* [in] */ _ELASTOS Double Param0) = 0;

    virtual CARAPI WriteString(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI WriteStruct(
        /* [in] */ _ELASTOS Handle32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI WriteEMuid(
        /* [in] */ const _ELASTOS EMuid & Param0) = 0;

    virtual CARAPI WriteEGuid(
        /* [in] */ const _ELASTOS EGuid & Param0) = 0;

    virtual CARAPI WriteArrayOf(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteArrayOfString(
        /* [in] */ const _ELASTOS ArrayOf<_ELASTOS String> & Param0) = 0;

    virtual CARAPI WriteBufferOf(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteBufferOfString(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS String> & Param0) = 0;

    virtual CARAPI WriteStringBuf(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteMemoryBuf(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteInterfacePtr(
        /* [in] */ IInterface * pParam0) = 0;

    virtual CARAPI WriteBytePtr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteBooleanPtr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteChar8Ptr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteChar16Ptr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteInt16Ptr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteInt32Ptr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteInt64Ptr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteFloatPtr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteDoublePtr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI WriteInterfacePtrPtr(
        /* [in] */ _ELASTOS Handle32 Param0) = 0;

    virtual CARAPI Clone(
        /* [in] */ ICallbackParcel * pParam0) = 0;

    virtual CARAPI GetElementPayload(
        /* [out] */ _ELASTOS Handle32 * pParam0) = 0;

    virtual CARAPI GetElementSize(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

};

#endif // __INTERFACE_ICallbackParcel_DEFINED__
#ifndef __INTERFACE_ICallbackRendezvous_DEFINED__
#define __INTERFACE_ICallbackRendezvous_DEFINED__

CAR_INTERFACE("73341821-9C52-280D-629C-40D123870C1C")
ICallbackRendezvous : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICallbackRendezvous*) Probe(PInterface pObj)
    {
        return (ICallbackRendezvous*)pObj->Probe(EIID_ICallbackRendezvous);
    }

    virtual CARAPI Wait(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

};

#endif // __INTERFACE_ICallbackRendezvous_DEFINED__
#ifndef __INTERFACE_ICallbackSink_DEFINED__
#define __INTERFACE_ICallbackSink_DEFINED__

CAR_INTERFACE("7BD88031-1C52-3FD0-8CC4-E91B4781091A")
ICallbackSink : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICallbackSink*) Probe(PInterface pObj)
    {
        return (ICallbackSink*)pObj->Probe(EIID_ICallbackSink);
    }

    virtual CARAPI AddCallback(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EventHandler Param1) = 0;

    virtual CARAPI RemoveCallback(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EventHandler Param1) = 0;

    virtual CARAPI AcquireCallbackRendezvous(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ ICallbackRendezvous ** ppParam1) = 0;

    virtual CARAPI RemoveAllCallbacks() = 0;

    virtual CARAPI CancelPendingCallback(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI CancelAllPendingCallbacks() = 0;

};

#endif // __INTERFACE_ICallbackSink_DEFINED__
#ifndef __INTERFACE_IContext_DEFINED__
#define __INTERFACE_IContext_DEFINED__

CAR_INTERFACE("64E92B21-A2D2-471F-871D-A578E9280000")
IContext : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IContext*) Probe(PInterface pObj)
    {
        return (IContext*)pObj->Probe(EIID_IContext);
    }

    virtual CARAPI ObjectEnter(
        /* [in] */ PInterface pParam0) = 0;

    virtual CARAPI ObjectLeave(
        /* [in] */ PInterface pParam0) = 0;

    virtual CARAPI CreateObject(
        /* [in] */ const _ELASTOS ClassID & Param0,
        /* [in] */ const _ELASTOS InterfaceID & Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_IContext_DEFINED__
#ifndef __INTERFACE_IAObjectContainerClassObject_DEFINED__
#define __INTERFACE_IAObjectContainerClassObject_DEFINED__

CAR_INTERFACE("AA3E5D24-8292-90A3-F41C-FD71E9280816")
IAObjectContainerClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAObjectContainerClassObject*) Probe(PInterface pObj)
    {
        return (IAObjectContainerClassObject*)pObj->Probe(EIID_IAObjectContainerClassObject);
    }

    virtual CARAPI CreateObjectWithDefaultCtor(
        /* [out] */ IInterface ** ppParam0) = 0;

};

#endif // __INTERFACE_IAObjectContainerClassObject_DEFINED__
#ifndef __INTERFACE_IKernel_DEFINED__
#define __INTERFACE_IKernel_DEFINED__

CAR_INTERFACE("DE97FC2F-C312-E51F-7617-D7BCBB78B9F6")
IKernel : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IKernel*) Probe(PInterface pObj)
    {
        return (IKernel*)pObj->Probe(EIID_IKernel);
    }

    virtual CARAPI GetSystemTime(
        /* [out] */ _ELASTOS SystemTime * pParam0) = 0;

    virtual CARAPI SetSystemTime(
        /* [in] */ _ELASTOS SystemTime Param0) = 0;

    virtual CARAPI GetElapsedTime(
        /* [out] */ _ELASTOS Millisecond32 * pParam0) = 0;

    virtual CARAPI GetIdleTime(
        /* [out] */ _ELASTOS Millisecond32 * pParam0) = 0;

    virtual CARAPI CreateProcess(
        /* [out] */ IProcess ** ppParam0) = 0;

    virtual CARAPI GetCurrentProcess(
        /* [out] */ IProcess ** ppParam0) = 0;

    virtual CARAPI GetAllProcesses(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI ExitProcess(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI CreateThread(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS Address Param1,
        /* [in] */ _ELASTOS Address Param2,
        /* [in] */ _ELASTOS ThreadCreationFlags Param3,
        /* [out] */ IThread ** ppParam4) = 0;

    virtual CARAPI GetCurrentThread(
        /* [out] */ IThread ** ppParam0) = 0;

    virtual CARAPI LoadModule(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS ModuleLoadFlags Param1,
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Address> * pParam2,
        /* [out] */ IModule ** ppParam3,
        /* [out] */ _ELASTOS Boolean * pParam4) = 0;

    virtual CARAPI Sleep(
        /* [in] */ _ELASTOS Millisecond32 Param0,
        /* [out] */ WaitResult * pParam1) = 0;

    virtual CARAPI GetDelayFactor(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI Yield() = 0;

    virtual CARAPI VirtualMemoryMap(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS MemorySize Param1,
        /* [in] */ _ELASTOS MemoryMapFlags Param2,
        /* [in] */ MemoryProtection Param3,
        /* [out] */ _ELASTOS Address * pParam4) = 0;

    virtual CARAPI MemoryQuery(
        /* [in] */ _ELASTOS Address Param0,
        /* [out] */ _ELASTOS Address * pParam1,
        /* [out] */ _ELASTOS MemorySize * pParam2) = 0;

    virtual CARAPI MemoryQueryPhysicalBlock(
        /* [in] */ _ELASTOS Address Param0,
        /* [out] */ _ELASTOS Address * pParam1,
        /* [out] */ _ELASTOS MemorySize * pParam2) = 0;

    virtual CARAPI MemoryProtect(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS MemorySize Param1,
        /* [in] */ MemoryProtection Param2) = 0;

    virtual CARAPI MemoryCheck(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ MemoryProtection Param1,
        /* [out] */ _ELASTOS Boolean * pParam2) = 0;

    virtual CARAPI MemoryCommit(
        /* [in] */ _ELASTOS Address Param0) = 0;

    virtual CARAPI IoRemap(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS MemorySize Param1,
        /* [in] */ _ELASTOS Address Param2,
        /* [in] */ _ELASTOS MemoryMapFlags Param3,
        /* [in] */ MemoryProtection Param4,
        /* [out] */ _ELASTOS Address * pParam5) = 0;

    virtual CARAPI MemoryUnmap(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS MemorySize Param1) = 0;

    virtual CARAPI CreateMutex(
        /* [out] */ IMutex ** ppParam0) = 0;

    virtual CARAPI CreateNamedMutex(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IMutex ** ppParam1,
        /* [out] */ _ELASTOS Boolean * pParam2) = 0;

    virtual CARAPI CreateCondition(
        /* [out] */ ICondition ** ppParam0) = 0;

    virtual CARAPI CreateNamedCondition(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ ICondition ** ppParam1,
        /* [out] */ _ELASTOS Boolean * pParam2) = 0;

    virtual CARAPI CreateEvent(
        /* [in] */ _ELASTOS Boolean Param0,
        /* [in] */ _ELASTOS EventState Param1,
        /* [out] */ IEvent ** ppParam2) = 0;

    virtual CARAPI CreateNamedEvent(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Boolean Param1,
        /* [in] */ _ELASTOS EventState Param2,
        /* [out] */ IEvent ** ppParam3,
        /* [out] */ _ELASTOS Boolean * pParam4) = 0;

    virtual CARAPI CreateReaderWriterLock(
        /* [out] */ IReaderWriterLock ** ppParam0) = 0;

    virtual CARAPI CreateNamedReaderWriterLock(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IReaderWriterLock ** ppParam1,
        /* [out] */ _ELASTOS Boolean * pParam2) = 0;

    virtual CARAPI CreateSharedMemory(
        /* [in] */ _ELASTOS MemorySize Param0,
        /* [in] */ _ELASTOS Boolean Param1,
        /* [out] */ ISharedMemory ** ppParam2) = 0;

    virtual CARAPI CreateNamedSharedMemory(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS MemorySize Param1,
        /* [in] */ _ELASTOS Boolean Param2,
        /* [out] */ ISharedMemory ** ppParam3,
        /* [out] */ _ELASTOS Boolean * pParam4) = 0;

    virtual CARAPI RequestSystemEvent(
        /* [in] */ _ELASTOS SystemEvents Param0,
        /* [out] */ IEvent ** ppParam1) = 0;

    virtual CARAPI GetHostingManager(
        /* [out] */ IHostingManager ** ppParam0) = 0;

    virtual CARAPI GetEnvironmentMutex(
        /* [out] */ IMutex ** ppParam0) = 0;

    virtual CARAPI AcquireThreadLocalSlot(
        /* [in] */ ThreadLocalSlotType Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI RelinquishThreadLocalSlot(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Address> * pParam1) = 0;

    virtual CARAPI CleanUpThreadLocalSlot(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Address> * pParam1) = 0;

    virtual CARAPI WaitForAnyEvents(
        /* [in] */ const _ELASTOS BufferOf<IEvent *> & Param0,
        /* [out] */ WaitResult * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS EventState * pParam3) = 0;

    virtual CARAPI TryWaitForAnyEvents(
        /* [in] */ const _ELASTOS BufferOf<IEvent *> & Param0,
        /* [in] */ _ELASTOS Millisecond32 Param1,
        /* [out] */ WaitResult * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3,
        /* [out] */ _ELASTOS EventState * pParam4) = 0;

    virtual CARAPI GetGlobalMemorySizes(
        /* [out] */ _ELASTOS MemorySize * pParam0,
        /* [out] */ _ELASTOS MemorySize * pParam1) = 0;

    virtual CARAPI FlushInstructionCache(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS MemorySize Param1) = 0;

};

#endif // __INTERFACE_IKernel_DEFINED__
#ifndef __INTERFACE_IStringEnumerator_DEFINED__
#define __INTERFACE_IStringEnumerator_DEFINED__

CAR_INTERFACE("9033262D-6C12-3F63-30FD-243A18000000")
IStringEnumerator : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStringEnumerator*) Probe(PInterface pObj)
    {
        return (IStringEnumerator*)pObj->Probe(EIID_IStringEnumerator);
    }

    virtual CARAPI Current(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI MoveNext(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI Reset() = 0;

};

#endif // __INTERFACE_IStringEnumerator_DEFINED__
#ifndef __INTERFACE_IBasicFileSystem_DEFINED__
#define __INTERFACE_IBasicFileSystem_DEFINED__

CAR_INTERFACE("82772923-9892-BB6A-7FE4-2EF7586439D6")
IBasicFileSystem : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IBasicFileSystem*) Probe(PInterface pObj)
    {
        return (IBasicFileSystem*)pObj->Probe(EIID_IBasicFileSystem);
    }

    virtual CARAPI Sync() = 0;

    virtual CARAPI GetRoot(
        /* [out] */ IBasicDirectory ** ppParam0) = 0;

    virtual CARAPI Lookup(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IBasicFile ** ppParam1) = 0;

    virtual CARAPI GetStat(
        /* [out] */ struct FileSystemStat * pParam0) = 0;

};

#endif // __INTERFACE_IBasicFileSystem_DEFINED__
#ifndef __INTERFACE_IBasicFile_DEFINED__
#define __INTERFACE_IBasicFile_DEFINED__

CAR_INTERFACE("F77DA422-9892-3F6A-7297-5B5E6E4871CD")
IBasicFile : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IBasicFile*) Probe(PInterface pObj)
    {
        return (IBasicFile*)pObj->Probe(EIID_IBasicFile);
    }

    virtual CARAPI Sync() = 0;

    virtual CARAPI GetType(
        /* [out] */ FileType * pParam0) = 0;

    virtual CARAPI GetAccessTime(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI SetAccessTime(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetModificationTime(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI SetModificationTime(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetCreateTime(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI CheckAccessMode(
        /* [in] */ FileAccessMode Param0) = 0;

    virtual CARAPI GetAccessMode(
        /* [out] */ FileAccessMode * pParam0) = 0;

    virtual CARAPI SetAccessMode(
        /* [in] */ FileAccessMode Param0) = 0;

    virtual CARAPI GetShareMode(
        /* [out] */ FileShareMode * pParam0) = 0;

    virtual CARAPI SetShareMode(
        /* [in] */ FileShareMode Param0) = 0;

};

#endif // __INTERFACE_IBasicFile_DEFINED__
#ifndef __INTERFACE_IBasicDirectory_DEFINED__
#define __INTERFACE_IBasicDirectory_DEFINED__

CAR_INTERFACE("237CFF37-1892-3F59-445E-AAA6AADADF4B")
IBasicDirectory : public IBasicFile
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IBasicDirectory*) Probe(PInterface pObj)
    {
        return (IBasicDirectory*)pObj->Probe(EIID_IBasicDirectory);
    }

    virtual CARAPI Lookup(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IBasicFile ** ppParam1) = 0;

    virtual CARAPI CreateFile(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ FileAccessMode Param1,
        /* [in] */ _ELASTOS Boolean Param2,
        /* [out] */ IBasicFile ** ppParam3) = 0;

    virtual CARAPI DeleteFile(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI Rename(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ IBasicDirectory * pParam1,
        /* [in] */ _ELASTOS String Param2) = 0;

    virtual CARAPI CreateDirectory(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ FileAccessMode Param1) = 0;

    virtual CARAPI DeleteDirectory(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI GetDirEntries(
        /* [out] */ IStringEnumerator ** ppParam0) = 0;

};

#endif // __INTERFACE_IBasicDirectory_DEFINED__
#ifndef __INTERFACE_IAbsoluteIO_DEFINED__
#define __INTERFACE_IAbsoluteIO_DEFINED__

CAR_INTERFACE("A0763626-9052-3F77-E89E-2F175A73E872")
IAbsoluteIO : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAbsoluteIO*) Probe(PInterface pObj)
    {
        return (IAbsoluteIO*)pObj->Probe(EIID_IAbsoluteIO);
    }

    virtual CARAPI Read(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2) = 0;

    virtual CARAPI Write(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1,
        /* [out] */ _ELASTOS Int32 * pParam2) = 0;

    virtual CARAPI GetSize(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI SetSize(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetOptimalBlockSize(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

};

#endif // __INTERFACE_IAbsoluteIO_DEFINED__
#ifndef __INTERFACE_IFileMonitor_DEFINED__
#define __INTERFACE_IFileMonitor_DEFINED__

CAR_INTERFACE("62652C35-B552-3F9E-8C54-EBD9B75A4F00")
IFileMonitor : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IFileMonitor*) Probe(PInterface pObj)
    {
        return (IFileMonitor*)pObj->Probe(EIID_IFileMonitor);
    }

    virtual CARAPI AddFileMonitor(
        /* [out] */ IEvent ** ppParam0) = 0;

    virtual CARAPI RemoveFileMonitor(
        /* [in] */ IEvent * pParam0) = 0;

};

#endif // __INTERFACE_IFileMonitor_DEFINED__
#ifndef __INTERFACE_IDiskFileSystem_DEFINED__
#define __INTERFACE_IDiskFileSystem_DEFINED__

CAR_INTERFACE("79BA2634-AC12-BB6A-7F98-695083458EFB")
IDiskFileSystem : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDiskFileSystem*) Probe(PInterface pObj)
    {
        return (IDiskFileSystem*)pObj->Probe(EIID_IDiskFileSystem);
    }

    virtual CARAPI BindDriver(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI UnbindDriver() = 0;

};

#endif // __INTERFACE_IDiskFileSystem_DEFINED__
#ifndef __INTERFACE_IDiskManager_DEFINED__
#define __INTERFACE_IDiskManager_DEFINED__

CAR_INTERFACE("BD5B7B34-2C12-3F96-8CC0-6205CB29AC3F")
IDiskManager : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDiskManager*) Probe(PInterface pObj)
    {
        return (IDiskManager*)pObj->Probe(EIID_IDiskManager);
    }

    virtual CARAPI AddDisk(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS String Param1,
        /* [in] */ _ELASTOS String Param2,
        /* [in] */ DiskType Param3) = 0;

    virtual CARAPI DelDisk(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI OpenDisk(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS StringBuf * pParam1) = 0;

    virtual CARAPI CloseDisk(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetDisks(
        /* [in] */ DiskType Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetPartitionFreeSpace(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Int64 * pParam1,
        /* [out] */ _ELASTOS Int64 * pParam2) = 0;

    virtual CARAPI AcquireDirInterface(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IBasicDirectory ** ppParam1,
        /* [out] */ _ELASTOS StringBuf * pParam2) = 0;

    virtual CARAPI AddFileMonitor(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IEvent ** ppParam1) = 0;

    virtual CARAPI RemoveFileMonitor(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ IEvent * pParam1) = 0;

};

#endif // __INTERFACE_IDiskManager_DEFINED__
#ifndef __INTERFACE_ILocaleInfo_DEFINED__
#define __INTERFACE_ILocaleInfo_DEFINED__

CAR_INTERFACE("0BF85339-4792-3F7E-CA15-67CF4F7371F6")
ILocaleInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ILocaleInfo*) Probe(PInterface pObj)
    {
        return (ILocaleInfo*)pObj->Probe(EIID_ILocaleInfo);
    }

    virtual CARAPI GetTimeZoneInfo(
        /* [out] */ struct TimeZoneInfo * pParam0) = 0;

    virtual CARAPI SetTimeZoneInfo(
        /* [in] */ const struct TimeZoneInfo & Param0) = 0;

    virtual CARAPI GetTimeZoneBias(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI SetLocaleInfo(
        /* [in] */ LocaleType Param0,
        /* [in] */ _ELASTOS String Param1) = 0;

    virtual CARAPI GetLocaleInfo(
        /* [in] */ LocaleType Param0,
        /* [out] */ _ELASTOS StringBuf * pParam1) = 0;

};

#endif // __INTERFACE_ILocaleInfo_DEFINED__
#ifndef __INTERFACE_IDeviceEventManager_DEFINED__
#define __INTERFACE_IDeviceEventManager_DEFINED__

CAR_INTERFACE("D95E2636-0352-3914-5898-40D18CE58FCB")
IDeviceEventManager : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDeviceEventManager*) Probe(PInterface pObj)
    {
        return (IDeviceEventManager*)pObj->Probe(EIID_IDeviceEventManager);
    }

    virtual CARAPI SendEvent(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1) = 0;

    virtual CARAPI PostEvent(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1) = 0;

};

#endif // __INTERFACE_IDeviceEventManager_DEFINED__
#ifndef __INTERFACE_IDeviceEventHandler_DEFINED__
#define __INTERFACE_IDeviceEventHandler_DEFINED__

CAR_INTERFACE("C6A53524-0352-3914-5898-40D10CDD0F23")
IDeviceEventHandler : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDeviceEventHandler*) Probe(PInterface pObj)
    {
        return (IDeviceEventHandler*)pObj->Probe(EIID_IDeviceEventHandler);
    }

    virtual CARAPI AddEventHandler(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ IDeviceEventDispatcher * pParam1) = 0;

    virtual CARAPI RemoveEventHandler(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ IDeviceEventDispatcher * pParam1) = 0;

};

#endif // __INTERFACE_IDeviceEventHandler_DEFINED__
#ifndef __INTERFACE_IDeviceEventDispatcher_DEFINED__
#define __INTERFACE_IDeviceEventDispatcher_DEFINED__

CAR_INTERFACE("E21E384D-91D2-A0DF-1CF8-8E710309D81B")
IDeviceEventDispatcher : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDeviceEventDispatcher*) Probe(PInterface pObj)
    {
        return (IDeviceEventDispatcher*)pObj->Probe(EIID_IDeviceEventDispatcher);
    }

    virtual CARAPI InvokeEventHandler(
        /* [in] */ const _ELASTOS MemoryBuf & Param0) = 0;

    virtual CARAPI SetEventHandler(
        /* [in] */ _ELASTOS Address Param0,
        /* [in] */ _ELASTOS Address Param1) = 0;

};

#endif // __INTERFACE_IDeviceEventDispatcher_DEFINED__
#ifndef __INTERFACE_IGrafixEngine_DEFINED__
#define __INTERFACE_IGrafixEngine_DEFINED__

CAR_INTERFACE("2E7CBE56-8412-DCBB-A0C0-3BFA438109BA")
IGrafixEngine : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGrafixEngine*) Probe(PInterface pObj)
    {
        return (IGrafixEngine*)pObj->Probe(EIID_IGrafixEngine);
    }

    virtual CARAPI AcquireGrafixLayer(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IGrafixLayer ** ppParam1) = 0;

    virtual CARAPI CreateGrafixObject(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ const struct GrafixObjectParams & Param1,
        /* [out] */ IGrafixObject ** ppParam2) = 0;

    virtual CARAPI CreateGrafixSurface(
        /* [in] */ const struct GrafixSurfaceParams & Param0,
        /* [out] */ IGrafixSurface ** ppParam1) = 0;

    virtual CARAPI BroadcastGrafixEvent(
        /* [in] */ const struct GrafixObjectEvent & Param0) = 0;

    virtual CARAPI GetAllGrafixObjects(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IObjectEnumerator ** ppParam1) = 0;

    virtual CARAPI AcquireGrafixEventBuffer(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IGrafixEventBuffer ** ppParam1) = 0;

    virtual CARAPI Render() = 0;

    virtual CARAPI RenderRegion(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3) = 0;

    virtual CARAPI SetScreenOrientation(
        /* [in] */ ScreenOrientation Param0) = 0;

    virtual CARAPI GetScreenOrientation(
        /* [out] */ ScreenOrientation * pParam0) = 0;

};

#endif // __INTERFACE_IGrafixEngine_DEFINED__
#ifndef __INTERFACE_IGrafixLayer_DEFINED__
#define __INTERFACE_IGrafixLayer_DEFINED__

CAR_INTERFACE("57783158-8412-DCBB-2A44-7AF6038A1E24")
IGrafixLayer : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGrafixLayer*) Probe(PInterface pObj)
    {
        return (IGrafixLayer*)pObj->Probe(EIID_IGrafixLayer);
    }

    virtual CARAPI Enable(
        /* [in] */ const struct GrafixLayerFormat & Param0) = 0;

    virtual CARAPI Disable() = 0;

    virtual CARAPI SetOpacity(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetAttributes(
        /* [out] */ struct GrafixLayerFormat * pParam0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

};

#endif // __INTERFACE_IGrafixLayer_DEFINED__
#ifndef __INTERFACE_IGrafixObject_DEFINED__
#define __INTERFACE_IGrafixObject_DEFINED__

CAR_INTERFACE("674AFE55-8412-DCBB-BEFC-A862A54A878C")
IGrafixObject : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGrafixObject*) Probe(PInterface pObj)
    {
        return (IGrafixObject*)pObj->Probe(EIID_IGrafixObject);
    }

    virtual CARAPI GetId(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetTitle(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI Attach(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Detach() = 0;

    virtual CARAPI AddEvent(
        /* [in] */ const struct GrafixObjectEvent & Param0) = 0;

    virtual CARAPI AddNotifyEvent(
        /* [in] */ const struct GrafixObjectEvent & Param0) = 0;

    virtual CARAPI RollbackEvent(
        /* [in] */ const struct GrafixObjectEvent & Param0) = 0;

    virtual CARAPI SetUserDefinedHandles(
        /* [in] */ _ELASTOS Handle32 Param0,
        /* [in] */ _ELASTOS Handle32 Param1) = 0;

    virtual CARAPI GetUserDefinedHandles(
        /* [out] */ _ELASTOS Handle32 * pParam0,
        /* [out] */ _ELASTOS Handle32 * pParam1) = 0;

    virtual CARAPI SetOwner(
        /* [in] */ IGrafixObject * pParam0) = 0;

    virtual CARAPI GetOwner(
        /* [out] */ IGrafixObject ** ppParam0) = 0;

    virtual CARAPI GetGrafixSurface(
        /* [out] */ IGrafixSurface ** ppParam0) = 0;

    virtual CARAPI SetOpacity(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetOpacity(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI EnableGrafixLayerTransparent() = 0;

    virtual CARAPI DisableGrafixLayerTransparent() = 0;

    virtual CARAPI AddGrafixLayerTransparentRect(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3) = 0;

    virtual CARAPI RemoveGrafixLayerTransparentRect(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3) = 0;

    virtual CARAPI RemoveAllGrafixLayerTransparentRects() = 0;

    virtual CARAPI GrabKey(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ InputMask Param1) = 0;

    virtual CARAPI UngrabKey(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ InputMask Param1) = 0;

    virtual CARAPI GrabPointer() = 0;

    virtual CARAPI UngrabPointer() = 0;

    virtual CARAPI SetPriority(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI GetPriority(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI Move(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI MoveTo(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI Resize(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI RaiseToTop() = 0;

    virtual CARAPI LowerToBottom() = 0;

    virtual CARAPI RequestFocus() = 0;

    virtual CARAPI SetTimer(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI KillTimer(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI Close() = 0;

    virtual CARAPI SetProperty(
        /* [in] */ GrafixObjectProperty Param0) = 0;

    virtual CARAPI GetProperty(
        /* [out] */ GrafixObjectProperty * pParam0) = 0;

    virtual CARAPI SetVisible(
        /* [in] */ _ELASTOS Boolean Param0) = 0;

    virtual CARAPI IsVisible(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI SetInputEnabled(
        /* [in] */ _ELASTOS Boolean Param0) = 0;

    virtual CARAPI IsInputEnabled(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetBounds(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI SetBounds(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ GrafixBound Param4) = 0;

    virtual CARAPI SetActiveArea(
        /* [in] */ const struct Rectangle & Param0) = 0;

    virtual CARAPI InterceptKey(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ InputMask Param1) = 0;

    virtual CARAPI UninterceptKey(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ InputMask Param1) = 0;

    virtual CARAPI SetLeadingTransition(
        /* [in] */ TransitionEffect Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ _ELASTOS Millisecond32 Param4) = 0;

    virtual CARAPI SetTrailingTransition(
        /* [in] */ TransitionEffect Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ _ELASTOS Millisecond32 Param4) = 0;

    virtual CARAPI GetLeadingTransition(
        /* [out] */ TransitionEffect * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3,
        /* [out] */ _ELASTOS Millisecond32 * pParam4) = 0;

    virtual CARAPI GetTrailingTransition(
        /* [out] */ TransitionEffect * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3,
        /* [out] */ _ELASTOS Millisecond32 * pParam4) = 0;

    virtual CARAPI __Impl_SetObject(
        /* [in] */ IInterface * pParam0) = 0;

    virtual CARAPI __Impl_GetObject(
        /* [out] */ IInterface ** ppParam0) = 0;

};

#endif // __INTERFACE_IGrafixObject_DEFINED__
#ifndef __INTERFACE_IGrafixSurface_DEFINED__
#define __INTERFACE_IGrafixSurface_DEFINED__

CAR_INTERFACE("D273EB4A-8412-DCBB-38F0-BEF6A3CA021C")
IGrafixSurface : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGrafixSurface*) Probe(PInterface pObj)
    {
        return (IGrafixSurface*)pObj->Probe(EIID_IGrafixSurface);
    }

    virtual CARAPI GetBufferInformation(
        /* [out] */ struct BitmapBufInfo * pParam0) = 0;

    virtual CARAPI EndBufferOperation() = 0;

    virtual CARAPI GetPixelFormat(
        /* [out] */ PixelFormat * pParam0) = 0;

    virtual CARAPI GetAttribute(
        /* [out] */ GrafixAttribute * pParam0) = 0;

    virtual CARAPI SetOffset(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetBounds(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ GrafixBound Param4) = 0;

    virtual CARAPI GetBounds(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI SetClip(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3) = 0;

    virtual CARAPI GetClip(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI GetVisibleRegion(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI Blit(
        /* [in] */ IGrafixSurface * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ _ELASTOS Int32 Param4,
        /* [in] */ _ELASTOS Int32 Param5,
        /* [in] */ _ELASTOS Int32 Param6) = 0;

    virtual CARAPI BlitFromA8(
        /* [in] */ IGrafixSurface * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ _ELASTOS Int32 Param4,
        /* [in] */ _ELASTOS Int32 Param5,
        /* [in] */ _ELASTOS Int32 Param6,
// mayq, replace
//        /* [in] */ Color Param7) = 0;
		/* [in] */ Elastos::Int32 Param7) = 0;

    virtual CARAPI StretchBlit(
        /* [in] */ IGrafixSurface * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ _ELASTOS Int32 Param4,
        /* [in] */ _ELASTOS Int32 Param5,
        /* [in] */ _ELASTOS Int32 Param6,
        /* [in] */ _ELASTOS Int32 Param7,
        /* [in] */ _ELASTOS Int32 Param8) = 0;

    virtual CARAPI Flip(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3) = 0;

    virtual CARAPI GetSubGrafixSurface(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [out] */ IGrafixSurface ** ppParam4) = 0;

    virtual CARAPI InvalidateRectangle(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3) = 0;

    virtual CARAPI UpdateInvalidatedRectangles() = 0;

    virtual CARAPI Clear(
// mayq, replace
//    	/* [in] */ Color Param0) = 0;
    	/* [in] */ Elastos::Int32 Param0) = 0;


    virtual CARAPI __Impl_GetBufferInformation(
        /* [out] */ struct BitmapBufInfo * pParam0) = 0;

    virtual CARAPI __Impl_ReGetBufferInformation(
        /* [out] */ struct BitmapBufInfo * pParam0) = 0;

    virtual CARAPI __Impl_EndBufferOperation() = 0;

};

#endif // __INTERFACE_IGrafixSurface_DEFINED__
#ifndef __INTERFACE_IGrafixEventBuffer_DEFINED__
#define __INTERFACE_IGrafixEventBuffer_DEFINED__

CAR_INTERFACE("6C321B26-8412-241A-52B0-D8D14CCD8F72")
IGrafixEventBuffer : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGrafixEventBuffer*) Probe(PInterface pObj)
    {
        return (IGrafixEventBuffer*)pObj->Probe(EIID_IGrafixEventBuffer);
    }

    virtual CARAPI GetEvent(
        /* [out] */ struct GrafixObjectEvent * pParam0) = 0;

};

#endif // __INTERFACE_IGrafixEventBuffer_DEFINED__
#ifndef __INTERFACE_IAppletSession_DEFINED__
#define __INTERFACE_IAppletSession_DEFINED__

CAR_INTERFACE("19613132-1312-F80E-E3FF-A07BFE8FF8C2")
IAppletSession : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletSession*) Probe(PInterface pObj)
    {
        return (IAppletSession*)pObj->Probe(EIID_IAppletSession);
    }

    virtual CARAPI Read(
        /* [out] */ _ELASTOS MemoryBuf * pParam0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

    virtual CARAPI Write(
        /* [in] */ const _ELASTOS MemoryBuf & Param0) = 0;

    virtual CARAPI Close() = 0;

    virtual CARAPI WaitResponse(
        /* [out] */ WaitResult * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2) = 0;

    virtual CARAPI Response(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1) = 0;

};

#endif // __INTERFACE_IAppletSession_DEFINED__
#ifndef __INTERFACE_IAppletGUI_DEFINED__
#define __INTERFACE_IAppletGUI_DEFINED__

CAR_INTERFACE("7A91483A-1312-1E08-24FC-B804A1068914")
IAppletGUI : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletGUI*) Probe(PInterface pObj)
    {
        return (IAppletGUI*)pObj->Probe(EIID_IAppletGUI);
    }

    virtual CARAPI CreateGrafixObject(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ const struct GrafixObjectParams & Param1,
        /* [out] */ IGrafixObject ** ppParam2) = 0;

    virtual CARAPI PostEvent(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI GetAllForms(
        /* [out] */ IObjectEnumerator ** ppParam0) = 0;

    virtual CARAPI Activate() = 0;

    virtual CARAPI Deactivate() = 0;

    virtual CARAPI Close() = 0;

};

#endif // __INTERFACE_IAppletGUI_DEFINED__
#ifndef __INTERFACE_JAppletPrivateEvents_DEFINED__
#define __INTERFACE_JAppletPrivateEvents_DEFINED__

CAR_INTERFACE("C7ED2438-9313-350C-58E4-20710345331B")
JAppletPrivateEvents : public IInterface
{

    // callback helper method
    static _ELASTOS ECode AddRequestToFinishCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletPrivateEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletPrivateEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AddRequestToFinishCallback(
                        Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode AddRequestToFinishCallback(
                PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletPrivateEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletPrivateEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        if (Conversion<T, CCarObject>::exists) {
            ec = pHandler->AddRequestToFinishCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CAR));
        }
        else {
            ec = pHandler->AddRequestToFinishCallback(
                            Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc, CallbackType_CPP));
        }
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode RemoveRequestToFinishCallback(
                    PInterface pServerObj,
                    _ELASTOS ECode (*pFunc)(_ELASTOS PVoid, PInterface),
                    _ELASTOS PVoid pUserData=NULL)
    {
        JAppletPrivateEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletPrivateEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveRequestToFinishCallback(
                                Elastos::EventHandler::Make(pUserData, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    template <class T>
    static _ELASTOS ECode RemoveRequestToFinishCallback(
                    PInterface pServerObj,
                T *pThis,
                _ELASTOS ECode (CARAPICALLTYPE T::*pFunc)(
                        PInterface))
    {
        JAppletPrivateEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletPrivateEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->RemoveRequestToFinishCallback(
                                    Elastos::EventHandler::Make(pThis, *(_ELASTOS PVoid*)&pFunc));
        pHandler->Release();
        return ec;
    }

    static _ELASTOS ECode AcquireRequestToFinishRendezvous(
                            PInterface pServerObj,
                            ICallbackRendezvous** ppRendezvous)
    {
        JAppletPrivateEventsHandler* pHandler;
        _ELASTOS ECode ec;

        ec = _Impl_AcquireCallbackHandler(pServerObj,

                        EIID_JAppletPrivateEventsHandler, (PInterface*)&pHandler);
        if (FAILED(ec)) return ec;

        ec = pHandler->AcquireRequestToFinishRendezvous(ppRendezvous);
        pHandler->Release();
        return ec;
    }

};

#endif // __INTERFACE_JAppletPrivateEvents_DEFINED__
#ifndef __INTERFACE_IAppletTaskStartup_DEFINED__
#define __INTERFACE_IAppletTaskStartup_DEFINED__

CAR_INTERFACE("62AB1723-9312-240E-6CB8-48FD23250000")
IAppletTaskStartup : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletTaskStartup*) Probe(PInterface pObj)
    {
        return (IAppletTaskStartup*)pObj->Probe(EIID_IAppletTaskStartup);
    }

    virtual CARAPI Main(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS String> & Param0) = 0;

};

#endif // __INTERFACE_IAppletTaskStartup_DEFINED__
#ifndef __INTERFACE_IAppletServices_DEFINED__
#define __INTERFACE_IAppletServices_DEFINED__

CAR_INTERFACE("EFAC242F-9312-36CC-7E08-CE6C14000000")
IAppletServices : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletServices*) Probe(PInterface pObj)
    {
        return (IAppletServices*)pObj->Probe(EIID_IAppletServices);
    }

    virtual CARAPI RequestService(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS String Param1,
        /* [in] */ IAppletSession * pParam2) = 0;

    virtual CARAPI Notify(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1) = 0;

};

#endif // __INTERFACE_IAppletServices_DEFINED__
#ifndef __INTERFACE_IAppletSystemSpecific_DEFINED__
#define __INTERFACE_IAppletSystemSpecific_DEFINED__

CAR_INTERFACE("72778827-9312-1CDD-66A0-30C122050B13")
IAppletSystemSpecific : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IAppletSystemSpecific*) Probe(PInterface pObj)
    {
        return (IAppletSystemSpecific*)pObj->Probe(EIID_IAppletSystemSpecific);
    }

    virtual CARAPI GetCallbackContext(
        /* [out] */ IInterface ** ppParam0) = 0;

    virtual CARAPI SetAppletGUI(
        /* [in] */ IAppletGUI * pParam0) = 0;

    virtual CARAPI NotifyActivated(
        /* [in] */ _ELASTOS Flags32 Param0) = 0;

    virtual CARAPI NotifyDeactivated(
        /* [in] */ _ELASTOS Flags32 Param0) = 0;

    virtual CARAPI NotifyLayoutReady(
        /* [in] */ _ELASTOS Flags32 Param0) = 0;

    virtual CARAPI NotifyThreadCreated(
        /* [in] */ IThread * pParam0) = 0;

    virtual CARAPI NotifyThreadQuit(
        /* [in] */ IThread * pParam0) = 0;

};

#endif // __INTERFACE_IAppletSystemSpecific_DEFINED__
#ifndef __INTERFACE_IActiveTimer_DEFINED__
#define __INTERFACE_IActiveTimer_DEFINED__

CAR_INTERFACE("A1D4422A-0292-3713-58E4-4031FC876AD7")
IActiveTimer : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IActiveTimer*) Probe(PInterface pObj)
    {
        return (IActiveTimer*)pObj->Probe(EIID_IActiveTimer);
    }

    virtual CARAPI Start() = 0;

    virtual CARAPI Stop() = 0;

    virtual CARAPI SetInterval(
        /* [in] */ _ELASTOS Millisecond32 Param0) = 0;

    virtual CARAPI GetInterval(
        /* [out] */ _ELASTOS Millisecond32 * pParam0) = 0;

    virtual CARAPI SetPriority(
        /* [in] */ ThreadPriority Param0) = 0;

    virtual CARAPI GetPriority(
        /* [out] */ ThreadPriority * pParam0) = 0;

};

#endif // __INTERFACE_IActiveTimer_DEFINED__
#ifndef __INTERFACE_ISocket_DEFINED__
#define __INTERFACE_ISocket_DEFINED__

CAR_INTERFACE("14395E32-E952-421F-CC38-2AC75568390E")
ISocket : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ISocket*) Probe(PInterface pObj)
    {
        return (ISocket*)pObj->Probe(EIID_ISocket);
    }

    virtual CARAPI Accept(
        /* [out] */ ISocket ** ppParam0,
        /* [out] */ struct SocketAddr * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2) = 0;

    virtual CARAPI Bind(
        /* [in] */ const struct SocketAddr & Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI Connect(
        /* [in] */ const struct SocketAddr & Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetPeerName(
        /* [out] */ struct SocketAddr * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetSockName(
        /* [out] */ struct SocketAddr * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI Listen(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI Recv(
        /* [in] */ _ELASTOS Flags32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI RecvFrom(
        /* [in] */ _ELASTOS Flags32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2,
        /* [out] */ struct SocketAddr * pParam3,
        /* [out] */ _ELASTOS Int32 * pParam4) = 0;

    virtual CARAPI Send(
        /* [in] */ _ELASTOS Flags32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI SendTo(
        /* [in] */ _ELASTOS Flags32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [in] */ const struct SocketAddr & Param3,
        /* [out] */ _ELASTOS Int32 * pParam4) = 0;

    virtual CARAPI Shutdown(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI EventSelect(
        /* [in] */ IEvent * pParam0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

};

#endif // __INTERFACE_ISocket_DEFINED__
#ifndef __INTERFACE_ISocketEx_DEFINED__
#define __INTERFACE_ISocketEx_DEFINED__

CAR_INTERFACE("90448130-6952-3F68-3473-9061C245D472")
ISocketEx : public ISocket
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ISocketEx*) Probe(PInterface pObj)
    {
        return (ISocketEx*)pObj->Probe(EIID_ISocketEx);
    }

    virtual CARAPI SetSockOpt(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ const _ELASTOS MemoryBuf & Param2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI GetSockOpt(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [out] */ _ELASTOS MemoryBuf * pParam3,
        /* [out] */ _ELASTOS Int32 * pParam4) = 0;

    virtual CARAPI Ioctl(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ const _ELASTOS MemoryBuf & Param1,
        /* [out] */ _ELASTOS MemoryBuf * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

};

#endif // __INTERFACE_ISocketEx_DEFINED__
#ifndef __INTERFACE_ISocketService_DEFINED__
#define __INTERFACE_ISocketService_DEFINED__

CAR_INTERFACE("1E6E372A-E952-3FCC-2E95-16EFADB48D72")
ISocketService : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ISocketService*) Probe(PInterface pObj)
    {
        return (ISocketService*)pObj->Probe(EIID_ISocketService);
    }

    virtual CARAPI CreateSocket(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [out] */ ISocket ** ppParam3,
        /* [out] */ _ELASTOS Int32 * pParam4) = 0;

    virtual CARAPI WaitForSockets(
        /* [in] */ const struct SocketTime & Param0,
        /* [in] */ const _ELASTOS BufferOf<IInterface *> & Param1,
        /* [in] */ const _ELASTOS MemoryBuf & Param2,
        /* [out] */ _ELASTOS MemoryBuf * pParam3,
        /* [out] */ _ELASTOS Int32 * pParam4) = 0;

    virtual CARAPI GetIPAddresses(
        /* [out] */ struct IPv4Address * pParam0,
        /* [out] */ struct IPv4Address * pParam1,
        /* [out] */ struct IPv4Address * pParam2,
        /* [out] */ struct IPv4Address * pParam3,
        /* [out] */ struct IPv4Address * pParam4) = 0;

};

#endif // __INTERFACE_ISocketService_DEFINED__
#ifndef __INTERFACE_IModuleInfo_DEFINED__
#define __INTERFACE_IModuleInfo_DEFINED__

CAR_INTERFACE("EB08F22D-4E92-3F7E-CA69-2D07BE9C1E4B")
IModuleInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IModuleInfo*) Probe(PInterface pObj)
    {
        return (IModuleInfo*)pObj->Probe(EIID_IModuleInfo);
    }

    virtual CARAPI GetPath(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetVersion(
        /* [out] */ _ELASTOS Int32 * pParam0,
        /* [out] */ _ELASTOS Int32 * pParam1,
        /* [out] */ _ELASTOS Int32 * pParam2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI GetClassCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllClassInfos(
        /* [out] */ _ELASTOS BufferOf<IClassInfo *> * pParam0) = 0;

    virtual CARAPI GetClassInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IClassInfo ** ppParam1) = 0;

    virtual CARAPI GetInterfaceCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllInterfaceInfos(
        /* [out] */ _ELASTOS BufferOf<IInterfaceInfo *> * pParam0) = 0;

    virtual CARAPI GetInterfaceInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IInterfaceInfo ** ppParam1) = 0;

    virtual CARAPI GetStructCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllStructInfos(
        /* [out] */ _ELASTOS BufferOf<IStructInfo *> * pParam0) = 0;

    virtual CARAPI GetStructInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IStructInfo ** ppParam1) = 0;

    virtual CARAPI GetEnumCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllEnumInfos(
        /* [out] */ _ELASTOS BufferOf<IEnumInfo *> * pParam0) = 0;

    virtual CARAPI GetEnumInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IEnumInfo ** ppParam1) = 0;

    virtual CARAPI GetTypeAliasCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllTypeAliasInfos(
        /* [out] */ _ELASTOS BufferOf<ITypeAliasInfo *> * pParam0) = 0;

    virtual CARAPI GetTypeAliasInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ ITypeAliasInfo ** ppParam1) = 0;

    virtual CARAPI GetConstantCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllConstantInfos(
        /* [out] */ _ELASTOS BufferOf<IConstantInfo *> * pParam0) = 0;

    virtual CARAPI GetConstantInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IConstantInfo ** ppParam1) = 0;

    virtual CARAPI GetImportModuleInfoCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllImportModuleInfos(
        /* [out] */ _ELASTOS BufferOf<IModuleInfo *> * pParam0) = 0;

};

#endif // __INTERFACE_IModuleInfo_DEFINED__
#ifndef __INTERFACE_IClassInfo_DEFINED__
#define __INTERFACE_IClassInfo_DEFINED__

CAR_INTERFACE("3B52F53A-1E92-3F7E-CA09-2D27AF9C4E7E")
IClassInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IClassInfo*) Probe(PInterface pObj)
    {
        return (IClassInfo*)pObj->Probe(EIID_IClassInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetId(
        /* [out] */ _ELASTOS ClassID * pParam0) = 0;

    virtual CARAPI GetModuleInfo(
        /* [out] */ IModuleInfo ** ppParam0) = 0;

    virtual CARAPI IsSingleton(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetThreadingModel(
        /* [out] */ ThreadingModel * pParam0) = 0;

    virtual CARAPI IsPrivate(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI IsReturnValue(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI IsBaseClass(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI HasBaseClass(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetBaseClassInfo(
        /* [out] */ IClassInfo ** ppParam0) = 0;

    virtual CARAPI IsGeneric(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI HasGeneric(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetGenericInfo(
        /* [out] */ IClassInfo ** ppParam0) = 0;

    virtual CARAPI IsContext(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetAspectCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllAspectInfos(
        /* [out] */ _ELASTOS BufferOf<IClassInfo *> * pParam0) = 0;

    virtual CARAPI GetAspectInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IClassInfo ** ppParam1) = 0;

    virtual CARAPI IsAspect(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetAggregateeCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllAggregateeInfos(
        /* [out] */ _ELASTOS BufferOf<IClassInfo *> * pParam0) = 0;

    virtual CARAPI GetAggregateeInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IClassInfo ** ppParam1) = 0;

    virtual CARAPI GetConstructorCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllConstructorInfos(
        /* [out] */ _ELASTOS BufferOf<IConstructorInfo *> * pParam0) = 0;

    virtual CARAPI GetConstructorInfoByParamNames(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IConstructorInfo ** ppParam1) = 0;

    virtual CARAPI GetConstructorInfoByParamCount(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IConstructorInfo ** ppParam1) = 0;

    virtual CARAPI GetInterfaceCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllInterfaceInfos(
        /* [out] */ _ELASTOS BufferOf<IInterfaceInfo *> * pParam0) = 0;

    virtual CARAPI GetInterfaceInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IInterfaceInfo ** ppParam1) = 0;

    virtual CARAPI GetCallbackInterfaceCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllCallbackInterfaceInfos(
        /* [out] */ _ELASTOS BufferOf<IInterfaceInfo *> * pParam0) = 0;

    virtual CARAPI GetCallbackInterfaceInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IInterfaceInfo ** ppParam1) = 0;

    virtual CARAPI GetMethodCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllMethodInfos(
        /* [out] */ _ELASTOS BufferOf<IMethodInfo *> * pParam0) = 0;

    virtual CARAPI GetMethodInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IMethodInfo ** ppParam1) = 0;

    virtual CARAPI GetCallbackMethodCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllCallbackMethodInfos(
        /* [out] */ _ELASTOS BufferOf<ICallbackMethodInfo *> * pParam0) = 0;

    virtual CARAPI GetCallbackMethodInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ ICallbackMethodInfo ** ppParam1) = 0;

    virtual CARAPI RemoveAllCallbackHandlers(
        /* [in] */ PInterface pParam0) = 0;

    virtual CARAPI CreateObject(
        /* [out] */ PInterface * ppParam0) = 0;

    virtual CARAPI CreateObjectInContext(
        /* [in] */ PContext pParam0,
        /* [out] */ PInterface * ppParam1) = 0;

};

#endif // __INTERFACE_IClassInfo_DEFINED__
#ifndef __INTERFACE_IFunctionInfo_DEFINED__
#define __INTERFACE_IFunctionInfo_DEFINED__

CAR_INTERFACE("7017573D-3892-3F7E-CA09-2D97D552B925")
IFunctionInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IFunctionInfo*) Probe(PInterface pObj)
    {
        return (IFunctionInfo*)pObj->Probe(EIID_IFunctionInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetParamCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllParamInfos(
        /* [out] */ _ELASTOS BufferOf<IParamInfo *> * pParam0) = 0;

    virtual CARAPI GetParamInfoByIndex(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IParamInfo ** ppParam1) = 0;

    virtual CARAPI GetParamInfoByName(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IParamInfo ** ppParam1) = 0;

};

#endif // __INTERFACE_IFunctionInfo_DEFINED__
#ifndef __INTERFACE_IParamInfo_DEFINED__
#define __INTERFACE_IParamInfo_DEFINED__

CAR_INTERFACE("32C78328-5652-3F7E-CAD9-E4574E68397D")
IParamInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IParamInfo*) Probe(PInterface pObj)
    {
        return (IParamInfo*)pObj->Probe(EIID_IParamInfo);
    }

    virtual CARAPI GetMethodInfo(
        /* [out] */ IMethodInfo ** ppParam0) = 0;

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetIndex(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetIOAttribute(
        /* [out] */ ParamIOAttribute * pParam0) = 0;

    virtual CARAPI IsReturnValue(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

    virtual CARAPI GetAdvisedCapacity(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI IsUsingTypeAlias(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetUsedTypeAliasInfo(
        /* [out] */ ITypeAliasInfo ** ppParam0) = 0;

};

#endif // __INTERFACE_IParamInfo_DEFINED__
#ifndef __INTERFACE_IMethodInfo_DEFINED__
#define __INTERFACE_IMethodInfo_DEFINED__

CAR_INTERFACE("44317B39-4D92-3F7E-2E55-D98830870C17")
IMethodInfo : public IFunctionInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IMethodInfo*) Probe(PInterface pObj)
    {
        return (IMethodInfo*)pObj->Probe(EIID_IMethodInfo);
    }

    virtual CARAPI CreateArgumentList(
        /* [out] */ IArgumentList ** ppParam0) = 0;

    virtual CARAPI Invoke(
        /* [in] */ PInterface pParam0,
        /* [in] */ IArgumentList * pParam1) = 0;

};

#endif // __INTERFACE_IMethodInfo_DEFINED__
#ifndef __INTERFACE_IArgumentList_DEFINED__
#define __INTERFACE_IArgumentList_DEFINED__

CAR_INTERFACE("A82FEE26-9552-3F8D-CA89-E3A7196015A6")
IArgumentList : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IArgumentList*) Probe(PInterface pObj)
    {
        return (IArgumentList*)pObj->Probe(EIID_IArgumentList);
    }

    virtual CARAPI GetFunctionInfo(
        /* [out] */ IFunctionInfo ** ppParam0) = 0;

    virtual CARAPI SetInputArgumentOfInt16(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int16 Param1) = 0;

    virtual CARAPI SetInputArgumentOfInt32(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetInputArgumentOfInt64(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int64 Param1) = 0;

    virtual CARAPI SetInputArgumentOfByte(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Byte Param1) = 0;

    virtual CARAPI SetInputArgumentOfFloat(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Float Param1) = 0;

    virtual CARAPI SetInputArgumentOfDouble(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Double Param1) = 0;

    virtual CARAPI SetInputArgumentOfChar8(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char8 Param1) = 0;

    virtual CARAPI SetInputArgumentOfChar16(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char16 Param1) = 0;

    virtual CARAPI SetInputArgumentOfString(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS String Param1) = 0;

    virtual CARAPI SetInputArgumentOfBoolean(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Boolean Param1) = 0;

    virtual CARAPI SetInputArgumentOfEMuid(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI SetInputArgumentOfEGuid(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI SetInputArgumentOfECode(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS ECode Param1) = 0;

    virtual CARAPI SetInputArgumentOfLocalPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ LocalPtr pParam1) = 0;

    virtual CARAPI SetInputArgumentOfLocalType(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetInputArgumentOfEnum(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetInputArgumentOfCarArray(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS PCarQuintet pParam1) = 0;

    virtual CARAPI SetInputArgumentOfStructPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetInputArgumentOfObjectPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ PInterface pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfInt16Ptr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int16 * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfInt32Ptr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfInt64Ptr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int64 * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfBytePtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Byte * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfFloatPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Float * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfDoublePtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Double * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfChar8Ptr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char8 * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfChar16Ptr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char16 * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfBooleanPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfEMuidPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfEGuidPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfECodePtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS ECode * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfLocalPtrPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ LocalPtr * ppParam1) = 0;

    virtual CARAPI SetOutputArgumentOfLocalTypePtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfEnumPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfStringBufPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS StringBuf * pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfStringBufPtrPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out, callee] */ _ELASTOS StringBuf ** ppParam1) = 0;

    virtual CARAPI SetOutputArgumentOfCarArrayPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PCarQuintet pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfCarArrayPtrPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PCarQuintet * ppParam1) = 0;

    virtual CARAPI SetOutputArgumentOfStructPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetOutputArgumentOfStructPtrPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PVoid * ppParam1) = 0;

    virtual CARAPI SetOutputArgumentOfObjectPtrPtr(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ PInterface * ppParam1) = 0;

};

#endif // __INTERFACE_IArgumentList_DEFINED__
#ifndef __INTERFACE_IDataTypeInfo_DEFINED__
#define __INTERFACE_IDataTypeInfo_DEFINED__

CAR_INTERFACE("AF892722-A652-FCE5-7E94-135A2E74B94C")
IDataTypeInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDataTypeInfo*) Probe(PInterface pObj)
    {
        return (IDataTypeInfo*)pObj->Probe(EIID_IDataTypeInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetSize(
        /* [out] */ _ELASTOS MemorySize * pParam0) = 0;

    virtual CARAPI GetDataType(
        /* [out] */ CarDataType * pParam0) = 0;

};

#endif // __INTERFACE_IDataTypeInfo_DEFINED__
#ifndef __INTERFACE_ITypeAliasInfo_DEFINED__
#define __INTERFACE_ITypeAliasInfo_DEFINED__

CAR_INTERFACE("49F64054-1C92-2C05-1769-F951A5CBCE2A")
ITypeAliasInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ITypeAliasInfo*) Probe(PInterface pObj)
    {
        return (ITypeAliasInfo*)pObj->Probe(EIID_ITypeAliasInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

    virtual CARAPI GetModuleInfo(
        /* [out] */ IModuleInfo ** ppParam0) = 0;

    virtual CARAPI IsDummy(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetPtrLevel(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

};

#endif // __INTERFACE_ITypeAliasInfo_DEFINED__
#ifndef __INTERFACE_IConstructorInfo_DEFINED__
#define __INTERFACE_IConstructorInfo_DEFINED__

CAR_INTERFACE("64399B59-1112-7FC8-5F5D-D5F28301DE46")
IConstructorInfo : public IFunctionInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IConstructorInfo*) Probe(PInterface pObj)
    {
        return (IConstructorInfo*)pObj->Probe(EIID_IConstructorInfo);
    }

    virtual CARAPI CreateArgumentList(
        /* [out] */ IArgumentList ** ppParam0) = 0;

    virtual CARAPI CreateObject(
        /* [in] */ IArgumentList * pParam0,
        /* [out] */ PInterface * ppParam1) = 0;

    virtual CARAPI CreateObjectInContext(
        /* [in] */ PContext pParam0,
        /* [in] */ IArgumentList * pParam1,
        /* [out] */ PInterface * ppParam2) = 0;

};

#endif // __INTERFACE_IConstructorInfo_DEFINED__
#ifndef __INTERFACE_IInterfaceInfo_DEFINED__
#define __INTERFACE_IInterfaceInfo_DEFINED__

CAR_INTERFACE("F8108D33-40D2-3F7E-CAC9-2BA7935FC28F")
IInterfaceInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IInterfaceInfo*) Probe(PInterface pObj)
    {
        return (IInterfaceInfo*)pObj->Probe(EIID_IInterfaceInfo);
    }

    virtual CARAPI GetId(
        /* [out] */ _ELASTOS InterfaceID * pParam0) = 0;

    virtual CARAPI GetModuleInfo(
        /* [out] */ IModuleInfo ** ppParam0) = 0;

    virtual CARAPI IsLocal(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI HasBase(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetBaseInfo(
        /* [out] */ IInterfaceInfo ** ppParam0) = 0;

    virtual CARAPI GetMethodCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllMethodInfos(
        /* [out] */ _ELASTOS BufferOf<IMethodInfo *> * pParam0) = 0;

    virtual CARAPI GetMethodInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IMethodInfo ** ppParam1) = 0;

};

#endif // __INTERFACE_IInterfaceInfo_DEFINED__
#ifndef __INTERFACE_ICallbackMethodInfo_DEFINED__
#define __INTERFACE_ICallbackMethodInfo_DEFINED__

CAR_INTERFACE("8159972C-1C52-FC9B-7E18-89D337CEA554")
ICallbackMethodInfo : public IFunctionInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICallbackMethodInfo*) Probe(PInterface pObj)
    {
        return (ICallbackMethodInfo*)pObj->Probe(EIID_ICallbackMethodInfo);
    }

    virtual CARAPI AddCallback(
        /* [in] */ PInterface pParam0,
        /* [in] */ _ELASTOS EventHandler Param1) = 0;

    virtual CARAPI RemoveCallback(
        /* [in] */ PInterface pParam0,
        /* [in] */ _ELASTOS EventHandler Param1) = 0;

    virtual CARAPI CreateDelegateProxy(
        /* [in] */ _ELASTOS PVoid pParam0,
        /* [in] */ _ELASTOS PVoid pParam1,
        /* [in] */ ICallbackInvocation * pParam2,
        /* [out] */ IDelegateProxy ** ppParam3) = 0;

};

#endif // __INTERFACE_ICallbackMethodInfo_DEFINED__
#ifndef __INTERFACE_ICallbackInvocation_DEFINED__
#define __INTERFACE_ICallbackInvocation_DEFINED__

CAR_INTERFACE("10DA1A28-1C52-3984-6498-2001FF07C21C")
ICallbackInvocation : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICallbackInvocation*) Probe(PInterface pObj)
    {
        return (ICallbackInvocation*)pObj->Probe(EIID_ICallbackInvocation);
    }

    virtual CARAPI Invoke(
        /* [in] */ _ELASTOS PVoid pParam0,
        /* [in] */ _ELASTOS PVoid pParam1,
        /* [in] */ ICallbackArgumentList * pParam2) = 0;

};

#endif // __INTERFACE_ICallbackInvocation_DEFINED__
#ifndef __INTERFACE_ICallbackArgumentList_DEFINED__
#define __INTERFACE_ICallbackArgumentList_DEFINED__

CAR_INTERFACE("424EF325-9C52-1B2A-7F94-8B63935F39CC")
ICallbackArgumentList : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICallbackArgumentList*) Probe(PInterface pObj)
    {
        return (ICallbackArgumentList*)pObj->Probe(EIID_ICallbackArgumentList);
    }

    virtual CARAPI GetCallbackMethodInfo(
        /* [out] */ ICallbackMethodInfo ** ppParam0) = 0;

    virtual CARAPI GetServerPtrArgument(
        /* [out] */ PInterface * ppParam0) = 0;

    virtual CARAPI GetInt16Argument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int16 * pParam1) = 0;

    virtual CARAPI GetInt32Argument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetInt64Argument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int64 * pParam1) = 0;

    virtual CARAPI GetByteArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Byte * pParam1) = 0;

    virtual CARAPI GetFloatArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Float * pParam1) = 0;

    virtual CARAPI GetDoubleArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Double * pParam1) = 0;

    virtual CARAPI GetChar8Argument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char8 * pParam1) = 0;

    virtual CARAPI GetChar16Argument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char16 * pParam1) = 0;

    virtual CARAPI GetStringArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS String * pParam1) = 0;

    virtual CARAPI GetBooleanArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

    virtual CARAPI GetEMuidArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EMuid ** ppParam1) = 0;

    virtual CARAPI GetEGuidArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EGuid ** ppParam1) = 0;

    virtual CARAPI GetECodeArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS ECode * pParam1) = 0;

    virtual CARAPI GetLocalPtrArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ LocalPtr * ppParam1) = 0;

    virtual CARAPI GetEnumArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetCarArrayArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PCarQuintet * ppParam1) = 0;

    virtual CARAPI GetStructPtrArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PVoid * ppParam1) = 0;

    virtual CARAPI GetObjectPtrArgument(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ PInterface * ppParam1) = 0;

};

#endif // __INTERFACE_ICallbackArgumentList_DEFINED__
#ifndef __INTERFACE_IDelegateProxy_DEFINED__
#define __INTERFACE_IDelegateProxy_DEFINED__

CAR_INTERFACE("CAF7623F-AA52-350C-64EC-E0F1A35C1C9B")
IDelegateProxy : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDelegateProxy*) Probe(PInterface pObj)
    {
        return (IDelegateProxy*)pObj->Probe(EIID_IDelegateProxy);
    }

    virtual CARAPI GetCallbackMethodInfo(
        /* [out] */ ICallbackMethodInfo ** ppParam0) = 0;

    virtual CARAPI GetTargetObject(
        /* [out] */ _ELASTOS PVoid * ppParam0) = 0;

    virtual CARAPI GetTargetMethod(
        /* [out] */ _ELASTOS PVoid * ppParam0) = 0;

    virtual CARAPI GetCallbackInvocation(
        /* [out] */ ICallbackInvocation ** ppParam0) = 0;

    virtual CARAPI GetDelegate(
        /* [out] */ _ELASTOS EventHandler * pParam0) = 0;

};

#endif // __INTERFACE_IDelegateProxy_DEFINED__
#ifndef __INTERFACE_IStructInfo_DEFINED__
#define __INTERFACE_IStructInfo_DEFINED__

CAR_INTERFACE("C3DE8828-6C52-3F7E-CAE9-E457EE010B14")
IStructInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStructInfo*) Probe(PInterface pObj)
    {
        return (IStructInfo*)pObj->Probe(EIID_IStructInfo);
    }

    virtual CARAPI GetModuleInfo(
        /* [out] */ IModuleInfo ** ppParam0) = 0;

    virtual CARAPI GetFieldCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllFieldInfos(
        /* [out] */ _ELASTOS BufferOf<IFieldInfo *> * pParam0) = 0;

    virtual CARAPI GetFieldInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IFieldInfo ** ppParam1) = 0;

    virtual CARAPI CreateVariable(
        /* [out] */ IVariableOfStruct ** ppParam0) = 0;

    virtual CARAPI CreateVariableBox(
        /* [in] */ _ELASTOS PVoid pParam0,
        /* [out] */ IVariableOfStruct ** ppParam1) = 0;

};

#endif // __INTERFACE_IStructInfo_DEFINED__
#ifndef __INTERFACE_IFieldInfo_DEFINED__
#define __INTERFACE_IFieldInfo_DEFINED__

CAR_INTERFACE("46D71D54-03D2-2783-B5FC-A8D265671539")
IFieldInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IFieldInfo*) Probe(PInterface pObj)
    {
        return (IFieldInfo*)pObj->Probe(EIID_IFieldInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

};

#endif // __INTERFACE_IFieldInfo_DEFINED__
#ifndef __INTERFACE_IVariable_DEFINED__
#define __INTERFACE_IVariable_DEFINED__

CAR_INTERFACE("47D42425-F712-E51F-96F3-2B9781048F17")
IVariable : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IVariable*) Probe(PInterface pObj)
    {
        return (IVariable*)pObj->Probe(EIID_IVariable);
    }

    virtual CARAPI GetTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

    virtual CARAPI GetPayload(
        /* [out] */ _ELASTOS PVoid * ppParam0) = 0;

    virtual CARAPI Rebox(
        /* [in] */ _ELASTOS PVoid pParam0) = 0;

};

#endif // __INTERFACE_IVariable_DEFINED__
#ifndef __INTERFACE_IVariableOfStruct_DEFINED__
#define __INTERFACE_IVariableOfStruct_DEFINED__

CAR_INTERFACE("6EA5483B-7712-B1A6-7F94-D37CE37EB972")
IVariableOfStruct : public IVariable
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IVariableOfStruct*) Probe(PInterface pObj)
    {
        return (IVariableOfStruct*)pObj->Probe(EIID_IVariableOfStruct);
    }

    virtual CARAPI GetSetter(
        /* [out] */ IStructSetter ** ppParam0) = 0;

    virtual CARAPI GetGetter(
        /* [out] */ IStructGetter ** ppParam0) = 0;

};

#endif // __INTERFACE_IVariableOfStruct_DEFINED__
#ifndef __INTERFACE_IStructSetter_DEFINED__
#define __INTERFACE_IStructSetter_DEFINED__

CAR_INTERFACE("3759FB32-6C52-37CD-EEFF-58BFE4010B14")
IStructSetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStructSetter*) Probe(PInterface pObj)
    {
        return (IStructSetter*)pObj->Probe(EIID_IStructSetter);
    }

    virtual CARAPI ZeroAllFields() = 0;

    virtual CARAPI SetInt16Field(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Int16 Param1) = 0;

    virtual CARAPI SetInt32Field(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetInt64Field(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Int64 Param1) = 0;

    virtual CARAPI SetByteField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Byte Param1) = 0;

    virtual CARAPI SetFloatField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Float Param1) = 0;

    virtual CARAPI SetDoubleField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Double Param1) = 0;

    virtual CARAPI SetChar8Field(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Char8 Param1) = 0;

    virtual CARAPI SetChar16Field(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Char16 Param1) = 0;

    virtual CARAPI SetBooleanField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Boolean Param1) = 0;

    virtual CARAPI SetEMuidField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI SetEGuidField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI SetECodeField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS ECode Param1) = 0;

    virtual CARAPI SetLocalPtrField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ LocalPtr pParam1) = 0;

    virtual CARAPI SetLocalTypeField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetEnumField(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI GetStructFieldSetter(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IStructSetter ** ppParam1) = 0;

    virtual CARAPI GetCppVectorFieldSetter(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ ICppVectorSetter ** ppParam1) = 0;

};

#endif // __INTERFACE_IStructSetter_DEFINED__
#ifndef __INTERFACE_ICppVectorSetter_DEFINED__
#define __INTERFACE_ICppVectorSetter_DEFINED__

CAR_INTERFACE("8922F754-0312-1FB4-885D-5593F9C78867")
ICppVectorSetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICppVectorSetter*) Probe(PInterface pObj)
    {
        return (ICppVectorSetter*)pObj->Probe(EIID_ICppVectorSetter);
    }

    virtual CARAPI ZeroAllElements() = 0;

    virtual CARAPI SetAllElements(
        /* [in] */ _ELASTOS PVoid pParam0,
        /* [in] */ _ELASTOS MemorySize Param1) = 0;

    virtual CARAPI SetInt16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int16 Param1) = 0;

    virtual CARAPI SetInt32Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetInt64Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int64 Param1) = 0;

    virtual CARAPI SetByteElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Byte Param1) = 0;

    virtual CARAPI SetFloatElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Float Param1) = 0;

    virtual CARAPI SetDoubleElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Double Param1) = 0;

    virtual CARAPI SetChar8Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char8 Param1) = 0;

    virtual CARAPI SetChar16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char16 Param1) = 0;

    virtual CARAPI SetBooleanElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Boolean Param1) = 0;

    virtual CARAPI SetEMuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI SetEGuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI SetECodeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS ECode Param1) = 0;

    virtual CARAPI SetLocalPtrElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ LocalPtr pParam1) = 0;

    virtual CARAPI SetLocalTypeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetEnumElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI GetStructElementSetter(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IStructSetter ** ppParam1) = 0;

    virtual CARAPI GetCppVectorElementSetter(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ ICppVectorSetter ** ppParam1) = 0;

};

#endif // __INTERFACE_ICppVectorSetter_DEFINED__
#ifndef __INTERFACE_IStructGetter_DEFINED__
#define __INTERFACE_IStructGetter_DEFINED__

CAR_INTERFACE("84EDEE25-EC52-3772-EEFF-286730808107")
IStructGetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStructGetter*) Probe(PInterface pObj)
    {
        return (IStructGetter*)pObj->Probe(EIID_IStructGetter);
    }

    virtual CARAPI GetInt16Field(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Int16 * pParam1) = 0;

    virtual CARAPI GetInt32Field(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetInt64Field(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Int64 * pParam1) = 0;

    virtual CARAPI GetByteField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Byte * pParam1) = 0;

    virtual CARAPI GetFloatField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Float * pParam1) = 0;

    virtual CARAPI GetDoubleField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Double * pParam1) = 0;

    virtual CARAPI GetChar8Field(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Char8 * pParam1) = 0;

    virtual CARAPI GetChar16Field(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Char16 * pParam1) = 0;

    virtual CARAPI GetBooleanField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

    virtual CARAPI GetEMuidField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI GetEGuidField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI GetECodeField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS ECode * pParam1) = 0;

    virtual CARAPI GetLocalPtrField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ LocalPtr * ppParam1) = 0;

    virtual CARAPI GetLocalTypeField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI GetEnumField(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetStructFieldGetter(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IStructGetter ** ppParam1) = 0;

    virtual CARAPI GetCppVectorFieldGetter(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ ICppVectorGetter ** ppParam1) = 0;

};

#endif // __INTERFACE_IStructGetter_DEFINED__
#ifndef __INTERFACE_ICppVectorGetter_DEFINED__
#define __INTERFACE_ICppVectorGetter_DEFINED__

CAR_INTERFACE("35EFFD4C-0312-1FB4-885D-AD92F947950A")
ICppVectorGetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICppVectorGetter*) Probe(PInterface pObj)
    {
        return (ICppVectorGetter*)pObj->Probe(EIID_ICppVectorGetter);
    }

    virtual CARAPI GetLength(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetRank(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetInt16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int16 * pParam1) = 0;

    virtual CARAPI GetInt32Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetInt64Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int64 * pParam1) = 0;

    virtual CARAPI GetByteElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Byte * pParam1) = 0;

    virtual CARAPI GetFloatElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Float * pParam1) = 0;

    virtual CARAPI GetDoubleElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Double * pParam1) = 0;

    virtual CARAPI GetChar8Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char8 * pParam1) = 0;

    virtual CARAPI GetChar16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char16 * pParam1) = 0;

    virtual CARAPI GetBooleanElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

    virtual CARAPI GetEMuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI GetEGuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI GetECodeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS ECode * pParam1) = 0;

    virtual CARAPI GetLocalPtrElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ LocalPtr * ppParam1) = 0;

    virtual CARAPI GetLocalTypeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI GetEnumElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetStructElementGetter(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IStructGetter ** ppParam1) = 0;

    virtual CARAPI GetCppVectorElementGetter(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ ICppVectorGetter ** ppParam1) = 0;

};

#endif // __INTERFACE_ICppVectorGetter_DEFINED__
#ifndef __INTERFACE_IEnumInfo_DEFINED__
#define __INTERFACE_IEnumInfo_DEFINED__

CAR_INTERFACE("1D9F6422-31D2-3F7E-CAE9-E4574EA1A572")
IEnumInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IEnumInfo*) Probe(PInterface pObj)
    {
        return (IEnumInfo*)pObj->Probe(EIID_IEnumInfo);
    }

    virtual CARAPI GetModuleInfo(
        /* [out] */ IModuleInfo ** ppParam0) = 0;

    virtual CARAPI GetItemCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetAllItemInfos(
        /* [out] */ _ELASTOS BufferOf<IEnumItemInfo *> * pParam0) = 0;

    virtual CARAPI GetItemInfo(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IEnumItemInfo ** ppParam1) = 0;

};

#endif // __INTERFACE_IEnumInfo_DEFINED__
#ifndef __INTERFACE_IEnumItemInfo_DEFINED__
#define __INTERFACE_IEnumItemInfo_DEFINED__

CAR_INTERFACE("9336283E-31D2-FC85-7E94-135AEE18BF72")
IEnumItemInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IEnumItemInfo*) Probe(PInterface pObj)
    {
        return (IEnumItemInfo*)pObj->Probe(EIID_IEnumItemInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetEnumInfo(
        /* [out] */ IEnumInfo ** ppParam0) = 0;

    virtual CARAPI GetValue(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

};

#endif // __INTERFACE_IEnumItemInfo_DEFINED__
#ifndef __INTERFACE_IConstantInfo_DEFINED__
#define __INTERFACE_IConstantInfo_DEFINED__

CAR_INTERFACE("F4DC2A4D-1112-82C8-6E68-F951A5CBCE2A")
IConstantInfo : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IConstantInfo*) Probe(PInterface pObj)
    {
        return (IConstantInfo*)pObj->Probe(EIID_IConstantInfo);
    }

    virtual CARAPI GetName(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetValue(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetModuleInfo(
        /* [out] */ IModuleInfo ** ppParam0) = 0;

};

#endif // __INTERFACE_IConstantInfo_DEFINED__
#ifndef __INTERFACE_IVariableOfCarArray_DEFINED__
#define __INTERFACE_IVariableOfCarArray_DEFINED__

CAR_INTERFACE("0E754A26-7712-0CA6-48D4-C0F2A39CE61B")
IVariableOfCarArray : public IVariable
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IVariableOfCarArray*) Probe(PInterface pObj)
    {
        return (IVariableOfCarArray*)pObj->Probe(EIID_IVariableOfCarArray);
    }

    virtual CARAPI GetSetter(
        /* [out] */ ICarArraySetter ** ppParam0) = 0;

    virtual CARAPI GetGetter(
        /* [out] */ ICarArrayGetter ** ppParam0) = 0;

};

#endif // __INTERFACE_IVariableOfCarArray_DEFINED__
#ifndef __INTERFACE_ICarArraySetter_DEFINED__
#define __INTERFACE_ICarArraySetter_DEFINED__

CAR_INTERFACE("BAC5FF25-0312-3512-B068-BE71FF87E6EC")
ICarArraySetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICarArraySetter*) Probe(PInterface pObj)
    {
        return (ICarArraySetter*)pObj->Probe(EIID_ICarArraySetter);
    }

    virtual CARAPI SetUsed(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI SetInt16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int16 Param1) = 0;

    virtual CARAPI SetInt32Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetInt64Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int64 Param1) = 0;

    virtual CARAPI SetByteElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Byte Param1) = 0;

    virtual CARAPI SetFloatElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Float Param1) = 0;

    virtual CARAPI SetDoubleElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Double Param1) = 0;

    virtual CARAPI SetEnumElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1) = 0;

    virtual CARAPI SetChar8Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char8 Param1) = 0;

    virtual CARAPI SetChar16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char16 Param1) = 0;

    virtual CARAPI SetStringElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS String Param1) = 0;

    virtual CARAPI SetBooleanElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Boolean Param1) = 0;

    virtual CARAPI SetEMuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI SetEGuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI SetECodeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS ECode Param1) = 0;

    virtual CARAPI SetLocalTypeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI SetObjectPtrElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ PInterface pParam1) = 0;

    virtual CARAPI GetStructElementSetter(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IStructSetter ** ppParam1) = 0;

};

#endif // __INTERFACE_ICarArraySetter_DEFINED__
#ifndef __INTERFACE_ICarArrayGetter_DEFINED__
#define __INTERFACE_ICarArrayGetter_DEFINED__

CAR_INTERFACE("7900F729-0312-3512-B094-BB71FF47393A")
ICarArrayGetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICarArrayGetter*) Probe(PInterface pObj)
    {
        return (ICarArrayGetter*)pObj->Probe(EIID_ICarArrayGetter);
    }

    virtual CARAPI GetCapacity(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetUsed(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetInt16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int16 * pParam1) = 0;

    virtual CARAPI GetInt32Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetInt64Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int64 * pParam1) = 0;

    virtual CARAPI GetByteElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Byte * pParam1) = 0;

    virtual CARAPI GetFloatElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Float * pParam1) = 0;

    virtual CARAPI GetDoubleElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Double * pParam1) = 0;

    virtual CARAPI GetEnumElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI GetChar8Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char8 * pParam1) = 0;

    virtual CARAPI GetChar16Element(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char16 * pParam1) = 0;

    virtual CARAPI GetStringElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS String * pParam1) = 0;

    virtual CARAPI GetBooleanElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Boolean * pParam1) = 0;

    virtual CARAPI GetEMuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EMuid * pParam1) = 0;

    virtual CARAPI GetEGuidElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS EGuid * pParam1) = 0;

    virtual CARAPI GetECodeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS ECode * pParam1) = 0;

    virtual CARAPI GetLocalTypeElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS PVoid pParam1) = 0;

    virtual CARAPI GetObjectPtrElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ PInterface * ppParam1) = 0;

    virtual CARAPI GetStructElementGetter(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IStructGetter ** ppParam1) = 0;

};

#endif // __INTERFACE_ICarArrayGetter_DEFINED__
#ifndef __INTERFACE_IVariableOfStringBuf_DEFINED__
#define __INTERFACE_IVariableOfStringBuf_DEFINED__

CAR_INTERFACE("0AF94B30-7712-B0A6-D7FC-28A7F9C6FD72")
IVariableOfStringBuf : public IVariable
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IVariableOfStringBuf*) Probe(PInterface pObj)
    {
        return (IVariableOfStringBuf*)pObj->Probe(EIID_IVariableOfStringBuf);
    }

    virtual CARAPI GetSetter(
        /* [out] */ IStringBufSetter ** ppParam0) = 0;

    virtual CARAPI GetGetter(
        /* [out] */ IStringBufGetter ** ppParam0) = 0;

};

#endif // __INTERFACE_IVariableOfStringBuf_DEFINED__
#ifndef __INTERFACE_IStringBufSetter_DEFINED__
#define __INTERFACE_IStringBufSetter_DEFINED__

CAR_INTERFACE("3C972228-EC12-9A35-6FDC-FFA1D9C10B14")
IStringBufSetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStringBufSetter*) Probe(PInterface pObj)
    {
        return (IStringBufSetter*)pObj->Probe(EIID_IStringBufSetter);
    }

    virtual CARAPI SetElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Char8 Param1) = 0;

    virtual CARAPI SetData(
        /* [in] */ _ELASTOS String Param0) = 0;

};

#endif // __INTERFACE_IStringBufSetter_DEFINED__
#ifndef __INTERFACE_IStringBufGetter_DEFINED__
#define __INTERFACE_IStringBufGetter_DEFINED__

CAR_INTERFACE("5EC13623-EC12-E535-6EDC-FF518E4E3989")
IStringBufGetter : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStringBufGetter*) Probe(PInterface pObj)
    {
        return (IStringBufGetter*)pObj->Probe(EIID_IStringBufGetter);
    }

    virtual CARAPI GetCapacity(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetLength(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetElement(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ _ELASTOS Char8 * pParam1) = 0;

    virtual CARAPI GetData(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_IStringBufGetter_DEFINED__
#ifndef __INTERFACE_ILocalPtrInfo_DEFINED__
#define __INTERFACE_ILocalPtrInfo_DEFINED__

CAR_INTERFACE("DA265134-C7D2-370C-6AF0-FB51AE03891A")
ILocalPtrInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ILocalPtrInfo*) Probe(PInterface pObj)
    {
        return (ILocalPtrInfo*)pObj->Probe(EIID_ILocalPtrInfo);
    }

    virtual CARAPI GetTargetTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

    virtual CARAPI GetPtrLevel(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

};

#endif // __INTERFACE_ILocalPtrInfo_DEFINED__
#ifndef __INTERFACE_ICarArrayInfo_DEFINED__
#define __INTERFACE_ICarArrayInfo_DEFINED__

CAR_INTERFACE("0EC46638-0312-3512-B0F0-FB51CEC10B14")
ICarArrayInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICarArrayInfo*) Probe(PInterface pObj)
    {
        return (ICarArrayInfo*)pObj->Probe(EIID_ICarArrayInfo);
    }

    virtual CARAPI GetElementTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

    virtual CARAPI CreateVariable(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IVariableOfCarArray ** ppParam1) = 0;

    virtual CARAPI CreateVariableBox(
        /* [in] */ _ELASTOS PCarQuintet pParam0,
        /* [out] */ IVariableOfCarArray ** ppParam1) = 0;

};

#endif // __INTERFACE_ICarArrayInfo_DEFINED__
#ifndef __INTERFACE_IStringBufInfo_DEFINED__
#define __INTERFACE_IStringBufInfo_DEFINED__

CAR_INTERFACE("D29F5526-EC12-FC35-7E5C-E27E89FB0219")
IStringBufInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStringBufInfo*) Probe(PInterface pObj)
    {
        return (IStringBufInfo*)pObj->Probe(EIID_IStringBufInfo);
    }

    virtual CARAPI CreateVariable(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [out] */ IVariableOfStringBuf ** ppParam1) = 0;

    virtual CARAPI CreateVariableBox(
        /* [in] */ _ELASTOS PCarQuintet pParam0,
        /* [out] */ IVariableOfStringBuf ** ppParam1) = 0;

};

#endif // __INTERFACE_IStringBufInfo_DEFINED__
#ifndef __INTERFACE_ICppVectorInfo_DEFINED__
#define __INTERFACE_ICppVectorInfo_DEFINED__

CAR_INTERFACE("688C514F-0312-1FB4-885D-D5F2A38A8394")
ICppVectorInfo : public IDataTypeInfo
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICppVectorInfo*) Probe(PInterface pObj)
    {
        return (ICppVectorInfo*)pObj->Probe(EIID_ICppVectorInfo);
    }

    virtual CARAPI GetElementTypeInfo(
        /* [out] */ IDataTypeInfo ** ppParam0) = 0;

    virtual CARAPI GetLength(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

};

#endif // __INTERFACE_ICppVectorInfo_DEFINED__
#ifndef __INTERFACE_IMediaObject_DEFINED__
#define __INTERFACE_IMediaObject_DEFINED__

CAR_INTERFACE("2B993726-0592-2CFD-481C-FD518E79B90C")
IMediaObject : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IMediaObject*) Probe(PInterface pObj)
    {
        return (IMediaObject*)pObj->Probe(EIID_IMediaObject);
    }

    virtual CARAPI GetURL(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetPermissions(
        /* [out] */ _ELASTOS Boolean * pParam0,
        /* [out] */ IConstraint ** ppParam1,
        /* [out] */ IConstraint ** ppParam2,
        /* [out] */ IConstraint ** ppParam3,
        /* [out] */ IConstraint ** ppParam4) = 0;

    virtual CARAPI DoneOnce(
        /* [in] */ DrmActionType Param0) = 0;

    virtual CARAPI GetContentType(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_IMediaObject_DEFINED__
#ifndef __INTERFACE_IConstraint_DEFINED__
#define __INTERFACE_IConstraint_DEFINED__

CAR_INTERFACE("6CB3495B-1112-77C8-25DE-F871858EAB18")
IConstraint : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IConstraint*) Probe(PInterface pObj)
    {
        return (IConstraint*)pObj->Probe(EIID_IConstraint);
    }

    virtual CARAPI IsUnconstrained(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI GetGrantCount(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI GetStartTime(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetEndTime(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

    virtual CARAPI GetInterval(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_IConstraint_DEFINED__
#ifndef __INTERFACE_IDrmManage_DEFINED__
#define __INTERFACE_IDrmManage_DEFINED__

CAR_INTERFACE("1E364B53-1352-1618-04F1-F951A5090C0B")
IDrmManage : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDrmManage*) Probe(PInterface pObj)
    {
        return (IDrmManage*)pObj->Probe(EIID_IDrmManage);
    }

    virtual CARAPI GetDrmMediaType(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ DrmMediaType * pParam1) = 0;

    virtual CARAPI AcquireMediaObject(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IMediaObject ** ppParam1) = 0;

    virtual CARAPI AddMediaObject(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IMediaObject ** ppParam1) = 0;

    virtual CARAPI RemoveMediaObject(
        /* [in] */ _ELASTOS String Param0) = 0;

};

#endif // __INTERFACE_IDrmManage_DEFINED__
#ifndef __INTERFACE_IInputStream_DEFINED__
#define __INTERFACE_IInputStream_DEFINED__

CAR_INTERFACE("95C85153-96D2-6CB5-84C1-F8A1A0370B93")
IInputStream : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IInputStream*) Probe(PInterface pObj)
    {
        return (IInputStream*)pObj->Probe(EIID_IInputStream);
    }

    virtual CARAPI Available(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI Close() = 0;

    virtual CARAPI Mark(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI IsMarkSupported(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI Read(
        /* [out] */ _ELASTOS Byte * pParam0) = 0;

    virtual CARAPI ReadBuffer(
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Byte> * pParam0) = 0;

    virtual CARAPI ReadBufferEx(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Byte> * pParam2) = 0;

    virtual CARAPI Reset() = 0;

    virtual CARAPI Skip(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

};

#endif // __INTERFACE_IInputStream_DEFINED__
#ifndef __INTERFACE_IOutputStream_DEFINED__
#define __INTERFACE_IOutputStream_DEFINED__

CAR_INTERFACE("5E8D352C-54D2-28D9-48C0-F8F1E7C10B1C")
IOutputStream : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IOutputStream*) Probe(PInterface pObj)
    {
        return (IOutputStream*)pObj->Probe(EIID_IOutputStream);
    }

    virtual CARAPI Close() = 0;

    virtual CARAPI Flush() = 0;

    virtual CARAPI Write(
        /* [in] */ _ELASTOS Byte Param0) = 0;

    virtual CARAPI WriteBuffer(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI WriteBufferEx(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

};

#endif // __INTERFACE_IOutputStream_DEFINED__
#ifndef __INTERFACE_IFileInputStream_DEFINED__
#define __INTERFACE_IFileInputStream_DEFINED__

CAR_INTERFACE("08A4723B-3552-B280-5190-80F1A35CB581")
IFileInputStream : public IInputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IFileInputStream*) Probe(PInterface pObj)
    {
        return (IFileInputStream*)pObj->Probe(EIID_IFileInputStream);
    }

    virtual CARAPI GetFileInterface(
        /* [out] */ IBasicFile ** ppParam0) = 0;

};

#endif // __INTERFACE_IFileInputStream_DEFINED__
#ifndef __INTERFACE_IFileOutputStream_DEFINED__
#define __INTERFACE_IFileOutputStream_DEFINED__

CAR_INTERFACE("0CAC573A-B552-B2A9-5190-80F1A35CB581")
IFileOutputStream : public IOutputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IFileOutputStream*) Probe(PInterface pObj)
    {
        return (IFileOutputStream*)pObj->Probe(EIID_IFileOutputStream);
    }

    virtual CARAPI GetFileInterface(
        /* [out] */ IBasicFile ** ppParam0) = 0;

};

#endif // __INTERFACE_IFileOutputStream_DEFINED__
#ifndef __INTERFACE_IDataInputStream_DEFINED__
#define __INTERFACE_IDataInputStream_DEFINED__

CAR_INTERFACE("AFFBC92F-2652-B280-5190-80F183AEC100")
IDataInputStream : public IInputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDataInputStream*) Probe(PInterface pObj)
    {
        return (IDataInputStream*)pObj->Probe(EIID_IDataInputStream);
    }

    virtual CARAPI ReadInt16(
        /* [out] */ _ELASTOS Int16 * pParam0) = 0;

    virtual CARAPI ReadInt32(
        /* [out] */ _ELASTOS Int32 * pParam0) = 0;

    virtual CARAPI ReadInt64(
        /* [out] */ _ELASTOS Int64 * pParam0) = 0;

    virtual CARAPI ReadFloat(
        /* [out] */ _ELASTOS Float * pParam0) = 0;

    virtual CARAPI ReadDouble(
        /* [out] */ _ELASTOS Double * pParam0) = 0;

    virtual CARAPI ReadChar8(
        /* [out] */ _ELASTOS Char8 * pParam0) = 0;

    virtual CARAPI ReadChar16(
        /* [out] */ _ELASTOS Char16 * pParam0) = 0;

    virtual CARAPI ReadBoolean(
        /* [out] */ _ELASTOS Boolean * pParam0) = 0;

    virtual CARAPI ReadEMuid(
        /* [out] */ _ELASTOS EMuid * pParam0) = 0;

    virtual CARAPI ReadEGuid(
        /* [out] */ _ELASTOS EGuid * pParam0) = 0;

    virtual CARAPI ReadECode(
        /* [out] */ _ELASTOS ECode * pParam0) = 0;

};

#endif // __INTERFACE_IDataInputStream_DEFINED__
#ifndef __INTERFACE_IDataOutputStream_DEFINED__
#define __INTERFACE_IDataOutputStream_DEFINED__

CAR_INTERFACE("BCCFB921-A652-B2A9-5190-80F1E3BCC100")
IDataOutputStream : public IOutputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IDataOutputStream*) Probe(PInterface pObj)
    {
        return (IDataOutputStream*)pObj->Probe(EIID_IDataOutputStream);
    }

    virtual CARAPI WriteInt16(
        /* [in] */ _ELASTOS Int16 Param0) = 0;

    virtual CARAPI WriteInt32(
        /* [in] */ _ELASTOS Int32 Param0) = 0;

    virtual CARAPI WriteInt64(
        /* [in] */ _ELASTOS Int64 Param0) = 0;

    virtual CARAPI WriteFloat(
        /* [in] */ _ELASTOS Float Param0) = 0;

    virtual CARAPI WriteDouble(
        /* [in] */ _ELASTOS Double Param0) = 0;

    virtual CARAPI WriteChar8(
        /* [in] */ _ELASTOS Char8 Param0) = 0;

    virtual CARAPI WriteChar16(
        /* [in] */ _ELASTOS Char16 Param0) = 0;

    virtual CARAPI WriteBoolean(
        /* [in] */ _ELASTOS Boolean Param0) = 0;

    virtual CARAPI WriteEMuid(
        /* [in] */ const _ELASTOS EMuid & Param0) = 0;

    virtual CARAPI WriteEGuid(
        /* [in] */ const _ELASTOS EGuid & Param0) = 0;

    virtual CARAPI WriteECode(
        /* [in] */ _ELASTOS ECode Param0) = 0;

};

#endif // __INTERFACE_IDataOutputStream_DEFINED__
#ifndef __INTERFACE_IStringInputStream_DEFINED__
#define __INTERFACE_IStringInputStream_DEFINED__

CAR_INTERFACE("31649541-9AD2-6B2D-D908-83F1E3CC9044")
IStringInputStream : public IInputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStringInputStream*) Probe(PInterface pObj)
    {
        return (IStringInputStream*)pObj->Probe(EIID_IStringInputStream);
    }

    virtual CARAPI ReadChar8(
        /* [out] */ _ELASTOS Char8 * pParam0) = 0;

    virtual CARAPI ReadChar8Array(
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Char8> * pParam0) = 0;

    virtual CARAPI ReadChar8ArrayEx(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Char8> * pParam2) = 0;

    virtual CARAPI ReadString(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_IStringInputStream_DEFINED__
#ifndef __INTERFACE_ITextInputStream_DEFINED__
#define __INTERFACE_ITextInputStream_DEFINED__

CAR_INTERFACE("C0059B33-7052-B280-5190-80F1A39C8318")
ITextInputStream : public IInputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ITextInputStream*) Probe(PInterface pObj)
    {
        return (ITextInputStream*)pObj->Probe(EIID_ITextInputStream);
    }

    virtual CARAPI GetEncoding(
        /* [out] */ _ELASTOS Encoding * pParam0) = 0;

    virtual CARAPI ReadChar(
        /* [out] */ _ELASTOS Char16 * pParam0) = 0;

    virtual CARAPI ReadCharArray(
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Char16> * pParam0) = 0;

    virtual CARAPI ReadCharArrayEx(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS BufferOf<_ELASTOS Char16> * pParam2) = 0;

    virtual CARAPI ReadString(
        /* [out] */ _ELASTOS StringBuf * pParam0) = 0;

};

#endif // __INTERFACE_ITextInputStream_DEFINED__
#ifndef __INTERFACE_ITextOutputStream_DEFINED__
#define __INTERFACE_ITextOutputStream_DEFINED__

CAR_INTERFACE("D1C18433-F052-B2A9-5190-80F1A39C8318")
ITextOutputStream : public IOutputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ITextOutputStream*) Probe(PInterface pObj)
    {
        return (ITextOutputStream*)pObj->Probe(EIID_ITextOutputStream);
    }

    virtual CARAPI GetEncoding(
        /* [out] */ _ELASTOS Encoding * pParam0) = 0;

    virtual CARAPI WriteChar(
        /* [in] */ _ELASTOS Char16 Param0) = 0;

    virtual CARAPI WriteCharArray(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Char16> & Param0,
        /* [out] */ _ELASTOS Int32 * pParam1) = 0;

    virtual CARAPI WriteCharArrayEx(
        /* [in] */ _ELASTOS Int32 Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Char16> & Param2,
        /* [out] */ _ELASTOS Int32 * pParam3) = 0;

    virtual CARAPI WriteString(
        /* [in] */ _ELASTOS String Param0) = 0;

};

#endif // __INTERFACE_ITextOutputStream_DEFINED__
#ifndef __INTERFACE_IGZipInputStream_DEFINED__
#define __INTERFACE_IGZipInputStream_DEFINED__

CAR_INTERFACE("32B76231-8412-2C11-6600-948D82048C1F")
IGZipInputStream : public IInputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGZipInputStream*) Probe(PInterface pObj)
    {
        return (IGZipInputStream*)pObj->Probe(EIID_IGZipInputStream);
    }


};

#endif // __INTERFACE_IGZipInputStream_DEFINED__
#ifndef __INTERFACE_IGZipOutputStream_DEFINED__
#define __INTERFACE_IGZipOutputStream_DEFINED__

CAR_INTERFACE("1DD8473B-8412-2C11-664C-958D82048C1F")
IGZipOutputStream : public IOutputStream
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IGZipOutputStream*) Probe(PInterface pObj)
    {
        return (IGZipOutputStream*)pObj->Probe(EIID_IGZipOutputStream);
    }


};

#endif // __INTERFACE_IGZipOutputStream_DEFINED__
#ifndef __INTERFACE_ICFileInputStreamClassObject_DEFINED__
#define __INTERFACE_ICFileInputStreamClassObject_DEFINED__

CAR_INTERFACE("DF936E35-8312-006A-65A3-200143CFD11F")
ICFileInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICFileInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICFileInputStreamClassObject*)pObj->Probe(EIID_ICFileInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithFileName(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithFile(
        /* [in] */ IBasicFile * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

};

#endif // __INTERFACE_ICFileInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICFileOutputStreamClassObject_DEFINED__
#define __INTERFACE_ICFileOutputStreamClassObject_DEFINED__

CAR_INTERFACE("69D37B3C-8312-536A-65A3-200143CFD11F")
ICFileOutputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICFileOutputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICFileOutputStreamClassObject*)pObj->Probe(EIID_ICFileOutputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithFileNameAppend(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Boolean Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

    virtual CARAPI CreateObjectWithFileAppend(
        /* [in] */ IBasicFile * pParam0,
        /* [in] */ _ELASTOS Boolean Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_ICFileOutputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICBufferedInputStreamClassObject_DEFINED__
#define __INTERFACE_ICBufferedInputStreamClassObject_DEFINED__

CAR_INTERFACE("4E68832D-0312-FA35-01CA-464102869EA3")
ICBufferedInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICBufferedInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICBufferedInputStreamClassObject*)pObj->Probe(EIID_ICBufferedInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IInputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithStreamDefaultBufferSize(
        /* [in] */ IInputStream * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_ICBufferedInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICBufferedOutputStreamClassObject_DEFINED__
#define __INTERFACE_ICBufferedOutputStreamClassObject_DEFINED__

CAR_INTERFACE("8FA58437-0312-FA35-A7CA-464102869EA3")
ICBufferedOutputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICBufferedOutputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICBufferedOutputStreamClassObject*)pObj->Probe(EIID_ICBufferedOutputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IOutputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithStreamDefaultBufferSize(
        /* [in] */ IOutputStream * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_ICBufferedOutputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICDataInputStreamClassObject_DEFINED__
#define __INTERFACE_ICDataInputStreamClassObject_DEFINED__

CAR_INTERFACE("EBF15830-8312-004C-65A3-200143CFD11F")
ICDataInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICDataInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICDataInputStreamClassObject*)pObj->Probe(EIID_ICDataInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IInputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

};

#endif // __INTERFACE_ICDataInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICDataOutputStreamClassObject_DEFINED__
#define __INTERFACE_ICDataOutputStreamClassObject_DEFINED__

CAR_INTERFACE("4E0E592D-8312-534C-65A3-200143CFD11F")
ICDataOutputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICDataOutputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICDataOutputStreamClassObject*)pObj->Probe(EIID_ICDataOutputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IOutputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

};

#endif // __INTERFACE_ICDataOutputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICByteArrayInputStreamClassObject_DEFINED__
#define __INTERFACE_ICByteArrayInputStreamClassObject_DEFINED__

CAR_INTERFACE("6AF27F32-8312-3736-5060-01281B050918")
ICByteArrayInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICByteArrayInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICByteArrayInputStreamClassObject*)pObj->Probe(EIID_ICByteArrayInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithBuffer(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithBufferOffsetLength(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [out] */ IInterface ** ppParam3) = 0;

};

#endif // __INTERFACE_ICByteArrayInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICByteArrayOutputStreamClassObject_DEFINED__
#define __INTERFACE_ICByteArrayOutputStreamClassObject_DEFINED__

CAR_INTERFACE("607B8029-8312-3736-5060-992A1B050918")
ICByteArrayOutputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICByteArrayOutputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICByteArrayOutputStreamClassObject*)pObj->Probe(EIID_ICByteArrayOutputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithBuffer(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithBufferOffsetLength(
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [out] */ IInterface ** ppParam3) = 0;

};

#endif // __INTERFACE_ICByteArrayOutputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICStringInputStreamClassObject_DEFINED__
#define __INTERFACE_ICStringInputStreamClassObject_DEFINED__

CAR_INTERFACE("5C785A29-0312-00D8-65A3-200143CFD11F")
ICStringInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICStringInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICStringInputStreamClassObject*)pObj->Probe(EIID_ICStringInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithString(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IInterface ** ppParam1) = 0;

};

#endif // __INTERFACE_ICStringInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICTextInputStreamClassObject_DEFINED__
#define __INTERFACE_ICTextInputStreamClassObject_DEFINED__

CAR_INTERFACE("2BA17626-8312-00E0-65A3-200143CFD11F")
ICTextInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICTextInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICTextInputStreamClassObject*)pObj->Probe(EIID_ICTextInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IInputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithStreamEncoding(
        /* [in] */ IInputStream * pParam0,
        /* [in] */ _ELASTOS Encoding Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_ICTextInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICTextOutputStreamClassObject_DEFINED__
#define __INTERFACE_ICTextOutputStreamClassObject_DEFINED__

CAR_INTERFACE("FA507735-8312-53E0-65A3-200143CFD11F")
ICTextOutputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICTextOutputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICTextOutputStreamClassObject*)pObj->Probe(EIID_ICTextOutputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IOutputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithStreamEncoding(
        /* [in] */ IOutputStream * pParam0,
        /* [in] */ _ELASTOS Encoding Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

};

#endif // __INTERFACE_ICTextOutputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICGZipInputStreamClassObject_DEFINED__
#define __INTERFACE_ICGZipInputStreamClassObject_DEFINED__

CAR_INTERFACE("BE71A22C-0312-2308-58CC-00281B050918")
ICGZipInputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICGZipInputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICGZipInputStreamClassObject*)pObj->Probe(EIID_ICGZipInputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IInputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithStreamWindowBits(
        /* [in] */ IInputStream * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ IInterface ** ppParam2) = 0;

    virtual CARAPI CreateObjectWithStreamWindowBitsDictionary(
        /* [in] */ IInputStream * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param2,
        /* [out] */ IInterface ** ppParam3) = 0;

};

#endif // __INTERFACE_ICGZipInputStreamClassObject_DEFINED__
#ifndef __INTERFACE_ICGZipOutputStreamClassObject_DEFINED__
#define __INTERFACE_ICGZipOutputStreamClassObject_DEFINED__

CAR_INTERFACE("484EED30-0312-2308-58CC-982A1B050918")
ICGZipOutputStreamClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ICGZipOutputStreamClassObject*) Probe(PInterface pObj)
    {
        return (ICGZipOutputStreamClassObject*)pObj->Probe(EIID_ICGZipOutputStreamClassObject);
    }

    virtual CARAPI CreateObjectWithStream(
        /* [in] */ IOutputStream * pParam0,
        /* [out] */ IInterface ** ppParam1) = 0;

    virtual CARAPI CreateObjectWithStreamWindowBitsCompressLevelMemoryUsageLevelStrategy(
        /* [in] */ IOutputStream * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ CompressStrategy Param4,
        /* [out] */ IInterface ** ppParam5) = 0;

    virtual CARAPI CreateObjectWithStreamWindowBitsCompressLevelMemoryUsageLevelStrategyDictionary(
        /* [in] */ IOutputStream * pParam0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [in] */ _ELASTOS Int32 Param2,
        /* [in] */ _ELASTOS Int32 Param3,
        /* [in] */ CompressStrategy Param4,
        /* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param5,
        /* [out] */ IInterface ** ppParam6) = 0;

};

#endif // __INTERFACE_ICGZipOutputStreamClassObject_DEFINED__
#ifndef __INTERFACE_IVerifyFile_DEFINED__
#define __INTERFACE_IVerifyFile_DEFINED__

CAR_INTERFACE("D7BD162B-7852-2916-7854-FB119E450A1E")
IVerifyFile : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IVerifyFile*) Probe(PInterface pObj)
    {
        return (IVerifyFile*)pObj->Probe(EIID_IVerifyFile);
    }

    virtual CARAPI VerifyFile(
        /* [in] */ _ELASTOS String Param0,
        /* [in] */ _ELASTOS Int32 Param1,
        /* [out] */ _ELASTOS Int32 * pParam2) = 0;

};

#endif // __INTERFACE_IVerifyFile_DEFINED__
#ifndef __INTERFACE_IScheme_DEFINED__
#define __INTERFACE_IScheme_DEFINED__

CAR_INTERFACE("1394134E-0712-3B51-7F6C-812CE8732300")
IScheme : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IScheme*) Probe(PInterface pObj)
    {
        return (IScheme*)pObj->Probe(EIID_IScheme);
    }

    virtual CARAPI Instantiate(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ PInterface * ppParam1) = 0;

};

#endif // __INTERFACE_IScheme_DEFINED__
#ifndef __INTERFACE_IStream_DEFINED__
#define __INTERFACE_IStream_DEFINED__

CAR_INTERFACE("A96F0812-7712-28D7-09FF-1277D72809FF")
IStream : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStream*) Probe(PInterface pObj)
    {
        return (IStream*)pObj->Probe(EIID_IStream);
    }


};

#endif // __INTERFACE_IStream_DEFINED__
#ifndef __INTERFACE_IStorage_DEFINED__
#define __INTERFACE_IStorage_DEFINED__

CAR_INTERFACE("D2FA162C-8712-F91B-49A8-40F1C388AA6B")
IStorage : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IStorage*) Probe(PInterface pObj)
    {
        return (IStorage*)pObj->Probe(EIID_IStorage);
    }

    virtual CARAPI Add(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI Delete(
        /* [in] */ _ELASTOS String Param0) = 0;

    virtual CARAPI Find(
        /* [in] */ _ELASTOS String Param0,
        /* [out] */ IFile ** ppParam1) = 0;

};

#endif // __INTERFACE_IStorage_DEFINED__
#ifndef __INTERFACE_IFile_DEFINED__
#define __INTERFACE_IFile_DEFINED__

CAR_INTERFACE("1DE80602-C3D2-E8BE-2F3D-EC8BFED2C3BE")
IFile : public IInterface
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(IFile*) Probe(PInterface pObj)
    {
        return (IFile*)pObj->Probe(EIID_IFile);
    }


};

#endif // __INTERFACE_IFile_DEFINED__
#ifndef __INTERFACE_ITAppletClassObject_DEFINED__
#define __INTERFACE_ITAppletClassObject_DEFINED__

CAR_INTERFACE("7FED543A-0752-7A26-8EFE-B87414048B1B")
ITAppletClassObject : public IClassObject
{
    virtual CARAPI_(PInterface) Probe(
            /* [in] */ _ELASTOS REIID riid) = 0;

    static CARAPI_(ITAppletClassObject*) Probe(PInterface pObj)
    {
        return (ITAppletClassObject*)pObj->Probe(EIID_ITAppletClassObject);
    }

    virtual CARAPI CreateObjectWithDefaultCtor(
        /* [out] */ IInterface ** ppParam0) = 0;

};

#endif // __INTERFACE_ITAppletClassObject_DEFINED__

interface _ITAppletCallbackTrigger{
    virtual CARAPI RequestToFinish() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI RequestToFinishWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingRequestToFinish() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingRequestToFinishWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Started() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI StartedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingStarted() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingStartedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI MainCompleted(_ELASTOS ECode Param0) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI MainCompletedWithPriority(_ELASTOS Int32 cFlags, _ELASTOS ECode Param0) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingMainCompleted(_ELASTOS ECode Param0) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingMainCompletedWithPriority(_ELASTOS Int32 cFlags, _ELASTOS ECode Param0) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI LayoutReady() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI LayoutReadyWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingLayoutReady() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingLayoutReadyWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Finishing() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI FinishingWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingFinishing() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingFinishingWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Activated() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI ActivatedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingActivated() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingActivatedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Deactivated() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI DeactivatedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingDeactivated() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingDeactivatedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Snoozed() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI SnoozedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingSnoozed() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingSnoozedWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Wakenup() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI WakenupWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingWakenup() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingWakenupWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI Idling() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI IdlingWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingIdling() { return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingIdlingWithPriority(_ELASTOS Int32 cFlags) { return E_NOT_IMPLEMENTED; }

};

#ifdef _DEBUG
interface _ITApplet_ForCallbackKeywordChecking{
    virtual CARAPI RequestToFinish() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI RequestToFinishWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingRequestToFinish() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingRequestToFinishWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Started() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI StartedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingStarted() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingStartedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI MainCompleted(_ELASTOS ECode Param0) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI MainCompletedWithPriority(_ELASTOS Int32 cFlags, _ELASTOS ECode Param0) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingMainCompleted(_ELASTOS ECode Param0) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingMainCompletedWithPriority(_ELASTOS Int32 cFlags, _ELASTOS ECode Param0) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI LayoutReady() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI LayoutReadyWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingLayoutReady() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingLayoutReadyWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Finishing() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI FinishingWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingFinishing() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingFinishingWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Activated() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI ActivatedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingActivated() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingActivatedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Deactivated() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI DeactivatedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingDeactivated() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingDeactivatedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Snoozed() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI SnoozedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingSnoozed() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingSnoozedWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Wakenup() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI WakenupWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingWakenup() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingWakenupWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI Idling() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI IdlingWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingIdling() { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

    virtual CARAPI UpdatingIdlingWithPriority(_ELASTOS Int32 cFlags) { assert(0 && "NOT Implemented!!!"); return E_NOT_IMPLEMENTED; }

};
#endif // _DEBUG




