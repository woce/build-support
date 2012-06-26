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
 * @file HidControlIpc.h
 *
 * @brief Public header file for HidControlIpc.c
 *******************************************************************************
 */

#ifndef __HID_CONTROL_IPC_H
#define __HID_CONTROL_IPC_H

/**
 * @addtogroup hidlib_control_ipc_public
 *
 * @{
 */

#include <cjson/json.h>
#include <stdint.h>
#include "HidPlugin.h"
#include "HidError.h"

/**
 *******************************************************************************
 * @brief  Callback that is called when "mode" is "get".
 *
 * @param  ppValue  OUT  the return value which should be created with @ref HidStringNew
 * @param  ppErr    OUT  should be created when an error occurs using @ref HidErrorNew
 *
 * @retval  true on success
 * @retval  false on failure
 *******************************************************************************
 */
typedef bool (HidIpcGetCallback_t)(char** ppValue, HidError_t** ppErr);

/**
 *******************************************************************************
 * @brief  Callback that is called when "mode" is "set".
 *
 * @param  pValue   IN   the string passed in as "value" in the JSON message
 * @param  ppErr    OUT  should be created when an error occurs using @ref HidErrorNew
 *
 * @retval  true on success
 * @retval  false on failure
 *******************************************************************************
 */
typedef bool (HidIpcSetCallback_t)(const char* pValue, HidError_t** ppErr);

/**
 *  Used to define the sysfs-like callbacks for a plugin
 */
typedef struct HidIpcCallbackInfo
{
    const char* pName;                  /**< name of the method */
    HidIpcGetCallback_t* pGetCallback;  /**< called when "mode" is set to "get" */
    HidIpcSetCallback_t* pSetCallback;  /**< called when "mode" is set to "set" */
} HidIpcCallbackInfo_t;

PmErr HidIpcRegisterCallbacks(const PluginInfo_t* pPluginInfo, const HidIpcCallbackInfo_t* pCallbackInfo);

typedef bool (HidIpcSignalCallback_t)(struct json_object* pJson, void* pUserData);

/**
 *  Used to define signal callbacks for a plugin
 */
typedef struct HidIpcSignalCallbackInfo
{
    const char* pMethod;                        /**< name of the method */
    const char* pCategory;                      /**< name of category */
    void* pUserData;                            /**< any custom data to pass to callback */
    HidIpcSignalCallback_t* pSignalCallback;    /**< called when the signal is received */
} HidIpcSignalCallbackInfo_t;

PmErr HidIpcRegisterSignalCallbacks(const PluginInfo_t* pPluginInfo, const HidIpcSignalCallbackInfo_t* pCallbackInfo);

PmErr HidIpcSendSignal(const char *uri, const char *payload);

PmErr HidIpcCall(const char *uri, const char *payload);

/** @} */

#endif  /* __HID_CONTROL_IPC_H */
