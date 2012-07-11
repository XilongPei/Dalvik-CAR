/**
  * ElastosBridgeApi.cpp
  */

#undef bool
#undef true
#undef false
#define true 1
#define false 0
#define bool int

#define __bool_true_false_are_defined 1

#define DEFAULT_ARRAY_SIZE 10

extern "C" {

//use /usr/include/string.h
//#define _STRING_H
#define __EL__STRING_H__

#define _DALVIK_INDIRECTREFTABLE
#define _DALVIK_REGISTERMAP
#undef  WITH_DALVIK_ASSERT

#define _LIBDEX_INSTRUTILS
typedef unsigned char InstructionFormat;
typedef signed char InstructionWidth;
typedef unsigned char InstructionFlags;

#define _DALVIK_VM_COMPILER
//in Elastos, we won't use JIT
typedef int CompilerWorkOrder;
typedef int ICPatchWorkOrder;
#define COMPILER_WORK_QUEUE_SIZE        100
#define COMPILER_IC_PATCH_QUEUE_SIZE    64

#define _DALVIK_OO_OBJECTINLINES

#include "Dalvik.h"

#undef _DALVIK_INDIRECTREFTABLE
#undef InstructionFormat
#undef InstructionWidth
#undef InstructionFlags


#undef _DALVIK_REGISTERMAP
#undef _LIBDEX_INSTRUTILS

#undef _DALVIK_VM_COMPILER
#undef CompilerWorkOrder
#undef ICPatchWorkOrder
#undef COMPILER_WORK_QUEUE_SIZE
#undef COMPILER_IC_PATCH_QUEUE_SIZE


#undef _DALVIK_OO_OBJECTINLINES
#undef INLINE

#include "jni.h"
#include "libdex/OptInvocation.h"
// mayq, add, to include kTypeString etc.
#include "ElastosBridgeApi.h"
}

#include "elastos.h"
#include "CJavaCallbackInvocation.h"

#define METHOD_INDEX(n)             ((n) & 0x0000FFFF)
#define INTERFACE_INDEX(n)			(((n)>>16)-2)

//come from  $\ElastosDll\reflection\CMethodInfo.cpp
struct VTable  {   void* methods[1];  };
typedef struct VTable VTable;
struct VObject {   VTable* vtab;      };
typedef struct VObject VObject;


struct CMethodInfo {
	void* pThis;
	void* pMethodDescript;
	UInt32 m_uIndex;
};

static bool IsCallback(char *name, IClassInfo *pClassInfo, ICallbackMethodInfo **callbackInfo);
static ICallbackInvocation* AcquireCallbackInvocation(JNIEnv* env);
static ECode GetMethodInfoAndInterfaceIndex(IClassInfo *pClassInfo, char *methodName, u2 *interfaceIndex, IMethodInfo **pMethodInfo);
static int allParamArePrimitive(const Method *method);
static u4 CreateCARSingletonObject(IClassInfo *pClassInfo);
static bool checkCarSetterGetterOfField(IMethodInfo *pMethodInfo);
static bool checkJavaSetterGetterOfField(Field *field, Method *meth);
static int checkClassForOutInterface(Method *method, const char *returnDesc, char *pInterfaceName);
static bool checkCompatibilityOfIFunctionInfoAndMethod(IFunctionInfo *pIFun, Method *meth);
static void releaseCARMethodInfoInside(Method* meth, Int32 paramCount);
static void insideThrowException(const char* msg);


bool dvmElapiInitialize()
{
	LOGD("dvmElapiInitialize");
	return ElapiInitialize();
}

void dvmElapiUninitialize()
{
	LOGD("dvmElapiUninitialize");
	ElapiUninitialize();
}

bool dvmSetCARClassInfo(/*const*/ ClassObject* clazz)
{
	char *CARModule = dvmGetCARClassAnnotationValue(clazz, (char*)"Module");
	char *CARClass = dvmGetCARClassAnnotationValue(clazz, (char*)"Class");
	char *CARSingletonClass = dvmGetCARClassAnnotationValue(clazz, (char*)"SingletonClass");

	if (CARModule == NULL /*|| CARClass == NULL*/) {

	    /** TODO!
	      * support these annotation information come from a service java object
	      * which work according to a config file
	      * then, Dalvik&CAR will work dynamically
	      */

		LOGE("Can not create class object without module name or class name");
	    char buf[512];
	    snprintf(buf, sizeof(buf)-1, "Can not create class object without module name or class name:%s", clazz->descriptor);
	    insideThrowException(buf);
		return false;
	}

	LOGD("We set CAR class from the %s , %s",CARModule, CARClass);
	IModuleInfo *pModuleInfo;
	ECode ec;

    /**
     * CARModule should in the same directory with java class file,
     * clazz->pDvmDex->pDexFile->dexFilePath;
     *
     * OR
     * in the Elastos system directory
     */
    char *cachedName;

    if (clazz->pDvmDex != NULL) {
        cachedName = dexOptGenerateCacheFileName(clazz->pDvmDex->pDexFile->dexFilePath, CARModule);
        if (cachedName == NULL) {
    	    LOGD("dexOptGenerateCacheFileName Failed");

    	    char buf[512];
    	    snprintf(buf, sizeof(buf)-1, "dexOptGenerateCacheFileName Failed:%s", clazz->descriptor);
	        insideThrowException(buf);
    	    return false;
        }
    } else {
        cachedName = CARModule;
    }

	dvmHashTableLock(gDvm.nativeLibs);
	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(cachedName, kAddRefCount, NULL);
	if (pModuleInfo == NULL) {
	    ec = _CReflector_AcquireModuleInfo(cachedName, &pModuleInfo);
	    if (FAILED(ec)) {
		    if (clazz->pDvmDex != NULL) {
                //continue search CAR in Elastos system path
            	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(CARModule, kAddRefCount, NULL);
            	if (pModuleInfo == NULL) {
            	    ec = _CReflector_AcquireModuleInfo(CARModule, &pModuleInfo);
            	    if (FAILED(ec)) {
		                LOGD("_CReflector_AcquireModuleInfo Failed:%s", CARModule);
            	        dvmHashTableUnlock(gDvm.nativeLibs);
		                free(cachedName);

                	    char buf[512];
                	    snprintf(buf, sizeof(buf)-1, "_CReflector_AcquireModuleInfo Failed:%s", CARModule);
	                    insideThrowException(buf);

            		    return false;
            		}
  		    		if (addHashCARModuleInfo(CARModule, pModuleInfo) == NULL) {
    		            LOGD("add hash _CReflector_AcquireModuleInfo Failed");
    		        }
    		    }
    		}
		} else {
    		if (addHashCARModuleInfo(cachedName, pModuleInfo) == NULL) {
    		    LOGD("add hash _CReflector_AcquireModuleInfo Failed");
    		}
		}
	}
	dvmHashTableUnlock(gDvm.nativeLibs);

    if (clazz->pDvmDex != NULL)
	    free(cachedName);

	IClassInfo *pClassInfo;
	LOGD("pClassInfo %p", pClassInfo);
	if (CARClass != NULL && *CARClass != '\0') {
    	ec = pModuleInfo->GetClassInfo(CARClass, &pClassInfo);
    	LOGD("pClassInfo %p", pClassInfo);
    	if (FAILED(ec)) {
    		LOGD("GetClassInfo Failed");

    	    char buf[512];
    	    snprintf(buf, sizeof(buf)-1, "GetClassInfo Failed:%s", CARClass);
	        insideThrowException(buf);

    		return false;
    	}

    	clazz->pClassInfo = (u4)pClassInfo;

        IConstructorInfo *p;
        ec = pClassInfo->GetConstructorInfoByParamCount(3, &p);
	    if (FAILED(ec)) {
    	    clazz->pConstructorInfo = NULL;
    	} else {
    	    clazz->pConstructorInfo = (u4)p;
        }

#ifdef WITH_COPYING_GC
        u2  interfaceIndex;
        IMethodInfo *pMethodInfo;

        ec = GetMethodInfoAndInterfaceIndex(pClassInfo, (char*)"JavaObjMoved", &interfaceIndex, &pMethodInfo);
        if (FAILED(ec)) {
            clazz->pCARFunJavaObjMoved = 0;
        } else {
            clazz->pCARFunJavaObjMoved = ((u4)pMethodInfo)|IMethodInfoInU4_Mask;
            clazz->interfaceIndex = interfaceIndex;
        }
#endif

    } else {
    	clazz->pClassInfo = NULL;
    }

    if (CARSingletonClass != NULL && *CARSingletonClass != '\0') {
    	ec = pModuleInfo->GetClassInfo(CARSingletonClass, &pClassInfo);
    	LOGD("pClassInfo %p", pClassInfo);
    	if (FAILED(ec)) {
    		LOGD("GetClassInfo Failed");

    	    char buf[512];
    	    snprintf(buf, sizeof(buf)-1, "GetClassInfo Failed:%s", CARSingletonClass);
	        insideThrowException(buf);

    		return false;
    	}
        clazz->pStaticClassInfo = (u4)pClassInfo;

    	//system, static CAR component
    	dvmHashTableLock(gDvm.globalCARClass);
    	//if (strcmp(CARModule, "Elastos.CAR") != 0) {
    	Boolean  tf;
    	pClassInfo->IsSingleton(&tf);
    	if (tf) {

            /*
    	     * cause the CAR environment to initialize its singleton class object.
    	     *
             * clazz->pCARSingletonObject needn't to be managed, another calling of
             * dvmCreateCARSingletonClassObject() will return the same one.
             */
            clazz->pCARSingletonObject = (u4)dvmCreateCARSingletonClassObject(clazz, NULL);

    	    //if addHashCARClass cause error, it will dvmAbort();
    	    pClassInfo->AddRef();
    	    addHashCARClass(CARSingletonClass, (void*)clazz);
    	} else {
    	    //warnning
    	    char buf[512];

            clazz->pStaticClassInfo = (u4)NULL;

    	    snprintf(buf, sizeof(buf)-1, "CARSingletonClass should be a Singleton:%s", CARSingletonClass);
	        insideThrowException(buf);

    	    dvmHashTableUnlock(gDvm.globalCARClass);
    		return false;
    	}
    	dvmHashTableUnlock(gDvm.globalCARClass);

    } else {
        clazz->pStaticClassInfo = NULL;
    }

	return true;
}

bool dvmSetCARInterfaceInfo(/*const*/ ClassObject* clazz)
{
	char* CARModule = dvmGetCARInterfaceAnnotationValue(clazz, (char*)"Module");
	char* CARInterface = dvmGetCARInterfaceAnnotationValue(clazz, (char*)"Interface");
	if(CARModule == NULL || CARInterface == NULL || *CARModule == '\0' || *CARInterface == '\0' ){
		LOGE("Can not create class object without module name or class name");

	    char buf[512];
	    snprintf(buf, sizeof(buf)-1, "Can not create class object without module name or class name:%s", clazz->descriptor);
	    insideThrowException(buf);

		return false;
	}

	LOGD("We set CAR Interface from the %s , %s",CARModule, CARInterface);
	IModuleInfo *pModuleInfo;
	ECode ec;

    /**
     * CARModule should in the same directory with java class file,
     * clazz->pDvmDex->pDexFile->dexFilePath;
     *
     * OR
     * in the Elastos system directory
     */
    char *cachedName;

    if (clazz->pDvmDex != NULL) {
        cachedName = dexOptGenerateCacheFileName(clazz->pDvmDex->pDexFile->dexFilePath, CARModule);
        if (cachedName == NULL) {
    	    LOGD("dexOptGenerateCacheFileName Failed");

    	    char buf[512];
            snprintf(buf, sizeof(buf)-1, "dexOptGenerateCacheFileName Failed:%s", clazz->descriptor);
	        insideThrowException(buf);

    	    return false;
        }
    } else {
        cachedName = CARModule;
    }

	dvmHashTableLock(gDvm.nativeLibs);
	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(cachedName, kAddRefCount, NULL);
	if( pModuleInfo == NULL ) {
	    ec = _CReflector_AcquireModuleInfo(cachedName, &pModuleInfo);
	    if (FAILED(ec)) {
		    if (clazz->pDvmDex != NULL) {
                //continue search CAR in Elastos system path
            	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(CARModule, kAddRefCount, NULL);
            	if (pModuleInfo == NULL) {
            	    ec = _CReflector_AcquireModuleInfo(CARModule, &pModuleInfo);
            	    if (FAILED(ec)) {
		                LOGD("_CReflector_AcquireModuleInfo Failed:%s", CARModule);
            	        dvmHashTableUnlock(gDvm.nativeLibs);
		                free(cachedName);

                	    char buf[512];
                        snprintf(buf, sizeof(buf)-1, "_CReflector_AcquireModuleInfo Failed:%s", CARModule);
	                    insideThrowException(buf);

            		    return false;
            		}
  		    		if (addHashCARModuleInfo(CARModule, pModuleInfo) == NULL) {
    		            LOGD("add hash _CReflector_AcquireModuleInfo Failed");
    		        }
    		    }
    		}
		} else {
    		if (addHashCARModuleInfo(cachedName, pModuleInfo) == NULL) {
    		    LOGD("add hash _CReflector_AcquireModuleInfo Failed");
    		}
		}
	}
	dvmHashTableUnlock(gDvm.nativeLibs);

    if (clazz->pDvmDex != NULL)
	    free(cachedName);

	IInterfaceInfo *pInterfaceInfo;
	ec = pModuleInfo->GetInterfaceInfo(CARInterface, &pInterfaceInfo);
	if (FAILED(ec)) {
		LOGD("GetClassInfo Failed");

	    char buf[512];
        snprintf(buf, sizeof(buf)-1, "GetClassInfo Failed:%s", CARInterface);
	    insideThrowException(buf);

		return false;
	}

	clazz->pClassInfo = (u4)pInterfaceInfo;

	return true;
}


u4 dvmCreateCARClassObject(const ClassObject *clazz, const Object *object)
{
	LOGD("dvmCreateCARClassObject");

	IClassInfo       *pClassInfo;
	PInterface        pObject;
	ECode             ec;

	pClassInfo = (IClassInfo*)(clazz->pClassInfo);

    /*
     * we cache the ConstructorInfo to speed up the dvmCreateCARClassObject()
     *
    IConstructorInfo *pConstructorInfo;
	ec = pClassInfo->GetConstructorInfoByParamCount(3, &pConstructorInfo);
	if (FAILED(ec)) {
	*/
	if (clazz->pConstructorInfo == (u4)NULL) {
    	ec = pClassInfo->CreateObject(&pObject);
    } else {
        Thread  *self = dvmThreadSelf();

        if (self->pArgumentList == (u4)NULL) {

            IArgumentList *pArgumentList;

            ec = ((IConstructorInfo*)clazz->pConstructorInfo)->CreateArgumentList(&pArgumentList);
            if (SUCCEEDED(ec)) {
                self->pArgumentList = (u4)pArgumentList;
                pArgumentList->SetInputArgumentOfInt32(0, (int)(self->jniEnv));
                pArgumentList->SetInputArgumentOfInt32(1, (int)clazz);
                pArgumentList->SetInputArgumentOfInt32(2, (int)object);
                ec = ((IConstructorInfo*)clazz->pConstructorInfo)->CreateObject(pArgumentList, &pObject);
                //pArgumentList->Release();
            }
        } else {
            typedef struct tagMyCArgumentList {
                void  *thisPtr;
                unsigned int *m_pParamBuf;
            } MyCArgumentList;

            unsigned int *buf;

            buf = ((MyCArgumentList*)(self->pArgumentList))->m_pParamBuf;
            buf[1] = (int)self->jniEnv;
            buf[2] = (int)clazz;
            buf[3] = (int)object;

            ec = ((IConstructorInfo*)clazz->pConstructorInfo)->CreateObject((IArgumentList*)self->pArgumentList, &pObject);
        }

        //ConstructorInfo has been cached
        //pConstructorInfo->Release();
    }

	if (FAILED(ec)) {
		LOGD("CreateObject Failed");
	    char buf[512];

	    snprintf(buf, sizeof(buf)-1, "CreateObject Failed: (ECode = %d)%s", ec, clazz->descriptor);
	    dvmThrowException("Ljava/lang/NullPointerException;", buf);
		return NULL;
	}


	return (u4)pObject;
}


/**
 * Constructor of CAR singleton class can't have any parameter!
 */
u4 dvmCreateCARSingletonClassObject(const ClassObject *clazz, const Object *object)
{
	LOGD("dvmCreateCARClassObject");

	IClassInfo       *pClassInfo;
	PInterface        pObject;
	ECode             ec;
    IMethodInfo      *pMethodInfo;

	pClassInfo = (IClassInfo*)(clazz->pStaticClassInfo);

    ec = pClassInfo->CreateObject(&pObject);
	if (FAILED(ec)) {
		LOGD("CreateObject Failed");
	    char buf[512];

	    snprintf(buf, sizeof(buf)-1, "CreateObject Failed: (ECode = %d)%s", ec, clazz->descriptor);
	    dvmThrowException("Ljava/lang/NullPointerException;", buf);
		return NULL;
	}

    ec = pClassInfo->GetMethodInfo("SingletonInit", &pMethodInfo);
	if (SUCCEEDED(ec)) {
#if 1
        IArgumentList    *pArgumentList;

        ec = pMethodInfo->CreateArgumentList(&pArgumentList);
        if (SUCCEEDED(ec)) {
            IFunctionInfo *functionInfo;
            int            count;
            pArgumentList->GetFunctionInfo(&functionInfo);
            functionInfo->GetParamCount(&count);
            LOGD("param count %d", count);

            pArgumentList->SetInputArgumentOfInt32(0, (int)(dvmThreadSelf()->jniEnv));
            pArgumentList->SetInputArgumentOfInt32(1, /*((int)clazz*/0);
            pArgumentList->SetInputArgumentOfInt32(2, /*(int)object*/0);
            ec = pMethodInfo->Invoke(pObject, pArgumentList);
            pArgumentList->Release();
        }
#else
        struct MyCArgumentList {
            void  *thisPtr;
            unsigned int *m_pParamBuf;
        } myArgumentList;
        unsigned int buf[4];

        myArgumentList.m_pParamBuf = (unsigned int *)&buf[0];
        buf[1] = (int)dvmThreadSelf()->jniEnv;
        buf[2] = (int)clazz;
        buf[3] = (int)object;
        ec = pMethodInfo->Invoke(pObject, (IArgumentList*)&myArgumentList);
#endif
        pMethodInfo->Release();
    }


	return (u4)pObject;
}




void dvmReleaseCARClassObject(const u4 pObject)
{
    if ((void*)pObject != NULL )
	    ((PInterface)pObject)->Release();
}

void dvmReleaseCARClassInfo(ClassObject* clazz)
{
	LOGD("dvmReleaseCARClassInfo");

	if ((void*)clazz->pClassInfo != NULL) {
	    IClassInfo *pClassInfo = (IClassInfo*)clazz->pClassInfo;
	    clazz->pClassInfo = NULL;
	    pClassInfo->Release();
    }
	if ((void*)clazz->pStaticClassInfo != NULL) {
	    IClassInfo *pStaticClassInfo = (IClassInfo*)clazz->pStaticClassInfo;
	    clazz->pStaticClassInfo = NULL;
	    pStaticClassInfo->Release();
    }
}

