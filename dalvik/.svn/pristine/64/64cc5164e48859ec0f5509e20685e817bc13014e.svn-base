//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __EL__ASSERT_H__
#define __EL__ASSERT_H__

#undef  assert

#if defined(_DEBUG)

#ifdef __cplusplus
extern "C" {
#endif

void __cdecl _assert(const char *exp, const char *fn, int ln);

#ifdef __cplusplus
}
#endif

#define assert(exp) ((exp) ? (void)0 : _assert(#exp, __FILE__, __LINE__))

#else

#define assert(exp) ((void) 0)

#endif // _DEBUG

#endif //__ASSERT_H__
