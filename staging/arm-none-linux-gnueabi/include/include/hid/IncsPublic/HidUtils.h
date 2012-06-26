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

/** 
 *******************************************************************************
 * @file HidUtils.h
 * 
 * @brief Public header file for HidUtils.c
 *******************************************************************************
 */

#ifndef __HID_UTILS_H
#define __HID_UTILS_H

/**
 * @addtogroup hidlib_utils_public
 *
 * @{
 */

/* 
 * Stringification macros -- turn a #define into a string
 *
 * STR() macro just turns the argument into a string
 * XSTR() macro expands the argument passed in
 *
 * e.g.,
 * #define MY_DEFINE    5
 * 
 * STR(MY_DEFINE) would give "MY_DEFINE"
 * XSTR(MY_DEFINE) would give "5" 
 */
#define STR(S)  #S
#define XSTR(S) STR(S)

/**
 * Get the size of an array 
 */
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

/**
 * @def likely(x)
 * @brief Provide the compiler with branch prediction information
 *
 * @def unlikely(x)
 * @brief Provide the compiler with branch prediction information
 */
#if __GNUC__

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#else

#define likely(x)       (x)
#define unlikely(x)     (x)

#endif  /* __GNUC__ */

char* HidStringNew(const char* pFmt, ...);
void HidStringFree(char** ppStr);

int HidReadNumBytes(int fd, void* pData, int len);
void HidNanoSleep(long sec, long nsec);

/** @} */

#endif
