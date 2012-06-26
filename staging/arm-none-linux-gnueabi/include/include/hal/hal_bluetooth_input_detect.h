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
 * @file hal_bluetooth_input_detect.h
 *
 * @brief definition of HAL's public API for accessing bluetooth_input_detect
 * and events it generates.
 *
 *******************************************************************************
 */

#ifndef _HAL_BLUETOOTH_INPUT_DETECT_H_
#define _HAL_BLUETOOTH_INPUT_DETECT_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_bluetooth_input_detect_public HAL's public bluetooth_input_detect API.
* @ingroup hal_public
* @brief HAL's public  bluetooth_input_detect API -- this is meant to be temporary API and deprecated in vers. 2.0
* @{
*/

/**
 * hal_bluetooth_input_detect_event_type_t
 * This type is an enum describing the type of the bluetooth_input_detect event.
 */
typedef enum
{
    HAL_BLUETOOTH_INPUT_DETECT_EVENT_UNDEFINED = 0,	        /**< value HAL_BLUETOOTH_INPUT_DETECT_EVENT_UNDEFINED. */
    HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_ID_ADD,         /**< value HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_ID_ADD. */
    HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_ID_REMOVE,      /**< value HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_ID_REMOVE. */
    HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_KEYBOARD_TYPE,  /**< value HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_KEYBOARD_TYPE. */
    HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_COUNTRY,        /**< value HAL_BLUETOOTH_INPUT_DETECT_EVENT_DEVICE_COUNTRY. */

} hal_bluetooth_input_detect_event_type_t;

typedef struct
{
    hal_bluetooth_input_detect_event_type_t event_type;
    int value;

} hal_bluetooth_input_detect_event_item_t;

/**
 * Get the data associated with the hal_bluetooth_input_detect event
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	item_out_ptr - pointer to bluetooth_input_detect_event_item of als event.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_bluetooth_input_detect_event_get_data(hal_event_handle_t handle, hal_bluetooth_input_detect_event_item_t* item_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_BLUETOOTH_INPUT_DETECT_H_ */
