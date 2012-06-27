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

#ifndef J_CXX_API_H_
#define J_CXX_API_H_

#define API_EXPORT __attribute__((visibility("default")))
#define API_IMPORT __attribute__((visibility("default")))
#define API_LOCAL __attribute__((visibility("hidden")))

#ifdef PJSONCXX_SHARED
	#ifdef PJSONCXX_EXPORT
		#define PJSONCXX_API API_EXPORT
		#define PJSONCXX_LOCAL API_LOCAL
	#else
		#define PJSONCXX_API API_IMPORT
		#define PJSONCXX_LOCAL
	#endif
#else
	#define PJSONCXX_API
	#define PJSONCXX_LOCAL
#endif

namespace pbnjson {

/**
 * Set the name of the component utilizing this library.  This should be as descriptive as possible
 * to help narrow down bugs.  If this is never called, then the string "UNIDENTIFIED CONSUMER (pid)!!!!!" is used instead.
 * String must have program lifetime (or if it is no longer available, getConsumerName, setConsumerName(null), free old value).
 *
 * @param name The name of the component using this API (per-process)
 */
PJSONCXX_API void setConsumerName(const char *name);

/**
 * Gets the name set (this will not return the default, /proc/ based string)
 *
 * @return The name passed to setConsumerName previously or NULL if it was never called.
 */
PJSONCXX_API const char *getConsumerName();

}

#endif /* J_CXX_API_H_ */
