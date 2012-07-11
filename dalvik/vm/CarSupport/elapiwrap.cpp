/**
  * elapiwrap.cpp
  *
  * wrapper functions for Elastos
  */

#include "elastos.h"
#include "elapiwrap.h"
#include <dlfcn.h>
#include <stdio.h>
#undef LOG
#include <utils/Log.h>
using namespace Elastos;

#define PATH_MAX  4096
//#define __WITH_ELASTOS_NAME_CHECK

static void* handle_ecoloader = NULL;
//global handle of Elastos.so
static void* handle_elastos = NULL;
static void* handle_ElCRuntime = NULL;

extern "C" void dvmSetgDvmshouldCARWorking(bool b);

#ifdef __WITH_ELASTOS_NAME_CHECK
#define CheckError() do{if(dlerror()!=NULL){LOGE("%s:%d, %s",__FILE__, __LINE__, dlerror());; goto Err;}}while(0)
#else
#define CheckError()
#endif

EXTERN_C const _ELASTOS EMuid ECLSID_ClassInfo = { 0x4CDBF5FC,0xD030,0x4583,{ 0xAE,0xCD,0xA2,0x6E,0x95,0xB3,0x02,0x6F }};

const _ELASTOS InterfaceID EIID_ICallbackInvocation = {0x10DA1A28,0x1C52,0x3984,{0x64,0x98,0x20,0x01,0xFF,0x07,0xC2,0x1C}};

