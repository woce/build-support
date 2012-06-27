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
 * @file hal_led_controller.h
 *
 * @brief
 *
 *******************************************************************************
 */


#ifndef _HAL_LED_CONTROLLER_H_
#define _HAL_LED_CONTROLLER_H_

#include <hal/hal_led_controller_core_configuration.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_led_controller_public HAL's public led_controller API.
* @ingroup hal_public
* @brief HAL's public led_controller API.
* @{
*/

typedef enum {
	HAL_LED_CONTROLLER_NONE_LED		= 0,
	HAL_LED_CONTROLLER_LEFT_LED		= 0x01,
	HAL_LED_CONTROLLER_CENTER_LED	= 0x02,
	HAL_LED_CONTROLLER_RIGHT_LED	= 0x04,
	HAL_LED_CONTROLLER_KEYPAD		= 0x08,
	HAL_LED_CONTROLLER_LCD			= 0x10,
	HAL_LED_CONTROLLER_CORE_LEDS		=
			HAL_LED_CONTROLLER_LEFT_LED | HAL_LED_CONTROLLER_CENTER_LED | HAL_LED_CONTROLLER_RIGHT_LED,
	HAL_LED_CONTROLLER_BACKLIGHT_LEDS =
			HAL_LED_CONTROLLER_KEYPAD | HAL_LED_CONTROLLER_LCD,
	HAL_LED_CONTROLLER_ALL_LEDS =
			HAL_LED_CONTROLLER_LEFT_LED | HAL_LED_CONTROLLER_CENTER_LED | HAL_LED_CONTROLLER_RIGHT_LED |
			HAL_LED_CONTROLLER_KEYPAD | HAL_LED_CONTROLLER_LCD,
} led_controller_led_t;



typedef struct {
	struct {
		led_controller_led_t led;
		led_controller_effect_type_t effect;
	} required;

	/*
	 * backlight structure is used to provide parameters of the lcd/keypad
	 * backlight control.
	 */
	struct {
		int brightness_lcd;
		int brightness_keypad;
		hal_device_callback callback;
		void* callback_context;
	} backlight;


	/*
	 * core configuration structure is used to provide parameters of the core led
	 * control.
	 */
    hal_led_controller_core_configuration_handle_t core_configuration;

} led_controller_effect_t;

typedef enum {
    HAL_LED_CONTROLLER_STATE_UNKNOWN,
    HAL_LED_CONTROLLER_STATE_OFF,
    HAL_LED_CONTROLLER_STATE_ON,
} led_controller_state_t;


/*
 * Execute effect on the led controller.
 *
 * @param[in] 	handle - The device handle.
 * @param[in] 	effect - effect description and parameters.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_led_controller_execute_effect(hal_device_handle_t handle, led_controller_effect_t effect);

/*
 * Stop effect/s on give leds.
 *
 * @param[in] 	handle - The device handle.
 * @param[in] 	led - led mask for leds to stop.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_led_controller_stop(hal_device_handle_t handle, led_controller_led_t led);

/*
 * Get the state of leds.
 *
 * @param[in] 	handle - The device handle.
 * @param[in] 	led - led that you want the state of
 * @param[out] 	state_out_ptr - ptr to hold state of led
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_led_controller_get_state(hal_device_handle_t handle,
        led_controller_led_t led, led_controller_state_t* state_out_ptr);



/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_LED_CONTROLLER_H_ */
