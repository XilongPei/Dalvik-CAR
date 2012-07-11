//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __EL__STDDEF_H__
#define __EL__STDDEF_H__

#ifndef _PTRDIFF_T_
#define _PTRDIFF_T_
typedef int ptrdiff_t;
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else  /* __cplusplus */
#define NULL    ((void *)0)
#endif  /* __cplusplus */
#endif  /* NULL */

// mayq, add, to use the second branch
#define _GNUC

#ifdef _GNUC
typedef long long __int64;   // gnu c does not know __int64
typedef unsigned long long __uint64;
#else
typedef unsigned __int64 __uint64;
#endif // _GNUC

#if defined(_GNUC) && defined(_arm) && (__GNUC__ < 4)
typedef unsigned long size_t;
#else
typedef unsigned int size_t;
#endif

#if !defined(__cplusplus)
#if defined(_GNUC) && defined(_mips)
typedef unsigned int wchar_t;
#else
typedef unsigned short wchar_t;
#endif // defined(_GNUC) && defined(
#endif // !defined(__cplusplus)

#ifdef _EVC
typedef unsigned short wchar_t;
#endif

//#define offsetof(type, member)  ((size_t)&(((type *)1)->member) - 1)

#endif  //__STDDEF_H__
