//==========================================================================
// Copyright (c) 2000-2008,  Elastos, Inc.  All Rights Reserved.
//==========================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __CARARRAY_H__
#define __CARARRAY_H__

#include <elatypes.h>
#include <elaobj.h>

_ELASTOS_NAMESPACE_BEGIN

/** @addtogroup BaseTypesRef
  *   @{
  */
typedef enum _CarQuintetFlag
{
    CarQuintetFlag_HeapAlloced      = 0x00010000,

    CarQuintetFlag_Type_Unknown     = 0,

    CarQuintetFlag_Type_Int8        = 1,
    CarQuintetFlag_Type_Int16       = 2,
    CarQuintetFlag_Type_Int32       = 3,
    CarQuintetFlag_Type_Int64       = 4,

    CarQuintetFlag_Type_Byte        = 5,
    CarQuintetFlag_Type_UInt8       = CarQuintetFlag_Type_Byte,
    CarQuintetFlag_Type_UInt16      = 6,
    CarQuintetFlag_Type_UInt32      = 7,
    CarQuintetFlag_Type_UInt64      = 8,

    CarQuintetFlag_Type_Boolean     = CarQuintetFlag_Type_Byte,
    CarQuintetFlag_Type_Float       = 9,
    CarQuintetFlag_Type_Double      = 10,

    CarQuintetFlag_Type_Char8       = 11,
    CarQuintetFlag_Type_Char16      = CarQuintetFlag_Type_UInt16,
    CarQuintetFlag_Type_Char32      = CarQuintetFlag_Type_UInt32,
    CarQuintetFlag_Type_String      = 12,

    CarQuintetFlag_Type_EMuid       = 13,
    CarQuintetFlag_Type_EGuid       = 14,
    CarQuintetFlag_Type_ECode       = CarQuintetFlag_Type_Int32,
    CarQuintetFlag_Type_Enum        = CarQuintetFlag_Type_Int32,
    CarQuintetFlag_Type_Struct      = 15,
    CarQuintetFlag_Type_IObject     = 16,
    CarQuintetFlag_Type_Point       = 17,

    CarQuintetFlag_TypeMask         = 0x0000ffff
} CarQuintetFlag;

typedef Int32 CarQuintetFlags;
typedef Int32 CarQuintetLocks;

typedef struct CarQuintet
{
    CarQuintetFlags m_flags;
    CarQuintetLocks m_reserve;
    MemorySize      m_used;
    MemorySize      m_size;
    PVoid           m_pBuf;
} CarQuintet, *PCarQuintet, *PCARQUINTET;
/** @} */

_ELASTOS_NAMESPACE_END

