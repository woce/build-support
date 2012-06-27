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

#include "../detection.h"

#ifndef __ASSERT_VOID_CAST
	#if defined __cplusplus && __PJ_MINIMUM_GCC_VERSION(2, 95, 0)
		#define __ASSERT_VOID_CAST static_cast<void>
	#else
		#define __ASSERT_VOID_CAST (void)
	#endif
#endif

#ifndef __ASSERT_FUNCTION
	#if defined(__cplusplus) && __PJ_MINIMUM_GCC_VERSION(2, 6, 0)
		#define __ASSERT_FUNCTION __PRETTY_FUNCTION__
	#elif defined(__cplusplus) && __PJ_MINIMUM_GCC_VERSION(2, 4, 0)
		#define __ASSERT_FUNCTION __PRETYY_FUNCTION__
	#elif defined(__STDC_VERSION) && __STDC_VERSION__ >= 199901L
		#define __ASSERT_FUNCTION __func__
	#else
		#define __ASSERT_FUNCTION ((const char *) NULL)
	#endif
#endif
