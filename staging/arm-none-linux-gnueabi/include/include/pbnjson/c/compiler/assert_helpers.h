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

#ifndef ASSERT_HELPERS_H_
#define ASSERT_HELPERS_H_

#ifdef __GNUC__
#include "gcc/assert_helpers.h"
#endif

#if !defined(__ASSERT_VOID_CAST) || !defined(__ASSERT_FUNCTION)
	#if !defined(__ASSERT_VOID_CAST) && !defined(__ASSERT_FUNCTION)
		#define __ASSERT_VOID_CAST (void)
		#define __ASSERT_FUNCTION ((const char *)NULL)
	#else
		#error "Compiler implementation only implements this header partially"
	#endif
#endif

#endif /* ASSERT_HELPERS_H_ */

