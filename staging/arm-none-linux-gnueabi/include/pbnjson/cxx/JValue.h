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

#ifndef JVALUE_CXX_H_
#define JVALUE_CXX_H_

#include "japi.h"

#include "../c/jconversion.h"
#include "../c/compiler/nonnull_attribute.h"
#include "../c/jcallbacks.h"
#include "../c/jtypes.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <stdint.h>

#define PBNJSON_ZERO_COPY_STL_STR 0

namespace pbnjson {

class JSchema;

/**
 * This class represents an opaque object containing a JSON value.
 * The type that it represents can be any valid JSON value:
 * @li Object: As a string, represented as {"key":value,"key2":value} where values are any JSON type. Equivalent to the concept of an unordered map.
 * @li Array: As a string, represented by [] with comma-separated elements.  Elements are any JSON type.
 * @li String: Represented by text surrounded with double-quotes.  Double-quotes within the string are escaped with '\'
 * @li Number: An abstract number type that can be represented in several forms as a string (+/-XXXX.YYYYEZZZZ) where almost all the parts
 *             are optional.
 * @li Boolean: As a string, "true" or "false" (without quotes).  
 * @li Null: As a string, "null" (without quotes).
 * @see http://www.json.org
 */
class PJSONCXX_API JValue {
	friend class JDomParser;
	friend class JGenerator;
	friend JValue Object();
	friend JValue Array();

private:
	static JValue JNULL;

	jvalue_ref m_jval;
	std::string m_input;
#if PBNJSON_ZERO_COPY_STL_STR
	std::vector<std::string> m_children;
#endif

	JValue(jvalue_ref toOwn);
	JValue(jvalue_ref parsed, std::string input);

	static JValue& Null()
	{
		return JNULL;
	}
protected:
	jvalue_ref peekRaw() const {
		return m_jval;
	}

	jvalue_ref grabOwnership() {
		jvalue_ref transferred = m_jval;
		m_jval = JNULL.m_jval;
		return transferred;
	}

public:
	/**
	 * Convenience alias for representing a key/value pair within a JSON object.
	 */
	typedef std::pair<JValue, JValue> KeyValue;

	//{@
	/**
	 * Constructs an object representing JSON null.
	 *
	 * @see Object()
	 * @see Array()
	 */
	/**
	 * Constructs the default JSON value (NULL).
	 *
	 * @see pbnjson::Object
	 * @see pbnjson::Array
	 * @see template<class V> JValue(const V& v)
	 * @see JValue(const char *)
	 */
	JValue();

	/**
	 * Regular copy constructor - no magic here.
	 *
	 * @param[in] other
	 */
	JValue(const JValue& other);
	
	/**
	 * Convenience method to construct a JSON string.
	 * \note This isn't a routine to parse JSON.  It actually creates a JSON representation of a string.
	 * @todo: Document why this isn't a specialization of the template constructor (I believe it was causing confusion for the compiler)
	 *
	 * @param[in] value The c-string to construct a JSON string from.
	 *
	 * @see JValue()
	 * @see Object()
	 * @see Array()
	 */
	JValue(const char *value);

	/**
	 * This constructor is explicitely specialized - it is used
	 * to construct a primitive JSON value (string, number, boolean).
	 * 
	 * The supported C types are converted as follows:
	 *    std::string : JSON string
	 *    int32_t, int64_t, double, NumericString : JSON number
	 *    bool : JSON bool
	 *
	 * @param[in] v The value to convert to a JSON value.
	 *
	 * @see NumericString
	 * @see Object()
	 * @see Array()
	 * @see JValue()
	 */
	template <class V>
	JValue(const V& v);
	//@}
	~JValue();

	//{@
	/**
	 * Copy the other JSON value into this one.
	 *
	 * @param[in] other The JSON value to copy.
	 * @return The reference to this object except with its contents re-assigned to be a copy of the
	 *         other value.
	 */
	JValue& operator=(const JValue& other);

	/**
	 * Convenience method - negation of what the equality operator would return
	 *
	 * @param[in] other
	 * @return
	 */
	template <class T>
	bool operator!=(const T& other) const { return !((*this) == other); }