#ifdef __cplusplus
extern "C" {
#endif
    _ELASTOS PCarQuintet __cdecl _CarQuintet_Init(_ELASTOS PCarQuintet pCq,
            _ELASTOS PVoid pBuf, _ELASTOS Int32 size, _ELASTOS Int32 used,
            _ELASTOS CarQuintetFlags flags);
    _ELASTOS PCarQuintet __cdecl _CarQuintet_Clone(const _ELASTOS PCarQuintet pCq);
    void __cdecl _CarQuintet_Free(_ELASTOS PCarQuintet pCq);

    _ELASTOS Int32 __cdecl _ArrayOf_Copy(_ELASTOS PCarQuintet pcqDst,
            const _ELASTOS CarQuintet* pcqSrc);
    _ELASTOS Int32 __cdecl _ArrayOf_CopyEx(_ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* p, _ELASTOS Int32 n);
    _ELASTOS PCarQuintet __cdecl _ArrayOf_Alloc(_ELASTOS Int32 size,
            _ELASTOS CarQuintetFlags flags);
    _ELASTOS PCarQuintet __cdecl _ArrayOf_Alloc_Box(_ELASTOS PVoid pBuf,
            _ELASTOS Int32 size, _ELASTOS CarQuintetFlags flags);
    _ELASTOS Int32 __cdecl _ArrayOf_Replace(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte p, _ELASTOS Int32 n);

    _ELASTOS Int32 __cdecl _BufferOf_Insert(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte pb, _ELASTOS MemorySize n);
    _ELASTOS Int32 __cdecl _BufferOf_Append(_ELASTOS PCarQuintet pCq,
            const _ELASTOS PByte p, _ELASTOS MemorySize n);
    _ELASTOS Int32 __cdecl _BufferOf_Replace(_ELASTOS PCarQuintet pCq,
            _ELASTOS Int32 offset, const _ELASTOS PByte p, _ELASTOS Int32 n);
    _ELASTOS Int32 __cdecl _BufferOf_Copy(_ELASTOS PCarQuintet pcqDst,
            const _ELASTOS CarQuintet* pcqSrc);
    _ELASTOS Int32 __cdecl _BufferOf_CopyEx(_ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* p, _ELASTOS Int32 n);
    _ELASTOS PCarQuintet __cdecl _BufferOf_Alloc(_ELASTOS Int32 size,
            _ELASTOS CarQuintetFlags flags);
    _ELASTOS PCarQuintet __cdecl _BufferOf_Alloc_Box(_ELASTOS PVoid pBuf,
            _ELASTOS Int32 capacity, _ELASTOS Int32 used,
            _ELASTOS CarQuintetFlags flags);

    void _MemoryBuf_SetByteValue(_ELASTOS PCarQuintet pCq, _ELASTOS Byte value);
    _ELASTOS Int32 _MemoryBuf_Compare(const _ELASTOS PCarQuintet pCq,
            const _ELASTOS Byte* pBuf, _ELASTOS Int32 count);

    _ELASTOS PCarQuintet __cdecl _CarQuintet_GetNullValue(
            _ELASTOS CarQuintetFlags flag);
#ifdef __cplusplus
}
#endif

//
//  Memory structure of ArrayOf:
//
//           ________
//          |  pBuf  |
//          |        v
//  +------------+   +------------------------+
//  | CarQuintet |   |  C Array Data          |
//  +------------+   +------------------------+
//  ^
//  |____ ArrayOf (m_pCq)
//
//

#ifdef __cplusplus

_ELASTOS_NAMESPACE_BEGIN

class String;

// NOTE1: MS CL compiler can't support function's template specialization well,
//   so only template class works.
// NOTE2: We shall emit a COMPILE-TIME error if user let ArrayOf
//   to contain a
//   non-automation type. There's an undefined variable in Type2Flag::Flag()'s
//   default implementation, which will emit the error. Also, we must deal
//   with illegal types at runtime.
//
template <class T> struct Type2Flag
{
    static Int32 Flag() {
        if (Conversion<T, IInterface *>::exists) {
            return CarQuintetFlag_Type_IObject;
        }
        else {
            return CarQuintetFlag_Type_Struct;
        }
    }
};

#define DECL_TYPE2FLAG_TMPL(type, flag) \
    template <> struct Type2Flag<type> { static Int32 Flag() \
    { return (flag); } }

DECL_TYPE2FLAG_TMPL(Int8,               CarQuintetFlag_Type_Int8);
DECL_TYPE2FLAG_TMPL(Int16,              CarQuintetFlag_Type_Int16);
DECL_TYPE2FLAG_TMPL(Int32,              CarQuintetFlag_Type_Int32);
DECL_TYPE2FLAG_TMPL(Int64,              CarQuintetFlag_Type_Int64);

DECL_TYPE2FLAG_TMPL(Byte,               CarQuintetFlag_Type_Byte);
DECL_TYPE2FLAG_TMPL(UInt16,             CarQuintetFlag_Type_UInt16);
DECL_TYPE2FLAG_TMPL(UInt32,             CarQuintetFlag_Type_UInt32);
DECL_TYPE2FLAG_TMPL(UInt64,             CarQuintetFlag_Type_UInt64);

