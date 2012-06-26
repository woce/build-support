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
 * JDomParser.h
 *
 *  Created on: Sep 28, 2009
 */

#ifndef JDOMPARSER_H_
#define JDOMPARSER_H_

#include "JParser.h"
#include "JValue.h"
#include "../c/jparse_types.h"

namespace pbnjson {

class JResolver;

/**
 * For consistency purposes, I'm borrowing the XML terminology.  The DOM represents JSON
 * values stored as a tree in memory.  SAX represents JSON parsing that doesn't actually create any intermediary
 * representation but instead tokenizes into JSON primitives that the caller is responsible for handling.
 *
 * @see JParser
 */
class PJSONCXX_API JDomParser : public JParser
{
public:
	/**
 	 * Initialize a JSON parser that will generate a DOM.
 	 *
 	 * @param resolver The object to use when resolving external references within a schema.
 	 *
 	 * @see JResolver
 	 */
	JDomParser(JResolver *resolver = NULL);
	virtual ~JDomParser();

	/**
	 * By default, we initialize to a conservative optimization level.
	 * Here, if you know additional information about the stream you will be parsing, you can change it.
	 *
	 * @param optLevel The optimization level to use.
	 *
	 * @see JDOMOptimization
	 */
	void changeOptimization(JDOMOptimization optLevel) { m_optimization = optLevel; }

	/**
	 * Parse the input using the given schema.
	 *
	 * @param input The JSON string to parse.  Must be a JSON object or an array.  Behaviour is undefined
	 *              if it isn't.  This is part of the JSON spec.
	 * @param schema The JSON schema to use when parsing.
	 * @param errors The error handler to use if you want more detailed information if parsing failed.
	 * @return True if we got validly formed JSON input that was accepted by the schema, false otherwise.
	 *
	 * @see JSchema
	 * @see JSchemaFile
	 * @see JErrorHandler
	 */
	bool parse(const std::string& input, const JSchema& schema, JErrorHandler *errors = NULL);

	/**
	 * Parse the input file using the given schema.
	 * @param file The JSON string to parse.  Must be a JSON object or an array.  Behaviour is undefined
	 *             if it isn't.  This is part of the JSON spec.
	 * @param schema The JSON schema to use when parsing
	 * @param optimization The optimization level to use for parsing the file.  The JDOMOptimization is
	 *                     not used - it is implicitely set to the most optimal level since the backing buffer
	 *                     will be owned by pbnjson.
	 * @param errors The error handler to use if you want more detailed information if parsing failed.
	 * @return True if we got a validly formed JSON input that was accepted by the schema, false otherwise.
	 *
	 * @see JSchema
	 * @see JSchemaFile
	 * @see JErrorHandler
	 */
	bool parseFile(const std::string& file, const JSchema& schema, ::JFileOptimizationFlags optimization = JFileOptNoOpt, JErrorHandler *errors = NULL);

	/**
	 * Retrieve the "DOM" representation of the input that was last parsed by this object.
	 *
	 * @return A JValue representation of the input.
	 * @see JValue
	 */
	JValue getDom();

protected:
	JParser::NumberType conversionToUse() const { return JParser::JNUM_CONV_RAW; }

private:
	JSchemaInfo prepare(const JSchema& schema, const JSchemaResolver& resolver, const JErrorCallbacks& cErrCbs, JErrorHandler *errors);
	inline JSchemaResolver prepareResolver() const;
	inline JErrorCallbacks prepareCErrorCallbacks() const;

	bool jsonPrimitive(const JValue& created);

	JSchemaResolutionResult resolve(void *resolver, jschema_ref *resolvedSchema);

	JValue m_dom;
	JDOMOptimization m_optimization;
	JResolver *m_resolver;

	friend JSchemaResolutionResult dom_bounce_resolver(JSchemaResolverRef, jschema_ref *);
};

}

#endif /* JDOMPARSER_H_ */
