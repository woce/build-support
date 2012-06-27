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

#ifndef JSCHEMA_CXX_H_
#define JSCHEMA_CXX_H_

#include "japi.h"
#include "../c/compiler/nonnull_attribute.h"
#include "../c/jschema_types.h"
#include "JValue.h"

/**
 * Not thread safe.  Do not share instances of this class
 * between threads.
 *
 * Javascript-style comments are allowed within schemas.
 *
 * This is an abstract class representing a JSON schema as defined in http://json-schema.org.
 * Schemas are used to ensure that any conversion to/from serialized form generates data
 * that is semantically valid (IPC, for large part, is the biggest visible user targetted for this feature).
 */
namespace pbnjson {

class PJSONCXX_API JSchema
{
protected:
	/**
	 * Represents a resource that can be shared by multiple
	 * JSchema instances so that there's as little overhead as possible
	 * for sharing JSchemas.
	 *
	 * This represents the data backing the schema representation.  Right now,
	 * it represents the string backing the schema so a number of memory-saving & space-saving
	 * techniques can be used, although nothing really makes requirements about what needs to
	 * back the schema.
	 *
	 * The primary user is JSchemaFile which uses this for memory-mapping
	 * the file & using the memory-mapped file to back the schema.
	 */
	class Resource {
	public:
		enum SchemaOwnership {
			TakeSchema,
			CopySchema,
		};

		Resource();
		/**
		  * \p schema The schema this resource wraps.  Lifetime of the schema
		  *    is tied to the lifetime of this resource
		  * \p ownership Indicates that the schema is owned
		  *    outside of this resource and it needs to grab a copy
		  */
		Resource(jschema_ref schema, SchemaOwnership ownership);
		/**
		  * \p data Some arbitrary pointer to a data structure.  Meant for
		  *    subclass use.
		  * \p schema The schema this resource wraps.  Lifetime of the schema
		  *    is tied to the lifetime of this resource
		  * \p ownership Indicates that the schema is owned
		  *    outside of this resource and it needs to grab a copy
		  */
		Resource(void *data, jschema_ref schema, SchemaOwnership ownersehip);

		virtual ~Resource();

		jschema_ref schema();
	protected:
		void *data() const;

	private:
		void ref();
		bool unref();

		int m_refCnt;
		void *m_data;
		jschema_ref m_schema;

		friend class JSchema;
	};

private:
	Resource *m_resource;

protected:
	jschema_ref peek() const {
		if (m_resource == NULL)
			return NULL;
		return m_resource->schema();
	}

	/**
	 * Construct a schema wrapper from the backing resource.
	 */
	JSchema(Resource *resource);
public:
	/**
	 * A schema that is guaranteed to never accept any input
	 * as valid.
	 */
	static JSchema NullSchema();

	/**
	 * Create a copy of the schema object.
	 */
	JSchema(const JSchema& other);
	virtual ~JSchema();

	/**
	 */
	virtual JSchema& operator=(const JSchema& other);

	virtual bool isInitialized() const;

	friend class JParser;
	friend class JGenerator;
	friend class JDomParser;
};

}

#endif /* JSCHEMA_CXX_H_ */