//copy from system/zener/libpub/elasys/sysiids.cpp
EXTERN_C const _ELASTOS InterfaceID EIID_IInterface = \
    {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_IClassObject = \
    {0x00000001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

EXTERN_C const _ELASTOS InterfaceID EIID_METADATA_INFO = \
    {0x00010001,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_CALLBACK_CONNECTOR = \
    {0x00010004,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_IProxy = \
    {0x00010005,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_GENERIC_INFO = \
    {0x00010006,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_MUTEX_INFO = \
    {0x00010007,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_NEXT_ASPECT = \
    {0x00010008,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_PARENT_CONTEXT = \
    {0x00010009,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_CALLBACK_TRIGGER = \
    {0x0001000A,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_SUPER_CALLBACK_CONNECTOR = \
    {0x0001000B,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_SUPER_OBJECT= \
    {0x0001000C,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

EXTERN_C const _ELASTOS InterfaceID EIID_ICustomMarshal = \
    {0xd53fba36,0xa887,0x466c,{0x97,0xc9,0x47,0x83,0x4b,0xa6,0x7b,0x8c}};

EXTERN_C const _ELASTOS InterfaceID EIID_IObject = \
    {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x68}};

EXTERN_C const _ELASTOS InterfaceID EIID_IAspect = \
    {0x00010002,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x66}};

static ELFUNC (*_CObject_CreateInstance_Internal)(_ELASTOS RClassID, PContext,
    	 	_ELASTOS REIID, PInterface*);
static ELFUNC (*_CObject_AddCallback_Internal)(PInterface, _ELASTOS Int32,
    		_ELASTOS EventHandler);
static ELFUNC (*_CObject_RemoveCallback_Internal)(PInterface, _ELASTOS Int32,
		_ELASTOS EventHandler);
static ELFUNC (*_CObject_ReflectClassInfo_Internal)(PInterface, IClassInfo**);

static ELFUNC (*_Impl_CallbackSink_RequestToFinish_Internal)(PInterface, _ELASTOS Int32);
static ELFUNC (*_Impl_CallbackSink_InitCallbackContext_Internal)(PInterface *ppCallbackContext);
static ELFUNC (*_Impl_CallbackSink_TryToHandleEvents_Internal)(IInterface* pCallbackContext);

static _ELASTOS ECode __cdecl (*_CReflector_AcquireModuleInfo_Internal)(Elastos::String name, IModuleInfo**);

void __cdecl (*_Impl_SetHelperInfoFlag_Internal)(_ELASTOS Flags32 flag, _ELASTOS Boolean bValue);

static _ELASTOS PCarQuintet __cdecl (*_CarQuintet_Init_Internal)(_ELASTOS PCarQuintet,
	_ELASTOS PVoid, _ELASTOS Int32, _ELASTOS Int32, _ELASTOS CarQuintetFlags);
static _ELASTOS PCarQuintet __cdecl(*_CarQuintet_Clone_Internal)(const _ELASTOS PCarQuintet);
static void __cdecl (*_CarQuintet_Free_Internal)(_ELASTOS PCarQuintet);
static _ELASTOS PCarQuintet __cdecl(*_CarQuintet_GetNullValue_Internal)(_ELASTOS CarQuintetFlags);
static _ELASTOS Int32 __cdecl(*_ArrayOf_Copy_Internal)(_ELASTOS PCarQuintet, const _ELASTOS CarQuintet*);
static _ELASTOS Int32 __cdecl(*_ArrayOf_CopyEx_Internal)(_ELASTOS PCarQuintet,
		const _ELASTOS Byte*, _ELASTOS Int32);
static _ELASTOS PCarQuintet __cdecl(*_ArrayOf_Alloc_Internal)(_ELASTOS Int32,
		_ELASTOS CarQuintetFlags);
static _ELASTOS PCarQuintet __cdecl(*_ArrayOf_Alloc_Box_Internal)(_ELASTOS PVoid,
        _ELASTOS Int32, _ELASTOS CarQuintetFlags);
static _ELASTOS Int32 __cdecl(*_ArrayOf_Replace_Internal)(_ELASTOS PCarQuintet,
        _ELASTOS Int32, const _ELASTOS PByte, _ELASTOS Int32);
static _ELASTOS PCarQuintet __cdecl(*_BufferOf_Alloc_Internal)(_ELASTOS Int32,
        _ELASTOS CarQuintetFlags);
static _ELASTOS PCarQuintet __cdecl(*_BufferOf_Alloc_Box_Internal)(_ELASTOS PVoid,
        _ELASTOS Int32, _ELASTOS Int32,
        _ELASTOS CarQuintetFlags);
static _ELASTOS Int32 __cdecl(*_BufferOf_Insert_Internal)(_ELASTOS PCarQuintet,
        _ELASTOS Int32, const _ELASTOS PByte, _ELASTOS MemorySize);
static _ELASTOS Int32 __cdecl(*_BufferOf_Replace_Internal)(_ELASTOS PCarQuintet,
        _ELASTOS Int32, const _ELASTOS PByte, _ELASTOS Int32);
static _ELASTOS Int32 __cdecl(*_BufferOf_Copy_Internal)(_ELASTOS PCarQuintet,
        const _ELASTOS CarQuintet*);
static _ELASTOS Int32 __cdecl(*_BufferOf_CopyEx_Internal)(_ELASTOS PCarQuintet,
        const _ELASTOS Byte*, _ELASTOS Int32);
static _ELASTOS Int32 __cdecl(*_BufferOf_Append_Internal)(_ELASTOS PCarQuintet,
        const _ELASTOS PByte, _ELASTOS MemorySize);
static void (*_MemoryBuf_SetByteValue_Internal)(_ELASTOS PCarQuintet, _ELASTOS Byte);
static _ELASTOS Int32 __cdecl(*_MemoryBuf_Compare_Internal)(const _ELASTOS PCarQuintet,
        const _ELASTOS Byte*, _ELASTOS Int32);
static _ELASTOS Int32 __cdecl(*_StringBuf_SetLength_Internal)(_ELASTOS PCarQuintet,
    _ELASTOS Int32);
static _ELASTOS PCarQuintet __cdecl(*_StringBuf_Alloc_Internal)(_ELASTOS Int32 length);
static _ELASTOS Int32 __cdecl(*_String_GetLength_Internal)(const char *str, Int32 maxLen);
static _ELASTOS ECode (*_Impl_CheckClsId_Internal)(PInterface pServerObj, const _ELASTOS ClassID* pClassID,
	PInterface *ppServerObj);
static ELFUNC (*_Impl_EnterProtectedZone_Internal)();
static ELFUNC (*_Impl_LeaveProtectedZone_Internal)();
static ELFUNC (*_Impl_CallbackSink_CancelPendingCallback_Internal)(IInterface *pCallbackContext, PInterface pSender, CallbackEventId id);
static ELFUNC (*_Impl_CallbackSink_GetCallbackContext_Internal)(PInterface *ppCallbackContext);
static ELFUNC (*_Impl_CallbackSink_CancelCallbackEvents_Internal)(IInterface *pCallbackContext, PInterface pSender, CallbackEventId id, PVoid pHandlerThis, PVoid 				pHandlerFunc);
static ELFUNC (*_Impl_CallbackSink_AcquireCallbackContext_Internal)(PInterface *ppCallbackContext);
static ELFUNC (*_Impl_CCallbackRendezvous_New_Internal)(PInterface pCallbackContext, ICallbackSink* pCallbackSink, CallbackEventId eventId,
										Boolean* pbEventF, Boolean bNewCallback, ICallbackRendezvous** ppICallbackRendezvous);

static ELFUNC (*_String_Compare_Internal)(const char *string1, const char *string2, StringCase stringCase);

static _ELASTOS Boolean __cdecl(*_StringBuf_StartWith_Internal)(
		const _ELASTOS PCarQuintet pCq,
	    const char *substr, _ELASTOS StringCase stringCase);

static _ELASTOS Boolean __cdecl(*_StringBuf_EndWith_Internal)(
		const _ELASTOS PCarQuintet pCq,
	    const char *substr, _ELASTOS StringCase stringCase);

static _ELASTOS Int32 __cdecl(*_StringBuf_Insert_Internal)(
		_ELASTOS PCarQuintet pCq,
		_ELASTOS Int32 offset,
		_ELASTOS String s);

static _ELASTOS Int32 __cdecl(*_StringBuf_Append_Int32_Internal)(
		_ELASTOS PCarQuintet pCq,
	    _ELASTOS Int32 value,
	    _ELASTOS Flags32 fmt);

static _ELASTOS Int32 __cdecl(*_StringBuf_Copy_Internal)(
		_ELASTOS PCarQuintet pCq,
		_ELASTOS String s);

int atomic_inc(int *ptr){
	return (*ptr)++;
}

int atomic_dec(int *ptr){
	return (*ptr)--;
}

typedef  pthread_key_t * (*t_elastos_getTlSystemSlotBase)();
static t_elastos_getTlSystemSlotBase elastos_getTlSystemSlotBase;

pthread_key_t *getTlSystemSlotBase(){
	return elastos_getTlSystemSlotBase();
}

bool ElapiInitialize()
{
	LOGD("ElapiInitialize() start");

    const char* elastosPath = NULL;
    const char* extraFile = "elastos.eco";
	char        fullPath[PATH_MAX];
	int         i;

	if (NULL != handle_elastos)
	    return true;

	//elastosPath = getenv("ELASTOS_JS_ROOT");
	if(NULL == elastosPath) {
        elastosPath = "/data/data/com.elastos.runtime/elastos";
	}

	if( strlen(elastosPath) >= PATH_MAX-12)
	    return  false;

	strcpy(fullPath, elastosPath);
    i = strlen(fullPath);

    if(fullPath[i-1] != '/'){
        strcpy(fullPath+i, "/");
        i++;
    }
	strcpy(fullPath+i, extraFile);

	// dlopen(elfloader.dll)
	handle_ecoloader = dlopen("/data/data/com.elastos.runtime/elastos/ecoloader.dso", RTLD_LAZY);
	if (NULL == handle_ecoloader) {
		LOGE("dlopen ecoloader.dso failed");
        dvmSetgDvmshouldCARWorking(false);
        return false;
	} else {
		LOGE("dlopen ecoloader.dso OK");
	}

	// dlsym(LoadElfModule)
	void* (*pLoadElfModule)(const char*, const char*, int);
	// attention: function name format: __DLL_FUN
	pLoadElfModule = (void* (*)(const char*, const char*, int))dlsym(handle_ecoloader, "__ecoloader_LoadElfModule");
	if (NULL == pLoadElfModule) {
	    LOGE("dlsym LoadElfModule failed");
        dvmSetgDvmshouldCARWorking(false);
        return false;
	} else {
	    LOGE("dlsym LoadElfModule ok");
	}

	// dlsym(GetElfModuleSymbol)
	void* (*pGetElfModuleSymbol)(void*, char*);
	pGetElfModuleSymbol = (void* (*)(void*, char*))dlsym(handle_ecoloader, "__ecoloader_GetElfModuleSymbol");
	if (NULL == pGetElfModuleSymbol) {
	    LOGE("dlsym GetElfModuleSymbol failed");
        dvmSetgDvmshouldCARWorking(false);;
        return false;
	} else {
	    LOGE("dlsym GetElfModuleSymbol ok");
	}

	// LoadElfModule(elastos.dll)
	handle_elastos = pLoadElfModule("/data/data/com.elastos.runtime/elastos", "Elastos.Runtime.CarRuntime.eco", RTLD_LAZY); // flag right?
	if (NULL == handle_elastos) {
	    LOGE("LoadElfModule Elastos.Runtime.CarRuntime.eco failed");
        dvmSetgDvmshouldCARWorking(false);
        return false;
	} else {
	    LOGE("LoadElfMoudule Elastos.Runtime.CarRuntime.eco ok");
	}

	handle_ElCRuntime = pLoadElfModule("/data/data/com.elastos.runtime/elastos", "Elastos.Runtime.eco", RTLD_LAZY); // flag right?
	if (NULL == handle_ElCRuntime) {
	    LOGE("LoadElfModule Elastos.Runtime.eco failed");
        dvmSetgDvmshouldCARWorking(false);
        return false;
	} else {
	    LOGE("LoadElfMoudule Elastos.Runtime.eco ok");
	}

	elastos_getTlSystemSlotBase =
			(t_elastos_getTlSystemSlotBase)pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime_getTlSystemSlotBase");

	_CObject_CreateInstance_Internal =
			(ELFUNC(*)(_ELASTOS RClassID, PContext,
    	 	_ELASTOS REIID, PInterface*))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CObject_CreateInstance");

	CheckError();

	_CObject_AddCallback_Internal =
			(ELFUNC(*)(PInterface, _ELASTOS Int32,
    		_ELASTOS EventHandler))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CObject_AddCallback");
	LOGD("_CObject_AddCallback_Internal, addr:0x%x", (int)_CObject_AddCallback_Internal);
	CheckError();

	_CObject_RemoveCallback_Internal =
			(ELFUNC(*)(PInterface, _ELASTOS Int32,
    		_ELASTOS EventHandler))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CObject_RemoveCallback");

	CheckError();

	_CObject_ReflectClassInfo_Internal =
			(ELFUNC(*)(PInterface, IClassInfo**))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CObject_ReflectClassInfo");

	CheckError();

	_Impl_CallbackSink_RequestToFinish_Internal =
			(ELFUNC(*)(PInterface, _ELASTOS Int32))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_RequestToFinish");

	CheckError();

	_Impl_CallbackSink_InitCallbackContext_Internal =
			(ELFUNC(*)(PInterface *ppCallbackContext))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_InitCallbackContext");

	CheckError();

	_Impl_CallbackSink_TryToHandleEvents_Internal =
			(ELFUNC(*)(IInterface* pCallbackContext))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_TryToHandleEvents");

	CheckError();

	_CReflector_AcquireModuleInfo_Internal =
			(_ELASTOS ECode __cdecl (*)(Elastos::String, IModuleInfo**))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CReflector_AcquireModuleInfo");

	CheckError();

	// mayq add, til end
	_Impl_SetHelperInfoFlag_Internal = (void __cdecl(*)(_ELASTOS Flags32, _ELASTOS Boolean)) pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_SetHelperInfoFlag");

	CheckError();
	// mayq end

	_CarQuintet_Init_Internal =
			(_ELASTOS PCarQuintet __cdecl (*)(_ELASTOS PCarQuintet, _ELASTOS PVoid, _ELASTOS Int32,
		 	_ELASTOS Int32, _ELASTOS CarQuintetFlags))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CarQuintet_Init");

	CheckError();

	_CarQuintet_Clone_Internal = (_ELASTOS PCarQuintet __cdecl(*)(const _ELASTOS PCarQuintet))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CarQuintet_Clone");

	CheckError();

	_CarQuintet_Free_Internal = (void __cdecl(*)(_ELASTOS PCarQuintet))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CarQuintet_Free");

	CheckError();

	_CarQuintet_GetNullValue_Internal = (_ELASTOS PCarQuintet __cdecl(*)(_ELASTOS CarQuintetFlags))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CarQuintet_GetNullValue");

	CheckError();

	_ArrayOf_Copy_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet, const _ELASTOS CarQuintet*))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__CarQuintet_Clone");

	CheckError();

	_ArrayOf_CopyEx_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
			const _ELASTOS Byte*, _ELASTOS Int32))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__ArrayOf_CopyEx");

	CheckError();

	_ArrayOf_Alloc_Internal = (_ELASTOS PCarQuintet __cdecl(*)(_ELASTOS Int32,
			_ELASTOS CarQuintetFlags))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__ArrayOf_Alloc");

	CheckError();

	_ArrayOf_Alloc_Box_Internal = (_ELASTOS PCarQuintet __cdecl(*)(_ELASTOS PVoid,
            _ELASTOS Int32, _ELASTOS CarQuintetFlags))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__ArrayOf_Alloc_Box");

	CheckError();

	_ArrayOf_Replace_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
            _ELASTOS Int32, const _ELASTOS PByte, _ELASTOS Int32))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__ArrayOf_Replace");

	CheckError();

	_BufferOf_Alloc_Internal = (_ELASTOS PCarQuintet __cdecl(*)(_ELASTOS Int32,
	        _ELASTOS CarQuintetFlags))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_Alloc");

	CheckError();

	_BufferOf_Alloc_Box_Internal = (_ELASTOS PCarQuintet __cdecl(*)(_ELASTOS PVoid,
            _ELASTOS Int32, _ELASTOS Int32,
            _ELASTOS CarQuintetFlags))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_Alloc_Box");

	CheckError();

	_BufferOf_Insert_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
            _ELASTOS Int32, const _ELASTOS PByte, _ELASTOS MemorySize))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_Insert");

	CheckError();

	_BufferOf_Replace_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
            _ELASTOS Int32, const _ELASTOS PByte, _ELASTOS Int32))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_Replace");

	CheckError();

	_BufferOf_Copy_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
            const _ELASTOS CarQuintet*))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_Copy");

	CheckError();

	_BufferOf_CopyEx_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
            const _ELASTOS Byte*, _ELASTOS Int32))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_CopyEx");

	CheckError();

	_BufferOf_Append_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
            const _ELASTOS PByte, _ELASTOS MemorySize))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__BufferOf_Append");

	CheckError();

	_MemoryBuf_SetByteValue_Internal =
			(void (*)(_ELASTOS PCarQuintet, _ELASTOS Byte))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__MemoryBuf_SetByteValue");

	CheckError();

	_MemoryBuf_Compare_Internal = (_ELASTOS Int32 __cdecl(*)(const _ELASTOS PCarQuintet,
            const _ELASTOS Byte*, _ELASTOS Int32))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__MemoryBuf_Compare");

	CheckError();

	_StringBuf_SetLength_Internal = (_ELASTOS Int32 __cdecl(*)(_ELASTOS PCarQuintet,
    	_ELASTOS Int32))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_SetLength");

	CheckError();

	_StringBuf_Alloc_Internal = (_ELASTOS PCarQuintet __cdecl(*)(_ELASTOS Int32 length))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_Alloc");

	CheckError();

	_String_GetLength_Internal = (_ELASTOS Int32 __cdecl (*)(const char *str,
			Int32 maxLen))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__String_GetLength");

	_Impl_CheckClsId_Internal = (_ELASTOS ECode(*)(PInterface, const _ELASTOS ClassID*,
   		PInterface*))pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CheckClsId");

	CheckError();

	_Impl_EnterProtectedZone_Internal = (ELFUNC (*)())
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_EnterProtectedZone");

	CheckError();

	_Impl_LeaveProtectedZone_Internal = (ELFUNC (*)())
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_LeaveProtectedZone");

	CheckError();

	_Impl_CallbackSink_CancelPendingCallback_Internal = (ELFUNC (*)(IInterface *, PInterface , CallbackEventId ))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_CancelPendingCallback");

	CheckError();

	_Impl_CallbackSink_GetCallbackContext_Internal = (ELFUNC (*)(PInterface *))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_GetCallbackContext");
	//LOGD("_Impl_CallbackSink_GetCallbackContext_Internal=0x%x", _Impl_CallbackSink_GetCallbackContext_Internal);

	CheckError();

	_Impl_CallbackSink_CancelCallbackEvents_Internal = (ELFUNC (*)(IInterface *, PInterface, CallbackEventId, PVoid, PVoid ))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_CancelCallbackEvents");

	CheckError();

	_Impl_CallbackSink_AcquireCallbackContext_Internal = (ELFUNC (*)(PInterface *))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CallbackSink_AcquireCallbackContext");
	//LOGD("_Impl_CallbackSink_AcquireCallbackContext_Internal=0x%x",_Impl_CallbackSink_AcquireCallbackContext_Internal);
	CheckError();

	_Impl_CCallbackRendezvous_New_Internal = (ELFUNC (*)(PInterface , ICallbackSink* , CallbackEventId ,
											Boolean* , Boolean , ICallbackRendezvous** ))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__Impl_CCallbackRendezvous_New");
	CheckError();

	_String_Compare_Internal = (ELFUNC (*)(const char*, const char*, StringCase))
										pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__String_Compare");

	CheckError();

	_StringBuf_StartWith_Internal = (_ELASTOS Boolean __cdecl (*)(const PCarQuintet,
											   const char *,
											   StringCase))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_StartWith");
	CheckError();

	_StringBuf_EndWith_Internal = (_ELASTOS Boolean __cdecl (*)(const PCarQuintet,
											   const char *,
											   StringCase))
									pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_EndWith");
	CheckError();

	_StringBuf_Insert_Internal = (_ELASTOS Int32 __cdecl (*)(
									_ELASTOS PCarQuintet,
									_ELASTOS Int32,
									_ELASTOS String))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_Insert");

	CheckError();

	_StringBuf_Append_Int32_Internal = (_ELASTOS Int32 __cdecl (*)(
							_ELASTOS PCarQuintet,
							_ELASTOS Int32,
							_ELASTOS Flags32))
						pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_Append_Int32");

	CheckError();

	_StringBuf_Copy_Internal = (_ELASTOS Int32 __cdecl (*)(
									_ELASTOS PCarQuintet,
									_ELASTOS String))
								pGetElfModuleSymbol(handle_elastos, (char*)"__Elastos_Runtime_CarRuntime__StringBuf_Copy");
	CheckError();

	LOGD("ElapiInitialize successful");
	return true;

