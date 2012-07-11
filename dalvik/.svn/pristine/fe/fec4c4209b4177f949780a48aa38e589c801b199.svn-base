#ifndef __ELAPIWRAP_H__
#define __ELAPIWRAP_H__

bool ElapiInitialize();
void ElapiUninitialize();
bool IsElapiInitialized();

//======================================================================================
////Elastso Execution Engine APIs  1-200

void __cdecl _CProcess_Exit(ExitCode exitCode);

ELAPI _CObject_CreateInstance(
    /* [in] */ _ELASTOS RClassID rclsid,
    /* [in] */ PContext pContext,
    /* [in] */ _ELASTOS REIID riid,
    /* [out] */ PInterface *ppObject);

ELAPI _CObject_AddCallback(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [in] */ _ELASTOS EventHandler delegate);

ELAPI _CObject_ReleaseAtThreadQuit(
    /* [in] */ PInterface pObject);

ELAPI _CObject_RemoveCallback(
    /* [in] */ PInterface pServerObj,
    /* [in] */ _ELASTOS Int32 dwEvent,
    /* [in] */ _ELASTOS EventHandler delegate);

ELAPI _CObject_ReflectClassInfo(
	/* [in] */ PInterface pObj,
    /* [in] */ IClassInfo **ppClassInfo);

//APIs for callback
ELAPI _Impl_CallbackSink_RequestToFinish(
    PInterface pCallbackContext, _ELASTOS Int32 flag);
//Profile A{Is

//Reflection APIs
_ELASTOS ECode __cdecl _CReflector_AcquireModuleInfo(Elastos::String name, IModuleInfo **ppModuleInfo);

//Console APIs
_ELASTOS ECode __cdecl _Console_Write_String(_ELASTOS String s);

_ELASTOS ECode __cdecl _Console_WriteLine_String(_ELASTOS String s);

// mayq add
void __cdecl _Impl_SetHelperInfoFlag(_ELASTOS Flags32 flag, _ELASTOS Boolean bValue);

//Debug APIs

//=====================================================================================
////CAR data-type APIs, using ordinal 200-499

//CarArray, StringBuf, WStringBuf
//

_ELASTOS PCarQuintet __cdecl _CarQuintet_Init(_ELASTOS PCarQuintet pCq,
		_ELASTOS PVoid pBuf, _ELASTOS Int32 size, _ELASTOS Int32 used,
	    _ELASTOS CarQuintetFlags flags);

_ELASTOS PCarQuintet __cdecl _CarQuintet_Clone(const _ELASTOS PCarQuintet pCq);

void __cdecl _CarQuintet_Free(_ELASTOS PCarQuintet pCq);

_ELASTOS PCarQuintet __cdecl _CarQuintet_GetNullValue(
            _ELASTOS CarQuintetFlags flag);

_ELASTOS Int32 __cdecl _ArrayOf_Copy(_ELASTOS PCarQuintet pcqDst,
			const _ELASTOS CarQuintet* pcqSrc);

_ELASTOS Int32 __cdecl _ArrayOf_CopyEx(_ELASTOS PCarQuintet pCq,
			const _ELASTOS Byte* p, _ELASTOS Int32 n);

_ELASTOS PCarQuintet __cdecl _ArrayOf_Alloc(_ELASTOS Int32 size,
			_ELASTOS CarQuintetFlags flags);

_ELASTOS PCarQuintet __cdecl _ArrayOf_Alloc_Box(_ELASTOS PVoid pBuf,
            _ELASTOS Int32 size, _ELASTOS CarQuintetFlags flags);

_ELASTOS Int32 __cdecl _ArrayOf_Replace(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte p, _ELASTOS Int32 n);

_ELASTOS PCarQuintet __cdecl _BufferOf_Alloc(_ELASTOS Int32 size,
            _ELASTOS CarQuintetFlags flags);

_ELASTOS PCarQuintet __cdecl _BufferOf_Alloc_Box(_ELASTOS PVoid pBuf,
            _ELASTOS Int32 capacity, _ELASTOS Int32 used,
            _ELASTOS CarQuintetFlags flags);

