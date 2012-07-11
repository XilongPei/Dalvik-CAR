//==========================================================================
// Copyright (c) 2000-2009,  Elastos, Inc.  All Rights Reserved.
//==========================================================================
#ifndef __HASHTABLE_INC__
#define __HASHTABLE_INC__

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Enumeration.h"

#define MUL_LOADFACTOR(n) (((n) * 3) >> 2) //n * 0.75


template <class TCHAR, class V>
class __HashTableElementEnumeration;

template <class TCHAR, class V>
class __HashTableKeyEnumeration;

template <class TCHAR, class V>
class tempHashTable
{
    friend class __HashTableElementEnumeration<TCHAR, V>;
    friend class __HashTableKeyEnumeration<TCHAR, V>;

public:
    tempHashTable(int nInitialCapacity = 11, float fLoadFactor = 0.75f);

    ~tempHashTable();

    inline int Size();

    inline bool IsEmpty();

    V* Get(const TCHAR *wszName);

    V* operator[](TCHAR *wszName);

    bool Put(TCHAR *wszName, V* pValue);

    bool Put(TCHAR *wszName, V& value);

    bool Remove(TCHAR *wszName);

    bool Contains(TCHAR *wszName);

    Enumeration<V> *Elements();

    Enumeration<TCHAR *> *Keys();

    void Clear();

private:
    bool Rehash();

    unsigned int Hash(const TCHAR * str);

    int tstrcmp(const TCHAR *str1, const TCHAR *str2);

private:
    struct HashEntry {
        int nHash;
        V value;
        HashEntry *pNext;
        TCHAR wszName[1];
    };

    struct HashEntry **m_pTable;
    int m_nCapacity;
    int m_nCount;
    int m_nThreshold;
    float m_fLoadFactor;
    int m_nModCount;
};

template <class TCHAR, class V>
class __HashTableElementEnumeration : public Enumeration<V>
{
    friend class tempHashTable<TCHAR, V>;

protected:
    __HashTableElementEnumeration(tempHashTable<TCHAR, V> *pHashtable) :
            m_pHashtable(pHashtable), m_nItems(0),
            m_nIndex(-1), m_pEntry(NULL)
    {
    }

public:
    virtual bool HasMoreElements();

    virtual V* NextElement();

private:
    tempHashTable<TCHAR, V> *m_pHashtable;
    int m_nItems;
    int m_nIndex;
    struct tempHashTable<TCHAR, V>::HashEntry *m_pEntry;
};

template <class TCHAR, class V>
class __HashTableKeyEnumeration : public Enumeration<TCHAR*>
{
    friend class tempHashTable<TCHAR, V>;

protected:
    __HashTableKeyEnumeration(tempHashTable<TCHAR, V> *pHashtable) :
            m_pHashtable(pHashtable), m_nItems(0),
            m_nIndex(-1), m_pEntry(NULL), m_wszKey(NULL)
    {
    }

public:
    virtual bool HasMoreElements();

    virtual TCHAR** NextElement();

private:
    tempHashTable<TCHAR, V> *m_pHashtable;
    int m_nItems;
    int m_nIndex;
    struct tempHashTable<TCHAR, V>::HashEntry *m_pEntry;
    TCHAR *m_wszKey;
};

template <class TCHAR, class V>
tempHashTable<TCHAR, V>::tempHashTable(int nInitialCapacity, float fLoadFactor) :
        m_pTable(NULL), m_nCapacity(0), m_nCount(0), m_nThreshold(0),
        m_fLoadFactor(0), m_nModCount(0)
{
    if (nInitialCapacity <= 0)
        nInitialCapacity = 10;

    m_pTable = (struct HashEntry **)malloc(sizeof(struct HashEntry **)
                * nInitialCapacity);

    assert(m_pTable && "Alloc memory for Hashtable failed!");

    if (!m_pTable)
        return;

    memset(m_pTable, 0, sizeof(struct HashEntry **) * nInitialCapacity);

    m_nCapacity = nInitialCapacity;
    m_nThreshold = (int)MUL_LOADFACTOR(nInitialCapacity);
}

template <class TCHAR, class V>
tempHashTable<TCHAR, V>::~tempHashTable()
{
    if (m_pTable) {
        Clear();
        free(m_pTable);
    }
}

template <class TCHAR, class V>
int tempHashTable<TCHAR, V>::Size()
{
    return m_nCount;
}

template <class TCHAR, class V>
bool tempHashTable<TCHAR, V>::IsEmpty()
{
    return m_nCount == 0;
}

