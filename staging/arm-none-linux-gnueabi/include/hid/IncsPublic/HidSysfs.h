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
 * @file HidSysfs.h
 * 
 * @brief Public header file for HidSysfs.c.
 *******************************************************************************
 */

#ifndef __HID_SYSFS_H
#define __HID_SYSFS_H

#include "HidPlugin.h"
#include "HidError.h"

char* HidFindSysfsPath(const char* pDevSymLink);

bool HidGetSysfsString(const PluginInfo_t* pPluginInfo, const char* pSysfsFile,
                       char** ppString, HidError_t** ppErr);

bool HidSetSysfsString(const PluginInfo_t* pPluginInfo, const char* pSysfsFile,
                       const char* pBuf, HidError_t** ppErr);

#endif  /* __HID_SYSFS_H */
