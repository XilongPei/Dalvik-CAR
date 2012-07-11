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
 * Native method resolution.
 *
 * Currently the "Dalvik native" methods are only used for internal methods.
 * Someday we may want to export the interface as a faster but riskier
 * alternative to JNI.
 */
#include "Dalvik.h"

#include "ElastosBridgeApi.h"

#include <stdlib.h>
#include <dlfcn.h>

static void freeSharedLibEntry(void* ptr);
static void* lookupSharedLibMethod(const Method* method);
static int hashcmpSharedLib(const void* ventry, const void* vnewEntry);
static int hashcmpCARClass(const void* ventry, const void* vnewEntry);

/*
 * Initialize the native code loader.
 */
bool dvmNativeStartup(void)
{
    gDvm.nativeLibs = dvmHashTableCreate(4, freeSharedLibEntry);
    if (gDvm.nativeLibs == NULL)
        return false;

    gDvm.globalCARClass = dvmHashTableCreate(4, NULL);
    if (gDvm.globalCARClass == NULL)
        return false;

    return true;
}

/*
 * Free up our tables.
 */
void dvmNativeShutdown(void)
{
    dvmHashTableFree(gDvm.nativeLibs);
    gDvm.nativeLibs = NULL;

    dvmHashTableFree(gDvm.globalCARClass);
    gDvm.globalCARClass = NULL;
}


/*
 * Resolve a native method and invoke it.
 *
 * This is executed as if it were a native bridge or function.  If the
 * resolution succeeds, method->insns is replaced, and we don't go through
 * here again unless the method is unregistered.
 *
 * Initializes method's class if necessary.
 *
 * An exception is thrown on resolution failure.
 *
 * (This should not be taking "const Method*", because it modifies the
 * structure, but the declaration needs to match the DalvikBridgeFunc
 * type definition.)
 */
void dvmResolveNativeMethod(const u4* args, JValue* pResult,
    const Method* method, Thread* self)
{
    u4          *pCARObject;
    ClassObject *clazz = method->clazz;
	void        *func;
	int          i;

    /*
     * If this is a static method, it could be called before the class
     * has been initialized.
     */
    if (dvmIsStaticMethod(method)) {
        if (!dvmIsClassInitialized(clazz) && !dvmInitClass(clazz)) {
            assert(dvmCheckException(dvmThreadSelf()));
            return;
        }
    } else {
        assert(dvmIsClassInitialized(clazz) ||
               dvmIsClassInitializing(clazz));
    }

	if (IS_CLASS_FLAG_SET(clazz, CLASS_CAR_CLASS|CLASS_CAR_INTERFACE)) {
	    /*
	       there are 2 type of c/c++ CAR functions to correspond to the dalvik inside function:
	       (1)
	       Foo(int para1, int para2, int paraN, void *env, void *clazz);
	           //p1 -> JNIEnv* env, p2 -> jclass clazz
	       (2)
	       Foo(int para1, int para2, int paraN);

	       the type 1 will be called like CAR specialied JNI function
	       the type 2 will be called like inline native function

	       the last 2 parameter's information come from CAR reflection
	    */

	    //jni.c
	    //dvmCallCarJNIMethod(const u4* args, JValue* pResult, const Method* method,Thread* self, void *thisCAR);

	    //get native function ptr from thisCAR, thisCAR is a normal CAR object created by CAR reflection, NewByFriend()

	    /* resolution always gets the same answer, so no race here */
#if 0
        char* desc = dexProtoCopyMethodDescriptor(&method->prototype);
        LOGD("+++ resolved CAR native %s.%s %s, invoking\n",
            clazz->descriptor, method->name, desc);
        free(desc);
#endif

        i = dvmSetCARMethodInfo((Method*)method);
		if (i >= 0) {
		    char buf[512];

			LOGW("Set MethodInfo failed %s %0x", method->name, i);
			if (method->pCARMethodInfo == (void*)1)
			    goto A_NORMAL_NATIVE_METHOD;

		    snprintf(buf, sizeof(buf), "parameter 0x%08x not match", i);
		    dvmThrowException("Ljava/lang/UnsatisfiedLinkError;", buf);
			return;
		}

		if (dvmIsStaticMethod(method)) {

		    if (method->clazz->pStaticClassInfo == (u4)NULL) {
    		    char buf[512];

                char* desc = dexProtoCopyMethodDescriptor(&method->prototype);
                LOGD("+++ resolved static CAR native %s.%s %s, invoking\n",
                    clazz->descriptor, method->name, desc);
                free(desc);

    		    snprintf(buf, sizeof(buf), "CAR-native-method can't be declared as 'static': %s.%s\n", method->clazz->descriptor, method->name);
    		    dvmThrowException("Ljava/lang/NoSuchMethodError;", buf);
    		    return;
    		}

            // dvmCallCARJNIMethod() will create this singleton object, but I have to create too, for
            // I want to calculate the function pointer of this method.
            // pCARObject = (u4*)dvmCreateCARSingletonClassObject(method->clazz, NULL);

            pCARObject = (u4*)method->clazz->pCARSingletonObject;

        } else {
    		Object *object = (Object*)args[0];
    		int     i;
    		ClassObject *clz;

    		//find my CAR object
    		for (i = 0, clz = object->clazz;  clz != method->clazz && clz != NULL;  clz = clz->super) {
           		if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS))
            	    i++;
        	}
		    pCARObject = (u4*)(*(u4*)(((char*)object)+clazz->objectSize + sizeof(u4)*i));
        }

        if (pCARObject != NULL)
		    func = (void*)dvmGetCARMethodAddr((Method*)method, pCARObject);
		else
		    func = NULL;

		if(func != NULL) {
		    if (dvmIsSynchronizedMethod(method))
		        dvmSetNativeFunc((Method*)method, dvmCallSynchronizedCARJNIMethod, (const u2*)func);
		    else
		        dvmSetNativeFunc((Method*)method, dvmCallCARJNIMethod, (const u2*)func);

		    dvmCallCARJNIMethod(args, pResult, method, self);
		    return;
		} else {
		    char buf[512];

            char* desc = dexProtoCopyMethodDescriptor(&method->prototype);
            LOGD("+++ resolved CAR native %s.%s %s, invoking\n",
                clazz->descriptor, method->name, desc);
            free(desc);

		    snprintf(buf, sizeof(buf), "CAR method locating error on %s.%s\n", method->clazz->descriptor, method->name);
		    dvmThrowException("Ljava/lang/NoSuchMethodError;", buf);
		    return;
		}
	}

