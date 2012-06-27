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
 * @file hal_sensor_rotation.h
 *
 * @brief definition of HAL's public API for accessing rotation
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_ROTATION_H_
#define _HAL_SENSOR_ROTATION_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_rotation_public HAL's public rotation API.
* @ingroup hal_public
* @brief HAL's public rotation API.
* @{
*/


typedef struct
{
    float w;
    float x;
    float y;
    float z;
} hal_sensor_rotation_quaternion_vector_t;

typedef struct {
    float roll;       /**< amount of roll in degrees */
    float pitch;      /**< amount of pitch in degrees */
    float yaw;        /**< amount of yaw in degrees */
} hal_sensor_rotation_euler_angle_t;

/**
 * Definition of rotation event type.
 */
typedef struct {

    /** Rotation matrix */
    float matrix[9];
    /** Quaternion vector of rotation */
    hal_sensor_rotation_quaternion_vector_t quaternion_vector;
    /** Euler angle of rotation (in degrees) */
    hal_sensor_rotation_euler_angle_t euler_angle;

} hal_sensor_rotation_event_item_t;

/**
 * Get the event items for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	event_out_ptr - pointer to the rotation event item
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_rotation_event_get_item(hal_event_handle_t handle, hal_sensor_rotation_event_item_t *event_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif


#endif /* _HAL_SENSOR_ROTATION_H_ */