static IEnumInfo* getEnumInfo(String enumName, IClassInfo* pClassInfo)
{
	IModuleInfo* pModuleInfo;
	IEnumInfo* pEnumInfo;
	if(pClassInfo == NULL){
		LOGW("Can not Get Enum info from a class of NULL");
		return NULL;
	}

	ECode ec = pClassInfo->GetModuleInfo(&pModuleInfo);
	if (FAILED(ec)) {
		LOGW("FAILED in GetModuleInfo in CAR");
		return NULL;
	}

	ec = pModuleInfo->GetEnumInfo(enumName, &pEnumInfo);
	if (FAILED(ec)) {
		LOGW("FAILED in GetEnumInfo in CAR");
		pModuleInfo->Release();
		return NULL;
	}

	pModuleInfo->Release();
	return pEnumInfo;
}

/*
 * check the parameter and fill the Method->inParameterTranformRule, and Method->outParameterTranformRule
 * with ParameterTranformRule (defined in Object.h)
 *
 * exception definaion:
 * 1.parameter error: dvmThrowException("Ljava/lang/IllegalArgumentException;",
 *                    parameterName+" in "+methodName+" in "+moduleName+" in "+CARClassName););
 * 2.memory error: dvmThrowException("Ljava/lang/OutOfMemoryError;",
 *                    "recent alloc");
 * 3.no method: dvmThrowException("Ljava/lang/NoSuchMethodError;",
 *                    CARClassName+" in "+moduleName);
 *
 * return:
 *     success: -1
 *     fail: 0..paramCount
 */
int dvmSetCARMethodInfo(Method* meth)
{
	LOGD("dvmSetCARMethodInfo");
	ClassObject     *clazz = meth->clazz;
	IMethodInfo     *pMethodInfo = NULL;
	IClassInfo      *pClassInfo = NULL;
	IInterfaceInfo  *pInterfaceInfo = NULL;
	ECode            ec = -1;
    Int32            paramCount;
    Int32            i, k, outParamNum;
    IParamInfo      *pParamInfo = NULL;
    IDataTypeInfo   *pTypeInfo = NULL;
    IDataTypeInfo   *pElementTypeInfo = NULL;
    CarDataType      dataType;
	ParamIOAttribute ioAttrib;
	CARMethodInfo   *p;
	const char      **paramDesc;
    StringBuf_<256>  pName;
    u2               interfaceIndex = 0;
    char            *methodName;
	ClassObject     *clazz2;
    Method          *methodEnum, *methodEnum2;


	int size = 0;

    methodName = dvmGetCARMethodAnnotationValue(meth, (char*)"value");
    if (methodName == NULL || *methodName == '\0')
        methodName = (char*)meth->name;

	if (IS_CLASS_FLAG_SET(clazz, CLASS_CAR_CLASS)) {

	    if (dvmIsStaticMethod(meth))
		    pClassInfo = (IClassInfo*)(clazz->pStaticClassInfo);
		else
		    pClassInfo = (IClassInfo*)(clazz->pClassInfo);

		if (pClassInfo != NULL) {
		    //ec = pClassInfo->GetMethodInfo(meth->name, &pMethodInfo);
		    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, methodName, &interfaceIndex, &pMethodInfo);
		}
	} else if (IS_CLASS_FLAG_SET(clazz, CLASS_CAR_INTERFACE)){
		pInterfaceInfo = (IInterfaceInfo*)(clazz->pClassInfo);
		//when an object is (interface)CARed java object, its 'this' pointer needn't to be adjusted
		interfaceIndex = 1;

		if (pInterfaceInfo != NULL)
		    ec = pInterfaceInfo->GetMethodInfo(methodName, &pMethodInfo);
	}

#if 0
    if (FAILED(ec)) {
        if (strcmp(methodName, "constructor") == 0) {
            IConstructorInfo *pConstructorInfo;

            //first byte in shorty holds return type
            i = strlen(meth->shorty) - 1;

            /*
             * IConstructorInfo(contains m_pMethodInfo) INHERIT-> IFunctionInfo INHERIT-> IInterface
             * IMethodInfo INHERIT-> IFunctionInfo INHERIT-> IInterface
             */
            ec = pClassInfo->GetConstructorInfoByParamCount(i, &pConstructorInfo);

            if (SUCCEEDED(ec))
                pMethodInfo = ((CConstructorInfo*)pConstructorInfo)->m_pMethodInfo;
        }

/******
//
// every static native method must provided by its SingletonClass
// or
// which is 'this' pointer when refering to the method?
//
        else {
            //look the global CAR singleton classes for method information,
            //we take CAR singleton classes as global static
            for (i = 0; i < gDvm.globalCARClass->tableSize; i++) {
                HashEntry* pEnt = &gDvm.globalCARClass->pEntries[i];
                if (pEnt->data != NULL && pEnt->data != HASH_TOMBSTONE) {

                    ClassObject  *clz = (ClassObject*)pEnt->data;

	                if (dvmIsStaticMethod(meth)) {
                        pClassInfo = (IClassInfo*)clz->pStaticClassInfo;
                    } else {
                        pClassInfo = (IClassInfo*)clz->pClassInfo;
                    }

            		if (pClassInfo != NULL) {
            		    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, methodName, &interfaceIndex, &pMethodInfo);
    	                if (SUCCEEDED(ec))
    	                    break;
    	            }
    	        }
            }
        }
******/
    }
#endif

    if (FAILED(ec)) {
#if 0
//this could occures when the native method is not in the CAR but in a native library
        char buf[512];
        StringBuf_<256> pName;
        IModuleInfo *pModuleInfo;

		LOGE("GetMethodInfo Failed");

		if (IS_CLASS_FLAG_SET(clazz, CLASS_CAR_CLASS)) {
		    pClassInfo->GetName(pName);
		    strcpy(buf, (char *)pName);
		    pName.SetEmpty();

            ec = pClassInfo->GetModuleInfo(&pModuleInfo);
            if (!FAILED(ec)) {
                pModuleInfo->GetPath(&pName);
		        pModuleInfo->Release();
		        strcat(buf, " in ");
		        strcat(buf, (char *)pName);
		    }
		} else if (IS_CLASS_FLAG_SET(clazz, CLASS_CAR_INTERFACE)) {
		    pInterfaceInfo->GetName(pName);
		    strcpy(buf, (char *)pName);
		    pName.SetEmpty();

            ec = pInterfaceInfo->GetModuleInfo(&pModuleInfo);
            if (!FAILED(ec)) {
                pModuleInfo->GetPath(&pName);
		        pModuleInfo->Release();
		        strcat(buf, " in ");
		        strcat(buf, (char *)pName);
		    }
		} else buf[0] = '\0';

		dvmThrowException("Ljava/lang/NoSuchMethodError;", buf);
#endif
        //set it with 1 to signal that it (perhaps) is a native method
        meth->pCARMethodInfo = (CARMethodInfo*)1;
		return 0;
    }

    //dvmLinearAlloc will abort the VM on failure, so it's not necessary to check for a NULL return value.
	p = (CARMethodInfo*)dvmLinearAlloc(clazz->classLoader, sizeof(CARMethodInfo));
    p->pMethodInfo = (u4)pMethodInfo;
	p->regTypes = (u4*)dvmLinearAlloc(clazz->classLoader, (meth->insSize+1)*sizeof(u4)); //+1 for outs
	p->regExtraData = (u4*)dvmLinearAlloc(clazz->classLoader, (meth->insSize+1)*sizeof(u4)); // +1 for outs

	paramDesc = (const char**)_alloca((meth->insSize+1)*sizeof(char *));

	p->needCopy = false;
	p->interfaceIndex = interfaceIndex-1;
	meth->pCARMethodInfo = p;
	int actualArgs = 0;
    /*
     * regTypes defination:
     *                     1                   2                   3
     * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     * \_____________________________/ \_____________/           | \_/
     *  ParamTypeExtra                  ParamType                |  paramInOutAttribute
     *                                                           |
     *                                                           isParamPrimitive
     */
	//the first param in argv is this point.
	u4* regTypes = meth->pCARMethodInfo->regTypes;
	u4* regExtraData = meth->pCARMethodInfo->regExtraData;
	//set paramInOutAttribute = carParamIOAttribute_In
	regTypes[actualArgs] = 1<<30;
	//set isParamPrimitive to true
	regTypes[actualArgs] |= 1<<29;
    actualArgs++;
    //examine the parameters
    pMethodInfo->GetParamCount(&paramCount);
    //get java method signature info
    DexParameterIterator iterator;

    dexParameterIteratorInit(&iterator, &(meth->prototype));
    const char* protoDesc = dexParameterIteratorNextDescriptor(&iterator);
    k = 0;
    while (protoDesc != NULL) {
        paramDesc[k++] = protoDesc;
        protoDesc = dexParameterIteratorNextDescriptor(&iterator);
    }

    //should consider the condition that the last 2 paramaters are [env, obj]
//    if (i != paramCount-1) {
//
//        // ... i
//        //     |
//        // ... [in] Int32 jniEnv, [in] Int32 jniObj)
//        // ... [out] ...
//        //
//
//        LOGD("[ERROR] parameter number mismatch");

//        pMethodInfo->GetParamInfoByIndex(i++, &pParamInfo);
//		pParamInfo->GetIOAttribute(&ioAttrib);
//        pParamInfo->GetTypeInfo(&pTypeInfo);
//        pTypeInfo->GetDataType(&dataType);
//        pParamInfo->GetName(pName);
//        pTypeInfo->Release();
//        pParamInfo->Release();
//
//        if (ioAttrib == ParamIOAttribute_In && ((dataType != CarDataType_Int32) || strcmp((char *)pName, "jniEnv") != 0)) {
//            dvmThrowException("Ljava/lang/IllegalArgumentException;", (char *)pName);
//            return  false;
//        }
//
//        i++;
//        if (i != paramCount) {
//            pMethodInfo->GetParamInfoByIndex(i++, &pParamInfo);
//            pParamInfo->Release();
//            pParamInfo->GetTypeInfo(&pTypeInfo);
//            pTypeInfo->GetDataType(&dataType);
//            pParamInfo->GetName(pName);
//            pTypeInfo->Release();
//            pParamInfo->Release();
//
//            if ((dataType != CarDataType_Int32) || (strcmp((char *)pName, "jniObj") != 0)) {
//                dvmThrowException("Ljava/lang/IllegalArgumentException;", (char *)pName);
//                return  false;
//            }
//            i++;

