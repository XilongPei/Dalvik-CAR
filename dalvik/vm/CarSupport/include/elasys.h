#ifndef __CAR_ELASTOSCORE_H__
#define __CAR_ELASTOSCORE_H__

#ifndef _NO_INCLIST
#include <elastos.h>
#endif // !_NO_INCLIST
#ifdef _UNDEFDLLEXP
#define DLLEXP
#else
#define DLLEXP __declspec(dllimport)
#endif

EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_AObjectEx;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_AObjectContainer;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_AObjectContainerClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CDeviceEventDispatcher;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CFileInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CFileInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CFileOutputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CFileOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CBufferedInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CBufferedInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CBufferedOutputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CBufferedOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CDataInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CDataInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CDataOutputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CDataOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CByteArrayInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CByteArrayInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CByteArrayOutputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CByteArrayOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CStringInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CStringInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CTextInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CTextInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CTextOutputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CTextOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CGZipInputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CGZipInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CGZipOutputStream;
EXTERN_C DLLEXP const _ELASTOS ClassID ECLSID_CGZipOutputStreamClassObject;

EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IMutex;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICondition;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IEvent;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IReaderWriterLock;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDeviceDriver;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IObjectEx;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IObjectContainer;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICallbackParcel;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICallbackRendezvous;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICallbackSink;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IContext;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IAObjectContainerClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IAppletHosting;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IHostingManager;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IKernel;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ISharedMemory;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IProcess;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IMemoryTrace;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IThread;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IThreadContext;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IModule;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IObjectEnumerator;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStringEnumerator;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDiskFileSystem;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IAbsoluteIO;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IBasicFile;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IBasicDirectory;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IBasicFileSystem;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IFileMonitor;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDiskManager;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ILocaleInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDeviceEventManager;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDeviceEventHandler;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDeviceEventDispatcher;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IActiveTimer;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ISocket;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ISocketEx;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ISocketService;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDataTypeInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ILocalPtrInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IEnumInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IEnumItemInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICarArrayInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStringBufInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICppVectorInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStructInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IFieldInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IInterfaceInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IFunctionInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IMethodInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IParamInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ITypeAliasInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IArgumentList;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IVariable;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IVariableOfCarArray;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IVariableOfStringBuf;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IVariableOfStruct;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICarArraySetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICarArrayGetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStringBufSetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStringBufGetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStructSetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStructGetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICppVectorSetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICppVectorGetter;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IModuleInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IConstantInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IClassInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IConstructorInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICallbackMethodInfo;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDelegateProxy;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICallbackInvocation;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICallbackArgumentList;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IConstraint;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IMediaObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDrmManage;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IInputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IOutputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IFileInputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IFileOutputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDataInputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IDataOutputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStringInputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ITextInputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ITextOutputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IGZipInputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IGZipOutputStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICFileInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICFileOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICBufferedInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICBufferedOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICDataInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICDataOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICByteArrayInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICByteArrayOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICStringInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICTextInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICTextOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICGZipInputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_ICGZipOutputStreamClassObject;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IVerifyFile;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IScheme;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStream;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IStorage;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_IFile;

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
interface IAppletHosting;
interface IHostingManager;
interface IKernel;
interface ISharedMemory;
interface IProcess;
interface IMemoryTrace;
interface IThread;
interface IThreadContext;
interface IModule;
interface IObjectEnumerator;
interface IStringEnumerator;
interface IDiskFileSystem;
interface IAbsoluteIO;
interface IBasicFile;
interface IBasicDirectory;
interface IBasicFileSystem;
interface IFileMonitor;
interface IDiskManager;
interface ILocaleInfo;
interface IDeviceEventManager;
interface IDeviceEventHandler;
interface IDeviceEventDispatcher;
interface IActiveTimer;
interface ISocket;
interface ISocketEx;
interface ISocketService;
interface IDataTypeInfo;
interface ILocalPtrInfo;
interface IEnumInfo;
interface IEnumItemInfo;
interface ICarArrayInfo;
interface IStringBufInfo;
interface ICppVectorInfo;
interface IStructInfo;
interface IFieldInfo;
interface IInterfaceInfo;
interface IFunctionInfo;
interface IMethodInfo;
interface IParamInfo;
interface ITypeAliasInfo;
interface IArgumentList;
interface IVariable;
interface IVariableOfCarArray;
interface IVariableOfStringBuf;
interface IVariableOfStruct;
interface ICarArraySetter;
interface ICarArrayGetter;
interface IStringBufSetter;
interface IStringBufGetter;
interface IStructSetter;
interface IStructGetter;
interface ICppVectorSetter;
interface ICppVectorGetter;
interface IModuleInfo;
interface IConstantInfo;
interface IClassInfo;
interface IConstructorInfo;
interface ICallbackMethodInfo;
interface IDelegateProxy;
interface ICallbackInvocation;
interface ICallbackArgumentList;
interface IConstraint;
interface IMediaObject;
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


