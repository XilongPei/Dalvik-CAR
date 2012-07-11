/*
 * Copyright (C) 2010 The Android Open Source Project
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

#define LOG_TAG "Matcher"

#include <stdlib.h>

#include "ErrorCode.h"
#include "JNIHelp.h"
#include "JniConstants.h"
#include "ScopedJavaUnicodeString.h"
#include "ScopedPrimitiveArray.h"
#include "UniquePtr.h"
#include "jni.h"
#include "unicode/parseerr.h"
#include "unicode/regex.h"

// ICU documentation: http://icu-project.org/apiref/icu4c/classRegexMatcher.html

static RegexMatcher* toRegexMatcher(jint addr) {
    return reinterpret_cast<RegexMatcher*>(static_cast<uintptr_t>(addr));
}

/**
 * We use ICU4C's RegexMatcher class, but our input is on the Java heap and potentially moving
 * around between calls. This wrapper class ensures that our RegexMatcher is always pointing at
 * the current location of the char[]. Earlier versions of Android simply copied the data to the
 * native heap, but that's wasteful and hides allocations from the garbage collector.
 */
class MatcherAccessor {
public:
    MatcherAccessor(JNIEnv* env, jint addr, jstring javaInput, bool reset) {
        init(env, addr);

        mJavaInput = javaInput;
        mChars = env->GetStringChars(mJavaInput, NULL);
        if (mChars == NULL) {
            return;
        }

        mUText = utext_openUChars(NULL, mChars, env->GetStringLength(mJavaInput), &mStatus);
        if (mUText == NULL) {
            return;
        }

        if (reset) {
            mMatcher->reset(mUText);
        } else {
            mMatcher->refreshInputText(mUText, mStatus);
        }
    }

    MatcherAccessor(JNIEnv* env, jint addr) {
        init(env, addr);
    }

    ~MatcherAccessor() {
        utext_close(mUText);
        if (mJavaInput) {
            mEnv->ReleaseStringChars(mJavaInput, mChars);
        }
        icu4jni_error(mEnv, mStatus);
    }

    RegexMatcher* operator->() {
        return mMatcher;
    }

    UErrorCode& status() {
        return mStatus;
    }

    void updateOffsets(jintArray javaOffsets) {
        ScopedIntArrayRW offsets(mEnv, javaOffsets);
        if (offsets.get() == NULL) {
            return;
        }

        for (size_t i = 0, groupCount = mMatcher->groupCount(); i <= groupCount; ++i) {
            offsets[2*i + 0] = mMatcher->start(i, mStatus);
            offsets[2*i + 1] = mMatcher->end(i, mStatus);
        }
    }

private:
    void init(JNIEnv* env, jint addr) {
        mEnv = env;
        mJavaInput = NULL;
        mMatcher = toRegexMatcher(addr);
        mChars = NULL;
        mStatus = U_ZERO_ERROR;
        mUText = NULL;
    }

    JNIEnv* mEnv;
    jstring mJavaInput;
    RegexMatcher* mMatcher;
    const jchar* mChars;
    UErrorCode mStatus;
    UText* mUText;

    // Disallow copy and assignment.
    MatcherAccessor(const MatcherAccessor&);
    void operator=(const MatcherAccessor&);
};

static void Matcher_closeImpl(JNIEnv*, jclass, jint addr) {
    delete toRegexMatcher(addr);
}

static jint Matcher_findImpl(JNIEnv* env, jclass, jint addr, jstring javaText, jint startIndex, jintArray offsets) {
    MatcherAccessor matcher(env, addr, javaText, false);
    UBool result = matcher->find(startIndex, matcher.status());
    if (result) {
        matcher.updateOffsets(offsets);
    }
    return result;
}