//            if (i != paramCount) {
//                dvmThrowException("Ljava/lang/IllegalArgumentException;", NULL);
//                return  false;
//            }
//
//            paramCount -= 2;
//
//        }
//    }
    //paramDesc[i++] = dexProtoGetReturnType(proto);

    /*
     *  Hints:
     *    In, input parameter
     *    Out, output parameter
     *
     *  Rule:
     *    Java parameter: Out Foo(In1, In2, In3, ... InN)
     *    CAR  parameter: Foo(In1, In2, In3, ... InK, Out)
     *                    or
     *                    Foo(In1, In2, In3, ... InK, Out, JNIEnv, JObject)
     *
     *    if N != K  --> E_INVALID_ARGUMENT
     */
    outParamNum = 0;
    for (i = 0; i < paramCount; i++) {
        pMethodInfo->GetParamInfoByIndex(i, &pParamInfo);
		pParamInfo->GetIOAttribute(&ioAttrib);
        pParamInfo->GetTypeInfo(&pTypeInfo);
        pTypeInfo->GetDataType(&dataType);

		if (ioAttrib == ParamIOAttribute_In) {
			regTypes[actualArgs] = 1<<30;
		    switch (dataType) {
		        case CarDataType_Char8:
		        case CarDataType_Char16:
		        case CarDataType_Byte:
		        case CarDataType_Int16:
		        case CarDataType_Int32:
		        case CarDataType_Float:
		        case CarDataType_ECode:
				case CarDataType_Boolean:
					regTypes[actualArgs] |= 1<<29;
					actualArgs++;
					break;
				case CarDataType_Int64:
				case CarDataType_Double:
					regTypes[actualArgs] |= 1<<29;
					regTypes[actualArgs+1] = 1<<30;
					regTypes[actualArgs+1] |= 1<<29;
					actualArgs += 2;
					break;
		        case CarDataType_String:
					regTypes[actualArgs] |= kTypeString<<16;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
				case CarDataType_StringBuf:
					regTypes[actualArgs] |= kTypeStringBuffer<<16;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
				case CarDataType_ArrayOf:
					regTypes[actualArgs] |= kTypeArrayOf<<16;
					((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
					pElementTypeInfo->GetDataType(&dataType);
					pElementTypeInfo->Release();
					switch(dataType){
						case CarDataType_Boolean:
							regTypes[actualArgs] |= kTypeBoolean<<8;
							break;
						case CarDataType_Byte:
							regTypes[actualArgs] |= kTypeByte<<8;
							break;
						case CarDataType_Char8:
		        		case CarDataType_Char16:
	   						regTypes[actualArgs] |= kTypeChar<<8;
							break;
		        		case CarDataType_Int16:
							regTypes[actualArgs] |= kTypeShort<<8;
							break;
		        		case CarDataType_Int32:
							regTypes[actualArgs] |= kTypeInt<<8;
							break;
						case CarDataType_Int64:
							regTypes[actualArgs] |= kTypeLong<<8;
							break;
						case CarDataType_Float:
							regTypes[actualArgs] |= kTypeFloat<<8;
							break;
						case CarDataType_Double:
							regTypes[actualArgs] |= kTypeDouble<<8;
							break;
						default:
							LOGE("Not Implement");
					}
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
				case CarDataType_BufferOf:
					regTypes[actualArgs] |= kTypeBufferOf<<16;
					((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
					pElementTypeInfo->GetDataType(&dataType);
					pElementTypeInfo->Release();
					switch(dataType){
						case CarDataType_Boolean:
							regTypes[actualArgs] |= kTypeBoolean<<8;
							break;
						case CarDataType_Byte:
							regTypes[actualArgs] |= kTypeByte<<8;
							break;
						case CarDataType_Char8:
		        		case CarDataType_Char16:
	   						regTypes[actualArgs] |= kTypeChar<<8;
							break;
		        		case CarDataType_Int16:
							regTypes[actualArgs] |= kTypeShort<<8;
							break;
		        		case CarDataType_Int32:
							regTypes[actualArgs] |= kTypeInt<<8;
							break;
						case CarDataType_Int64:
							regTypes[actualArgs] |= kTypeLong<<8;
							break;
						case CarDataType_Float:
							regTypes[actualArgs] |= kTypeFloat<<8;
							break;
						case CarDataType_Double:
							regTypes[actualArgs] |= kTypeDouble<<8;
							break;
						default:
							LOGE("Not Implement");
					}
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
                case CarDataType_Enum:
                    /*
                     * check wether it is a enum class
                     *
                     * we check methods of the class, for enum could be a lot of pattern
                     */
    				clazz2 = dvmFindClass(paramDesc[i], meth->clazz->classLoader);
    				if (clazz2 == NULL) {
					    LOGD("pTypeInfo->GetId error");
                        pParamInfo->Release();
                        pTypeInfo->Release();
        		        return  i;
        		    }

    				methodEnum = dvmFindDirectMethodHierByDescriptor(clazz2, "valueOf", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Enum;");
    			    methodEnum2 = dvmFindVirtualMethodHierByDescriptor(clazz2, "name", "()Ljava/lang/String;");
    				if (methodEnum == NULL || methodEnum2 == NULL) {
					    LOGD("CarDataType_Enum error");
                        pParamInfo->Release();
                        pTypeInfo->Release();
                        releaseCARMethodInfoInside(meth, i);
        		        return  i;
        		    }

					regTypes[actualArgs] |= kTypeEnum<<16;
					meth->pCARMethodInfo->needCopy = true;
					pTypeInfo->GetName(&pName);
					regExtraData[actualArgs] = (u4)getEnumInfo(pName.GetPayload(), pClassInfo);
					actualArgs++;
					break;
				case CarDataType_Interface:
				    if (*paramDesc[i] != 'L') {
				        dvmThrowException("Ljava/lang/IllegalArgumentException;", paramDesc[i]);
				        break;
				    }

				    InterfaceID iid;

				    ec = ((IInterfaceInfo*)pTypeInfo)->GetId(&iid);
				    if (FAILED(ec)) {
					    LOGD("pTypeInfo->GetId error");
                        pParamInfo->Release();
                        pTypeInfo->Release();
                        releaseCARMethodInfoInside(meth, i);
        		        return  i;
				    }

				    // regExtraData[actualArgs] = (u4)iid;
					regExtraData[actualArgs] = (u4)malloc(sizeof(InterfaceID));
					if ((void*)regExtraData[actualArgs] == NULL) {
					    LOGD("Memory allocation error");
                        pParamInfo->Release();
                        pTypeInfo->Release();
                        releaseCARMethodInfoInside(meth, i);
        		        return  i;
        		    }
        		    memcpy((void*)regExtraData[actualArgs], &iid, sizeof(InterfaceID));

					regTypes[actualArgs] |= kTypeInterface<<16;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
		        default:
		            LOGE(" not implemented");
		    }
		} else if (ioAttrib == ParamIOAttribute_CallerAllocOut) {

		    // return void in Java method
			//only one [out] parameter is allowed
		    if (meth->shorty[0] == 'V' || outParamNum != 0) {
                pParamInfo->Release();
                pTypeInfo->Release();
                releaseCARMethodInfoInside(meth, i);
		        return  i;
		    }

			outParamNum++;

			regTypes[actualArgs] = 2<<30;
			switch (dataType) {
		        case CarDataType_Char8:
		        case CarDataType_Char16:
		        case CarDataType_Byte:
		        case CarDataType_Int16:
		        case CarDataType_Int32:
		        case CarDataType_Float:
		        case CarDataType_ECode:
				case CarDataType_Boolean:
				case CarDataType_Int64:
				case CarDataType_Double:
					regTypes[actualArgs] |= 1<<29;
					//regTypes[actualArgs+1] |= 1<<29;
					//actualArgs += 2;
                    actualArgs++;
					break;
		        case CarDataType_String:
					regTypes[actualArgs] |= kTypeString<<16;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
				case CarDataType_StringBuf:
					regTypes[actualArgs] |= kTypeStringBuffer<<16;
					pParamInfo->GetAdvisedCapacity(&size);
                    if (FAILED(ec) || size == 0)
                        size = DEFAULT_ARRAY_SIZE;
                    else
                        size++;
					meth->outsSize = size;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
				case CarDataType_ArrayOf:
					regTypes[actualArgs] |= kTypeArrayOf<<16;
					((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
					pElementTypeInfo->GetDataType(&dataType);
					pElementTypeInfo->Release();
					switch(dataType){
						case CarDataType_Boolean:
							regTypes[actualArgs] |= kTypeBoolean<<8;
							break;
						case CarDataType_Byte:
							regTypes[actualArgs] |= kTypeByte<<8;
							break;
						case CarDataType_Char8:
		        		case CarDataType_Char16:
	   						regTypes[actualArgs] |= kTypeChar<<8;
							break;
		        		case CarDataType_Int16:
							regTypes[actualArgs] |= kTypeShort<<8;
							break;
		        		case CarDataType_Int32:
							regTypes[actualArgs] |= kTypeInt<<8;
							break;
						case CarDataType_Int64:
							regTypes[actualArgs] |= kTypeLong<<8;
							break;
						case CarDataType_Float:
							regTypes[actualArgs] |= kTypeFloat<<8;
							break;
						case CarDataType_Double:
							regTypes[actualArgs] |= kTypeDouble<<8;
							break;
						default:
							LOGD("Not Implement data type");
                            pParamInfo->Release();
                            pTypeInfo->Release();
                            releaseCARMethodInfoInside(meth, i);
            		        return  i;
					}

					ec = pParamInfo->GetAdvisedCapacity(&size);
                    if (FAILED(ec) || size == 0)
                        size = DEFAULT_ARRAY_SIZE;
                    else
                        size++;
					meth->outsSize = size;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
				case CarDataType_BufferOf:
					regTypes[actualArgs] |= kTypeBufferOf<<16;
					((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
					pElementTypeInfo->GetDataType(&dataType);
					pElementTypeInfo->Release();
					switch(dataType){
						case CarDataType_Boolean:
							regTypes[actualArgs] |= kTypeBoolean<<8;
							break;
						case CarDataType_Byte:
							regTypes[actualArgs] |= kTypeByte<<8;
							break;
						case CarDataType_Char8:
		        		case CarDataType_Char16:
	   						regTypes[actualArgs] |= kTypeChar<<8;
							break;
		        		case CarDataType_Int16:
							regTypes[actualArgs] |= kTypeShort<<8;
							break;
		        		case CarDataType_Int32:
							regTypes[actualArgs] |= kTypeInt<<8;
							break;
						case CarDataType_Int64:
							regTypes[actualArgs] |= kTypeLong<<8;
							break;
						case CarDataType_Float:
							regTypes[actualArgs] |= kTypeFloat<<8;
							break;
						case CarDataType_Double:
							regTypes[actualArgs] |= kTypeDouble<<8;
							break;
						default:
							LOGD("Not Implement data type");
                            pParamInfo->Release();
                            pTypeInfo->Release();
                            releaseCARMethodInfoInside(meth, i);
            		        return  i;
					}
					ec = pParamInfo->GetAdvisedCapacity(&size);
                    if (FAILED(ec) || size == 0)
                        size = DEFAULT_ARRAY_SIZE;
                    else
                        size++;
					meth->outsSize = size;
					meth->pCARMethodInfo->needCopy = true;
					actualArgs++;
					break;
                case CarDataType_Enum:
	                  //check wether it is a enum class
    				clazz2 = dvmGetBoxedReturnType(meth);
    				methodEnum = dvmFindDirectMethodHierByDescriptor(clazz, "valueOf", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Enum;");
    			    methodEnum2 = dvmFindVirtualMethodHierByDescriptor(clazz, "name", "()Ljava/lang/String;");
    				if (methodEnum == NULL || methodEnum2 == NULL) {
    				    LOGD("enum parameter error");
                        pParamInfo->Release();
                        pTypeInfo->Release();
                        releaseCARMethodInfoInside(meth, i);
    				    return  i;
    				}

					regTypes[actualArgs] |= kTypeEnum<<16;
					meth->pCARMethodInfo->needCopy = true;
					pTypeInfo->GetName(&pName);
					regExtraData[actualArgs] = (u4)getEnumInfo(pName.GetPayload(), pClassInfo);
					actualArgs++;
					break;
				case CarDataType_Interface:
					regTypes[actualArgs] |= kTypeInterface<<16;
					meth->pCARMethodInfo->needCopy = true;

					pTypeInfo->GetName(&pName);
					regExtraData[actualArgs] = (u4)strdup((char*)pName);
					if ((void*)regExtraData[actualArgs] == NULL) {
					    LOGD("Memory allocation error");
                        pParamInfo->Release();
                        pTypeInfo->Release();
                        releaseCARMethodInfoInside(meth, i);
        		        return  i;
        		    }

                    k = checkClassForOutInterface(meth, dexProtoGetReturnType(&meth->prototype), (char*)pName);
                    if (k > 0) {
                        LOGD("[out] parameter error:Java:%s CAR:%s", dexProtoGetReturnType(&meth->prototype), (char*)pName);
                        pParamInfo->Release();
                        pTypeInfo->Release();
                        releaseCARMethodInfoInside(meth, i);
        		        return  (k<<16)|i;
        		    }

					actualArgs++;
					break;
		        default:
		            LOGD("not implemented");
                    pParamInfo->Release();
                    pTypeInfo->Release();
                    releaseCARMethodInfoInside(meth, i);
    		        return  i;
		    }
		}

        pParamInfo->Release();
        pTypeInfo->Release();
    } //end of for(every parameter)
//	if(actualArgs != meth->insSize+1) {
//		LOGD("failed, actual args size is %d, expected size is %d", actualArgs, meth->insSize+1);
//		return false;
//	}

    if ((paramCount - outParamNum) != k || ((meth->shorty[0] != 'V') && (outParamNum == 0))) {
        releaseCARMethodInfoInside(meth, paramCount);
        return  paramCount;
    }

	return -1;
}

char* dvmReflectClassName(void* pObject)
{
	LOGD("dvmReflectClassName");
	if(pObject == NULL)
		return NULL;

	IClassInfo *pClassInfo;
	StringBuf_<256>  pName;

	ECode ec = _CObject_ReflectClassInfo((PInterface)pObject, &pClassInfo);
	if (FAILED(ec)) {
		LOGD("_CObject_ReflectClassInfo FAILED");
		return NULL;
	}
	pClassInfo->GetName(&pName);
	//char* s = pName->GetPayload();
    char* s = strdup((char*)pName);
	ClassID id;
	pClassInfo->GetId(&id);
	return s;
}

bool dvmSetCARMemberHook(InstField* instField)
{
	LOGD("dvmSetCARMemberHook");
	ClassObject *clazz, *clz;
	ECode        ec;
	IClassInfo  *pClassInfo;
	IMethodInfo *pMethodInfo;
	char        *funcName;
	u2           ui2;
	char        *s;
	const char  *cons;
	Field       *field = &instField->field;
	int          i;
    char         buf[512];
    Method      *meth;

    //add 10 bytes to hold "Getter" or "Setter"
    funcName = (char *)alloca(10+strlen(field->name));

	clazz = field->clazz;
	if(clazz == NULL)
		return false;
	if (!IS_CLASS_FLAG_SET(clazz, CLASS_CAR_CLASS))
		return false;

	pClassInfo = (IClassInfo*)(clazz->pClassInfo);
	if (pClassInfo == NULL)
		return false;

    if (instField->interfaceIndexOfSetter == 0xFFFF || instField->interfaceIndexOfSetter == 0xFFFE) {

        /*
         * Delegate field
         * no CARMember annotation
         */

    	//IDelegateProxy *piDelegateProxy = NULL;
    	ICallbackMethodInfo *pCallbackInfo = NULL;

        /*
         * God take care of me, let:
         * strlen("Callback")==8 and strlen("Delegate")==8
         */
        cons = field->name;
        i = strlen(cons);
        if (i > 8) {
            //memory is big enough to hold "Callback", "Delegate"
            i -= 8;
            if (strcmp(cons+i, "Callback") == 0 || strcmp(cons+i, "Delegate") == 0 ) {
                strncpy(buf, cons, i);
                buf[i] = '\0';
                s = buf;
            }
        }

    	for (i = 0, clz = clazz;  clz != NULL;  clz = clz->super) {
            if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
    	        if (IsCallback(s, (IClassInfo*)clz->pClassInfo, &pCallbackInfo))
                    break;
                i++;
            }
        }

        //if it is a CAR callback event
        if (clz != NULL) {

            if (instField->interfaceIndexOfSetter == 0xFFFF ) {
                //check wheter the pCallbackInfo is a Delegate
            } else /*|| instField->interfaceIndexOfSetter == 0xFFFE)*/ {
                //check wheter the pCallbackInfo is a Callback
            }

    	    //instField->interfaceIndexOfSetter = 0xFFFF;
            instField->setter = (u4)pCallbackInfo;
    	    instField->interfaceIndexOfGetter = (u2)i;
            //instField->getter = (u4)pCallbackInfo;

            /*
             * these check is redundant
             * for this dvmSetCARMemberHook() is work in 'else' of dvmHasCARMemberAnnotation()
             * it has no CARMember information on this field Delegate defination
             */
#if 0
        	s = dvmGetCARMemberAnnotationValue(field, "Getter");
        	s1 = dvmGetCARMemberAnnotationValue(field, "Setter");
        	if (s != NULL && *s != '\0' && s1 != NULL && *s1 != '\0' ) {
        	    //program grammer error
        	    snprintf(buf, sizeof(buf)-1, "field defination syntax error:%s", field->name);
        	    dvmThrowException("Ljava/lang/IllegalArgumentException;", buf);
        		return false;
        	}
#endif
        } else {
#if 0
    //Delegate field can be a normal Java field
            //Delegate defination error
    	    snprintf(buf, sizeof(buf)-1, "Delegate defination error, no this callback:%s", field->name);
    	    dvmThrowException("Ljava/lang/IllegalArgumentException;", buf);
#endif
    		return false;
        }
        return  true;
    }

    /* ???
     * should the following pClassInfo consider Java class inheritting?
     * no, every CARMember should in current CAR class.
     */

	s = dvmGetCARMemberAnnotationValue(field, (char*)"Getter");
	if (s == NULL || *s == '\0') {
    	strcpy(funcName, "get");
    	strcat(funcName, field->name);

	    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, funcName, &ui2, &pMethodInfo);
    	if (FAILED(ec) || !checkCarSetterGetterOfField(pMethodInfo)) {
    	    ui2 = 0xFFF1;
    		pMethodInfo = NULL;
    	}
    } else {
	    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, s, &ui2, &pMethodInfo);

	    //continue search method in Java method table
    	if (FAILED(ec) || !checkCarSetterGetterOfField(pMethodInfo)) {
            meth = dvmFindVirtualMethodHierByDescriptor(clazz, s, NULL);
            if (meth == NULL) {
                // search private methods and constructors; non-hierarchical
                meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
            }

            if (meth != NULL && checkJavaSetterGetterOfField((Field*)instField, meth)) {
                pMethodInfo = (IMethodInfo*)meth;
                ui2 = 0xFFFD;
            } else {
                return  false;
            }
        }
    }

	instField->getter = (u4)pMethodInfo;
	instField->interfaceIndexOfGetter = ui2 - 1;

	s = dvmGetCARMemberAnnotationValue(field, (char*)"Setter");
	if (s == NULL || *s == '\0') {
    	strcpy(funcName, "set");
    	strcat(funcName, field->name);

	    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, funcName, &ui2, &pMethodInfo);
    	if (FAILED(ec) || !checkCarSetterGetterOfField(pMethodInfo)) {
    	    ui2 = 0xFFF1;
    		pMethodInfo = NULL;
    	}
	} else {
	    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, s, &ui2, &pMethodInfo);
    	if (FAILED(ec) || !checkCarSetterGetterOfField(pMethodInfo)) {
            meth = dvmFindVirtualMethodHierByDescriptor(clazz, s, NULL);
            if (meth == NULL) {
                // search private methods and constructors; non-hierarchical
                meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
            }

            if (meth != NULL && checkJavaSetterGetterOfField((Field*)instField, meth)) {
                pMethodInfo = (IMethodInfo*)meth;
                ui2 = 0xFFFD;
            } else {
                return  false;
            }
        }
	}

	instField->setter = (u4)pMethodInfo;
	instField->interfaceIndexOfSetter = ui2 - 1;

	return true;
}

bool dvmSetStaticCARMemberHook(StaticField* staticField)
{
	LOGD("dvmSetStaticCARMemberHook");
	ClassObject *clazz, *clz;
	ECode        ec;
	IClassInfo  *pClassInfo, *p;
	IMethodInfo *pMethodInfo;
	char        *funcName;
	u2           ui2;
	int          i;
	char        *s;
	char        *sClassDescriptor;
	Field       *field = &(staticField->field);
	bool         hasGetter = true;
	bool         hasSetter = true;
    Method      *meth;

    //add 10 bytes to hold "Getter" or "Setter"
    funcName = (char *)alloca(10+strlen(field->name));
    clazz = ((Field *)staticField)->clazz;

	/*
	if (!IS_CLASS_FLAG_SET(clazz, CLASS_CAR_CLASS))
		return false;
	*/
	staticField->pSetterGetterClassObject = NULL;
	pClassInfo = NULL;

	//class descriptor is like "Ljava/lang/InternalError;"
	sClassDescriptor = dvmGetCARMemberAnnotationValue(field, (char*)"ClassDescriptor");
    if (sClassDescriptor != NULL && *sClassDescriptor == '\0')
	   sClassDescriptor = NULL;

	s = dvmGetCARMemberAnnotationValue(field, (char*)"Getter");
	if (s == NULL || *s == '\0') {
	    hasGetter = false;
	    strcpy(funcName, "get");
	    strcat(funcName, field->name);
	    s = funcName;
	}

    if (sClassDescriptor != NULL) {

        //find the class in global cache hash table

        for (i = 0; i < gDvm.globalCARClass->tableSize; i++) {
            HashEntry* pEnt = &gDvm.globalCARClass->pEntries[i];

            clz = (ClassObject*)pEnt->data;
            if (clz != NULL && clz != HASH_TOMBSTONE) {

                if (strcmp(clz->descriptor, sClassDescriptor) != 0)
                    continue;

                p = (IClassInfo*)(clz->pStaticClassInfo);
                ec = GetMethodInfoAndInterfaceIndex(p, s, &ui2, &pMethodInfo);
                if (SUCCEEDED(ec) && checkCarSetterGetterOfField(pMethodInfo)) {
                    pClassInfo = p;
                    staticField->pSetterGetterClassObject = (u4)clz->pCARSingletonObject;
                    break;
                }
            }
        }

        //not in global, test whether it is a java method in the same java class
        if (i >= gDvm.globalCARClass->tableSize) {

            if (hasGetter) {
                meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
                    pMethodInfo = (IMethodInfo*)meth;
                    ui2 = 0xFFFD;
                } else {
                    //throw an exception
                    //user has defined Setter, but can't find the method in VM resource
                    return  false;
                }
            }
        }
    } else {
        p = (IClassInfo*)clazz->pStaticClassInfo;
        if (p != NULL) {
            ec = GetMethodInfoAndInterfaceIndex(p, funcName, &ui2, &pMethodInfo);
            if (SUCCEEDED(ec) && checkCarSetterGetterOfField(pMethodInfo)) {
                pClassInfo = p;
                staticField->pSetterGetterClassObject = clazz->pCARSingletonObject;
            } else {
                if (hasGetter) {
                    meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                    if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
                        pClassInfo = NULL;
                        pMethodInfo = (IMethodInfo*)meth;
                        ui2 = 0xFFFD;
                    } else {
                        //throw an exception
                        //user has defined Setter, but can't find the method in VM resource
                        return  false;
                    }
                }
            }
        } else {
            pClassInfo = NULL;
            if (hasGetter) {
                meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
                    pMethodInfo = (IMethodInfo*)meth;
                    ui2 = 0xFFFD;
                } else {
                    //throw an exception
                    //user has defined Setter, but can't find the method in VM resource
                    return  false;
                }
            }
        }
    }

	if (pClassInfo != NULL || ui2 == 0xFFFD) {
    	staticField->getter = (u4)pMethodInfo;
    	staticField->interfaceIndexOfGetter = ui2 - 1;
    }

	s = dvmGetCARMemberAnnotationValue(field, (char*)"Setter");
	if (s == NULL || *s == '\0') {
	    hasSetter = false;
	    strcpy(funcName, "set");
	    strcat(funcName, field->name);
	    s = funcName;
	}

    if (pClassInfo == NULL) {
        if (sClassDescriptor != NULL) {

            //find the class in global cache hash table

            for (i = 0; i < gDvm.globalCARClass->tableSize; i++) {
                HashEntry* pEnt = &gDvm.globalCARClass->pEntries[i];

                clz = (ClassObject*)pEnt->data;
                if (clz != NULL && clz != HASH_TOMBSTONE) {

                    if (strcmp(clz->descriptor, sClassDescriptor) != 0)
                        continue;

                    p = (IClassInfo*)(clz->pClassInfo);
    	            ec = GetMethodInfoAndInterfaceIndex(p, s, &ui2, &pMethodInfo);
    	            if (SUCCEEDED(ec) && checkCarSetterGetterOfField(pMethodInfo)) {
    	                staticField->pSetterGetterClassObject = (u4)clz->pCARSingletonObject;
                    	staticField->setter = (u4)pMethodInfo;
                    	staticField->interfaceIndexOfSetter = ui2 - 1;
    	                break;
    	            }
    	        }
            }

            //not in global, test whether it is a java method in the same java class
            if (i >= gDvm.globalCARClass->tableSize) {
                //throw an exception
                //user has defined Setter, but can't find the method in VM resource
                if (hasSetter) {
                    meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                    if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
    	                //staticField->pSetterGetterClassObject = (u4)0;
                    	staticField->setter = (u4)meth;
                    	staticField->interfaceIndexOfSetter = 0xFFFC;
                    } else {
                        //throw an exception
                        //user has defined Setter, but can't find the method in VM resource
                        return  false;
                    }
                } else {
                    return  false;
                }
            }
        } else {
            p = (IClassInfo*)clazz->pStaticClassInfo;
            if (p != NULL) {
                ec = GetMethodInfoAndInterfaceIndex(p, s, &ui2, &pMethodInfo);
                if (SUCCEEDED(ec) && checkCarSetterGetterOfField(pMethodInfo)) {
	                staticField->pSetterGetterClassObject = clazz->pCARSingletonObject;
                	staticField->setter = (u4)pMethodInfo;
                	staticField->interfaceIndexOfSetter = ui2 - 1;
                } else {
                    if (hasSetter) {
                        meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                        if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
        	                //staticField->pSetterGetterClassObject = (u4)0;
                        	staticField->setter = (u4)meth;
                        	staticField->interfaceIndexOfSetter = 0xFFFC;
                        } else {
                            return  false;
                        }
                    } else {
                        return  false;
                    }
                }
            } else {
                if (hasSetter) {
                    meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                    if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
    	                //staticField->pSetterGetterClassObject = (u4)0;
                    	staticField->setter = (u4)meth;
                    	staticField->interfaceIndexOfSetter = 0xFFFC;
                    } else {
                        return  false;
                    }
                } else {
                    return  false;
                }
            }
        }
    } else {
	    ec = GetMethodInfoAndInterfaceIndex(pClassInfo, s, &ui2, &pMethodInfo);
    	if (FAILED(ec) || !checkCarSetterGetterOfField(pMethodInfo)) {
            if (hasSetter) {
                meth = dvmFindDirectMethodByDescriptor(clazz, s, NULL);
                if (meth != NULL && checkJavaSetterGetterOfField((Field*)staticField, meth)) {
	                //staticField->pSetterGetterClassObject = (u4)0;
                	staticField->setter = (u4)meth;
                	staticField->interfaceIndexOfSetter = 0xFFFC;
                } else {
                	staticField->setter = NULL;
                	staticField->interfaceIndexOfSetter = -1;
                    return  false;
                }
            }
    	}
    }

    if (staticField->interfaceIndexOfSetter == 0xFFFC)
        staticField->pSetterGetterClassObject = (u4)1;      //a not NULL value

	return true;
}