#ifdef __WITH_ELASTOS_NAME_CHECK
Err:
#endif

	LOGE("ElapiInitialize error");
	return false;

}


void ElapiUninitialize()
{
	if(handle_elastos != NULL)
	{
		int (*pCloseElfModule)(void*);
		// attention: function name format: __DLL_FUN
		pCloseElfModule = (int (*)(void*))dlsym(handle_ecoloader, "__ecoloader_CloseElfModule");
		if (NULL == pCloseElfModule) {
			LOGE("dlsym pCloseElfModule failed");
		} else {
		    pCloseElfModule(handle_elastos);
		    handle_elastos = NULL;
		}

		dlclose(handle_ecoloader);
		handle_ecoloader = NULL;
	}
}


bool IsElapiInitialized()
{
	return handle_elastos != NULL;
}

//======================================================================================
////Elastos Execution Engine APIs  1-200
ELFUNC _CObject_CreateInstance(
    /* [in] */ _ELASTOS RClassID rclsid,
    /* [in] */ PContext pContext,
    /* [in] */ _ELASTOS REIID riid,
    /* [out] */ PInterface *ppObject)
{
	return _CObject_CreateInstance_Internal(rclsid, pContext, riid, ppObject);
}

ELFUNC _CObject_AddCallback(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [in] */ _ELASTOS EventHandler delegate)
{
	LOGD("_CObject_AddCallback, call _CObject_AddCallback_Internal");
	return _CObject_AddCallback_Internal(pServerObj, dwEvent, delegate);
}

