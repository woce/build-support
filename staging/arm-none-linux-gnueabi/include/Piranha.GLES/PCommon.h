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
#ifndef PCOMMON_H
#define PCOMMON_H

#include <stdlib.h>
#include "PBackend.h"



#define PMIN(a, b) (((a) < (b)) ? (a) : (b))
#define PMAX(a, b) (((a) > (b)) ? (a) : (b))

#define PCOMPILE_TIME_ASSERT(x) switch(0) { case 0: case x: break; }

#define PUNUSED(x) (void)x

#ifndef DOXYGEN
    #if defined(_MSC_VER)
        #define PPACKED
        #define PNAKED
        #define PPREFETCH
        #define FASTCALL

        #if defined(IDEBUG)
            #include <stdio.h>

            #error PASSERT not defined yet for _MSC_VER
        #endif

    #elif defined(__GNUC__)
        #define PPACKED __attribute__((__packed__, aligned(4)))
        #define PNAKED  __attribute__((naked))
        #define PEXPORT __attribute__((visibility("default")))
        #define PPREFETCH(x) __builtin_prefetch(x)

        #ifdef __arm__
            #define PTRAP (*(volatile unsigned int*)0x0 = 99)
            #define FASTCALL
        #else
            #define PTRAP asm("int $3")
            #define FASTCALL __attribute__((fastcall))
        #endif

        #if defined(IDEBUG)
            #include <stdio.h>

extern bool Asserts;                            ///< \brief Enables/Disables the asserts

            #define PASSERT(x, format, ...) if (!(x) && Asserts) do {   \
                 printf("ASSERT [%s:%d] ", __FILE__, __LINE__);         \
                 printf(format, ## __VA_ARGS__);                        \
                 printf("\n");                                          \
                 PTRAP;                                                 \
                 } while (0)

            #define PON()   Asserts = true
            #define POFF()  Asserts = false
        #endif

    #else
        #error Defined compiler is not supported!
    #endif

    #ifndef PASSERT
        #define PASSERT(x, format, ...) do {} while (0)
        #define PON() do {} while (0)
        #define POFF() do {} while (0)
    #endif



    #ifdef IDEBUG
        #define DRUN(x) x
    #else
        #define DRUN(x) do {} while (0)
    #endif



    #define PALIGN(a, b) ((a + (b - 1)) & (~(b - 1)))

    #if defined(IDEBUG) && defined(DO_PRACE)
        #include <stdio.h>
        #define PTRACE(format, ...) do {                        \
            printf("[%s:%4d] ", __FILE__, __LINE__ );           \
            printf(format, ## __VA_ARGS__);                     \
        } while(0)

    #else
       #define PTRACE(format, ...) do {} while (0)
    #endif // IDEBUG

    #define PDELETE(x)   delete x; x = NULL
    #define PDELETEA(x)  delete [] x; x = NULL

    #if defined  __ARM_NEON__
    #define P_USE_NEON
    #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6J__)
    #define P_USE_ARM
    #endif

#endif



#endif
