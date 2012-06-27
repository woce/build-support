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

#ifndef JOBJECT_TYPES_H_
#define JOBJECT_TYPES_H_

#include <stddef.h>
#include "japi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct jvalue* jvalue_ref;

typedef struct {
	void *m_opaque;
} jobject_iter;

typedef struct {

} *jarray_opts;

typedef enum {
	SPLICE_NOCHANGE,	/// the splice doesn't have any affect on the ownership of the elements
	SPLICE_TRANSFER, /// the ownership of the spliced elements gets transferred to the new array (the old array loses ownership)
	SPLICE_COPY, /// the new array retains a copy of the individual elements from the first array
} JSpliceOwnership;

/**
 * A structure to represent strings that have length instead of being NULL-terminated.
 * This means it's friendly with Unicode encodings other than UTF-8 but more importantly allows
 * for some no-copy optimizations.
 */
typedef struct {
	const char *m_str;
	long m_len;	/// this MUST be the number of characters in m_str not including any terminating nulls.
} raw_buffer;

/**
 * A structure representing a key/value pair in a JSON object.
 */
typedef struct {
    jvalue_ref key;
    jvalue_ref value;
} jobject_key_value;

typedef void (*jdeallocator)(void *buffer);

#ifdef __cplusplus
}
#endif

#endif /* JOBJECT_TYPES_H_ */
