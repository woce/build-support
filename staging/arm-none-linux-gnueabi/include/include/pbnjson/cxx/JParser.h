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

#ifndef JPARSER_H
#define JPARSER_H

#include "japi.h"

#include <stack>
#include <string>

#include "JSchema.h"

#include "../c/jconversion.h"

namespace pbnjson {

class JErrorHandler;
class JSchema;
class JResolver;

extern "C" JSchemaResolutionResult sax_schema_resolver(JSchemaResolverRef resolver, jschema_ref *resolvedSchema);

/**
 * For consistency purposes, I'm borrowing the XML terminology.  The DOM represents JSON
 * values stored as a tree in memory.  SAX represents JSON parsing that doesn't actually create any intermediary
 * representation but instead tokenizes into JSON primitives that the caller is responsible for handling.
 *
 * @see JDomParser
 */
class PJSONCXX_API JParser
{
public:
	enum NumberType {
		JNUM_CONV_RAW,
		JNUM_CONV_NATIVE,
	};

	struct ParserPosition {
		int m_line;
		int m_column;
	};

	JParser(JResolver *schemaResolver);
	JParser(const JParser& other);
	virtual ~JParser();

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
	virtual bool parse(const std::string& input, const JSchema &schema, JErrorHandler *errors = NULL);

	JErrorHandler* getErrorHandler() const;
	ParserPosition getPosition() const;

protected:
	class DocumentState {
	public:
		virtual ~DocumentState();
		DocumentState(const DocumentState& other);

	protected:
		DocumentState();
	};

	bool haveKeys() const { return m_keyStack.empty(); }
	void pushKey(const std::string& key) { m_keyStack.push(key); }
	const std::string& peekKey() const { return m_keyStack.top(); }
	std::string popKey() { std::string top = peekKey(); m_keyStack.pop(); return top; }

	bool haveState() const { return m_stateStack.empty(); }
	void pushState(const DocumentState& state) { m_stateStack.push(state); }
	const DocumentState& peekState() const { return m_stateStack.top(); }
	DocumentState popState() { DocumentState top = peekState(); m_stateStack.pop(); return top; }

	/*
	 * By default, this parser will not parse any input.  You must override
	 * all the functions that might be called if you want.  Schema validation occurs
	 * just before these virtual functions are called.
	 */

	/**
	 * Called when a valid { is encountered.
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonObjectOpen() { return false; }
	/**
	 * Called when a valid property instance name is encountered
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonObjectKey(const std::string& key) { return false; }
	/**
	 * Called when a valid } is encountered
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonObjectClose() { return false; }

	/**
	 * Called when a valid [ is encountered
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonArrayOpen() { return false; }
	/**
	 * Called when a valid ] is encountered
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonArrayClose() { return false; }

	/**
	 * Called when a valid non-object-key string is encountered
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonString(const std::string& s) { return false; }

	/**
	 * Called when a valid number is encountered.  This method is invoked
	 * only if conversionToUse returns JNUM_CONV_RAW.
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonNumber(const std::string& n) { return false; }
	/**
	 * Called when a valid number is encountered.  This method is invoked
	 * only if conversionToUse returns JNUM_CONV_NATIVE and the JSON number can be
	 * converted perfectly to a 64-bit integer.  Careful because even if you expect a floating point
	 * number, you may receive an integer.
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonNumber(int64_t number) { return false; }
	/**
	 * Called when a valid number is encountered.  This method is invoked
	 * only if the number cannot be converted to a 64-bit integer.  Any errors converting this
	 * to a number are passed along (e.g. potential loss of precision, overflows, etc).
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonNumber(double &number, ConversionResultFlags asFloat) { return false; }
	/**
	 * Called when a valid boolean is encountered.
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonBoolean(bool truth) { return false; }
	/**
	 * Called when a valid null is encountered.
	 * @return Whether or not parsing should continue.
	 */
	virtual bool jsonNull() { return false; }

	/**
	 * Called when the schema should be resolved.  By default, this does not need to be overridden
	 * (it invokes the resolver you created this class with).
	 * @param abstractResolver - The resolution information from the C library
	 * @param resolvedSchema - An output variable.  It is set to the parsed external schema & ownership is
	 *                         transferred to the invoker of the callback.  This should be NULL if and only if
	 *                         the return value is not SCHEMA_RESOLVED.
	 * @return Whether or not resolution of the external schema reference succeeded.
	 */
	virtual JSchemaResolutionResult resolve(JSchemaResolverRef abstractResolver, jschema_ref *resolvedSchema);

	/**
	 * How your parser expects numbers to be handled.
	 * JNUM_CONV_NATIVE - The numeric string is converted to a 64-bit integer or a floating point
	 *                    number for you (using proper JSON number parsing - no assumptions about
	 *                    limits like most parsers do).
	 * JNUM_CONV_RAW    - The numeric string is passed in untouched.  Use this only if you have
	 *                    some well defined need that can't be served by using native types
	 *                    (if there are any bugs in the number parser, I would recommend fixing those
	 *                    instead of trying to work around by doing it yourself).
	 *
	 * @return The number type this parser is expecting.  This controls the sax routine
	 *         that is called for number notification.
	 */
	virtual NumberType conversionToUse() const = 0;

	JErrorHandler* errorHandlers() const;
	void setErrorHandlers(JErrorHandler* errors);
private:
	std::stack<std::string> m_keyStack;
	std::stack<DocumentState> m_stateStack;
	JErrorHandler* m_errors;
	JResolver* m_resolver;

	friend class SaxBounce;
	friend JSchemaResolutionResult sax_schema_resolver(JSchemaResolverRef resolver, jschema_ref *resolvedSchema);
};

}

#endif /* JPARSER_H_ */
