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

#define LOG_TAG "NativePluralRules"

#include "ErrorCode.h"
#include "JNIHelp.h"
#include "JniConstants.h"
#include "ScopedUtfChars.h"
#include "unicode/plurrule.h"

static PluralRules* toPluralRules(jint address) {
    return reinterpret_cast<PluralRules*>(static_cast<uintptr_t>(address));
}

static void NativePluralRules_finalizeImpl(JNIEnv*, jclass, jint address) {
    delete toPluralRules(address);
}

static jint NativePluralRules_forLocaleImpl(JNIEnv* env, jclass, jstring localeName) {
    Locale locale = Locale::createFromName(ScopedUtfChars(env, localeName).c_str());
    UErrorCode status = U_ZERO_ERROR;
    PluralRules* result = PluralRules::forLocale(locale, status);
    icu4jni_error(env, status);
    return reinterpret_cast<uintptr_t>(result);
}

static jint NativePluralRules_quantityForIntImpl(JNIEnv*, jclass, jint address, jint value) {
    UnicodeString keyword = toPluralRules(address)->select(value);
    if (keyword == "zero") {
        return 0;
    } else if (keyword == "one") {
        return 1;
    } else if (keyword == "two") {
        return 2;
    } else if (keyword == "few") {
        return 3;
    } else if (keyword == "many") {
        return 4;
    } else {
        return 5;
    }
}

static JNINativeMethod gMethods[] = {
    NATIVE_METHOD(NativePluralRules, finalizeImpl, "(I)V"),
    NATIVE_METHOD(NativePluralRules, forLocaleImpl, "(Ljava/lang/String;)I"),
    NATIVE_METHOD(NativePluralRules, quantityForIntImpl, "(II)I"),
};
int register_libcore_icu_NativePluralRules(JNIEnv* env) {
    return jniRegisterNativeMethods(env, "libcore/icu/NativePluralRules", gMethods, NELEM(gMethods));
}