template <class TCHAR, class V>
int tempHashTable<TCHAR, V>::tstrcmp(const TCHAR *str1, const TCHAR *str2)
{
    int ret = 0;
    do {
        ret = *str1 - *str2;
        str1++;
    } while (ret == 0 && *str2++ != 0);
    return ret;
}
template <class TCHAR, class V>
V* tempHashTable<TCHAR, V>::Get(const TCHAR *wszName)
{
    assert(wszName && *wszName && "NULL or empty key name!");
    assert(m_pTable && "Uninitialized Hashtable!");

    //static T nullRef;

    if (!wszName || !*wszName || !m_pTable) {
        //memset(&nullRef, 0, sizeof(V));
        return NULL;
    }

    int nHash = Hash(wszName);
    int nIndex = (nHash & 0x7FFFFFFF) % m_nCapacity;
    for (struct HashEntry *e = m_pTable[nIndex]; e != NULL ; e = e->pNext) {
        if ((e->nHash == nHash) && tstrcmp(e->wszName, wszName) == 0)
            return &e->value;
    }

    //assert(0 && "Element not exist!");
    //memset(&nullRef, 0, sizeof(V));
    return NULL;
}

template <class TCHAR, class V>
V* tempHashTable<TCHAR, V>::operator[](TCHAR *wszName)
{
    return Get(wszName);
}
template <class TCHAR, class V>
bool tempHashTable<TCHAR, V>::Rehash()
{
    int nOldCapacity = m_nCapacity;
    struct HashEntry **pOldTable = m_pTable;

    int nNewCapacity = nOldCapacity * 2 + 1;
    struct HashEntry **pNewTable = (struct HashEntry **)malloc(
            sizeof(struct HashEntry **) * nNewCapacity);
    if (!pNewTable)
        return false;

    memset(pNewTable, 0, sizeof(struct HashEntry **) * nNewCapacity);

    m_nModCount++;
    m_nThreshold = (int)(MUL_LOADFACTOR(nNewCapacity));
    m_nCapacity = nNewCapacity;
    m_pTable = pNewTable;

    for (int i = nOldCapacity ; i-- > 0 ;) {
        for (struct HashEntry *p = pOldTable[i]; p != NULL ; ) {
            struct HashEntry *e = p;
            p = p->pNext;

            int nIndex = (e->nHash & 0x7FFFFFFF) % nNewCapacity;
            e->pNext = pNewTable[nIndex];
            pNewTable[nIndex] = e;
        }
    }

    free(pOldTable);

    return true;
}

template <class TCHAR, class V>
bool tempHashTable<TCHAR, V>::Put(TCHAR *wszName, V* pValue)
{
    assert(wszName && *wszName && "NULL or empty key name!");
    assert(pValue && "Can not put NULL value to Hashtable!");
    assert(m_pTable && "Uninitialized Hashtable!");

    if (!wszName || *wszName == 0 || !pValue || !m_pTable)
        return false;

    // Makes sure the key is not already in the hashtable.
    int nHash = Hash(wszName);
    int nIndex = (nHash & 0x7FFFFFFF) % m_nCapacity;
    struct HashEntry *e;
    for (e = m_pTable[nIndex] ; e != NULL ; e = e->pNext) {
        if ((e->nHash == nHash) && tstrcmp(e->wszName, wszName) == 0) {
            memcpy(&(e->value), pValue, sizeof(V));
            return true;
        }
    }

    m_nModCount++;
    if (m_nCount >= m_nThreshold) {
        // Rehash the table if the threshold is exceeded
        if (!Rehash())
            return false;

        nIndex = (nHash & 0x7FFFFFFF) % m_nCapacity;
    }

    // Creates the new entry.
    size_t len = 0;
    TCHAR *ptr = wszName;
    while(ptr && *ptr) { len++; ptr++; }

    e = (struct HashEntry *)malloc(
            sizeof(struct HashEntry) + sizeof(TCHAR) * (len+1));
    if (!e)
        return false;

    e->nHash = nHash;
    e->pNext = m_pTable[nIndex];
    memcpy(&(e->value), pValue, sizeof(V));
    //wcscpy(e->wszName, wszName);
    TCHAR *p = wszName, *q =e->wszName;
    while ((*q++ = *p++) != 0)    // copy Source to Dest
        ;
    m_pTable[nIndex] = e;
    m_nCount++;

    return true;
}

template <class TCHAR, class V>
bool tempHashTable<TCHAR, V>::Put(TCHAR *wszName, V& value)
{
    return Put(wszName, &value);
}