ELFUNC _CObject_RemoveCallback(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [in] */ _ELASTOS EventHandler delegate)
{
	return _CObject_RemoveCallback_Internal(pServerObj, dwEvent, delegate);
}

ELFUNC _CObject_ReflectClassInfo(
	/* [in] */ PInterface pObj,
    /* [in] */ IClassInfo **ppClassInfo)
{
	return _CObject_ReflectClassInfo_Internal(pObj, ppClassInfo);
}


//APIs for callback
ELFUNC _Impl_CallbackSink_RequestToFinish(
    PInterface pCallbackContext, _ELASTOS Int32 flag)
{
	return _Impl_CallbackSink_RequestToFinish_Internal(pCallbackContext, flag);
}
ELFUNC _Impl_CallbackSink_InitCallbackContext(
    PInterface *ppCallbackContext)
{
	return _Impl_CallbackSink_InitCallbackContext_Internal(ppCallbackContext);
}
ELFUNC _Impl_CallbackSink_TryToHandleEvents(
    IInterface* pCallbackContext)
{
	return _Impl_CallbackSink_TryToHandleEvents_Internal(pCallbackContext);
}
//Profile APIs

//Reflection APIs
_ELASTOS ECode __cdecl _CReflector_AcquireModuleInfo(Elastos::String name, IModuleInfo **ppModuleInfo)
{
	return _CReflector_AcquireModuleInfo_Internal(name, ppModuleInfo);
}

