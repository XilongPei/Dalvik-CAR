#undef bool
#undef true
#undef false
#define true 1
#define false 0
#define bool int

#define __bool_true_false_are_defined 1

//#include "utils/Log.h"
extern "C" {

//use /usr/include/string.h
//#define _STRING_H
#define __EL__STRING_H__
#undef  WITH_DALVIK_ASSERT

#include "Dalvik.h"
}

#include "CJavaCallbackInvocation.h"
ECode CJavaCallbackInvocation::Invoke(
    /* [in] */ PVoid pTargetObject,
    /* [in] */ PVoid pTargetMethod,
    /* [in] */ ICallbackArgumentList * pCallbackArgumentList)
{
    // TODO: Add your code here
    ECode ec;
	LOGD("CJavaCallbackInvocation::Invoke %p, %p", (void*)m_threadSelf, (Method*)pTargetMethod);

    //CAR method?
    if (((Method *)pTargetMethod)->pCARMethodInfo != NULL) {
        int          i;
        ClassObject *clz;
        IMethodInfo *pMethodInfo = (IMethodInfo*)((Method *)pTargetMethod)->pCARMethodInfo->pMethodInfo;

        /*
         * in fact, the parameter has been checked:
         * 1. addCallbackHandler
         * 2. dvmSetCARMethodInfo
         */
#if 0
        //check wether the parameter is suited each other
        Int32 paramCount;

        ICallbackMethodInfo* pICallbackMethodInfo = NULL;
        ec = pCallbackArgumentList->GetCallbackMethodInfo(&pICallbackMethodInfo);
        if (FAILED(ec))
            return ec;

    	ec = pICallbackMethodInfo->GetParamCount(&paramCount);
        if (FAILED(ec)) {
    		LOGD("GetParamCount Failed");
    	}

        pICallbackMethodInfo->Release();

        pMethodInfo->GetParamCount(&i);
        if (FAILED(ec)) {
    		LOGD("GetParamCount Failed");
    	}

        if (paramCount != i) {
            LOGE("CAR callback parameters mismatch");
        }

        pICallbackMethodInfo->Release();
#endif

        //find correct CAR 'this' pointer
    	for (i = 0, clz = ((Object *)pTargetObject)->clazz;
    	                             clz != ((Method*)pTargetMethod)->clazz && clz != NULL;
    	                             clz = clz->super) {
            if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS|CLASS_CAR_INTERFACE))
                i++;
        }

    	if (clz == NULL) {
    	    LOGE("CAR this pointer error");
    	} else {
        	u4* pCARObject = (u4*)(((char*)pTargetObject) + ((Object*)pTargetObject)->clazz->objectSize + sizeof(u4)*i);;

            //force to add jniEnv, jniObj? needn't.
            if (pCARObject != NULL)
                pMethodInfo->Invoke((IInterface*)pCARObject, (IArgumentList*)pCallbackArgumentList);
            else
                LOGE("CAR this pointer error");
        }

        return NOERROR;
    }

    Int32 paramCount;
    //JSValueRef* paramValueArray = NULL;
    ICallbackMethodInfo* pICallbackMethodInfo = NULL;
    ec = pCallbackArgumentList->GetCallbackMethodInfo(&pICallbackMethodInfo);
    if (FAILED(ec))
        return ec;

	ec = pICallbackMethodInfo->GetParamCount(&paramCount);
    if (FAILED(ec)) {
		LOGD("GetParamCount Failed");
	}

	jvalue *args;
    if (paramCount > 0) {
		args = (jvalue*)_alloca((paramCount) * sizeof(jvalue));

		ec = OrganizeParameters(pICallbackMethodInfo, pCallbackArgumentList, args, paramCount);
        if (FAILED(ec)) {
            pICallbackMethodInfo->Release();
            LOGD("FAILED OrganizeParameters");
        }
    } else {
        args = NULL;
    }

	JValue  rt;
    Thread *self = dvmThreadSelf();

	dvmChangeStatus(self, THREAD_RUNNING);
	dvmCallMethodA(self, (Method*)pTargetMethod, (Object*)pTargetObject, false, &rt, args);
	dvmChangeStatus(self, THREAD_NATIVE);

    pICallbackMethodInfo->Release();

	return NOERROR;

}

ECode CJavaCallbackInvocation::constructor(
    /* [in] */ PVoid pEnv,
    /* [in] */ PVoid pSelf)
{
    // TODO: Add your code here
	m_jniEnv = pEnv;
	m_threadSelf = pSelf;
	LOGD("pSelf %p %p", pEnv, pSelf);
    return NOERROR;
}

