/**
  * ElastosBridgeApi.h
  */

#ifndef _DALVIK_ELASTOSBRIGEAPI
#define _DALVIK_ELASTOSBRIGEAPI


//for jdwp support
//a littlest address for java field struct
#define MAX_PSEUDO_FIELD_ID    0x800


enum {
    kTypeUnknown = 0,
	kTypePrimitive,
	kTypeString,
	kTypeStringBuffer,
	kTypeArrayOf,
	kTypeBufferOf,
	kTypeEnum,
	kTypeInterface,
};

enum {
    kTypeBoolean = 0,
    kTypeByte,
    kTypeChar,
    kTypeShort,
    kTypeInt,
	kTypeLong,
	kTypeFloat,
	kTypeDouble,
};

enum {
    carParamIOAttribute_In = 1,
    carParamIOAttribute_CallerAllocOut,
};

bool dvmSetCARClassInfo(/*const*/ ClassObject* clazz);
bool dvmSetCARInterfaceInfo(/*const*/ ClassObject* clazz);

/*
 * Create a PInterface for the Class, return as u4. For each CAR class this will do only when the class is load.
*/
u4 dvmCreateCARClassObject(const ClassObject* clazz, const Object *object);
u4 dvmCreateCARSingletonClassObject(const ClassObject *clazz, const Object *object);

void dvmReleaseCARClassObject(const u4 pObject);

/*
 * Get the IMethodInfo for the specify Method. For each method this will do only when the method is Resolved.
*/
int dvmSetCARMethodInfo(/*const*/ Method* meth);

bool dvmSetCARMemberHook(InstField* field);
bool dvmSetStaticCARMemberHook(StaticField* staticField);

void* dvmGetCARMethodAddr(Method* meth, u4 *pCARObject);

bool dvmRemoveAllCallbackHandler(Object* CARObject);

int dvmGetCARConstInt(Object *CARObject, char *CARConstName);
int dvmGetCAREnumInt(void* ptr, char* CAREnumItemName);
char* dvmGetCAREnumString(void* ptr, int value);
char* dvmReflectClassName(void* pObject);

void dvmReleaseCARMethodInfo(Method* meth);
void dvmReleaseCARClassInfo(ClassObject* clazz);

bool dvmElapiInitialize();
void dvmElapiUninitialize();

bool dvmCreateMsgLoopThread(void **ppAppletObj);
void dvmShutdownMsgLoopThread(void *pAppletObj);
void dvmAttachMsgLoopThread(void *pAppletObj);
void dvmDetachMsgLoopThread();

bool dvmAddCallbackHandler(Object* CARObject, char* callbackMethodName, ClassObject* clazz, Method* method);
bool dvmAddEventCallbackHandler(Object *object, u2 idxCARClass, u4 thisJavaObj, u4 u4CallbackInfo, Method *method);
bool dvmRemoveEventCallbackHandler(Object *object, u2 idxCARClass, u4 thisJavaObj, u4 u4CallbackInfo, Method *method);
bool dvmRemoveCallbackHandler(Object* CARObject, u4 *u4CallbackInfo, u4 handler);

void *dvmElapiNewStringBuf(int length);
void  dvmElapiFreeStringBuf(void *strBuf);
char *dvmElapiStringBufGetPayload(void *sb);
void *dvmElapiStringBufAppend(void *strBuf, char *str);

const char *dvmElapiNewString(const char *pch);

#define PRIMITIVE_CAR_ARRAY_NEW_DECLARE(_rtype, _cartype, _name)					\
void* dvmElapiArrayNew##_name(_rtype* payLoad, int size);

#define PRIMITIVE_CAR_ARRAY_GETPAYLOAD_DECLARE(_rtype, _cartype, _name)		        \
_rtype* dvmElapiArrayGetPayload##_name(void* array);

#define PRIMITIVE_CAR_ARRAY_GETLENGTH_DECLARE(_rtype, _cartype, _name)				\
int dvmElapiArrayGetLength##_name(void* array);

#define PRIMITIVE_CAR_ARRAY_FREE_DECLARE(_rtype, _cartype, _name)				    \
void dvmElapiArrayFree##_name(void* array);

#define PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(_rtype, _cartype, _name)            	\
	PRIMITIVE_CAR_ARRAY_NEW_DECLARE(_rtype, _cartype, _name)					   	\
	PRIMITIVE_CAR_ARRAY_GETPAYLOAD_DECLARE(_rtype, _cartype, _name)			   	    \
	PRIMITIVE_CAR_ARRAY_GETLENGTH_DECLARE(_rtype, _cartype, _name)				    \
	PRIMITIVE_CAR_ARRAY_FREE_DECLARE(_rtype, _cartype, _name)

PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(unsigned char, Boolean, Boolean);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(unsigned char, Byte, Byte);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(char, AChar, Char);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(short, Int16, Short);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(int, Int32, Int);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(long long, Int64, Long);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(float, Float, Float);
PRIMITIVE_CAR_ARRAY_FUNCTIONS_DECLARE(double, Double, Double);


//void* dvmElapiArrayNewDouble(double* payLoad, int size);
//double* dvmElapiArrayGetPayloadDouble(void* ArrayOfInt);
//int dvmElapiArrayGetLengthDouble(void* ArrayOfInt);

#define PRIMITIVE_CAR_BUFFER_NEW_DECLARE(_rtype, _cartype, _name)				    \
void* dvmElapiBufferNew##_name(_rtype* payLoad, int size);

#define PRIMITIVE_CAR_BUFFER_GETPAYLOAD_DECLARE(_rtype, _cartype, _name)		    \
_rtype* dvmElapiBufferGetPayload##_name(void* array);

#define PRIMITIVE_CAR_BUFFER_GETLENGTH_DECLARE(_rtype, _cartype, _name)				\
int dvmElapiBufferGetLength##_name(void* array);

#define PRIMITIVE_CAR_BUFFER_FREE_DECLARE(_rtype, _cartype, _name)				    \
void dvmElapiBufferFree##_name(void* array);

#define PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(_rtype, _cartype, _name)            	\
	PRIMITIVE_CAR_BUFFER_NEW_DECLARE(_rtype, _cartype, _name)					   	\
	PRIMITIVE_CAR_BUFFER_GETPAYLOAD_DECLARE(_rtype, _cartype, _name)			   	\
	PRIMITIVE_CAR_BUFFER_GETLENGTH_DECLARE(_rtype, _cartype, _name)				   	\
	PRIMITIVE_CAR_BUFFER_FREE_DECLARE(_rtype, _cartype, _name)

PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(unsigned char, Boolean, Boolean);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(unsigned char, Byte, Byte);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(char, AChar, Char);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(short, Int16, Short);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(int, Int32, Int);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(long long, Int64, Long);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(float, Float, Float);
PRIMITIVE_CAR_BUFFER_FUNCTIONS_DECLARE(double, Double, Double);

//void* dvmElapiBufferNewInt(int* payLoad, int size);
//int* dvmElapiBufferGetPayloadInt(void* ArrayOfInt);
//int dvmElapiBufferGetLengthInt(void* ArrayOfInt);

bool setCARObjectinJavaObject(Object* JavaObject, Method* method, void *CARObject);
void* ProbeInterface(u4 obj, u4 iid);
int ProbeIfxByName(ClassObject *clazz, const char *clzName, char *ifxName, bool isStatic);

void* dvmGetCARMethodinfoFunctionAddr(u4 *pCARObject, u4* pMethodInfo, u2 interfaceIndex);

//set CAR method info into java Method stored in directMethods and virtualMethods, for parameter conversion
int dvmSetCARmethodInfoForJavaMethod(ClassObject *clazz);

//for dvmCallMethodV, convert CAR object into Java object
Object *dvmCARObject2JavaObject(Thread *self, Object *object, const Method *method, u4 pCARObject, int idxParam);

//for dvmCallMethodV, convert Java object into CAR object
void *dvmJavaObject2CARObject(Thread *self, Object *object, const Method *method, u4 pJavaObject, int idxParam);

//for JDWP support
int dvmSetCARInspectObjMoreInfo(Object *JavaHostObj,Object *CARObjectDescObj, u4 *pCARObject, int idxCARObjInJavaObj);

//for cache CAR component in $BOOTCLASSPATH
bool dvmCacheCARModuleInBootclasspath(char *CARModule);

// check two interfaces, wether they are the same
bool dvmChkInterfaceWithInterfaceID(u4 theInterface, u4 piid);

void *dvmObjectSubstituteGeneric(Object* object, int inheritanceLevel, char *ElastosModuleName, char *ElastosClassName);

bool dvmIsCARClassGeneric(const ClassObject *clazz);

//Create a new instance of clazz.
Object *dvmClassNewInstance(ClassObject *clazz, Method *init, ...);

void dvmSetgDvmshouldCARWorking(bool b);


#endif
