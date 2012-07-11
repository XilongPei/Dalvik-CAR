/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Garbage-collecting memory allocator.
 */
#include "Dalvik.h"
#include "alloc/Heap.h"
#include "alloc/HeapInternal.h"
#include "alloc/HeapSource.h"
#include "ElastosBridgeApi.h"

#if WITH_HPROF && WITH_HPROF_STACK
#include "hprof/Hprof.h"
#endif

//#define  __SERIOUSLY_REMOVE_REF_TABLE__
/*
 * Initialize the GC universe.
 *
 * We're currently using a memory-mapped arena to keep things off of the
 * main heap.  This needs to be replaced with something real.
 */
bool dvmGcStartup(void)
{
    dvmInitMutex(&gDvm.gcHeapLock);

    return dvmHeapStartup();
}

/*
 * Post-zygote heap initialization, including starting
 * the HeapWorker thread.
 */
bool dvmGcStartupAfterZygote(void)
{
    if (!dvmHeapWorkerStartup()) {
        return false;
    }
    return dvmHeapStartupAfterZygote();
}

/*
 * Shutdown the threads internal to the garbage collector.
 */
void dvmGcThreadShutdown(void)
{
    dvmHeapWorkerShutdown();
    dvmHeapThreadShutdown();
}

/*
 * Shut the GC down.
 */
void dvmGcShutdown(void)
{
    //TODO: grab and destroy the lock
    dvmHeapShutdown();
}

/*
 * Do any last-minute preparation before we call fork() for the first time.
 */
bool dvmGcPreZygoteFork(void)
{
    return dvmHeapSourceStartupBeforeFork();
}

/*
 * Create a "stock instance" of an exception class.
 */
static Object* createStockException(const char* descriptor, const char* msg)
{
    Thread* self = dvmThreadSelf();
    StringObject* msgStr = NULL;
    ClassObject* clazz;
    Method* init;
    Object* obj;

    /* find class, initialize if necessary */
    clazz = dvmFindSystemClass(descriptor);
    if (clazz == NULL) {
        LOGE("Unable to find %s\n", descriptor);
        return NULL;
    }

    init = dvmFindDirectMethodByDescriptor(clazz, "<init>",
            "(Ljava/lang/String;)V");
    if (init == NULL) {
        LOGE("Unable to find String-arg constructor for %s\n", descriptor);
        return NULL;
    }

    obj = dvmAllocObject(clazz, ALLOC_DEFAULT);
    if (obj == NULL)
        return NULL;

    if (msg == NULL) {
        msgStr = NULL;
    } else {
        msgStr = dvmCreateStringFromCstr(msg);
        if (msgStr == NULL) {
            LOGW("Could not allocate message string \"%s\"\n", msg);
            dvmReleaseTrackedAlloc(obj, self);
            return NULL;
        }
    }

    JValue unused;
    dvmCallMethod(self, init, obj, &unused, msgStr);
    if (dvmCheckException(self)) {
        dvmReleaseTrackedAlloc((Object*) msgStr, self);
        dvmReleaseTrackedAlloc(obj, self);
        return NULL;
    }

    dvmReleaseTrackedAlloc((Object*) msgStr, self);     // okay if msgStr NULL
    return obj;
}

/*
 * Create some "stock" exceptions.  These can be thrown when the system is
 * too screwed up to allocate and initialize anything, or when we don't
 * need a meaningful stack trace.
 *
 * We can't do this during the initial startup because we need to execute
 * the constructors.
 */
bool dvmCreateStockExceptions(void)
{
    /*
     * Pre-allocate some throwables.  These need to be explicitly added
     * to the GC's root set (see dvmHeapMarkRootSet()).
     */
    gDvm.outOfMemoryObj = createStockException("Ljava/lang/OutOfMemoryError;",
        "[memory exhausted]");
    dvmReleaseTrackedAlloc(gDvm.outOfMemoryObj, NULL);
    gDvm.internalErrorObj = createStockException("Ljava/lang/InternalError;",
        "[pre-allocated]");
    dvmReleaseTrackedAlloc(gDvm.internalErrorObj, NULL);
    gDvm.noClassDefFoundErrorObj =
        createStockException("Ljava/lang/NoClassDefFoundError;",
            "[generic]");
    dvmReleaseTrackedAlloc(gDvm.noClassDefFoundErrorObj, NULL);

    if (gDvm.outOfMemoryObj == NULL || gDvm.internalErrorObj == NULL ||
        gDvm.noClassDefFoundErrorObj == NULL)
    {
        LOGW("Unable to create stock exceptions\n");
        return false;
    }

    return true;
}