A_NORMAL_NATIVE_METHOD:

    /* start with our internal-native methods */
    func = dvmLookupInternalNativeMethod(method);
    if (func != NULL) {
        /* resolution always gets the same answer, so no race here */
        IF_LOGVV() {
            char* desc = dexProtoCopyMethodDescriptor(&method->prototype);
            LOGVV("+++ resolved native %s.%s %s, invoking\n",
                clazz->descriptor, method->name, desc);
            free(desc);
        }
        if (dvmIsSynchronizedMethod(method)) {
            LOGE("ERROR: internal-native can't be declared 'synchronized'\n");
            LOGE("Failing on %s.%s\n", method->clazz->descriptor, method->name);
            dvmAbort();     // harsh, but this is VM-internal problem
        }
        DalvikBridgeFunc dfunc = (DalvikBridgeFunc) func;
        dvmSetNativeFunc((Method*) method, dfunc, NULL);
        dfunc(args, pResult, method, self);
        return;
    }

    /* now scan any DLLs we have loaded for JNI signatures */
    func = lookupSharedLibMethod(method);
    if (func != NULL) {
        /* found it, point it at the JNI bridge and then call it */
        dvmUseJNIBridge((Method*) method, func);
        (*method->nativeFunc)(args, pResult, method, self);
        return;
    }

    IF_LOGW() {
        char* desc = dexProtoCopyMethodDescriptor(&method->prototype);
        LOGW("No implementation found for native %s.%s %s\n",
            clazz->descriptor, method->name, desc);
        free(desc);
    }

    //to avoid the method->pCARMethodInfo==1
    ((Method*)method)->pCARMethodInfo = NULL;

    //in Java&CAR this exception should be "Ljava/lang/NoSuchMethodError;",
    //but that will make the java programer confused
    dvmThrowException("Ljava/lang/UnsatisfiedLinkError;", method->name);
}


/*
 * ===========================================================================
 *      Native shared library support
 * ===========================================================================
 */

// TODO? if a ClassLoader is unloaded, we need to unload all DLLs that
// are associated with it.  (Or not -- can't determine if native code
// is still using parts of it.)

typedef enum OnLoadState {
    kOnLoadPending = 0,     /* initial state, must be zero */
    kOnLoadFailed,
    kOnLoadOkay,
} OnLoadState;

typedef enum HashedLibType {
    kpCARModuleInfo = 1,     /* CAR module */
    kpDllHandle = 2,      /* DLL open by dlopen() */
} HashedLibType;

/*
 * We add one of these to the hash table for every library we load.  The
 * hash is on the "pathName" field.
 */
typedef struct SharedLib {
    char*       pathName;           /* absolute path to library */
    void*       handle;             /* from dlopen */
    Object*     classLoader;        /* ClassLoader we are associated with */

    pthread_mutex_t onLoadLock;     /* guards remaining items */
    pthread_cond_t  onLoadCond;     /* wait for JNI_OnLoad in other thread */
    u4              onLoadThreadId; /* recursive invocation guard */
    OnLoadState     onLoadResult;   /* result of earlier JNI_OnLoad */

    HashedLibType   libType;
    int             refCount;

} SharedLib;

/*
 * (This is a dvmHashTableLookup callback.)
 *
 * Find an entry that matches the string.
 */
static int hashcmpNameStr(const void* ventry, const void* vname)
{
    const SharedLib* pLib = (const SharedLib*) ventry;
    const char* name = (const char*) vname;

    return strcmp(pLib->pathName, name);
}

/*
 * (This is a dvmHashTableLookup callback.)
 *
 * Find an entry that matches the new entry.
 *
 * We don't compare the class loader here, because you're not allowed to
 * have the same shared library associated with more than one CL.
 */
static int hashcmpSharedLib(const void* ventry, const void* vnewEntry)
{
    const SharedLib* pLib = (const SharedLib*) ventry;
    const SharedLib* pNewLib = (const SharedLib*) vnewEntry;

    LOGD("--- comparing %p '%s' %p '%s'\n",
        pLib, pLib->pathName, pNewLib, pNewLib->pathName);
    return strcmp(pLib->pathName, pNewLib->pathName);
}

/*
 * Check to see if an entry with the same pathname already exists.
 */
static SharedLib* findSharedLibEntry(const char* pathName)
{
    u4 hash = dvmComputeUtf8Hash(pathName);
    void* ent;

    ent = dvmHashTableLookup(gDvm.nativeLibs, hash, (void*)pathName,
                hashcmpNameStr, false);
    return ent;
}

/*
 * Add the new entry to the table.
 *
 * Returns the table entry, which will not be the same as "pLib" if the
 * entry already exists.
 */
static SharedLib* addSharedLibEntry(SharedLib* pLib)
{
    u4 hash = dvmComputeUtf8Hash(pLib->pathName);

    /*
     * Do the lookup with the "add" flag set.  If we add it, we will get
     * our own pointer back.  If somebody beat us to the punch, we'll get
     * their pointer back instead.
     */
    return dvmHashTableLookup(gDvm.nativeLibs, hash, pLib, hashcmpSharedLib,
                true);
}

/*
 * Free up an entry.  (This is a dvmHashTableFree callback.)
 */
static void freeSharedLibEntry(void* ptr)
{
    SharedLib* pLib = (SharedLib*) ptr;

    if (pLib->libType == kpDllHandle) {
        /*
         * Calling dlclose() here is somewhat dangerous, because it's possible
         * that a thread outside the VM is still accessing the code we loaded.
         */
        if (false)
            dlclose(pLib->handle);

        if( pLib->pathName != NULL )
            free(pLib->pathName);
        free(pLib);
    } else if (pLib->libType == kpCARModuleInfo) {

        if (false)
            dvmReleaseCARClassObject((u4)pLib->handle);

        if( pLib->pathName != NULL )
            free(pLib->pathName);
        free(pLib);
    }
}

