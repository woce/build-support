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
 * @file hal_core.h
 *
 * @brief
 *
 *******************************************************************************
 */


#ifndef _HAL_CORE_H_
#define _HAL_CORE_H_

#include <hal/hal_error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_core_public HAL's public core API.
* @ingroup hal_public
* @brief HAL's public  core APIs.
* @{
*/

/**
 * Initializes HAL library.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
hal_error_t hal_init(void);

/**
 * Deinitializes HAL library.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
hal_error_t hal_deinit(void);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_CORE_H_ */
