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

#ifndef FORMAT_ATTRIBUTE_H_
#define FORMAT_ATTIRBUTE_H_

#if __GNUC__
#include "gcc/format_attribute.h"
#endif

#if !defined(FORMAT_ARG) || !defined(PRINTF_FORMAT_FUNC)

	#if !defined(FORMAT_ARG) && !defined(PRINTF_FORMAT_FUNC)
		#define FORMAT_ARG(index)
		#define PRINTF_FORMAT_FUNC(stringIndex, firstToCheck)
	#else
		#error "Bad compiler header"
	#endif

#endif

#endif /* FORMAT_ATTIBUTE_H_*/