ECode CJavaCallbackInvocation::OrganizeParameters(
    /* [in] */ ICallbackMethodInfo* pICallbackMethodInfo ,
    /* [in] */ ICallbackArgumentList* pCallbackArgumentList,
    /* [in] */ jvalue* args,
    /* [in] */ Int32 paramCount)
{
	BufferOf<IParamInfo*>* pparamInfos;
    IParamInfo* paramInfo = NULL;
    IDataTypeInfo* typeInfo = NULL;

    pparamInfos = BufferOf<IParamInfo*>::Alloc(paramCount);
    if (!pparamInfos) {
        return E_OUT_OF_MEMORY;
    }

    ECode ec = pICallbackMethodInfo->GetAllParamInfos(pparamInfos);
    if (FAILED(ec)) {
        BufferOf<IParamInfo*>::Free(pparamInfos);
        return ec;
    }

    CarDataType dataType;
    for (Int32 i = 0; i < paramCount; i++)
    {
        paramInfo = (*pparamInfos)[i];
        if (NULL == paramInfo) {
            ec = E_NO_INTERFACE;
            goto ERR;
        }

        paramInfo->GetTypeInfo(&typeInfo);
        typeInfo->GetDataType(&dataType);
        switch(dataType) {
            case CarDataType_Int16: {
                Int16 val;
                pCallbackArgumentList->GetInt16Argument(i, &val);
                args[i].i = val;
                break;
            }
            case CarDataType_Int32: {
                Int32 val;
                pCallbackArgumentList->GetInt32Argument(i, &val);
                args[i].i = val;
                break;
            }
            case CarDataType_Int64: {
                Int64 val;
                pCallbackArgumentList->GetInt64Argument(i, &val);
                args[i].j = val;
                break;
            }
            case CarDataType_Float: {
                Float val;
                pCallbackArgumentList->GetFloatArgument(i, &val);
                args[i].f = val;
                break;
            }
            case CarDataType_Double: {
                Double val;
                pCallbackArgumentList->GetDoubleArgument(i, &val);
                args[i].d = val;
                break;
                }
            case CarDataType_String: {
                String val;
                pCallbackArgumentList->GetStringArgument(i, &val);

                break;
                }
/*            case CarDataType_WString: {
                WString val;
                pCallbackArgumentList->GetWStringArgument(i, &val);
                JSStringRef objceIString = JSStringCreateWithUTF8CString((char *)CW2A((wchar_t *)(const wchar_t*)val));
                paramValueArray[i] = JSValueMakeString(m_jsContext,objceIString);
                if (FAILED(ec))
                    goto ERR;
                break;
                }*/
            case CarDataType_Boolean: {
                Boolean val;
                pCallbackArgumentList->GetBooleanArgument(i, &val);

                break;
            }
            case CarDataType_Enum: {
                Int32 val;
                pCallbackArgumentList->GetEnumArgument(i, &val);

                break;
            }
            case CarDataType_Interface: {
                PInterface object = NULL;
                pCallbackArgumentList->GetObjectPtrArgument(i, &object);

                if (FAILED(ec)) goto ERR;
                break;
            }
            case CarDataType_ArrayOf:
            case CarDataType_BufferOf: {
                PCarQuintet value;
                pCallbackArgumentList->GetCarArrayArgument(i, &value);

                break;
            }
            case CarDataType_Struct: {
                void* value;
                pCallbackArgumentList->GetStructPtrArgument(i, &value);

                break;
            }
            case CarDataType_Byte: {
                Byte value;
                pCallbackArgumentList->GetByteArgument(i, &value);

                break;
            }
            case CarDataType_Char8: {
                Char8 value[2];
                pCallbackArgumentList->GetChar8Argument(i, &(value[0]));
                value[1] = '\0';

                break;
            }
            case CarDataType_Char16: {
                Char16 value;
                pCallbackArgumentList->GetChar16Argument(i, &value);

                break;
            }
            case CarDataType_EMuid: {
                EMuid *val;
                pCallbackArgumentList->GetEMuidArgument(i, &val);

                break;
            }
            case CarDataType_EGuid: {
                EGuid *val;
                pCallbackArgumentList->GetEGuidArgument(i, &val);

                break;
            }
            case CarDataType_ECode: {
                ECode val;
                pCallbackArgumentList->GetECodeArgument(i, &val);

                break;
            }
            default:
                assert(0 && " not implemented");
                break;
        }
        typeInfo->Release();
        paramInfo->Release();
    }
    BufferOf<IParamInfo *>::Free(pparamInfos);
    return NOERROR;

ERR:
    for (Int32 i = 0; i < paramCount; i++) {
        if ((*pparamInfos)[i]) (*pparamInfos)[i]->Release();
    }
    BufferOf<IParamInfo *>::Free(pparamInfos);
    return ec;

	return NOERROR;
}
