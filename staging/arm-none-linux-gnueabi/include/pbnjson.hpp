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

#ifndef PJSONCXX_H_
#define PJSONCXX_H_

/*!
 @mainpage PBNJSON C++
 @section PBNJSONCPP_INTRO C++ API Introduction
 
 This API allows easier C++ abstraction over the core PBNJSON library written in C.
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
    - First class C++ bindings.  C++ bindings are maintained as part of this library and are treated
      as important as the core C library.
 
 @subsection PBNJSONCPP_GEN_OVERVIEW Generating JSON & serializing to a string
 This is an example of how to create a JSON value and then convert it to a string.

 @subsubsection PBNJSON_CPP_GEN_OVERVIEW_SCHEMA The schema used in the code snippet below
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

 @subsubsection PBNJSON_CPP_GEN_OVERVIEW_SNIPPET The code snippet as promised
@code
#include <pbnjson.hpp>
#include <string>
#include <iostream>

// ....

{
	pbnjson::JValue myresponse = pbnjson::Object();
	myresponse.put("errorCode", 5);	// {"errorCode":5}
	myresponse.put("errorText", "This is an example of a pbnjson object");	// {"errorCode":5,"errorText":"This is an example of a pbnjson object"}

	pbnjson::JGenerator serializer(NULL);	// our schema that we will be using does not have any external references
	std::string serialized;
	pbnjson::JSchemaFile responseSchema("response.schema");
	if (!serializer.toString(myresponse, responseSchema, serialized)) {
		// handle error (e.g. generated json would fail to validate & or some other error occured)
		return;
	}

	std::cout << serialized << std::endl;	// write out {"errorCode":5,"errorText"...} to stdout
}
@endcode

 
 @section PBNJSONCPP_OVERVIEW C++ API Overview
 @subsection PBNJSONCPP_PARSE_OVERVIEW Parsing JSON serialized within a string
 This is an example of how to take a JSON value serialized into a string, parse it into an in-memory format,
 and interact with it.

 @subsubsection PBNJSONCPP_PARSE_OVERVIEW_SCHEMA The schema used in the code snippet below
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
 @subsubsection PBNJSONCPP_PARSE_OVERVIEW_SNIPPET The code snippet as promised:
@code
#include <pbnjson.hpp>
#include <string>
#include <iostream>

//...

{
	// since the schema doesn't specify additionalProperties, all other
	// properties are accepted by default
	std::string input = "{\"guess\" : 5.3, \"cheat\" : true}";

	pbnjson::JSchemaFile inputSchema("input.schema");

	pbnjson::JDomParser parser(NULL);	// our schema that we will be using does not have any external references

	// in this example, I don't care about the actual errors that cause parsing to fail.
	if (!parser.parse(input, inputSchema, NULL)) {		
		// handle error
		return;
	}

	pbnjson::JValue parsed = parser.getDom();

	std::cout << parsed["guess"].asNumber<double>() << std::endl; // this is always guaranteed to print a number between 1 & 10.  no additional validation necessary within the code.
	std::cout << parsed["cheat"].asBool() << std::endl; // this will print the value of cheat (if cheat isn't present or isn't a boolean, this will print false)
}

@endcode

@subsubsection PBNJSONCPP_PARSE_OVERVIEW_SNIPPET2 Once more with a default schema:
@code
#include <pbnjson.hpp>
#include <string>
#include <iostream>

//...

{
	// since the schema doesn't specify additionalProperties, all other
	// properties are accepted by default
	std::string input = "{\"guess\" : 5.3, \"cheat\" : true}";

	pbnjson::JSchemaFragment inputSchema("{}");

	pbnjson::JDomParser parser(NULL);	// our schema that we will be using does not have any external references

	// in this example, I don't care about the actual errors that cause parsing to fail.
	if (!parser.parse(input, inputSchema, NULL)) {		
		// handle error
		return;
	}

	pbnjson::JValue parsed = parser.getDom();

	std::cout << parsed["guess"].asNumber<double>() << std::endl; // this is always guaranteed to print a number between 1 & 10.  no additional validation necessary within the code.
	std::cout << parsed["cheat"].asBool() << std::endl; // this will print the value of cheat (if cheat isn't present or isn't a boolean, this will print false)
}

@endcode
 */

#include "pbnjson/cxx/japi.h"
#include "pbnjson/cxx/JValue.h"
#include "pbnjson/cxx/JGenerator.h"
#include "pbnjson/cxx/JSchema.h"
#include "pbnjson/cxx/JDomParser.h"
#include "pbnjson/cxx/JSchemaFile.h"
#include "pbnjson/cxx/JSchemaFragment.h"
#include "pbnjson/cxx/JResolver.h"

#endif /* PJSONCXX_H_ */
