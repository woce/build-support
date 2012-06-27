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
 * @file hal_custom.h
 *
 * @brief definition of HAL's public API for  controlling and
 * accessing custom device.
 *
 *******************************************************************************
 */

#ifndef _HAL_CUSTOM_H_
#define _HAL_CUSTOM_H_

#include <hal/hal_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Set the property of the custom device.
 *
 * @param[in] 	handle - The device handle.
 * @param[in] 	property_in_ptr - pointer pointing to the property to store.
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_custom_set_property(hal_device_handle_t handle, void* property_in_ptr);

/*
 * Get the property of the custom device.
 *
 * @param[in] 	handle - The device handle.
 * @param[out] 	property_out_ptr - pointer pointing to where to store the pointer to property..
 *
 * @return error that will be HAL_ERROR_SUCCESS if operation is
 * successful or an actual error if operation did not succeed.
 *
 */
API_EXPORT hal_error_t hal_custom_get_property(hal_device_handle_t handle, void** poperty_out_ptr);

#ifdef __cplusplus
}
#endif

#endif /* _HAL_CUSTOM_H_ */