DECL_TYPE2FLAG_TMPL(Float,              CarQuintetFlag_Type_Float);
DECL_TYPE2FLAG_TMPL(Double,             CarQuintetFlag_Type_Double);

DECL_TYPE2FLAG_TMPL(Char8,              CarQuintetFlag_Type_Char8);
//DECL_TYPE2FLAG_TMPL(Char16,             CarQuintetFlag_Type_Char16);
DECL_TYPE2FLAG_TMPL(String,             CarQuintetFlag_Type_String);

DECL_TYPE2FLAG_TMPL(EMuid,              CarQuintetFlag_Type_EMuid);
DECL_TYPE2FLAG_TMPL(EGuid,              CarQuintetFlag_Type_EGuid);
DECL_TYPE2FLAG_TMPL(IInterface *,       CarQuintetFlag_Type_IObject);

#define _MAX_CARQUINTET_SIZE_  (0x7FFFFFFF - sizeof(CarQuintet))


//---------------ArrayOf-----------------------------------------------------

template <class T>
class BufferOf;

/** @addtogroup CARTypesRef
  *   @{
  */
template <class T>
class ArrayOf : public CarQuintet
{
public:
    T* GetPayload() const {
        return (T*)m_pBuf;
    };

    operator PCarQuintet() {
        return this;
    }

    Int32 GetLength() const {
        return m_pBuf ? m_size / sizeof(T) : 0;
    }

    ArrayOf& Replace(Int32 offset, const T* pBuf, Int32 n) {
        _ArrayOf_Replace(this, offset * sizeof(T), (PByte)pBuf,
        n * sizeof(T));
        return *this;
    }

    ArrayOf& Copy(const ArrayOf<T> *pSrc) {
        _ArrayOf_Copy(this, pSrc);
        return *this;
    }

    ArrayOf& Copy(const T* pBuf, Int32 n) {
        _ArrayOf_CopyEx(this, (Byte *)pBuf, n * sizeof(T));
        return *this;
    }

    ArrayOf<T> *Clone() const {
        return (ArrayOf<T> *)_CarQuintet_Clone((const PCarQuintet)this);
    }

    T& operator[](Int32 index) {
        assert(m_pBuf && index >= 0 && index < GetLength());
        return ((T*)(m_pBuf))[index];
    }

    const T& operator[](Int32 index) const {
        assert(m_pBuf && index >= 0 && index < GetLength());
        return ((T*)(m_pBuf))[index];
    }

    operator const BufferOf<T>&() const {
        return *(const BufferOf<T>*)this;
    }

    static ArrayOf<T> *Alloc(Int32 capacity) {
        return (ArrayOf<T> *)_ArrayOf_Alloc(capacity * sizeof(T),
        Type2Flag<T>::Flag());
    }

    static ArrayOf<T> *Alloc(T *pBuf, Int32 capacity) {
        return (ArrayOf<T> *)_ArrayOf_Alloc_Box(
            pBuf, capacity * sizeof(T), Type2Flag<T>::Flag());
    }

    static void Free(ArrayOf<T> *pArray) {
        _CarQuintet_Free(pArray);
    }

    ArrayOf(T *pBuf, Int32 capacity) {
        _CarQuintet_Init(this, pBuf, capacity * sizeof(T),
                        capacity * sizeof(T), Type2Flag<T>::Flag());
    }

private:
    // prohibit 'new' operator
    void * operator new(size_t cb);
    ArrayOf() {}
    ArrayOf& operator = (const ArrayOf& buf) {}
    ArrayOf(const ArrayOf& buf) {}
};
/** @} */

/** @addtogroup BaseTypesRef
  *   @{
  */