void __cdecl _Impl_SetHelperInfoFlag(_ELASTOS Flags32 flag, _ELASTOS Boolean bValue)
{
	return _Impl_SetHelperInfoFlag_Internal(flag, bValue);
}

ELFUNC _String_Compare(
		const char *string1,
		const char *string2,
		_ELASTOS StringCase stringCase)
{
	return _String_Compare_Internal(string1, string2, stringCase);
}

_ELASTOS Boolean __cdecl _StringBuf_StartWith(
		const _ELASTOS PCarQuintet pCq,
		const char *substr,
		_ELASTOS StringCase stringCase)
{
	return _StringBuf_StartWith_Internal(pCq, substr, stringCase);
}

_ELASTOS Boolean __cdecl _StringBuf_EndWith(
		const _ELASTOS PCarQuintet pCq,
		const char *substr,
		_ELASTOS StringCase stringCase)
{
	return _StringBuf_EndWith_Internal(pCq, substr, stringCase);
}

_ELASTOS Int32 __cdecl _StringBuf_Insert(
		_ELASTOS PCarQuintet pCq,
		_ELASTOS Int32 offset, _ELASTOS String s)
{
    return _StringBuf_Insert_Internal(pCq, offset, s);
}

_ELASTOS Int32 __cdecl _StringBuf_Append_Int32(
		_ELASTOS PCarQuintet pCq,
		_ELASTOS Int32 value,
		_ELASTOS Flags32 fmt)
{
    return _StringBuf_Append_Int32_Internal(pCq, value, fmt);
}

