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
 * @file hal_sensor_angular_velocity.h
 *
 * @brief definition of HAL's public API for accessing angular_velocity
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_ANGULAR_VELOCITY_H_
#define _HAL_SENSOR_ANGULAR_VELOCITY_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_angular_velocity_public HAL's public angular_velocity API.
* @ingroup hal_public
* @brief HAL's public angular_velocity API.
* @{
*/


/**
 * Definition of angular velocity event type.
 */
typedef struct {

    float x;	/**< angular velocity around x-axis in radians per second */
    float y;	/**< angular velocity around y-axis in radians per second */
    float z;	/**< angular velocity around z-axis in radians per second */

} hal_sensor_angular_velocity_event_item_t;

/**
 * Get the event item for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	event_out_ptr - pointer to the angular_velocity event item
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_angular_velocity_event_get_item(hal_event_handle_t handle, hal_sensor_angular_velocity_event_item_t *event_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif


#endif /* _HAL_SENSOR_ANGULAR_VELOCITY_H_ */
