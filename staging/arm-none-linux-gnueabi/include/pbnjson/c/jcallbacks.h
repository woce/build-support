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

#ifndef J_CALLBACKS_H_
#define J_CALLBACKS_H_

#include "japi.h"

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct PJSON_LOCAL  __JSAXContext; /// internal structure maintaining context about the parser
typedef struct __JSAXContext* JSAXContextRef;	/// opaque reference to the parser context

/*
 * With these callbacks, you typically want to return false.  Return true if and only if you
 * were positively able to fix up the input to not contain the error.
 */
typedef bool (*jerror_parsing)(void *ctxt, JSAXContextRef parseCtxt);
typedef bool (*jerror_schema)(void *ctxt, JSAXContextRef parseCtxt);
typedef bool (*jerror_misc)(void *ctxt, JSAXContextRef parseCtxt);

typedef struct JErrorCallbacks {
    jerror_parsing m_parser; /// there was an error parsing the input
    jerror_schema m_schema; /// there was an error validating the input against the schema
    jerror_misc m_unknown; /// some other error occured while parsing
    void *m_ctxt;	/// user-specified context to use
} *JErrorCallbacksRef;

#ifdef __cplusplus
}
#endif

#endif /* J_CALLBACKS_H_ */