_ELASTOS Int32 __cdecl _StringBuf_Copy(
		_ELASTOS PCarQuintet pCq,
		_ELASTOS String s)
{
    return _StringBuf_Copy_Internal(pCq, s);
}

//Debug APIs

//=====================================================================================
////CAR data-type APIs, using ordinal 200-499

//CarArray, StringBuf, WStringBuf
//

_ELASTOS PCarQuintet __cdecl _CarQuintet_Init(_ELASTOS PCarQuintet pCq,
		_ELASTOS PVoid pBuf, _ELASTOS Int32 size, _ELASTOS Int32 used,
	    _ELASTOS CarQuintetFlags flags)
{
	return _CarQuintet_Init_Internal(pCq, pBuf, size, used, flags);
}

_ELASTOS PCarQuintet __cdecl _CarQuintet_Clone(const _ELASTOS PCarQuintet pCq)
{
	return _CarQuintet_Clone_Internal(pCq);
}

void __cdecl _CarQuintet_Free(_ELASTOS PCarQuintet pCq)
{
	return _CarQuintet_Free_Internal(pCq);
}

_ELASTOS PCarQuintet __cdecl _CarQuintet_GetNullValue(
            _ELASTOS CarQuintetFlags flag)
{
	return _CarQuintet_GetNullValue_Internal(flag);
}

