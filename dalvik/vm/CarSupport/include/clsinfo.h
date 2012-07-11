//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _CLSINFO_H_
#define _CLSINFO_H_

#include <elatypes.h>

#ifndef _UNDEFDLLEXP
#define _UNDEFDLLEXP
#endif

#ifndef DLLEXP 
#ifdef _UNDEFDLLEXP
#define DLLEXP
#else
#define DLLEXP __declspec(dllimport)
#endif
#endif

// mayq, compiler can't find DLLEXP, we define it here
//#define DLLEXP

EXTERN_C DLLEXP const _ELASTOS EMuid ECLSID_ClassInfo;
// { 0x4CDBF5FC,0xD030,0x4583,{ 0xAE,0xCD,0xA2,0x6E,0x95,0xB3,0x02,0x6F }

typedef _ELASTOS UInt32  CIBaseType;
//+------------+-------------------------------+----------------------+-------+---------------------------------------------------------------+
//|  31 ~ 16   |   15  |  14   |  13   |  12   |  11   |   10  |   9  |  8    |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
//+------------+-------------------------------+----------------------+-------+---------------------------------------------------------------+
//| type size  |            reserved           |    attributes        |pointer|                         type                                  |
//+------------+-------------------------------+----------------------+-------+---------------------------------------------------------------+
//                                             |retval |  in   |  out |
//                                             +-------+-------+------+
// attributes: Attribute of parameter, i.e. [in] [out] [retval] & return.
// pointer: Identify if a type is pointer.
// type: Type tag to identify a system type. invalid for retval, which
//     is always ECode.
// type size:   size of type, especially for base type or custom struct
//

// NOTE: please update macro BT_IS_VALID when adding new types
//
#define BT_ATTR_RETVAL          0x00000800
#define BT_ATTR_IN              0x00000400
#define BT_ATTR_OUT             0x00000200
#define BT_ATTR_INOUT           0x00000600
#define BT_ATTR_RET             0x00000000

#define BT_TYPE_NONE            0x00000000

#define BT_TYPE_UINT8           0x00000001
#define BT_TYPE_UINT16          0x00000002
#define BT_TYPE_UINT32          0x00000003
#define BT_TYPE_UINT64          0x00000004
#define BT_TYPE_EMUID           0x00000005
#define BT_TYPE_ARRAYOF         0x00000007
#define BT_TYPE_BUFFEROF        0x00000008
#define BT_TYPE_DELEGATE        0x00000009
#define BT_TYPE_STRINGBUF       0x0000000A
#define BT_TYPE_INTERFACE       0x0000000B
#define BT_TYPE_EGUID           0x0000000C
#define BT_TYPE_STRING          0x0000000D
#define BT_TYPE_STRUCT          0x0000000E

#define BT_TYPE_POINTER         0x00000100

#define BT_TYPE_PUINT8          (BT_TYPE_UINT8  | BT_TYPE_POINTER)
#define BT_TYPE_PUINT16         (BT_TYPE_UINT16 | BT_TYPE_POINTER)
#define BT_TYPE_PUINT32         (BT_TYPE_UINT32 | BT_TYPE_POINTER)
#define BT_TYPE_PUINT64         (BT_TYPE_UINT64 | BT_TYPE_POINTER)
#define BT_TYPE_PEMUID          (BT_TYPE_EMUID  | BT_TYPE_POINTER)
#define BT_TYPE_PEGUID          (BT_TYPE_EGUID  | BT_TYPE_POINTER)
#define BT_TYPE_PBUFFEROF       (BT_TYPE_BUFFEROF | BT_TYPE_POINTER)
#define BT_TYPE_PDELEGATE       (BT_TYPE_DELEGATE | BT_TYPE_POINTER)
#define BT_TYPE_PINTERFACE      (BT_TYPE_INTERFACE | BT_TYPE_POINTER)

#define BT_TYPE_PSTRUCT         (BT_TYPE_STRUCT | BT_TYPE_POINTER)

#define BT_ATTR(a)      (a & 0x00000E00)
#define BT_TYPE(a)      (a & 0x000001FF)