template <class TCHAR, class V>
bool tempHashTable<TCHAR, V>::Remove(TCHAR *wszName)
{
    assert(wszName && *wszName && "NULL or empty key name!");
    assert(m_pTable && "Uninitialized Hashtable!");

    if (!wszName || *wszName == 0 || !m_pTable)
        return false;

    int nHash = Hash(wszName);
    int nIndex = (nHash & 0x7FFFFFFF) % m_nCapacity;
    for (struct HashEntry *e = m_pTable[nIndex], *prev = NULL ; e != NULL ;
            prev = e, e = e->pNext) {
        if ((e->nHash == nHash) && tstrcmp(e->wszName, wszName) == 0) {
            m_nModCount++;
            if (prev != NULL) {
                prev->pNext = e->pNext;
            } else {
                m_pTable[nIndex] = e->pNext;
            }

            m_nCount--;

            free(e);
            return true;
        }
    }

    return false;
}

template <class TCHAR, class V>
bool tempHashTable<TCHAR, V>::Contains(TCHAR *wszName)
{
    assert(wszName && *wszName && "NULL or empty key name!");
    assert(m_pTable && "Uninitialized Hashtable!");

    if (!wszName || *wszName == 0 || !m_pTable)
        return false;

    int nHash = Hash(wszName);
    int nIndex = (nHash & 0x7FFFFFFF) % m_nCapacity;
    for (struct HashEntry *e = m_pTable[nIndex] ; e != NULL ; e = e->pNext) {
        if ((e->nHash == nHash) && tstrcmp(e->wszName, wszName) == 0)
            return true;
    }

    return false;
}

template <class TCHAR, class V>
void tempHashTable<TCHAR, V>::Clear()
{
    if (!m_pTable)
        return;

    m_nModCount++;

    for (int nIndex = m_nCapacity; --nIndex >= 0; ) {
        for (struct HashEntry *e = m_pTable[nIndex]; e != NULL; ) {
            struct HashEntry *p = e;
            e = e->pNext;
            free(p);
        }

        m_pTable[nIndex] = NULL;
    }

    m_nCount = 0;
}

template <class TCHAR, class V>
Enumeration<TCHAR*> *tempHashTable<TCHAR, V>::Keys()
{
    return new __HashTableKeyEnumeration<TCHAR, V>(this);
}

template <class TCHAR, class V>
Enumeration<V> *tempHashTable<TCHAR, V>::Elements()
{
    return new __HashTableElementEnumeration<TCHAR, V>(this);
}

template <class TCHAR, class V>
unsigned int tempHashTable<TCHAR, V>::Hash(const TCHAR * str)
{
    unsigned int value = 0L;
    TCHAR ch;

    if (str != NULL) {
        value += 30 * (*str);
        while ((ch = *str++) != 0) {
            value = value ^ ((value << 5) + (value >> 3) + (unsigned long)ch);
        }
    }

    return value;
}


template <class TCHAR, class V>
bool __HashTableElementEnumeration<TCHAR, V>::HasMoreElements()
{
    return m_nItems < m_pHashtable->m_nCount;
}

template <class TCHAR, class V>
V* __HashTableElementEnumeration<TCHAR, V>::NextElement()
{
    if (m_pEntry)
        m_pEntry = m_pEntry->pNext;

    if (!m_pEntry) {
        for (++m_nIndex; m_nIndex < m_pHashtable->m_nCapacity &&
                (m_pEntry = m_pHashtable->m_pTable[m_nIndex]) == NULL;
                m_nIndex++);

        if (!m_pEntry) {
            return NULL;
        }
    }

    m_nItems++;
    return &m_pEntry->value;
}

template <class TCHAR, class V>
bool __HashTableKeyEnumeration<TCHAR, V>::HasMoreElements()
{
    return m_nItems < m_pHashtable->m_nCount;
}

template <class TCHAR, class V>
TCHAR** __HashTableKeyEnumeration<TCHAR, V>::NextElement()
{
    if (m_pEntry)
        m_pEntry = m_pEntry->pNext;

    if (!m_pEntry) {
        for (++m_nIndex; m_nIndex < m_pHashtable->m_nCapacity &&
                (m_pEntry = m_pHashtable->m_pTable[m_nIndex]) == NULL;
                m_nIndex++);

        if (!m_pEntry) {
            assert(0 && "End of key enumeration!");
            m_wszKey = NULL;
            return &m_wszKey;
        }
    }

    m_nItems++;
    m_wszKey = m_pEntry->wszName;
    return &m_wszKey;
}

#endif // __HASHTABLE_INC__
