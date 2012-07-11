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

#define LOG_TAG "ByteOrder"

#include "JNIHelp.h"
#include "JniConstants.h"

static jboolean ByteOrder_isLittleEndian(JNIEnv*, jclass) {
    int i = 1;
    return *reinterpret_cast<jbyte*>(&i) == 1;
}

static JNINativeMethod gMethods[] = {
    NATIVE_METHOD(ByteOrder, isLittleEndian, "()Z"),
};
int register_java_nio_ByteOrder(JNIEnv* env) {
    return jniRegisterNativeMethods(env, "java/nio/ByteOrder", gMethods, NELEM(gMethods));
}