/*
 * Convert library name to system-dependent form, e.g. "jpeg" becomes
 * "libjpeg.so".
 *
 * (Should we have this take buffer+len and avoid the alloc?  It gets
 * called very rarely.)
 */
char* dvmCreateSystemLibraryName(char* libName)
{
    char buf[256];
    int len;

    len = snprintf(buf, sizeof(buf), OS_SHARED_LIB_FORMAT_STR, libName);
    if (len >= (int) sizeof(buf))
        return NULL;
    else
        return strdup(buf);
}

/*
 * Check the result of an earlier call to JNI_OnLoad on this library.  If
 * the call has not yet finished in another thread, wait for it.
 */
static bool checkOnLoadResult(SharedLib* pEntry)
{
    Thread* self = dvmThreadSelf();
    if (pEntry->onLoadThreadId == self->threadId) {
        /*
         * Check this so we don't end up waiting for ourselves.  We need
         * to return "true" so the caller can continue.
         */
        LOGI("threadid=%d: recursive native library load attempt (%s)\n",
            self->threadId, pEntry->pathName);
        return true;
    }

    LOGV("+++ retrieving %s OnLoad status\n", pEntry->pathName);
    bool result;

    dvmLockMutex(&pEntry->onLoadLock);
    while (pEntry->onLoadResult == kOnLoadPending) {
        LOGD("threadid=%d: waiting for %s OnLoad status\n",
            self->threadId, pEntry->pathName);
        ThreadStatus oldStatus = dvmChangeStatus(self, THREAD_VMWAIT);
        pthread_cond_wait(&pEntry->onLoadCond, &pEntry->onLoadLock);
        dvmChangeStatus(self, oldStatus);
    }
    if (pEntry->onLoadResult == kOnLoadOkay) {
        LOGV("+++ earlier OnLoad(%s) okay\n", pEntry->pathName);
        result = true;
    } else {
        LOGV("+++ earlier OnLoad(%s) failed\n", pEntry->pathName);
        result = false;
    }
    dvmUnlockMutex(&pEntry->onLoadLock);
    return result;
}

typedef int (*OnLoadFunc)(JavaVM*, void*);

/*
 * Load native code from the specified absolute pathname.  Per the spec,
 * if we've already loaded a library with the specified pathname, we
 * return without doing anything.
 *
 * TODO? for better results we should absolutify the pathname.  For fully
 * correct results we should stat to get the inode and compare that.  The
 * existing implementation is fine so long as everybody is using
 * System.loadLibrary.
 *
 * The library will be associated with the specified class loader.  The JNI
 * spec says we can't load the same library into more than one class loader.
 *
 * Returns "true" on success. On failure, sets *detail to a
 * human-readable description of the error or NULL if no detail is
 * available; ownership of the string is transferred to the caller.
 */
bool dvmLoadNativeCode(const char* pathName, Object* classLoader,
        char** detail)
{
    SharedLib* pEntry;
    void* handle;
    bool verbose;

    /* reduce noise by not chattering about system libraries */
    verbose = !!strncmp(pathName, "/system", sizeof("/system")-1);
    verbose = verbose && !!strncmp(pathName, "/vendor", sizeof("/vendor")-1);

    if (verbose)
        LOGD("Trying to load lib %s %p\n", pathName, classLoader);

    *detail = NULL;

    /*
     * See if we've already loaded it.  If we have, and the class loader
     * matches, return successfully without doing anything.
     */
    pEntry = findSharedLibEntry(pathName);
    if (pEntry != NULL) {
        if (pEntry->classLoader != classLoader) {
            LOGW("Shared lib '%s' already opened by CL %p; can't open in %p\n",
                pathName, pEntry->classLoader, classLoader);
            return false;
        }
        if (verbose) {
            LOGD("Shared lib '%s' already loaded in same CL %p\n",
                pathName, classLoader);
        }
        if (!checkOnLoadResult(pEntry))
            return false;
        return true;
    }

    /*
     * Open the shared library.  Because we're using a full path, the system
     * doesn't have to search through LD_LIBRARY_PATH.  (It may do so to
     * resolve this library's dependencies though.)
     *
     * Failures here are expected when java.library.path has several entries
     * and we have to hunt for the lib.
     *
     * The current version of the dynamic linker prints detailed information
     * about dlopen() failures.  Some things to check if the message is
     * cryptic:
     *   - make sure the library exists on the device
     *   - verify that the right path is being opened (the debug log message
     *     above can help with that)
     *   - check to see if the library is valid (e.g. not zero bytes long)
     *   - check config/prelink-linux-arm.map to ensure that the library
     *     is listed and is not being overrun by the previous entry (if
     *     loading suddenly stops working on a prelinked library, this is
     *     a good one to check)
     *   - write a trivial app that calls sleep() then dlopen(), attach
     *     to it with "strace -p <pid>" while it sleeps, and watch for
     *     attempts to open nonexistent dependent shared libs
     *
     * This can execute slowly for a large library on a busy system, so we
     * want to switch from RUNNING to VMWAIT while it executes.  This allows
     * the GC to ignore us.
     */
    Thread* self = dvmThreadSelf();
    ThreadStatus oldStatus = dvmChangeStatus(self, THREAD_VMWAIT);
    handle = dlopen(pathName, RTLD_LAZY);
    dvmChangeStatus(self, oldStatus);

    if (handle == NULL) {
        *detail = strdup(dlerror());
        return false;
    }

    /* create a new entry */
    SharedLib* pNewEntry;
    pNewEntry = (SharedLib*) calloc(1, sizeof(SharedLib));
    pNewEntry->pathName = strdup(pathName);
    pNewEntry->handle = handle;
    pNewEntry->classLoader = classLoader;
    pNewEntry->libType = kpDllHandle;
    pNewEntry->refCount = 1;

    dvmInitMutex(&pNewEntry->onLoadLock);
    pthread_cond_init(&pNewEntry->onLoadCond, NULL);
    pNewEntry->onLoadThreadId = self->threadId;

    /* try to add it to the list */
    SharedLib* pActualEntry = addSharedLibEntry(pNewEntry);

    if (pNewEntry != pActualEntry) {
        LOGI("WOW: we lost a race to add a shared lib (%s CL=%p)\n",
            pathName, classLoader);
        freeSharedLibEntry(pNewEntry);
        return checkOnLoadResult(pActualEntry);
    } else {
        if (verbose)
            LOGD("Added shared lib %s %p\n", pathName, classLoader);

        bool result = true;
        void* vonLoad;
        int version;

        vonLoad = dlsym(handle, "JNI_OnLoad");
        if (vonLoad == NULL) {
            LOGD("No JNI_OnLoad found in %s %p, skipping init\n",
                pathName, classLoader);
        } else {
            /*
             * Call JNI_OnLoad.  We have to override the current class
             * loader, which will always be "null" since the stuff at the
             * top of the stack is around Runtime.loadLibrary().  (See
             * the comments in the JNI FindClass function.)
             */
            OnLoadFunc func = vonLoad;
            Object* prevOverride = self->classLoaderOverride;

            self->classLoaderOverride = classLoader;
            oldStatus = dvmChangeStatus(self, THREAD_NATIVE);
            LOGV("+++ calling JNI_OnLoad(%s)\n", pathName);
            version = (*func)(gDvm.vmList, NULL);
            dvmChangeStatus(self, oldStatus);
            self->classLoaderOverride = prevOverride;

            if (version != JNI_VERSION_1_2 && version != JNI_VERSION_1_4 &&
                version != JNI_VERSION_1_6)
            {
                LOGW("JNI_OnLoad returned bad version (%d) in %s %p\n",
                    version, pathName, classLoader);
                /*
                 * It's unwise to call dlclose() here, but we can mark it
                 * as bad and ensure that future load attempts will fail.
                 *
                 * We don't know how far JNI_OnLoad got, so there could
                 * be some partially-initialized stuff accessible through
                 * newly-registered native method calls.  We could try to
                 * unregister them, but that doesn't seem worthwhile.
                 */
                result = false;
            } else {
                LOGV("+++ finished JNI_OnLoad %s\n", pathName);
            }
        }

        if (result)
            pNewEntry->onLoadResult = kOnLoadOkay;
        else
            pNewEntry->onLoadResult = kOnLoadFailed;

        pNewEntry->onLoadThreadId = 0;

        /*
         * Broadcast a wakeup to anybody sleeping on the condition variable.
         */
        dvmLockMutex(&pNewEntry->onLoadLock);
        pthread_cond_broadcast(&pNewEntry->onLoadCond);
        dvmUnlockMutex(&pNewEntry->onLoadLock);
        return result;
    }
}


