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

#ifndef UNUSED_ATTRIBUTE_H_
#define UNUSED_ATTRIBUTE_H_

#if __GNUC__
#include "gcc/unused_attribute.h"
#endif

#if !defined(UNUSED_FUNC) || !defined(UNUSED_VAR) || !defined(WARN_UNUSED_RESULT)

	#if !defined(UNUSED_FUNC) && !defined(UNUSED_VAR) && !defined(WARN_UNUSED_RESULT)
		#define UNUSED_FUNC
		#define UNUSED_VAR
		#define WARN_UNUSED_RESULT
	#else
		#error "Bad compiler header"
	#endif

#endif

#endif /* UNUSED_ATTRIBUTE_H_ */