	/**
	 * Test this object against another object.
	 *
	 * @param[in] other The JSON value to compare against
	 * @return True if and only if this object represents a JSON value that is equivalent to this JSON value
	 *         as outlined by the equivalence operators for string, double, int, bool, etc).  In essecence,
	 *         it must have the same JSON type & contain the same contents.
	 *         For objects, they must have the same key-value pairs.
	 *         For arrays, they must have the same elements in the same order.
	 */
	bool operator==(const JValue& other) const;
	/**
	 * Test this object against a string.
	 *
	 * @param[in] other The value to test this JSON string against.
	 * @return True if and only if this object represents a JSON string with the same bytes (careful here if you need
	 *         actual textual comparison and you have utf8).
	 */
	bool operator==(const std::string& other) const;
	/**
	 * Test this object against a floating point number.
	 * @param[in] other The value to test this JSON number against
	 * @return True if and only if this object represents a JSON number with the same value.
	 */
	bool operator==(const double& other) const;
	/**
	 * Test this object against a 64-bit signed integer.
	 *
	 * @param[in] other The value to test this JSON number against.
	 * @return True if and only if this object represents a JSON number that can be converted
	 * to a 64-bit signed integer without error and it has a value equivalent to the requested value.
	 */
	// using const with pass-by-reference so that we minimize the amount of copies on 32-bit machines
	// and make it easier for the compiler to optimize
	bool operator==(const int64_t& other) const;
	/**
	 * Test this object against a 32-bit signed integer.
	 *
	 * @param[in] other The value to test this JSON number against.
	 * @return True if and only if this object represents a JSON number that can be converted
	 * to a 32-bit signed integer without error and it has a value equivalent to the requested value.
	 */
	bool operator==(int32_t other) const;
	/**
	 * Test whether this object has the requested boolean value.
	 *
	 * @param[in] other The value to test this JSON boolean against.
	 * @return True if and only if this object represents a JSON boolean with the given value.
	 */
	bool operator==(bool other) const;
	//@}

	/**
	 * Lookups up the value in this array with the given index
	 *
	 * @note There are 3 different cases that are indistinguishable when using this API:
	 *     1)  This value doesn't represent a JSON array
	 *     2)  The index is out of bounds
	 *     3)  The value associated with that index is null
	 *
	 * @param[in] index The key to look up
	 * @return The value at the requested index.
	 * @see JValue::isNull
	 * @see JValue::hasKey
	 * @see JValue::isArray
	 */
	JValue operator[](int index) const;

	//{@
	/**
	 * Lookups up the value in this object mapped to the given key.
	 *
	 * @note There are 3 different cases that are indistinguishable when using this API:
	 *     1)  This value doesn't represent a JSON object
	 *     2)  The key doesn't exist
	 *     3)  The value associated with this key is null
	 *
	 * @param[in] key The key to look up
	 * @return The value associated with the key.
	 * @see JValue::isNull
	 * @see JValue::hasKey
	 * @see JValue::isObject
	 */
	JValue operator[](const std::string& key) const;
	/**
	 * Convenience method to access values within this JSON object,
	 * without using STL.
	 *
	 * @param[in] key The key to look up
	 * @return The value associated with the key, or a JSON null if this isn't a JSON object.
	 */
	JValue operator[](const raw_buffer& key) const;
	//@}


	/**
	 * Returns whether or not this JSON object has a key/value pair with the given key.
	 *
	 * @param[in] key The key to find in the object
	 * @return True if and only if this JValue represents a JSON object & the object contains
	 *         the key.
	 */
	bool hasKey(const std::string& key) const;

	/**
	 * Returns the length of this JSON array.
	 *
	 * @return The size of the array, or -1 if this isn't an array.
	 */
	ssize_t arraySize() const;


	//{@
	/**
	 * Convenience method.
	 * @param[in] i
	 * @param[in] value
	 * @return
	 * @see put(size_t, const JValue&)
	 */
	bool put(long i, const JValue& value)
	{
		if (i < 0)
			return false;
		return put((size_t)i, value);
	}

	/**
	 * Convenience method.
	 * @param[in] i
	 * @param[in] value
	 * @return
	 * @see put(size_t, const JValue&)
	 */
	bool put(int i, const JValue& value)
	{
		return put((long)i, value);
	}

	/**
	 * Insert a JSON value into this array.
	 *
	 * @param[in] index The index to insert into.  If it is past the end of the array, then
	 *              all intermediary elements are initialized to NULL.  Any elements >= index,
	 *              are shifted up by 1.
	 * @param[in] value The JSON value to insert at that index.
	 * @return True if this object represents a JSON array & the element was successfully inserted at the requested location.
	 */
	bool put(size_t index, const JValue& value);
	//@}

