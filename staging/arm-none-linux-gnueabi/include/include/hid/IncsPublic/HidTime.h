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
 * @file HidTime.h
 * 
 * @brief Public header file for time-related functions.
 *******************************************************************************
 */

#ifndef __HID_TIME_H
#define __HID_TIME_H

/** 
 * @addtogroup hidlib_time_public
 *
 * @{
 */

#include <sys/time.h>
#include <time.h>

/** 
 * A timestamp that should be used by plugins instead of using struct timeval
 * or struct timestamp directly
 */
typedef struct HidTimeStamp
{
    struct timespec time;   /**< internal time stamp format */
} HidTimeStamp_t;

/**
 * Used for converting between timestamp types 
 */
typedef enum
{
    TIMESTAMP_TIMEVAL = 0,  /**< struct timeval */
    TIMESTAMP_TIMESPEC,     /**< struct timestamp */
    TIMESTAMP_HIDTIMESTAMP  /**< @ref HidTimeStamp_t */
} HidTimeStampType_t;

inline void HidGetTimeStamp(HidTimeStamp_t* pTime);
inline int HidGetBootTime(HidTimeStamp_t* pTime);
inline void HidDbgGetTimeStamp(int level, HidTimeStamp_t* pTime);
inline void HidTimeStampCopy(void* pDestTime, HidTimeStampType_t destType, 
                             void* pSrcTime, HidTimeStampType_t srcType);
inline void HidPrintTimeStamp(int level, const char* pMsg,
                                  const HidTimeStamp_t* pTime);
inline double HidCalcTimeDiff(const HidTimeStamp_t* pTime1, const HidTimeStamp_t* pTime2);
inline void HidPrintTimeDiff(int level, const char* pMsg, const HidTimeStamp_t* pTime1, const HidTimeStamp_t* pTime2);

/** @} */

#endif  /* __HID_TIME_H */
