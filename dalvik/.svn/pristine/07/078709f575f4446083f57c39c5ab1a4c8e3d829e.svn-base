//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __EL__STRING_H__
#define __EL__STRING_H__

#include <el_types.h>
#include <el_stddef.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef STRSAFE_NO_DEPRECATE

// mayq, compiler can't find __cdecl, we define it
#define __cdecl

char *      __cdecl strcat(char *, const char *);
char *      __cdecl strcpy(char *, const char *);
char *      __cdecl strncat(char *, const char *, size_t);
char *      __cdecl strncpy(char *, const char *, size_t);
size_t      __cdecl strlen(const char *);
wchar_t *   __cdecl wcscat(wchar_t *, const wchar_t *);
wchar_t *   __cdecl wcscpy(wchar_t *, const wchar_t *);
wchar_t *   __cdecl wcsncpy(wchar_t *, const wchar_t *, size_t);
wchar_t *   __cdecl wcsncat(wchar_t *, const wchar_t *, size_t);
#endif

void *      __cdecl _memccpy(void *, const void *, int, unsigned int);
int         __cdecl _memicmp(const void *, const void *, unsigned int);
char *      __cdecl _strset(char *, int);
wchar_t *   __cdecl _wcsset(wchar_t *, int);
void *      __cdecl memchr(const void *, int, size_t);
void *      __cdecl memmove(void *, const void *, size_t);
char *      __cdecl _strdup(const char *);
wchar_t *   __cdecl _wcsdup(const wchar_t *);
int         __cdecl _stricmp(const char *, const char *);
int         __cdecl _wcsicmp(const wchar_t *, const wchar_t *);
wchar_t *   __cdecl wcschr(const wchar_t *, wchar_t);
int         __cdecl wcscmp(const wchar_t *, const wchar_t *);
size_t      __cdecl wcslen(const wchar_t *);
int         __cdecl wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t *   __cdecl wcsstr(const wchar_t *, const wchar_t *);
int         __cdecl _strnicmp(const char *, const char *, size_t);
int         __cdecl _wcsnicmp(const wchar_t*, const wchar_t*, size_t);
char *      __cdecl _strlwr(char *);
wchar_t *   __cdecl _wcslwr(wchar_t *);
char *      __cdecl _strupr(char *);
wchar_t *   __cdecl _wcsupr(wchar_t *);
wchar_t *   __cdecl wcsrchr(const wchar_t *, wchar_t);

char *      __cdecl strchr(const char *, int);
char *      __cdecl strrchr(const char *, int);
int         __cdecl strncmp(const char *, const char *, size_t);
size_t      __cdecl strspn(const char *, const char *);
char *      __cdecl strpbrk(const char *, const char *);
wchar_t *   __cdecl wcspbrk(const wchar_t *, const wchar_t *);
char *      __cdecl strstr(const char *, const char *);
char *      __cdecl strtok(char *, const char *);
wchar_t *   __cdecl wcstok(wchar_t *, const wchar_t *, wchar_t **);
size_t      __cdecl strcspn(const char *, const char *);
int         __cdecl strcoll(const char *, const char *);
int         __cdecl wcscoll(const wchar_t *, const wchar_t *);
size_t      __cdecl strxfrm(char *, const char *, size_t);

/* Compiler intrinsics */
int         __cdecl memcmp(const void *, const void *, size_t);
void *      __cdecl memcpy(void *, const void *, size_t);
void *      __cdecl memset(void *, int, size_t);

size_t      __cdecl strnlen(const char *, size_t);
int         __cdecl strcmp(const char *, const char *);

char*       __cdecl strerror(int);
char*       __cdecl _strerror(const char *);
wchar_t*    __cdecl _wcserror(int);
wchar_t*    __cdecl __wcserror(const wchar_t *);

int         __cdecl _stricoll(const char *, const char *);
int         __cdecl _wcsicoll(const wchar_t *, const wchar_t *);

//POSIX
void *      __cdecl memccpy(void *, const void *, int, unsigned int);
int         __cdecl memicmp(const void *, const void *, unsigned int);
char *      __cdecl strdup(const char *);
wchar_t *   __cdecl wcsdup(wchar_t *);
int         __cdecl stricmp(const char *, const char *);
int         __cdecl wcsicmp(const wchar_t *, const wchar_t *);
int         __cdecl strnicmp(const char *, const char *, size_t);
int         __cdecl wcsnicmp(const wchar_t*, const wchar_t*, size_t);
char *      __cdecl strlwr(char *);
wchar_t *   __cdecl wcslwr(wchar_t *);
char *      __cdecl strupr(char *);
wchar_t *   __cdecl wcsupr(wchar_t *);
char *      __cdecl strset(char *, int);
char *      __cdecl wcsset(char *, int);

//
int         __cdecl strncasecmp(const char *, const char *, size_t);
int         __cdecl wcsncasecmp(const wchar_t*, const wchar_t*, size_t);

#ifndef _GNUC
#pragma function(_strset, strcmp, memcpy, memset, strcat, strcpy, strlen)
#pragma function(memcmp)
#endif

#ifdef _EVC
#pragma function(_wcsset, wcscat, wcscmp, wcsncmp, wcsncpy, memchr)
#pragma function(strncmp, strncpy, wcscpy, wcslen)
#endif

#ifdef  __cplusplus
}
#endif

#endif // __STRING_H__
