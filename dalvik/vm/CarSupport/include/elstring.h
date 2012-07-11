//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __EZSTRING_H__
#define __EZSTRING_H__

#include <elquintet.h>

_ELASTOS_NAMESPACE_BEGIN

/** @addtogroup BaseTypesRef
  *   @{
  */
typedef enum _StringCase
{
    StringCase_Sensitive         = 0x0000,
    StringCase_Insensitive       = 0x0001,
} StringCase;

typedef enum _Encoding
{
    Encoding_Default             = 0x0000,
    Encoding_ASCII               = 0x0001,
    Encoding_UTF7                = 0x0002,
    Encoding_UTF8                = 0x0003,
    Encoding_GB18030             = 0x0004,
    Encoding_LATIN_1             = 0x0005,
    Encoding_BIG5                = 0x0006,
    Encoding_EUC_JP              = 0x0007,
} Encoding;
/** @} */

_ELASTOS_NAMESPACE_END

#ifdef __cplusplus
extern "C" {
#endif
    _ELASTOS Int32 __cdecl _String_GetLength(const char *string,
        _ELASTOS Int32 nMaxLen);
    _ELASTOS Int32 __cdecl _String_EstimateWStringLength(const char *str);
    _ELASTOS Int32 __cdecl _String_Compare(const char *string1,
        const char *string2, _ELASTOS StringCase stringCase);
    char* __cdecl _String_Duplicate(const char *strSource);

	void __cdecl _String_Free(char * str);

    _ELASTOS Int32 __cdecl _String_ToInt32(const char *string);
    _ELASTOS Int64 __cdecl _String_ToInt64(const char *string);
    _ELASTOS Boolean __cdecl _String_ToBoolean(const char *string);
    _ELASTOS Double __cdecl _String_ToDouble(const char *string);

    _ELASTOS Int32 __cdecl _String_GetCharCount(const char *string);
    _ELASTOS Char32 __cdecl _String_GetChar(const char *string,
        _ELASTOS Int32 index);

    _ELASTOS Boolean __cdecl _String_Contains(const char *string,
        const char *substr, _ELASTOS StringCase stringCase);

    _ELASTOS Boolean __cdecl _String_StartWith(const char *string,
        const char *substr, _ELASTOS StringCase stringCase);
    _ELASTOS Boolean __cdecl _String_EndWith(const char *string,
        const char *substr, _ELASTOS StringCase stringCase);

    _ELASTOS Int32 __cdecl _String_IndexOf_Char8(const char *string, char ch,
        _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_IndexOf_AnyChar8(const char *string,
        const char* strCharSet, _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_IndexOf_Char(const char *string,
        _ELASTOS Char32 ch, _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_IndexOf_AnyChar(const char *string,
        _ELASTOS Char32 *strCharSet, _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_IndexOf_Substring(const char *string,
        const char *substr, _ELASTOS StringCase stringCase);

    _ELASTOS Int32 __cdecl _String_LastIndexOf_Char8(const char *string, char ch,
        _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_LastIndexOf_AnyChar8(const char *string,
        const char* strCharSet, _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_LastIndexOf_Char(const char *string,
        _ELASTOS Char32 ch, _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_LastIndexOf_AnyChar(const char *string,
        _ELASTOS Char32 *strCharSet, _ELASTOS StringCase stringCase);
    _ELASTOS Int32 __cdecl _String_LastIndexOf_Substring(const char *string,
        const char *substr, _ELASTOS StringCase stringCase);

    char* __cdecl _String_Substring_Buffer(const char *string, _ELASTOS Int32 start,
        _ELASTOS PCarQuintet pCq);
    char* __cdecl _String_Substring(const char *string, _ELASTOS Int32 start);
    char* __cdecl _String_Substring_Length_Buffer(const char *string,
        _ELASTOS Int32 start, _ELASTOS Int32 len, _ELASTOS PCarQuintet pCq);

    char* __cdecl _String_ToLowerCase(const char *string, _ELASTOS PCarQuintet pCq);
    char* __cdecl _String_ToUpperCase(const char *string,
        _ELASTOS PCarQuintet pCq);

    char* __cdecl _String_TrimStart(const char *string, _ELASTOS PCarQuintet pCq);

    char* __cdecl _String_TrimEnd(const char *string, _ELASTOS PCarQuintet pCq);
    char* __cdecl _String_Trim(const char *string, _ELASTOS PCarQuintet pCq);

    _ELASTOS Int32 __cdecl _String_ConvertString(const char *string, _ELASTOS PCarQuintet pCq);

    _ELASTOS PCarQuintet  __cdecl _StringBuf_Box_Init(_ELASTOS PCarQuintet pCq,
        char *str, _ELASTOS Int32 size, _ELASTOS Boolean bHeapAlloced);

    _ELASTOS Int32 _StringBuf_ToUnicode(_ELASTOS PChar16 u16str, const char *string,
        _ELASTOS Int32 count);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

_ELASTOS_NAMESPACE_BEGIN

class StringBuf;

/** @addtogroup CARTypesRef
  *   @{
  */
class String
{
public:
    // e.g., String as;
    String() : m_string(NULL) {}

//  This class accords with bitwise copy semantics, and needn't declare copy
//  contructor.
//  //e.g., String as(str);
//  String(const String& str) : m_string(str.m_string) {};

    // e.g., String as("Hello");
    String(const char* pch) : m_string(pch) {}

    Int32 GetLength(Int32 maxLen = -1) const { // e.g., as.Length(64);
        return _String_GetLength(m_string, maxLen);
    }

    Int32 Compare(const String& str, StringCase stringCase = StringCase_Sensitive) const { //e.g., as.Compare(str);
        return _String_Compare(m_string, str.m_string, stringCase);
    }

    Boolean IsNull() const {  // e.g., if (str.IsNull()) {...} or Boolean b = str.IsNull();
        return m_string == NULL;
    }

    Boolean IsEmpty() const {
        assert(m_string);
        return m_string[0] == '\0';
    }

    Boolean IsNullOrEmpty() const {
        return (m_string == NULL || m_string[0] == '\0');
    }

    Int32 ToInt32() const {
        return _String_ToInt32(m_string);
    }

    Int64 ToInt64() const {
        return _String_ToInt64(m_string);
    }

    Boolean ToBoolean() const {
        return _String_ToBoolean(m_string);
    }

    Double ToDouble() const {
        return _String_ToDouble(m_string);
    }

    Int32 GetCharCount() const {
        return _String_GetCharCount(m_string);
    }

    Char32 GetChar(Int32 index) const {
        return _String_GetChar(m_string, index);
    }

    //---- Contains ----
    Boolean Contains(const String&  substr, StringCase stringCase = StringCase_Sensitive) const {
        return _String_Contains(m_string, substr, stringCase);
    }

    Boolean StartWith(const String&  substr,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_StartWith(m_string, substr, stringCase);
    }

    Boolean EndWith(const String& substr,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_EndWith(m_string, substr, stringCase);
    }

    //---- IndexOf ----
    Int32 IndexOf(Char8 ch, StringCase stringCase = StringCase_Sensitive) const {
        return _String_IndexOf_Char8(m_string, ch, stringCase);
    }

    Int32 IndexOfAny(const String& strCharSet,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_IndexOf_AnyChar8(m_string, strCharSet, stringCase);
    }

    Int32 IndexOfChar(Char32 ch, StringCase stringCase  = StringCase_Sensitive) const {
        return _String_IndexOf_Char(m_string, ch, stringCase);
    }

    Int32 IndexOfAnyChar(Char32 *strCharSet,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_IndexOf_AnyChar(m_string, strCharSet, stringCase);
    }

    Int32 IndexOf(const String& str, StringCase stringCase  = StringCase_Sensitive) const {
        return _String_IndexOf_Substring(m_string, str, stringCase);
    }

    //---- LastIndexOf ----
    Int32 LastIndexOf(Char8 ch,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_LastIndexOf_Char8(m_string, ch, stringCase);
    }

    Int32 LastIndexOfAny(const String& strCharSet,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_LastIndexOf_AnyChar8(m_string, strCharSet, stringCase);
    }

    Int32 LastIndexOfChar(Char32 ch, StringCase stringCase  = StringCase_Sensitive) const {
        return _String_LastIndexOf_Char(m_string, ch, stringCase);
    }

    Int32 LastIndexOfAnyChar(Char32 *strCharSet,
            StringCase stringCase = StringCase_Sensitive) const {
        return _String_LastIndexOf_AnyChar(m_string, strCharSet,
            stringCase);
    }

    Int32 LastIndexOf(const String& str, StringCase stringCase  = StringCase_Sensitive) const {
        return _String_LastIndexOf_Substring(m_string, str, stringCase);
    }

    //---- Substring ----
    String Substring(Int32 start, StringBuf& sub) {
        return _String_Substring_Buffer(m_string, start,
            (PCarQuintet)&sub);
    }

    String Substring(Int32 start) {
        return _String_Substring(m_string, start);
    }

    String Substring(Int32 start, Int32 len, StringBuf& sub) {
        return _String_Substring_Length_Buffer(m_string, start, len,
            (PCarQuintet)&sub);
    }

    //---- ToLowerCase ----
    String ToLowerCase(StringBuf& lowser) {
        return _String_ToLowerCase(m_string, (PCarQuintet)&lowser);
    }

    //---- ToUpperCase ----
    String ToUpperCase(StringBuf& upper) {
        return _String_ToUpperCase(m_string, (PCarQuintet)&upper);
    }

    //---- TrimStart ----
    String TrimStart(StringBuf& str) const {
        return _String_TrimStart(m_string, (PCarQuintet)&str);
    }

    //---- TrimEnd ----
    String TrimEnd(StringBuf& str) const {
        return _String_TrimEnd(m_string, (PCarQuintet)&str);
    }

    //---- Trim ----
    String Trim(StringBuf& str) const {
        return _String_Trim(m_string, (PCarQuintet)&str);
    }

    operator const char*() const
    {  //  for 3rd party API such as foo(char* pch);
        return (char *)m_string;
    }

    void operator=(const String& str) { // e.g., str1 = str2;
        m_string = str.m_string;
    }

    void operator=(const StringBuf& asb) { // e.g., str = asb;
        m_string = (char *)((PCarQuintet)&asb)->m_pBuf;
    }

    void operator=(const char* pch) {  // e.g., str = "Hello";
        m_string = pch;
    }

#if 0
    const Char8 operator[](Int32 idx) const {
        assert(idx >= 0);
        return m_string[idx];
    }
#endif

    static String Duplicate(const String& strSource) {
        return _String_Duplicate(strSource);
    }

    static void Free(String& str) {
        _String_Free((char *)str.m_string);
    }

    Char16 *ToUnicode(Char16 *u16str, Int32 count) {
        _StringBuf_ToUnicode(u16str, m_string, count);
        return u16str;
    }

protected:
    void operator==(const char *) {}
    void operator!=(const char *) {}
    void operator!() {}
    void operator*() {}

    void operator+=(const char *) {}
    void operator+(const char *) {}
    void operator+=(const int) {}
    void operator-=(const int) {}
    void operator+(const int) {}
    void operator-(const int) {}

    const char* m_string;
};
/** @} */

_ELASTOS_NAMESPACE_END

#else //!__cplusplus

typedef const char* String;

#endif //__cplusplus

#endif //__EZSTRING_H__