/*
 * Un-register JNI native methods.
 *
 * There are two relevant fields in struct Method, "nativeFunc" and
 * "insns".  The former holds a function pointer to a "bridge" function
 * (or, for internal native, the actual implementation).  The latter holds
 * a pointer to the actual JNI method.
 *
 * The obvious approach is to reset both fields to their initial state
 * (nativeFunc points at dvmResolveNativeMethod, insns holds NULL), but
 * that creates some unpleasant race conditions.  In particular, if another
 * thread is executing inside the call bridge for the method in question,
 * and we reset insns to NULL, the VM will crash.  (See the comments above
 * dvmSetNativeFunc() for additional commentary.)
 *
 * We can't rely on being able to update two 32-bit fields in one atomic
 * operation (e.g. no 64-bit atomic ops on ARMv5TE), so we want to change
 * only one field.  It turns out we can simply reset nativeFunc to its
 * initial state, leaving insns alone, because dvmResolveNativeMethod
 * ignores "insns" entirely.
 *
 * When the method is re-registered, both fields will be updated, but
 * dvmSetNativeFunc guarantees that "insns" is updated first.  This means
 * we shouldn't be in a situation where we have a "live" call bridge and
 * a stale implementation pointer.
 */
static void unregisterJNINativeMethods(Method* methods, size_t count)
{
    while (count != 0) {
        count--;

        Method* meth = &methods[count];
        if (!dvmIsNativeMethod(meth))
            continue;
        if (dvmIsAbstractMethod(meth))      /* avoid abstract method stubs */
            continue;

        /*
         * Strictly speaking this ought to test the function pointer against
         * the various JNI bridge functions to ensure that we only undo
         * methods that were registered through JNI.  In practice, any
         * native method with a non-NULL "insns" is a registered JNI method.
         *
         * If we inadvertently unregister an internal-native, it'll get
         * re-resolved on the next call; unregistering an unregistered
         * JNI method is a no-op.  So we don't really need to test for
         * anything.
         */

        LOGD("Unregistering JNI method %s.%s:%s\n",
            meth->clazz->descriptor, meth->name, meth->shorty);
        dvmSetNativeFunc(meth, dvmResolveNativeMethod, NULL);
    }
}

/*
 * Un-register all JNI native methods from a class.
 */
void dvmUnregisterJNINativeMethods(ClassObject* clazz)
{
    unregisterJNINativeMethods(clazz->directMethods, clazz->directMethodCount);
    unregisterJNINativeMethods(clazz->virtualMethods, clazz->virtualMethodCount);
}


/*
 * ===========================================================================
 *      Signature-based method lookup
 * ===========================================================================
 */

/*
 * Create the pre-mangled form of the class+method string.
 *
 * Returns a newly-allocated string, and sets "*pLen" to the length.
 */
static char* createJniNameString(const char* classDescriptor,
    const char* methodName, int* pLen)
{
    char* result;
    size_t descriptorLength = strlen(classDescriptor);

    *pLen = 4 + descriptorLength + strlen(methodName);

    result = malloc(*pLen +1);
    if (result == NULL)
        return NULL;

    /*
     * Add one to classDescriptor to skip the "L", and then replace
     * the final ";" with a "/" after the sprintf() call.
     */
    sprintf(result, "Java/%s%s", classDescriptor + 1, methodName);
    result[5 + (descriptorLength - 2)] = '/';

    return result;
}

/*
 * Returns a newly-allocated, mangled copy of "str".
 *
 * "str" is a "modified UTF-8" string.  We convert it to UTF-16 first to
 * make life simpler.
 */
