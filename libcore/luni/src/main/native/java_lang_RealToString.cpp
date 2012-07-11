/*
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#define LOG_TAG "RealToString"

#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "JNIHelp.h"
#include "JniConstants.h"
#include "ScopedPrimitiveArray.h"
#include "cbigint.h"

#define INV_LOG_OF_TEN_BASE_2 (0.30102999566398114) /* Local */

/*NB the Number converter methods are synchronized so it is possible to
 *have global data for use by bigIntDigitGenerator */
#define RM_SIZE 21     /* Local. */
#define STemp_SIZE 22  /* Local. */

/* The algorithm for this particular function can be found in:
 *
 *      Printing Floating-Point Numbers Quickly and Accurately, Robert
 *      G. Burger, and R. Kent Dybvig, Programming Language Design and
 *      Implementation (PLDI) 1996, pp.108-116.
 *
 * The previous implementation of this function combined m+ and m- into
 * one single M which caused some inaccuracy of the last digit. The
 * particular case below shows this inaccuracy:
 *
 *       System.out.println(new Double((1.234123412431233E107)).toString());
 *       System.out.println(new Double((1.2341234124312331E107)).toString());
 *       System.out.println(new Double((1.2341234124312332E107)).toString());
 *
 *       outputs the following:
 *
 *           1.234123412431233E107
 *           1.234123412431233E107
 *           1.234123412431233E107
 *
 *       instead of:
 *
 *           1.234123412431233E107
 *           1.2341234124312331E107
 *           1.2341234124312331E107
 *
 */
