// @@@LICENSE
//
//      Copyright (c) 2008-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

//#public
#ifndef PSMP_H
#define PSMP_H

#ifndef CORES
 #define CORES 1                 ///< This defines the number of Cores on the destination platform
#endif

#include <pthread.h>
#include "PCommon.h"



int GetNumCore(void);

struct PAtomicInt {
    static int Add     (volatile int *Addr, const int Val);
    static int Dec     (volatile int &Addr);
    static void Inc    (volatile int &Addr);
    static void MemBar (void);
};



struct PBarrier : public PAtomicInt {
    PBarrier();
    ~PBarrier();

    void Set    (const unsigned Count);     ///< Initializes the barrier to Count
    void Spin   (void);                     ///< Spinlocks on the barrier
    void Wait   (const int us = 500);       ///< Spin/Wait  on the barrier

private:
    unsigned            Start;              ///< Starting value
    volatile int        Counter;            ///< Number of threads ready to do some work
    volatile int        CounterAck;         ///< Number of threads that acknoledged the work
    volatile int        Blocked;            ///< If the barrier is blocked or not

    pthread_mutex_t     Mutex;              ///< Mutex to lock the thread sleep
    pthread_cond_t      Condition;          ///< Condition variable to wake up from sleep
};



struct PEXPORT PSMP {
    PSMP();

    unsigned    GetCores    (void);                     ///< Retrieves the number of cores supported by the hardware

protected:
    int         Cores;
};

#endif
