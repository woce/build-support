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

/******************************************************************************
 * @file HidDebug.h
 *
 * @brief Useful debugging macros
 *****************************************************************************/

#ifndef __HID_DEBUG_H
#define __HID_DEBUG_H

#include <stdio.h>
#include <syslog.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

/* FIXME: use this once asserts are fixed in the toolchain
#include <assert.h> */


/**
 * @defgroup hidlib_public_debug HidLib Public Debug Details
 *
 * @ingroup hidlib_public
 *
 * @brief Useful debugging macros
 *
 * @{
 */

#undef NDEBUG

/**
 * @def TRIM_FILE
 * 
 * @brief Replacement for __FILE__, to ensure that we only use the filename
 * and not the full path (pmmakefiles has a readlink that causes __FILE__ to
 * be the full path
 */
#define TRIM_FILE   (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) 

/**
 * @def ASSERT
 * @brief Replacement for assert()
 */


/* 
 * Our current toolchain has problems with assert(). You won't get a stack
 * trace if you call it, so we have a macro to purposely segfault
 */
#ifndef NDEBUG
    #define ASSERT(x)	                                                            \
    do {							                    \
        if (!(x)) {						                    \
            if (likely(kHidDebugSyslog == gDebugDest))                              \
            {                                                                       \
                syslog(LOG_USER | LOG_ERR, "%s:%d : %s: assertion \"%s\" failed\n", \
                        TRIM_FILE, __LINE__, __func__, #x);                          \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                fprintf(stderr, "%s:%d : %s: assertion \"%s\" failed\n",            \
                        TRIM_FILE, __LINE__, __func__, #x);	                    \
            }                                                                       \
            *((int*)0x0) = 0;                                                       \
        }							                    \
    } while (0)	
#else
    #define ASSERT(x)	                                                            \
    do {							                    \
        if (!(x)) {						                    \
            if (likely(kHidDebugSyslog == gDebugDest))                              \
            {                                                                       \
                syslog(LOG_USER | LOG_ERR, "%s:%d : %s: assertion \"%s\" failed\n", \
                        TRIM_FILE, __LINE__, __func__, #x);                          \
            }                                                                       \
            else                                                                    \
            {                                                                       \
                fprintf(stderr, "%s:%d : %s: assertion \"%s\" failed\n",            \
                        TRIM_FILE, __LINE__, __func__, #x);	                    \
            }                                                                       \
        }							                    \
    } while (0)	
#endif  /* NDEBUG */


/**
 * @def HidDbgPerror
 * @brief Intended to be a replacement for perror, but it gives more
 * information such as the function name, file and line number 
 * @param  level  IN debug level
 *
 * @def HidDbgMsg
 * @brief Intended to be a replacement for printing debug messages with printf
 * and adds some formatting.
 * @param  level    IN  debug level
 * @param  fmt      IN  printf-style format
 * @param  args...  IN  printf-style args
 *
 * @def HidDbgPrint
 * @brief Intended to be a replacement for printf, but doesn't add formatting
 * like HidDbgMsg
 * @param  level    IN  debug level
 * @param  fmt      IN  printf-style format
 * @param  args...  IN  printf-style args
 *
 */

typedef enum HidDebugDest
{
    kHidDebugSyslog,    /**< route logs to syslog  */
    kHidDebugConsole    /**< route logs to console */
} HidDebugDest_t;

extern int gVerbosity;                 /**< global verbosity level */
extern HidDebugDest_t gDebugDest;      /**< global destination of debug messages */

/** 
 * Output to stderr or syslog depending on whether this is defined
 */
#define DISPLAY_DEBUG_MSGS

#define DBG_FORCE LOG_EMERG     /**< force debug messages to be output */
#define DBG_ERR   LOG_ERR       /**< only essential error messages */
#define DBG_INFO  LOG_INFO      /**< info messages useful for tracing */
#define DBG_MAX   LOG_DEBUG     /**< all messages */

#define HID_STRERROR_BUF_SIZE   256

#define HidDbgPerrorCustom(level, fmt, args...)                         \
do {                                                                    \
    if (level <= gVerbosity)                                            \
    {                                                                   \
        char errMsg[HID_STRERROR_BUF_SIZE];                             \
        if (unlikely(-1 == strerror_r(errno, errMsg, sizeof(errMsg))))  \
        {                                                               \
            errMsg[0] = (char)0;                                        \
        }                                                               \
        if (likely(kHidDebugSyslog == gDebugDest))                      \
        {                                                               \
            syslog(LOG_USER | level, "%s:%d : %s: %s ["fmt"]\n",      \
                   TRIM_FILE, __LINE__, __func__,                       \
                   errMsg[0] ? errMsg : "Unknown error",                \
                   ##args);                                             \
        }                                                               \
        else                                                            \
        {                                                               \
            fprintf(stderr, "%s:%d : %s: %s ["fmt"]\n",                 \
                    TRIM_FILE, __LINE__, __func__,                      \
                    errMsg[0] ? errMsg : "Unknown error",               \
                    ##args);                                            \
        }                                                               \
    }                                                                   \
} while (0)

#define HidDbgPerror(level)                                             \
do {                                                                    \
    if (level <= gVerbosity)                                            \
    {                                                                   \
        char errMsg[HID_STRERROR_BUF_SIZE];                             \
        if (unlikely(-1 == strerror_r(errno, errMsg, sizeof(errMsg))))  \
        {                                                               \
            errMsg[0] = (char)0;                                        \
        }                                                               \
        if (likely(kHidDebugSyslog == gDebugDest))                      \
        {                                                               \
            syslog(LOG_USER | level, "%s:%d : %s: %s\n",              \
                   TRIM_FILE, __LINE__, __func__,                       \
                   errMsg[0] ? errMsg : "Unknown error");               \
        }                                                               \
        else                                                            \
        {                                                               \
            fprintf(stderr, "%s:%d : %s: %s\n",                         \
                    TRIM_FILE, __LINE__, __func__,                      \
                    errMsg[0] ? errMsg : "Unknown error");              \
        }                                                               \
    }                                                                   \
} while (0)

#define HidDbgPrint(level, fmt, args...)                                \
do {                                                                    \
    if (level <= gVerbosity)                                            \
    {                                                                   \
        if (likely(kHidDebugSyslog == gDebugDest))                      \
        {                                                               \
            syslog(LOG_USER | level, fmt, ##args);                  \
        }                                                               \
        else                                                            \
        {                                                               \
            fprintf(stderr, fmt, ##args);                               \
        }                                                               \
    }                                                                   \
} while (0)

#define HidDbgMsg(level, fmt, args...)                                  \
do {                                                                    \
    if (level <= gVerbosity)                                            \
    {                                                                   \
        if (likely(kHidDebugSyslog == gDebugDest))                      \
        {                                                               \
            syslog(LOG_USER | level, "%s: "fmt"\n",                 \
                   __func__, ##args);                                   \
        }                                                               \
        else                                                            \
        {                                                               \
            fprintf(stderr, "%s:\n  ", __func__);                       \
            fprintf(stderr, fmt, ##args);                               \
            fprintf(stderr, "\n");                                      \
        }                                                               \
    }                                                                   \
} while (0)

/** @} */

#endif  /* define __HID_DEBUG_H */
