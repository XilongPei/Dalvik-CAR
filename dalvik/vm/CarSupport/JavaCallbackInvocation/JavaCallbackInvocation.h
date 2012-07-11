#ifndef __CAR_JAVACALLBACKINVOCATION_H__
#define __CAR_JAVACALLBACKINVOCATION_H__

#ifndef _NO_INCLIST
#include <elastos.h>
#endif // !_NO_INCLIST

#ifndef __UUNM_JavaCallbackInvocation_DEFINED__
#define __UUNM_JavaCallbackInvocation_DEFINED__
#define c_pJavaCallbackInvocationUunm "JavaCallbackInvocation.eco"
#endif // __UUNM_JavaCallbackInvocation_DEFINED__

#ifndef __ECLSID_CJavaCallbackInvocationClassObject_DEFINED__
#define __ECLSID_CJavaCallbackInvocationClassObject_DEFINED__
static const _ELASTOS ClassID ECLSID_CJavaCallbackInvocationClassObject = {
    {0xC3153923,0x04CC,0x3912,{0x48,0xC4,0x41,0x98,0x43,0x86,0x09,0x12}},
    (char *)c_pJavaCallbackInvocationUunm,
    0x8b489c23 };
#endif // __CLSID_CJavaCallbackInvocationClassObject_DEFINED__

#ifndef __EIID_ICJavaCallbackInvocationClassObject_DEFINED__
#define __EIID_ICJavaCallbackInvocationClassObject_DEFINED__
static const _ELASTOS InterfaceID EIID_ICJavaCallbackInvocationClassObject = \
    {0x25BB6022,0x8312,0x2409,{0x72,0x90,0x88,0x83,0x30,0x87,0x0C,0x13}};
#endif // __IID_ICJavaCallbackInvocationClassObject_DEFINED__

interface ICJavaCallbackInvocationClassObject;


#ifdef __cplusplus
#include <_JavaCallbackInvocation.h>



#else // !__cplusplus
#include <_JavaCallbackInvocation_c.h>
#endif // __cplusplus

#endif // __CAR_JAVACALLBACKINVOCATION_H__