	//{@
	/**
	 * Convenience method for adding a value to a JSON object.
	 *
	 * This behaves like a regular map if the key already exists.
	 *
	 * @param[in] key
	 * @param[in] value Any JSON object.
	 * @return True if this object represents a JSON object, the key represents a JSON string, & the key/value pair was successfully inserted.
	 */
	bool put(const std::string& key, const JValue& value);

	/**
	 * Add a key/value pair to a JSON object.
	 *
	 * This behaves like a regular map if the key already exists.
	 *
	 * @param[in] key An object representing a JSON string
	 * @param[in] value Any JSON object.
	 * @return True if this object represents a JSON object, the key represents a JSON string, & the key/value pair was successfully inserted.
	 */
	bool put(const JValue& key, const JValue& value);

	/**
	 * Convenience method for adding a value to a JSON object.
	 *
	 * This behaves like a regular map if the key already exists.
	 *
	 * @param[in] key
	 * @param[in] value
	 * @return True if this object represents a JSON object & the key/value pair was successfully inserted.
	 */
	bool put(const char *key, const JValue& value)
	{
		return put(std::string(key), value);
	}
	//@}

	/**
	 * Convenience method for appending an element to an array.
	 *
	 * If this isn't an array or some other error during insertion occurred, then the return is a JSON null.
	 *
	 * @param[in] element The JSON value to append to this array.
	 * @return A reference to this object if this represents a JSON array or JSON null otherwise.
	 */
	JValue& operator<<(const JValue& element);

	/**
	 * Convenience method for adding a key-value pair to an object.
	 *
	 * If this isn't an object, or some other error during insertion occurred, then the return is a JSON null.
	 *
	 * @param[in] pair
	 * @return A reference to this object if this value represents a JSON object or JSON null otherwise.
	 */
	JValue& operator<<(const KeyValue& pair);

	/**
	 * Convenience method for appending to a JSON array.
	 *
	 * @param[in] value The JSON value to append to this array
	 * @return True if this value is an array & the value was added successfully.
	 */
	bool append(const JValue& value);

	/**
	 * Determines whether or not this JSON value represents a NULL
	 * @return True if this is a JSON null, false otherwise
	 */
	bool isNull() const;

	/**
	 * Determines whether or not this JSON value represents a number.
	 * @return True if this is a JSON number, false otherwise.
	 */
	bool isNumber() const;

	/**
	 * Determines whether or not this JSON value represents a string.
	 * @return True if this is a JSON string, false otherwise.
	 */
	bool isString() const;
	/**
	 * Determines whether or not this JSON value represents a object.
	 * @return True if this is a JSON object, false otherwise.
	 */
	bool isObject() const;
	/**
	 * Determines whether or not this JSON value represents a array.
	 * @return True if this is a JSON array, false otherwise.
	 */
	bool isArray() const;
	/**
	 * Determines whether or not this JSON value represents a boolean.
	 * @return True if this is a JSON boolean, false otherwise.
	 */
	bool isBoolean() const;

	//{@
	/**
	 * Store the numeric representation of this number in the requested native type.
	 *
	 * This library doesn't make any assumptions about the native type to use when representing the number.  Instead,
	 * when you ask the library to convert it to a native type (e.g. int, double), it will convert it & return a conversion result
	 * indicating how accurately the native type represents the original string.
	 *
	 * @note Rounding errors in native floating point representation are not necessarily accounted for.
	 * For example, if the serialized JSON contained 0.01, the returned value may return
	 * ::CONV_OK even though the native type will not be exactly 0.01 - this may change).
	 *
	 * @note Integers are indistinguishable from floating point numbers (even if the serialized form is X.000000).  This is by design.
	 *
	 * @param[out] number Pass-by-reference to the variable to store the converted result in.
	 * @return ::CONV_OK if this objects represents a number that was stored in the native type without any problems.
	 */
	template <class T>
	ConversionResultFlags asNumber(T& number) const;

	/**
	 * Converts this JSON value to a native numeric type.  This is a convenience method I strongly
	 * recommend you do not use.
	 *
	 * @note Behaviour is undefined if this JSON value does not represent a number.
	 *
	 * @return The native numeric representation of this JSON value.
	 */
	template <class T>
	T asNumber() const
	{
		T result;
		asNumber(result);
		return result;
	}
	//@}

