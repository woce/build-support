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

#ifndef JGEN_TYPES_H_
#define JGEN_TYPES_H_

#include "japi.h"
#include "jtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __JStream* JStreamRef;	/// use this only

typedef enum {
	GEN_OK,
	GEN_KEYS_MUST_BE_STRINGS,
	GEN_INCOMPLETE_DOCUMENT,
	GEN_SCHEMA_VIOLATION,
	GEN_GENERIC_ERROR,
} StreamStatus;

typedef JStreamRef (*jObjectBegin)(JStreamRef stream);
typedef JStreamRef (*jObjectEnd)(JStreamRef stream);
typedef JStreamRef (*jArrayBegin)(JStreamRef stream);
typedef JStreamRef (*jArrayEnd)(JStreamRef stream);
typedef JStreamRef (*jNumber)(JStreamRef stream, raw_buffer num);
typedef JStreamRef (*jNumberI)(JStreamRef stream, int64_t num);
typedef JStreamRef (*jNumberF)(JStreamRef stream, double num);
typedef JStreamRef (*jString)(JStreamRef stream, raw_buffer str);
typedef JStreamRef (*jBoolean)(JStreamRef stream, bool value);
typedef JStreamRef (*jNull)(JStreamRef stream);
typedef char* (*jFinish)(JStreamRef stream, StreamStatus *errorCode);

// Efficient & clean object creation
struct __JStream {
	jObjectBegin o_begin;
	jObjectEnd o_end;
	jArrayBegin a_begin;
	jArrayEnd a_end;
	jNumber number;
	jNumberI integer;
	jNumberF floating;
	jString string;
	jBoolean boolean;
	jNull null_value;
	jFinish finish;
};  /// internal structure - do not use directly - use @JStreamRef instead

#ifdef __cplusplus
}
#endif

#endif /* JGEN_TYPES_H_ */
