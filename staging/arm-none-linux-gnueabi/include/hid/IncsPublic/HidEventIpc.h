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
 * @file HidEventIpc.h
 * 
 * @brief Public header file for HidEventIpc.c
 *******************************************************************************
 */

#ifndef __HID_EVENT_IPC_H
#define __HID_EVENT_IPC_H

#include <stdbool.h>
#include "HidError.h"
#include "HidEvent.h"

/** 
 * @defgroup hidlib_event_ipc_public HidLib Public Event IPC Details
 *
 * @ingroup hidlib_public
 *
 * @brief Plugin event IPC abstraction
 *
 * @{
 */

/** Default XML file containing plugin settings */
#define HID_DEFAULT_XML_FILE    "/etc/hidd/HidPlugins.xml"
#define HID_QEMU_XML_FILE       "/etc/hidd/HidPlugins.xml"

#define HID_KEYPAD          "HidKeypad"             /**< keypad plugin name */
#define HID_TOUCHPANEL      "HidTouchpanel"         /**< touchpanel plugin name */
#define HID_ACCELEROMETER   "HidAccelerometer"      /**< accelerometer plugin name */
#define HID_COMPASS         "HidCompass"            /**< compass plugin name */
#define HID_LIGHT           "HidLight"              /**< light sensor plugin name */
#define HID_PROXIMITY       "HidProximity"          /**< proximity sensor plugin name */
#define HID_INPUT_DEV       "HidInputDev"           /**< hot-pluggable input devices */
#define HID_FUSION          "HidFusion"             /**< fusion plugin name */


/** Internal definition; don't access members of struct directly */
struct HidPluginSettings
{
    const char* pName;
    const char* pPath;
    const char* pEventSocketAddress;
    const char* pCmdSocketAddress;
    bool eventsDeferIdle;
};

typedef struct HidPluginSettings HidPluginSettings_t;
typedef struct HidHandle HidHandle_t;

PmErr HidInitPluginTransport(const char* pName, HidPluginSettings_t* pSettings, int numPlugins, HidHandle_t** ppHandle);
PmErr HidDestroyPluginTransport(HidHandle_t** ppHandle);
PmErr HidAllocPluginSettings(const char* pXmlFile, HidPluginSettings_t** ppSettings, int* pNumPlugins);
PmErr HidFreePluginSettings(HidPluginSettings_t** ppSettings, int numPlugins);
int HidHandleGetFd(HidHandle_t* pHandle);
int HidHandleReadInputEvent(HidHandle_t* pHandle, InputEvent_t* pEvents, int maxEvents);

/** @} */

#endif  /* __HID_EVENT_IPC_H */