template <class T, Int32 SIZE>
class ArrayOf_ : public ArrayOf<T>
{
public:
    ArrayOf_() : ArrayOf<T>(m_buf, SIZE)
    {
        if (Type2Flag<T>::Flag() != CarQuintetFlag_Type_Struct) {
            _MemoryBuf_SetByteValue(this, 0x0);
        }
    }

protected:
    T   m_buf[SIZE ? SIZE : 1];

private:
    // prohibit "=" operator
    ArrayOf_& operator = (const ArrayOf<T>& buf) {}
    ArrayOf_& operator = (const ArrayOf_& buf) {}
    ArrayOf_(const ArrayOf<T>& buf) {}
    ArrayOf_(const ArrayOf_& buf) {}
};
/** @} */

/** @addtogroup CARTypesRef
  *   @{
  */
//---------------BufferOf-----------------------------------------------------

template <class T>
class BufferOf : public CarQuintet
{
public:
    T* GetPayload() const {
        return (T*)m_pBuf;
    };

    operator PCarQuintet() {
        return this;
    }

    Int32 GetCapacity() const {
        return m_size / sizeof(T);
    }

    Int32 GetAvailableSpace() const {
        return (m_size - m_used) / sizeof(T);
    }

    Boolean IsNull() const {
        return m_pBuf == NULL;
    }

    Boolean IsEmpty() const {
        return m_used == 0;
    }

    Boolean IsNullOrEmpty() const {
        return (m_pBuf == NULL || m_used == 0);
    }

    Int32 SetUsed(Int32 used) {
        if (used < 0) {
            return -1;
        }
        used = MIN(used, GetCapacity());
        m_used = used * sizeof(T);
        return used;
    }

    Int32 GetUsed() const {
        return m_used / sizeof(T);
    }

    BufferOf& Insert(Int32 offset, const T* p, Int32 n) {
        _BufferOf_Insert(this, offset * sizeof(T), (PByte)p, n * sizeof(T));
        return *this;
    }

    BufferOf& Replace(Int32 offset, const T* pBuf, Int32 n) {
        _BufferOf_Replace(this, offset * sizeof(T), (PByte)pBuf,
        n * sizeof(T));
        return *this;
    }

    BufferOf& Append(T value) {
        _BufferOf_Append(this, (PByte)&value, sizeof(T));
        return *this;
    }

    BufferOf& Append(const T* pBuf, Int32 n) {
        _BufferOf_Append(this, (PByte)pBuf, n * sizeof(T));
        return *this;
    }

    BufferOf& Append(const BufferOf<T> *pSrc) {
        _BufferOf_Append(this, (PByte)pSrc->m_pBuf,
        pSrc->GetUsed() * sizeof(T));
        return *this;
    }

    BufferOf& Copy(const BufferOf<T> *pSrc) {
        _BufferOf_Copy(this, pSrc);
        return *this;
    }

    BufferOf& Copy(const T* pBuf, Int32 n) {
        _BufferOf_CopyEx(this, (Byte *)pBuf, n * sizeof(T));
        return *this;
    }

    BufferOf<T> *Clone() const {
        return (BufferOf<T> *)_CarQuintet_Clone((const PCarQuintet)this);
    }

    T& operator[](Int32 index) {
        assert(m_pBuf && index >= 0 && index < GetUsed());
        return ((T*)(m_pBuf))[index];
    }

    const T& operator[](Int32 index) const {
        assert(m_pBuf && index >= 0 && index < GetUsed());
        return ((T*)(m_pBuf))[index];
    }

    operator const ArrayOf<T>&() const {
        return *(const ArrayOf<T>*)this;
    }

    static BufferOf<T> *Alloc(Int32 capacity) {
        return (BufferOf<T> *)_BufferOf_Alloc(capacity * sizeof(T),
        Type2Flag<T>::Flag());
    }

    static BufferOf<T> *Alloc(T *pBuf, Int32 capacity, Int32 used) {
        assert(used <= capacity);
        return (BufferOf<T> *)_BufferOf_Alloc_Box(pBuf, capacity * sizeof(T),
            used * sizeof(T), Type2Flag<T>::Flag());
    }

    static BufferOf<T> *Alloc(T *pBuf, Int32 capacity) {
        return (BufferOf<T> *)_BufferOf_Alloc_Box(
            pBuf, capacity * sizeof(T),
            capacity * sizeof(T), Type2Flag<T>::Flag());
    }

