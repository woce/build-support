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
 * @file hal_sensor_orientation.h
 *
 * @brief definition of HAL's public API for accessing orientation
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_ORIENTATION_H_
#define _HAL_SENSOR_ORIENTATION_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_orientation_public HAL's public orientation API.
* @ingroup hal_public
* @brief HAL's public orientation API.
* @{
*/

/**
 * hal_sensor_orientation_value_t
 * This type is an enum describing the value of the orientation event.
 */
typedef enum {
	HAL_SENSOR_ORIENTATION_UNDEFINED,	/**< Device orientation is unknown */
	HAL_SENSOR_ORIENTATION_FACE_UP,	/**< Device is facing up */
	HAL_SENSOR_ORIENTATION_FACE_DOWN,	/**< Device is facing down */
	HAL_SENSOR_ORIENTATION_FACE_FORWARD,	/**< Device is in normal, portrait orientation */
	HAL_SENSOR_ORIENTATION_FACE_BACK,		/**< Device is in upside-down, portrait orientation */
	HAL_SENSOR_ORIENTATION_LEFT,		/**< Device has left side facing down */
	HAL_SENSOR_ORIENTATION_RIGHT,		/**< Device has right side facing down */
} hal_sensor_orientation_value_t;

/**
 * Definition of threshold values in x,y,z axis for orientation event.
 * The orientation (in degrees) must be greater than threshold for an event to be emitted.
 */
typedef struct {
	int x;        /**< Threshold (minimum rotation) for x-axis in degrees */
	int y;        /**< Threshold (minimum rotation) for y-axis in degrees */
	int z;        /**< Threshold (minimum rotation) for z-axis in degrees */
} hal_sensor_orientation_threshold_t;

	   
/**
 * Definition of orientation event type.
 */
typedef struct {

    hal_sensor_orientation_value_t value;	/**< orientation value of type @ref hal_sensor_orientation_value_t. */

} hal_sensor_orientation_event_item_t;

/**
 * Get the event items for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	event_out_ptr - pointer to the orientation event item
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_orientation_event_get_item(hal_event_handle_t handle, hal_sensor_orientation_event_item_t *event_out_ptr);

/**
 * Get the threshold values for the orientation sensor.
 *
 * @param[in]  handle the device handle.
 * @param[out] threshold orientation threshold values as defined by @ref hal_sensor_orientation_threshold_t.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 */
API_EXPORT hal_error_t hal_sensor_orientation_get_threshold(hal_device_handle_t handle, hal_sensor_orientation_threshold_t* threshold);

/**
 * Set the threshold values for the orientation sensor.
 *
 * @param[in]  handle the device handle.
 * @param[in]  new_threshold orientation threshold values to set as defined by @ref hal_sensor_orientation_threshold_t.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 */
API_EXPORT hal_error_t hal_sensor_orientation_set_threshold(hal_device_handle_t handle, hal_sensor_orientation_threshold_t* new_threshold);

/** @} */
#ifdef __cplusplus
}
#endif



#endif /* _HAL_SENSOR_ORIENTATION_H_ */
