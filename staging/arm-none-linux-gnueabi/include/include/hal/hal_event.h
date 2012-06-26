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
 * @file hal_event.h
 *
 * @brief definition of HAL's events and associated types.
 *
 *
 *******************************************************************************
 */

#ifndef _HAL_EVENT_H_
#define _HAL_EVENT_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
* @defgroup hal_event_public HAL's public event-related interface.
* @ingroup hal_public
* @brief HAL's public event-related inteface.
* @{
*/

/*
 * HAL device types
 */
typedef enum {
	HAL_EVENT_UNDEFINED,			/**< Undefined device type */
	HAL_EVENT_BLUETOOTH_INPUT_DETECT,	 /**< Bluetooth Input Detect*/
	HAL_EVENT_KEYS,				/**< Keys */
	HAL_EVENT_TOUCHPANEL,			/**< Touchpanel */
	HAL_EVENT_SENSOR_ACCELERATION,		/**< Acceleration */
	HAL_EVENT_SENSOR_ALS,				/**< Ambient light sensor */
	HAL_EVENT_SENSOR_ANGULAR_VELOCITY,	/**< Angular velocity */
	HAL_EVENT_SENSOR_BEARING,		/**< Bearing (heading) */
	HAL_EVENT_SENSOR_GRAVITY,		/**< Gravity */
	HAL_EVENT_SENSOR_LINEAR_ACCELERATION, 	/**< Linear Acceleration */
	HAL_EVENT_SENSOR_MAGNETIC_FIELD,	/**< Magnetic field */
	HAL_EVENT_SENSOR_ORIENTATION,		/**< Orientation */
	HAL_EVENT_SENSOR_PROXIMITY,		/**< Proximity */
	HAL_EVENT_SENSOR_ROTATION,		/**< Rotation */
	HAL_EVENT_SENSOR_SHAKE,			/**< Shake */
	HAL_EVENT_CUSTOM,			/**< Custom */
} hal_event_type_t;

struct hal_event;

/*
 * HAL handle to the event. Event's are opaque for clients.
 */
typedef struct hal_event* hal_event_handle_t;

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_EVENT_H_ */
