//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __EL__MALLOC_H__
#define __EL__MALLOC_H__

#include <el_types.h>
#include <el_stddef.h>

#ifdef  __cplusplus
extern "C" {
#endif

void * __cdecl malloc(size_t);
void   __cdecl free(void *);
void * __cdecl realloc(void *, size_t);

#if defined (_GNUC)
#define _alloca __builtin_alloca
#else
void *  __cdecl _alloca(size_t);
#endif

#ifdef  __cplusplus
}
#endif

#endif //__MALLOC_H__
