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
 * @file hal_sensor_magnetic_field.h
 *
 * @brief definition of HAL's public API for accessing magnetic_field
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_MAGNETIC_FIELD_H_
#define _HAL_SENSOR_MAGNETIC_FIELD_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_magnetic_field_public HAL's public magnetic_field API.
* @ingroup hal_public
* @brief HAL's public magnetic_field API.
* @{
*/

/**
 * Definition of magnetic field event type.
 */
typedef struct {

    int x;	/**< strength of magnetic field for x-axis in micro Teslas */
    int y;	/**< strength of magnetic field for y-axis in micro Teslas */
    int z;	/**< strength of magnetic field for z-axis in micro Teslas */

    int raw_x;	/**< raw strength of magnetic field for x-axis in micro Teslas */
    int raw_y;	/**< raw strength of magnetic field for y-axis in micro Teslas */
    int raw_z;	/**< raw strength of magnetic field for z-axis in micro Teslas */

} hal_sensor_magnetic_field_event_item_t;

/**
 * Get the event items for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	event_out_ptr - pointer to the magnetic_field event item
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_magnetic_field_event_get_item(hal_event_handle_t handle, hal_sensor_magnetic_field_event_item_t *event_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif


#endif /* _HAL_SENSOR_MAGNETIC_FIELD_H_ */