#ifndef __ENUM_WAITRESULT__
#define __ENUM_WAITRESULT__

enum {
    WaitResult_OK = 0x00000000,
    WaitResult_Interrupted = 0x00000001,
    WaitResult_TimedOut = 0x00000002,
};
typedef _ELASTOS Int32 WaitResult;

#endif //__ENUM_WAITRESULT__


#ifndef __ENUM_MEMORYPROTECTION__
#define __ENUM_MEMORYPROTECTION__

enum {
    MemoryProtection_Read = 0x00000001,
    MemoryProtection_Write = 0x00000002,
    MemoryProtection_Exec = 0x00000004,
    MemoryProtection_RW = 0x00000003,
    MemoryProtection_RX = 0x00000005,
    MemoryProtection_RWX = 0x00000007,
};
typedef _ELASTOS Int32 MemoryProtection;

#endif //__ENUM_MEMORYPROTECTION__


#ifndef __ENUM_IOREMAPFLAG__
#define __ENUM_IOREMAPFLAG__

enum {
    IoRemapFlag_Direct = 0x00000008,
    IoRemapFlag_BufferedWrite = 0x00000018,
};
typedef _ELASTOS Int32 IoRemapFlag;

#endif //__ENUM_IOREMAPFLAG__


#ifndef __ENUM_MEMORYMAP__
#define __ENUM_MEMORYMAP__

enum {
    MemoryMap_Private = 0x00000001,
    MemoryMap_Shared = 0x00000002,
    MemoryMap_Fixed = 0x00000004,
    MemoryMap_UpGrow = 0x00000010,
    MemoryMap_DownGrow = 0x00000020,
};
typedef _ELASTOS Int32 MemoryMap;

#endif //__ENUM_MEMORYMAP__


#ifndef __ENUM_SYSTEMEVENT__
#define __ENUM_SYSTEMEVENT__

enum {
    SystemEvent_Break = 0x00000001,
    SystemEvent_SessionEnd = 0x00000002,
    SystemEvent_TimeChanged = 0x00000004,
    SystemEvent_LowMemory = 0x00000008,
    SystemEvent_CriticallyLowMemory = 0x00000010,
    SystemEvent_Shutdown = 0x00000020,
};
typedef _ELASTOS Int32 SystemEvent;

#endif //__ENUM_SYSTEMEVENT__


#ifndef __ENUM_THREADCREATIONFLAG__
#define __ENUM_THREADCREATIONFLAG__

enum {
    ThreadCreationFlag_Started = 0,
    ThreadCreationFlag_Unstarted = 4,
};
typedef _ELASTOS Int32 ThreadCreationFlag;

#endif //__ENUM_THREADCREATIONFLAG__


#ifndef __ENUM_THREADLOCALSLOTTYPE__
#define __ENUM_THREADLOCALSLOTTYPE__

enum {
    ThreadLocalSlotType_Free = 0x00000000,
    ThreadLocalSlotType_Value = 0x00000001,
    ThreadLocalSlotType_Mem = 0x00000002,
    ThreadLocalSlotType_Obj = 0x00000003,
};
typedef _ELASTOS Int32 ThreadLocalSlotType;

#endif //__ENUM_THREADLOCALSLOTTYPE__


#ifndef __ENUM_THREADEVENT__
#define __ENUM_THREADEVENT__

enum {
    ThreadEvent_RequestToQuit = 0x00000001,
    ThreadEvent_ForceToQuit = 0x00000002,
    ThreadEvent_RequestToCancelOperation = 0x00000003,
    ThreadEvent_RequestToInterrupt = 0x00000004,
    ThreadEvent_NewArrival = 0xffffffff,
    ThreadEvent_Interrupt = 0xfffffffe,
};
typedef _ELASTOS Int32 ThreadEvent;

#endif //__ENUM_THREADEVENT__


#ifndef __ENUM_CALLBACKPRIORITY__
#define __ENUM_CALLBACKPRIORITY__

enum {
    CallbackPriority_Highest = 0x00000000,
    CallbackPriority_AboveNormal = 0x00000007,
    CallbackPriority_Normal = 0x00000010,
    CallbackPriority_BelowNormal = 0x00000017,
    CallbackPriority_Lowest = 0x0000001f,
};
typedef _ELASTOS Int32 CallbackPriority;

