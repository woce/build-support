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

#ifndef JSCHEMA_TYPES_H_
#define JSCHEMA_TYPES_H_

#include "japi.h"
#include "jtypes.h"
#include "jdom_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct jschema* jschema_ref;

typedef enum {
	SCHEMA_RESOLVED = 0, /// the external ref resolved perfectly
	SCHEMA_NOT_FOUND = 1, /// the external ref is invalid
	SCHEMA_IO_ERROR = 2, /// there was some kind of error reading the schema resource
	SCHEMA_INVALID, /// the schema read wasn't a valid schema
	SCHEMA_GENERIC_ERROR = 256, /// some other unknown error occured
} JSchemaResolutionResult;

typedef struct JSchemaResolver* JSchemaResolverRef;

typedef enum {
	JSCHEMA_DOM_NOOPT = 0,
	/**
	 * Currently a no-op (probably will remain as such).  Inidicates that the lifetime of the input buffer outlives
	 * when the DOM object is freed completely.
	 * NOTE: This includes copies as well.
	 */
	JSCHEMA_INPUT_OUTLIVES_DOM = 1,
	/**
	 * Currently a no-op (probably will remain as such).  Indicates that the input buffer will not be modified.
	 */
	JSCHEMA_DOM_INPUT_NOCHANGE = 2,
} JSchemaOptimization;

// some or combination of JSchemaOptimization
typedef unsigned int JSchemaOptimizationFlags;

/**
 * @param resolver The contextual information for resolution to continue
 * @param resolved The a pointer to the reference to set the value of with the resolved schema.
 * @return SCHEMA_RESOLVED if the resolution succeeded, some other value otherwise.
 */
typedef JSchemaResolutionResult (*j_schema_resolver)(JSchemaResolverRef resolver, jschema_ref *resolvedSchema);

struct JSchemaResolver {
	j_schema_resolver m_resolve;
	void *m_userCtxt;	/// some arbitrary user data (e.g. pointer to the C++ class to use)
	jschema_ref m_ctxt;	/// supplied by the schema parser (no point in initializing)
	raw_buffer m_resourceToResolve; /// supplied by the schema parser (no point in initializing). NULL-terminated string
};

typedef struct JSchemaInfo {
	jschema_ref m_schema; /// The schema to use when parsing
	JErrorCallbacksRef m_errHandler; /// The error handlers when parsing fails
	JSchemaResolverRef m_resolver; /// The schema resolver to invoke when an external reference is encountered.
	// future compatability - 1 slots for extra data structure pointers/callbacks.  The 2nd slot is for some undefined
	// pointer to extend this structure further if it is ever needed.
	void *m_padding[2]; /// Padding for future binary compatibility
} JSchemaInfo, *JSchemaInfoRef;

#ifdef __cplusplus
}
#endif

#endif /* JSCHEMA_TYPES_H_ */
