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
 * @file hal_sensor_bearing.h
 *
 * @brief definition of HAL's public API for accessing bearing
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_BEARING_H_
#define _HAL_SENSOR_BEARING_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_bearing_public HAL's public bearing API.
* @ingroup hal_public
* @brief HAL's public bearing API.
* @{
*/

/**
 * Definition of type for specifying location 
 */
typedef struct {
	float longitude;    /**< location longitude in degrees */
	float latitude;     /**< location latitude in degrees */
	float altitude;     /**< altitude in meters */
} hal_sensor_bearing_location_t;

/**
 * Definition of bearing event type.
 */
typedef struct {

    float magnetic;        /**< magnetic bearing in degrees */
    float true_bearing;    /**< true bearing in degrees */
    float confidence;      /**< confidence of bearing values in percent (%) */

} hal_sensor_bearing_event_item_t;

/**
 * Get the event items for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	event_out_ptr - pointer to the bearing event item
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_bearing_event_get_item(hal_event_handle_t handle, hal_sensor_bearing_event_item_t *event_out_ptr);

/**
 * Get the device's global location.
 *
 * @param[in]  handle the device handle.
 * @param[out] location the device's location as defined in @ref hal_sensor_bearing_location_t.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 */
API_EXPORT hal_error_t hal_sensor_bearing_get_location(hal_device_handle_t handle, hal_sensor_bearing_location_t* location);

/**
 * Set the device's global location.
 *
 * @param[in]  handle the device handle.
 * @param[in]  location the device's location as defined in @ref hal_sensor_bearing_location_t.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 */
API_EXPORT hal_error_t hal_sensor_bearing_set_location(hal_device_handle_t handle, hal_sensor_bearing_location_t* new_location);

/** @} */
#ifdef __cplusplus
}
#endif


#endif /* _HAL_SENSOR_BEARING_H_ */