static char* mangleString(const char* str, int len)
{
    u2* utf16 = NULL;
    char* mangle = NULL;
    int charLen;

    //LOGI("mangling '%s' %d\n", str, len);

    assert(str[len] == '\0');

    charLen = dvmUtf8Len(str);
    utf16 = (u2*) malloc(sizeof(u2) * charLen);
    if (utf16 == NULL)
        goto bail;

    dvmConvertUtf8ToUtf16(utf16, str);

    /*
     * Compute the length of the mangled string.
     */
    int i, mangleLen = 0;

    for (i = 0; i < charLen; i++) {
        u2 ch = utf16[i];

        if (ch == '$' || ch > 127) {
            mangleLen += 6;
        } else {
            switch (ch) {
            case '_':
            case ';':
            case '[':
                mangleLen += 2;
                break;
            default:
                mangleLen++;
                break;
            }
        }
    }

    char* cp;

    mangle = (char*) malloc(mangleLen +1);
    if (mangle == NULL)
        goto bail;

    for (i = 0, cp = mangle; i < charLen; i++) {
        u2 ch = utf16[i];

        if (ch == '$' || ch > 127) {
            sprintf(cp, "_0%04x", ch);
            cp += 6;
        } else {
            switch (ch) {
            case '_':
                *cp++ = '_';
                *cp++ = '1';
                break;
            case ';':
                *cp++ = '_';
                *cp++ = '2';
                break;
            case '[':
                *cp++ = '_';
                *cp++ = '3';
                break;
            case '/':
                *cp++ = '_';
                break;
            default:
                *cp++ = (char) ch;
                break;
            }
        }
    }

    *cp = '\0';

bail:
    free(utf16);
    return mangle;
}

/*
 * Create the mangled form of the parameter types.
 */
static char* createMangledSignature(const DexProto* proto)
{
    DexStringCache sigCache;
    const char* interim;
    char* result;

    dexStringCacheInit(&sigCache);
    interim = dexProtoGetParameterDescriptors(proto, &sigCache);
    result = mangleString(interim, strlen(interim));
    dexStringCacheRelease(&sigCache);

    return result;
}

/*
 * (This is a dvmHashForeach callback.)
 *
 * Search for a matching method in this shared library.
 *
 * TODO: we may want to skip libraries for which JNI_OnLoad failed.
 */
static int findMethodInLib(void* vlib, void* vmethod)
{
    const SharedLib* pLib = (const SharedLib*) vlib;
    const Method* meth = (const Method*) vmethod;
    char* preMangleCM = NULL;
    char* mangleCM = NULL;
    char* mangleSig = NULL;
    char* mangleCMSig = NULL;
    void* func = NULL;
    int len;

    if (meth->clazz->classLoader != pLib->classLoader) {
        LOGV("+++ not scanning '%s' for '%s' (wrong CL)\n",
            pLib->pathName, meth->name);
        return 0;
    } else
        LOGV("+++ scanning '%s' for '%s'\n", pLib->pathName, meth->name);

    /*
     * First, we try it without the signature.
     */
    preMangleCM =
        createJniNameString(meth->clazz->descriptor, meth->name, &len);
    if (preMangleCM == NULL)
        goto bail;

    mangleCM = mangleString(preMangleCM, len);
    if (mangleCM == NULL)
        goto bail;

    LOGV("+++ calling dlsym(%s)\n", mangleCM);
    func = dlsym(pLib->handle, mangleCM);
    if (func == NULL) {
        mangleSig =
            createMangledSignature(&meth->prototype);
        if (mangleSig == NULL)
            goto bail;

        mangleCMSig = (char*) malloc(strlen(mangleCM) + strlen(mangleSig) +3);
        if (mangleCMSig == NULL)
            goto bail;

        sprintf(mangleCMSig, "%s__%s", mangleCM, mangleSig);

        LOGV("+++ calling dlsym(%s)\n", mangleCMSig);
        func = dlsym(pLib->handle, mangleCMSig);
        if (func != NULL) {
            LOGV("Found '%s' with dlsym\n", mangleCMSig);
        }
    } else {
        LOGV("Found '%s' with dlsym\n", mangleCM);
    }

bail:
    free(preMangleCM);
    free(mangleCM);
    free(mangleSig);
    free(mangleCMSig);
    return (int) func;
}

/*
 * See if the requested method lives in any of the currently-loaded
 * shared libraries.  We do this by checking each of them for the expected
 * method signature.
 */
static void* lookupSharedLibMethod(const Method* method)
{
    if (gDvm.nativeLibs == NULL) {
        LOGE("Unexpected init state: nativeLibs not ready\n");
        dvmAbort();
    }
    return (void*) dvmHashForeach(gDvm.nativeLibs, findMethodInLib,
        (void*) method);
}


static void appendValue(char type, const JValue value, char* buf, size_t n,
        bool appendComma)
{
    size_t len = strlen(buf);
    if (len >= n - 32) { // 32 should be longer than anything we could append.
        buf[len - 1] = '.';
        buf[len - 2] = '.';
        buf[len - 3] = '.';
        return;
    }
    char* p = buf + len;
    switch (type) {
    case 'B':
        if (value.b >= 0 && value.b < 10) {
            sprintf(p, "%d", value.b);
        } else {
            sprintf(p, "0x%x (%d)", value.b, value.b);
        }
        break;
    case 'C':
        if (value.c < 0x7f && value.c >= ' ') {
            sprintf(p, "U+%x ('%c')", value.c, value.c);
        } else {
            sprintf(p, "U+%x", value.c);
        }
        break;
    case 'D':
        sprintf(p, "%g", value.d);
        break;
    case 'F':
        sprintf(p, "%g", value.f);
        break;
    case 'I':
        sprintf(p, "%d", value.i);
        break;
    case 'L':
        sprintf(p, "0x%x", value.i);
        break;
    case 'J':
        sprintf(p, "%lld", value.j);
        break;
    case 'S':
        sprintf(p, "%d", value.s);
        break;
    case 'V':
        strcpy(p, "void");
        break;
    case 'Z':
        strcpy(p, value.z ? "true" : "false");
        break;
    default:
        sprintf(p, "unknown type '%c'", type);
        break;
    }

    if (appendComma) {
        strcat(p, ", ");
    }
}

