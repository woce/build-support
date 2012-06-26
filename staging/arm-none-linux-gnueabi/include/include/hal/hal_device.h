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
 * @file hal_device.h
 *
 * @brief definition of HAL's public API for dealing with any
 * device.
 *
 *******************************************************************************
 */

#ifndef _HAL_DEVICE_H_
#define _HAL_DEVICE_H_

#include <hal/hal_macros.h>
#include <hal/hal_error.h>
#include <hal/hal_event.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_device_public HAL's generic (common) device interface.
* @ingroup hal_public
* @brief HAL's generic (commin) device interface.
* @{
*/

typedef enum {
    HAL_DEVICE_ILLEGAL_DEVICE = 0,
    HAL_DEVICE_FIRST_VALID,
    HAL_DEVICE_BLUETOOTH_INPUT_DETECT = HAL_DEVICE_FIRST_VALID,
    HAL_DEVICE_CUSTOM,
    HAL_DEVICE_GENERIC,
    HAL_DEVICE_HAPTICS,
    HAL_DEVICE_KEYS,
    HAL_DEVICE_LED,
    HAL_DEVICE_LED_CONTROLLER,
    HAL_DEVICE_SENSOR_FIRST,          /* all psc sensors */
    HAL_DEVICE_SENSOR_ACCELERATION = HAL_DEVICE_SENSOR_FIRST,
    HAL_DEVICE_SENSOR_ALS,
    HAL_DEVICE_SENSOR_ANGULAR_VELOCITY,
    HAL_DEVICE_SENSOR_BEARING,
    HAL_DEVICE_SENSOR_GRAVITY,
    HAL_DEVICE_SENSOR_LINEAR_ACCELERATION,
    HAL_DEVICE_SENSOR_MAGNETIC_FIELD,
    HAL_DEVICE_SENSOR_ORIENTATION,
    HAL_DEVICE_SENSOR_PROXIMITY,
    HAL_DEVICE_SENSOR_ROTATION,
    HAL_DEVICE_SENSOR_SHAKE,
    HAL_DEVICE_SENSOR_LAST = HAL_DEVICE_SENSOR_SHAKE,
    HAL_DEVICE_TOUCHPANEL,
    HAL_DEVICE_TYPE_COUNT, /* should always be the last, used primarly in testing
                             for iterating over all known devices */
} hal_device_type_t;

typedef enum {
	HAL_FILTER_DEFAULT = 0, 				/**< include default set of devices */
	HAL_FILTER_INCLUDE_MOCK_DEVICES = 0x1, 	/**< include the mock devices in the iterator */
	HAL_FILTER_ALL = 0xffff,
} hal_device_filter_t;

typedef enum {
	HAL_OPERATING_MODE_UNKNOWN = -1,
	HAL_OPERATING_MODE_OFF = 0,
	HAL_OPERATING_MODE_ON,
} hal_operating_mode_t;

struct hal_device;
typedef struct hal_device* hal_device_handle_t;
typedef const char* hal_device_id_t;

struct hal_device_iterator;
typedef struct hal_device_iterator* hal_device_iterator_handle_t;

typedef enum {
	HAL_CALLBACK_STATUS_UNDEFINED = 0,
	HAL_CALLBACK_STATUS_DONE,
	HAL_CALLBACK_STATUS_ASYNC,
	HAL_CALLBACK_STATUS_HARDWARE_ASYNC,
	HAL_CALLBACK_STATUS_FAILED,
	HAL_CALLBACK_STATUS_CANCELLED,
	HAL_CALLBACK_STATUS_PREMPTIED,
} callback_status_t;

typedef void (*hal_device_callback)(hal_device_handle_t, callback_status_t, void*);

/**
 * hal_report_rate_t
 * @brief Defines all valid poll rates for sensors.
 *
 * Each sensor module that polls for events defines a corresponding rate (in samples per second)
 * for each of these values.
 */
typedef enum {
    HAL_REPORT_RATE_UNKNOWN = -1,   /**< Report rate is unknown */
    HAL_REPORT_RATE_DEFAULT = 0,    /**< Default reporting rate for sensor when user has not requested specific rate */
    HAL_REPORT_RATE_LOW,            /**< Slow rate of reporting sensor events */
    HAL_REPORT_RATE_MEDIUM,         /**< Medium rate of reporting sensor events */
    HAL_REPORT_RATE_HIGH,           /**< Fast rate of reporting sensor events */
    HAL_REPORT_RATE_HIGHEST,        /**< Fastest rate of reporting sensor events */
    HAL_REPORT_RATE_COUNT,		/* Must always be last */
} hal_report_rate_t;


/**
 * Create a new device iterator.
 *
 * @param[in] 	type - device type
 * @param[in] 	filter - flags defining what kind of devices to return.
 * @param[out]  iterator_out_ptr - pointer to store handle to the iterator. Will be NULL
 * 				if no matching devices are found. If not NULL it has to be released
 * 				with the call to hal_release_device_iterator.
 *
 * @return hal_error_t that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_get_device_iterator(hal_device_type_t type, hal_device_filter_t filter, hal_device_iterator_handle_t *iterator_out_ptr);

/**
 * Obtain an Id for the next device.
 *
 * @param[in] 	iterator - iterator from which to obtain the next device.
 * @param[out]  id_out_ptr - pointer to store device id. It has to be
 * 				released with the call to hal_release_device_id.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_iterator_get_next_id(hal_device_iterator_handle_t iterator, hal_device_id_t *id_out_ptr);

/**
 * Release memory associated with the hal_device_iterator_handle_t generated by the call to
 * hal_get_device_iterator.
 *
 * @param[in] 	iterator - iterator to be released.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_release_device_iterator(hal_device_iterator_handle_t iterator);

/**
 * Create a new device of a known type and and id.
 *
 * @param[in] 	type - device type
 * @param[in] 	id - device id
 * @param[out]	handle_ptr - pointer to a handle to store handle for the
 *              newly created device.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_open(hal_device_type_t type, hal_device_id_t id, hal_device_handle_t* handle_ptr);

/**
 * Close the device associated with the handle and release all of its resources.
 * After this call assume the handle is no longer valid.
 *
 * @param[in]	handle - handle to the device to be destroyed.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_close(hal_device_handle_t handle);

/**
 * Set the operating mode of the device.
 *
 * @param[in]	handle - handle to the device.
 * @param[in]	mode - operating mode to set.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_set_operating_mode(hal_device_handle_t handle, hal_operating_mode_t mode);

/**
 * Get the operating mode of the device.
 *
 * @param[in]	handle - handle to the device.
 * @param[out]	mode_out_ptr - pointer to store current operating mode  of the device.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_get_operating_mode(hal_device_handle_t handle, hal_operating_mode_t* mode_out_ptr);

/**
 * Get the file descriptor for the event source.
 *
 * @param[in]	handle - handle to the device.
 * @param[out]	source_out_ptr - pointer to store file descriptor for the event source.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_get_event_source(hal_device_handle_t handle, int* source_out_ptr);

/**
 * Get the current event for the device.
 *
 * @param[in]	handle - handle to the device.
 * @param[out]	event_out_ptr - pointer to store the event handle.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_get_event(hal_device_handle_t handle, hal_event_handle_t* event_out_ptr);

/**
 * Release the event.
 *
 * @param[in]	handle - handle to the device.
 * @param[int]	event_handle - handle to the event.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_release_event(hal_device_handle_t handle, hal_event_handle_t event_handle);

/**
 * Set the reporting rate of the device.
 *
 * @param[in] 	handle - The device handle.
 * @param[in] 	rate - report rate from a predefined set of rates for a sensor.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_set_report_rate(hal_device_handle_t handle, hal_report_rate_t rate);

/**
 * Get the reporting rate of the device.
 *
 * @param[in] 	handle - The device handle.
 * @param[out] 	rate_out_ptr - pointer to store current rate (as defined in #hal_report_rate_t) of a sensor.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_device_get_report_rate(hal_device_handle_t handle, hal_report_rate_t *rate_out_ptr);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* _HAL_DEVICE_H_ */