static void *pAppletObj;
pthread_mutex_t appletMutex;
pthread_cond_t appletCond;

static void* MsgLoopThread(void *vptr_args)
//static Elastos::ECode MsgLoopThread(Elastos::PVoid args)
{
    Thread  *self;
	ECode    ec;

	LOGD("MsgLoopThread");
	JavaVMAttachArgs attachArgs;
	attachArgs.version = JNI_VERSION_1_2;
	attachArgs.name = "MsgLoopThread";
	attachArgs.group = (jobject)dvmGetSystemThreadGroup();

	dvmAttachCurrentThread(&attachArgs,true);
	self = dvmThreadSelf();
	dvmChangeStatus(self, THREAD_VMWAIT);

	/*
	ec = _Impl_TApplet_Create(&pAppletObj);
	ec = _Impl_TApplet_Prepare(pAppletObj);
	*/
    IInterface *pOrgCallbackContext;
    IInterface *m_pCallbackContext;

    _Impl_CallbackSink_InitCallbackContext(&m_pCallbackContext);
    pOrgCallbackContext = (PInterface)pthread_getspecific(TL_CALLBACK_SLOT);
    if (NULL != pOrgCallbackContext) {
        pOrgCallbackContext->Release();
    }
    pthread_setspecific(TL_CALLBACK_SLOT, m_pCallbackContext);

    pAppletObj = m_pCallbackContext;

    /*
     * all Dalvik&CAR callbacks are called from this thread.
     * so, we should set gDvm.pCallbackInvocation here
     */
	gDvm.pCallbackInvocation = (unsigned int)AcquireCallbackInvocation(self->jniEnv);
	if ((void*)gDvm.pCallbackInvocation == NULL)
	    LOGD("AcquireCallbackInvocation error!");

	//CApplet::Finish(AppletFinish_ASAP);
	pthread_mutex_lock(&appletMutex);
	pthread_cond_signal(&appletCond);
	pthread_mutex_unlock(&appletMutex);

	//ec = _Impl_TApplet_DoWork(pAppletObj, ec);
	ec = _Impl_CallbackSink_TryToHandleEvents(m_pCallbackContext);

	LOGD("MsgLoopThread DoWork!");
	dvmChangeStatus(self, THREAD_RUNNING);
	dvmDetachCurrentThread();
	return NULL;
}

bool dvmCreateMsgLoopThread(void **ppAppletObj)
{
	LOGD("dvmCreateMsgLoopThread");
    pthread_t  mThread;
    pthread_attr_t threadAttr;

    if (gDvm.zygote && (ppAppletObj != &(gDvm.pAppletObj))) {
		LOGD("MsgLoopThread couldn't be created in zygote mode program");
        return  false;
    }

	pthread_mutex_init(&appletMutex, NULL);
	pthread_cond_init(&appletCond, NULL);

	pthread_mutex_lock(&appletMutex);

    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

	if (pthread_create(&mThread, &threadAttr, MsgLoopThread, NULL) != 0)
	{
		LOGD("MsgLoopThread Create failed");
	    pthread_mutex_unlock(&appletMutex);
    	pthread_mutex_destroy(&appletMutex);
    	pthread_cond_destroy(&appletCond);
		return false;
	}

	pthread_cond_wait(&appletCond, &appletMutex);
	pthread_mutex_unlock(&appletMutex);

	if (ppAppletObj != NULL)
	    *ppAppletObj = pAppletObj;

    //main AppletThread
	if (ppAppletObj == &(gDvm.pAppletObj)) {
	    pthread_setspecific(TL_CALLBACK_SLOT, pAppletObj);
	}

	pthread_mutex_destroy(&appletMutex);
	pthread_cond_destroy(&appletCond);

	return true;
}


//shutdown not main thread's MsgLoopThread
void dvmShutdownMsgLoopThread(void *pAppletObj)
{
	LOGD("dvmDestroyMsgLoopThread");

	if (pAppletObj == NULL)
	    return;
    /*
    IApplet *pApplet = (IApplet*)pAppletObj;
    pApplet->Finish(AppletFinish_ASAP);
    */
    ECode ec;

    ec = _Impl_CallbackSink_RequestToFinish((IInterface *)pAppletObj, CallbackContextFinish_ASAP);

    ((IInterface *)pAppletObj)->Release();
}


//shutdown not main thread's MsgLoopThread
void dvmAttachMsgLoopThread(void *pAppletObj)
{
    if (!gDvm.shouldCARWorking)
        return;

	LOGD("dvmAttachMsgLoopThread");

	if (pAppletObj == NULL)
	    return;

	//ec = _Impl_TApplet_Prepare(pAppletObj);
	pthread_setspecific(TL_CALLBACK_SLOT, pAppletObj);
}


void dvmDetachMsgLoopThread()
{
    if (!gDvm.shouldCARWorking)
        return;

	LOGD("dvmDetachMsgLoopThread");

    //_Impl_CAppletContext_Uninitialize();
    pthread_setspecific(TL_CALLBACK_SLOT, NULL);
}


static bool IsCallback(char *name, IClassInfo *pClassInfo, ICallbackMethodInfo **callbackInfo)
{
    if (name == NULL) {
        *callbackInfo = NULL;
        return false;
    }

    ICallbackMethodInfo *callbackMethodInfo;
    ECode ec = pClassInfo->GetCallbackMethodInfo(name, &callbackMethodInfo);
    if (FAILED(ec)) {
        *callbackInfo = NULL;
        return false;
    }

    *callbackInfo = callbackMethodInfo;
    return true;
}

static ICallbackInvocation* AcquireCallbackInvocation(JNIEnv* env)
{
	CJavaCallbackInvocation *pJavaCallbackInvocation;
	ICallbackInvocation *pICallbackInvocation;
	ECode ec = CJavaCallbackInvocation::NewByFriend((PVoid)env, (PVoid)(dvmThreadSelf()), &pJavaCallbackInvocation);
	if(FAILED(ec)){
		return NULL;
	}

	pICallbackInvocation = ICallbackInvocation::Probe((ICallbackInvocation*)pJavaCallbackInvocation);
	pJavaCallbackInvocation->AddRef();
	return pICallbackInvocation;
}

//bool dvmCreateCallbackInvocation()
//{
//}

bool dvmAddCallbackHandler(Object* CARObject, char* callbackMethodName, ClassObject* clazz, Method* method)
{
    ClassObject  *clz;
    int           i;

	LOGD("dvmAddCallbackHandler");

	ICallbackInvocation *pCallbackInvocation;

	/*
	 * I attempt to cache the pCallbackInvocation, but it is dvmThreadSelf depended, and the dvmCallMethodA()
	 * (.\vm\CarSupport\JavaCallbackInvocation\CJavaCallbackInvocation.cpp) will use the thread handle
	 *
	 * pCallbackInvocation = (IClassInfo*)CARObject->clazz->pCallbackInvocation;
	 *
	 * the clazz is global in Dalvik.
	 *
	 * so, I give up this idea.
	 *
	 * !!!Is this thinking right?
	 * NO! for the thread that dvmCallMethodA() depends on is the MsgLoopThread.
	 */
	pCallbackInvocation = (ICallbackInvocation *)gDvm.pCallbackInvocation;
	//this should not happen
	if (pCallbackInvocation == NULL)
	    pCallbackInvocation = AcquireCallbackInvocation(dvmThreadSelf()->jniEnv);

	IDelegateProxy *piDelegateProxy = NULL;
	ICallbackMethodInfo *pCallbackInfo = NULL;

	for (i = 0, clz = CARObject->clazz;  clz != method->clazz && clz != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
	        if (IsCallback(callbackMethodName, (IClassInfo*)clz->pClassInfo, &pCallbackInfo))
                break;
            i++;
        }
    }
    if (clz == NULL)
        return  false;
	/*
	if(!IsCallback(callbackMethodName,  (IClassInfo*)CARObject->clazz->pClassInfo, &pCallbackInfo) || (pCallbackInfo == NULL))
	{
		return false;
	}*/

	ECode ec = pCallbackInfo->CreateDelegateProxy((void*)clazz, (void*)method, pCallbackInvocation, &piDelegateProxy);
	if (FAILED(ec)) {
        pCallbackInfo->Release();
        return false;
    }
	EventHandler handler;
	piDelegateProxy->GetDelegate(&handler);
	pCallbackInfo->AddCallback((IInterface*)(*(u4*)(((char*)CARObject)+CARObject->clazz->objectSize+sizeof(u4)*i)), handler);
LOGD("AddCallback");
//	dvmThreadSelf();
//	JValue rt;
//	dvmCallMethod(dvmThreadSelf(), method, NULL, &rt);
	return true;
}


/**
  * object: which CAR object has this callback method
  * idxCARClass, idx of CAR object in Java Object
  * thisJavaObj: which Java Object will run for method
  * u4CallbackInfo: pICallbackInfo, CAR callback method information
  * method: Java method
  */
bool dvmAddEventCallbackHandler(Object *object, u2 idxCARClass, u4 thisJavaObj, u4 u4CallbackInfo, Method *method)
{
	IDelegateProxy      *piDelegateProxy = NULL;
	ICallbackInvocation *pCallbackInvocation;
	ICallbackMethodInfo *pCallbackInfo = (ICallbackMethodInfo*)u4CallbackInfo;
	//ClassObject         *clz;
	ECode                ec;

	LOGD("dvmAddEventCallbackHandler");
	if (!checkCompatibilityOfIFunctionInfoAndMethod((IFunctionInfo*)pCallbackInfo, method)) {
	    return  false;
	}

	pCallbackInvocation = (ICallbackInvocation *)gDvm.pCallbackInvocation;
	//this should not happen
	if (pCallbackInvocation == NULL)
	    pCallbackInvocation = AcquireCallbackInvocation(dvmThreadSelf()->jniEnv);

    if (thisJavaObj != 0)
	    ec = pCallbackInfo->CreateDelegateProxy((void*)thisJavaObj, (void*)method, pCallbackInvocation, &piDelegateProxy);
	else
	    ec = pCallbackInfo->CreateDelegateProxy((void*)object, (void*)method, pCallbackInvocation, &piDelegateProxy);

	if (FAILED(ec)) {
        pCallbackInfo->Release();
        return false;
    }

    EventHandler handler;
	piDelegateProxy->GetDelegate(&handler);
	pCallbackInfo->AddCallback((IInterface*)(*(u4*)(((char*)object)+object->clazz->objectSize+sizeof(u4)*idxCARClass)), handler);
    LOGD("AddEventCallback");
	return true;
}


/**
  * object: which CAR object has this callback method
  * idxCARClass, idx of CAR object in Java Object
  * thisJavaObj: which Java Object will run for method
  * u4CallbackInfo: pICallbackInfo, CAR callback method information
  * method: Java method
  */
bool dvmRemoveEventCallbackHandler(Object *object, u2 idxCARClass, u4 thisJavaObj, u4 u4CallbackInfo, Method *method)
{
	IDelegateProxy      *piDelegateProxy = NULL;
	ICallbackInvocation *pCallbackInvocation;
	ICallbackMethodInfo *pCallbackInfo = (ICallbackMethodInfo*)u4CallbackInfo;
	//ClassObject         *clz;
	ECode                ec;

	LOGD("dvmRemoveEventCallbackHandler");

	pCallbackInvocation = (ICallbackInvocation *)gDvm.pCallbackInvocation;
	//this should not happen
	if (pCallbackInvocation == NULL)
	    pCallbackInvocation = AcquireCallbackInvocation(dvmThreadSelf()->jniEnv);

	ec = pCallbackInfo->CreateDelegateProxy((void*)thisJavaObj, (void*)method, pCallbackInvocation, &piDelegateProxy);
	if (FAILED(ec)) {
        pCallbackInfo->Release();
        return false;
    }

    EventHandler handler;
	piDelegateProxy->GetDelegate(&handler);
	pCallbackInfo->RemoveCallback((IInterface*)(*(u4*)(((char*)object)+object->clazz->objectSize+sizeof(u4)*idxCARClass)), handler);
	piDelegateProxy->Release();
    LOGD("RemoveEventCallback");
	return true;
}


bool dvmRemoveCallbackHandler(Object* CARObject, u4 *u4CallbackInfo, u4 handler)
{
	EventHandler  *h = (EventHandler*)handler;

	ICallbackMethodInfo *pCallbackInfo = (ICallbackMethodInfo*)u4CallbackInfo;

    pCallbackInfo->RemoveCallback((IInterface*)CARObject, *h);
    free((void*)handler);

	return true;
}


bool dvmRemoveAllCallbackHandler(Object* CARObject)
{
    ClassObject  *clz;
    int           i;
    IClassInfo   *CARclsInfo;

	for (i = 0, clz = CARObject->clazz;  clz != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
            CARclsInfo = (IClassInfo*)clz->pClassInfo;
            CARclsInfo->RemoveAllCallbackHandlers((IInterface*)(*(u4*)(((char*)CARObject)+CARObject->clazz->objectSize+sizeof(u4)*i)));
            i++;
        }
    }

	return true;
}

//int dvmGetCAREnumInt(Object *CARObject, char *CAREnumName, char *CAREnumItemName)
//{
//    IModuleInfo *pIModuleInfo;
//    ECode        ec;
//    IEnumInfo   *pEnumInfo;
//    IEnumItemInfo *pEnumItemInfo;
//	Int32        value = -1;
//
//    if ((CARObject == NULL) || (CARObject->clazz->pClassInfo == NULL))
//        return  -1;
//
//    //this will make the CAR reflection reload the module
//    ec = ((IClassInfo*)(CARObject->clazz->pClassInfo))->GetModuleInfo(&pIModuleInfo);
//    if (FAILED(ec))
//        return  -1;
//
//    ec = pIModuleInfo->GetEnumInfo(CAREnumName, &pEnumInfo);
//    if (FAILED(ec))
//        return  -1;

//    ec = pEnumInfo->GetItemInfo(CAREnumItemName, &pEnumItemInfo);
//    if (FAILED(ec))
//        return  -1;
//
//    ec = pEnumItemInfo->GetValue(&value);
//    pEnumInfo->Release();
//    pEnumItemInfo->Release();
//    pIModuleInfo->Release();
//
//    return  value;
//}
char* dvmGetCAREnumString(void* ptr, int value)
{
	IEnumInfo   *pEnumInfo;
	BufferOf<IEnumItemInfo*>* pItemInfosBufferOf;
	int count;

	if(ptr == NULL){
		LOGE("the ptr for enum is NULL");
		return  NULL;
	}
	pEnumInfo = (IEnumInfo*)ptr;

	pEnumInfo->GetItemCount(&count);
    if (count <= 0)
		return NULL;

	pItemInfosBufferOf = BufferOf<IEnumItemInfo*>::Alloc(count);
	pEnumInfo->GetAllItemInfos(pItemInfosBufferOf);
	IEnumItemInfo** pItemInfos = pItemInfosBufferOf->GetPayload();

	Int32 enumValue = -1;
    StringBuf_<256>  pName;

	for(int i = 0; i < count; i++){
		pItemInfos[i]->GetValue(&enumValue);
		if (enumValue == value){
		 	pItemInfos[i]->GetName(&pName);
			BufferOf<IEnumItemInfo*>::Free(pItemInfosBufferOf);
			return  strdup((char*)pName);
		}
	}
	BufferOf<IEnumItemInfo*>::Free(pItemInfosBufferOf);
	return NULL;
}

int dvmGetCAREnumInt(void* ptr, char* CAREnumItemName)
{
	IEnumInfo   *pEnumInfo;
	IEnumItemInfo *pEnumItemInfo;
	Int32        value = -1;
	if(ptr == NULL){
		LOGE("the ptr for enum is NULL");
		return  -1;
	}
	pEnumInfo = (IEnumInfo*)ptr;
    ECode ec = pEnumInfo->GetItemInfo(CAREnumItemName, &pEnumItemInfo);
    if (FAILED(ec)){
		LOGE("failed in GetItemInfo");
		return  -1;
	}

    ec = pEnumItemInfo->GetValue(&value);
	if(FAILED(ec)){
		LOGE("failed in GetValue");
		return -1;
	}

    pEnumInfo->Release();
    pEnumItemInfo->Release();
	return value;
}

int dvmGetCARConstInt(Object *CARObject, char *CARConstName)
{
    IModuleInfo   *pIModuleInfo;
    ECode          ec;
    IConstantInfo *pConstInfo;
	Int32          value = -1;

    if ((CARObject == NULL) || ((void*)CARObject->clazz->pClassInfo == NULL))
        return  -1;

    //this will make the CAR reflection reload the module
    ec = ((IClassInfo*)CARObject->clazz->pClassInfo)->GetModuleInfo(&pIModuleInfo);
    if (FAILED(ec))
        return  -1;

    ec = pIModuleInfo->GetConstantInfo(CARConstName, &pConstInfo);
    if (FAILED(ec))
        return  -1;

    ec = pConstInfo->GetValue(&value);
    pConstInfo->Release();
    pIModuleInfo->Release();

    return  value;
}


void dvmReleaseCARMethodInfo(Method* meth)
{
	LOGD("dvmReleaseCARMethodInfo");

	if ((void*)meth->pCARMethodInfo != NULL && (void*)meth->pCARMethodInfo->pMethodInfo != NULL) {
    	IInterfaceInfo  *pInterfaceInfo = NULL;
    	//ECode            ec = -1;
        Int32            paramCount;
        Int32            i;
        IParamInfo      *pParamInfo = NULL;
        IDataTypeInfo   *pTypeInfo = NULL;
        //IDataTypeInfo   *pElementTypeInfo = NULL;
        CarDataType      dataType;
    	ParamIOAttribute ioAttrib;
    	int              actualArgs = 1;

	    IMethodInfo* pMethodInfo = (IMethodInfo*)meth->pCARMethodInfo->pMethodInfo;
    	//u4* regTypes = meth->pCARMethodInfo->regTypes;
    	u4* regExtraData = meth->pCARMethodInfo->regExtraData;

        pMethodInfo->GetParamCount(&paramCount);

        for (i = 0; i < paramCount; i++) {
            pMethodInfo->GetParamInfoByIndex(i, &pParamInfo);
    		pParamInfo->GetIOAttribute(&ioAttrib);
            pParamInfo->GetTypeInfo(&pTypeInfo);
            pTypeInfo->GetDataType(&dataType);

    		if (ioAttrib == ParamIOAttribute_In) {
    		    switch (dataType) {
                    case CarDataType_Enum:
                        pInterfaceInfo = (IInterfaceInfo *)regExtraData[actualArgs];
                        ((IInterface *)pInterfaceInfo)->Release();
                        break;
    				case CarDataType_Interface:
    				    //free InterfaceID
    				    free((void*)regExtraData[actualArgs]);
    				    break;
    		    }
    		} else if (ioAttrib == ParamIOAttribute_CallerAllocOut) {
    			switch (dataType) {
                    case CarDataType_Enum:
                        pInterfaceInfo = (IInterfaceInfo *)regExtraData[actualArgs];
                        ((IInterface *)pInterfaceInfo)->Release();
                        break;
    				case CarDataType_Interface:
    				    //free Interface name
    				    free((void*)regExtraData[actualArgs]);
    				    break;

    			}
    		}
    		actualArgs++;
    	}
	    pMethodInfo->Release();
	}
}


