/*
 * Copyright (C) 2010 elastos
 *
 * package for CAR base datatype
 */

package elastos.runtime;

import dalvik.annotation.ElastosClass;
import dalvik.annotation.ElastosMethod;

@ElastosClass(Module="ElastosRuntime.dll", Class="StringBuf")
public class StringBuf {

    native void Init(int size);

    @ElastosMethod("AppendStr")
    native void Append(String str);
    @ElastosMethod("AppendSubstr")
    native void Append(String str, int offset, int count);
    @ElastosMethod("AppendC")
    native void Append(char c);
    @ElastosMethod("AppendI")
    native void Append(int i);
    @ElastosMethod("AppendL")
    native void Append(long l);
    @ElastosMethod("Append6")
    native void AppendD(double d);
    @ElastosMethod("Append7")
    native void AppendB(boolean b);

    native StringBuf Clone();

    @ElastosMethod("CompareStr")
    native int Compare(String str, boolean StringCaseSenitive);
    @ElastosMethod("CompareStrbuf")
    native int Compare(StringBuf strbuf, boolean StringCaseSenitive);

    native void Concatenate(String str);

    @ElastosMethod("CopyStr")
    native void Copy(String str);
    @ElastosMethod("CopySubstr")
    native void Copy(String str, int len);

    native String GetPayload();
    native int GetCapacity();
    native int GetLength();
    native int GetAvailableSpace();
    native int SetLength(int len);
    native int ToInt32();
    native long ToInt64();
    native boolean ToBoolean();
    native double ToDouble();
    native int GetCharCount();
    native char GetChar(int index);

    native boolean Contains(String str, boolean StringCaseSenitive);
    native boolean StartWith(String str, boolean StringCaseSenitive);
    native boolean EndWith(String str, boolean StringCaseSenitive);

    //---- IndexOf ----
    native int IndexOf(char ch, boolean StringCaseSenitive);
    native int IndexOfAny(String str, boolean StringCaseSenitive);
    native int IndexOfChar(char ch, boolean StringCaseSenitive);
    native int IndexOfAnyChar(Char32 strCharSet, boolean StringCaseSenitive);


    //---- LastIndexOf ----
    native int LastIndexOf(char ch, boolean StringCaseSenitive);
    native int LastIndexOfAny(String str, boolean StringCaseSenitive);
    native int LastIndexOfChar(char ch, boolean StringCaseSenitive);
    native int LastIndexOfAnyChar(Char32 strCharSet, boolean StringCaseSenitive);

    //---- Substring ----
    native String Substring(int start, StringBuf sub);
    native String Substring(int start, int len, StringBuf sub);

    //---- ToLowerCase ----
    native void ToLowerCase();

    //---- ToUpperCase ----
    native void ToUpperCase();

    //---- TrimStart ----
    native void TrimStart();

    //---- TrimEnd ----
    native void TrimEnd();

    //---- Trim ----
    native void Trim();

    //
    native void PadLeft(int width);
    native void PadRight(int width);

    @ElastosMethod("PadLeft2")
    native void PadLeft(int width, char ch);
    @ElastosMethod("PadRight2")
    native void PadRight(int width, char ch);
}


