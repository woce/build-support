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

#ifndef JGEN_STREAM_H_
#define JGEN_STREAM_H_

#include <stdint.h>
#include <stdbool.h>
#include "jschema_types.h"
#include "japi.h"
#include "jgen_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opens a stream with no top-level object.  You have to make sure that you manually
 * start & end a top level object or array.  This is strictly if you need to split the setup of the stream
 * from beginning generation.
 *
 * NOTE: Not calling finish will result in a memory leak
 *
 * @param schema
 * @return
 *
 * @see jstreamObj
 * @see jstreamArr
 */
extern PJSON_API JStreamRef jstream(jschema_ref schema);

/**
 * Opens a stream containing a top-level object.  Calls to the members
 * of JStreamRef must come in pairs - a call to "string" for the key followed
 * by the value.  Unmatched pairs will cause an error to be generated when finish is called.
 * This also applies to any child objects.  Child objects must be opened & closed manually.
 *
 * NOTE: Not calling finish will result in a memory leak.
 *
 * @param schema
 * @return
 *
 * @see jstream
 * @see jstreamObj
 */
extern PJSON_API JStreamRef jstreamObj(jschema_ref schema);

/**
 * Opens a stream containing a top-level array.
 *
 * NOTE: Not calling finish will result in a memory leak
 *
 * @param schema
 * @return
 *
 * @see jstream
 * @see jstreamObj
 */
extern PJSON_API JStreamRef jstreamArr(jschema_ref schema);

#ifdef __cplusplus
}
#endif

#endif /* JGEN_STREAM_H_ */

