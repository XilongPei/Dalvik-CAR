#include "Dalvik.h"
#include "native/InternalNativePriv.h"
#include "ElastosBridgeApi.h"

static void Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandler(const u4* args,
    JValue* pResult)
{
	LOGD("Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandler");
	Object* CARObj = (Object*)args[0];
	//u4 CARObj = *(u4 *)(((char *)obj)+obj->clazz->objectSize);

	StringObject* nameObj;
	nameObj = (StringObject*)args[1];
	char* callbackMethodName = dvmCreateCstrFromString(nameObj);

	nameObj = (StringObject*)args[2];
	ClassObject* clazz;

	//Now we use dvmGetSystemClassLoader to specify the classLoader, this may be changed in the future.
	if (CARObj->clazz->classLoader != NULL) {
	    clazz = dvmFindClassByName(nameObj, CARObj->clazz->classLoader, true);
	} else {
	    clazz = dvmFindClassByName(nameObj, dvmGetSystemClassLoader(), true);
	}

	nameObj = (StringObject*)args[3];
	char* methodName = dvmCreateCstrFromString(nameObj);

	nameObj = (StringObject*)args[4];
	char* methodDescript = dvmCreateCstrFromString(nameObj);

	Method* method = dvmFindDirectMethodByDescriptor(clazz, methodName, methodDescript);
	LOGD("method %p", method);
	dvmAddCallbackHandler(CARObj, callbackMethodName, clazz, method);

	free(callbackMethodName);
	free(methodName);
	free(methodDescript);
}

static void Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandlerNoSignature(const u4* args,
    JValue* pResult)
{
	Object* CARObj = (Object*)args[0];
	bool    inVirtual;
	int     nameConflict;

	//u4 CARObj = *(u4 *)(((char *)obj)+obj->clazz->objectSize);

	StringObject* nameObj;
	nameObj = (StringObject*)args[1];
	char* callbackMethodName = dvmCreateCstrFromString(nameObj);

	nameObj = (StringObject*)args[2];
	ClassObject* clazz;
	//Now we use dvmGetSystemClassLoader to specify the classLoader, this may be changed in the future.
	if (CARObj->clazz->classLoader != NULL) {
	    clazz = dvmFindClassByName(nameObj, CARObj->clazz->classLoader, true);
	} else {
	    clazz = dvmFindClassByName(nameObj, dvmGetSystemClassLoader(), true);
	}

	nameObj = (StringObject*)args[3];
	char* methodName = dvmCreateCstrFromString(nameObj);

	Method* method = dvmFindMethodInListByNameForCAR(clazz, methodName, &inVirtual, &nameConflict);
	LOGD("method %p", method);

	if (nameConflict == 1) {
	    dvmAddCallbackHandler(CARObj, callbackMethodName, clazz, method);
    } else {
	    LOGD("name Conflict, cannot locate the method %s", methodName);
    }

	free(callbackMethodName);
	free(methodName);
}


static void Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandlerByMethodObject(const u4 *args,
    JValue *pResult)
{
	Object *CARObj = (Object *)args[0];

	StringObject* nameObj;
	nameObj = (StringObject*)args[1];
	char* callbackMethodName = dvmCreateCstrFromString(nameObj);

	Method *method = (Method *)args[2];
	dvmAddCallbackHandler(CARObj, callbackMethodName, method->clazz, method);
	free(callbackMethodName);
}


static void Dalvik_dalvik_CAR_CARCallbackFunc_removeCallbackHandler(const u4* args,
    JValue* pResult)
{
	LOGD("removeCallbackHandler NOT IMPLEMENTED");
}

static void Dalvik_dalvik_CAR_CARCallbackFunc_removeAllCallbackHandler(const u4* args,
    JValue* pResult)
{
	Object  *CARObj = (Object*)args[0];

	LOGD("removeAllCallbackHandler");
	dvmRemoveAllCallbackHandler(CARObj);
}

/*
 * int i = CAREnum(obj, "enum");
 *//*
static void Dalvik_dalvik_CAR_CARCallbackFunc_CAREnum(const u4* args,
    JValue* pResult)
{
	//Object         *CARObj = (Object*)args[0];
	StringObject   *nameObj;
	char           *CAREnumName;
	char           *CAREnumItemName;

	nameObj = (StringObject*)args[1];
	CAREnumName = dvmCreateCstrFromString(nameObj);
	nameObj = (StringObject*)args[2];
	CAREnumItemName = dvmCreateCstrFromString(nameObj);

    //pResult->i = dvmGetCAREnumInt(CARObj, CAREnumName, CAREnumItemName);

    free(CAREnumName);
    free(CAREnumItemName);
}
*/
/*
 * int i = CARConst(obj, jmethod);
 *//*
static void Dalvik_dalvik_CAR_CARCallbackFunc_CARConst(const u4* args,
    JValue* pResult)
{
	Object         *CARObj = (Object*)args[0];
	StringObject   *nameObj;
	char           *CARConstName;

	nameObj = (StringObject*)args[1];
	CARConstName = dvmCreateCstrFromString(nameObj);

    pResult->i = dvmGetCARConstInt(CARObj, CARConstName);

    free(CARConstName);
}
*/

//defined in jni.c
extern jclass FindClass(JNIEnv* env, const char* name);

/*
 * int i = GetiCallbackMethodInfoNoSignatire(classname, methodname);
 */
