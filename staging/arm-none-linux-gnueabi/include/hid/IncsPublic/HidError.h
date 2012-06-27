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
 * @file HidError.h
 * 
 * @brief Public header file for error reporting functions.
 *******************************************************************************
 */

#ifndef __HID_ERROR_H
#define __HID_ERROR_H

/** 
 * @defgroup hidlib_error_internal HidLib Error Internal Details
 *
 * @ingroup hidlib_internal
 *
 * @brief
 *
 * @{
 */

#include <stdint.h>
#include <inttypes.h>

#include "HidDebug.h"
#include "HidUtils.h"

typedef struct HidError HidError_t;

HidError_t* _HidErrorNew(const char* pFile, int line, const char* pFunction,
                         int errCode, const char* pErrMsg, ...);
/** @} */

/** 
 * @defgroup hidlib_error_public HidLib Public Error Details
 *
 * @ingroup hidlib_public
 *
 * @brief
 *
 * @{
 */

typedef uint32_t PmErr;

/* We can add more error types in the future if we need to. Right now just
 * check to see if the return value is kPmErrorNone (i.e., success) */
enum {
    kPmErrorNone = (uint32_t)0x00000000,    /**< no error */
    kPmErrorInvalidFd,                      /**< pipe has invalid fd */
    kPmErrorNoMem,                          /**< out of memory */
    kPmErrorInvalidParam,                   /**< an invalid parameter was passed to                                                  the function (e.g., NULL ptr); this 
                                                 indicates incorrect API usage */
    kPmErrorExit,                           /**< indicate that we should exit; 
                                                 currently used by plugins to know
                                                 when to stop their worker thread */
    kPmErrorTimeout,                        /**< timeout occurred */
    kPmErrorUnknown                         /**< unknown (generic error) */
};


/** 
 *******************************************************************************
 * @brief Allocate a new error with the specified error code and message. 
 * 
 * @param  errCode  IN  error code
 * @param  errMsg   IN  error message (printf-style) 
 * @param  args...  IN  printf-style args 
 * 
 * @retval  new error on success
 * @retval  NULL on failure
 *******************************************************************************
 */
#define HidErrorNew(errCode, errMsg, args...)   \
    _HidErrorNew(__FILE__, __LINE__, __FUNCTION__, errCode, errMsg, ##args)

void HidErrorFree(HidError_t** ppError);
void HidErrorPrint(int level, HidError_t* pError);
inline void HidErrorPrintAndFree(int level, HidError_t** ppError);


/** 
 *******************************************************************************
 * @brief Return @ref ret if @ref cond is not met. Prints an error message as a
 * side effect.
 * 
 * @param  cond  IN     condition that must be true
 * @param  ret   IN     value to return
 *******************************************************************************
 */
#define HidReturnValIfFail(cond, ret)                                 \
do {                                                                  \
    if (unlikely(!(cond)))                                            \
    {                                                                 \
        HidDbgMsg(DBG_ERR, #cond);                                       \
        return ret;                                                   \
    }                                                                 \
} while (0)


/** 
 *******************************************************************************
 * @brief  Return if @ref cond is not met. Prints an error message as a side
 * effect.
 * 
 * @param  cond  IN condition that must be true
 *******************************************************************************
 */
#define HidReturnIfFail(cond)                                         \
do {                                                                  \
    if (unlikely(!(cond)))                                            \
    {                                                                 \
        HidDbgMsg(DBG_ERR, #cond);                                       \
        return;                                                       \
    }                                                                 \
} while (0)


/** 
 *******************************************************************************
 * @brief  Jump to @ref label if @ref cond is not met. Prints an error message
 * as a side effect.
 * 
 * @param  cond   IN condition that must be true
 * @param  label  IN label to jump to
 *******************************************************************************
 */
#define HidGotoIfFail(cond, label)                                    \
do {                                                                  \
    if (unlikely(!(cond)))                                            \
    {                                                                 \
        HidDbgMsg(DBG_ERR, #cond);                                       \
        goto label;                                                   \
    }                                                                 \
} while (0)

/** @} */

#endif  /* __HID_ERROR_H */