static jint Matcher_findNextImpl(JNIEnv* env, jclass, jint addr, jstring javaText, jintArray offsets) {
    MatcherAccessor matcher(env, addr, javaText, false);
    if (matcher.status() != U_ZERO_ERROR) {
        return -1;
    }
    UBool result = matcher->find();
    if (result) {
        matcher.updateOffsets(offsets);
    }
    return result;
}

static jint Matcher_groupCountImpl(JNIEnv* env, jclass, jint addr) {
    MatcherAccessor matcher(env, addr);
    return matcher->groupCount();
}

static jint Matcher_hitEndImpl(JNIEnv* env, jclass, jint addr) {
    MatcherAccessor matcher(env, addr);
    return matcher->hitEnd();
}

static jint Matcher_lookingAtImpl(JNIEnv* env, jclass, jint addr, jstring javaText, jintArray offsets) {
    MatcherAccessor matcher(env, addr, javaText, false);
    UBool result = matcher->lookingAt(matcher.status());
    if (result) {
        matcher.updateOffsets(offsets);
    }
    return result;
}

static jint Matcher_matchesImpl(JNIEnv* env, jclass, jint addr, jstring javaText, jintArray offsets) {
    MatcherAccessor matcher(env, addr, javaText, false);
    UBool result = matcher->matches(matcher.status());
    if (result) {
        matcher.updateOffsets(offsets);
    }
    return result;
}

static jint Matcher_openImpl(JNIEnv* env, jclass, jint patternAddr) {
    RegexPattern* pattern = reinterpret_cast<RegexPattern*>(static_cast<uintptr_t>(patternAddr));
    UErrorCode status = U_ZERO_ERROR;
    RegexMatcher* result = pattern->matcher(status);
    icu4jni_error(env, status);
    return static_cast<jint>(reinterpret_cast<uintptr_t>(result));
}

static jint Matcher_requireEndImpl(JNIEnv* env, jclass, jint addr) {
    MatcherAccessor matcher(env, addr);
    return matcher->requireEnd();
}

static void Matcher_setInputImpl(JNIEnv* env, jclass, jint addr, jstring javaText, jint start, jint end) {
    MatcherAccessor matcher(env, addr, javaText, true);
    matcher->region(start, end, matcher.status());
}

static void Matcher_useAnchoringBoundsImpl(JNIEnv* env, jclass, jint addr, jboolean value) {
    MatcherAccessor matcher(env, addr);
    matcher->useAnchoringBounds(value);
}

static void Matcher_useTransparentBoundsImpl(JNIEnv* env, jclass, jint addr, jboolean value) {
    MatcherAccessor matcher(env, addr);
    matcher->useTransparentBounds(value);
}

static JNINativeMethod gMethods[] = {
    NATIVE_METHOD(Matcher, closeImpl, "(I)V"),
    NATIVE_METHOD(Matcher, findImpl, "(ILjava/lang/String;I[I)Z"),
    NATIVE_METHOD(Matcher, findNextImpl, "(ILjava/lang/String;[I)Z"),
    NATIVE_METHOD(Matcher, groupCountImpl, "(I)I"),
    NATIVE_METHOD(Matcher, hitEndImpl, "(I)Z"),
    NATIVE_METHOD(Matcher, lookingAtImpl, "(ILjava/lang/String;[I)Z"),
    NATIVE_METHOD(Matcher, matchesImpl, "(ILjava/lang/String;[I)Z"),
    NATIVE_METHOD(Matcher, openImpl, "(I)I"),
    NATIVE_METHOD(Matcher, requireEndImpl, "(I)Z"),
    NATIVE_METHOD(Matcher, setInputImpl, "(ILjava/lang/String;II)V"),
    NATIVE_METHOD(Matcher, useAnchoringBoundsImpl, "(IZ)V"),
    NATIVE_METHOD(Matcher, useTransparentBoundsImpl, "(IZ)V"),
};
int register_java_util_regex_Matcher(JNIEnv* env) {
    return jniRegisterNativeMethods(env, "java/util/regex/Matcher", gMethods, NELEM(gMethods));
}
