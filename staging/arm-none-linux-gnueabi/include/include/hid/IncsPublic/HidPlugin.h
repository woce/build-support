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
 * @file HidPlugin.h
 * 
 * @brief Public header file for plugin related definitions.
 *******************************************************************************
 */
#ifndef __HID_PLUGIN_H
#define __HID_PLUGIN_H

#include <stdbool.h>
#include "HidError.h"
#include "HidEvent.h"

#define INVALID_FD  -1

typedef int PluginId_t;     /**< unique plugin id */

/**
 * Used to pass settings to the "gremlins" plugin
 */ 
typedef struct PluginDebugInfo
{
    long int maxEvents;         /**< max number of events to send        */
    long int rateLimit;         /**< throughput rate limit in events/sec */
    unsigned int randomSeed;    /**< seed used to generate events        */
    bool useRandomStamp;        /**< indicate we should generate a random timestamp
                                     rather than use one from GetTimeStamp() */
} PluginDebugInfo_t;

/**
 * Information passed to the plugin by the Init() function
 */
typedef struct PluginInfo {
    const char* pName;          /**< name of plugin as read from XML file */
    PluginId_t id;              /**< unique plugin id */
    PluginDebugInfo_t debug;    /**< settings for "gremlins" plugins */
} PluginInfo_t;

/**
 * The "report" function that gets called by the plugin when it receives an
 * event 
 */
typedef PmErr (ReportFn_t)(void*, int, EventType_t, PluginId_t);

/**
 * Each plugin must have one of these function tables, which specifies which
 * functions that will be called for each of the specified actions
 */
typedef struct PluginFuncTable {
    PmErr (*GetEventCallbackFn_t)(ReportFn_t*);
    PmErr (*InitFn_t) (PluginInfo_t*);
    PmErr (*ExitFn_t)(void);
    PmErr (*SuspendFn_t)(void);
    PmErr (*ResumeFn_t)(void);
    PmErr (*PollFn_t)(void);
} PluginFuncTable_t;

#endif  /* __HID_PLUGIN_H */
