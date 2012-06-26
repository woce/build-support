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
 * @file HidPluginUsdUtils.h
 * 
 * @brief Public header file exposing utility functions for plugins using
 * usdlib.
 *******************************************************************************
 */

#ifndef __HID_PLUGINS_USD_UTILS_H
#define __HID_PLUGINS_USD_UTILS_H

/**
 * @addtogroup hidlib_plugin_usd_utils_public
 *
 * @{
 */

#include <glib.h>
#include "HidPlugin.h"
#include "HidError.h"
#include "HidPluginUtils.h"
#include "usd.h"
#include "usf.h"

#define MAX_EVENTS      64

typedef enum
{
    kHidUsdStateInvalid = -1,
    kHidUsdStateOff,
    kHidUsdStateOn
} HidUsdState_t;

typedef struct UsdPluginPrvInfo UsdPluginPrvInfo_t;

typedef void (UsdToInputFn_t)(const struct usf_event* pUsdEvent, InputEvent_t* pInputEvent);

typedef bool (HidUsdChangeStateFn_t)(const UsdPluginPrvInfo_t* pPluginPrvInfo, HidUsdState_t newState, HidError_t** ppErr);

typedef struct HidUsdEventSource HidUsdEventSource_t;

/**
 *  Used to create a "generic" plugin that reads from usdlib */
struct UsdPluginPrvInfo
{
    ReportFn_t* pReportFn;              /**< function that reports events */
    PluginInfo_t hidPluginInfo;         /**< plugin info passed by Init() */
    EventReaderFn_t* pEventReaderFn;    /**< function to be called in a new thread to read events */

    UsdToInputFn_t* pUsdToInputFn;      /**< callback to convert usd events into
                                             @ref InputEvent_t events suitable for hidd */
    const char* pDeviceType;            /**< usd device type */
    const char* pId;                    /**< usd id */
    uint32_t usdFlags;                  /**< usd flags */
    struct usf_event* pUsdEvents;
    int numUsdEvents;
    HidUsdState_t curState;             /**< current state */
    HidUsdState_t suspendState;         /**< saved state during suspend */
    HidUsdChangeStateFn_t* pChangeStateOnFn;  /**< callback to turn device on */
    HidUsdChangeStateFn_t* pChangeStateOffFn;  /**< callback to turn device off */
    HidUsdEventSource_t* pEventSource;     /**< event and wakeup source */
    IpcSetupFn_t* pIpcSetupFn;          /**< function to be called to register IPC callbacks */
    pthread_t thread;                   /**< thread id of event reader */
    bool threadRunning;                 /**< whether the reader thread is currently running */
    pthread_mutex_t threadMutex;        /**< protects state transitioning of the plugin */
};

bool HidUsdSet(UsdPluginPrvInfo_t* pPluginPrvInfo, const char* pName, const char* pValue, HidError_t** ppErr);
bool HidUsdGet(UsdPluginPrvInfo_t* pPluginPrvInfo, const char* pName, char** ppValue, HidError_t** ppErr);
    
bool HidUsdChangeState(UsdPluginPrvInfo_t* pPluginPrvInfo, HidUsdState_t newState, HidError_t** ppErr);

GSource* HidUsdAddTimeoutCallback(const UsdPluginPrvInfo_t* pPluginPrvInfo,
                         int priority, int ms, GSourceFunc func, void* pData,
                         GDestroyNotify notify, HidError_t** ppErr);

void HidUsdRemoveTimeoutCallback(const UsdPluginPrvInfo_t* pPluginPrvInfo, GSource** ppSource);

PmErr HidAllocUsdEventSource(const char* pDeviceType, const char* pId, uint32_t flags, struct usf_event* pUsdEvents, int numUsdEvents, UsdToInputFn_t* pUsdToInputFn, HidUsdEventSource_t** ppSrc);
void HidFreeUsdEventSource(HidUsdEventSource_t** ppSrc);

PmErr HidReadUsdEventSource(HidUsdEventSource_t* pSrc, int maxInputEvents, InputEvent_t* pEvents, int* pNumEvents);

PmErr HidSleepUsdEventSource(HidUsdEventSource_t* pSrc, int ms);

PmErr HidPluginUsdGenericSleepWithWakeup(const UsdPluginPrvInfo_t* pPluginPrvInfo, int ms);

PmErr HidPluginUsdGenericStartReaderThread(UsdPluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginUsdGenericStopReaderThread(UsdPluginPrvInfo_t* pPluginPrvInfo);

PmErr HidPluginUsdGenericGetEvents(const UsdPluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginUsdGenericInit(const PluginInfo_t* pPluginInfo, UsdPluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginUsdGenericExit(UsdPluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginUsdGenericSuspend(UsdPluginPrvInfo_t* pPluginPrvInfo);
PmErr HidPluginUsdGenericResume(UsdPluginPrvInfo_t* pPluginPrvInfo);

/** @} */

#endif  /* __HID_PLUGINS_USD_UTILS_H */