void *dvmGetCARMethodAddr(Method* meth, u4 *pCARObject)
{
	VObject     *vobj = (VObject*)(pCARObject);
	CMethodInfo *pMethodInfo;
	UInt32       index;

	pMethodInfo = (CMethodInfo*)meth->pCARMethodInfo->pMethodInfo;
	index = pMethodInfo->m_uIndex;

	//vobj += INTERFACE_INDEX(index);
	//LOGD("dvmGetCARMethodAddr %d", meth->pCARMethodInfo->interfaceIndex);
	vobj += meth->pCARMethodInfo->interfaceIndex;
	return vobj->vtab->methods[METHOD_INDEX(index)];
}

void *dvmElapiNewStringBuf(int length)
{
	StringBuf* strbuf;
	strbuf = StringBuf::Alloc(length);
	return strbuf;
}

void  dvmElapiFreeStringBuf(void *strBuf)
{
	StringBuf::Free((StringBuf*)strBuf);
}

char *dvmElapiStringBufGetPayload(void* sb)
{
	return ((StringBuf*)sb)->GetPayload();
}

void *dvmElapiStringBufAppend(void *strBuf, char *str)
{
	return  ((StringBuf*)strBuf)->Append(String(str));
}

const char *dvmElapiNewString(const char* pch)
{
    //in fact, in CAR, String is the same of 'char *'
	String str(pch);
	return str;
}

/*
 * dvmElapiArrayNewBoolean
 * dvmElapiArrayNewByte
 * dvmElapiArrayNewChar
 * dvmElapiArrayNewShort
 * dvmElapiArrayNewInt
 * dvmElapiArrayNewLong
 * dvmElapiArrayNewFloat
 * dvmElapiArrayNewDouble
 */
#define PRIMITIVE_CAR_ARRAY_NEW(_rtype, _cartype, _name)					\
void* dvmElapiArrayNew##_name(_rtype* payLoad, int size)			        \
{																            \
	ArrayOf<_cartype> *pArray;										        \
	if(payLoad != NULL){										            \
		pArray = ArrayOf<_cartype>::Alloc(payLoad, size);			        \
	} else {													            \
		pArray = ArrayOf<_cartype>::Alloc(size);					        \
	}															            \
	return pArray;												            \
}

/*
 * dvmElapiArrayCloneBoolean
 * dvmElapiArrayCloneByte
 * dvmElapiArrayCloneChar
 * dvmElapiArrayCloneShort
 * dvmElapiArrayCloneInt
 * dvmElapiArrayCloneLong
 * dvmElapiArrayCloneFloat
 * dvmElapiArrayCloneDouble
 */
#define PRIMITIVE_CAR_ARRAY_CLONE(_rtype, _cartype, _name)					\
void* dvmElapiArrayClone##_name(_rtype* payLoad, int size)			        \
{																            \
	ArrayOf<_cartype> *pArray;										        \
	pArray = ArrayOf<_cartype>::Alloc(size);					            \
	if (pArray != NULL)                                                     \
	    pArray->Copy(payLoad, size);                                        \
	return pArray;												            \
}

/*
 * dvmElapiArrayGetPayloadBoolean
 * dvmElapiArrayGetPayloadByte
 * dvmElapiArrayGetPayloadChar
 * dvmElapiArrayGetPayloadShort
 * dvmElapiArrayGetPayloadInt
 * dvmElapiArrayGetPayloadLong
 * dvmElapiArrayGetPayloadFloat
 * dvmElapiArrayGetPayloadDouble
 */
#define PRIMITIVE_CAR_ARRAY_GETPAYLOAD(_rtype, _cartype, _name)		        \
_rtype* dvmElapiArrayGetPayload##_name(void* array)      	                \
{                                                              	            \
	ArrayOf<_cartype>* pArray;        								        \
	pArray = (ArrayOf<_cartype>*)array;							            \
	return pArray->GetPayload();								            \
}

/*
 * dvmElapiArrayGetLengthBoolean
 * dvmElapiArrayGetLengthByte
 * dvmElapiArrayGetLengthChar
 * dvmElapiArrayGetLengthShort
 * dvmElapiArrayGetLengthInt
 * dvmElapiArrayGetLengthLong
 * dvmElapiArrayGetLengthFloat
 * dvmElapiArrayGetLengthDouble
 */
#define PRIMITIVE_CAR_ARRAY_GETLENGTH(_rtype, _cartype, _name)			    \
int dvmElapiArrayGetLength##_name(void* array)					            \
{																            \
	ArrayOf<_cartype>* pArray;										        \
	pArray = (ArrayOf<_cartype>*)array;							            \
	return pArray->GetLength();									            \
}

/*
 * dvmElapiArrayFreeBoolean
 * dvmElapiArrayFreeByte
 * dvmElapiArrayFreeChar
 * dvmElapiArrayFreeShort
 * dvmElapiArrayFreeInt
 * dvmElapiArrayFreeLong
 * dvmElapiArrayFreeFloat
 * dvmElapiArrayFreeDouble
 */
#define PRIMITIVE_CAR_ARRAY_FREE(_rtype, _cartype, _name)					\
void dvmElapiArrayFree##_name(void* array)			                        \
{																            \
	ArrayOf<_cartype>* pArray;										        \
	pArray = (ArrayOf<_cartype>*)array;					                    \
	return ArrayOf<_cartype>::Free(pArray);									\
}

#define PRIMITIVE_CAR_ARRAY_FUNCTIONS(_rtype, _cartype, _name)            	\
	PRIMITIVE_CAR_ARRAY_NEW(_rtype, _cartype, _name)					   	\
	PRIMITIVE_CAR_ARRAY_GETPAYLOAD(_rtype, _cartype, _name)			   		\
	PRIMITIVE_CAR_ARRAY_GETLENGTH(_rtype, _cartype, _name)				   	\
	PRIMITIVE_CAR_ARRAY_FREE(_rtype, _cartype, _name)                       \
    PRIMITIVE_CAR_ARRAY_CLONE(_rtype, _cartype, _name)

PRIMITIVE_CAR_ARRAY_FUNCTIONS(unsigned char, Boolean, Boolean);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(unsigned char, Byte, Byte);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(char, Char8, Char);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(short, Int16, Short);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(int, Int32, Int);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(long long, Int64, Long);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(float, Float, Float);
PRIMITIVE_CAR_ARRAY_FUNCTIONS(double, Double, Double);


/*
 * dvmElapiBufferNewBoolean
 * dvmElapiBufferNewByte
 * dvmElapiBufferNewChar
 * dvmElapiBufferNewShort
 * dvmElapiBufferNewInt
 * dvmElapiBufferNewLong
 * dvmElapiBufferNewFloat
 * dvmElapiBufferNewDouble
 */
#define PRIMITIVE_CAR_BUFFER_NEW(_rtype, _cartype, _name)					\
void* dvmElapiBufferNew##_name(_rtype* payLoad, int size)			        \
{																            \
	BufferOf<_cartype> *pArray;										        \
	if(payLoad != NULL){										            \
		pArray = BufferOf<_cartype>::Alloc(payLoad, size);			        \
	} else {													            \
		pArray = BufferOf<_cartype>::Alloc(size);					        \
	}															            \
	return pArray;												            \
}


/*
 * dvmElapiBufferCloneBoolean
 * dvmElapiBufferCloneByte
 * dvmElapiBufferCloneChar
 * dvmElapiBufferCloneShort
 * dvmElapiBufferCloneInt
 * dvmElapiBufferCloneLong
 * dvmElapiBufferCloneFloat
 * dvmElapiBufferCloneDouble
 */
#define PRIMITIVE_CAR_BUFFER_CLONE(_rtype, _cartype, _name)					\
void* dvmElapiBufferClone##_name(_rtype* payLoad, int size)			        \
{																            \
    BufferOf<_cartype> *pArray;										        \
	pArray = BufferOf<_cartype>::Alloc(size);					            \
	if (pArray != NULL)                                                     \
	    pArray->Copy(payLoad, size);                                        \
	return pArray;												            \
}


/*
 * dvmElapiBufferGetPayloadBoolean
 * dvmElapiBufferGetPayloadByte
 * dvmElapiBufferGetPayloadChar
 * dvmElapiBufferGetPayloadShort
 * dvmElapiBufferGetPayloadInt
 * dvmElapiBufferGetPayloadLong
 * dvmElapiBufferGetPayloadFloat
 * dvmElapiBufferGetPayloadDouble
 */
#define PRIMITIVE_CAR_BUFFER_GETPAYLOAD(_rtype, _cartype, _name)		    \
_rtype* dvmElapiBufferGetPayload##_name(void* array)      	                \
{                                                              	            \
	BufferOf<_cartype>* pArray;        								        \
	pArray = (BufferOf<_cartype>*)array;							        \
	return pArray->GetPayload();								            \
}

/*
 * dvmElapiBufferGetLengthBoolean
 * dvmElapiBufferGetLengthByte
 * dvmElapiBufferGetLengthChar
 * dvmElapiBufferGetLengthShort
 * dvmElapiBufferGetLengthInt
 * dvmElapiBufferGetLengthLong
 * dvmElapiBufferGetLengthFloat
 * dvmElapiBufferGetLengthDouble
 */
#define PRIMITIVE_CAR_BUFFER_GETLENGTH(_rtype, _cartype, _name)				\
int dvmElapiBufferGetLength##_name(void* array)					            \
{																            \
	BufferOf<_cartype>* pArray;										        \
	pArray = (BufferOf<_cartype>*)array;							        \
	return pArray->GetCapacity();									        \
}

/*
 * dvmElapiBufferFreeBoolean
 * dvmElapiBufferFreeByte
 * dvmElapiBufferFreeChar
 * dvmElapiBufferFreeShort
 * dvmElapiBufferFreeInt
 * dvmElapiBufferFreeLong
 * dvmElapiBufferFreeFloat
 * dvmElapiBufferFreeDouble
 */
#define PRIMITIVE_CAR_BUFFER_FREE(_rtype, _cartype, _name)				   \
void dvmElapiBufferFree##_name(void* array)								   \
{																           \
	BufferOf<_cartype>* pArray;										       \
	pArray = (BufferOf<_cartype>*)array;							       \
	return BufferOf<_cartype>::Free(pArray);							   \
}

#define PRIMITIVE_CAR_BUFFER_FUNCTIONS(_rtype, _cartype, _name)            \
	PRIMITIVE_CAR_BUFFER_NEW(_rtype, _cartype, _name)					   \
	PRIMITIVE_CAR_BUFFER_CLONE(_rtype, _cartype, _name)					   \
	PRIMITIVE_CAR_BUFFER_GETPAYLOAD(_rtype, _cartype, _name)			   \
	PRIMITIVE_CAR_BUFFER_GETLENGTH(_rtype, _cartype, _name)				   \
	PRIMITIVE_CAR_BUFFER_FREE(_rtype, _cartype, _name)

PRIMITIVE_CAR_BUFFER_FUNCTIONS(unsigned char, Boolean, Boolean);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(unsigned char, Byte, Byte);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(char, Char8, Char);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(short, Int16, Short);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(int, Int32, Int);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(long long, Int64, Long);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(float, Float, Float);
PRIMITIVE_CAR_BUFFER_FUNCTIONS(double, Double, Double);


bool setCARObjectinJavaObject(Object* JavaObject, Method* method, void *CARObject)
{
    //when consider the inherit of class, this function will complex
	LOGD("setCARObjectinJavaObject");

//	int  i;
//	for (i = 0, clz = JavaObject->clazz;  clz != NULL;  clz = clz->super) {
//	    if (method->clazz == clz)
//	        break;
//	}
//	if (method->clazz != clz)
//	    LOGD("class set error");

//    (IInterface*)(*(u4 *)((char *)JavaObject+JavaObject->clazz->objectSize + sizeof(u4)*i)) = CARObject;
	return true;
}


void* ProbeInterface(u4 obj, u4 iid)
{
    return  ((IInterface*)obj)->Probe(*(Elastos::_EMuid *)iid);
}


int ProbeIfxByName(ClassObject *clazz, const char *clzName, char *ifxName, bool isStatic)
{
    IClassInfo                 *pClassInfo = (IClassInfo*)clazz->pClassInfo;
    ECode                       ec;
    int                         i;
    int                         interfaceCount;
    BufferOf<IInterfaceInfo*>  *interfaceInfos;
    StringBuf_<256>             pName;

    if (isStatic)
        pClassInfo = (IClassInfo*)clazz->pStaticClassInfo;
    else
        pClassInfo = (IClassInfo*)clazz->pClassInfo;

    if (clzName != NULL) {
        ec = pClassInfo->GetName(&pName);
        if (FAILED(ec))
            return  -1;
        if (strcmp((char*)pName, clzName) != 0)
            return  -2;
    }

    //ec = pClassInfo->GetMethodInfo(meth->name, &pMethodInfo);
    ec = pClassInfo->GetInterfaceCount(&interfaceCount);
    if (FAILED(ec))
        return  -1;

	interfaceInfos = BufferOf<IInterfaceInfo*>::Alloc(interfaceCount);

    ec = pClassInfo->GetAllInterfaceInfos(interfaceInfos);
    if (FAILED(ec))
        return  -1;

    IInterfaceInfo** pInterfaceInfos = interfaceInfos->GetPayload();
    IInterfaceInfo* iteration;

    //the first interface in IInterface
    for (i = 1;  i < interfaceCount;  i++) {
    	iteration = pInterfaceInfos[i];
        ec = iteration->GetName(&pName);
        if (FAILED(ec))
            break;

        if (strcmp((char*)pName, ifxName) == 0) {
            BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
            return  i;
        }
    }

    BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
    return  -1;
}


void* dvmGetCARMethodinfoFunctionAddr(u4 *pCARObject, u4* pMethodInfo, u2 interfaceIndex)
{
	VObject *vobj;
	UInt32   index;

    if (pCARObject == NULL || pMethodInfo == NULL)
        return  NULL;

    vobj = (VObject*)(pCARObject);

	index = ((CMethodInfo *)pMethodInfo)->m_uIndex;
	//vobj += INTERFACE_INDEX(index);
	vobj += interfaceIndex;
	return vobj->vtab->methods[METHOD_INDEX(index)];
}


static ECode GetMethodInfoAndInterfaceIndex(IClassInfo *pClassInfo, char *methodName, u2 *interfaceIndex, IMethodInfo **pMethodInfo)
{
    ECode                       ec;
    int                         i;
    int                         interfaceCount;
    BufferOf<IInterfaceInfo*>  *interfaceInfos;

    //ec = pClassInfo->GetMethodInfo(meth->name, &pMethodInfo);
    ec = pClassInfo->GetInterfaceCount(&interfaceCount);
    if (FAILED(ec))
        return  -1;

	interfaceInfos = BufferOf<IInterfaceInfo*>::Alloc(interfaceCount);

    ec = pClassInfo->GetAllInterfaceInfos(interfaceInfos);
    if (FAILED(ec))
        return  -1;

    IInterfaceInfo** pInterfaceInfos = interfaceInfos->GetPayload();
    IInterfaceInfo* iteration;

    //the first interface in IInterface
    for (i = 1;  i < interfaceCount;  i++) {
    	iteration = pInterfaceInfos[i];
        ec = iteration->GetMethodInfo(methodName, pMethodInfo);
        if (SUCCEEDED(ec)) {
            *interfaceIndex = i;
            BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
            return  0;
        }
    }

    BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
    return  -1;
}

int dvmSetCARmethodInfoForJavaMethod(ClassObject *clazz)
{
    ECode                       ec;
    int                         i, j, k;
    int                         interfaceCount, methodCount;
    BufferOf<IInterfaceInfo*>  *interfaceInfos;
    BufferOf<IMethodInfo*>     *methodInfos;
    StringBuf_<256>             pName;
	CARMethodInfo              *p;
	IClassInfo                 *pClassInfo;

    if ((void*)clazz->pClassInfo != NULL)
    	pClassInfo = (IClassInfo *)(clazz->pClassInfo);
    else
    	pClassInfo = (IClassInfo *)(clazz->pStaticClassInfo);

    ec = pClassInfo->GetInterfaceCount(&interfaceCount);
    if (FAILED(ec))
        return  -1;

    if (interfaceCount <= 0)
        return  0;

	interfaceInfos = BufferOf<IInterfaceInfo*>::Alloc(interfaceCount);

    ec = pClassInfo->GetAllInterfaceInfos(interfaceInfos);
    if (FAILED(ec)) {
        BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
        return  -1;
    }

    IInterfaceInfo **pInterfaceInfos = interfaceInfos->GetPayload();
    IInterfaceInfo  *iteration;
    IMethodInfo    **pMethodInfos;
    IMethodInfo     *pMethodInfo;

    //the first interface in IInterface
    for (i = 1;  i < interfaceCount;  i++) {
    	iteration = pInterfaceInfos[i];
    	iteration->GetName(&pName);
    	if (strncmp((char*)pName, "Ijava", 5) == 0) {
    	    iteration->GetMethodCount(&methodCount);
			methodInfos = BufferOf<IMethodInfo*>::Alloc(methodCount);
            iteration->GetAllMethodInfos(methodInfos);
            pMethodInfos = methodInfos->GetPayload();
            for (j = 0;  j < methodCount;  j++) {
                pMethodInfo = pMethodInfos[j];
                pMethodInfo->GetName(&pName);

                for(k = 0;  k < clazz->directMethodCount;  k++) {

                    if (dvmIsNativeMethod(&(clazz->directMethods[k])))
                        continue;

                    if (strcmp((char*)pName, (clazz->directMethods[k]).name) == 0) {
                        //dvmLinearAlloc will abort the VM on failure, so it's not necessary to check for a NULL return value.
                    	p = (CARMethodInfo*)dvmLinearAlloc(clazz->classLoader, sizeof(CARMethodInfo));
                        p->pMethodInfo = (u4)pMethodInfo;
                    	p->regTypes = NULL;
                    	p->regExtraData = NULL;

                    	if (allParamArePrimitive(&(clazz->directMethods[k]))) {
                            p->needCopy = false;
                    	} else {
                            p->needCopy = true;
                    	}

                        (clazz->directMethods[k]).pCARMethodInfo = p;

                        //the java method name is unique, this is confirmed by javac
                        break;
                    }
                }

                //if doesn't suit to a directMethods
                if (k >= clazz->directMethodCount) {
                    for(k = 0;  k < clazz->virtualMethodCount;  k++) {

                        if (dvmIsNativeMethod(&(clazz->virtualMethods[k])))
                            continue;

                        if (strcmp((char*)pName, (clazz->virtualMethods[k]).name) == 0) {
                            //dvmLinearAlloc will abort the VM on failure, so it's not necessary to check for a NULL return value.
                        	p = (CARMethodInfo*)dvmLinearAlloc(clazz->classLoader, sizeof(CARMethodInfo));
                            p->pMethodInfo = (u4)pMethodInfo;
                        	p->regTypes = NULL;
                        	p->regExtraData = NULL;
                            (clazz->virtualMethods[k]).pCARMethodInfo = p;

                            //the java method name is unique, this is confirmed by javac, needn't to continue
                            break;
                        }
                    }

                    if (k >= clazz->virtualMethodCount) {
                        pMethodInfo->Release();
                    }
                }
            } //end of for j
			BufferOf<IMethodInfo*>::Free(methodInfos);
    	} //end of if Ijava
    }

    BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
    return  0;
}

