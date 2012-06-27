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

#ifndef JRESOLVER_H_
#define JRESOLVER_H_

#include "JSchema.h"

namespace pbnjson {

class PJSONCXX_API JResolver {
public:
	class ResolutionRequest {
	public:
		ResolutionRequest(const JSchema &schema, const std::string &resource);

		JSchema schema() const;
		std::string resource() const;
	private:
		JSchema m_ctxt;	/// the schema that generated the resolution request
		std::string m_resource;	/// the resource name that needs resolution
	};

	JResolver();
	virtual ~JResolver();

	/**
	 * An external reference was made within a schema - the user
	 * of the library is responsible for converting this abstract concept
	 * of a reference to an actual schema.
	 */
	virtual JSchema resolve(const ResolutionRequest &request, JSchemaResolutionResult &resolutionResult) = 0;
};

}

#endif /* JRESOLVER_H_ */

