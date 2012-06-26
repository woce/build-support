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
 * @file hal_sensor_proximity.h
 *
 * @brief definition of HAL's public API for accessing proximity
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_PROXIMITY_H_
#define _HAL_SENSOR_PROXIMITY_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_proximity_public HAL's public proximity API.
* @ingroup hal_public
* @brief HAL's public proximity API.
* @{
*/


/**
 * Get the event items for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	present_out_ptr - pointer to the proximity presence value of the proximity event.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_proximity_event_get_presence(hal_event_handle_t handle, int* present_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif


#endif /* _HAL_SENSOR_PROXIMITY_H_ */
