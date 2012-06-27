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

#ifndef PJSONC_H_
#define PJSONC_H_

/*!
 @mainpage PBNJSON C
 @section PBNJSONC_INTRO C API Introduction
 
 This API allows easier C abstraction over the core PBNJSON library written in C.
 The advantages of this API over the other APIs we have used in the past:
    - Numbers are parsed correctly regardless of how they are sent along the wire (supports generic number format as defined by JSON spec).
    - Much faster
       - Uses a faster (& correct) parser
       - Much fewer DOM nodes created
       - Number parsing is delayed until a conversion request is made.
    - First implementation of schemas in C (more of the spec implemented than any other implementation posted on the internet).
       - Schemas are integral to using pbnsjon.
       - Schemas define what input is accepted/reject when parsing
           - No more unnecessary checks of valid parameter passing; simply write the schema
       - Schemas can be created from files & use mmap for minimal memory overhead & optimal behaviour (no swapping necessary)
    - First class C++ bindings.  C++ bindings are maintained as part of this library and treated equivalently in terms of priority.
 
 @subsection PBNJSONC_GEN_OVERVIEW Generating JSON & serializing to a string
 This is an example of how to create a JSON value and then convert it to a string.

 @subsubsection PBNJSON_C_GEN_OVERVIEW_SCHEMA The schema used in the code snippet below

@code
{
	"type" : "object", // the top-level response is a JSON object
	"properties" : { // the keys allowed by an object
		"errorCode" : { "type" : "integer" }, // errorCode is a non-floating point number
		"errorText" : { "type" : "string" } // errorText is a string value
	},
	"additionalProperties" : false // don't allow any other properties to appear in this object
}
@endcode

 @subsubsection PBNJSON_CPP_GEN_OVERVIEW_SNIPPET The code snippet as promised:
@code
#include <pbnjson.h>
#include <stdio.h>

// ....

{
	jvalue_ref myresponse = jobject_create_var(
		{J_CSTR_TO_JVAL("errorCode"), jnumber_create_i32(5)},
		{J_CSTR_TO_JVAL("errorText"), jstring_create("This is an example of a pbnjson object")},
		J_END_OBJ_DECL
	);

	jschema_ref responseSchema = jschema_parse_file("response.schema", NULL);
	const char *serialized = jvalue_tostring(myresponse, responseSchema); // asStr lives as long as responseSchema
	if (serialized == NULL) {
		// some problem occured during generation
		j_release(&my_response); // remember to not leak memory
		return;
	}
	
	fprintf(stdout, "%s", serialized);
	j_release(&my_response);
}
@endcode

 @section PBNJSONC_OVERVIEW C API Overview
 @subsection PBNJSONC_PARSE_OVERVIEW Parsing JSON serialized within a string
 This is an example of how to take a JSON value serialized into a string, parse it into an in-memory format,
 and interact with it.

 @subsubsection PBNJSONC_PARSE_OVERVIEW_SCHEMA The schema used in the code snippet below

@code
{
	"type" : "object",
	"properties" : {
		"guess" : {
			"type" : "number",
			"minimum" : 1,
			"maximum" : 10
		}
	}
}
@endcode
 @subsubsection PBNJSONC_PARSE_OVERVIEW_SNIPPET The code snippet as promised:
@code
#include <pbnjson.h>
#include <stdio.h>

// ...

{
	char *input;
	// ...	// input is initialized

	jschema_ref inputSchema = jschema_parse_file("input.schema", NULL);
	JSchemaInfo schemaInfo;
	jschema_info_init(&schemaInfo, inputSchema, NULL, NULL); // no external refs & no error handlers
	jvalue_ref parsed = jdom_parse(j_cstr_to_buffer(input), DOMOPT_NOOPT, &schemaInfo);
	jschema_release(&inputSchema);

	if (jis_null(parsed)) {
		// input failed to parse (this is OK since we only allow parsing of top level elements (an object or array)
		j_release(&parsed);
		return;
	}

	// this is always guaranteed to print a number between 1 & 10.  no additional validation necessary within the code.
	int guess = jnumber_get_i32(jobject_get(parsed, J_CSTR_TO_JVAL("guess")));

	fprintf(stdout, "The guess was %d\n", guess);

	j_release(&parsed);
@endcode

 @subsubsection PBNJSONC_PARSE_OVERVIEW_SNIPPET1 The code snippet with a default schema that accepts all input:
@code
#include <pbnjson.h>
#include <stdio.h>

// ...

{
	char *input;
	// ...	// input is initialized

	JSchemaInfo schemaInfo;
	jschema_info_init(&schemaInfo, jschema_all(), NULL, NULL); // no external refs & no error handlers
	jvalue_ref parsed = jdom_parse(j_cstr_to_buffer(input), DOMOPT_NOOPT, &schemaInfo);

	if (jis_null(parsed)) {
		// input failed to parse (this is OK since we only allow parsing of top level elements (an object or array)
		j_release(&parsed);
		return;
	}

	// this is always guaranteed to print a number between 1 & 10.  no additional validation necessary within the code.
	int guess = jnumber_get_i32(jobject_get(parsed, J_CSTR_TO_JVAL("guess")));

	fprintf(stdout, "The guess was %d\n", guess);

	j_release(&parsed);
@endcode

 */
#ifdef __cplusplus
extern "C" {
#endif

#include "pbnjson/c/japi.h"
#include "pbnjson/c/jobject.h"
#include "pbnjson/c/jschema.h"
#include "pbnjson/c/jgen_stream.h"
#include "pbnjson/c/jparse_stream.h"

#ifdef __cplusplus
}
#endif

#endif /* PJSONC_H_ */