#define LOGI_NATIVE(...) LOG(LOG_INFO, LOG_TAG "-native", __VA_ARGS__)

void dvmLogNativeMethodEntry(const Method* method, const u4* args)
{
    char thisString[32] = { 0 };
    const u4* sp = args; // &args[method->registersSize - method->insSize];
    if (!dvmIsStaticMethod(method)) {
        sprintf(thisString, "this=0x%08x ", *sp++);
    }

    char argsString[128]= { 0 };
    const char* desc = &method->shorty[1];
    while (*desc != '\0') {
        char argType = *desc++;
        JValue value;
        if (argType == 'D' || argType == 'J') {
            value.j = dvmGetArgLong(sp, 0);
            sp += 2;
        } else {
            value.i = *sp++;
        }
        appendValue(argType, value, argsString, sizeof(argsString),
        *desc != '\0');
    }

    char* signature = dexProtoCopyMethodDescriptor(&method->prototype);
    LOGI_NATIVE("-> %s.%s%s %s(%s)", method->clazz->descriptor, method->name,
            signature, thisString, argsString);
    free(signature);
}

void dvmLogNativeMethodExit(const Method* method, Thread* self,
        const JValue returnValue)
{
    char* signature = dexProtoCopyMethodDescriptor(&method->prototype);
    if (dvmCheckException(self)) {
        Object* exception = dvmGetException(self);
        LOGI_NATIVE("<- %s.%s%s threw %s", method->clazz->descriptor,
                method->name, signature, exception->clazz->descriptor);
    } else {
        char returnValueString[128] = { 0 };
        char returnType = method->shorty[0];
        appendValue(returnType, returnValue,
                returnValueString, sizeof(returnValueString), false);
        LOGI_NATIVE("<- %s.%s%s returned %s", method->clazz->descriptor,
                method->name, signature, returnValueString);
    }
    free(signature);
}


//for CAR support
//if you want to exclusive access the hash table, dvmHashTableLock(gDvm.nativeLibs);
void* findHashCARModuleInfo(const char* pathName, whyFindCARModuleInfo why, int *refCount)
{
    SharedLib* ptr;

    ptr = findSharedLibEntry(pathName);
    if (ptr == NULL)
        return  NULL;

    if (ptr->libType != kpCARModuleInfo) {
        return  NULL;
    }

    if( why == kAddRefCount )
        ptr->refCount++;
    else if( why == kReleaseRefCount )
        ptr->refCount--;

    if( refCount != NULL )
        *refCount = ptr->refCount;

    return  ptr->handle;
}

void *addHashCARModuleInfo(const char *pathName, void* pModuleInfo)
{
    SharedLib *pNewEntry;

    pNewEntry = (SharedLib *)calloc(1, sizeof(SharedLib));
    pNewEntry->pathName = strdup(pathName);
    pNewEntry->handle = pModuleInfo;
    pNewEntry->classLoader = NULL;
    pNewEntry->libType = kpCARModuleInfo;
    pNewEntry->refCount = 1;

    /* try to add it to the list */
    SharedLib* pActualEntry = addSharedLibEntry(pNewEntry);

    if (pNewEntry != pActualEntry) {
/*        LOGI("WOW: we lost a race to add a CAR component(%s CL=%p)\n",*/
/*            pathName, classLoader);*/
        freeSharedLibEntry(pNewEntry);
        return NULL;
    }

    return  pActualEntry;
}


bool freeHashCARModuleInfo(const char *pathName)
{
    void *ptr = findHashCARModuleInfo(pathName, kReleaseRefCount , NULL);
    if (NULL == ptr)
        return false;

    u4 hash = dvmComputeUtf8Hash(pathName);

    freeSharedLibEntry(ptr);
    return dvmHashTableRemove(gDvm.nativeLibs, hash, ptr);
}

/*
 * (This is a dvmHashTableLookup callback.)
 */
static int hashcmpCARClass(const void* ventry, const void* vnewEntry)
{
    return ((u4)ventry-(u4)vnewEntry);
}

//we don't pay more attention of the ClassName in hash table
void *addHashCARClass(const char *className, void* pClassInfo)
{
    u4 hash = dvmComputeUtf8Hash(className);

    /*
     * Do the lookup with the "add" flag set.  If we add it, we will get
     * our own pointer back.  If somebody beat us to the punch, we'll get
     * their pointer back instead.
     */
    return  dvmHashTableLookup(gDvm.globalCARClass, hash, pClassInfo,
                               hashcmpCARClass, true);
}


//
// CAR Getter
//     MyGetter(thisCAR, InstField *, void *);
// typedef cdecl void (*CARGetter)(void *thisCAR, void *InstField, void *data);
// typedef cdecl void (*CARSetter)(void *thisCAR, void *InstField, void *data);
//
void dvmFieldBeforeRead(Object *object, InstField *pField)
{
    int          i;
    ClassObject* clz;

#if 0
    //this work do in asm
    if (pField->getter == (u4)NULL)
        return;
#endif
	LOGD("dvmFieldBeforeRead");

	if (pField->interfaceIndexOfSetter == 0xFFFC) {
        JValue  result;
        u1     *p = (u1*)object+pField->byteOffset;

        if (*(pField->field.signature) == 'D' || *(pField->field.signature) == 'J') {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->getter, object, &result, *(u8*)p);
            *(u8*)p = result.j;
        } else {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->getter, object, &result, *(u4*)p);
            *(u4*)p = result.i;
        }

	    return;
	}

	//find my CAR object
	for (i = 0, clz = object->clazz;  clz != (pField->field).clazz && clz != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS))
            i++;
    }
	if (clz == NULL) {
	    LOGE("CAR this pointer error");
	    return;
	}

    u4* pCARObject = (u4*)(*(u4*)(((char*)object) + (pField->field).clazz->objectSize + sizeof(u4)*i));
	if (pCARObject == NULL) {
	    LOGE("CAR this pointer error");
	    return;
	}

    if (!IS_FIELD_FLAG_SET(&(pField->field), FIELD_GETTER_SETTER_RESOLVED)) {
        pField->getter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->getter, pField->interfaceIndexOfGetter);
        pField->setter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->setter, pField->interfaceIndexOfSetter);
        SET_FIELD_FLAG(&(pField->field), FIELD_GETTER_SETTER_RESOLVED);
    }

	LOGD("pField->getter %p", (u4*)pField->getter);
	LOGD("pField->setter %p", (u4*)pField->setter);
    if (pField->getter != (u4)NULL)
        ((CARGetter)pField->getter)(pCARObject+pField->interfaceIndexOfGetter, pField, (u1 *)object+pField->byteOffset);
        //((CARGetter)pField->getter)((u1 *)object+pField->byteOffset);
}