static void Dalvik_dalvik_CAR_CARCallbackFunc_GetiCallbackMethodInfoNoSignature(const u4* args,
    JValue* pResult)
{
	ClassObject  *clazz;
	char         *className;
	char         *methodName;
	Method       *method;
	StringObject *nameObj;
	bool          inVirtual;
	int           nameConflict;

	nameObj = (StringObject*)args[0];
	className = dvmCreateCstrFromString(nameObj);
	clazz = FindClass(NULL, className);

	nameObj = (StringObject*)args[1];
	methodName = dvmCreateCstrFromString(nameObj);
	method = dvmFindMethodInListByNameForCAR(clazz, methodName, &inVirtual, &nameConflict);

	//only static method needn't check its object
    if (dvmIsStaticMethod(method)) {
        RETURN_INT(0);
    }

	free(methodName);
	free(className);

	if (nameConflict == 1) {
	    RETURN_PTR(method);
    }

	LOGD("name Conflict, cannot locate the method %s", methodName);
    RETURN_INT(nameConflict);
}


/*
 * int i = GetiCallbackMethodInfoNoSignatire(methodname);
 */
static void Dalvik_dalvik_CAR_CARCallbackFunc_GetiCallbackMethodInfoInSameClass(const u4* args,
    JValue* pResult)
{
	ClassObject  *clazz;
	char         *methodName;
	Method       *method;
	StringObject *nameObj;
	bool          inVirtual;
	int           nameConflict;

    method = (Method*)getLastNthMethodFromStackFrames(dvmThreadSelf(), 2);

    if (method == NULL) {
        RETURN_INT(0);
        return;
    }

    clazz = method->clazz;

	nameObj = (StringObject*)args[0];
	methodName = dvmCreateCstrFromString(nameObj);

	method = dvmFindMethodInListByNameForCAR(clazz, methodName, &inVirtual, &nameConflict);
	LOGD("method %p", method);

	free(methodName);

	if (nameConflict == 1) {
	    RETURN_PTR(method);
    }

	LOGD("name Conflict, cannot locate the method %s", methodName);
    RETURN_INT(nameConflict);
}


/*
 * int i = GetiCallbackMethodInfoNoSignatire(obj, methodname);
 */
static void Dalvik_dalvik_CAR_CARCallbackFunc_GetiCallbackMethodInfoFromObj(const u4* args,
    JValue* pResult)
{
	ClassObject  *clazz;
	char         *methodName;
	Method       *method;
	StringObject *nameObj;
	bool          inVirtual;
	int           nameConflict;
	Object       *obj;

    obj = (Object*)args[0];
    clazz = obj->clazz;

	nameObj = (StringObject*)args[1];
	methodName = dvmCreateCstrFromString(nameObj);

	method = dvmFindMethodInListByNameForCAR(clazz, methodName, &inVirtual, &nameConflict);
	LOGD("method %p", method);

	free(methodName);

	if (nameConflict == 1) {
	    RETURN_PTR(method);
    }

	LOGD("name Conflict, cannot locate the method %s", methodName);
    RETURN_INT(nameConflict);
}

/*
 * int i = GetiCallbackMethodInfoNoSignatire(obj, methodname);
 */
static void Dalvik_dalvik_CAR_CARCallbackFunc_Object2Int(const u4* args,
    JValue* pResult)
{
	Object       *obj;

    obj = (Object*)args[0];
	RETURN_INT((int)obj);
}



const DalvikNativeMethod dvm_dalvik_CAR_CARCallbackFunc[] = {
    {"addCallbackHandler",        "(Ljava/lang/Object;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
        Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandler},
    {"addCallbackHandlerNoSignatire",        "(Ljava/lang/Object;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
        Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandlerNoSignature},
    {"addCallbackHandler",        "(Ljava/lang/Object;Ljava/lang/Object;)V",
        Dalvik_dalvik_CAR_CARCallbackFunc_addCallbackHandlerByMethodObject},
    {"removeCallbackHandler",     "(Ljava/lang/Object;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V",
        Dalvik_dalvik_CAR_CARCallbackFunc_removeCallbackHandler},
    {"removeAllCallbackHandler",  "(Ljava/lang/Object;)V",
        Dalvik_dalvik_CAR_CARCallbackFunc_removeAllCallbackHandler},
/*    {"CarEnumInt",  "(Ljava/lang/Object;Ljava/lang/String;)I",*/
/*        Dalvik_dalvik_CAR_CARCallbackFunc_CAREnum},*/
/*    {"CarConstInt",  "(Ljava/lang/Object;Ljava/lang/String;)I",*/
/*        Dalvik_dalvik_CAR_CARCallbackFunc_CARConst},*/
    {"GetJavaMethodNoSignature",        "(Ljava/lang/String;Ljava/lang/String;)I",
        Dalvik_dalvik_CAR_CARCallbackFunc_GetiCallbackMethodInfoNoSignature},
    {"GetJavaMethodInSameClass",       "(Ljava/lang/String;)I",
        Dalvik_dalvik_CAR_CARCallbackFunc_GetiCallbackMethodInfoInSameClass},
    {"GetJavaMethodNoSignature",        "(Ljava/lang/Object;Ljava/lang/String;)I",
        Dalvik_dalvik_CAR_CARCallbackFunc_GetiCallbackMethodInfoFromObj},
    {"Object2Int",        "(Ljava/lang/Object;)I",
        Dalvik_dalvik_CAR_CARCallbackFunc_Object2Int},
    {NULL, NULL, NULL},
};

