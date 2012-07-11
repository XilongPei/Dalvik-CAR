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
 * java.lang.Runtime
 */
#include "Dalvik.h"
#include "native/InternalNativePriv.h"
#include <unistd.h>
#include <limits.h>

//#include "alloc/MarkSweep.h"
void dvmFreeObjectForcibly(Object *obj);

/*
 * public void gc()
 *
 * Initiate a gc.
 */
static void Dalvik_java_lang_Runtime_gc(const u4* args, JValue* pResult)
{
    UNUSED_PARAMETER(args);

    dvmCollectGarbage(false);
    RETURN_VOID();
}

/*
 * private static void nativeExit(int code, boolean isExit)
 *
 * Runtime.exit() calls this after doing shutdown processing.  Runtime.halt()
 * uses this as well.
 */
static void Dalvik_java_lang_Runtime_nativeExit(const u4* args,
    JValue* pResult)
{
    int status = args[0];
    bool isExit = (args[1] != 0);

    if (isExit && gDvm.exitHook != NULL) {
        dvmChangeStatus(NULL, THREAD_NATIVE);
        (*gDvm.exitHook)(status);     // not expected to return
        dvmChangeStatus(NULL, THREAD_RUNNING);
        LOGW("JNI exit hook returned\n");
    }
    LOGD("Calling exit(%d)\n", status);
#if defined(WITH_JIT) && defined(WITH_JIT_TUNING)
    dvmCompilerDumpStats();
#endif
    exit(status);
}

/*
 * static String nativeLoad(String filename, ClassLoader loader)
 *
 * Load the specified full path as a dynamic library filled with
 * JNI-compatible methods. Returns null on success, or a failure
 * message on failure.
 */
static void Dalvik_java_lang_Runtime_nativeLoad(const u4* args,
    JValue* pResult)
{
    StringObject* fileNameObj = (StringObject*) args[0];
    Object* classLoader = (Object*) args[1];
    char* fileName = NULL;
    StringObject* result = NULL;
    char* reason = NULL;
    bool success;

    assert(fileNameObj != NULL);
    fileName = dvmCreateCstrFromString(fileNameObj);

    success = dvmLoadNativeCode(fileName, classLoader, &reason);
    if (!success) {
        const char* msg = (reason != NULL) ? reason : "unknown failure";
        result = dvmCreateStringFromCstr(msg);
        dvmReleaseTrackedAlloc((Object*) result, NULL);
    }

    free(reason);
    free(fileName);
    RETURN_PTR(result);
}

/*
 * public void runFinalization(boolean forced)
 *
 * Requests that the VM runs finalizers for objects on the heap. If the
 * parameter forced is true, then the VM needs to ensure finalization.
 * Otherwise this only inspires the VM to make a best-effort attempt to
 * run finalizers before returning, but it's not guaranteed to actually
 * do anything.
 */
static void Dalvik_java_lang_Runtime_runFinalization(const u4* args,
    JValue* pResult)
{
    bool forced = (args[0] != 0);

    dvmWaitForHeapWorkerIdle();
    if (forced) {
        // TODO(Google) Need to explicitly implement this,
        //              although dvmWaitForHeapWorkerIdle()
        //              should usually provide the "forced"
        //              behavior already.
    }

    RETURN_VOID();
}

/*
 * public int availableProcessors()
 *
 * Returns the number of online processors, at least one.
 *
 */
static void Dalvik_java_lang_Runtime_availableProcessors(const u4* args,
    JValue* pResult)
{
    long result = 1;
#ifdef _SC_NPROCESSORS_ONLN
    result = sysconf(_SC_NPROCESSORS_ONLN);
    if (result > INT_MAX) {
        result = INT_MAX;
    } else if (result < 1 ) {
        result = 1;
    }
#endif
    RETURN_INT((int)result);
}
/*
 * public void maxMemory()
 *
 * Returns GC heap max memory in bytes.
 */
static void Dalvik_java_lang_Runtime_maxMemory(const u4* args, JValue* pResult)
{
    unsigned int result = gDvm.heapSizeMax;
    RETURN_LONG(result);
}

/*
 * public void totalMemory()
 *
 * Returns GC heap total memory in bytes.
 */
static void Dalvik_java_lang_Runtime_totalMemory(const u4* args,
    JValue* pResult)
{
    int result = dvmGetHeapDebugInfo(kVirtualHeapSize);
    RETURN_LONG(result);
}

/*
 * public void freeMemory()
 *
 * Returns GC heap free memory in bytes.
 */
static void Dalvik_java_lang_Runtime_freeMemory(const u4* args,
    JValue* pResult)
{
    int result = dvmGetHeapDebugInfo(kVirtualHeapSize)
                 - dvmGetHeapDebugInfo(kVirtualHeapAllocated);
    if (result < 0) {
        result = 0;
    }
    RETURN_LONG(result);
}

/*
 * public void freeObject()
 *
 * free an object, this function need superuser mode
 *
 * the references refer to this object SHOULD NOT use this object forever! or it will make error.
 *
 * class Foo {
 *    obj = new Class();
 *
 *    freeObject(obj);
 *    obj = null;
 * }
 */
static void Dalvik_java_lang_Runtime_freeObjectForcibly(const u4 *args, JValue *pResult)
{
    Object  *obj = (Object*)args[0];
    Thread  *self = dvmThreadSelf();

    if (obj == NULL)
        return;

    if (IS_CLASS_FLAG_SET(obj->clazz, CLASS_ISFINALIZABLE)) {
        Method *method = NULL;
        JValue  unused;

        method = obj->clazz->vtable[gDvm.voffJavaLangObject_finalize];
        assert(dvmCompareNameDescriptorAndMethod("finalize", "()V",
                        method) == 0);
        assert(method->clazz != gDvm.classJavaLangObject);

        dvmCallMethod(self, method, obj, &unused);

        /* Exceptions thrown during these calls interrupt
         * the method, but are otherwise ignored.
         */
        if (dvmCheckException(self)) {
#if DVM_SHOW_EXCEPTION >= 1
            LOGI("Uncaught exception thrown by finalizer (will be discarded):\n");
            dvmLogExceptionStackTrace();
#endif
            dvmClearException(self);
        }
    }

    dvmRemoveAllReference(obj);
    dvmFreeObjectForcibly(obj);
}



const DalvikNativeMethod dvm_java_lang_Runtime[] = {
    { "freeMemory",          "()J",
        Dalvik_java_lang_Runtime_freeMemory },
    { "gc",                 "()V",
        Dalvik_java_lang_Runtime_gc },
    { "availableProcessors", "()I",
        Dalvik_java_lang_Runtime_availableProcessors },
    { "maxMemory",          "()J",
        Dalvik_java_lang_Runtime_maxMemory },
    { "nativeExit",         "(IZ)V",
        Dalvik_java_lang_Runtime_nativeExit },
    { "nativeLoad",         "(Ljava/lang/String;Ljava/lang/ClassLoader;)Ljava/lang/String;",
        Dalvik_java_lang_Runtime_nativeLoad },
    { "runFinalization",    "(Z)V",
        Dalvik_java_lang_Runtime_runFinalization },
    { "totalMemory",          "()J",
        Dalvik_java_lang_Runtime_totalMemory },
    { "freeObjectForcibly",         "(Ljava/lang/Object;)V",
        Dalvik_java_lang_Runtime_freeObjectForcibly },
    { NULL, NULL, NULL },
};
