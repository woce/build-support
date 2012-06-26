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

#ifndef DETECTION_H_
#define DETECTION_H_

// major - any value
// minor - any value < 100
// patch - any value < 100
#define __PJ_APP_VERSION(major, minor, patch) (major * 1000000 + minor * 1000 + patch)

#define __PJ_REQUIRED_VERSION(major, minor, patch, actual_version) \
	(actual_version >= __PJ_APP_VERSION(major, minor, patch))

#define __PJ_REQUIRED_VERSION2(reqmajor, reqminor, reqpatch, major, minor, patch) \
	(__PJ_REQUIRED_VERSION(reqmajor, reqminor, reqpatch, __PJ_APP_VERSION(major, minor, patch)))

#ifdef __GNUC__
	#ifndef GCC_VERSION
		#define GCC_VERSION __PJ_APP_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
	#endif
	#define __PJ_COMPILER GCC
	#define __PJ_COMPILER_VERSION GCC_VERSION
	#define __PJ_MINIMUM_GCC_VERSION(major, minor, patch) \
		__PJ_REQUIRED_VERSION(major, minor, patch, __PJ_COMPILER_VERSION)
#else
	#warning "Unknown compiler being used"
#endif

#endif /* DETECTION_H_ */