#endif //__ENUM_CALLBACKPRIORITY__


#ifndef __ENUM_CALLBACKCONTEXTSTATUS__
#define __ENUM_CALLBACKCONTEXTSTATUS__

enum {
    CallbackContextStatus_Created = 0x00000001,
    CallbackContextStatus_Idling = 2,
    CallbackContextStatus_Working = 3,
    CallbackContextStatus_Finishing = 4,
};
typedef _ELASTOS Int32 CallbackContextStatus;

#endif //__ENUM_CALLBACKCONTEXTSTATUS__


#ifndef __ENUM_CALLBACKCONTEXTFINISH__
#define __ENUM_CALLBACKCONTEXTFINISH__

enum {
    CallbackContextFinish_Nice = 0x00000001,
    CallbackContextFinish_ASAP = 2,
};
typedef _ELASTOS Int32 CallbackContextFinish;

#endif //__ENUM_CALLBACKCONTEXTFINISH__


#ifndef __ENUM_THREADPRIORITYRANK__
#define __ENUM_THREADPRIORITYRANK__

enum {
    ThreadPriorityRank_Idle = 0x00000001,
    ThreadPriorityRank_Normal = 0x00000002,
    ThreadPriorityRank_SoftRealTime = 0x00000003,
    ThreadPriorityRank_HardRealTime = 0x00000004,
};
typedef _ELASTOS Int32 ThreadPriorityRank;

#endif //__ENUM_THREADPRIORITYRANK__


#ifndef __ENUM_THREADPRIORITY__
#define __ENUM_THREADPRIORITY__

enum {
    ThreadPriority_Lowest = 0x00000000,
    ThreadPriority_BelowNormal = 0x000000ff,
    ThreadPriority_Normal = 0x000001ff,
    ThreadPriority_AboveNormal = 0x000002ff,
    ThreadPriority_Highest = 0x000003ff,
};
typedef _ELASTOS Int32 ThreadPriority;

#endif //__ENUM_THREADPRIORITY__


#ifndef __ENUM_THREADSTATE__
#define __ENUM_THREADSTATE__

enum {
    ThreadState_Running = 0x00000000,
    ThreadState_Sleeping = 0x00000001,
    ThreadState_InterruptibleSleeping = 0x00000003,
    ThreadState_Suspended = 0x00000004,
    ThreadState_SleepingSuspended = 0x00000005,
    ThreadState_Finished = 0x00000010,
    ThreadState_Unstarted = 0x00000020,
    ThreadState_DebugSuspended = 0x00000080,
};
typedef _ELASTOS Int32 ThreadState;

#endif //__ENUM_THREADSTATE__


#ifndef __ENUM_FILETYPE__
#define __ENUM_FILETYPE__

enum {
    FileType_RegularFile = 0,
    FileType_Directory = 1,
};
typedef _ELASTOS Int32 FileType;

#endif //__ENUM_FILETYPE__


#ifndef __ENUM_FILEACCESSMODE__
#define __ENUM_FILEACCESSMODE__

enum {
    FileAccessMode_Read = 0,
    FileAccessMode_Write = 1,
    FileAccessMode_ReadWrite = 2,
};
typedef _ELASTOS Int32 FileAccessMode;

#endif //__ENUM_FILEACCESSMODE__


#ifndef __ENUM_FILESHAREMODE__
#define __ENUM_FILESHAREMODE__

enum {
    FileShareMode_Deny = 0,
    FileShareMode_Read = 1,
    FileShareMode_Write = 2,
};
typedef _ELASTOS Int32 FileShareMode;

#endif //__ENUM_FILESHAREMODE__


#ifndef __ENUM_FATTYPE__
#define __ENUM_FATTYPE__

enum {
    FatType_FAT12 = 0,
    FatType_FAT16 = 1,
    FatType_FAT32 = 2,
    FatType_Unknown = 3,
};
typedef _ELASTOS Int32 FatType;

#endif //__ENUM_FATTYPE__


#ifndef __ENUM_DISKTYPE__
#define __ENUM_DISKTYPE__

enum {
    DiskType_AllDisk = 0,
    DiskType_Bootmods = 1,
    DiskType_MemDisk = 2,
    DiskType_VfsDisk = 3,
    DiskType_HardDisk = 4,
    DiskType_FlashDisk = 5,
    DiskType_Removable = 6,
    DiskType_MaxValue = 7,
};
typedef _ELASTOS Int32 DiskType;

#endif //__ENUM_DISKTYPE__


#ifndef __ENUM_LOCALETYPE__
#define __ENUM_LOCALETYPE__

enum {
    LocaleType_TimeZone = 0,
    LocaleType_Language = 1,
    LocaleType_Country = 2,
    LocaleType_Encoding = 3,
    LocaleType_MaxValue = 4,
};
typedef _ELASTOS Int32 LocaleType;

