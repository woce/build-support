//  @@@LICENSE
//
//      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  LICENSE@@@

#ifndef HSEMAPHORE_H_
#define HSEMAPHORE_H_

#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

#include "HCommon.h"


struct HEXPORT HSemaphore
{
    HSemaphore(int InitialCount = 0)
    {
        int rc = sem_init(&Sem, 0, InitialCount);
        if (rc != 0) {
            HTRACE( "sem_init failed: %s\n", strerror(errno));
        }
    }

    void Post()
    {
        if (sem_post(&Sem) != 0) {
            HTRACE( "sem_post failed: %s\n", strerror(errno));
        }
    }

    bool Wait(int timeout = 0)
    {
        int retval;

        switch(timeout)
        {
        case -1:
            retval = sem_trywait(&Sem);
            break;

        case 0:
            while ((retval = sem_wait(&Sem)) != 0 && (errno == EINTR)) {
                // loop
            }
            break;

        default:
            struct timeval curtime;
            struct timespec abstime;

            gettimeofday(&curtime, NULL);

            abstime.tv_sec = curtime.tv_sec + (timeout/1000);
            abstime.tv_nsec = (curtime.tv_usec + (timeout%1000) * 1000) * 1000;
            if ( abstime.tv_nsec > 1000000000 ) {
                abstime.tv_sec += 1;
                abstime.tv_nsec -= 1000000000;
            }

            while ((retval = sem_timedwait(&Sem, &abstime)) != 0 && (errno == EINTR)) {
                // loop
            }
        }

        return (retval == 0);
    }

protected:
    sem_t Sem;
};

#endif /* NSEMAPHORE_H_ */