#define BT_TYPE_SIZE(bt)        (bt >> 16)

/*
 * Description  : BT_IS_XX(a) is utilized to check whether the variable "a" is XX type.
 */
#if 1   /* Start */
#define BT_IS_IN(a)     (0 != (a & BT_ATTR_IN))
#define BT_IS_OUT(a)    (0 != (a & BT_ATTR_OUT))
#define BT_IS_INOUT(a)  (BT_IS_IN(a) && BT_IS_OUT(a))
#define BT_IS_RETVAL(a) (0 != (a & BT_ATTR_RETVAL))
#else
#define BT_IS_IN(a)     (BT_ATTR(a) == BT_ATTR_IN)
#define BT_IS_OUT(a)    (BT_ATTR(a) == BT_ATTR_OUT)
#define BT_IS_INOUT(a)  (BT_ATTR(a) == BT_ATTR_INOUT)
#define BT_IS_RETVAL(a) (BT_ATTR(a) == BT_ATTR_RETVAL)
#endif  /* End */

#define BT_IS_RET(a)    (BT_ATTR(a) == BT_ATTR_RET)
#define BT_IS_ARG(a)    (!BT_IS_RET(a))

#define BT_IS_VALID_ARG(a) \
       (BT_IS_ARG(a) && \
           ((BT_TYPE(a) >= BT_TYPE_UINT8 \
                && BT_TYPE(a) <= BT_TYPE_STRUCT) \
            || (BT_TYPE(a) >= BT_TYPE_PUINT8 \
                && BT_TYPE(a) <= BT_TYPE_PSTRUCT)))

#define BT_IS_VALID_RET(a)  \
    (BT_IS_RET(a) && BT_TYPE(a) == BT_TYPE_UINT32)

/** @addtogroup SystemRef
  *   @{
  */
typedef struct _CIMethodEntry {
    _ELASTOS UInt8                   paramNum;
    _ELASTOS UInt8                   result;         // OBSOLETE. to be removed
    _ELASTOS UInt8                   reserved1; // the  highest digit for mark [in] interface
                                       // the next for [out] interface
                                       // the others is the stack length
    CIBaseType              *params;        // size_is(paramNum)
}   CIMethodEntry;

typedef struct _CIInterfaceEntry {
    _ELASTOS UInt16                  methodNumMinus3;    // exclude IUnknown's 3 methods
    CIMethodEntry           *methods;       // size_is(methodNumMinus3)
    _ELASTOS InterfaceID             iid;
}   CIInterfaceEntry;

typedef struct _CIClassEntry {
    _ELASTOS  EMuid         clsid;
    char                    *pszUunm;
    _ELASTOS UInt16                  interfaceNum;
    CIInterfaceEntry        **interfaces;   // size_is(interfaceNum)
    _ELASTOS UInt8                   *pVirTable;     // size_is(interfaceNum)
}   CIClassEntry;

typedef struct _CIClassInfo {
    int                     totalSize;
    int                     classNum;
    int                     interfaceNum;
    CIClassEntry            *classDir;      // size_is(classNum)
    CIInterfaceEntry        *interfaceDir;  // size_is(interfaceNum)
    char                    szUunm[1];
}   CIClassInfo;

typedef struct _CIClassInfoNode _CIClassInfoNode;
struct _CIClassInfoNode
{
    CIClassInfo *m_pClsInfo;
    _CIClassInfoNode *m_pNext;
};

typedef struct _CIClassInfoNode CIClassInfoNode;
/** @} */

extern _ELASTOS ECode InitServerClassInfo();

extern _ELASTOS ECode RegisterServerClassInfo(
        /* [in] */ const CIClassInfo *pClassInfo);

extern _ELASTOS ECode LookupServerClassEntry(
        /* [in] */ _ELASTOS REMuid rclsid,
        /* [out] */ const CIClassEntry **pClassInfo);

extern _ELASTOS ECode UnregisterServerClassInfos();

#endif // _CLSINFO_H_