#endif //__ENUM_LOCALETYPE__


#ifndef __ENUM_PIXELFORMAT__
#define __ENUM_PIXELFORMAT__

enum {
    PixelFormat_Unknown = 0x00000000,
    PixelFormat_A8 = 0x00118001,
    PixelFormat_RGBT555 = 0x00200782,
    PixelFormat_RGB565 = 0x00200803,
    PixelFormat_RGBT666 = 0x00400904,
    PixelFormat_RGB24 = 0x00400c05,
    PixelFormat_ARGB = 0x00418c06,
    PixelFormat_YUV422 = 0x00000007,
    PixelFormat_YUV420 = 0x00000008,
    PixelFormat_A1 = 0x00111009,
    PixelFormat_ARGB4444 = 0x0021460a,
    PixelFormat_LUT4 = 0x40010209,
    PixelFormat_LUT5 = 0x4011028a,
    PixelFormat_LUT8 = 0x4011040b,
};
typedef _ELASTOS Int32 PixelFormat;

#endif //__ENUM_PIXELFORMAT__


#ifndef __ENUM_INPUTMASK__
#define __ENUM_INPUTMASK__

enum {
    InputMask_None = 0x00000000,
    InputMask_Ctrl = 0x00000001,
    InputMask_Alt = 0x00000002,
    InputMask_Shift = 0x00000004,
    InputMask_Num = 0x00020000,
    InputMask_Caps = 0x00040000,
    InputMask_LButton = 0x00000020,
    InputMask_RButton = 0x00000040,
    InputMask_MButton = 0x00000080,
    InputMask_KeyChar = 0x00000010,
    InputMask_Substitute = 0x00000100,
};
typedef _ELASTOS Int32 InputMask;

#endif //__ENUM_INPUTMASK__


#ifndef __ENUM_CARDATATYPE__
#define __ENUM_CARDATATYPE__

enum {
    CarDataType_Int16 = 1,
    CarDataType_Int32 = 2,
    CarDataType_Int64 = 3,
    CarDataType_Byte = 4,
    CarDataType_Float = 5,
    CarDataType_Double = 6,
    CarDataType_Char8 = 7,
    CarDataType_Char16 = 8,
    CarDataType_String = 9,
    CarDataType_Boolean = 10,
    CarDataType_EMuid = 11,
    CarDataType_EGuid = 12,
    CarDataType_ECode = 13,
    CarDataType_LocalPtr = 14,
    CarDataType_LocalType = 15,
    CarDataType_Enum = 16,
    CarDataType_StringBuf = 17,
    CarDataType_ArrayOf = 18,
    CarDataType_BufferOf = 19,
    CarDataType_MemoryBuf = 20,
    CarDataType_CppVector = 21,
    CarDataType_Struct = 22,
    CarDataType_Interface = 23,
};
typedef _ELASTOS Int32 CarDataType;

#endif //__ENUM_CARDATATYPE__


#ifndef __ENUM_PARAMIOATTRIBUTE__
#define __ENUM_PARAMIOATTRIBUTE__

enum {
    ParamIOAttribute_In = 0,
    ParamIOAttribute_CalleeAllocOut = 1,
    ParamIOAttribute_CallerAllocOut = 2,
};
typedef _ELASTOS Int32 ParamIOAttribute;

#endif //__ENUM_PARAMIOATTRIBUTE__


#ifndef __ENUM_THREADINGMODEL__
#define __ENUM_THREADINGMODEL__

enum {
    ThreadingModel_Sequenced = 1,
    ThreadingModel_Synchronized = 2,
    ThreadingModel_ThreadSafe = 3,
    ThreadingModel_Naked = 4,
};
typedef _ELASTOS Int32 ThreadingModel;

#endif //__ENUM_THREADINGMODEL__


#ifndef __ENUM_DRMMEDIATYPE__
#define __ENUM_DRMMEDIATYPE__

enum {
    DrmMediaType_Right = 0x00000001,
    DrmMediaType_DCF = 2,
    DrmMediaType_Message = 3,
    DrmMediaType_Normal = 4,
};
typedef _ELASTOS Int32 DrmMediaType;

#endif //__ENUM_DRMMEDIATYPE__


#ifndef __ENUM_DRMACTIONTYPE__
#define __ENUM_DRMACTIONTYPE__

enum {
    DrmActionType_Play = 0x00000001,
    DrmActionType_Display = 2,
    DrmActionType_Execute = 3,
    DrmActionType_Print = 4,
};
typedef _ELASTOS Int32 DrmActionType;

#endif //__ENUM_DRMACTIONTYPE__


