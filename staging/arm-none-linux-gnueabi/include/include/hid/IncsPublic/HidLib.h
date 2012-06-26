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
 * @file HidLib.h
 * 
 * @brief Public header file for hidlib. Plugins and utilities using hidlib
 * should include this file.
 *******************************************************************************
 */
#ifndef __HID_LIB_H
#define __HID_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup hidlib HidLib Documentation
 *
 * @brief HidLib Documentation
 */

/** 
 * @defgroup hidlib_public HidLib Public API
 * @ingroup hidlib
 * @brief Public API for HidLib.
 */

/**
 * @defgroup hidlib_protected HidLib Protected API
 * @ingroup hidlib
 * @brief Protected API that you should not use unless you know what you are
 * doing.
 */

/**
 * @defgroup hidlib_internal HidLib Internal Details
 * @ingroup hidlib
 * @brief Internal implementation detail useful for developing or debugging
 * HidLib.
 */

#include "HidDebug.h"
#include "HidControlIpc.h"
#include "HidSysfs.h"
#include "HidError.h"
#include "HidUtils.h"
#include "HidTime.h"
#include "HidEvent.h"
#include "HidPlugin.h"
#include "HidPluginUtils.h"
#include "HidEventIpc.h"

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* __HID_LIB_H */
