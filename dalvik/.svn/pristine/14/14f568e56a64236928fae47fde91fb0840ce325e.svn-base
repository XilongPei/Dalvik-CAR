
#ifndef __CJAVACALLBACKINVOCATION_H__
#define __CJAVACALLBACKINVOCATION_H__

//extern "C" {
//#include "jni.h"
//}

#include "_CJavaCallbackInvocation.h"

CarClass(CJavaCallbackInvocation)
{
public:
    CARAPI Invoke(
        /* [in] */ PVoid pTargetObject,
        /* [in] */ PVoid pTargetMethod,
        /* [in] */ ICallbackArgumentList * pCallbackArgumentList);

    CARAPI constructor(
        /* [in] */ PVoid pEnv,
        /* [in] */ PVoid pSelf);

private:
    // TODO: Add your private member variables here.
    ECode OrganizeParameters(
    /* [in] */ ICallbackMethodInfo* pICallbackMethodInfo ,
    /* [in] */ ICallbackArgumentList* pCallbackArgumentList, 
    /* [in] */ jvalue* args,
    /* [in] */ Int32 paramCount);
    
    void*	m_jniEnv;
	void*   m_threadSelf;
};

#endif // __CJAVACALLBACKINVOCATION_H__
