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
 * @file hal_keys.h
 *
 * @brief definition of HAL's public API for accessing keyboard
 * device and events it generates.
 *
 *******************************************************************************
 */

#ifndef _HAL_KEYS_H_
#define _HAL_KEYS_H_

#include <hal/hal_device.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_keys_public HAL's public keys API.
* @ingroup hal_public
* @brief HAL's public keys APIs.
* @{
*/

/**
 * hal_key_type_t
 * This type is an enum describing the type of the keyboard event.
 * If keyboard_key_type_standard is returned, keys are defined by Linux keycodes
 * If keyboard_key_type_custom is returned, keys are specific to WebOs and their
 *     values should be referenced from hal_keys_custom_key_t
 */
typedef enum {
          HAL_KEY_TYPE_UNDEFINED, 	/**< value keyboard_key_type_undefined. */
          HAL_KEY_TYPE_STANDARD,  	/**< value keyboard_key_type_standard. */
          HAL_KEY_TYPE_CUSTOM,	/**< value keyboard_key_type_custom. */
} hal_key_type_t;


/**
 * hal_keys_custom_key_t
 * This type is an enum describing the WebOs specific keys
 */
typedef enum {
         HAL_KEYS_CUSTOM_KEY_UNDEFINED,			/**< value HAL_KEYS_CUSTOM_KEY_UNDEFINED. */
         HAL_KEYS_CUSTOM_KEY_VOL_UP,			/**< value HAL_KEYS_CUSTOM_KEY_VOL_UP. */
         HAL_KEYS_CUSTOM_KEY_VOL_DOWN,			/**< value HAL_KEYS_CUSTOM_KEY_VOL_DOWN. */
         HAL_KEYS_CUSTOM_KEY_POWER_ON,			/**< value HAL_KEYS_CUSTOM_KEY_POWER_ON. */
         HAL_KEYS_CUSTOM_KEY_HOME,				/**< value HAL_KEYS_CUSTOM_KEY_HOME. */
         HAL_KEYS_CUSTOM_KEY_RINGER_SW,			/**< value HAL_KEYS_CUSTOM_KEY_RINGER_SW. */
         HAL_KEYS_CUSTOM_KEY_SLIDER_SW,			/**< value HAL_KEYS_CUSTOM_KEY_SLIDER_SW. */
         HAL_KEYS_CUSTOM_KEY_HEADSET_BUTTON,    /**< value HAL_KEYS_CUSTOM_KEY_HEADSET_BUTTON. */
         HAL_KEYS_CUSTOM_KEY_HEADSET_PORT,		/**< value HAL_KEYS_CUSTOM_KEY_HEADSET_PORT. */
         HAL_KEYS_CUSTOM_KEY_HEADSET_PORT_MIC,	/**< value HAL_KEYS_CUSTOM_KEY_HEADSET_PORT_MIC. */
         HAL_KEYS_CUSTOM_KEY_OPTICAL,			/**< value HAL_KEYS_CUSTOM_KEY_OPTICAL. */

         HAL_KEYS_CUSTOM_KEY_MEDIA_PLAY,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_PLAY. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_PAUSE,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_PAUSE. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_STOP,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_STOP. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_NEXT,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_NEXT. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_PREVIOUS,/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_PREVIOUS. */

         HAL_KEYS_CUSTOM_KEY_MEDIA_REPEAT_ALL,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_REPEAT_ALL. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_REPEAT_TRACK,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_REPEAT_TRACK. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_REPEAT_NONE,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_REPEAT_NONE. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_SHUFFLE_ON,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_SHUFFLE_ON. */
         HAL_KEYS_CUSTOM_KEY_MEDIA_SHUFFLE_OFF,	/**< value HAL_KEYS_CUSTOM_KEY_MEDIA_SHUFFLE_OFF. */
} hal_keys_custom_key_t;


/**
 * Get the key for the current event.
 * If the key type is standard, then the keyCode is returned and left to caller to lookup in keymap.
 * No keys are consumed.
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	key_out_ptr - pointer to store key value
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_keys_event_get_key(hal_event_handle_t handle, int* key_out_ptr);

/**
 * Get the key type for the current event.
 * Key type will be standard or custom (webos specific type)
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	key_type_out_ptr - pointer to store key type
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_keys_event_get_key_type(hal_event_handle_t handle, hal_key_type_t* key_type_out_ptr);

/**
 * Get the is_key_press for the current event.
 * Value is 1 if it is a down event, 0 if it is an up event
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	key_is_press_out_ptr - pointer to store is_press value
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_keys_event_get_key_is_press(hal_event_handle_t handle, bool* key_is_press_out_ptr);

/**
 * Get the is_auto_repeat for the current event.
 * If is_auto_repeat is true for the current key, that means that this key was previously in a down state
 * and the new event is a the same key in a down state
 *
 * @param[in] 	handle - the event handle.
 * @param[out] 	key_is_auto_repeat_out_ptr - pointer to store is_auto_repeat value
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_keys_event_get_key_is_auto_repeat(hal_event_handle_t handle, bool* key_is_auto_repeat_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_KEYS_H_ */