_ELASTOS Int32 __cdecl _BufferOf_Insert(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte pb, _ELASTOS MemorySize n);

_ELASTOS Int32 __cdecl _BufferOf_Replace(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte p, _ELASTOS Int32 n);

_ELASTOS Int32 __cdecl _BufferOf_Copy(_ELASTOS PCarQuintet pcqDst,
            const _ELASTOS CarQuintet* pcqSrc);

_ELASTOS Int32 __cdecl _BufferOf_CopyEx(_ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* p, _ELASTOS Int32 n);

_ELASTOS Int32 __cdecl _BufferOf_Append(_ELASTOS PCarQuintet pCq,
            const _ELASTOS PByte p, _ELASTOS MemorySize n);

void _MemoryBuf_SetByteValue(_ELASTOS PCarQuintet pCq, _ELASTOS Byte value);

_ELASTOS Int32 _MemoryBuf_Compare(const _ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* pBuf, _ELASTOS Int32 count);

// mayq, remove
/*_ELASTOS Int32 __cdecl _StringBuf_LastIndexOf_AChar(const _ELASTOS PCarQuintet pCq, char ch,
        _ELASTOS StringCase stringCase, _ELASTOS Encoding encoding);
*/
_ELASTOS Int32 __cdecl _StringBuf_SetLength(_ELASTOS PCarQuintet pCq,
    _ELASTOS Int32 len);

// mayq, remove
/*
_ELASTOS Int32 __cdecl _WStringBuf_Append_AChar(_ELASTOS PCarQuintet pCq,
        _ELASTOS AChar ac);

_ELASTOS Int32 __cdecl _StringBuf_Append_AChar(_ELASTOS PCarQuintet pCq,
        _ELASTOS AChar ch);
*/

_ELASTOS Int32 __cdecl _String_GetLength(const char *str, Elastos::Int32 maxLen);

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
   		PInterface *ppServerObj);
//

void* __cdecl _Impl_Memset(void *dest, int c, size_t n);
void* __cdecl _Impl_Memset(void *dest, int c, size_t n);

ELAPI _CCriticalSection_Initialize(_ELASTOS CriticalSection *pCriticalSection);
void _CCriticalSection_Enter(_ELASTOS CriticalSection *pCriticalSection);
void _CCriticalSection_Leave(_ELASTOS CriticalSection *pCriticalSection);
void _CCriticalSection_Terminate(_ELASTOS CriticalSection *pCriticalSection);
ELAPI _Impl_EnterProtectedZone();
ELAPI _Impl_LeaveProtectedZone();
_ELASTOS Int32 __cdecl SWPADD(_ELASTOS PInt32 pAddend, _ELASTOS Int32 increment);
_ELASTOS Int32 __cdecl CMPSWP(_ELASTOS PInt32 pDestination, _ELASTOS Int32 exchange, _ELASTOS Int32 comperand);
_ELASTOS PVoid _CMemoryHeap_Alloc(_ELASTOS MemorySize size, _ELASTOS Boolean zeroMem);
void _CMemoryHeap_Free(_ELASTOS PVoid pMem);


ELAPI _Impl_CallbackSink_CancelPendingCallback(IInterface *pCallbackContext, PInterface pSender, CallbackEventId id);
ELAPI _Impl_CallbackSink_GetCallbackContext(PInterface *ppCallbackContext);
ELAPI _Impl_CallbackSink_CancelCallbackEvents(IInterface *pCallbackContext, PInterface pSender, CallbackEventId id, _ELASTOS PVoid pHandlerThis, _ELASTOS PVoid pHandlerFunc);
ELAPI _Impl_CallbackSink_AcquireCallbackContext(PInterface *ppCallbackContext);
ELAPI _Impl_CCallbackRendezvous_New(PInterface pCallbackContext, ICallbackSink* pCallbackSink, CallbackEventId eventId,
		_ELASTOS Boolean* pbEventFlag, _ELASTOS Boolean bNewCallback, ICallbackRendezvous** ppICallbackRendezvous);

int __cdecl _Impl_Strcmp(const char* src, const char* dst);
#endif

