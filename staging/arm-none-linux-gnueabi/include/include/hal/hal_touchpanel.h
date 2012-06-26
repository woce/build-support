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
 * @file hal_touchpanel.h
 *
 * @brief definition of HAL's public API for accessing touchpanel
 * device and events it generates.
 *
 *******************************************************************************
 */
#ifndef __HAL_TOUCHPANEL_H__
#define __HAL_TOUCHPANEL_H__

#include <hal/hal_device.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
* @defgroup hal_touchpanel_public HAL's public touchpanel interface.
* @ingroup hal_public
* @brief HAL's public touchpanel interface.
* @{
*/


/**
 * This type is an enum describing the touchpanel event.
 */
typedef enum {
        HAL_TOUCHPANEL_EVENT_TYPE_INVALID, /**< value HAL_TOUCHPANEL_EVENT_TYPE_INVALID. */
        HAL_TOUCHPANEL_EVENT_TYPE_TOUCH, 	/**< value HAL_TOUCHPANEL_EVENT_TYPE_TOUCH. */
        HAL_TOUCHPANEL_EVENT_TYPE_SCAN_COMPLETE, /**< value HAL_TOUCHPANEL_EVENT_TYPE_SCAN_COMPLETE. */

} hal_touchpanel_event_type_t;

/**
 * This type is an enum describing the state of the touchpanel event.
 */
typedef enum {
	HAL_TOUCHPANEL_STATE_UNDEFINED = -1, /**< value HAL_TOUCHPANEL_STATE_UNDEFINED. */
	HAL_TOUCHPANEL_STATE_DOWN, /**< value HAL_TOUCHPANEL_STATE_DOWN. */
	HAL_TOUCHPANEL_STATE_UP, /**< value HAL_TOUCHPANEL_STATE_UP. */
	HAL_TOUCHPANEL_STATE_MOVE, /**< value HAL_TOUCHPANEL_STATE_MOVE. */
} hal_touchpanel_state_t;

/**
 * This type is an enum used for setting current mode of the touchpanel.
 */
typedef enum {
    HAL_TOUCHPANEL_MODE_DEFAULT = 0, /**< value HAL_TOUCHPANEL_MODE_DEFAULT. */
    HAL_TOUCHPANEL_MODE_VIRTUAL_KEYBOARD = 1, /**< value HAL_TOUCHPANEL_MODE_VIRTUAL_KEYBOARD. */
} hal_touchpanel_mode_t;

typedef struct {

	int64_t	timestamp; /**< value timestamp of touch event. */
	unsigned int finger; /**< value finger of touch event. */
	hal_touchpanel_state_t state; /**< value state of touch event. */
	int x; /**< value x coordinate of touch event. */
	int y; /**< value y coordinate of touch event. */
	int gestureKey; /**< value gestureKey is the raw gesture key value to be interpretted by caller */
	int xVelocity; /**< value xVelocity is the xVelocity associated with the gestureKey */
	int yVelocity; /**< value yVelocity is the yVelocity associated with the gestureKey */
	double weight; /**< value weight of touch event. */

} hal_touchpanel_event_item_t;

/**
 * Get the active scan rate of the touchpanel.
 *
 * @param[in]   handle - the event handle.
 * @param[out]  active_scan_rate_out_ptr - pointer to store active scan rate
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_get_active_scan_rate(hal_device_handle_t handle, unsigned int* active_scan_rate_out_ptr);

/**
 * Get the idle scan rate of the touchpanel.
 *
 * @param[in]   handle - the event handle.
 * @param[out]  idle_scan_rate_out_ptr - pointer to store idle scan rate.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_get_idle_scan_rate(hal_device_handle_t handle, unsigned int* idle_scan_rate_out_ptr);

/**
 * Set the active scan rate of the touchpanel.
 *
 * @param[in]   handle - the event handle.
 * @param[in]   active_scan_rate_in - active scan rate to be set
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_set_active_scan_rate(hal_device_handle_t handle, unsigned int active_scan_rate_in);

/**
 * Set the idle scan rate of the touchpanel.
 *
 * @param[in]   handle - the event handle.
 * @param[in]   idle_scan_rate_in - idle scan rate to be set
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_set_idle_scan_rate(hal_device_handle_t handle, unsigned int idle_scan_rate_in);

/**
 * Get the current mode of the touchpanel.
 *
 * @param[in]   handle - the event handle.
 * @param[out]  mode_mask_out_ptr - pointer to store current mode(s)
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_get_mode(hal_device_handle_t handle, int *mode_mask_out_ptr);

/**
 * Set the current mode of the touchpanel.
 *
 * @param[in]   handle - the event handle.
 * @param[in]   mode_mask - mode(s) to be set
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_set_mode(hal_device_handle_t handle, int mode_mask);

/**
 * Get the type of the touchpanel event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	type_out_ptr - pointer to store type of touchpanel event
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_event_get_type(hal_event_handle_t handle, hal_touchpanel_event_type_t *type_out_ptr);

/**
 * Get the array of touches associated with the touchpanel event.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	touches_out_ptr - pointer to store array of touches
 * @param[out] 	count_out_ptr - number of valid touches in the array
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_touchpanel_event_get_touches(hal_event_handle_t handle, hal_touchpanel_event_item_t** touches_out_ptr,
    int *count_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif

#endif // __HAL_TOUCHPANEL_H__