    static void Free(BufferOf<T> *pArray) {
        _CarQuintet_Free(pArray);
    }

    BufferOf(T *pBuf, Int32 capacity, Int32 used) {
        assert(used <= capacity);
        _CarQuintet_Init(this, pBuf, capacity * sizeof(T),
                        used * sizeof(T), Type2Flag<T>::Flag());
    }

    BufferOf(T *pBuf, Int32 capacity) {
        _CarQuintet_Init(this, pBuf, capacity * sizeof(T),
                        capacity * sizeof(T), Type2Flag<T>::Flag());
    }

protected:
    // prohibit 'new' operator
    void * operator new(size_t cb);
    BufferOf() {}
    BufferOf& operator = (const BufferOf& buf) {}
    BufferOf(const BufferOf& buf) {}
};
/** @} */

/** @addtogroup BaseTypesRef
  *   @{
  */
template <class T, Int32 SIZE>
class BufferOf_ : public BufferOf<T>
{
public:
    BufferOf_() : BufferOf<T>(m_buf, SIZE, 0)
    {
#ifndef _RELEASE
        if (Type2Flag<T>::Flag() != CarQuintetFlag_Type_Struct) {
            _MemoryBuf_SetByteValue(this, 0xCC);
        }
#endif
    }

protected:
    T   m_buf[SIZE ? SIZE : 1];

private:
    // prohibit "=" operator
    BufferOf_& operator = (const BufferOf<T>& buf) {}
    BufferOf_& operator = (const BufferOf_& buf) {}
    BufferOf_(const BufferOf<T>& buf) {}
    BufferOf_(const BufferOf_& buf) {}
};
/** @} */

/** @addtogroup CARTypesRef
  *   @{
  */
//---------------MemoryBuf---------------------------------------------------

class MemoryBuf : public BufferOf<Byte>
{
public:
    MemoryBuf& SetByteValue(Byte value)
    {
        _MemoryBuf_SetByteValue(this, value);
        return *this;
    }

    Int32 Compare(const Byte* pBuf, Int32 n) const
    {
        return _MemoryBuf_Compare((const PCarQuintet)this, pBuf, n);
    }

    Int32 Compare(const PCarQuintet pCq) const
    {
        assert(pCq && pCq->m_pBuf);
        return _MemoryBuf_Compare((const PCarQuintet)this,
                        (const Byte*)pCq->m_pBuf, pCq->m_used);
    }

    MemoryBuf& Insert(Int32 offset, const Byte* p, Int32 n)
    {
        BufferOf<Byte>::Insert(offset, p, n);
        return *this;
    }

    MemoryBuf& Replace(Int32 offset, const Byte* pBuf, Int32 n)
    {
        BufferOf<Byte>::Replace(offset, pBuf, n);
        return *this;
    }

    MemoryBuf& Append(Byte value)
    {
        BufferOf<Byte>::Append(value);
        return *this;
    }

    MemoryBuf& Append(const Byte* pBuf, Int32 n)
    {
        BufferOf<Byte>::Append(pBuf, n);
        return *this;
    }

    MemoryBuf& Append(const PCarQuintet pSrc)
    {
        BufferOf<Byte>::Append((BufferOf<Byte> *)pSrc);
        return *this;
    }

    MemoryBuf& Copy(const PCarQuintet pSrc)
    {
        BufferOf<Byte>::Copy((BufferOf<Byte> *)pSrc);
        return *this;
    }

    MemoryBuf& Copy(const Byte* pBuf, Int32 n)
    {
        BufferOf<Byte>::Copy(pBuf, n);
        return *this;
    }

    MemoryBuf *Clone() const
    {
        return (MemoryBuf *)BufferOf<Byte>::Clone();
    }

    static MemoryBuf *Alloc(Int32 capacity)
    {
        return (MemoryBuf *)BufferOf<Byte>::Alloc(capacity);
    }