//defined in jni.c
jobject addGlobalReference(jobject obj);
void deleteGlobalReference(jobject obj);

void dvmFieldAfterWrite(Object *object, InstField *pField)
{
    int          i;
    ClassObject* clz;

#if 0
    //this work do in asm
    if (pField->setter == (u4)NULL)
        return;
#endif
	LOGD("dvmFieldAfterWrite");

	if (pField->interfaceIndexOfSetter == 0xFFFC) {
        JValue  result;
        u1     *p = (u1*)object+pField->byteOffset;

        if (*(pField->field.signature) == 'D' || *(pField->field.signature) == 'J') {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->setter, object, &result, *(u8*)p);
            *(u8*)p = result.j;
        } else {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->setter, object, &result, *(u4*)p);
            *(u4*)p = result.i;
        }

	    return;
	}

	//find my CAR object
	for (i = 0, clz = object->clazz;  clz != (pField->field).clazz && clz != NULL;  clz = clz->super) {
        if (IS_CLASS_FLAG_SET(clz, CLASS_CAR_CLASS))
            i++;
    }
	if (clz == NULL) {
	    LOGE("CAR this pointer error");
	    return;
	}

    u4* pCARObject = (u4*)(*(u4*)(((char*)object) + (pField->field).clazz->objectSize + sizeof(u4)*i));
    LOGD("pCARObject %p", pCARObject);
	if (pCARObject == NULL) {
	    LOGE("CAR this pointer error");
	    return;
	}

	LOGD("pField->getter %p", (u4*)pField->getter);
	LOGD("pField->setter %p", (u4*)pField->setter);

	if (pField->interfaceIndexOfSetter == 0xFFFF || pField->interfaceIndexOfSetter == 0xFFFE) {

        int      i;
        bool     tf;
    	Method  *method;
    	bool     inVirtual;
    	int      nameConflict;
    	char     buf[256];
    	Object  *obj;
        u4      *CallbacksObj;
        u4      *CallbackMethods;
        u4      *thisObjs;
        u4       icount;

        //first, remove older callbacks
		CallbacksObj = (u4*)(*(u4*)((u1*)object+pField->byteOffset+sizeof(u4)));
        if (CallbacksObj != NULL) {
            //free the elders
			//dvmRemoveAllCallbackHandler(object);

    	    CallbackMethods = (u4*)(((ArrayObject*)dvmGetFieldObject((const Object*)CallbacksObj,
    	                                    gDvm.offJavaLangDelegate_value))->contents);
    	    thisObjs = (u4*)(((ArrayObject*)dvmGetFieldObject((const Object*)CallbacksObj,
    	                                    gDvm.offJavaLangDelegate_thisObj))->contents);
    	    icount = dvmGetFieldInt((const Object*)CallbacksObj, gDvm.offJavaLangDelegate_count);

            for (i = 0;  i < (int)icount;  i++) {

                obj = (Object*)(thisObjs[i]);

                if (CallbackMethods[i] == 0) {
                    if (pField->interfaceIndexOfSetter == 0xFFFF)
                        strcat(strcat(strcpy(buf, "Do"), pField->field.name), "Delegate");
                    else /* pField->interfaceIndexOfSetter == 0xFFFE) */
                        strcat(strcat(strcpy(buf, "On"), pField->field.name), "Callback");

                    if (obj != 0) {
                	    method = dvmFindMethodInListByNameForCAR(obj->clazz, buf, &inVirtual, &nameConflict);
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
                	    tf = dvmRemoveEventCallbackHandler(object, pField->interfaceIndexOfGetter, (u4)obj,
                	                                        pField->setter, method);
                	//}
                } else {
                    if (obj != 0) {
            	        tf = dvmRemoveEventCallbackHandler(object, pField->interfaceIndexOfGetter, (u4)obj,
            	                                        pField->setter, (Method*)CallbackMethods[i]);
                    } else {
                	    continue;
                	}
                }
        	    if (!tf) {
        	        LOGE("error");
        	    }
        	}

            deleteGlobalReference((Object*)CallbacksObj);
        }

        //second, add new callbacks if needed
        CallbacksObj = (u4*)(*(u4*)((u1*)object+pField->byteOffset));
        *(u4*)((u1*)object+pField->byteOffset+sizeof(u4)) = (u4)CallbacksObj;
        if (CallbacksObj != NULL) {
            CallbackMethods = (u4*)(((ArrayObject*)dvmGetFieldObject((const Object*)CallbacksObj,
                                            gDvm.offJavaLangDelegate_value))->contents);
            thisObjs = (u4*)(((ArrayObject*)dvmGetFieldObject((const Object*)CallbacksObj,
                                            gDvm.offJavaLangDelegate_thisObj))->contents);
            icount = dvmGetFieldInt((const Object*)CallbacksObj, gDvm.offJavaLangDelegate_count);

            for (i = 0;  i < (int)icount;  i++) {

                obj = (Object*)(thisObjs[i]);

                if (CallbackMethods[i] == 0) {

                    /*
                     * God take care of me, let:
                     * strlen("Callback")==8 and strlen("Delegate")==8
                     */
                    char *s = (char*)pField->field.name;
                    int   j = strlen(s);
                	char  buf2[256];

                    if (j > 8) {
                        //memory is big enough to hold "Callback", "Delegate"
                        j -= 8;
                        if (strcmp(s+j, "Callback") == 0 || strcmp(s+j, "Delegate") == 0 ) {
                            strncpy(buf2, s, j);
                            buf2[j] = '\0';
                            s = buf2;
                        }
                    }

                    if (pField->interfaceIndexOfSetter == 0xFFFF)
                        strcat(strcat(strcpy(buf, "Do"), s), "Delegate");
                    else /* pField->interfaceIndexOfSetter == 0xFFFE) */
                        strcat(strcat(strcpy(buf, "On"), s), "Callback");

                    if (obj == 0) {
						method = dvmFindMethodInListByNameForCAR(((Object*)CallbacksObj)->clazz, buf, &inVirtual, &nameConflict);
                	} else {
                	    method = dvmFindMethodInListByNameForCAR(obj->clazz, buf, &inVirtual, &nameConflict);
                	}

                	LOGD("method %p", method);
                	/*
                     * when nameconflict>1 ,method is the first matched value
                	 * if (nameConflict != 1) {
                	 *    tf = false;
                     * } else {
                     */
                	    tf = dvmAddEventCallbackHandler(object, pField->interfaceIndexOfGetter, (u4)obj,
                	                                        pField->setter, method);
                	//}
                } else {
            	    tf = dvmAddEventCallbackHandler(object, pField->interfaceIndexOfGetter, (u4)obj,
            	                                        pField->setter, (Method*)CallbackMethods[i]);
                }
        	    if (!tf) {
        	        LOGE("error");
        	    }
        	}

            addGlobalReference((Object*)CallbacksObj);
	    }

    	return;
	}

    if (!IS_FIELD_FLAG_SET(&(pField->field), FIELD_GETTER_SETTER_RESOLVED)) {
        pField->getter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->getter, pField->interfaceIndexOfGetter);
        pField->setter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->setter, pField->interfaceIndexOfSetter);
        SET_FIELD_FLAG(&(pField->field), FIELD_GETTER_SETTER_RESOLVED);
    }

	LOGD("pField->getter %p", (u4*)pField->getter);
	LOGD("pField->setter %p", (u4*)pField->setter);
	LOGD("pCARObject %p, %p", pCARObject, (u4*)pField->setter);
    if (pField->setter != (u4)NULL)
        ((CARSetter)pField->setter)(pCARObject+pField->interfaceIndexOfSetter, pField, (u1*)object+pField->byteOffset);
    LOGD("dvmFieldAfterWrite end");
        //((CARSetter)pField->setter)((u1 *)object+pField->byteOffset);
}

