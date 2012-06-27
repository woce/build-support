/* @@@LICENSE
*
*      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */

/**
 *******************************************************************************
 * @file hal_macros.h
 *
 * @brief definition of HAL's macros.
 *
 *******************************************************************************
 */

#ifndef _HAL_MACORS_H_
#define _HAL_MACORS_H_

#define API_EXPORT __attribute__((visibility("default")))
#define API_IMPORT __attribute__((visibility("default")))
#define API_LOCAL __attribute__((visibility("hidden")))
#define API_INTERNAL __attribute__((visibility("internal")))

#endif // _HAL_MACORS_H_

