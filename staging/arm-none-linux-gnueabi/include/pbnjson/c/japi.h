/* @@@LICENSE
*
*      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
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
LICENSE@@@ */

#ifndef J_API_H_
#define J_API_H_

#define API_EXPORT __attribute__((visibility("default")))
#define API_IMPORT __attribute__((visibility("default")))
#define API_LOCAL __attribute__((visibility("hidden")))
#define API_INTERNAL __attribute__((visibility("internal")))

#ifdef PJSON_SHARED
	#ifdef PJSON_EXPORT
		#define PJSON_API API_EXPORT
		#define PJSON_LOCAL API_LOCAL
		#define PJSON_PRIVATE API_INTERNAL
	#else
		#define PJSON_API API_IMPORT
		#define PJSON_LOCAL
		#define PJSON_PRIVATE
	#endif
#else
	#define PJSON_API
	#define PJSON_LOCAL
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set the name of the component utilizing this library.  This should be as descriptive as possible
 * to help narrow down bugs.  If this is never called, then the string "UNIDENTIFIED CONSUMER (pid)!!!!!" is used instead.
 * String must have program lifetime (or if it is no longer available, old value = getConsumerName, setConsumerName(null), free old value).
 *
 * @param name The name of the component using this API (per-process)
 */
PJSON_API void setConsumerName(const char *name);

/**
 * Gets the name set (this will not return the default, /proc/ based string)
 *
 * @return The name passed to setConsumerName previously or NULL if it was never called.
 */
PJSON_API const char *getConsumerName();

#ifdef __cplusplus
}
#endif

#endif /* J_API_H_ */