	/**
	 * Store the text within this JSON value (if it is a JSON string) within the STL string.
	 *
	 * @param[out] asStr Pass-by-reference to the STL string to copy in to
	 * @return ::CONV_OK if this JSON value represents a JSON string, otherwise some error code.
	 */
	ConversionResultFlags asString(std::string& asStr) const;

	/**
	 * Converts this JSON value to a native string type.  This is a convenience method I strongly
	 * recommend you do not use.
	 *
	 * Behaviour is undefined if this JSON value does not represent a string.
	 *
	 * @return The native string representation of this JSON value.
	 */
	std::string asString() const
	{
		std::string result;
		asString(result);
		return result;
	}

	/**
	 * Converts this JSON value to a native boolean type.
	 *
	 * @param[out] value Pass-by-reference to the boolean to assign
	 * @return ::CONV_OK if this JSON value represents a JSON boolean.
	 */
	ConversionResultFlags asBool(bool &value) const;

	/**
	 * Convenience method to convert to a boolean.  I strongly discourage using it.
	 *
	 * 
	 */
	bool asBool() const
	{
		bool result;
		asBool(result);
		return result;
	}

#if 0
	/**
	 * Convenience method to avoid having to construct a JGenerator.
	 *
	 * @see JGenerator
	 */
	bool toString(const JSchema& schema, std::string& toStr) const;
#endif

	/**
	 * The iterator class for key/value pairs in a JSON object.
	 */
	class ObjectIterator : public std::iterator<std::input_iterator_tag, JValue, void, void, void> {
		friend class JValue;

	private:
		jobject_iter i;
		jvalue_ref m_parent;
//		KeyValue m_keyval;

	protected:
		ObjectIterator(jvalue_ref parent, const jobject_iter &i);

	public:
		ObjectIterator();
		~ObjectIterator();

		ObjectIterator(const ObjectIterator& other);

		ObjectIterator& operator=(const ObjectIterator& other);

		/**
		 * Pre-increment the iterator to the next element.
		 *
		 * \note Behaviour is undefined if you try to do this to end()
		 *
		 * \return This iterator except it has moved 1 element forward.
		 */
		ObjectIterator& operator++();
		/**
		 * Post-increment the iterator to the next element.
		 *
		 * \note Behaviour is undefined if you try to do this to end()
		 *
		 * \see ObjectIterator::operator++()
		 * \return An iterator representing the current element (not the next element)
		 */
		ObjectIterator operator++(int);
		/**
		 * Jump n elements forward.  Note that this is likely an O(n)
		 * operation.
		 *
		 * \note Behaviour is unspecified if you try to jump to an element after the last one.
		 * \note Behaviour is undefined if you try to do this to end()
		 *
		 * \return An iterator representing n elements ahead.
		 */
		ObjectIterator operator+(int n) const;
		/**
		 * Pre-decrement the iterator the previous element.
		 *
		 * \note Behaviour is undefined if you try to do this to the first element.
		 * \note Behaviour is undefined if you try to do this to the end()
		 *
		 * \return This iterator except it has moved 1 element back.
		 */
		ObjectIterator& operator--();
		/**
		 * Post-decrement the iterator to the previous element.
		 *
		 * \note Behaviour is undefined if you try to use this once you hit the end.
		 *
		 * \see ObjectIterator::operator--()
		 * \return An iterator representing the current element (not the previous element)
		 */
		ObjectIterator operator--(int);
		/**
		 * Jump n elements backward.
		 *
		 * \note It is an implementation detail, but currently this is an O(n) operation.
		 *
		 * \param n The amount of elements to jump backward
		 * \return An iterator representing the position of this iteration - n elements.
		 */
		ObjectIterator operator-(int n) const;

		/**
		 * Convenience operator for determining inequality.
		 *
		 * @return True if the iterators point to different key/value pairs.
		 * @see operator==(const ObjectIterator&)
		 */
		bool operator!=(const ObjectIterator& other) const { return !(this->operator==(other)); }


		/**
		 * Determine equality between iterators - do they point to the same key/value pair.
		 *
		 * @note Behaviour is unspecified if objects are modified during iteration.
		 *
		 * @param[in] other The iterator to compare to
		 * @return True if both iterators are for the same object and represent the same point in iteration.
		 */
		bool operator==(const ObjectIterator& other) const;

