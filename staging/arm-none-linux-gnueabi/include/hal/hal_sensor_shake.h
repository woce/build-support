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
 * @file hal_sensor_shake.h
 *
 * @brief definition of HAL's public API for accessing shake
 * device and events it generates.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_SENSOR_SHAKE_H_
#define _HAL_SENSOR_SHAKE_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_sensor_shake_public HAL's public shake API.
* @ingroup hal_public
* @brief HAL's public shake sensor API.
* @{
*/

/**
 * hal_sensor_shake_state_t
 * An enum that describes the state of shaking on device.
 */
typedef enum {
    HAL_SENSOR_SHAKE_NONE,		/**< Device is not shaking */
    HAL_SENSOR_SHAKE_START,	/**< Device has started shaking */
    HAL_SENSOR_SHAKE_SHAKING,	/**< Device continues to shake */
    HAL_SENSOR_SHAKE_STOP,		/**< Device has stopped shaking */
} hal_sensor_shake_state_t;

typedef struct {

    hal_sensor_shake_state_t state;	/**< shaking state of type @ref hal_sensor_shake_state_t. */
    float magnitude;			/**< magnitude of shaking in meters per (second)^2 ?? */

} hal_sensor_shake_event_item_t;

/**
 * Get the event items for the current event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	event_out_ptr - pointer to the shake event item
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_sensor_shake_event_get_item(hal_event_handle_t handle, hal_sensor_shake_event_item_t *event_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif


#endif /* _HAL_SENSOR_SHAKE_H_ */
