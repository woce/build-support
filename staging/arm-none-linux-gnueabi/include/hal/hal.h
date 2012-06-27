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
 * @file hal.h
 *
 * @brief HAL's main include file that includes all the necessary include files
 * to use HAL.
 *
 *******************************************************************************
 */

#ifndef _HAL_H_
#define _HAL_H_

#include <stdint.h>

#include <hal/hal_macros.h>
#include <hal/hal_error.h>
#include <hal/hal_event.h>

#include <hal/hal_core.h>

#include <hal/hal_device.h>

#include <hal/hal_bluetooth_input_detect.h>
#include <hal/hal_haptics.h>
#include <hal/hal_keys.h>
#include <hal/hal_led.h>
#include <hal/hal_led_controller.h>
#include <hal/hal_led_controller_core_configuration.h>
#include <hal/hal_touchpanel.h>

#include <hal/hal_sensor_acceleration.h>
#include <hal/hal_sensor_als.h>
#include <hal/hal_sensor_angular_velocity.h>
#include <hal/hal_sensor_bearing.h>
#include <hal/hal_sensor_gravity.h>
#include <hal/hal_sensor_linear_acceleration.h>
#include <hal/hal_sensor_magnetic_field.h>
#include <hal/hal_sensor_orientation.h>
#include <hal/hal_sensor_proximity.h>
#include <hal/hal_sensor_rotation.h>
#include <hal/hal_sensor_shake.h>

#endif /* _HAL_H_ */
