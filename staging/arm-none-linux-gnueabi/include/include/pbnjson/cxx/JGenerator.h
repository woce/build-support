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
 * JGenerator.h
 *
 *  Created on: Sep 24, 2009
 */

#ifndef JGENERATOR_H_
#define JGENERATOR_H_

#include "japi.h"
#include "JValue.h"
#include "JSchema.h"

namespace pbnjson {

class JResolver;

class PJSONCXX_API JGenerator {
public:
	JGenerator(JResolver *resolver = NULL);
	~JGenerator();

	/**
	 * Equivalent to Javascript's JSON.stringify; converts this JSON DOM into a string ready for over-the-wire
	 * transport.
	 *
	 * @param val The JSON value to convert to a string.
	 *        NOTE: Behaviour is unspecified if this value doesn't represent an object or array. Most likely, it'll fail.
	 * @param schema The schema to use to ensure the DOM is in the correct format for over-the-wire
	 * @param asStr The stringified version of the JSON DOM
	 *
	 * @return True if the DOM was successfully stringified, false otherwise.  False typically indicates a schema violation or invalid DOM
	 *         (e.g. Root of DOM isn't an object or array)
	 */
	bool toString(const JValue &val, const JSchema& schema, std::string &asStr);

	/**
	 * Convenience function to wrap call to toString for JSON objects/arrays.
	 *
	 * Any other type will return an empty string.
	 *
	 * @param val
	 * @param schema
	 * @param resolver The resolver to use for the schema (only necessary if it contains external references
	 * @return The JSON string serialized to a string or the empty string on error (violated schema).
	 */
	static std::string serialize(const JValue &val, const JSchema &schema, JResolver *resolver = NULL);
private:
	JResolver *m_resolver;
};

}

#endif /* JGENERATOR_H_ */
