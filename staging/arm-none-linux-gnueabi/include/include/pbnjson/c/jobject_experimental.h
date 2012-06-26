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

/**
 * WARNING: EXPERIMENTAL API.  DO NOT USE THIS.  THIS IS ONLY FOR
 * THE C++ LIBRARY
 */
#ifndef JOBJECT_EXPERIMENTAL_H_
#define JOBJECT_EXPERIMENTAL_H_

#include "jtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the iterator representing the element after the last valid iterable
 * key/value pair in the object.
 */
jobject_iter jobj_iter_init_last(const jvalue_ref obj);
jobject_iter jobj_iter_previous (const jobject_iter i);

#ifdef __cplusplus
}
#endif

#endif /* JOBJECT_EXPERIMENTAL_H_ */
