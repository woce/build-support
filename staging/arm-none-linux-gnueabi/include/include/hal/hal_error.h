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
 * @file hal_error.h
 *
 * @brief definition of HAL's errors .
 *
 *******************************************************************************
 */

#ifndef _HAL_ERROR_H_
#define _HAL_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup hal_error_public HAL's public error interface and definition.
* @ingroup hal_public
* @brief HAL's public error interface and definition.
* @{
*/


/*
 * HAL error codes
 */
typedef enum hal_error_enum {
	HAL_ERROR_SUCCESS,					/**< Operation successful */
	HAL_ERROR_INVALID_HANDLE,			/**< Incorrect handle passes to API function */
	HAL_ERROR_WRONG_DEVICE_TYPE,		/**< Device used for this operation has the wrong type */
	HAL_ERROR_DEVICE_NOT_EXIST,			/**< Device does not exist */
	HAL_ERROR_TOO_MANY_OPENS,			/**< Reached maximum opens allowed on device */
	HAL_ERROR_OUT_OF_MEMORY,			/**< Out of memory */
	HAL_ERROR_DEVICE_UNAVAILABLE,		/**< Device not present OR Connection to device not available */
	HAL_ERROR_UNSUPPORTED_DEVICE_TYPE,	/**< No support for this device type currently */
	HAL_ERROR_INVALID_VALUE,            /**< Value passed in is not valid */
	HAL_ERROR_NOT_IMPLEMENTED,			/**< The method/function has not been implemented by module */
	HAL_ERROR_INVALID_EVENT_TYPE,       /**< Event is of a wrong type for this operation */
	HAL_ERROR_INVALID_OPERATION,        /**< This operation cannot be performed at this time */
    HAL_ERROR_GENERIC,					/**< Generic HAL_LOG_ERROR */
} hal_error_t;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _HAL_ERROR_H_ */