#ifndef __ENUM_COMPRESSSTRATEGY__
#define __ENUM_COMPRESSSTRATEGY__

enum {
    CompressStrategy_Default = 0,
    CompressStrategy_Filtered = 1,
    CompressStrategy_Huffman = 2,
    CompressStrategy_RLE = 3,
    CompressStrategy_Fixed = 4,
};
typedef _ELASTOS Int32 CompressStrategy;

#endif //__ENUM_COMPRESSSTRATEGY__

typedef _ELASTOS Int32 ExitCode;
typedef _ELASTOS Int32 QuitCode;
typedef _ELASTOS Int32 ProcessId;
typedef _ELASTOS Int32 ThreadId;
typedef _ELASTOS Handle32 Color;
typedef _ELASTOS PVoid LocalPtr;

struct FileSystemStat {
    FatType fatType;
    _ELASTOS Int32 clusterSize;
    _ELASTOS Int32 totalClusters;
    _ELASTOS Int32 freeClusters;
};

typedef struct FileSystemStat FileSystemStat;


struct TimeZoneInfo {
    _ELASTOS Int32 bias;
    _ELASTOS Char8 standardName[32];
    struct _ELASTOS DateTime standardDate;
    _ELASTOS Int32 standardBias;
    _ELASTOS Char8 daylightName[32];
    struct _ELASTOS DateTime daylightDate;
    _ELASTOS Int32 daylightBias;
};

typedef struct TimeZoneInfo TimeZoneInfo;


struct Rectangle {
    _ELASTOS Int32 x;
    _ELASTOS Int32 y;
    _ELASTOS Int32 width;
    _ELASTOS Int32 height;
};

typedef struct Rectangle Rectangle;


struct Region {
    _ELASTOS Int32 left;
    _ELASTOS Int32 top;
    _ELASTOS Int32 right;
    _ELASTOS Int32 bottom;
};

typedef struct Region Region;


struct Point {
    _ELASTOS Int32 x;
    _ELASTOS Int32 y;
};

typedef struct Point Point;


struct Pixel {
    _ELASTOS Byte b;
    _ELASTOS Byte g;
    _ELASTOS Byte r;
    _ELASTOS Byte a;
};

typedef struct Pixel Pixel;


struct IPv4Address {
    _ELASTOS Byte octet[4];
};

typedef struct IPv4Address IPv4Address;


struct SocketAddr {
    _ELASTOS Byte length;
    _ELASTOS Byte family;
    _ELASTOS Int16 port;
    struct IPv4Address ipAddr;
};

typedef struct SocketAddr SocketAddr;


struct SocketTime {
    _ELASTOS Second32 time_sec;
    _ELASTOS Microsecond32 time_usec;
};

typedef struct SocketTime SocketTime;


#ifdef __cplusplus
#include <_ElastosCore.h>






EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class AObjectEx
{
public:
    INLINE static _ELASTOS ECode Attach(/* [in] */ IInterface* pObject)
    {
        return _CObject_AttachAspect(pObject, ECLSID_AObjectEx);
    }

    INLINE static _ELASTOS ECode Detach(/* [in] */ IInterface* pObject)
    {
        return _CObject_DetachAspect(pObject, ECLSID_AObjectEx);
    }
};


EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class AObjectContainer
{
public:
    INLINE static _ELASTOS ECode Attach(/* [in] */ IInterface* pObject)
    {
        return _CObject_AttachAspect(pObject, ECLSID_AObjectContainer);
    }

    INLINE static _ELASTOS ECode Detach(/* [in] */ IInterface* pObject)
    {
        return _CObject_DetachAspect(pObject, ECLSID_AObjectContainer);
    }
};




















EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CDeviceEventDispatcher
{
public:

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* pContext,/* [out] */ IDeviceEventDispatcher** ppIDeviceEventDispatcher)
    {
        return _CObject_CreateInstance(ECLSID_CDeviceEventDispatcher,pContext,EIID_IDeviceEventDispatcher,(IInterface**)ppIDeviceEventDispatcher);
    }


    static _ELASTOS ECode New(/* [out] */ IDeviceEventDispatcher** ppIDeviceEventDispatcher)
    {
        return _CObject_CreateInstance(ECLSID_CDeviceEventDispatcher,CTX_SAME_DOMAIN,EIID_IDeviceEventDispatcher,(PInterface*)ppIDeviceEventDispatcher);
    }
};




EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CFileInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS String Param0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICFileInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CFileInputStream, __pContext, 
                EIID_ICFileInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithFileName(Param0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IBasicFile * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICFileInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CFileInputStream, __pContext, 
                EIID_ICFileInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithFile(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS String Param0,/* [out] */ IFileInputStream** __ppIFileInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIFileInputStream = IFileInputStream::Probe(__pNewObj);
        if (*__ppIFileInputStream) (*__ppIFileInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ _ELASTOS String Param0,
/* [out] */ IFileInputStream** __ppIFileInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, __ppIFileInputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IBasicFile * pParam0,/* [out] */ IFileInputStream** __ppIFileInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIFileInputStream = IFileInputStream::Probe(__pNewObj);
        if (*__ppIFileInputStream) (*__ppIFileInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IBasicFile * pParam0,
/* [out] */ IFileInputStream** __ppIFileInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIFileInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CFileOutputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS String Param0,/* [in] */ _ELASTOS Boolean Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICFileOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CFileOutputStream, __pContext, 
                EIID_ICFileOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithFileNameAppend(Param0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IBasicFile * pParam0,/* [in] */ _ELASTOS Boolean Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICFileOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CFileOutputStream, __pContext, 
                EIID_ICFileOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithFileAppend(pParam0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS String Param0,/* [in] */ _ELASTOS Boolean Param1,/* [out] */ IFileOutputStream** __ppIFileOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIFileOutputStream = IFileOutputStream::Probe(__pNewObj);
        if (*__ppIFileOutputStream) (*__ppIFileOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ _ELASTOS String Param0,
/* [in] */ _ELASTOS Boolean Param1,
/* [out] */ IFileOutputStream** __ppIFileOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, Param1, __ppIFileOutputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IBasicFile * pParam0,/* [in] */ _ELASTOS Boolean Param1,/* [out] */ IFileOutputStream** __ppIFileOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIFileOutputStream = IFileOutputStream::Probe(__pNewObj);
        if (*__ppIFileOutputStream) (*__ppIFileOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IBasicFile * pParam0,
/* [in] */ _ELASTOS Boolean Param1,
/* [out] */ IFileOutputStream** __ppIFileOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, __ppIFileOutputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CBufferedInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICBufferedInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CBufferedInputStream, __pContext, 
                EIID_ICBufferedInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICBufferedInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CBufferedInputStream, __pContext, 
                EIID_ICBufferedInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamDefaultBufferSize(pParam0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IInputStream** __ppIInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIInputStream = IInputStream::Probe(__pNewObj);
        if (*__ppIInputStream) (*__ppIInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [out] */ IInputStream** __ppIInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIInputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [out] */ IInputStream** __ppIInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIInputStream = IInputStream::Probe(__pNewObj);
        if (*__ppIInputStream) (*__ppIInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [in] */ _ELASTOS Int32 Param1,
/* [out] */ IInputStream** __ppIInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, __ppIInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CBufferedOutputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICBufferedOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CBufferedOutputStream, __pContext, 
                EIID_ICBufferedOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICBufferedOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CBufferedOutputStream, __pContext, 
                EIID_ICBufferedOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamDefaultBufferSize(pParam0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IOutputStream** __ppIOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIOutputStream = IOutputStream::Probe(__pNewObj);
        if (*__ppIOutputStream) (*__ppIOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [out] */ IOutputStream** __ppIOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIOutputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [out] */ IOutputStream** __ppIOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIOutputStream = IOutputStream::Probe(__pNewObj);
        if (*__ppIOutputStream) (*__ppIOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [in] */ _ELASTOS Int32 Param1,
/* [out] */ IOutputStream** __ppIOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, __ppIOutputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CDataInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICDataInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CDataInputStream, __pContext, 
                EIID_ICDataInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IDataInputStream** __ppIDataInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIDataInputStream = IDataInputStream::Probe(__pNewObj);
        if (*__ppIDataInputStream) (*__ppIDataInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [out] */ IDataInputStream** __ppIDataInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIDataInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CDataOutputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICDataOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CDataOutputStream, __pContext, 
                EIID_ICDataOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IDataOutputStream** __ppIDataOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIDataOutputStream = IDataOutputStream::Probe(__pNewObj);
        if (*__ppIDataOutputStream) (*__ppIDataOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [out] */ IDataOutputStream** __ppIDataOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIDataOutputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CByteArrayInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICByteArrayInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CByteArrayInputStream, __pContext, 
                EIID_ICByteArrayInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithBuffer(Param0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICByteArrayInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CByteArrayInputStream, __pContext, 
                EIID_ICByteArrayInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithBufferOffsetLength(Param0, Param1, Param2, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [out] */ IInputStream** __ppIInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIInputStream = IInputStream::Probe(__pNewObj);
        if (*__ppIInputStream) (*__ppIInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
/* [out] */ IInputStream** __ppIInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, __ppIInputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [out] */ IInputStream** __ppIInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, Param1, Param2, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIInputStream = IInputStream::Probe(__pNewObj);
        if (*__ppIInputStream) (*__ppIInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
/* [in] */ _ELASTOS Int32 Param1,
/* [in] */ _ELASTOS Int32 Param2,
/* [out] */ IInputStream** __ppIInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, Param1, Param2, __ppIInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CByteArrayOutputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICByteArrayOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CByteArrayOutputStream, __pContext, 
                EIID_ICByteArrayOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithBuffer(Param0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICByteArrayOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CByteArrayOutputStream, __pContext, 
                EIID_ICByteArrayOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithBufferOffsetLength(Param0, Param1, Param2, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [out] */ IOutputStream** __ppIOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIOutputStream = IOutputStream::Probe(__pNewObj);
        if (*__ppIOutputStream) (*__ppIOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
/* [out] */ IOutputStream** __ppIOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, __ppIOutputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [out] */ IOutputStream** __ppIOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, Param1, Param2, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIOutputStream = IOutputStream::Probe(__pNewObj);
        if (*__ppIOutputStream) (*__ppIOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param0,
/* [in] */ _ELASTOS Int32 Param1,
/* [in] */ _ELASTOS Int32 Param2,
/* [out] */ IOutputStream** __ppIOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, Param1, Param2, __ppIOutputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CStringInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS String Param0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICStringInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CStringInputStream, __pContext, 
                EIID_ICStringInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithString(Param0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ _ELASTOS String Param0,/* [out] */ IStringInputStream** __ppIStringInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, Param0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIStringInputStream = IStringInputStream::Probe(__pNewObj);
        if (*__ppIStringInputStream) (*__ppIStringInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ _ELASTOS String Param0,
/* [out] */ IStringInputStream** __ppIStringInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, Param0, __ppIStringInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CTextInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICTextInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CTextInputStream, __pContext, 
                EIID_ICTextInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Encoding Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICTextInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CTextInputStream, __pContext, 
                EIID_ICTextInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamEncoding(pParam0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ ITextInputStream** __ppITextInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppITextInputStream = ITextInputStream::Probe(__pNewObj);
        if (*__ppITextInputStream) (*__ppITextInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [out] */ ITextInputStream** __ppITextInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppITextInputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Encoding Param1,/* [out] */ ITextInputStream** __ppITextInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppITextInputStream = ITextInputStream::Probe(__pNewObj);
        if (*__ppITextInputStream) (*__ppITextInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [in] */ _ELASTOS Encoding Param1,
/* [out] */ ITextInputStream** __ppITextInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, __ppITextInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CTextOutputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICTextOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CTextOutputStream, __pContext, 
                EIID_ICTextOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Encoding Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICTextOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CTextOutputStream, __pContext, 
                EIID_ICTextOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamEncoding(pParam0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ ITextOutputStream** __ppITextOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppITextOutputStream = ITextOutputStream::Probe(__pNewObj);
        if (*__ppITextOutputStream) (*__ppITextOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [out] */ ITextOutputStream** __ppITextOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppITextOutputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Encoding Param1,/* [out] */ ITextOutputStream** __ppITextOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppITextOutputStream = ITextOutputStream::Probe(__pNewObj);
        if (*__ppITextOutputStream) (*__ppITextOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [in] */ _ELASTOS Encoding Param1,
/* [out] */ ITextOutputStream** __ppITextOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, __ppITextOutputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CGZipInputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICGZipInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CGZipInputStream, __pContext, 
                EIID_ICGZipInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICGZipInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CGZipInputStream, __pContext, 
                EIID_ICGZipInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamWindowBits(pParam0, Param1, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param2,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICGZipInputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CGZipInputStream, __pContext, 
                EIID_ICGZipInputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamWindowBitsDictionary(pParam0, Param1, Param2, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [out] */ IGZipInputStream** __ppIGZipInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIGZipInputStream = IGZipInputStream::Probe(__pNewObj);
        if (*__ppIGZipInputStream) (*__ppIGZipInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [out] */ IGZipInputStream** __ppIGZipInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIGZipInputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [out] */ IGZipInputStream** __ppIGZipInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIGZipInputStream = IGZipInputStream::Probe(__pNewObj);
        if (*__ppIGZipInputStream) (*__ppIGZipInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [in] */ _ELASTOS Int32 Param1,
/* [out] */ IGZipInputStream** __ppIGZipInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, __ppIGZipInputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IInputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param2,/* [out] */ IGZipInputStream** __ppIGZipInputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, Param2, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIGZipInputStream = IGZipInputStream::Probe(__pNewObj);
        if (*__ppIGZipInputStream) (*__ppIGZipInputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IInputStream * pParam0,
/* [in] */ _ELASTOS Int32 Param1,
/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param2,
/* [out] */ IGZipInputStream** __ppIGZipInputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, Param2, __ppIGZipInputStream);
    }
};



EXTERN_C ELAPI _Impl_CheckClsId(
    PInterface pServerObj,
    const _ELASTOS ClassID* pClassid,
    PInterface *ppServerObj);

class CGZipOutputStream
{
public:

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICGZipOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CGZipOutputStream, __pContext, 
                EIID_ICGZipOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStream(pParam0, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [in] */ _ELASTOS Int32 Param3,/* [in] */ CompressStrategy Param4,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICGZipOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CGZipOutputStream, __pContext, 
                EIID_ICGZipOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamWindowBitsCompressLevelMemoryUsageLevelStrategy(pParam0, Param1, Param2, Param3, Param4, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode _NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [in] */ _ELASTOS Int32 Param3,/* [in] */ CompressStrategy Param4,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param5,/* [out] */ IInterface** __ppObject)
    {
        _ELASTOS ECode ec;
        ICGZipOutputStreamClassObject* pClassObject;

        ec = _CObject_AcquireClassFactory(ECLSID_CGZipOutputStream, __pContext, 
                EIID_ICGZipOutputStreamClassObject, (IInterface**)&pClassObject);
        if (FAILED(ec)) return ec;

        ec = pClassObject->CreateObjectWithStreamWindowBitsCompressLevelMemoryUsageLevelStrategyDictionary(pParam0, Param1, Param2, Param3, Param4, Param5, __ppObject);
        if (!IS_CTX_NUMBER(__pContext)) {
            ec = _CObject_EnterContext(*__ppObject, __pContext);
        }
        pClassObject->Release();

        return ec;
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [out] */ IGZipOutputStream** __ppIGZipOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIGZipOutputStream = IGZipOutputStream::Probe(__pNewObj);
        if (*__ppIGZipOutputStream) (*__ppIGZipOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [out] */ IGZipOutputStream** __ppIGZipOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, __ppIGZipOutputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [in] */ _ELASTOS Int32 Param3,/* [in] */ CompressStrategy Param4,/* [out] */ IGZipOutputStream** __ppIGZipOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, Param2, Param3, Param4, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIGZipOutputStream = IGZipOutputStream::Probe(__pNewObj);
        if (*__ppIGZipOutputStream) (*__ppIGZipOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [in] */ _ELASTOS Int32 Param1,
/* [in] */ _ELASTOS Int32 Param2,
/* [in] */ _ELASTOS Int32 Param3,
/* [in] */ CompressStrategy Param4,
/* [out] */ IGZipOutputStream** __ppIGZipOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, Param2, Param3, Param4, __ppIGZipOutputStream);
    }

    static _ELASTOS ECode NewInContext(/* [in] */ IContext* __pContext,/* [in] */ IOutputStream * pParam0,/* [in] */ _ELASTOS Int32 Param1,/* [in] */ _ELASTOS Int32 Param2,/* [in] */ _ELASTOS Int32 Param3,/* [in] */ CompressStrategy Param4,/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param5,/* [out] */ IGZipOutputStream** __ppIGZipOutputStream)
    {
        IInterface* __pNewObj;
        _ELASTOS ECode ec = _NewInContext(__pContext, pParam0, Param1, Param2, Param3, Param4, Param5, &__pNewObj);
        if (FAILED(ec)) return ec;

        *__ppIGZipOutputStream = IGZipOutputStream::Probe(__pNewObj);
        if (*__ppIGZipOutputStream) (*__ppIGZipOutputStream)->AddRef();
        else ec = E_NO_INTERFACE;
        __pNewObj->Release();

        return ec;
    }

    static _ELASTOS ECode New(/* [in] */ IOutputStream * pParam0,
/* [in] */ _ELASTOS Int32 Param1,
/* [in] */ _ELASTOS Int32 Param2,
/* [in] */ _ELASTOS Int32 Param3,
/* [in] */ CompressStrategy Param4,
/* [in] */ const _ELASTOS BufferOf<_ELASTOS Byte> & Param5,
/* [out] */ IGZipOutputStream** __ppIGZipOutputStream)
    {
        return NewInContext((IContext*)CTX_SAME_DOMAIN, pParam0, Param1, Param2, Param3, Param4, Param5, __ppIGZipOutputStream);
    }
};



#else // !__cplusplus
#include <_ElastosCore_c.h>
#endif // __cplusplus

#endif // __CAR_ELASTOSCORE_H__