		/**
		 * Retrieve the key-value pair this iterator represents.
		 *
		 * \note If you iterate, the key/value stored within the reference are undefined.
		 *
		 * @return A pair of JValue objects.  The key is a string and the value is any JSON value.  If this is not a valid iterator,
		 *         then JSON null is returned for both fields.
		 */
		KeyValue operator*();
	};

	/**
	 * The iterator class for key/value pairs in a JSON object.
	 */
	class ObjectConstIterator : public std::iterator<std::input_iterator_tag, JValue, void, void, void> {
		friend class JValue;

	private:
		jobject_iter i;
		jvalue_ref m_parent;

	protected:
		ObjectConstIterator(jvalue_ref parent, const jobject_iter &i);

	public:
		ObjectConstIterator();
		~ObjectConstIterator();

		ObjectConstIterator(const ObjectConstIterator& other);

		ObjectConstIterator& operator=(const ObjectConstIterator& other);

		/**
		 * Pre-increment the iterator to the next element.
		 *
		 * \note Behaviour is undefined if you try to do this to end()
		 *
		 * \return This iterator except it has moved 1 element forward.
		 */
		ObjectConstIterator& operator++();
		/**
		 * Post-increment the iterator to the next element.
		 *
		 * \note Behaviour is undefined if you try to do this to end()
		 *
		 * \see ObjectConstIterator::operator++()
		 * \return An iterator representing the current element (not the next element)
		 */
		ObjectConstIterator operator++(int);
		/**
		 * Jump n elements forward.  Note that this is likely an O(n)
		 * operation.
		 *
		 * \note Behaviour is unspecified if you try to jump to an element after the last one.
		 * \note Behaviour is undefined if you try to do this to end()
		 *
		 * \return An iterator representing n elements ahead.
		 */
		ObjectConstIterator operator+(int n) const;
		/**
		 * Pre-decrement the iterator the previous element.
		 *
		 * \note Behaviour is undefined if you try to do this to the first element.
		 * \note Behaviour is undefined if you try to do this to the end()
		 *
		 * \return This iterator except it has moved 1 element back.
		 */
		ObjectConstIterator& operator--();
		/**
		 * Post-decrement the iterator to the previous element.
		 *
		 * \note Behaviour is undefined if you try to use this once you hit the end.
		 *
		 * \see ObjectConstIterator::operator--()
		 * \return An iterator representing the current element (not the previous element)
		 */
		ObjectConstIterator operator--(int);
		/**
		 * Jump n elements backward.
		 *
		 * \note It is an implementation detail, but currently this is an O(n) operation.
		 *
		 * \param n The amount of elements to jump backward
		 * \return An iterator representing the position of this iteration - n elements.
		 */
		ObjectConstIterator operator-(int n) const;

		/**
		 * Convenience operator for determining inequality.
		 *
		 * @return True if the iterators point to different key/value pairs.
		 * @see operator==(const ObjectConstIterator&)
		 */
		bool operator!=(const ObjectConstIterator& other) const { return !(this->operator==(other)); }


		/**
		 * Determine equality between iterators - do they point to the same key/value pair.
		 *
		 * @note Behaviour is unspecified if objects are modified during iteration.
		 *
		 * @param[in] other The iterator to compare to
		 * @return True if both iterators are for the same object and represent the same point in iteration.
		 */
		bool operator==(const ObjectConstIterator& other) const;

#if 0
		// TODO: implement const-safe key/value access

		/**
		 * Retrieve the key-value pair this iterator represents.
		 *
		 * \note If you iterate, the key/value stored within the reference are undefined.
		 *
		 * @return A pair of JValue objects.  The key is a string and the value is any JSON value.  If this is not a valid iterator,
		 *         then JSON null is returned for both fields.
		 */
		KeyValue operator*();

		/**
		 * Access the key/value pair this iterator represents.
		 *
		 * \note If you iterate, the key/value stored within the reference are undefined.
		 *
		 * \return A pair of JValue objects.  The key is a string and the value is any JSON value.  If this is not a valid iterator,
		 *         then JSON null is returned for both fields.
		 */
		KeyValue operator->();
#endif
	};

