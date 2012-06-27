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

#ifndef MALLOC_ATTRIBUTE_H_
#define MALLOC_ATTRIBUTE_H_

#if __GNUC__
#include "gcc/malloc_attribute.h"
#endif

#if !defined(MALLOC_FUNC) || !defined(RETURN_SIZE) || !defined(RETURN_SIZE2)

	#if !defined(MALLOC_FUNC) && !defined(RETURN_SIZE) && !defined(RETURN_SIZE2)
		#define MALLOC_FUNC
		/**
		 * argument arg of the function indicates the size in bytes of the
		 * pointer returned from the function.
		 */
		#define RETURN_SIZE(arg)
		/**
		 * argument arg1 multiplied by argument arg2 of the function indicate the size in bytes of the
		 * pointer returned from the function.
		 */
		#define RETURN_SIZE2(arg1, arg2)
	#else
		#error "Bad compiler header"
	#endif

#endif

#endif /* MALLOC_ATTRIBUTE_H_ */
