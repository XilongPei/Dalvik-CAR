//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
// mayq remove, redundant, including guard below is enough
/*#if _MSC_VER > 1000
#pragma once
#endif*/

#if !defined(__ELASTOS_H__)
#define __ELASTOS_H__

// mayq add
#define _GNUC
#define _arm
#define _UNDEFDLLEXP
#define _mips
#undef new
#undef delete
// mayq end

#include <eltypes.h>

#ifdef __cplusplus
#include <interlocked.h>
EXTERN_C _ELASTOS ECode __cdecl ElastosMain(
                const _ELASTOS BufferOf<_ELASTOS String>& argv);
#else // __cplusplus
EXTERN_C ECode __cdecl ElastosMain(
                const _ELASTOS PCarQuintet argv);
#endif // __cplusplus

#if !defined(__ELAPI_H__) && !defined(__CAR_ELASTOSCORE_H__) && !defined(__CAR_ELASYS_H__)
#include <elapi.h>
#include <elasysapi.h>
#include <evedelegate.h>
#ifdef __cplusplus
#include <critsec.h>
#endif // __cplusplus
#endif // !__CAR_ELASYS_H__ && !__EZAPI_H__

// mayq, add
#include <elapiwrap.h>

#endif  // __ELASTOS_H__
