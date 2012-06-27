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
 * @file HidPluginUtils.h
 * 
 * @brief Public header file exposing utility functions for plugins.
 *******************************************************************************
 */

#ifndef __HID_PLUGINS_UTILS_H
#define __HID_PLUGINS_UTILS_H

/**
 * @addtogroup hidlib_plugin_utils_public
 *
 * @{
 */

#include <poll.h>

#include "HidPlugin.h"
#include "HidError.h"

#ifndef EVIOCGMONO
#define EVIOCGMONO      _IOR('E', 0x05, int)        /* get monotonic time setting */
#endif

#ifndef EVIOCSMONO
#define EVIOCSMONO      _IOW('E', 0x05, int)        /* set monotonic time */
#endif


#define MAX_EVENTS      64

/**
 *  Used to set plugin info to an "invalid" state  
 */
#define INVALID_HID_PLUGIN_INFO {.pName = "Invalid Plugin", .id = (PluginId_t)-1, .debug = {.maxEvents = 0, .rateLimit = 0} }

typedef void* (EventReaderFn_t)(void*);
typedef void (IpcSetupFn_t)(void);

typedef struct HidWakeupSource HidWakeupSource_t;
typedef struct HidEventSource HidEventSource_t;

struct HidWakeupSource
{
    int aFd[2];
};

struct HidEventSource
{
    HidWakeupSource_t wakeUpSrc;
    bool hasWakeUpSrc;
    struct pollfd* pPollFds;
    int numEventFds;
};

typedef enum
{
    kInvalidSource = -1,
    kWakeupSource,          /**< wakeup message */
    kEventSource,           /**< normal event */
    kTimeoutSource          /**< timeout */
} HidEventSourceType_t;

typedef enum
{
    kWakeupMsgInvalid = -1,
    kWakeupMsgExit,
} HidWakeupMsg_t;

/**
 *  Used to create a "generic" plugin that reads from a "file" (e.g.,
 *  /dev/input/event*)
 */
typedef struct PluginPrvInfo
{
    ReportFn_t* pReportFn;              /**< function that reports events */
    const char* pEventFile;             /**< file to read events from, e.g., /dev/input/event0 */
    const char* pSysfsPath;             /**< sysfs path */
    int eventFd;                        /**< file descriptor */
    PluginInfo_t hidPluginInfo;         /**< plugin info passed by Init() */
    EventReaderFn_t* pEventReaderFn;    /**< function to be called in a new thread to read events */
    HidEventSource_t* pEventSource;     /**< event and wakeup source */
    IpcSetupFn_t* pIpcSetupFn;          /**< function to be called to register IPC callbacks */
    pthread_t thread;                   /**< thread id of event reader */
    bool threadRunning;                 /**< whether the reader thread is currently running */
    pthread_mutex_t threadMutex;        /**< protects threadRunning variable */
} PluginPrvInfo_t;

typedef enum
{
    HidHardwareRevisionUnknown = -1,
    HidHardwareRevisionEVT1 = 1,
    HidHardwareRevisionEVT2,
    HidHardwareRevisionEVT3,
    HidHardwareRevisionDVT1,
    HidHardwareRevisionDVT2,
    HidHardwareRevisionDVT3,
    HidHardwareRevisionDVT4,
    HidHardwareRevisionA,
    HidHardwareRevisionB,
    HidHardwareRevisionC
} HidHardwareRevision_t;

/*
 * NOTE: We're using #defines instead of enums to make sure that
 * the platforms don't show up in the symbol table (currently, they're
 * stripped out, but just in case that changes)
 */
typedef int HidHardwarePlatform_t;
#define HidHardwarePlatformUnknown     -1
#define HidHardwarePlatformCastle       1
#define HidHardwarePlatformCastlePlus   2
#define HidHardwarePlatformPixie        3
#define HidHardwarePlatformEmulator     4
#define HidHardwarePlatformWindsor      5
#define HidHardwarePlatformRoadrunner   6
#define HidHardwarePlatformBroadway     7
#define HidHardwarePlatformMantaray     8
#define HidHardwarePlatformTopaz        9
#define HidHardwarePlatformWindsorNot   10
#define HidHardwarePlatformOpal         11
#define HidHardwarePlatformTwain        12
#define HidHardwarePlatformMako         13
#define HidHardwarePlatformSapphire     14
#define HidHardwarePlatformPyramid      15

int HidReadNumBytes(int fd, void* pData, int len);

void HidFreeEventSource(HidEventSource_t** ppSrc);
PmErr HidAllocEventSource(int* pFds, int numFds, HidEventSource_t** ppSrc);

PmErr HidInitWakeupSource(HidEventSource_t* pSrc);
void HidShutdownWakeupSource(HidEventSource_t* pSrc);
PmErr HidSendWakeupMsg(HidEventSource_t* pSrc, HidWakeupMsg_t* pMsg);
PmErr HidReadWakeupMsg(HidEventSource_t* pSrc, HidWakeupMsg_t* pMsg);
PmErr HidPollEventSource(HidEventSource_t* pSrc, int timeout, HidEventSourceType_t* pType, int* pFd);

PmErr HidReadEventSource(HidEventSource_t* pSrc, int maxInputEvents, HidEventSourceType_t* pType, InputEvent_t* pEvents, int* pNumEvents, HidWakeupMsg_t* pMsg);
int HidReadInputEvent(int fd, InputEvent_t* pEvents, int maxEvents);
PmErr HidPluginGenericGetEvents(const PluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginGenericInit(const PluginInfo_t* pPluginInfo, PluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginGenericExit(PluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginGenericSuspend(PluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginGenericResume(PluginPrvInfo_t* pPluginPrvInfo);

PmErr HidPluginStartReaderThread(const PluginInfo_t* pPluginInfo, bool* pThreadRunning, pthread_mutex_t* pStateMutex, pthread_t* pThreadId, EventReaderFn_t* pEventReaderFn, void* pThreadArg);
PmErr HidPluginStopReaderThread(const PluginInfo_t* pPluginInfo, bool* pThreadRunning, pthread_mutex_t* pStateMutex, pthread_t* pThreadId, HidEventSource_t* pEventSource);

int HidGenerateRandomEvents(void* pEvent, EventType_t type, int numEvents, unsigned int* pSeed);
const char* HidOnOffToNum(const char* pStr, HidError_t** ppErr);
bool HidNumToOnOff(char** ppStr, HidError_t** ppErr);
HidHardwareRevision_t HidGetHardwareRevision();
const char* HidGetHardwareRevisionString();
HidHardwarePlatform_t HidGetHardwarePlatform();
const char* HidGetHardwarePlatformString();

/** @} */

#endif  /* __HID_PLUGINS_UTILS_H */