_ELASTOS Int32 __cdecl _ArrayOf_Copy(_ELASTOS PCarQuintet pcqDst,
			const _ELASTOS CarQuintet* pcqSrc)
{
	return _ArrayOf_Copy_Internal(pcqDst, pcqSrc);
}

_ELASTOS Int32 __cdecl _ArrayOf_CopyEx(_ELASTOS PCarQuintet pCq,
			const _ELASTOS Byte* p, _ELASTOS Int32 n)
{
	return _ArrayOf_CopyEx_Internal(pCq, p, n);
}

_ELASTOS PCarQuintet __cdecl _ArrayOf_Alloc(_ELASTOS Int32 size,
			_ELASTOS CarQuintetFlags flags)
{
	return _ArrayOf_Alloc_Internal(size, flags);
}

_ELASTOS PCarQuintet __cdecl _ArrayOf_Alloc_Box(_ELASTOS PVoid pBuf,
            _ELASTOS Int32 size, _ELASTOS CarQuintetFlags flags)
{
	return _ArrayOf_Alloc_Box_Internal(pBuf, size, flags);
}

_ELASTOS Int32 __cdecl _ArrayOf_Replace(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte p, _ELASTOS Int32 n)
{
	return _ArrayOf_Replace_Internal(pCq, offset, p, n);
}

_ELASTOS PCarQuintet __cdecl _BufferOf_Alloc(_ELASTOS Int32 size,
            _ELASTOS CarQuintetFlags flags)
{
	return _BufferOf_Alloc_Internal(size, flags);
}

_ELASTOS PCarQuintet __cdecl _BufferOf_Alloc_Box(_ELASTOS PVoid pBuf,
            _ELASTOS Int32 capacity, _ELASTOS Int32 used,
            _ELASTOS CarQuintetFlags flags)
{
	return _BufferOf_Alloc_Box_Internal(pBuf, capacity, used, flags);
}

_ELASTOS Int32 __cdecl _BufferOf_Insert(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte pb, _ELASTOS MemorySize n)
{
	return _BufferOf_Insert_Internal(pCq, offset, pb, n);
}

_ELASTOS Int32 __cdecl _BufferOf_Replace(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte p, _ELASTOS Int32 n)
{
	return _BufferOf_Replace_Internal(pCq, offset, p, n);
}

_ELASTOS Int32 __cdecl _BufferOf_Copy(_ELASTOS PCarQuintet pcqDst,
            const _ELASTOS CarQuintet* pcqSrc)
{
	return _BufferOf_Copy_Internal(pcqDst, pcqSrc);
}

_ELASTOS Int32 __cdecl _BufferOf_CopyEx(_ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* p, _ELASTOS Int32 n)
{
	return _BufferOf_CopyEx_Internal(pCq, p, n);
}

_ELASTOS Int32 __cdecl _BufferOf_Append(_ELASTOS PCarQuintet pCq,
            const _ELASTOS PByte p, _ELASTOS MemorySize n)
{
	return _BufferOf_Append_Internal(pCq, p, n);
}

void _MemoryBuf_SetByteValue(_ELASTOS PCarQuintet pCq, _ELASTOS Byte value)
{
	return _MemoryBuf_SetByteValue_Internal(pCq, value);
}

