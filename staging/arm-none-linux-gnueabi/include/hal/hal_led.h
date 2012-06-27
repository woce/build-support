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
 * @file hal_led.h
 *
 * @brief definition of HAL's public API for accessing LED device.
 *
 *******************************************************************************
 */

#ifndef _HAL_LED_H_
#define _HAL_LED_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_led_public HAL's public led API.
* @ingroup hal_public
* @brief HAL's public led APIs.
* @{
*/

/**
 * Set the brightness of the LED device. The range is 0-100%
 *
 * @param[in] 	handle - The device handle.
 * @param[in] 	brightness - brightness to set.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_led_set_brightness(hal_device_handle_t handle, int brightness);

/**
 * Get the brightness of the LED device. The range is 0-100%
 *
 * @param[in] 	handle - The device handle.
 * @param[out] 	brightness_out_ptr - pointer to store current brightness of the LED device.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_led_get_brightness(hal_device_handle_t handle, int *brightness_out_ptr);

/** @} */ 

#ifdef __cplusplus
}
#endif

#endif /* _HAL_LED_H_ */
