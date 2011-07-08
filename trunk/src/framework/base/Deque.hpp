/*
 *  Copyright 2009-2010 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
#pragma once
#include "base/Array.hpp"

namespace FW
{
//------------------------------------------------------------------------

template <class T> class Deque // Generalization of stack & queue.
{
private:
    struct Item
    {
        T           value;
        S32         prev;
        S32         next;
    };

public:
                    Deque       (void)                          { clear(); }
    explicit        Deque       (const T& item)                 { clear(); addLast(item); }
                    Deque       (const T* ptr, int size)        { set(ptr, size); }
                    Deque       (const Deque<T>& other)         { set(other); }
    explicit        Deque       (const Array<T>& other)         { set(other); }
                    ~Deque      (void)                          {}

    int             getSize     (void) const                    { return m_size; }
    const T&        getFirst    (void) const                    { FW_ASSERT(m_size); return m_items[m_first].value; }
    T&              getFirst    (void)                          { FW_ASSERT(m_size); return m_items[m_first].value; }
    const T&        getLast     (void) const                    { FW_ASSERT(m_size); return m_items[m_last].value; }
    T&              getLast     (void)                          { FW_ASSERT(m_size); return m_items[m_last].value; }

    void            reset       (void)                          { clear(); m_items.reset(); }
    void            clear       (void)                          { m_items.clear(); m_size = 0; m_free = -1; }
    void            setCapacity (int capacity)                  { m_items.setCapacity(capacity); }
    void            compact     (void)                          { set(getAll()); }

    void            set         (const T* ptr, int size);
    void            set         (const Deque<T>& other);
    void            set         (const Array<T>& other)         { set(other.getPtr(), other.getSize()); }
    void            getRange    (Array<T>& res, int start, int end) const;
    Array<T>        getRange    (int start, int end) const;
    void            getAll      (Array<T>& res) const           { getRange(res, 0, getSize()); }
    Array<T>        getAll      (void) const                    { return getRange(0, getSize()); }

    T&              addFirst    (void);
    T&              addFirst    (const T& item)                 { T& slot = addFirst(); slot = item; return slot; }
    T&              addLast     (void);
    T&              addLast     (const T& item)                 { T& slot = addLast(); slot = item; return slot; }

    T&              removeFirst (void);
    T&              removeLast  (void);

    Deque<T>&       operator=   (const Deque<T>& other)         { set(other); return *this; }
    Deque<T>&       operator=   (const Array<T>& other)         { set(other); return *this; }
    bool            operator==  (const Deque<T>& other) const;
    bool            operator!=  (const Deque<T>& other) const   { return (!operator==(other)); }

private:
    int             allocItem   (void);
    void            freeItem    (int idx);

    Array<Item>     m_items;
    S32             m_size;
    S32             m_first;
    S32             m_last;
    S32             m_free;
};

//------------------------------------------------------------------------

template <class T> void Deque<T>::set(const T* ptr, int size)
{
    FW_ASSERT(size >= 0);

    m_items.reset(size);
    for (int i = 0; i < size; i++)
    {
        if (ptr)
            m_items[i].value = ptr[i];
        m_items[i].prev = i - 1;
        m_items[i].next = i + 1;
    }

    m_first = 0;
    m_last = size - 1;
    m_free = -1;
    m_size = size;
}

//------------------------------------------------------------------------

template <class T> void Deque<T>::set(const Deque<T>& other)
{
    if (&other != this)
    {
        m_items = other.m_items;
        m_size = other.m_size;
        m_first = other.m_first;
        m_last = other.m_last;
        m_free = other.m_free;
    }
}

//------------------------------------------------------------------------

template <class T> void Deque<T>::getRange(Array<T>& res, int start, int end) const
{
    FW_ASSERT(start >= 0 && start <= end && end <= getSize());

    int src = m_first;
    for (int i = 0; i < start; i++)
        src = m_items[src].next;

    T* dst = res.add(NULL, end - start);
    for (int i = start; i < end; i++)
    {
        *dst++ = m_items[src].value;
        src = m_items[src].next;
    }
}

//------------------------------------------------------------------------

template <class T> Array<T> Deque<T>::getRange(int start, int end) const
{
    FW_ASSERT(start >= 0 && start <= end && end <= getSize());
    Array<T> res;
    res.setCapacity(end - start);
    getRange(res, start, end);
    return res;
}

//------------------------------------------------------------------------

template <class T> T& Deque<T>::addFirst(void)
{
    int idx = allocItem();
    if (m_size == 1)
        m_last = idx;
    else
    {
        m_items[idx].next = m_first;
        m_items[m_first].prev = idx;
    }
    m_first = idx;
    return m_items[idx].value;
}

//------------------------------------------------------------------------

template <class T> T& Deque<T>::addLast(void)
{
    int idx = allocItem();
    if (m_size == 1)
        m_first = idx;
    else
    {
        m_items[idx].prev = m_last;
        m_items[m_last].next = idx;
    }
    m_last = idx;
    return m_items[idx].value;
}

//------------------------------------------------------------------------

template <class T> T& Deque<T>::removeFirst(void)
{
    FW_ASSERT(m_size);
    int idx = m_first;
    m_first = m_items[idx].next;
    freeItem(idx);
    return m_items[idx].value;
}

//------------------------------------------------------------------------

template <class T> T& Deque<T>::removeLast(void)
{
    FW_ASSERT(m_size);
    int idx = m_last;
    m_last = m_items[idx].prev;
    freeItem(idx);
    return m_items[idx].value;
}

//------------------------------------------------------------------------

template <class T> bool Deque<T>::operator==(const Deque<T>& other) const
{
    if (m_size != other.m_size)
        return false;

    int idxA = m_first;
    int idxB = other.m_first;
    for (int i = 0; i < m_size; i++)
    {
        if (m_items[idxA].value != other.m_items[idxB].value)
            return false;
        idxA = m_items[idxA].next;
        idxB = other.m_items[idxB].next;
    }
    return true;
}

//------------------------------------------------------------------------

template <class T> int Deque<T>::allocItem(void)
{
    int idx = m_free;
    if (idx != -1)
        m_free = m_items[idx].next;
    else
    {
        idx = m_items.getSize();
        m_items.add();
    }
    m_size++;
    return idx;
}

//------------------------------------------------------------------------

template <class T> void Deque<T>::freeItem(int idx)
{
    m_items[idx].next = m_free;
    m_free = idx;
    m_size--;
}

//------------------------------------------------------------------------
}