    static MemoryBuf *Alloc(Byte *pBuf, Int32 capacity, Int32 used)
    {
        return (MemoryBuf *)BufferOf<Byte>::Alloc(pBuf, capacity, used);
    }

    static MemoryBuf *Alloc(Byte *pBuf, Int32 capacity)
    {
        return (MemoryBuf *)BufferOf<Byte>::Alloc(pBuf, capacity);
    }

    MemoryBuf(Byte *pBuf, Int32 capacity, Int32 used) :
        BufferOf<Byte>(pBuf, capacity, used)
    {
    }

    MemoryBuf(Byte *pBuf, Int32 capacity) :
        BufferOf<Byte>(pBuf, capacity)
    {
    }
};
/** @} */

/** @addtogroup BaseTypesRef
  *   @{
  */
template <Int32 SIZE>
class MemoryBuf_ : public MemoryBuf
{
public:
    MemoryBuf_() : MemoryBuf(m_buf, SIZE, 0)
    {
#ifndef _RELEASE
        _MemoryBuf_SetByteValue(this, 0xCC);
#endif
    }

protected:
    Byte   m_buf[SIZE ? SIZE : 1];
};
/** @} */

typedef MemoryBuf*              PMemoryBuf;

#define NULL_ARRAYOF(type) \
        *(const ArrayOf<type> *)_CarQuintet_GetNullValue( \
            Type2Flag<type>::Flag())

#define NULL_BUFFEROF(type) \
        *(const BufferOf<type> *)_CarQuintet_GetNullValue( \
            Type2Flag<type>::Flag())


#define NULL_MEMORYBUF    \
        *(const MemoryBuf *)_CarQuintet_GetNullValue( \
            CarQuintetFlag_Type_Byte)


_ELASTOS_NAMESPACE_END

#else // !__cplusplus

typedef CarQuintet  ArrayOf;
typedef CarQuintet  BufferOf;
typedef BufferOf    MemoryBuf;

#define NULL_ARRAYOF            0
#define NULL_BUFFEROF           0
#define NULL_MEMORYBUF          0

//ArrayOf
#define ARRAYOF_BOX(pCq, pBuf, size, flags) \
            do { \
                assert((size) >= 0); \
                (pCq)->m_flags = flags; \
                (pCq)->m_reserve = 0; \
                (pCq)->m_size = size; \
                (pCq)->m_used = size; \
                (pCq)->m_pBuf = pBuf; \
            } while (0)

#define ARRAYOF_UNBOX(Cq, ppBuf, pSize, elemsize) \
            do { \
                (*ppBuf) = (Cq).m_pBuf; \
                *(Int32*)pSize= (Cq).m_size / elemsize; \
            } while (0)

//BufferOf
#define BUFFEROF_BOX(pCq, pBuf, size, used, flags) \
            do { \
                assert((size) >= 0 && (used) >= 0); \
                (pCq)->m_flags = flags; \
                (pCq)->m_reserve = 0; \
                (pCq)->m_size = size; \
                (pCq)->m_used = used; \
                (pCq)->m_pBuf = pBuf; \
            } while (0)

#define BUFFEROF_UNBOX(Cq, ppBuf, pSize, pUsed, elemsize) \
            do { \
                (*ppBuf) = (Cq).m_pBuf; \
                *(Int32*)pSize= (Cq).m_size / elemsize; \
                *(Int32*)pUsed = (Cq).m_used / elemsize; \
            } while (0)

//MemoryBuf
#define MEMORYBUF_BOX(pCq, pBuf, size, used) \
            BUFFEROF_BOX(pCq, pBuf, size, used, CarQuintetFlag_Type_Byte)
#define MEMORYBUF_UNBOX(Cq, ppBuf, pSize, pUsed) \
            BUFFEROF_UNBOX(Cq, ppBuf, pSize, pUsed, 1)

#endif // __cplusplus

#endif // __CARARRAY_H__
