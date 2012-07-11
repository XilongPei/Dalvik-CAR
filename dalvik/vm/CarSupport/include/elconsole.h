//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#ifndef __EZCONSOLE_H__
#define __EZCONSOLE_H__

#include <eltypes.h>

#ifdef __cplusplus

#define STDIN  0
#define STDOUT 1
#define STDERR 2

extern "C" {
    _ELASTOS ECode __cdecl _Console_Write_String(_ELASTOS String s);
    _ELASTOS ECode __cdecl _Console_WriteLine_String(_ELASTOS String s);
    _ELASTOS Int32 __cdecl _Console_Read();
    _ELASTOS ECode __cdecl _Console_ReadLine_String(_ELASTOS StringBuf *psBuf);
    _ELASTOS ECode __cdecl _Console_SetIo_String(_ELASTOS UInt32 fd, _ELASTOS String s);
    IAbsoluteIO* __cdecl _Console_GetIo_Interface(_ELASTOS UInt32 fd);
}

#define __CONSOLE_WRITE_MODE(WrtieMode) \
             StringBuf_<64> s; \
             s.Append(value); \
             return WrtieMode(s);

#define __CONSOLE_WRITE_MODE_WITH_FMT(WrtieMode, fmt) \
             StringBuf_<64> s; \
             s.Append(value, fmt); \
             return WrtieMode(s);

_ELASTOS_NAMESPACE_BEGIN

class CConsole {
public:
    static ECode WriteLine() {
        return _Console_Write_String("\n");
    }

//    static ECode WriteLine(Boolean value) {
//        if (value) {
//            return _Console_Write_String("True\n");
//        }
//        else {
//            return _Console_Write_String("False\n");
//        }
//    }

    static ECode WriteLine(Char8 value) {
        __CONSOLE_WRITE_MODE(_Console_WriteLine_String);
    }

    static ECode WriteLine(Char16 value) {
        __CONSOLE_WRITE_MODE(_Console_WriteLine_String);
    }

    static ECode WriteLine(Byte value) {
        __CONSOLE_WRITE_MODE(_Console_WriteLine_String);
    }

    static ECode WriteLine(Int8 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_WriteLine_String, fmt);
    }

    static ECode WriteLine(Int16 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_WriteLine_String, fmt);
    }

    static ECode WriteLine(Int32 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_WriteLine_String, fmt);
    }

    static ECode WriteLine(Int64 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_WriteLine_String, fmt);
    }

    static ECode WriteLine(Float value) {
        __CONSOLE_WRITE_MODE(_Console_WriteLine_String);
    }

    static ECode WriteLine(Double value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_WriteLine_String, fmt);
    }

    static ECode WriteLine(String s) {
        return _Console_WriteLine_String(s);
    }

//------------------------------------------------------------------------------

//    static ECode Write(Boolean value) {
//        if (value) {
//            return _Console_Write_String("True");
//        }
//        else {
//            return _Console_Write_String("False");
//        }
//    }

    static ECode Write(Char8 value) {
        __CONSOLE_WRITE_MODE(_Console_Write_String);
    }

    static ECode Write(Char16 value) {
        __CONSOLE_WRITE_MODE(_Console_Write_String);
    }

    static ECode Write(Byte value) {
        __CONSOLE_WRITE_MODE(_Console_Write_String);
    }

    static ECode Write(Int8 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_Write_String, fmt);
    }

    static ECode Write(Int16 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_Write_String, fmt);
    }

    static ECode Write(Int32 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_Write_String, fmt);
    }

    static ECode Write(Int64 value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_Write_String, fmt);
    }

    static ECode Write(Float value) {
        __CONSOLE_WRITE_MODE(_Console_Write_String);
    }

    static ECode Write(Double value, Flags32 fmt = 0) {
        __CONSOLE_WRITE_MODE_WITH_FMT(_Console_Write_String, fmt);
    }

    static ECode Write(String s) {
         return _Console_Write_String(s);
    }

    static Int32 Read() {
         return _Console_Read();
    }

    static ECode ReadLine(StringBuf *psBuf) {
         return _Console_ReadLine_String(psBuf);
    }

    static ECode SetIn(String s) {
        return _Console_SetIo_String(STDIN, s);
    }

    static ECode SetOut(String s) {
        return _Console_SetIo_String(STDOUT, s);
    }

    static ECode SetError(String s) {
        return _Console_SetIo_String(STDERR, s);
    }

    static IAbsoluteIO* GetIn() {
        return _Console_GetIo_Interface(STDIN);
    }

    static IAbsoluteIO* GetOut() {
        return _Console_GetIo_Interface(STDOUT);
    }

    static IAbsoluteIO* GetError() {
        return _Console_GetIo_Interface(STDERR);
    }
};

_ELASTOS_NAMESPACE_END

#endif //__cplusplus

#endif //__EZCONSOLE_H__
