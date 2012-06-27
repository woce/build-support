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
 * @file hal_sensor_als.h
 *
 * @brief definition of HAL's public API for accessing als
 * device and events it generates.
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_ALS_H_
#define _HAL_SENSOR_ALS_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_als_public HAL's public als (ambient light sensor) API.
* @ingroup hal_public
* @brief HAL's public  als (ambient light sensor)API.
* @{
*/

/**
 * Get the light intensity value of the als (ambient light sensor) event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	intensity_in_lux_out_ptr - pointer to light intensity value (in lux) of the als event.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_als_event_get_intensity(hal_event_handle_t handle, int* intensity_in_lux_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_SENSOR_ALS_H_ */
