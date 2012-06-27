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
 * @file hal_haptics.h
 *
 * @brief definition of HAL's public API for accessing haptics device.
 *
 *******************************************************************************
 */

#ifndef _HAL_HAPTICS_H_
#define _HAL_HAPTICS_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_haptics_public HAL's public haptics API.
* @ingroup hal_public
* @brief HAL's public  haptics API.
* @{
*/



/**
 * This type is an enum describing the types of haptics effects
 */
typedef enum
{
    HAPTICS_EFFECT_UNDEFINED = 0,   /**< value HAPTICS_EFFECT_UNDEFINED. */
    HAPTICS_EFFECT_RINGTONE,        /**< value HAPTICS_EFFECT_RINGTONE. */
    HAPTICS_EFFECT_ALERT,           /**< value HAPTICS_EFFECT_ALERT. */
    HAPTICS_EFFECT_NOTIFICATION,    /**< value HAPTICS_EFFECT_NOTIFICATION. */
    HAPTICS_EFFECT_TAPDOWN,         /**< value HAPTICS_EFFECT_TAPDOWN. */
    HAPTICS_EFFECT_TAPUP,           /**< value HAPTICS_EFFECT_TAPUP. */


} haptics_effect_type_t;


/**
 * This type is an enum describing the direction for a custom haptics effect
 */
typedef enum
{
    HAPTICS_DIRECTION_RIGHT,        /**< value HAPTICS_DIRECTION_RIGHT. */
    HAPTICS_DIRECTION_LEFT,         /**< value HAPTICS_DIRECTION_LEFT. */

} haptics_direction_t;

typedef struct
{
    int period;
    int duration;
    haptics_direction_t direction;
    haptics_effect_type_t type;

} haptics_configuration_t;


/**
 * Vibrate with the configuration specified
 *  The configuration should either identify the type of effect (launching an effect that the
 *      device already has preconfigured), or contain values for the period, duration, and direction
 *      fields
 *
 * @param[in] 	handle - the device handle.
 * @param[in] 	configuration - structure containing effect data
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_haptics_vibrate(hal_device_handle_t handle, haptics_configuration_t configuration);

/**
 * Cancel the haptics effect id specified
 *
 * @param[in] 	handle - the device handle.
 * @param[in] 	haptics_id - id of the haptics effect to cancel
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_haptics_cancel(hal_device_handle_t handle, int haptics_id);

/**
 * Cancel all haptics effects
 *
 * @param[in] 	handle - the device handle.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_haptics_cancel_all(hal_device_handle_t handle);

/**
 * Get the haptics effect id associated with this device
 *
 * @param[in] 	handle - the device handle.
 * @param[out] 	haptics_id_out_ptr - ptr to store the haptics id
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_haptics_get_effect_id(hal_device_handle_t handle, int* haptics_effect_id_out_ptr);

/**
 * Set the dampening factor associated with this device handle
 *  The dampening factor is a single value to tone down the magnitude of haptics effects
 *      When the device is initially opened, the dampening factor is 100, signifying 100% of
 *      magnitude specified.  If the dampening factor is set to 50, the magnitude of the effect
 *      will be 50% of the originally specified magnitude.  This can be used for tuning the effect.
 *
 * @param[in] 	handle - the device handle.
 * @param[in] 	dampening_factor - value of new dampening factor
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_haptics_set_dampening_factor(hal_device_handle_t handle, int dampening_factor);

/**
 * Get the dampening factor associated with this device handle
 *  The dampening factor is a single value to tone down the magnitude of haptics effects
 *      When the device is initially opened, the dampening factor is 100, signifying 100% of
 *      magnitude specified.  If the dampening factor is set to 50, the magnitude of the effect
 *      will be 50% of the originally specified magnitude.  This can be used for tuning the effect.
 *
 * @param[in] 	handle - the device handle.
 * @param[out] 	dampening_factor_out_ptr - ptr to store value of dampening factor
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_haptics_get_dampening_factor(hal_device_handle_t handle, int* dampening_factor_out_ptr);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HAL_HAPTICS_H_ */