	/**
	 * Get the beginning iterator for this object.
	 *
	 * \note Behaviour is undefined if this isn't an object.
	 *
	 * \note Behaviour is currently undefined if you try to modify an object while iterating.
	 *       This is untested & likely unsafe.
	 *
	 * @note Iterating over this array is equivalent to walking a linked list.  However,
	 *       do not rely on this; if you need this performance behaviour, then please
	 *       tell me so I can properly mark this as a design requirement.
	 *
	 * @return An iterator representing the key/value pairs within this JSON object.
	 *
	 * \see end()
	 * \see begin() const
	 */
	ObjectIterator begin();
	/**
	 * Const-safe version of the iterator.
	 * \see begin()
	 * \return An iterator representing the key/value pairs within this JSON object.
	 */
	ObjectConstIterator begin() const;

	/**
 	 * Get the iterator representing the position after the last key-value pair in this object.
 	 *
 	 * \note Behaviour is undefined if this isn't an object.
 	 *
 	 * \note Behaviour is currently undefined if you try to modify an object while iterating.
 	 *       This is untested & likely unsafe.
 	 *
 	 * \note Behaviour is undefined if you try to iterate the returned iterator.
 	 *
 	 * \return An iterator representing the position after the last key/value pair in this JSON object.
 	 *
 	 * \see begin()
 	 * \see end() const
 	 */
	ObjectIterator end();
	/**
	 * Const-safe version of the iterator.
	 * \return An iterator representing the position after the last key/value pair in this JSON object
	 * \see end()
	 */
	ObjectConstIterator end() const;
};

/**
 * Convenience class for creating an already serialized form of a number.
 * This is useful if you want to avoid any serialization from native types to
 * string (or if you want a specific representation when serialized).
 *
 * @note All the constructors are explicit to avoid collisions with creating JSON
 * strings.
 */
class NumericString : public std::string
{
public:
	explicit NumericString() : std::string("0") {}
	//explicit NumericString(const char *str) : std::string(str) {}
	template <class T>
	explicit NumericString(const T& other) : std::string(other) {}
	NumericString(const char *str, size_t len) : std::string(str, len) {}

	NumericString& operator=(const NumericString& other) { std::string::operator=(other); return *this; }
	NumericString& operator=(const std::string& other) { std::string::operator=(other); return *this; }
	NumericString& operator=(const char *other) { std::string::operator=(other); return *this; }
	bool operator==(const NumericString& other) const { return this->operator==(reinterpret_cast<const std::string&>(other)); }
	bool operator==(const std::string& other) const { return reinterpret_cast<const std::string&>(*this) == other; }

	operator JValue();
};
//{@
/**
 * Return an object representing a JSON object.
 */
JValue Object();

/**
 * Return an object representing a JSON array.
 */
JValue Array();

///\name Constructor template specializations
//{@
#if 0
template <>
JValue JValue::Value<int64_t>(const int64_t& value);
template <>
JValue JValue::Value<double>(const double& value);
template <>
JValue JValue::Value<std::string>(const std::string &value);
template <>
JValue JValue::Value<bool>(const bool& value);
template<>
JValue JValue::Value<NumericString>(const NumericString& value);
#endif

template <>
JValue::JValue(const int32_t& value);
template <>
JValue::JValue(const int64_t& value);
template <>
JValue::JValue(const double& value);
template <>
JValue::JValue(const std::string &value);
template <>
JValue::JValue(const bool& value);
template<>
JValue::JValue(const NumericString& value);
//@}

/*! \name asNumber template specializations
 * The different explicit specializations of the templatized asNumber
 * @see JValue::asNumber(T&) const
 */
//{@
template <>
ConversionResultFlags JValue::asNumber<int32_t>(int32_t& value) const;
template <>
ConversionResultFlags JValue::asNumber<int64_t>(int64_t& value) const;
template <>
ConversionResultFlags JValue::asNumber<double>(double& value) const;
template <>
ConversionResultFlags JValue::asNumber<std::string>(std::string& value) const;
template <>
ConversionResultFlags JValue::asNumber<NumericString>(NumericString& value) const;

template <>
int32_t JValue::asNumber<int32_t>() const;
template <>
int64_t JValue::asNumber<int64_t>() const;
template <>
double JValue::asNumber<double>() const;
template <>
std::string JValue::asNumber<std::string>() const;
template <>
NumericString JValue::asNumber<NumericString>() const;
//@}

#if 0
// currently disabled because this allows bypass of schemas.
/**
 * Convenience method for serializing a JSON value to some arbitrary ostream.
 *
 * @param out The output stream to write to
 * @param toprint The JSON value to serialize
 * @return out
 */
std::ostream& operator<<(std::ostream& out, const JValue &toprint);
#endif

}

#endif /* JVALUE_H_ */