_ELASTOS Int32 _MemoryBuf_Compare(const _ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* pBuf, _ELASTOS Int32 count)
{
	return _MemoryBuf_Compare_Internal(pCq, pBuf, count);
}

_ELASTOS Int32 __cdecl _StringBuf_SetLength(_ELASTOS PCarQuintet pCq,
    _ELASTOS Int32 len)
{
	return _StringBuf_SetLength_Internal(pCq, len);
}

_ELASTOS PCarQuintet __cdecl _StringBuf_Alloc(_ELASTOS Int32 length)
{
	return _StringBuf_Alloc_Internal(length);
}

_ELASTOS Int32 __cdecl _StringBuf_Insert(_ELASTOS PCarQuintet pCq,
    _ELASTOS Int32 offset, _ELASTOS String s);

_ELASTOS Int32 __cdecl _StringBuf_Copy(_ELASTOS PCarQuintet pCq,
    _ELASTOS String s);

_ELASTOS Int32 __cdecl _StringBuf_Append_Int32(_ELASTOS PCarQuintet pCq,
    _ELASTOS Int32 value, _ELASTOS Flags32 fmt);

_ELASTOS Boolean __cdecl _StringBuf_StartWith(const _ELASTOS PCarQuintet pCq,
    const char *substr, _ELASTOS StringCase stringCase);

_ELASTOS Boolean __cdecl _StringBuf_EndWith(const _ELASTOS PCarQuintet pCq,
    const char *substr, _ELASTOS StringCase stringCase);

_ELASTOS Int32 __cdecl _String_GetLength(const char *str, Int32 maxLen)
{
	return _String_GetLength_Internal(str, maxLen);
}
//====================================================================================
////CAR Class IDs and Interface IDs, using ordinal 500-700

//====================================================================================
//new and delete C++ export

//====================================================================================
//CRT APIs for compiler

//====================================================================================
//APIs for arm float

//====================================================================================
//Internal APIs for crtzip

//====================================================================================
//Internal APIs and symbols required by C/C++ compilers

//====================================================================================
//callback helper APIs for making parameters
_ELASTOS ECode _Impl_CheckClsId(PInterface pServerObj, const _ELASTOS ClassID* pClassID,
   		PInterface *ppServerObj)
{
	return _Impl_CheckClsId_Internal(pServerObj, pClassID, ppServerObj);
}


void* __cdecl _Impl_Memset(void *dest, int c, size_t n)
{
	return memset(dest, c, n);
}


int __cdecl _Impl_Memcmp(const void *src, const void *des, size_t len)
{
	return memcmp(src, des, len);
}

ELFUNC _Impl_EnterProtectedZone()
{
	return _Impl_EnterProtectedZone_Internal();
}

ELFUNC _Impl_LeaveProtectedZone()
{
	return _Impl_LeaveProtectedZone_Internal();
}

ELFUNC _Impl_CallbackSink_CancelPendingCallback(IInterface *pCallbackContext, PInterface pSender, CallbackEventId id)
{
	return _Impl_CallbackSink_CancelPendingCallback_Internal(pCallbackContext,  pSender,  id);
}

ELFUNC _Impl_CallbackSink_GetCallbackContext(PInterface *ppCallbackContext)
{
	return _Impl_CallbackSink_GetCallbackContext_Internal(ppCallbackContext);
}
ELFUNC _Impl_CallbackSink_CancelCallbackEvents(IInterface *pCallbackContext, PInterface pSender, CallbackEventId id, PVoid pHandlerThis, PVoid pHandlerFunc)
{
	return _Impl_CallbackSink_CancelCallbackEvents_Internal(pCallbackContext, pSender, id, pHandlerThis, pHandlerFunc);
}


ELFUNC _Impl_CallbackSink_AcquireCallbackContext(PInterface *ppCallbackContext)
{
	return _Impl_CallbackSink_AcquireCallbackContext_Internal(ppCallbackContext);
}


ELFUNC _Impl_CCallbackRendezvous_New(PInterface pCallbackContext, ICallbackSink* pCallbackSink, CallbackEventId eventId,
											Boolean* pbEventFlag, Boolean bNewCallback, ICallbackRendezvous** ppICallbackRendezvous)
{
	return _Impl_CCallbackRendezvous_New_Internal( pCallbackContext,  pCallbackSink,  eventId,
											 pbEventFlag,  bNewCallback,  ppICallbackRendezvous);
}

int __cdecl _Impl_Strcmp(const char* src, const char* dst)
{
	return strcmp(src, dst);
}

