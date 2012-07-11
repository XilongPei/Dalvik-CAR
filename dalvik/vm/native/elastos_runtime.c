#include "Dalvik.h"
#include "native/InternalNativePriv.h"
#include "ElastosBridgeApi.h"

static void elastos_runtime_ElastosGeneric_substitutes(const u4* args,
    JValue* pResult)
{
	LOGD("elastos_runtime_ElastosGeneric_substitutes");
	Object *CARObj = (Object*)args[0];
	int     inheritanceLevel = (int)args[1];
	void   *p;
	//u4 CARObj = *(u4 *)(((char *)obj)+obj->clazz->objectSize);

	StringObject* nameObj;
	nameObj = (StringObject*)args[2];
	char  *ElastosModuleName = dvmCreateCstrFromString(nameObj);

	nameObj = (StringObject*)args[2];
	char  *ElastosClassName = dvmCreateCstrFromString(nameObj);

	p = dvmObjectSubstituteGeneric(CARObj, inheritanceLevel, ElastosModuleName, ElastosClassName);

	free(ElastosModuleName);
	free(ElastosClassName);

	RETURN_INT((int)p);
}


const DalvikNativeMethod elastos_runtime_ElastosGeneric_functions[] = {
    {"substitutes",        "(Ljava/lang/Object;ILjava/lang/String;Ljava/lang/String;)I",
        elastos_runtime_ElastosGeneric_substitutes},
    {NULL, NULL, NULL},
};

