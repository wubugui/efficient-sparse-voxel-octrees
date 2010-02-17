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
#include "base/Hash.hpp"
#include "base/DLLImports.hpp"

namespace FW
{
//------------------------------------------------------------------------

class Spinlock
{
public:
                        Spinlock        (void);
                        ~Spinlock       (void);

    void                enter           (void);
    void                leave           (void);

private:
                        Spinlock        (const Spinlock&); // forbidden
    Spinlock&           operator=       (const Spinlock&); // forbidden

private:
    CRITICAL_SECTION    m_critSect;
};

//------------------------------------------------------------------------

class Semaphore
{
public:
                        Semaphore       (int initCount = 1, int maxCount = 1);
                        ~Semaphore      (void);

    bool                acquire         (int millis = -1);
    void                release         (void);

private:
                        Semaphore       (const Semaphore&); // forbidden
    Semaphore&          operator=       (const Semaphore&); // forbidden

private:
    HANDLE              m_handle;
};

//------------------------------------------------------------------------

class Monitor
{
public:
                        Monitor         (void);
                        ~Monitor        (void);

    void                enter           (void);
    void                leave           (void);
    void                wait            (void);
    void                notify          (void);
    void                notifyAll       (void);

private:
                        Monitor         (const Monitor&); // forbidden
    Monitor&            operator=       (const Monitor&); // forbidden

private:
    Spinlock            m_lock;
    Semaphore           m_ownerSem;
    Semaphore           m_waitSem;
    Semaphore           m_notifySem;
    volatile U32        m_ownerThread;
    volatile S32        m_enterCount;
    volatile S32        m_waitCount;
};

//------------------------------------------------------------------------

class Thread
{
public:
    typedef void        (*ThreadFunc)   (void* param);

    enum Priority
    {
        Priority_Min    = -15,
        Priority_Normal = 0,
        Priority_Max    = 15
    };

private:
    struct StartParams
    {
        Thread*         thread;
        ThreadFunc      userFunc;
        void*           userParam;
        Semaphore       parentReady;
        Semaphore       childReady;
    };

public:
                        Thread          (void);
                        ~Thread         (void);

    void                start           (ThreadFunc func, void* param);

    static Thread*      getCurrent      (void);
    static Thread*      getMain         (void);
    static bool         isMain          (void);
    static U32          getID           (void);
    static void         sleep           (int millis);
    static void         yield           (void);

    Priority            getPriority     (void) const;
    void                setPriority     (Priority priority);
    bool                isAlive         (void);
    void                join            (void);

    static void         staticInit      (void);
    static void         staticDeinit    (void);

private:
    void                setCurrent      (void);
    void                started         (void);
    void                exited          (void);
    static DWORD WINAPI threadProc      (LPVOID lpParameter);

private:
                        Thread          (const Thread&); // forbidden
    Thread&             operator=       (const Thread&); // forbidden

private:
    static bool         s_inited;
    static Spinlock*    s_lock;
    static Hash<U32, Thread*>* s_threads;
    static Thread*      s_mainThread;

    U32                 m_id;
    HANDLE              m_handle;
};

//------------------------------------------------------------------------
}
