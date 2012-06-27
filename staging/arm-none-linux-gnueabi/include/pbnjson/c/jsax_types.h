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

/*
 * jparse_types.h
 *
 *  Created on: Sep 24, 2009
 */

#ifndef JSAX_TYPES_H_
#define JSAX_TYPES_H_

#include "jcallbacks.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*jsax_null)(JSAXContextRef ctxt);
typedef int (*jsax_boolean)(JSAXContextRef ctxt, bool value);
typedef int (*jsax_number)(JSAXContextRef ctxt, const char *number, size_t numberLen);
typedef int (*jsax_string)(JSAXContextRef ctxt, const char *string, size_t stringLen);
typedef int (*jsax_object_start)(JSAXContextRef ctxt);
typedef int (*jsax_object_key)(JSAXContextRef ctxt, const char *key, size_t keyLen);
typedef int (*jsax_object_end)(JSAXContextRef ctxt);
typedef int (*jsax_array_start)(JSAXContextRef ctxt);
typedef int (*jsax_array_end)(JSAXContextRef ctxt);

/**
 * If any function pointers are NULL in this structure, then they will not be invoked.
 * Note that m_errorHandler is an actual structure, not a pointer, so it's internal pointers
 * must be properly initialized.
 */
typedef struct {
	jsax_object_start m_objStart;
	jsax_object_key m_objKey;
	jsax_object_end m_objEnd;

	jsax_array_start m_arrStart;
	jsax_array_end m_arrEnd;

	jsax_string m_string;
	jsax_number m_number;
	jsax_boolean m_boolean;
	jsax_null m_null;
} PJSAXCallbacks;

#ifdef __cplusplus
}
#endif

#endif /* JSAX_TYPES_H_ */