/*
 * Create an instance of the specified class.
 *
 * Returns NULL and throws an exception on failure.
 */
Object* dvmAllocObject(ClassObject* clazz, int flags)
{
    Object* newObj;
    int          layerCount;
    ClassObject* clz;
    ClassObject* clz2;

    assert(dvmIsClassInitialized(clazz) || dvmIsClassInitializing(clazz));

    if (IS_CLASS_FLAG_SET(clazz, CLASS_ISFINALIZABLE)) {
        flags |= ALLOC_FINALIZABLE;
    }

    for (clz = clazz;  clz->super != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS|CLASS_CAR_INTERFACE))
            break;
    }
    //Elastos: when we create a java object, we check the class is or is not a CAR class.
	//if this is a CAR class we will create a CAR object, and put the object in the java object.
    if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
    	  /*the object relation diagram
                      NULL(java.lang.Object)
                      /
                     /
                   Clazz ->CARObject
                   /
                  /
                Clazz ->CARObject
                /
               /
           Clazz ->CARObject
        */
        for (layerCount = 1, clz2 = clz->super;  clz2->super != NULL;  clz2 = clz2->super) {
            if (IS_CLASS_FLAG_SET(clz2, CLASS_CAR_CLASS))
                layerCount++;
        }

    	newObj = dvmMalloc(clazz->objectSize + sizeof(u4)*layerCount, flags);

    	for (layerCount = 0, clz2 = clz;  clz2->super != NULL;  clz2 = clz2->super) {
            //create the CAR object
            if (IS_CLASS_FLAG_SET(clz2, CLASS_CAR_CLASS)) {

                /* NOTICE:
                 *
                 * in Dalvik, an Object won't be moved after it is allocated,
                 * if its GC algorithm is come from HeapSource
                 */
		        u4 pCARObject = dvmCreateCARClassObject(clazz, newObj);

		        if (pCARObject == (u4)NULL && !dvmIsCARClassGeneric(clz2)) {
			        LOGE("create a CAR object for a CAR class failed");

                    for (layerCount--;  layerCount >= 0;  layerCount--) {
                        pCARObject = *(u4 *)(((char *)newObj) + clazz->objectSize + sizeof(u4)*layerCount);
                        dvmReleaseCARClassObject(pCARObject);
                    }

                    dvmFreeObjectForcibly(newObj);
                    return  NULL;
                }

		    	*(u4 *)(((char *)newObj) + clazz->objectSize + sizeof(u4)*layerCount) = pCARObject;
		   	 	layerCount++;
		    }
        }
    }
    else if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_INTERFACE)) {
    	newObj = dvmMalloc(clazz->objectSize + sizeof(u4), flags);
    } else {
        /* allocate on GC heap; memory is zeroed out */
        newObj = dvmMalloc(clazz->objectSize, flags);
    }

    if (newObj != NULL) {
        DVM_OBJECT_INIT(newObj, clazz);
#if WITH_HPROF && WITH_HPROF_STACK
        hprofFillInStackTrace(newObj);
#endif
        dvmTrackAllocation(clazz, clazz->objectSize);
    }

    return newObj;
}

/*
 * Create a copy of an object, for Object.clone().
 *
 * We use the size actually allocated, rather than obj->clazz->objectSize,
 * because the latter doesn't work for array objects.
 */
Object* dvmCloneObject(Object* obj)
{
    Object* copy;
    int size;
    int flags;
    ClassObject* clz;

    assert(dvmIsValidObject(obj));

    /* Class.java shouldn't let us get here (java.lang.Class is final
     * and does not implement Clonable), but make extra sure.
     * A memcpy() clone will wreak havoc on a ClassObject's "innards".
     */
    assert(obj->clazz != gDvm.classJavaLangClass);

    if (IS_CLASS_FLAG_SET(obj->clazz, CLASS_ISFINALIZABLE))
        flags = ALLOC_DEFAULT | ALLOC_FINALIZABLE;
    else
        flags = ALLOC_DEFAULT;

    if (IS_CLASS_FLAG_SET(obj->clazz, CLASS_ISARRAY)) {
        size = dvmArrayObjectSize((ArrayObject *)obj);
    } else {
        size = obj->clazz->objectSize;
    }

    for (clz = obj->clazz;  clz->super != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS|CLASS_CAR_INTERFACE))
            size += sizeof(u4);
    }

    copy = dvmMalloc(size, flags);
    if (copy == NULL)
        return NULL;
