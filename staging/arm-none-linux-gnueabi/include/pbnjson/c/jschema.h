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

#ifndef J_SCHEMA_H_
#define J_SCHEMA_H_

#include "japi.h"
#include "jcallbacks.h"
#include "jschema_types.h"
#include "jtypes.h"
#include "compiler/pure_attribute.h"
#include "compiler/nonnull_attribute.h"

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The default schema that accepts any well-formed JSON input.  All schemas should extend from this.
 *
 * NOTE: It is undefined what the URI of the default schema is.  It is up to the implementation to define that.
 */
PJSON_API jschema_ref jschema_all();

/**
 * Returns some kind of copy of the schema.  Since schemas are immutable in the sense of being independant of state
 * it is likely this is a reference-counted structure.
 *
 * Schemas may still be modified as external references are resolved dynamically as they are encountered during validation.
 * Thus, this does not necessarily return a copy safe to use across threads.
 *
 * @param schema The schema to retain ownership over.
 * @return A reference to the copy (may simply return schema or another object).  In other words, the implementation
 *         is free to use a reference-counted implementation or deep-copy semantics.  Typically, this will do reference
 *         counting.
 *
 * @see jschema_duplicate
 * @see jschema_resolve
 */
PJSON_API jschema_ref jschema_copy(jschema_ref schema) NON_NULL(1);

/**
 * Returns a deep copy of this schema.  This may or may not be the same under the hood as jschema_copy,
 * however only this method guarantees to provide thread-safe semantics.
 *
 * @param schema The schema to duplicate.
 * @return A complete duplicate of the entire schema.  Any modifications that occur to one will never be represented
 *         in that schema (including any sub objects)
 */
PJSON_API jschema_ref jschema_duplicate(jschema_ref schema) NON_NULL(1);

#if 0
/**
 * Resolves any and all external references.  This is an expensive operation and you should consider carefully
 * whether or not you need it.  After a successful call to this method, the schema is guaranteed to be
 * immutable & thus the same reference will be thread-safe.
 *
 * @NOTE: For now, this API is unexposed - please discuss with the maintainer about exposing.
 *
 * @param schema The schema to resolve.
 * @return True if the schema resolved fully, false if some error occured.
 *         If some error occurred, you will typically want to remember to free the reference before-hand.
 */
PJSON_API bool jschema_resolve(jschema_ref schema) NON_NULL(1);
#endif

/**
 * NOTE: you should only release those schema you parsed or are sure that you have gotten ownership over.
 *
 * @param schema The schema to free
 */
PJSON_API void jschema_release(jschema_ref *schema) NON_NULL(1);

/**
 * Returns the "DOM" structure of the schema that is ready for validation
 * by the parser layer.
 *
 * Javascript-style comments are allowed within schemas.
 *
 * @param input The input to use for the schema
 * @param inputOpt The optimization flags that can be used when generating the schema DOM
 * @param schemaInfo The information about how the schema that is being parsed is itself
 *                   validated
 * @return
 *
 * @see jschema_parse
 */
PJSON_API jschema_ref jschema_parse_ex(raw_buffer input, JSchemaOptimizationFlags inputOpt, JSchemaInfoRef schemaInfo) NON_NULL(3);


/**
 * Returns the "DOM" structure of the schema that is ready for validation
 * by the parser layer.
 *
 * Javascript-style comments are allowed within schemas.
 *
 * @param file - The file path to the schema to use for validation.
 * @param errorHandler - The error handlers to use when parsing the schema dom.
 * @return A reference to a schema that can be used, or NULL if there was an error.
 *
 * @see jschema_parse_ex
 */
PJSON_API jschema_ref jschema_parse_file(const char *file, JErrorCallbacksRef errorHandler);

/**
 * Returns the "DOM" structure of the schema that is ready for validation
 * by the parser layer.
 *
 * Convenience wrapper in case you don't want to validate the input against a schema
 * itself.
 *
 * Javascript-style comments are allowed within schemas.
 *
 * @param input - The input to generate a schema from - must be a valid JSON object schema.
 * @param inputOpt - The optimization flags to enable when parsing the schema
 * @param errorHandler - The error handlers to use when parsing the schema dom.
 * @return A reference to a schema that can be used, or NULL if there was an error.
 *
 * @see jschema_parse_ex
 */
PJSON_API jschema_ref jschema_parse(raw_buffer input, JSchemaOptimizationFlags inputOpt, JErrorCallbacksRef errorHandler);

/**
 * Initializes the schema information structure with the given data.
 *
 * It is recommended you always
 *
 * @param schemaInfo the structure to initialize with data
 * @param schema The schema to use for validation
 * @param resolver The resolver callback to handle external references within the schema
 * @param errHandler The error handler to
 */
PJSON_API void jschema_info_init(JSchemaInfoRef schemaInfo, jschema_ref schema, JSchemaResolverRef resolver, JErrorCallbacksRef errHandler);

#ifdef __cplusplus
}
#endif

#endif /* J_SCHEMA_H_ */