/*
 * convert CAR complex datatype data into Java Object
 * these Java Object is stored in java Frame, has been called addLocalReference(), it is managed by Java heap mechanism
 */
Object *dvmCARObject2JavaObject(Thread *self, Object *object, const Method *method, u4 pCARObject, int idxParam)
{
    IParamInfo       *pParamInfo;
    IMethodInfo      *pMethodInfo;
    IDataTypeInfo    *pTypeInfo = NULL;
    IDataTypeInfo    *pElementTypeInfo = NULL;
    CarDataType       dataType;
	ParamIOAttribute  ioAttrib;
	Object           *obj = NULL;
	CARMethodInfo    *pCARMethodInfo = method->pCARMethodInfo;
	//ECode             ec;
	JNIEnv           *jniEnv = self->jniEnv;

    pMethodInfo = (IMethodInfo *)pCARMethodInfo->pMethodInfo;
    pMethodInfo->GetParamInfoByIndex(idxParam, &pParamInfo);
	pParamInfo->GetIOAttribute(&ioAttrib);
    pParamInfo->GetTypeInfo(&pTypeInfo);
    pTypeInfo->GetDataType(&dataType);

    switch (dataType) {
        case CarDataType_Char8:
        case CarDataType_Char16:
        case CarDataType_Byte:
        case CarDataType_Int16:
        case CarDataType_Int32:
        case CarDataType_Float:
        case CarDataType_ECode:
		case CarDataType_Boolean:
		case CarDataType_Int64:
		case CarDataType_Double:
            pTypeInfo->Release();
            pParamInfo->Release();
            return  (Object*)pCARObject;

		case CarDataType_String: {
			//jstring js = NewStringUTF(self->jniEnv, (char*)pCARObject);
			//jclass cls = jniEnv->FindClass("java/lang/String");
			jstring js = jniEnv->NewStringUTF((char*)pCARObject);
			Method *methodID = dvmFindDirectMethodByDescriptor(gDvm.classJavaLangString, "<init>", "(Ljava/lang/String;)V");
			obj = dvmClassNewInstance(gDvm.classJavaLangString, methodID, js);
			break;
		}
		case CarDataType_StringBuf: {
			//jclass cls = jniEnv->FindClass("java/lang/StringBuffer");
			//jmethodID methodID = jniEnv->GetMethodID(cls, "<init>", "(Ljava/lang/String;)V");
			jstring js = jniEnv->NewStringUTF(dvmElapiStringBufGetPayload((void*)pCARObject));
			//obj = (Object*)jniEnv->NewObject(cls, methodID, js);
			obj = dvmClassNewInstance(gDvm.classJavaLangStringBuffer, gDvm.methJavaLangStringBuffer, js);
			break;
		}
		case CarDataType_ArrayOf: {
			((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
			pElementTypeInfo->GetDataType(&dataType);
            pElementTypeInfo->Release();
			switch (dataType) {
				case CarDataType_Boolean:{
					jboolean* pBoolean = dvmElapiArrayGetPayloadBoolean((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthBoolean((void*)pCARObject);
					jbooleanArray arrayZ = jniEnv->NewBooleanArray(size);
					jniEnv->SetBooleanArrayRegion(arrayZ, 0, size, pBoolean);
					obj = (Object*)arrayZ;
					break;
				}
				case CarDataType_Byte: {
					jbyte* pByte = (jbyte*)dvmElapiArrayGetPayloadByte((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthByte((void*)pCARObject);
					jbyteArray arrayB = jniEnv->NewByteArray(size);
					jniEnv->SetByteArrayRegion(arrayB, 0, size, pByte);
					obj = (Object*)arrayB;
					break;
				}
				case CarDataType_Char8:
				case CarDataType_Char16: {
					jsize size = dvmElapiArrayGetLengthChar((void*)pCARObject);
					char* s = dvmElapiArrayGetPayloadChar((void*)pCARObject);
					int j;
					jchar* pChar = (jchar*)alloca(size*sizeof(char));
					for(j=0; j<size; j++){
						pChar[j] = s[j];
					}
					jcharArray arrayC = jniEnv->NewCharArray(size);
					jniEnv->SetCharArrayRegion(arrayC, 0, size, pChar);
					obj = (Object*)arrayC;
					break;
				}
				case CarDataType_Int16: {
					jshort* pShort = dvmElapiArrayGetPayloadShort((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthShort((void*)pCARObject);
					jshortArray arrayS = jniEnv->NewShortArray(size);
					jniEnv->SetShortArrayRegion(arrayS, 0, size, pShort);
					obj = (Object*)arrayS;
					break;
				}
				case CarDataType_Int32: {
					jint* pInt = dvmElapiArrayGetPayloadInt((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthInt((void*)pCARObject);
					jintArray arrayI = jniEnv->NewIntArray(size);
					jniEnv->SetIntArrayRegion(arrayI, 0, size, pInt);
					break;
				}
				case CarDataType_Int64: {
					jlong* pLong = dvmElapiArrayGetPayloadLong((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthLong((void*)pCARObject);
					jlongArray arrayJ = jniEnv->NewLongArray(size);
					jniEnv->SetLongArrayRegion(arrayJ, 0, size, pLong);
					obj = (Object*)arrayJ;
					break;
				}
				case CarDataType_Float:{
					jfloat* pFloat = dvmElapiArrayGetPayloadFloat((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthFloat((void*)pCARObject);
					jfloatArray arrayF = jniEnv->NewFloatArray(size);
					jniEnv->SetFloatArrayRegion(arrayF, 0, size, pFloat);
					obj = (Object*)arrayF;
					break;
				}
				case CarDataType_Double: {
					jdouble* pDouble = dvmElapiArrayGetPayloadDouble((void*)pCARObject);
					jsize size = dvmElapiArrayGetLengthDouble((void*)pCARObject);
					jdoubleArray arrayD = jniEnv->NewDoubleArray(size);
					jniEnv->SetDoubleArrayRegion(arrayD, 0, size, pDouble);
					obj = (Object *)arrayD;
					break;
				}
				default:
					LOGE("This type of ArrayOf not implement");
			}
			break;
		}
		case CarDataType_BufferOf: {
			((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
			pElementTypeInfo->GetDataType(&dataType);
            pElementTypeInfo->Release();
			switch (dataType) {
				case CarDataType_Boolean: {
					jboolean* pBoolean = dvmElapiBufferGetPayloadBoolean((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthBoolean((void*)pCARObject);
					jbooleanArray BufferZ = jniEnv->NewBooleanArray(size);
					jniEnv->SetBooleanArrayRegion(BufferZ, 0, size, pBoolean);
					obj = (Object*)BufferZ;
					break;
				}
				case CarDataType_Byte: {
					jbyte* pByte = (jbyte*)dvmElapiBufferGetPayloadByte((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthByte((void*)pCARObject);
					jbyteArray BufferB = jniEnv->NewByteArray(size);
					jniEnv->SetByteArrayRegion(BufferB, 0, size, pByte);
					obj = (Object*)BufferB;
					break;
				}
				case CarDataType_Char8:
				case CarDataType_Char16: {
					jsize size = dvmElapiBufferGetLengthChar((void*)pCARObject);
					char* s = dvmElapiBufferGetPayloadChar((void*)pCARObject);
					int j;
					jchar* pChar = (jchar*)alloca(size*sizeof(char));
					for(j=0; j<size; j++){
						pChar[j] = s[j];
					}
					jcharArray BufferC = jniEnv->NewCharArray(size);
					jniEnv->SetCharArrayRegion(BufferC, 0, size, pChar);
					obj = (Object*)BufferC;
					break;
				}
				case CarDataType_Int16: {
					jshort* pShort = dvmElapiBufferGetPayloadShort((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthShort((void*)pCARObject);
					jshortArray BufferS = jniEnv->NewShortArray(size);
					jniEnv->SetShortArrayRegion(BufferS, 0, size, pShort);
					obj = (Object*)BufferS;
					break;
				}
				case CarDataType_Int32:{
					jint* pInt = dvmElapiBufferGetPayloadInt((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthInt((void*)pCARObject);
					jintArray BufferI = jniEnv->NewIntArray(size);
					jniEnv->SetIntArrayRegion(BufferI, 0, size, pInt);
					obj = (Object*)BufferI;
					break;
				}
				case CarDataType_Int64: {
					jlong* pLong = dvmElapiBufferGetPayloadLong((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthLong((void*)pCARObject);
					jlongArray BufferJ = jniEnv->NewLongArray(size);
					jniEnv->SetLongArrayRegion(BufferJ, 0, size, pLong);
					obj = (Object*)BufferJ;
					break;
				}
				case CarDataType_Float: {
					jfloat* pFloat = dvmElapiBufferGetPayloadFloat((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthFloat((void*)pCARObject);
					jfloatArray BufferF = jniEnv->NewFloatArray(size);
					jniEnv->SetFloatArrayRegion(BufferF, 0, size, pFloat);
					obj = (Object*)BufferF;
					break;
				}
				case CarDataType_Double: {
					jdouble* pDouble = dvmElapiBufferGetPayloadDouble((void*)pCARObject);
					jsize size = dvmElapiBufferGetLengthDouble((void*)pCARObject);
					jdoubleArray BufferD = jniEnv->NewDoubleArray(size);
					jniEnv->SetDoubleArrayRegion(BufferD, 0, size, pDouble);
					obj = (Object*)BufferD;
					break;
				}
				default:
					LOGE("This type of BufferOf not implement");
			}
			break;
		}
		case CarDataType_Enum:
		{
			JValue           rt;
            StringBuf_<256>  pName;
            int              i;

            //get java method signature info
            DexParameterIterator iterator;

            dexParameterIteratorInit(&iterator, &(method->prototype));
            const char *protoDesc = dexParameterIteratorNextDescriptor(&iterator);
            for (i = 0;  (protoDesc != NULL) && (i < idxParam);  i++) {
                protoDesc = dexParameterIteratorNextDescriptor(&iterator);
            }

		    pTypeInfo->GetName(&pName);
            u4 CAREnumInfo = (u4)getEnumInfo((char*)pName, (IClassInfo*)(object->clazz->pClassInfo));

			char *s = dvmGetCAREnumString((void*)CAREnumInfo, (int)pCARObject);

			if (s != NULL) {
				ClassObject* clazz = dvmFindClass(protoDesc, method->clazz->classLoader);
				Method* methodEnum = dvmFindDirectMethodHierByDescriptor(clazz, "valueOf", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Enum;");
				dvmCallMethod(self, methodEnum, NULL, &rt, clazz, jniEnv->NewStringUTF(s));
				obj = (Object*)rt.l;
			    free(s);
			} else {
			}

			dvmReleaseCARClassObject(CAREnumInfo);

			break;
		}

	    case CarDataType_Interface:
	    {
	    	//LOGD("kTypeInterface%p %p",pCARObject, pCARObject->l);
	    	//char*s = dvmReflectClassName(pCARObject->l);
	    	//LOGD("s %s", s);
			const char        *desc = dexProtoGetReturnType(&method->prototype);
			char              *cp;
			ClassObject       *clazz;
			int                len;
			char              *wrapperFunc;
            StringBuf_<256>    pName;
			static const char *prefixCARInterfaceForWrapper = "Wrapper";

			LOGD("desc %s", desc);

			if (strcmp(desc, "Ljava/lang/Object;") == 0) {

				/* regExtraData[i] = CAR IInterface name
				 * return object is newed from class: packageName + "Wrapper" + CAR IInterface name
				 * packageName is same as method which provides this function
				 */

				desc = method->clazz->descriptor;
				len = strlen(desc);
				wrapperFunc = (char *)alloca((len+strlen(prefixCARInterfaceForWrapper)+1)*sizeof(char));

				for(cp = (char*)(desc+len); cp != desc; cp--) {
				    if (*cp == '/')
						break;
				}

				pTypeInfo->GetName(&pName);

				if (cp != desc) {
				    cp++;
				    strncpy(wrapperFunc, desc, cp-desc);
				    strcpy(wrapperFunc+(cp-desc), prefixCARInterfaceForWrapper);
				    strcat(wrapperFunc, (char *)pName);
				} else {
				    strcpy(wrapperFunc, prefixCARInterfaceForWrapper);
				    strcat(wrapperFunc, (char *)pName);
				}
			} else {
			    wrapperFunc = (char*)desc;
			}

			clazz = dvmFindClass(wrapperFunc, method->clazz->classLoader);
			Method *methodID = dvmFindDirectMethodByDescriptor(clazz, "<init>", "()V");
			obj = dvmClassNewInstance(clazz, methodID);
			*(u4 *)(((char *)obj)+clazz->objectSize) = pCARObject;
            break;
        }
		default:
			obj = (Object*)pCARObject;
	} //end of switch (dataType)

	pTypeInfo->Release();
    pParamInfo->Release();

	return  obj;
}

/*
 * convert CAR complex datatype data into Java Object
 *
 * object, this object pointer based on which calling method
 * pJavaObject, the parameter, which wants to be converted
 * idxParam, the parameter index in Java, 0 is the [out] return parameter
 */
void *dvmJavaObject2CARObject(Thread *self, Object *object, const Method *method, u4 pJavaObject, int idxParam)
{
    IParamInfo       *pParamInfo;
    IMethodInfo      *pMethodInfo;
    IDataTypeInfo    *pTypeInfo = NULL;
    IDataTypeInfo    *pElementTypeInfo = NULL;
    CarDataType       dataType;
	ParamIOAttribute  ioAttrib;
	void             *obj = NULL;
	CARMethodInfo    *pCARMethodInfo = method->pCARMethodInfo;
	ECode             ec;
    int               i;
    jsize             size;
    u8               *p;

    pMethodInfo = (IMethodInfo*)pCARMethodInfo->pMethodInfo;

    if (idxParam == 0) {
        idxParam = pCARMethodInfo->idxOutParam;
#if 0
//calculate this in allParamArePrimitive()

        //search for [out] parameter
        pMethodInfo->GetParamCount(&i);
        for(i--;  i >= 0;  i--) {
            pMethodInfo->GetParamInfoByIndex(i, &pParamInfo);
            pParamInfo->GetIOAttribute(&ioAttrib);
            if (ioAttrib == ParamIOAttribute_CallerAllocOut) {
                pParamInfo->GetTypeInfo(&pTypeInfo);
                pTypeInfo->GetDataType(&dataType);
                break;
            }
        }

        if (i < 0) {
		    LOGE("CAR [out] parameter error");
        }
#endif
    } else {
        pMethodInfo->GetParamInfoByIndex(idxParam, &pParamInfo);
    	pParamInfo->GetIOAttribute(&ioAttrib);
        pParamInfo->GetTypeInfo(&pTypeInfo);
        pTypeInfo->GetDataType(&dataType);
    }

    switch (dataType) {
        case CarDataType_Char8:
        case CarDataType_Char16:
        case CarDataType_Byte:
        case CarDataType_Int16:
        case CarDataType_Int32:
        case CarDataType_Float:
        case CarDataType_ECode:
		case CarDataType_Boolean:
		case CarDataType_Int64:
		case CarDataType_Double:
        	pTypeInfo->Release();
            pParamInfo->Release();
            return  (void *)pJavaObject;

	    case CarDataType_String: {
			char *s = dvmCreateCstrFromString((StringObject*)pJavaObject);
			obj = (void*)dvmElapiNewString(s);
			assert(obj==s);
			break;
		}

        //CAR don't allow StringBuf work as [in] parameter
	    case CarDataType_StringBuf: {
            StringBuf  *strbuf;
			char       *s = dvmCreateCstrFromString((StringObject*)pJavaObject);
            strbuf = (StringBuf*)dvmElapiNewStringBuf(strlen(s)+1);

	        obj = dvmElapiStringBufAppend(strbuf, s);
	        free(s);
            break;
	    }

		case CarDataType_ArrayOf: {
			((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
			pElementTypeInfo->GetDataType(&dataType);
            pElementTypeInfo->Release();
			size = ((ArrayObject*)pJavaObject)->length;
            p = ((ArrayObject*)pJavaObject)->contents;

			switch (dataType) {

			    /*
			     * dvmJavaObject2CARObject is working in Dalvik inside, shouldn't use JNI version
			     */

				case CarDataType_Boolean:
					obj = dvmElapiArrayCloneBoolean((unsigned char*)p, size);
					break;

				case CarDataType_Byte:
					obj = dvmElapiArrayCloneByte((unsigned char*)p, size);
					break;

				case CarDataType_Char8:
				case CarDataType_Char16: {
					jchar *pChar = (jchar*)p;
					char  *s = (char*)alloca(size*sizeof(char));
					for(i=0; i<size; i++)
					{
						s[i] = pChar[i];
					}
					obj = dvmElapiArrayCloneChar(s,size);
					break;
				}
				case CarDataType_Int16: {
                    u8 *p = ((ArrayObject*)pJavaObject)->contents;
					obj = dvmElapiArrayCloneShort((short*)p, size);
					break;
}
				case CarDataType_Int32:
					obj = dvmElapiArrayCloneInt((int*)p, size);
					break;

				case CarDataType_Int64:
					obj = dvmElapiArrayCloneLong((long long *)p, size);
					break;

				case CarDataType_Float:
					obj = dvmElapiArrayCloneFloat((float*)p, size);
					break;

				case CarDataType_Double:
					obj = dvmElapiArrayCloneDouble((double*)p, size);
					break;

				default:
					LOGE("This type of ArrayOf not implement");
			}
			break;
		}
		case CarDataType_BufferOf: {
			((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
			pElementTypeInfo->GetDataType(&dataType);
            pElementTypeInfo->Release();
			size = ((ArrayObject*)pJavaObject)->length;
            p = ((ArrayObject*)pJavaObject)->contents;

			switch (dataType) {
				case CarDataType_Boolean: {
					obj = dvmElapiBufferCloneBoolean((unsigned char *)p, size);
					break;
				}
				case CarDataType_Byte: {
					obj = dvmElapiBufferCloneByte((unsigned char *)p, size);
					break;
				}
				case CarDataType_Char8:
				case CarDataType_Char16: {
					jchar *pChar = (jchar*)p;
					char  *s = (char*)alloca(size*sizeof(char));
					for(i=0; i<size; i++)
					{
						s[i] = pChar[i];
					}
					obj = dvmElapiBufferCloneChar(s,size);
					break;
				}
				case CarDataType_Int16:
					obj = dvmElapiBufferCloneShort((short*)p, size);
					break;

				case CarDataType_Int32:
					obj = dvmElapiBufferCloneInt((int*)p, size);
					break;

				case CarDataType_Int64:
					obj = dvmElapiBufferCloneLong((long long *)p, size);
					break;

				case CarDataType_Float:
					obj = dvmElapiBufferCloneFloat((float*)p, size);
					break;

				case CarDataType_Double:
					obj = dvmElapiBufferCloneDouble((double*)p, size);
					break;

				default:
					LOGE("This type of BufferOf not implement");
			}
			break;
		}
		case CarDataType_Enum:
		{
			Object* obj = (Object*)pJavaObject;
			ClassObject* clazz = obj->clazz;
			Method* method = dvmFindVirtualMethodHierByDescriptor(clazz, "name", "()Ljava/lang/String;");
			JValue rt;
            StringBuf_<256>  pName;

			dvmCallMethod(self, method, obj, &rt);

			const char* s = dvmCreateCstrFromString((StringObject*)rt.l);

		    pTypeInfo->GetName(&pName);
            u4 CAREnumInfo = (u4)getEnumInfo((char*)pName, (IClassInfo*)(object->clazz->pClassInfo));
			i = dvmGetCAREnumInt((void*)CAREnumInfo, (char *)s);
    		dvmReleaseCARClassObject(CAREnumInfo);
			obj = (Object *)i;
			break;
		}
	    case CarDataType_Interface:
	    {
	        Object     *obj = (Object *)pJavaObject;
			u4          ifc = 0;
		    InterfaceID iid;
			ClassObject* clz;

		    ec = ((IInterfaceInfo*)pTypeInfo)->GetId(&iid);
            if (IS_CLASS_FLAG_SET(object->clazz, CLASS_CAR_INTERFACE)) {
                ifc = *(u4*)(((char*)object) + object->clazz->objectSize);
            } else {
                for (i = 0, clz = object->clazz;  clz != NULL;  clz = clz->super) {
                    if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
	                    ifc = (u4)ProbeInterface(*(u4*)(((char*)object) + object->clazz->objectSize + sizeof(u4)*i), (u4)(void*)&iid);
	                    if (ifc != 0)
	                        break;
	                    i++;
	                }
	            }
	        }
			obj = (Object *)ifc;
	        break;
	    }
		default:
			LOGE("This type not implement");
	} //end of switch (dataType)

	pTypeInfo->Release();
    pParamInfo->Release();

	return  obj;
}

/*
 * check wether all parameters are primitive datatype
 */
static int allParamArePrimitive(const Method *method)
{
    IParamInfo       *pParamInfo;
    IMethodInfo      *pMethodInfo;
    IDataTypeInfo    *pTypeInfo = NULL;
    CarDataType       dataType;
	CARMethodInfo    *pCARMethodInfo = method->pCARMethodInfo;
    int               i;
    int               count = 0;
	ParamIOAttribute  ioAttrib;

    pMethodInfo = (IMethodInfo*)pCARMethodInfo->pMethodInfo;
    pCARMethodInfo->idxOutParam = -1;

    pMethodInfo->GetParamCount(&i);
    for(i--;  i >= 0;  i--) {
        pMethodInfo->GetParamInfoByIndex(i, &pParamInfo);

		pParamInfo->GetIOAttribute(&ioAttrib);
		if (ioAttrib == ParamIOAttribute_CallerAllocOut) {
		    if (pCARMethodInfo->idxOutParam >= 0) {
        	    //warnning
        	    char buf[512];

        	    snprintf(buf, sizeof(buf)-1, "too many CAR [out] parameter:%d", i);
        	    dvmThrowException("Ljava/lang/IllegalArgumentException;", buf);
        		return  0;
    	    }
		    pCARMethodInfo->idxOutParam = (short)i;
		}

        pParamInfo->GetTypeInfo(&pTypeInfo);
        pTypeInfo->GetDataType(&dataType);
        switch (dataType) {
            case CarDataType_Char8:
            case CarDataType_Char16:
            case CarDataType_Byte:
            case CarDataType_Int16:
            case CarDataType_Int32:
            case CarDataType_Float:
            case CarDataType_ECode:
    		case CarDataType_Boolean:
    		case CarDataType_Int64:
    		case CarDataType_Double:
    		    count++;
    		    break;
	        default:
            	pTypeInfo->Release();
                pParamInfo->Release();
                return  0;
	    }
    	pTypeInfo->Release();
        pParamInfo->Release();
	}
	return  count;
}

//come from system/core/libcutils/mspace.c
extern "C" unsigned int mspace_usable_size(void *_unused, const void* mem);

//for JDWP support
int dvmSetCARInspectObjMoreInfo(Object *JavaHostObj,Object *CARObjectDescObj, u4 *pCARObject, int idxCARObjInJavaObj)
{
    ClassObject* clzHost = JavaHostObj->clazz;
    ClassObject* clzDesc = CARObjectDescObj->clazz;
    IClassInfo*  pClassInfo=(IClassInfo*)clzHost->pClassInfo;

    //jmethodID    methodID;
    //jstring      jstr;
    Method       *meth;
    StringObject *str;
    JValue        unused;

    Thread* self = dvmThreadSelf();
    //JNIEnv* pJNIEnv = self->jniEnv;

    //setCARClassName
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setCARClassName", "(Ljava/lang/String;)V");
    str = dvmCreateStringFromCstr(dvmGetCARClassAnnotationValue(clzHost, (char*)"Class"));
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, str);
    dvmReleaseTrackedAlloc((Object*)str, self);


    //setJavaClassName
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setJavaClassName", "(Ljava/lang/String;)V");
    str = dvmCreateStringFromCstr(clzHost->descriptor);
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, str);
    dvmReleaseTrackedAlloc((Object*)str, self);

    //setCARObjSize
	Int32 size;
	size = mspace_usable_size(NULL, pCARObject);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setCARObjSize", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, size);

    //setCARObjAddr
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setCARObjAddr", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, pCARObject);

    //setIsSingleton
    Boolean b;
    pClassInfo->IsSingleton(&b);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setIsSingleton", "(Z)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, b);

    //setMethodCount
    Int32 mc;
    pClassInfo->GetMethodCount(&mc);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setMethodCount", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, mc);

    //setAspectCount
    Int32 AsC;
    pClassInfo->GetAspectCount(&AsC);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setAspectCount", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, AsC);

    //setAggregateeCount
    Int32 AgC;
    pClassInfo->GetAggregateeCount(&AgC);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setAggregateeCount", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, AgC);

    //setInterfaceCount
    Int32 InC;
    pClassInfo->GetInterfaceCount(&InC);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setInterfaceCount", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, InC);

    //setCallbackInterfaceCount
    Int32 CakInC;
    pClassInfo->GetCallbackInterfaceCount(&CakInC);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setCallbackInterfaceCount", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, CakInC);

    //setCallbackMethodCount
    Int32 CakMeC;
    pClassInfo->GetCallbackMethodCount(&CakMeC);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setCallbackMethodCount", "(I)V");
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, CakMeC);

    //setID
    ClassID cID;
    char  buf1[256];
    cID.pUunm=buf1;
    pClassInfo->GetId(&cID);
    char  buf2[256];
    sprintf (buf2,"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            cID.clsid.Data1,cID.clsid.Data2,cID.clsid.Data3,
            cID.clsid.Data4[0],cID.clsid.Data4[1],cID.clsid.Data4[2],cID.clsid.Data4[3],
            cID.clsid.Data4[4],cID.clsid.Data4[5],cID.clsid.Data4[6],cID.clsid.Data4[7]);
    meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setID", "(Ljava/lang/String;)V");
    str = dvmCreateStringFromCstr(buf2);
    dvmCallMethod(self, meth, CARObjectDescObj, &unused, str);
    dvmReleaseTrackedAlloc((Object*)str, self);

    //setConstructorCount
/*
LOGD("111111");
    Int32 CoC;
LOGD("222222");
    pClassInfo->GetConstructorCount(&CoC);
LOGD("333333");
    methodID=pJNIEnv->GetMethodID((jclass)clzDesc, "setConstructorCount", "(I)V");
    pJNIEnv->CallVoidMethod((jobject)CARObjectDescObj,methodID,CoC);
*/
    //setMemDump
    int byteCount=8;
	ArrayObject* memDump = dvmAllocPrimitiveArray('B',byteCount,ALLOC_DEFAULT);
	memcpy(memDump->contents, pCARObject, byteCount);
	meth = dvmFindVirtualMethodByDescriptor(clzDesc, "setMemDump", "([B)V");
	dvmCallMethod(self, meth, CARObjectDescObj, &unused, memDump);

    //set information from pClassInfo and pCARObject
    return  0;
}


/**
 * dvmCacheCARModuleInBootclasspath()
 */
bool dvmCacheCARModuleInBootclasspath(char *CARModule)
{
	IModuleInfo *pModuleInfo;
	ECode        ec;
	IClassInfo  *pClassInfo, **ppClassInfo;
    BufferOf<IClassInfo *>  *pmClassInfo;
    int          count = 0;
    Boolean      tf;

	if (CARModule == NULL) {
		LOGE("Can not create class object without module name or class name");
		return false;
	}

	LOGD("CacheModuleInBootclasspath");

	dvmHashTableLock(gDvm.nativeLibs);
	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(CARModule, kAddRefCount, NULL);
	if (pModuleInfo == NULL) {
	    ec = _CReflector_AcquireModuleInfo(CARModule, &pModuleInfo);
	    if (FAILED(ec)) {
		    LOGD("_CReflector_AcquireModuleInfo Failed");
	        dvmHashTableUnlock(gDvm.nativeLibs);
		    return false;
		}

        pModuleInfo->GetClassCount(&count);
        if (count <= 0) {
		    LOGD("_CReflector_AcquireModuleInfo with no Class CAR component");
		    pModuleInfo->Release();
	        dvmHashTableUnlock(gDvm.nativeLibs);
		    return false;
		}

		if (addHashCARModuleInfo(CARModule, pModuleInfo) == NULL) {
		    LOGD("add hash _CReflector_AcquireModuleInfo Failed");
		}
	} else {
        pModuleInfo->GetClassCount(&count);
	}
	dvmHashTableUnlock(gDvm.nativeLibs);


    pmClassInfo = BufferOf<IClassInfo *>::Alloc(count);
    pModuleInfo->GetAllClassInfos(pmClassInfo);

    ppClassInfo = pmClassInfo->GetPayload();
    for (count--;  count >= 0;  count--) {
        pClassInfo = ppClassInfo[count];

    	pClassInfo->IsSingleton(&tf);
    	if (tf) {
            /*
    	     * cause the CAR environment to initialize its singleton class object.
    	     *
             * pCARObject needn't to be managed, another calling of CreateCARSingletonObject()
             * will return the same one.
            */
            u4 *pCARObject = (u4*)CreateCARSingletonObject(pClassInfo);
            if (pCARObject == NULL)
                LOGD("CreateCARSingletonObject returns NULL");
	    }
    }

	BufferOf<IClassInfo *>::Free(pmClassInfo);
	pModuleInfo->Release();

	return true;
}


/**
 * Constructor of CAR singleton class can't have any parameter!
 */
static u4 CreateCARSingletonObject(IClassInfo *pClassInfo)
{
	LOGD("CreateCARSingletonObject");

	PInterface        pObject;
	ECode             ec;
    //IConstructorInfo *pConstructorInfo;
    IMethodInfo      *pMethodInfo;

    ec = pClassInfo->CreateObject(&pObject);
	if (FAILED(ec)) {
		LOGD("CreateObject Failed");
	    char buf[512];

	    snprintf(buf, sizeof(buf)-1, "CreateObject Failed: (ECode = %d)", ec);
	    dvmThrowException("Ljava/lang/NullPointerException;", buf);
		return NULL;
	}

    ec = pClassInfo->GetMethodInfo("SingletonInit", &pMethodInfo);
	if (SUCCEEDED(ec)) {
        struct MyCArgumentList {
            void  *thisPtr;
            unsigned int *m_pParamBuf;
        } myArgumentList;
        unsigned int buf[4];
        void  *p = &myArgumentList;

        myArgumentList.m_pParamBuf = (unsigned int *)&buf[0];
        buf[1] = (int)dvmThreadSelf()->jniEnv;
        buf[2] = 0;
        buf[3] = 0;
        ec = pMethodInfo->Invoke(pObject, (IArgumentList*)p);

        pMethodInfo->Release();
    }

	return (u4)pObject;
}

/**
 * check whether a CAR method is Getter/Setter standard function, it is defined in Object.h
 * typedef void (*CARGetter)(void *thisCAR, void *InstField, void *data);
 * typedef void (*CARSetter)(void *thisCAR, void *InstField, void *data);
 * typedef void (*CARStaticGetter)(void *thisCAR, void *StaticField, void *data);
 * typedef void (*CARStaticSetter)(void *thisCAR, void *StaticField, void *data);
 */
static bool checkCarSetterGetterOfField(IMethodInfo *pMethodInfo)
{
    IArgumentList   *pArgumentList;
    ECode            ec;
    IFunctionInfo   *functionInfo;
    int              count = 0;
    IParamInfo      *pParamInfo;
    IDataTypeInfo   *pTypeInfo;
    ParamIOAttribute ioAttrib;
    CarDataType      dataType;

    ec = pMethodInfo->CreateArgumentList(&pArgumentList);
    if (SUCCEEDED(ec)) {
        ec = pArgumentList->GetFunctionInfo(&functionInfo);
        if (FAILED(ec)) {
            pArgumentList->Release();
            return  false;
        }
        functionInfo->GetParamCount(&count);

        if (count != 2) {
            functionInfo->Release();
            pArgumentList->Release();
            return  false;
        }

        for (count--;  count >= 0;  count--) {
            pMethodInfo->GetParamInfoByIndex(count, &pParamInfo);
    		pParamInfo->GetIOAttribute(&ioAttrib);
            pParamInfo->GetTypeInfo(&pTypeInfo);
            pTypeInfo->GetDataType(&dataType);
            pTypeInfo->Release();
            pParamInfo->Release();

            if (ioAttrib != ParamIOAttribute_In || dataType != CarDataType_Int32) {
                functionInfo->Release();
                pArgumentList->Release();
                return  false;
            }
        }

        functionInfo->Release();
        pArgumentList->Release();
        return  true;
    }
    return  false;
}

/**
 * check whether a Java method is Getter/Setter standard function
 *
 * Java:
 *     dataType Function(dataType data)
 */
static bool checkJavaSetterGetterOfField(Field *field, Method *meth)
{
    if (meth->insSize != 1)
        return  false;

    if (field->signature[0] != meth->shorty[0] || field->signature[0] != meth->shorty[1])
        return  false;

    if (dvmIsStaticField(field) && !dvmIsStaticMethod(meth))
        return  false;

    return  true;
}

/**
  * check wether a Java class (described in returnDesc) suit to be a CAR method
  * (described in method) return interface type (described in pInterfaceName)
  */
static int checkClassForOutInterface(Method *method, const char *returnDesc, char *pInterfaceName)
{
	char        *desc;
	char        *cp;
	ClassObject *clazz, *clz;
	int          len;
	char        *wrapperFunc;
	IClassInfo  *pClassInfo;
	IInterfaceInfo  *pInterfaceInfo;
    StringBuf_<256>  pName;
    ECode            ec;

	if (strcmp(returnDesc, "Ljava/lang/Object;") == 0) {

		/* regExtraData[i] = CAR IInterface name
		 * return object is newed from class: packageName + "Wrapper" + CAR IInterface name
		 * packageName is same as method which provides this function
		 */

		desc = (char*)method->clazz->descriptor;
		len = strlen(desc);
		wrapperFunc = (char *)alloca((len+strlen(prefixCARInterfaceForWrapper)+1)*sizeof(char));

		for(cp = desc+len; cp != desc; cp--) {
		    if (*cp == '/')
				break;
		}

		if (cp != desc) {
		    cp++;
		    strncpy(wrapperFunc, desc, cp-desc);
		    strcpy(wrapperFunc+(cp-desc), prefixCARInterfaceForWrapper);
		    strcat(wrapperFunc, pInterfaceName);
		} else {
		    strcpy(wrapperFunc, prefixCARInterfaceForWrapper);
		    strcat(wrapperFunc, pInterfaceName);
		}
	} else {
	    wrapperFunc = (char*)returnDesc;
	}

	LOGD("wrapperFunc %s", wrapperFunc);

	clazz = dvmFindClass(wrapperFunc, method->clazz->classLoader);
	if (clazz == NULL) {
	    return  1;
	}

	//there first one CARed class should contain only on CARClass and the CARClass has only interface
	for (clz = clazz;  clz != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS|CLASS_CAR_INTERFACE))
            break;
    }
	if (clz == NULL) {
	    return  2;
	}

    if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
        int  interfaceCount;
        BufferOf<IInterfaceInfo*>  *interfaceInfos;

	    if (dvmIsStaticMethod(method))
		    pClassInfo = (IClassInfo*)(clz->pStaticClassInfo);
		else
		    pClassInfo = (IClassInfo*)(clz->pClassInfo);

		if (pClassInfo == NULL)
		    return  3;

        ec = pClassInfo->GetInterfaceCount(&interfaceCount);
        if (FAILED(ec) || interfaceCount != 3)
            return  4;

	    interfaceInfos = BufferOf<IInterfaceInfo*>::Alloc(interfaceCount);
        ec = pClassInfo->GetAllInterfaceInfos(interfaceInfos);
        if (FAILED(ec)) {
            BufferOf<IInterfaceInfo*>::Free(interfaceInfos);
            return  5;
        }

        IInterfaceInfo** pInterfaceInfos = interfaceInfos->GetPayload();
        pInterfaceInfo = pInterfaceInfos[1];
        pInterfaceInfo->GetName(&pName);
        BufferOf<IInterfaceInfo*>::Free(interfaceInfos);

        if (strcmp((char*)pName, pInterfaceName) != 0)
            return  6;

    } else { /*CLASS_CAR_INTERFACE*/
        pInterfaceInfo = (IInterfaceInfo*)clz->pClassInfo;
        pInterfaceInfo->GetName(&pName);
        if (strcmp((char*)pName, pInterfaceName) != 0)
            return  7;
    }

    return  -1;
}


/**
  * check two interfaces, wether they are the same
  */
bool dvmChkInterfaceWithInterfaceID(u4 theInterface, u4 piid)
{
	InterfaceID  iid2;

    ((IInterface*)theInterface)->GetInterfaceID((IInterface*)theInterface, &iid2);
    if (memcmp((void*)piid, &iid2, sizeof(InterfaceID)) != 0) {
        return  false;
    }

	return  true;
}

/**
  * create an object for a CAR generic class
  *
  * when a CARed class is CAR generic, it could be NULL temporarily, it means
  * the NEW of the generic return  NULL.
  *
  * ElastosGeneric java class will call this function to create a substituted object
  */
void *dvmObjectSubstituteGeneric(Object* object, int inheritanceLevel,
                                 char *ElastosModuleName, char *ElastosClassName)
{
	IModuleInfo *pModuleInfo;
	IClassInfo  *pClassInfo;
	PInterface   pObject;
	ECode        ec;
    IConstructorInfo *pConstructorInfo;
    u4          *pCARObject;
    ClassObject *clz;
    ClassObject *clazz = object->clazz;
    int          layerCount;
    Boolean      b;
    u4          *pobj;

    if (ElastosModuleName == NULL || ElastosClassName == NULL)
        return  NULL;

    //check the generic's property
    for (layerCount = inheritanceLevel, clz = clazz;  clz->super != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
            if (layerCount <= 0)
                break;
            layerCount--;
        }
    }

    if (layerCount != 0)
        return  NULL;

    pClassInfo = (IClassInfo*)clz->pClassInfo;
    pClassInfo->IsGeneric(&b);
    if (!b)
        return  NULL;

    pobj = (u4*)((char*)object + clazz->objectSize + sizeof(u4)*inheritanceLevel);
    pCARObject = (u4*)*pobj;
    if (pCARObject != NULL) {
        ((IInterface*)pCARObject)->Release();
        *pobj = NULL;
    }

    /**
     * CARModule should in the same directory with java class file,
     * clazz->pDvmDex->pDexFile->dexFilePath;
     *
     * OR
     * in the Elastos system directory
     */
    char *cachedName;

    if (clazz->pDvmDex != NULL) {
        cachedName = dexOptGenerateCacheFileName(clazz->pDvmDex->pDexFile->dexFilePath, ElastosModuleName);
        if (cachedName == NULL) {
    	    LOGD("dexOptGenerateCacheFileName Failed");
    	    return NULL;
        }
    } else {
        cachedName = ElastosModuleName;
    }

	dvmHashTableLock(gDvm.nativeLibs);
	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(ElastosModuleName, kAddRefCount, NULL);
	if (pModuleInfo == NULL) {
	    ec = _CReflector_AcquireModuleInfo(ElastosModuleName, &pModuleInfo);
	    if (FAILED(ec)) {
		    if (clazz->pDvmDex != NULL) {
                //continue search CAR in Elastos system path
            	pModuleInfo = (IModuleInfo*)findHashCARModuleInfo(ElastosModuleName, kAddRefCount, NULL);
            	if (pModuleInfo == NULL) {
            	    ec = _CReflector_AcquireModuleInfo(ElastosModuleName, &pModuleInfo);
            	    if (FAILED(ec)) {
		                LOGD("_CReflector_AcquireModuleInfo Failed");
            	        dvmHashTableUnlock(gDvm.nativeLibs);
		                free(cachedName);
            		    return  NULL;
            		}
  		    		if (addHashCARModuleInfo(ElastosModuleName, pModuleInfo) == NULL) {
    		            LOGD("add hash _CReflector_AcquireModuleInfo Failed");
    		        }
    		    }
    		}
		} else {
    		if (addHashCARModuleInfo(ElastosModuleName, pModuleInfo) == NULL) {
    		    LOGD("add hash _CReflector_AcquireModuleInfo Failed");
    		}
		}
	}
	dvmHashTableUnlock(gDvm.nativeLibs);

    if (clazz->pDvmDex != NULL)
	    free(cachedName);

	ec = pModuleInfo->GetClassInfo(ElastosClassName, &pClassInfo);
	if (FAILED(ec)) {
		return NULL;
	}

    pClassInfo->IsGeneric(&b);
    if (b) {
        //should not be a generic class
        pClassInfo->Release();
        return  NULL;
    }

    ec = pClassInfo->GetConstructorInfoByParamCount(3, (IConstructorInfo **)&pConstructorInfo);
    if (FAILED(ec)) {
    	ec = pClassInfo->CreateObject(&pObject);
    } else {
        Thread        *self = dvmThreadSelf();

        if (self->pArgumentList == (u4)NULL) {

            IArgumentList *pArgumentList;

            ec = pConstructorInfo->CreateArgumentList(&pArgumentList);
            if (SUCCEEDED(ec)) {
                self->pArgumentList = (u4)pArgumentList;
                pArgumentList->SetInputArgumentOfInt32(0, (int)(self->jniEnv));
                pArgumentList->SetInputArgumentOfInt32(1, (int)object->clazz);
                pArgumentList->SetInputArgumentOfInt32(2, (int)object);
                ec = pConstructorInfo->CreateObject(pArgumentList, &pObject);
            }
        } else {
            typedef struct tagMyCArgumentList {
                void  *thisPtr;
                unsigned int *m_pParamBuf;
            } MyCArgumentList;

            unsigned int *buf;

            buf = ((MyCArgumentList*)(self->pArgumentList))->m_pParamBuf;
            buf[1] = (int)self->jniEnv;
            buf[2] = (int)object->clazz;
            buf[3] = (int)object;

            ec = pConstructorInfo->CreateObject((IArgumentList*)self->pArgumentList, &pObject);
        }

        //ConstructorInfo has been cached
        //pConstructorInfo->Release();
    }

	pClassInfo->Release();

	if (FAILED(ec)) {
	    char buf[512];

		LOGD("CreateObject Failed");

	    snprintf(buf, sizeof(buf), "CreateObject Failed: (ECode = %d)%s", ec, object->clazz->descriptor);
	    dvmThrowException("Ljava/lang/NullPointerException;", buf);
		return NULL;
	}

    *pobj = (u4)pCARObject;

	return (void *)pObject;
}


bool dvmIsCARClassGeneric(const ClassObject *clazz)
{
    Boolean  b;

    ((IClassInfo*)(clazz->pClassInfo))->IsGeneric(&b);

    return  b;
}


/**
  * check the compatibility of a CAR function (parameter IFunctionInfo *pIFun) and a
  * java function (parameter Method *meth)
  *
  * this check is static check
  */
static bool checkCompatibilityOfIFunctionInfoAndMethod(IFunctionInfo *pIFun, Method *meth)
{
    //ECode            ec;
    int              paramCount = 0;
    IParamInfo      *pParamInfo;
    IDataTypeInfo   *pTypeInfo;
    ParamIOAttribute ioAttrib;
    CarDataType      dataType, elementDataType;
	const char     **paramDesc;
    DexParameterIterator iterator;
    const char      *protoDesc;
    Int32            i, k, outParamNum;
    char             c1 = '\0';
    IDataTypeInfo   *pElementTypeInfo = NULL;
    ClassObject     *clazz;
    Method          *methodEnum, *methodEnum2;
    const char      *s;


	paramDesc = (const char**)_alloca((meth->insSize+1)*sizeof(char*));

    dexParameterIteratorInit(&iterator, &(meth->prototype));
    protoDesc = dexParameterIteratorNextDescriptor(&iterator);
    k = 0;
    while (protoDesc != NULL) {
        paramDesc[k++] = protoDesc;
        protoDesc = dexParameterIteratorNextDescriptor(&iterator);
    }

    outParamNum = 0;
    pIFun->GetParamCount(&paramCount);
    for (i = 0;  i < paramCount;  i++) {
        pIFun->GetParamInfoByIndex(i, &pParamInfo);
		pParamInfo->GetIOAttribute(&ioAttrib);
        pParamInfo->GetTypeInfo(&pTypeInfo);
        pTypeInfo->GetDataType(&dataType);
        pTypeInfo->Release();
        pParamInfo->Release();

		if (dataType == CarDataType_ArrayOf || dataType == CarDataType_BufferOf) {
		    ((ICarArrayInfo*)pTypeInfo)->GetElementTypeInfo(&pElementTypeInfo);
			pElementTypeInfo->GetDataType(&elementDataType);
			pElementTypeInfo->Release();
		}

		if (ioAttrib == ParamIOAttribute_In) {
		    c1 = meth->shorty[i+1];
		} else if (ioAttrib == ParamIOAttribute_CallerAllocOut) {
			c1 = meth->shorty[0];

			//only one [out] parameter is allowed
		    if (c1 == 'V' || outParamNum != 0) {
		        return  false;
		    }
			outParamNum++;

		} else {
		    return  false;
		}

	    switch (dataType) {
	        case CarDataType_Char8:
	        case CarDataType_Char16:
	        case CarDataType_Byte:
	        case CarDataType_Int16:
	        case CarDataType_Int32:
	        case CarDataType_Float:
	        case CarDataType_ECode:
			case CarDataType_Boolean:
				switch (c1) {
                    //case '[':       //JT_ARRAY
                    case 'B':       //JT_BYTE
                    case 'C':       //JT_CHAR
                    //case 'L':       //JT_OBJECT
                    case 'F':       //JT_FLOAT
                    //case 'D':       //JT_DOUBLE
                    case 'I':       //JT_INT
                    case 'J':       //JT_LONG
                    case 'S':       //JT_SHORT
                    //case 'V':       //JT_VOID
                    case 'Z':       //JT_BOOLEAN
                        break;
				    default:
				        return  false;
				}
				break;
			case CarDataType_Int64:
				switch (c1) {
                    //case '[':       //JT_ARRAY
                    //case 'B':       //JT_BYTE
                    //case 'C':       //JT_CHAR
                    //case 'L':       //JT_OBJECT
                    //case 'F':       //JT_FLOAT
                    //case 'D':       //JT_DOUBLE
                    //case 'I':       //JT_INT
                    case 'J':       //JT_LONG
                    //case 'S':       //JT_SHORT
                    //case 'V':       //JT_VOID
                    //case 'Z':       //JT_BOOLEAN
                        break;
				    default:
				        return  false;
				}
				break;
			case CarDataType_Double:
				switch (c1) {
                    //case '[':       //JT_ARRAY
                    //case 'B':       //JT_BYTE
                    //case 'C':       //JT_CHAR
                    //case 'L':       //JT_OBJECT
                    //case 'F':       //JT_FLOAT
                    case 'D':       //JT_DOUBLE
                    //case 'I':       //JT_INT
                    //case 'J':       //JT_LONG
                    //case 'S':       //JT_SHORT
                    //case 'V':       //JT_VOID
                    //case 'Z':       //JT_BOOLEAN
                        break;
				    default:
				        return  false;
				}
				break;
	        case CarDataType_String:
				switch (c1) {
                    //case '[':       //JT_ARRAY
                    //case 'B':       //JT_BYTE
                    //case 'C':       //JT_CHAR
                    case 'L':       //JT_OBJECT
    				    if (strcmp(paramDesc[i], "Ljava/lang/String;") == 0) {
    				        break;
    				    } else {
    				        return  false;
    				    }
                        break;
                    //case 'F':       //JT_FLOAT
                    //case 'D':       //JT_DOUBLE
                    //case 'I':       //JT_INT
                    //case 'J':       //JT_LONG
                    //case 'S':       //JT_SHORT
                    //case 'V':       //JT_VOID
                    //case 'Z':       //JT_BOOLEAN
                        break;
				    default:
				        return  false;
				}
				break;
			case CarDataType_Interface:
				switch (c1) {
                    //case '[':       //JT_ARRAY
                    //case 'B':       //JT_BYTE
                    //case 'C':       //JT_CHAR
                    case 'L':       //JT_OBJECT
                        break;
                    //case 'F':       //JT_FLOAT
                    //case 'D':       //JT_DOUBLE
                    //case 'I':       //JT_INT
                    //case 'J':       //JT_LONG
                    //case 'S':       //JT_SHORT
                    //case 'V':       //JT_VOID
                    //case 'Z':       //JT_BOOLEAN
                        break;
				    default:
				        return  false;
				}
				break;

            case CarDataType_Enum:
                /*
                 * check wether it is a enum class
                 *
                 * we check methods of the class, for enum could be a lot of pattern
                 */
		        if (ioAttrib == ParamIOAttribute_In) {
    				clazz = dvmFindClass(paramDesc[i], meth->clazz->classLoader);
                } else {
    				clazz = dvmGetBoxedReturnType(meth);
    			}

				if (clazz == NULL) {
    		        return  false;
    		    }

				methodEnum = dvmFindDirectMethodHierByDescriptor(clazz, "valueOf", "(Ljava/lang/Class;Ljava/lang/String;)Ljava/lang/Enum;");
			    methodEnum2 = dvmFindVirtualMethodHierByDescriptor(clazz, "name", "()Ljava/lang/String;");
				if (methodEnum == NULL || methodEnum2 == NULL)
				    return  false;
                break;

            case CarDataType_StringBuf:
                if (ioAttrib != ParamIOAttribute_CallerAllocOut) {
			        return  false;
			    }

                s = dexProtoGetReturnType(&meth->prototype);
			    if (strcmp(s, "Ljava/lang/StringBuffer;") == 0) {
			        break;
			    } else {
			        return  false;
			    }

                break;

			case CarDataType_ArrayOf:
			case CarDataType_BufferOf:
			    if (c1 != '[')
			        return  false;

                //I am sure paramDesc[i][0] == '[', loop from 0 for realibility
                int  j;
                for(j = 0;  paramDesc[i][j] == '[';  j++) ;
                c1 = paramDesc[i][j];

    		    switch (elementDataType) {
    		        case CarDataType_Char8:
    		        case CarDataType_Char16:
    		        case CarDataType_Byte:
    		        case CarDataType_Int16:
    		        case CarDataType_Int32:
    		        case CarDataType_Float:
    		        case CarDataType_ECode:
    				case CarDataType_Boolean:
    					switch (c1) {
                            //case '[':       //JT_ARRAY
                            case 'B':       //JT_BYTE
                            case 'C':       //JT_CHAR
                            //case 'L':       //JT_OBJECT
                            case 'F':       //JT_FLOAT
                            //case 'D':       //JT_DOUBLE
                            case 'I':       //JT_INT
                            case 'J':       //JT_LONG
                            case 'S':       //JT_SHORT
                            //case 'V':       //JT_VOID
                            case 'Z':       //JT_BOOLEAN
                                break;
    					    default:
    					        return  false;
    					}
    					break;
    				case CarDataType_Int64:
    					switch (c1) {
                            //case '[':       //JT_ARRAY
                            //case 'B':       //JT_BYTE
                            //case 'C':       //JT_CHAR
                            //case 'L':       //JT_OBJECT
                            //case 'F':       //JT_FLOAT
                            //case 'D':       //JT_DOUBLE
                            //case 'I':       //JT_INT
                            case 'J':       //JT_LONG
                            //case 'S':       //JT_SHORT
                            //case 'V':       //JT_VOID
                            //case 'Z':       //JT_BOOLEAN
                                break;
    					    default:
    					        return  false;
    					}
    					break;
    				case CarDataType_Double:
    					switch (c1) {
                            //case '[':       //JT_ARRAY
                            //case 'B':       //JT_BYTE
                            //case 'C':       //JT_CHAR
                            //case 'L':       //JT_OBJECT
                            //case 'F':       //JT_FLOAT
                            case 'D':       //JT_DOUBLE
                            //case 'I':       //JT_INT
                            //case 'J':       //JT_LONG
                            //case 'S':       //JT_SHORT
                            //case 'V':       //JT_VOID
                            //case 'Z':       //JT_BOOLEAN
                                break;
    					    default:
    					        return  false;
    					}
    					break;
    		    } //switch (elementDataType)
				break;
			default:
			    return  false;
		} //switch (dataType)
    }  //for(i)

    if ((paramCount - outParamNum) != k || ((meth->shorty[0] != 'V') && (outParamNum == 0)))
        return  false;

    return  true;
}



/*
 * public newInstance()
 *
 * Create a new instance of clazz.
 */
Object *dvmClassNewInstance(ClassObject *clazz, Method *init, ...)
{
    if (clazz == NULL || init == NULL)
        return  NULL;

    Thread *self = dvmThreadSelf();
    Object *newObj;

    /* initialize the class if it hasn't been already */
    if (!dvmIsClassInitialized(clazz) && !dvmInitClass(clazz)) {
        assert(dvmCheckException(_self));
        return  NULL;
    }

    newObj = dvmAllocObject(clazz, ALLOC_DEFAULT);
    if (newObj != NULL) {
        JValue unused;
        va_list args;

        va_start(args, init);
        //invoke constructor; unlike reflection calls, we don't wrap exceptions
        dvmCallMethodV(self, init, newObj, false, &unused, args);
        va_end(args);

        dvmReleaseTrackedAlloc(newObj, NULL);
    }

    return  newObj;
}


void dvmSetgDvmshouldCARWorking(bool b)
{
    gDvm.shouldCARWorking = b;
}


static void releaseCARMethodInfoInside(Method* meth, Int32 paramCount)
{
    CARMethodInfo *pCARMethodInfo = meth->pCARMethodInfo;

    if ((void*)pCARMethodInfo == NULL)
        return;

	ClassObject *clazz = meth->clazz;

    if ((void*)pCARMethodInfo->pMethodInfo != NULL) {
    	IInterfaceInfo  *pInterfaceInfo = NULL;
    	//ECode            ec = -1;
        Int32            i;
        IParamInfo      *pParamInfo = NULL;
        IDataTypeInfo   *pTypeInfo = NULL;
        //IDataTypeInfo   *pElementTypeInfo = NULL;
        CarDataType      dataType;
    	ParamIOAttribute ioAttrib;
    	int              actualArgs = 1;

	    IMethodInfo* pMethodInfo = (IMethodInfo*)pCARMethodInfo->pMethodInfo;
    	//u4* regTypes = meth->pCARMethodInfo->regTypes;
    	u4* regExtraData = pCARMethodInfo->regExtraData;

        for (i = 0; i < paramCount; i++) {
            pMethodInfo->GetParamInfoByIndex(i, &pParamInfo);
    		pParamInfo->GetIOAttribute(&ioAttrib);
            pParamInfo->GetTypeInfo(&pTypeInfo);
            pTypeInfo->GetDataType(&dataType);

    		if (ioAttrib == ParamIOAttribute_In) {
    		    switch (dataType) {
                    case CarDataType_Enum:
                        pInterfaceInfo = (IInterfaceInfo *)regExtraData[actualArgs];
                        ((IInterface *)pInterfaceInfo)->Release();
                        break;
    				case CarDataType_Interface:
    				    //free InterfaceID
    				    free((void*)regExtraData[actualArgs]);
    				    break;
    		    }
    		} else if (ioAttrib == ParamIOAttribute_CallerAllocOut) {
    			switch (dataType) {
                    case CarDataType_Enum:
                        pInterfaceInfo = (IInterfaceInfo *)regExtraData[actualArgs];
                        ((IInterface *)pInterfaceInfo)->Release();
                        break;
    				case CarDataType_Interface:
    				    //free Interface name
    				    free((void*)regExtraData[actualArgs]);
    				    break;

    			}
    		}
    		actualArgs++;
    	}
        pMethodInfo->Release();
    }

	if (pCARMethodInfo->regTypes != NULL) {
		dvmLinearFree(clazz->classLoader, (void*)pCARMethodInfo->regTypes);
	}
	if (pCARMethodInfo->regExtraData != NULL) {
		dvmLinearFree(clazz->classLoader, (void*)pCARMethodInfo->regExtraData);
	}

	dvmLinearFree(clazz->classLoader, (void*)pCARMethodInfo);
	meth->pCARMethodInfo = NULL;
}

static void insideThrowException(const char* msg)
{
    if (gDvm.noClassDefFoundErrorObj != NULL) {
        dvmThrowExceptionWithClassMessage("Ljava/lang/NoClassDefFoundError;", msg);
    }
}