#if WITH_HPROF && WITH_HPROF_STACK
    hprofFillInStackTrace(copy);
    dvmTrackAllocation(obj->clazz, size);
#endif

    memcpy(copy, obj, size);
    DVM_LOCK_INIT(&copy->lock);
    dvmWriteBarrierObject(copy);

    return copy;
}


/*
 * Track an object that was allocated internally and isn't yet part of the
 * VM root set.
 *
 * We could do this per-thread or globally.  If it's global we don't have
 * to do the thread lookup but we do have to synchronize access to the list.
 *
 * NOTE: "obj" is not a fully-formed object; in particular, obj->clazz will
 * usually be NULL since we're being called from dvmMalloc().
 */
void dvmAddTrackedAlloc(Object* obj, Thread* self)
{
    if (self == NULL)
        self = dvmThreadSelf();

    assert(self != NULL);
    if (!dvmAddToReferenceTable(&self->internalLocalRefTable, obj)) {
        LOGE("threadid=%d: unable to add %p to internal ref table\n",
            self->threadId, obj);
        dvmDumpThread(self, false);
        dvmAbort();
    }
}



/*
 * Stop tracking an object.
 *
 * We allow attempts to delete NULL "obj" so that callers don't have to wrap
 * calls with "if != NULL".
 */
void dvmReleaseTrackedAlloc(Object* obj, Thread* self)
{
    if (obj == NULL)
        return;

    if (self == NULL)
        self = dvmThreadSelf();
    assert(self != NULL);

    if (!dvmRemoveFromReferenceTable(&self->internalLocalRefTable,
            self->internalLocalRefTable.table, obj))
    {
        LOGE("threadid=%d: failed to remove %p from internal ref table\n",
            self->threadId, obj);
        dvmAbort();
    }
}



//defined in jni.c
void deleteGlobalReference(jobject obj);

/*
 * Release CAR objects compounded in Java object.
 */
