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

#ifndef JSCHEMA_FILE_CXX_H_
#define JSCHEMA_FILE_CXX_H_

#include "japi.h"
#include "JSchema.h"

namespace pbnjson {

/**
 * Javascript-style comments are allowed within schemas.
 *
 * Makes an optimization in that the object will actually just
 * memory map the schema.
 *
 * Should help keep memory usage to a minimum even with lots of schemas & since
 * all this will be read-only, they are easier to swap out.
 *
 * This class is not thread safe at the moment
 * (do not share a JSchemaFile object across threads).  If you find this is a common
 * pattern, let the maintainer know.
 *
 * <palm-internal-comment>
 * Direct usage of this class will likely go away in the future - instead upper layers
 * (i.e. luna service bus) will automatically handle most schema work for you.
 *
 * For now though, this class is the recommended mechanism for utilizing schemas.
 * </palm-internal-comment>
 */
class PJSONCXX_API JSchemaFile : public JSchema
{
private:
	struct Map {
		void *data;
		int64_t size;
	};

	class MMapResource : public JSchema::Resource {
	public:
		/**
		  * \p schemaFile The mmap backing the schema
		  * \p schema The parsed schema representation of the file.
		  *           This resources takes ownership over the schema.
		  *           Do not use the schema directly afterwards.
		  */
		MMapResource(Map &schemaFile, jschema_ref schema);
		~MMapResource();
	};


	static bool initSchemaMap(int fd, Map& map);
	static JSchema::Resource* createSchemaMap(int fd);
	static JSchema::Resource* createSchemaMap(const std::string &path);

public:
	/**
	 * Create a schema representation from a C FILE object.
	 * The ownership of the FILE object remains with the caller -
	 * closing it is the responsibility of the opener (this will not
	 * automatically close it for you).
	 *
	 * NOTE: you must supply a file object representing a mmap'able file.
	 *
	 * @see isInitialized
	 */
	JSchemaFile(FILE *f);

	/**
	 * Create a schema representation from file descriptor.
	 *
	 * The
	 * NOTE: you must supply a file object representing a mmap'able file.
	 *
	 * @see isInitialized
	 */
	JSchemaFile(int fileno);

	/**
	 * Create a schema representation from the file with the given path.
	 *
	 * NOTE: you must supply a path representing a mmap'able file.
	 *
	 * @see isInitialized
	 */
	JSchemaFile(const std::string& path);

	/**
	 * Copy the schema file.
	 *
	 * Behaviour is undefined if the object to copy was not initialized succesfully.
	 */
	JSchemaFile(const JSchemaFile& other);

	/**
	 * Release any resources associated with this object.  This in essence
	 * is a release of the mmap if no other objects hold a map open.
	 */
	virtual ~JSchemaFile();
};

}

#endif /* JSCHEMA_FILE_CXX_H_ */
