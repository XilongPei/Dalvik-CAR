#ifndef __CAR_JAVACALLBACKINVOCATIONPUB_CPP__
#define __CAR_JAVACALLBACKINVOCATIONPUB_CPP__

#include <clsinfo.h>
#include "elastos.h"

#include "CJavaCallbackInvocationClassObject.h"

#ifndef __UUNM_JavaCallbackInvocation_DEFINED__
#define __UUNM_JavaCallbackInvocation_DEFINED__
#define c_pJavaCallbackInvocationUunm "JavaCallbackInvocation.eco"
#endif // __UUNM_JavaCallbackInvocation_DEFINED__

#ifndef __ECLSID_CJavaCallbackInvocation_DEFINED__
#define __ECLSID_CJavaCallbackInvocation_DEFINED__
EXTERN_C const _ELASTOS ClassID ECLSID_CJavaCallbackInvocation = {
    {0x1F0B2E2A,0x04CC,0x3912,{0x48,0xC4,0x41,0x98,0x43,0x86,0x09,0x12}},
    (char *)c_pJavaCallbackInvocationUunm,
    0x8b489c23 };
#endif // __CLSID_CJavaCallbackInvocation_DEFINED__


#ifndef __ECLSID_CJavaCallbackInvocationClassObject_DEFINED__
#define __ECLSID_CJavaCallbackInvocationClassObject_DEFINED__
EXTERN_C const _ELASTOS ClassID ECLSID_CJavaCallbackInvocationClassObject = {
    {0xC3153923,0x04CC,0x3912,{0x48,0xC4,0x41,0x98,0x43,0x86,0x09,0x12}},
    (char *)c_pJavaCallbackInvocationUunm,
    0x8b489c23 };
#endif // __CLSID_CJavaCallbackInvocationClassObject_DEFINED__


#ifndef __EIID_ICJavaCallbackInvocationClassObject_DEFINED__
#define __EIID_ICJavaCallbackInvocationClassObject_DEFINED__
EXTERN_C const _ELASTOS InterfaceID EIID_ICJavaCallbackInvocationClassObject = \
    {0x25BB6022,0x8312,0x2409,{0x72,0x90,0x88,0x83,0x30,0x87,0x0C,0x13}};
#endif // __EIID_ICJavaCallbackInvocationClassObject_DEFINED__

extern "C" CJavaCallbackInvocationClassObject _g_CJavaCallbackInvocation_ClsObj;
extern CIClassInfo *g_JavaCallbackInvocation_classInfo;

EXTERN_C CARAPI _CarDllGetClassObject(
    REMuid clsid, _ELASTOS REIID riid, IInterface **ppObj)
{
    ECode ec = NOERROR;

    if (ECLSID_ClassInfo == clsid) {
        *ppObj = (IInterface *)g_JavaCallbackInvocation_classInfo;
        return ec;
    }
    return E_CLASS_NOT_AVAILABLE;
}

#ifndef _USE_MY_DLLMAIN_
EXTERN_C Boolean __stdcall DllMain(
    PVoid hDllHandle,
    UInt32 dwReason,
    PVoid preserved)
{
    return TRUE;
}
#endif // _USE_MY_DLLMAIN_

#endif // __CAR_JAVACALLBACKINVOCATIONPUB_CPP__
