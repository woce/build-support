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

#ifndef JERROR_HANDLER_H_
#define JERROR_HANDLER_H_

#include "japi.h"

namespace pbnjson {

class JParser;

class PJSONCXX_API JErrorHandler
{
public:

	enum SyntaxError {
		ERR_SYNTAX_GENERIC = 20,
	};

	enum SchemaError {
		ERR_SCHEMA_GENERIC = 40,
	};

	enum BadObject {
		ERR_BAD_OBJECT_OPEN = 60,
		ERR_BAD_OBJECT_KEY,
		ERR_BAD_OBJECT_CLOSE,
	};

	enum BadArray {
		ERR_BAD_ARRAY_OPEN = 80,
		ERR_BAD_ARRAY_CLOSE,
	};

	JErrorHandler(const JErrorHandler& handler);
	virtual ~JErrorHandler();

	virtual void syntax(JParser *ctxt, SyntaxError code, const std::string& reason) = 0;
	virtual void schema(JParser *ctxt, SchemaError code, const std::string& reason) = 0;
	virtual void misc(JParser *ctxt, const std::string& reason) = 0;
	virtual void badObject(JParser *ctxt, BadObject code) = 0;
	virtual void badArray(JParser *ctxt, BadArray code) = 0;
	virtual void badString(JParser *ctxt, const std::string& str) = 0;
	virtual void badNumber(JParser *ctxt, const std::string& number) = 0;
	virtual void badBoolean(JParser *ctxt) = 0;
	virtual void badNull(JParser *ctxt) = 0;
	virtual void parseFailed(JParser *ctxt, const std::string& reason) = 0;

protected:
	JErrorHandler();
};

}

#endif /* JERROR_HANDLER_H_ */
