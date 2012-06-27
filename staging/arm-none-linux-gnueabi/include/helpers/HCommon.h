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

#ifndef HCOMMON_H
#define HCOMMON_H

#ifdef __arm__
#define HTRAP (*(volatile unsigned int*)0x0 = 99)
#else
#define HTRAP asm("int $3")
#endif

#if defined(HDEBUG)
#include <stdio.h>

#define HASSERT(x, format, ...) if (!(x)) do {   \
    printf("ASSERT [%s:%d] ", __FILE__, __LINE__);         \
    printf(format, ## __VA_ARGS__);                        \
    printf("\n");                                          \
    HTRAP;                                                 \
} while (0)

#define HTRACE(format, ...) do {                        \
    printf("[%s:%4d] ", __FILE__, __LINE__ );           \
    printf(format, ## __VA_ARGS__);                     \
} while(0)

#endif

#ifndef HASSERT
#define HASSERT(x, format, ...) do {} while (0)
#endif

#ifndef HTRACE
#define HTRACE(format, ...) do {} while (0)
#endif

#define HEXPORT __attribute__((visibility("default")))

#endif /* NCOMMON_H */
