//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#ifndef __CAR_UUID_H__
#define __CAR_UUID_H__

#ifndef DLLEXP
#ifdef _UNDEFDLLEXP
#define DLLEXP
#else
#define DLLEXP __declspec(dllimport)
#endif
#endif

EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_METADATA_INFO;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_CALLBACK_CONNECTOR;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_SUPER_CALLBACK_CONNECTOR;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_CALLBACK_TRIGGER;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_GENERIC_INFO;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_MUTEX_INFO;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_NEXT_ASPECT;
EXTERN_C DLLEXP const _ELASTOS InterfaceID EIID_SUPER_OBJECT;

#if !defined(_openkode)
EXTERN_C int    __cdecl _Impl_Memcmp(const void *, const void *, size_t);
EXTERN_C int    __cdecl _Impl_Strcmp(const char* , const char* );
#else
#define _Impl_Memcmp memcmp
#define _Impl_Strcmp strcmp
#endif

#ifdef __cplusplus

#if defined(_arm) || defined(_mips)

INLINE _ELASTOS Boolean IsEqualEMuid(_ELASTOS REMuid r1, _ELASTOS REMuid r2)
{
    return (0 == _Impl_Memcmp(&r1, &r2, sizeof(_ELASTOS EMuid)));
}

#else // !_arm && !_mips

INLINE _ELASTOS Boolean IsEqualEMuid(_ELASTOS REMuid r1, _ELASTOS REMuid r2)
{
    return (((_ELASTOS UInt32*)&r1)[0] == ((_ELASTOS UInt32*)&r2)[0] &&
            ((_ELASTOS UInt32*)&r1)[1] == ((_ELASTOS UInt32*)&r2)[1] &&
            ((_ELASTOS UInt32*)&r1)[2] == ((_ELASTOS UInt32*)&r2)[2] &&
            ((_ELASTOS UInt32*)&r1)[3] == ((_ELASTOS UInt32*)&r2)[3]);
}

#endif // _arm || _mips

INLINE _ELASTOS Boolean operator ==(_ELASTOS REMuid rguid1, _ELASTOS REMuid rguid2)
{
    return IsEqualEMuid(rguid1, rguid2);
}

INLINE _ELASTOS Boolean operator ==(_ELASTOS REMuid rguid, _ELASTOS RClassID rclsid)
{
    return IsEqualEMuid(rguid, rclsid.clsid);
}

INLINE _ELASTOS Boolean operator ==(_ELASTOS RClassID rclsid, _ELASTOS REMuid rguid)
{
    return IsEqualEMuid(rguid, rclsid.clsid);
}

INLINE _ELASTOS Boolean operator !=(_ELASTOS REMuid rguid1, _ELASTOS REMuid rguid2)
{
    return !IsEqualEMuid(rguid1, rguid2);
}

INLINE _ELASTOS Boolean operator !=(_ELASTOS REMuid rguid, _ELASTOS RClassID rclsid)
{
    return !IsEqualEMuid(rguid, rclsid.clsid);
}

INLINE _ELASTOS Boolean operator !=(_ELASTOS RClassID rclsid, _ELASTOS REMuid rguid)
{
    return !IsEqualEMuid(rguid, rclsid.clsid);
}

#else  // !__cplusplus

#define IsEqualEMuid(rguid1, rguid2) (!_Impl_Memcmp(rguid1, rguid2, sizeof(_ELASTOS EMuid)))

#endif // __cplusplus

#define IsEqualIID(riid1, riid2)        IsEqualEMuid(riid1, riid2)
#define IsEqualCLSID(rclsid1, rclsid2)  IsEqualEMuid(rclsid1, rclsid2)

#ifdef __cplusplus

INLINE _ELASTOS Boolean IsEqualUunm(const char *pUunm1, const char *pUunm2)
{
    return !_Impl_Strcmp(pUunm1, pUunm2);
}

INLINE _ELASTOS Boolean IsEqualClassId(_ELASTOS RClassID r1, _ELASTOS RClassID r2)
{
    return IsEqualEMuid(r1.clsid, r2.clsid) && IsEqualUunm(r1.pUunm, r2.pUunm);
}

INLINE _ELASTOS Boolean operator ==(_ELASTOS RClassID r1, _ELASTOS RClassID r2)
{
    return IsEqualClassId(r1, r2);
}

INLINE _ELASTOS Boolean operator !=(_ELASTOS RClassID r1, _ELASTOS RClassID r2)
{
    return !IsEqualClassId(r1, r2);
}

#else // !__cplusplus

#define IsEqualUunm(u1, u2) \
    !_Impl_Strcmp(u1, u2)

#define IsEqualClassId(r1, r2) \
    (IsEqualEMuid(&r1.clsid, &r2.clsid) && IsEqualUunm(r1.pUunm, r2.pUunm))

#endif // __cplusplus

#endif // __CAR_UUID_H__