void dvmReleaseCompoundedCARObj(void *object)
{
    ClassObject *clz;
    u4           pCARObject;
    int          layerCount = 0;
    Object      *obj = (Object*)object;

    if (obj == NULL)
        return;

    clz = obj->clazz;
    if (clz == gDvm.classJavaLangClass)
        return;

    for (;  clz->super != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS)) {
	        pCARObject = *(u4 *)(((char *)obj) + obj->clazz->objectSize + sizeof(u4)*layerCount);
	        if (pCARObject == (u4)NULL) {
	            if (!dvmIsCARClassGeneric(clz)) {
		            LOGE("CAR object for a CAR class if NULL");
                    dvmAbort();
                }
            } else {
                //release the CAR object
                dvmReleaseCARClassObject(pCARObject);
            }
            layerCount++;
        } else if (IS_CLASS_FLAG_SET(obj->clazz, CLASS_CAR_INTERFACE)) {
            pCARObject = *(u4 *)(((char *)obj) + obj->clazz->objectSize + sizeof(u4));
            if (pCARObject != (u4)NULL) {
                //release the CAR object
                dvmReleaseCARClassObject(pCARObject);
            }
            break;
        }
    }

    clz = obj->clazz;
    if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_NEEDCLEAN)) {

        int        i, j;
        bool       tf;
    	Method    *method;
    	bool       inVirtual;
    	int        nameConflict;
    	char       buf[256];
        InstField *pField;
        u4        *CallbacksObj;
        u4        *CallbackMethods;
        u4        *thisObjs;
        int        icount;
    	Object    *objTmp;

        for (i = 0;  i < clz->ifieldRefCount;  i++)
        {
            pField = &clz->ifields[i];

            /*
            if (strcmp(pField->field.signature, "Ljava/lang/Delegates;") == 0 || \
                strcmp(pField->field.signature, "Ljava/lang/Callbacks;") == 0)
             */
            if (pField->interfaceIndexOfSetter == 0xFFFF || pField->interfaceIndexOfSetter == 0xFFFE)
            {
        		CallbacksObj = (u4*)*(u4*)((u1*)obj+pField->byteOffset);

                if (CallbacksObj != NULL) {
            	    CallbackMethods = (u4*)(((ArrayObject*)dvmGetFieldObject((const Object*)CallbacksObj,
            	                                    gDvm.offJavaLangDelegate_value))->contents);
            	    thisObjs = (u4*)(((ArrayObject*)dvmGetFieldObject((const Object*)CallbacksObj,
            	                                    gDvm.offJavaLangDelegate_thisObj))->contents);
            	    icount = dvmGetFieldInt((const Object*)CallbacksObj, gDvm.offJavaLangDelegate_count);

                    for (j = 0;  j < icount;  j++)
                    {
                        objTmp = (Object*)(thisObjs[i]);

                        if (CallbackMethods[i] == 0) {
                            if (pField->interfaceIndexOfSetter == 0xFFFF)
                                strcat(strcat(strcpy(buf, "Do"), pField->field.name), "Delegate");
                            else /* pField->interfaceIndexOfSetter == 0xFFFE) */
                                strcat(strcat(strcpy(buf, "On"), pField->field.name), "Callback");

                            if (objTmp != 0) {
                        	    method = dvmFindMethodInListByNameForCAR(clz, buf, &inVirtual, &nameConflict);
                        	} else {
                        	    continue;
                        	}

                        	LOGD("method %p", method);
                        	/*
                             * when nameconflict>1 ,method is the first matched value
                	         * if (nameConflict != 1) {
                	         *    tf = false;
                             * } else {
                             */
                        	    tf = dvmRemoveEventCallbackHandler(obj, pField->interfaceIndexOfGetter, (u4)objTmp,
                        	                                        pField->setter, method);
                        	//}
                        } else {
                            if (objTmp != 0) {
                    	        tf = dvmRemoveEventCallbackHandler(obj, pField->interfaceIndexOfGetter, (u4)objTmp,
                    	                                        pField->setter, (Method*)CallbackMethods[i]);
                            } else {
                        	    continue;
                        	}
                        }
                	    if (!tf) {
                	        LOGD("error");
                	    }
                	} //for(j)

                    deleteGlobalReference((Object*)CallbacksObj);
                }
            } //if()
        } //for(i)
    } //if(CLASS_CAR_NEEDCLEAN)
}


/*
 * Explicitly initiate garbage collection.
 */
void dvmCollectGarbage(bool collectSoftReferences)
{
    dvmLockHeap();
    while (gDvm.gcHeap->gcRunning) {
        dvmWaitForConcurrentGcToComplete();
    }
    dvmCollectGarbageInternal(collectSoftReferences, GC_EXPLICIT);
    dvmUnlockHeap();
}

typedef struct {
    const ClassObject *clazz;
    size_t count;
} CountContext;

static void countInstancesOfClassCallback(void *ptr, void *arg)
{
    CountContext *ctx = arg;
    const Object *obj = ptr;

    assert(ctx != NULL);
    if (obj->clazz == ctx->clazz) {
        ctx->count += 1;
    }
}

size_t dvmCountInstancesOfClass(const ClassObject *clazz)
{
    CountContext ctx = { clazz, 0 };
    HeapBitmap *bitmap = dvmHeapSourceGetLiveBits();
    dvmLockHeap();
    dvmHeapBitmapWalk(bitmap, countInstancesOfClassCallback, &ctx);
    dvmUnlockHeap();
    return ctx.count;
}

static void countAssignableInstancesOfClassCallback(void *ptr, void *arg)
{
    CountContext *ctx = arg;
    const Object *obj = ptr;

    assert(ctx != NULL);
    if (dvmInstanceof(obj->clazz, ctx->clazz)) {
        ctx->count += 1;
    }
}

size_t dvmCountAssignableInstancesOfClass(const ClassObject *clazz)
{
    CountContext ctx = { clazz, 0 };
    HeapBitmap *bitmap = dvmHeapSourceGetLiveBits();
    dvmLockHeap();
    dvmHeapBitmapWalk(bitmap, countAssignableInstancesOfClassCallback, &ctx);
    dvmUnlockHeap();
    return ctx.count;
}