void dvmStaticFieldBeforeRead(StaticField *pField)
{
#if 0
    //this work do in asm
    if (pField->pSetterGetterClassObject == (u4)NULL)
        return;
#endif

	if (pField->interfaceIndexOfSetter == 0xFFFC) {
        JValue  result;
        u1     *p = (u1*)&(pField->value);

        if (*(pField->field.signature) == 'D' || *(pField->field.signature) == 'J') {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->getter, NULL, &result, *(u8*)p);
            *(u8*)p = result.j;
        } else {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->getter, NULL, &result, *(u4*)p);
            *(u4*)p = result.i;
        }

	    return;
	}

    u4* pCARObject = (u4*)dvmCreateCARClassObject((ClassObject*)pField->pSetterGetterClassObject, NULL);

    if (pCARObject == NULL) {
	    char buf[512];

	    sprintf(buf, "dvmCreateCARClassObject: %s\n", pField->field.name);
	    dvmThrowException("Ljava/lang/NullPointerException;", buf);
        return;
    }

    if (!IS_FIELD_FLAG_SET(&(pField->field), FIELD_GETTER_SETTER_RESOLVED)) {
        pField->getter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->getter, pField->interfaceIndexOfGetter);
        pField->setter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->setter, pField->interfaceIndexOfSetter);
        SET_FIELD_FLAG(&(pField->field), FIELD_GETTER_SETTER_RESOLVED);
    }

	LOGD("pField->getter %p", (u4*)pField->getter);
	LOGD("pField->setter %p", (u4*)pField->setter);
	LOGD("pCARObject %p, %p", pCARObject, (u4*)pField->getter);
    if (pField->getter != (u4)NULL)
        ((CARStaticSetter)pField->getter)(pCARObject, pField, (u1*)&(pField->value));
    LOGD("dvmStaticFieldBeforeRead end");
        //((CARSetter)pField->setter)((u1 *)object+pField->byteOffset);

    dvmReleaseCARClassObject((u4)pCARObject);
}

void dvmStaticFieldAfterWrite(StaticField *pField)
{
#if 0
    //this work do in asm
    if (pField->pSetterGetterClassObject == (u4)NULL)
        return;
#endif

	if (pField->interfaceIndexOfSetter == 0xFFFC) {
        JValue  result;
        u1     *p = (u1*)&(pField->value);

        if (*(pField->field.signature) == 'D' || *(pField->field.signature) == 'J') {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->setter, NULL, &result, *(u8*)p);
            *(u8*)p = result.j;
        } else {
            dvmCallMethod(dvmThreadSelf(), (Method*)pField->setter, NULL, &result, *(u4*)p);
            *(u4*)p = result.i;
        }

	    return;
	}

    u4* pCARObject = (u4*)pField->pSetterGetterClassObject;

    if (pCARObject == NULL) {
	    char buf[512];

	    sprintf(buf, "dvmCreateCARClassObject: %s\n", pField->field.name);
	    dvmThrowException("Ljava/lang/NullPointerException;", buf);
        return;
    }

    if (!IS_FIELD_FLAG_SET(&(pField->field), FIELD_GETTER_SETTER_RESOLVED)) {
        pField->getter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->getter, pField->interfaceIndexOfGetter);
        pField->setter = (u4)dvmGetCARMethodinfoFunctionAddr(pCARObject, (u4*)pField->setter, pField->interfaceIndexOfSetter);
        SET_FIELD_FLAG(&(pField->field), FIELD_GETTER_SETTER_RESOLVED);
    }

	LOGD("pField->getter %p", (u4*)pField->getter);
	LOGD("pField->setter %p", (u4*)pField->setter);
	LOGD("pCARObject %p, %p", pCARObject, (u4*)pField->setter);
    if (pField->getter != (u4)NULL)
        ((CARStaticSetter)pField->setter)(pCARObject, pField, (u1 *)&(pField->value));
    LOGD("dvmStaticFieldAfterWrite end");
        //((CARSetter)pField->setter)((u1 *)object+pField->byteOffset);

    dvmReleaseCARClassObject((u4)pCARObject);
}