void RealToString_bigIntDigitGenerator(JNIEnv* env, jobject obj, jlong f, jint e,
        jboolean isDenormalized, jint p) {
  int RLength, SLength, TempLength, mplus_Length, mminus_Length;
  int high, low, i;
  jint k, firstK, U;

  uint64_t R[RM_SIZE], S[STemp_SIZE], mplus[RM_SIZE], mminus[RM_SIZE], Temp[STemp_SIZE];

  memset (R     , 0, RM_SIZE    * sizeof (uint64_t));
  memset (S     , 0, STemp_SIZE * sizeof (uint64_t));
  memset (mplus , 0, RM_SIZE    * sizeof (uint64_t));
  memset (mminus, 0, RM_SIZE    * sizeof (uint64_t));
  memset (Temp  , 0, STemp_SIZE * sizeof (uint64_t));

  if (e >= 0)
    {
      *R = f;
      *mplus = *mminus = 1;
      simpleShiftLeftHighPrecision (mminus, RM_SIZE, e);
      if (f != (2 << (p - 1)))
        {
          simpleShiftLeftHighPrecision (R, RM_SIZE, e + 1);
          *S = 2;
          /*
           * m+ = m+ << e results in 1.0e23 to be printed as
           * 0.9999999999999999E23
           * m+ = m+ << e+1 results in 1.0e23 to be printed as
           * 1.0e23 (caused too much rounding)
           *      470fffffffffffff = 2.0769187434139308E34
           *      4710000000000000 = 2.076918743413931E34
           */
          simpleShiftLeftHighPrecision (mplus, RM_SIZE, e);
        }
      else
        {
          simpleShiftLeftHighPrecision (R, RM_SIZE, e + 2);
          *S = 4;
          simpleShiftLeftHighPrecision (mplus, RM_SIZE, e + 1);
        }
    }
  else
    {
      if (isDenormalized || (f != (2 << (p - 1))))
        {
          *R = f << 1;
          *S = 1;
          simpleShiftLeftHighPrecision (S, STemp_SIZE, 1 - e);
          *mplus = *mminus = 1;
        }
      else
        {
          *R = f << 2;
          *S = 1;
          simpleShiftLeftHighPrecision (S, STemp_SIZE, 2 - e);
          *mplus = 2;
          *mminus = 1;
        }
    }

  k = static_cast<int>(ceil ((e + p - 1) * INV_LOG_OF_TEN_BASE_2 - 1e-10));

  if (k > 0)
    {
      timesTenToTheEHighPrecision (S, STemp_SIZE, k);
    }
  else
    {
      timesTenToTheEHighPrecision (R     , RM_SIZE, -k);
      timesTenToTheEHighPrecision (mplus , RM_SIZE, -k);
      timesTenToTheEHighPrecision (mminus, RM_SIZE, -k);
    }

  RLength = mplus_Length = mminus_Length = RM_SIZE;
  SLength = TempLength = STemp_SIZE;

  memset (Temp + RM_SIZE, 0, (STemp_SIZE - RM_SIZE) * sizeof (uint64_t));
  memcpy (Temp, R, RM_SIZE * sizeof (uint64_t));

  while (RLength > 1 && R[RLength - 1] == 0)
    --RLength;
  while (mplus_Length > 1 && mplus[mplus_Length - 1] == 0)
    --mplus_Length;
  while (mminus_Length > 1 && mminus[mminus_Length - 1] == 0)
    --mminus_Length;
  while (SLength > 1 && S[SLength - 1] == 0)
    --SLength;
  TempLength = (RLength > mplus_Length ? RLength : mplus_Length) + 1;
  addHighPrecision (Temp, TempLength, mplus, mplus_Length);

  if (compareHighPrecision (Temp, TempLength, S, SLength) >= 0)
    {
      firstK = k;
    }
  else
    {
      firstK = k - 1;
      simpleAppendDecimalDigitHighPrecision (R     , ++RLength      , 0);
      simpleAppendDecimalDigitHighPrecision (mplus , ++mplus_Length , 0);
      simpleAppendDecimalDigitHighPrecision (mminus, ++mminus_Length, 0);
      while (RLength > 1 && R[RLength - 1] == 0)
        --RLength;
      while (mplus_Length > 1 && mplus[mplus_Length - 1] == 0)
        --mplus_Length;
      while (mminus_Length > 1 && mminus[mminus_Length - 1] == 0)
        --mminus_Length;
    }

  static jfieldID digitsFid = env->GetFieldID(JniConstants::realToStringClass, "digits", "[I");
  jintArray javaDigits = reinterpret_cast<jintArray>(env->GetObjectField(obj, digitsFid));
  ScopedIntArrayRW digits(env, javaDigits);
  if (digits.get() == NULL) {
    return;
  }

  jint digitCount = 0;
  do
    {
      U = 0;
      for (i = 3; i >= 0; --i)
        {
          TempLength = SLength + 1;
          Temp[SLength] = 0;
          memcpy (Temp, S, SLength * sizeof (uint64_t));
          simpleShiftLeftHighPrecision (Temp, TempLength, i);
          if (compareHighPrecision (R, RLength, Temp, TempLength) >= 0)
            {
              subtractHighPrecision (R, RLength, Temp, TempLength);
              U += 1 << i;
            }
        }

      low = compareHighPrecision (R, RLength, mminus, mminus_Length) <= 0;

      memset (Temp + RLength, 0, (STemp_SIZE - RLength) * sizeof (uint64_t));
      memcpy (Temp, R, RLength * sizeof (uint64_t));
      TempLength = (RLength > mplus_Length ? RLength : mplus_Length) + 1;
      addHighPrecision (Temp, TempLength, mplus, mplus_Length);

      high = compareHighPrecision (Temp, TempLength, S, SLength) >= 0;

      if (low || high)
        break;

      simpleAppendDecimalDigitHighPrecision (R     , ++RLength      , 0);
      simpleAppendDecimalDigitHighPrecision (mplus , ++mplus_Length , 0);
      simpleAppendDecimalDigitHighPrecision (mminus, ++mminus_Length, 0);
      while (RLength > 1 && R[RLength - 1] == 0)
        --RLength;
      while (mplus_Length > 1 && mplus[mplus_Length - 1] == 0)
        --mplus_Length;
      while (mminus_Length > 1 && mminus[mminus_Length - 1] == 0)
        --mminus_Length;
      digits[digitCount++] = U;
    }
  while (1);

  simpleShiftLeftHighPrecision (R, ++RLength, 1);
  if (low && !high)
    digits[digitCount++] = U;
  else if (high && !low)
    digits[digitCount++] = U + 1;
  else if (compareHighPrecision (R, RLength, S, SLength) < 0)
    digits[digitCount++] = U;
  else
    digits[digitCount++] = U + 1;

  static jfieldID digitCountFid = env->GetFieldID(JniConstants::realToStringClass, "digitCount", "I");
  env->SetIntField(obj, digitCountFid, digitCount);

  static jfieldID firstKFid = env->GetFieldID(JniConstants::realToStringClass, "firstK", "I");
  env->SetIntField(obj, firstKFid, firstK);
}

static JNINativeMethod gMethods[] = {
    NATIVE_METHOD(RealToString, bigIntDigitGenerator, "(JIZI)V"),
};
int register_java_lang_RealToString(JNIEnv* env) {
    return jniRegisterNativeMethods(env, "java/lang/RealToString", gMethods, NELEM(gMethods));
}
