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

#ifndef JOBJECT_H_
#define JOBJECT_H_

#include <stdint.h>
#include <stdbool.h>

#include <unistd.h>	// for long
#include <assert.h>
#include <string.h>

#include "japi.h"
#include "jschema.h"
#include "jconversion.h"
#include "compiler/pure_attribute.h"
#include "compiler/nonnull_attribute.h"
#include "compiler/unused_attribute.h"
#include "compiler/builtins.h"
#include "jtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create - creates a JSON value with ownership given to the caller.  This call will usually only ever return NULL if memory allocation failed or a reference to a valid
 *          JSON value (never a reference to a JSON null).  Still, it is recommended to use jis_null to check the result (in fact, always use jis_null instead of actually
 *          comparing against some value).  For instance, the creation of a number from a double might return null if you attempt to provide it with a NaN or an infinity or any other
 *          unsupported value.
 *
 * Copy - grab ownership of the specified value.  Any changes to val must be reflected in the resultant value.
 * Release - release ownership of the specified value (after a Release, it is forbidden to use the pointer)
 * Get - no ownership change - only valid for as long as the parent has an owner for the duration the child is used.
 * Set/Add - no ownership change - both the parent that has a value set and the original owner have valid references (parent will grab a copy)
 * Put/Append - ownership is transferred to the jvalue_ref parent ( you lose ownership - the lifetime of the object becomes that of the parent unless you have explicitely
 *              grabbed a copy before-hand)
 * Remove - ownership is removed from the parent (& the parent will lose all references to the value).
 *
 * NOTE: Any unspecified behaviours listed are not an exhaustive list (and do not necessarily appear as a NOTE but will be attempted to be documented as such).
 * Any usage of the API that isn't explicitly documented, or is marked as simply the current implementation of unspecified behaviour,
 * is considered unspecified and suceptible to breakage at any time.  If a particular unspecified behaviour is necessary, please contact the maintainer to 
 * update the documentation & change the API if appropriate.  Unspecified behaviour may result in crashes or incorrect program behaviour.
 *
 * NOTE: It is unspecified the actual value that a reference to a JSON null value will have (it is possible for it to be different from a C NULL & it is in the current implementation).
 *       The only guarantee is that jis_null will properly tell you if the value is a reference to a JSON null value or not.
 *
 * NOTE: It is unspecified the behaviour of the DOM inspection/modification functions if a NULL pointer
 *       or a JSON null reference is passed as the DOM node.
 *
 * NOTE: Unspecified behaviour results from passing in a C-NULL instead of the result from jnull() in to the API that is expecting a jvalue_ref.  In the current implementation it might be
 *       safe sometimes to do so.
 *
 * NOTE: It is unspecified what happens if the string pointer is null or the length is 0 when a raw_buffer is used
 *       to retrieve parameters from an object.  It is unspecified what happens is jis_null returns true for a jvalue_ref
 *       used as the key to lookup within an object.
 *
 * If a parameter to a function is marked as NON_NULL, then the behaviour is undefined if NULL is passed in
 * (with a release binary, it is likely to crash).  It is the callers responsibility to ensure that NULL is checked for.
 */

/*** Generic JSON Value operations ***/
/**
 * Return a reference to a JSON value that contains the same information as val, but ownership
 * is residing with the caller.
 *
 * NOTE: It is unspecified whether or not further modifications on val affect the copy.  Currently they do (reference counting implementation as opposed to COW)
 * NOTE: It is recommended to not call this API on the result of jnull() or jstring_empty(), although it is safe (effectively a NO-OP).
 *       Behaviour however is unspecified if there is an imbalance in jvalue_copy & j_release.
 */
PJSON_API jvalue_ref jvalue_copy(jvalue_ref val) NON_NULL(1);

/**
 * Release ownership from *val.  *val has an undefined value afterwards.  It is an error
 * to call this on references for which ownership does not preside with the caller
 * (i.e. only call when there was a _create or _copy call was made without a corresponding put, append, or release)
 *
 * It is safe to call this as many times as you want on jnull(), jstring_empty(), or NULL.
 *
 * @param val A pointer to a value reference to release ownership for.  In DEBUG mode, the reference is changed to some garbage value afterwards.
 */
PJSON_API void j_release(jvalue_ref *val);

/**
 * Return a reference to a value representing a JSON null.  It is redundant (but not illegal) to copy
 * or release ownership on this reference since the implementation must guarantee that this reference has static
 * program scope.
 *
 * NOTE: Do not use this to test for whether or not a 
 */
PJSON_API jvalue_ref jnull() PURE_FUNC;

/**
 * Lets the caller determine whether or not the reference is 
 * @param val A reference to a JSON value
 * @return true if val is a reference to a JSON null value.  false otherwise
 */
PJSON_API bool jis_null(jvalue_ref val);

/**
 * Equivalent to JSON.stringify within Javascript.  Converts the JSON value to it's equivalent
 * string representation that is ready to be transferred across the wire (with all appropriate escaping and quoting performed).
 * The c-string returned has a lifetime equivalent at least to the lifetime of the reference provided.
 * It is unspecified as to whether or not it is also tied to the lifetime of any copies of the reference.
 *
 * @param val A reference to the JSON object to convert to a string.
 * @param schema The schema to validate against when converting to a string
 * @return The string representation of the value with a lifetime equivalent to the value reference. NULL if there is an error of any
 *         kind (e.g. schema validation failed)
 *
 * NOTE: FOR THE IMPLEMENTOR - even if it is possible to extend the lifetime, it's not necessarily smart if COW is used since a write
 * might cause weirdness conceptually with the lifetime of the buffer if the parent already had its ownership released (best not to encourage
 * such API usage).
 */
PJSON_API const char *jvalue_tostring(jvalue_ref val, const jschema_ref schema) NON_NULL(1, 2);

/*** JSON Object operations ***/
/**
 * Create an empty JSON object node.
 */
PJSON_API jvalue_ref jobject_create();

/**
 * Create a JSON object node initialized with a variable number of items.
 *
 * The last jobject_key_value item must have a NULL key pointer (an actual C NULL, not JSON null).  If the value
 * isn't also NULL, behaviour is undefined (use J_END_OBJ_DECL).
 *
 * NOTE: If item.key isn't a valid JSON string or NULL pointer, then a JSON null is returned.
 *
 * @param item A key value pair
 * @param ... The remaining jobject_key_value items.
 *
 * @return A JSON Object with the specified key-value pairs or a value for which jis_null returns true.
 *
 * @see jobject_put
 * @see J_END_OBJ_DECL
 */
PJSON_API jvalue_ref jobject_create_var(jobject_key_value item, ...);
#define J_END_OBJ_DECL ((jobject_key_value) {NULL, NULL})

/**
 * Create an empty JSON object node that is prepared to contain the requested number of
 * key-value pairs.
 */
PJSON_API jvalue_ref jobject_create_hint(int capacityHint);
/**
 * Returns whether or not this JSON value reference is an object or not.
 * @param val The reference to test
 * @return True if val represents an object, false otherwise
 */
PJSON_API bool jis_object(jvalue_ref val);

/**
 * Grab a reference to a JSON value within the parent object that has the specified key.
 *
 * @param obj The reference to the parent object to retrieve the value from
 * @param key The name of the key in the JSON object to retrieve the value for.
 * @param value A pointer to a JSON value reference which will contain the result.
 *              It is safe for this to be NULL.
 *
 * @return True if key is present within object, false if it is not or obj is not a valid object.
 *         NOTE: It is unspecified what *value is set to if this returns false.
 *
 * @see jobject_get
 */
PJSON_API bool jobject_get_exists(jvalue_ref obj, raw_buffer key, jvalue_ref *value);

/**
 * Alternate method to determine whether or not the object contains a key.
 *
 * This allows retrieval using a JSON value instead of a simple string buffer.
 *
 * @param obj
 * @param key
 * @param value
 * @return
 *
 * @see jobject_get_exists
 * @see jobject_containskey2
 */
PJSON_API bool jobject_get_exists2(jvalue_ref obj, jvalue_ref key, jvalue_ref *value);

/**
 * Convenience method to determine whether or not the object contains a key.
 *
 * @param obj
 * @param key
 * @return True if and only if this is an object & it has a key/value pair matching this key.
 */
static inline bool jobject_containskey(jvalue_ref obj, raw_buffer key)
{
	return jobject_get_exists(obj, key, NULL);
}

/**
 * Alternate convenience method to determine whether or not the object contains a key.
 *
 * @param obj
 * @param key
 * @return
 *
 * @see jobject_containskey
 * @see jobject_get_exists2
 */
static inline bool jobject_containskey2(jvalue_ref obj, jvalue_ref key)
{
	return jobject_get_exists2(obj, key, NULL);
}

/**
 * Grab a reference to a JSON value within the parent object that has the specified key.
 * Ownership remains with obj.
 *
 * Convenience wrapper if you don't care to distinguish between the key not being present, and it containing
 * a null.
 *
 * @param obj The reference to the parent object to retrieve the value from
 * @param key The name of the key in the JSON object to retrieve the value for
 *
 * @return A reference to the JSON value associated with key under obj or a JSON null
 *
 * @see jobject_get_exists
 */
PJSON_API jvalue_ref jobject_get(jvalue_ref obj, raw_buffer key);

/**
 * Remove any key/value association in the object with the specified key value.
 * 
 * @param key The key to use
 * @param obj The reference to the parent object.
 * @return True if there was an association under key.  False if there was not or obj was not an object.
 */
PJSON_API bool jobject_remove(jvalue_ref obj, raw_buffer key);

/**
 * Associate val with key in object obj.  The object associates a copy of val.
 * 
 * NOTE: It is unspecified whether or not changes to val after being set are reflected in the structure under obj.
 * NOTE: The RFC specifes behaviour is unspecified if key is already present within the object.  The implementation 
 *       behaviour is that existing key/value pairs are replaced (insert/replace semantics).
 * 
 * @param obj The JSON object to insert into
 * @param key The key to use for the association
 * @param val The reference to a JSON object containing the value to associate with key
 * @return True if the association was made, false otherwise.  Failure may occur for any number of reasons
 * (e.g. key is already present in the object, failure to allocate memory, etc)
 */
PJSON_API bool jobject_set(jvalue_ref obj, raw_buffer key, jvalue_ref val);

/**
 * Associate val with key in object obj.  The object takes over ownership of val.  It is an error to call this
 * if you do not have ownership of val to begin with.
 *
 * NOTE: Behaviour of library is undefined when changes to key or val occur after transferring ownership to obj
 * NOTE: The RFC specifes behaviour is unspecified if key is already present within the object.  The implementation 
 *       behaviour is that existing key/value pairs are replaced (insert/replace semantics).
 *
 * @param obj The JSON object to insert into
 * @param key The key to use for the association.  Ownership transfers to the object
 *            NOTE: Behaviour is undefined if key is not a valid JSON string
 * @param val The reference to the JSON object to associate with the key
 *            NOTE: Behaviour is undefined if val is a NULL pointer.
 * @return True if the association was made, false otherwise.  Failure may occur for any number of reasons
 * (e.g. key is already present in the object, failure to allocate memory, etc)
 */
PJSON_API bool jobject_put(jvalue_ref obj, jvalue_ref key, jvalue_ref val);

// JSON Object iterators
/**
 * Create an iterator for the object.  The iterator is allocated on the stack & will be automatically
 * cleaned
 * 
 * NOTE: It is assumed that ownership of obj is maintained for the lifetime of the iterator by the caller.
 * NOTE: Behaviour is undefined if the ownership is released while an iterator still exists.
 * NOTE: Behaviour is undefined if the object changes while iterating over it.
 *
 * @param obj The JSON object to iterate over
 * @return The iterator pointing to the first element of the object.
 */
PJSON_API jobject_iter jobj_iter_init(const jvalue_ref obj);

/**
 * Returns the iterator that comes after this one.
 * 
 * NOTE: Behaviour is unspecified if the iterator has not been initialized.
 * NOTE: Unspecified API use is logged if possible.
 *
 * @param i The iterator to use
 * @return "i + 1" - the structure pointing to the next key-value pair in the object.
 */
PJSON_API jobject_iter jobj_iter_next(const jobject_iter i);

/**
 * !!EXPERIMENTAL!!
 *
 * Deletes the key/value pair pointed to by this iterator.  This calls j_release
 * on the key and value.
 *
 * NOTE: Behaviour is unspecified if the iterator is not valid.
 *
 * @param i A valid iterator
 * @return The next key/value pair (or an invalid iterator if there is none).
 */
PJSON_API jobject_iter jobj_iter_remove(jobject_iter i);

/**
 * Determine whether or not the iterator points to a valid key-value.
 *
 * @param i A pointer to the object iterator to check the validity of
 * @return True if this still points to a key/value pair within the iteration of the object this iterator is for.
 *         False if the iterator has not been initialized or the end of the iteration has been reached.
 */
PJSON_API bool jobj_iter_is_valid(const jobject_iter i);

/**
 * NOTE: Behaviour is unspecified if the iterator has not been initialized or value is not a valid pointer.
 * NOTE: If any invalid parameters are provided that hit the error conditions below or unspecified use of the API
 *       is used, then this is logged if possible.
 * NOTE: It is unspecified what values this structure will have if this function returns false.
 *
 * @param i A pointer to the object iterator to get the key/value pair for
 * @param value A pointer to the key-value pair structure to fill in.
 * @return True if the key/value pair was retrieved, false otherwise.
 */
PJSON_API bool jobj_iter_deref(const jobject_iter i, jobject_key_value *value) NON_NULL(2);

/**
 * Determines if i1 & i2 point to the same key/value pair in the object.
 *
 * NOTE: Result is unspecified if both iterators are invalid.
 *
 * @param i1 The first iterator to compare
 * @param i2 The second iterator to compare
 * @return True if and only if i1 & i2 point to the same key/value pair.  If both are invalid,
 *         it is unspecified what the return value is (even if both of them are iterating over the same
 *         object).
 *
 * @see jobj_iter_is_valid
 */
PJSON_API bool jobj_iter_equal(const jobject_iter i1, const jobject_iter i2);

/*** JSON Array operations ***/
/**
 * Create an empty array with the specified properties.
 *
 * @param opts The options for the array (currently unspecified).  NULL indicates use default options.
 * @return A reference to the created array value.  The caller has ownership.
 */
PJSON_API jvalue_ref jarray_create(jarray_opts opts);

/**
 * Creates an array initialized with num_elements.  If num_elements > actual provided list,
 * the remaining spots are initialized with null.  If num_elements < actual provided list, the first num_elements are used.
 * In either case, the mismatch is logged.
 *
 * @param opts The options for the array (currently unspecified).  NULL indicates use default options.
 * @param ... A variadic list num_elements long of JSON value references (jvalue_ref).  This is equivalent to calling jarray_create
 *     and then passing each reference through a jarray_put.  The last object must be a NULL pointer (not a JSON null -
 *     those are inserted into the array as elements)
 *
 * @return A reference to the created array value.  The caller has ownership.
 */
PJSON_API jvalue_ref jarray_create_var(jarray_opts opts, ...);
#define J_END_ARRAY_DECL NULL

/**
 * Create an empty array with the specified properties and the hint that the array will eventually contain capacityHint elements.
 *
 * @param opts The options for the array (currently unspecified).  NULL indicates use default options.
 * @param capacityHint A guess-timate of the eventual size of the array (implementation is free to ignore this).
 * @return A reference to the created array value.  The caller has ownership.
 */
PJSON_API jvalue_ref jarray_create_hint(jarray_opts opts, size_t capacityHint);

/**
 * Determine whether or not the reference to the JSON value represents an array.
 *
 * @param val The reference to test
 * @return True if it is an array, false otherwise.
 */
PJSON_API bool jis_array(jvalue_ref val);

/**
 * Returns the array size of the array with the given reference.
 *
 * @param arr The reference to the array
 * @return The number of elements in the array or -1 if this is not an array or there is some other problem.
 */
PJSON_API ssize_t jarray_size(jvalue_ref arr) NON_NULL(1);

/**
 * Grab the reference to the index'th element of the array.
 *
 * NOTE: A JSON null is returned if obj is not an array or index is out of bounds.
 *
 * @param arr The reference to the array
 * @param index The element number in the array to retrieve.
 * @return A reference to the value.  Ownership of this value remains with the parent array.  jis_null will return true on the
 * result if the index'th element is null or invalid parameters are provided.
 */
PJSON_API jvalue_ref jarray_get(jvalue_ref arr, ssize_t index) NON_NULL(1);

/**
 * All elements at position above index have their positions decremented by 1.
 *
 * NOTE: It is unspecified what happens if an invalid index is passed.  Currently this will result in a log message being recorded
 *
 * @param arr The reference to the array
 * @param index The element to remove
 * @return True if the element was removed, false if arr is not an array, index is out of bounds, or some problem
 * occured in the removal.
 */
PJSON_API bool jarray_remove(jvalue_ref arr, ssize_t index) NON_NULL(1);

/**
 * Set the index'th element of arr to val. Ownership of val is not transferred (must be released manually).  The array will
 * contain a copy of the new element.  Any element already at position index gets overwritten.
 *
 * Arrays can be implicitly resized by setting an index greater than the size of the array.
 *
 * NOTE: It is unspecified behaviour to modify val after passing it to this array.
 *
 * @param arr The array to add an element to
 * @param index The element to change to val.  If index is out of bounds of the current size (e.g. setting element 10 of a 0-length array), the
 *              indicies in between are initialized with null.
 * @param val The element of the array
 * @return True if the element was successfully set, false otherwise.
 * @see jarray_put
 */
PJSON_API bool jarray_set(jvalue_ref arr, ssize_t index, jvalue_ref val) NON_NULL(1);

/**
 * Set the index'th element of arr to val. Ownership of val is transferred to arr.
 *
 * Sparse arrays can be implicitly created by setting an index greater than the size of the array.
 *
 * NOTE: It is unspecified behaviour to modify val after passing it to this array.
 *
 * @param arr The array to add an element to
 * @param index The element to change to val
 * @param val Reference to the value to put into the array
 * @return True if the element was successfully changed, false otherwise.
 * @see jarray_set
 */
PJSON_API bool jarray_put(jvalue_ref arr, ssize_t index, jvalue_ref val) NON_NULL(1, 3);

/**
 * Insert the value into the array before the specified position.
 *
 * arr[index] now contains val, with all elements shifted appropriately.
 *
 * NOTE: It is unspecified behaviour to modify val after passing it to this array
 *
 * @param arr
 * @param index
 * @param val
 *
 * @see jarray_append
 * @see jarray_put
 */
PJSON_API bool jarray_insert(jvalue_ref arr, ssize_t index, jvalue_ref val) NON_NULL(1, 3);

/**
 * Convenience method that is equivalent to
 * <code>jarray_put(arr, jarray_size(), val)</code>
 * @return True if the value was successfully appended, false otherwise.
 * @see jarray_put
 * @see jarray_set
 */
PJSON_API bool jarray_append(jvalue_ref arr, jvalue_ref val) NON_NULL(1, 2);

/**
 * Similar syntax to the Javascript splice.  Remove the specified number of elements from the given index, & then insert the array subset there.
 * Additional ownership of the copied elements is not retained.
 *
 * @param array1 The array to insert into/remove from
 * @param index The index of array1 to make modifications to
 * @param toRemove The number of elements to remove prior to insertion
 * @param array2 The array to insert from
 * @param begin The beginning index in array2 to start insertion from
 * @param end The final index (exclusive) in array2 to end insertion at (jarray_size(array2) represents the last element).
 * @param ownership What to do with the elements going from array2 into array1.  You can transfer ownership (meaning the element is then owned
 *                  by array1) or copy (meaning a copy of the element is used to insert into array1 when splicing, but array2 retains ownership as well)
 *
 * @see jarray_splice_inject
 * @see jarray_splice_append
 */
PJSON_API bool jarray_splice(jvalue_ref array1, ssize_t index, ssize_t toRemove, jvalue_ref array2, ssize_t begin, ssize_t end, JSpliceOwnership ownership) NON_NULL(1, 4);

/**
 * Simpler wrapper to insert all elements from the second array into the first at the given position.
 * Additional ownership of the copied elements is not retained.
 *
 * @param array1 The array to insert into
 * @param index The position to insert into (e.g. jarray_size(array) to append to array1)
 * @param array2 The array to insert from
 * @param ownership What to do with the elements going from array2 into array1.  You can transfer ownership or copy.
 *
 * @see jarray_splice
 * @see jarray_splice_append
 */
PJSON_API bool jarray_splice_inject(jvalue_ref array1, ssize_t index, jvalue_ref array2, JSpliceOwnership ownership) NON_NULL(1, 3);

/**
 * Append all the contents of array2 to array1.
 * Additional ownership of the copied elements is not retained.
 *
 * @param array1 The array to insert into
 * @param array2 The array to copy from
 * @param ownership What to do with the elements going from array2 into array1.  You can transfer ownership or copy.
 *
 * @see jarray_splice
 * @see jarray_splice_inject
 */
PJSON_API bool jarray_splice_append(jvalue_ref array1, jvalue_ref array2, JSpliceOwnership ownership) NON_NULL(1, 2);

/*** JSON String operations ***/
/**
 * Create an empty JSON string.
 *
 * @return A reference to the JSON string
 */
PJSON_API jvalue_ref jstring_empty() PURE_FUNC;

/**
 * Create a JSON string representing the Unicode-encoded string stored in the provided buffer.  Any encoding conversions are the responsibilities of the caller.
 *
 * NOTE: Enough characters are appended to the end of value in the resultant copy so that the raw backing buffer is properly null terminated regardless of the particular UTF encoding
 * (e.g. UTF-8, UTF-16, UTF-32).
 *
 * NOTE: The string need not be NULL-terminated since the length parameter has to have a valid value.
 *
 * @param toCopy The buffer to copy from.  It must be in some kind of Unicode (UTF-8, UTF-16 or UTF-32 as per the JSON RFC).
 * @return A reference to the JSON string
 *
 * @see jstring_get_fast
 */
PJSON_API jvalue_ref jstring_create_copy(raw_buffer toCopy);

/**
 * Determine whether or not the JSON value is a string
 *
 * @return True if this is a reference to a JSON value that is a string, false otherwise.
 */
PJSON_API bool jis_string(jvalue_ref str) NON_NULL(1);

/**
 * Create this JSON string so that it contains the same string (this will make a copy of the string).
 * If you are using constant strings (or strings that outlive the life of the top-level JSON value) you probably want jstring_create_fast.
 * This will potentially determine the size of the string using something like strlen, so if this is unsafe, then use one of the other string APIs.
 *
 * This does guarantee however that any JSON strings created using this API will have a backing buffer that will NULL-terminate
 * any Unicode input, even if it is malformed (currently this means that 7 '\\0' bytes are appended to handled the worst case of malformed
 * UTF-32).
 *
 * This is likely implemented as a convenience wrapper for jstring_create_utf8
 *
 * @param cstring A null-terminated c-string.
 *                NOTE: Undefined behaviour if this is a null pointer or the string is encoded with something that isn't UTF-8 compatible (e.g. UTF-16, UTF-32, UCS2, etc).
 *
 * @return A reference to the JSON string
 *
 * @see jstring_create_utf8
 * @see jstring_create_copy
 */
PJSON_API jvalue_ref jstring_create(const char* cstring);

/**
 * Create this JSON string to that it contains the same string (this will make a copy of the string).
 * This does guarantee however that any JSON strings created using this API will have a backing buffer that will NULL-terminate
 * any Unicode input, even if it is malformed (currently this means that 7 '\\0' bytes are appended to handled the worst case of malformed
 * UTF-32).
 *
 * Equivalent to jstring_create except safer in case you choose to change the encoding later on (you are responsible for determining
 * the length of the string).
 *
 * This is likely implemented as a convenience wrapper for jstring_create_copy
 *
 * @param string An arbitrary Unicode string.
 * @param length The number of bytes in the string.
 *
 * NOTE: Behaviour is undefined if you mix Unicode encodings together within an object/array.
 *
 * @see jstring_create
 * @see jstring_create_copy
 */
PJSON_API jvalue_ref jstring_create_utf8(const char *string, ssize_t length);

/**
 * Convenience method to create an empty JSON string
 *
 * @return A reference to the JSON string
 */
PJSON_API jvalue_ref jstring_empty();

/**
 * Convenience wrapper for jstring_create_full.  Equivalent to
 * <code>
 * jstring_create_full(val, NULL);
 * </code>
 *
 * Typical usage might be
 * <code>
 * jstring_create_fast(PJ_STR("abc"))
 * </code>
 *
 * @param val
 * @return
 *
 * @see jstring_create_full
 */
PJSON_API jvalue_ref jstring_create_nocopy(raw_buffer val);

/**
 * Transfer ownership of the provided buffer to the provided JSON string reference (JSON string with raw backing buffer).
 * The buffer is deallocated using the provided deallocator once the library is done with it.
 * Any previous buffers in this reference are freed.
 *
 * NOTE: It is unspecified whether references to JSON strings that are copies of JSON strings with raw backing buffers make copies
 * or simply maintain a COW reference to the raw backing buffer.
 *
 * @param val The UTF string (specific encoding is unimportant) to set.  Cannot be a value on the stack unless it outlives
 *              the lifetime of the created object.
 *              NOTE: Undefined behaviour if val.m_str is NULL
 * @param buffer_dealloc The deallocator to use on the provided string after it is no longer needed.  If NULL, then
 *                       the string is never de-allocated (potential memory leak if it was dynamically allocated).  Use NULL
 *                       if value is on the stack or a compile-time constant or you are managing it yourself.
 * @return A reference to the JSON string
 *
 * @see DECLARE_KEY
 * @see DECLARE_KEY_SAFE_AND_FAST
 */
PJSON_API jvalue_ref jstring_create_nocopy_full(raw_buffer val, jdeallocator buffer_dealloc);

/**
 * Return the number of bytes in the buffer backing the JSON string.  Convenience method.
 * Equivalent to jstring_get(str).m_len
 *
 * @param str The JSON string reference to examine
 * @return The number of bytes in the buffer backing this string (including any terminating NULLs).
 * NOTE: A negative return value represents some unspecified error (should never happen - just for assert purposes to catch overflows).
 */
PJSON_API ssize_t jstring_size(jvalue_ref str) NON_NULL(1);

/**
 * Get the C-string buffer representation for this JSON string.
 *
 * The caller is responsible for freeing the returned buffer.
 *
 * NOTE: if this is not a string, then NULL is assigned to the m_str value & m_len is undefined.
 *
 * @param str The JSON string reference
 * @return A C-String (null-terminated) copy of the backing buffer of this JSON string.
 *         This assumes the backing buffer is UTF-8.
 * @see jstring_free_buffer
 * NOTE: result.m_str is NULL & m_len is undefined if this was not a string or we failed to allocate space.
 */
PJSON_API raw_buffer jstring_get(jvalue_ref str) NON_NULL(1);

/**
 * Frees a string allocated by jstring_get().  Equivalent to manually
 * calling free() on the m_str member of raw_buffer.
 *
 * @param str The string allocated by jstring_get()
 * @see jstring_get()
 */
static inline void jstring_free_buffer(raw_buffer str)
{
	free((void *)str.m_str);
}

/**
 * Get the backing buffer for this JSON string.
 *
 * NOTE: if this is not a string, then NULL is assigned to the m_str value & m_len is undefined.
 *
 * @param str The JSON string reference
 * @return The backing buffer of this JSON string (may not be NULL-terminated).
 * NOTE: result.m_str is NULL & m_len is undefined if this was not a string.
 */
PJSON_API raw_buffer jstring_get_fast(jvalue_ref str) NON_NULL(1);

/**
 * Determines whether or not this JSON string matches another JSON string
 *
 * @param str
 * @param other
 * @return True if and only if both are valid strings & are textually the same.
 */
PJSON_API bool jstring_equal(jvalue_ref str, jvalue_ref other);

/**
 * Determines whether or not this JSON string matches a raw string
 *
 * @param str The JSON string to compare with
 * @param other The raw string to compare with
 * @return True if and only str is actually a JSON string & matches exactly the other string (ending null-terminator is optional - the length must be accurate and not including
 *           the terminating null)
 * @see DECLARE_KEY
 * @see DECLARE_KEY_SAFE_AND_FAST
 */
PJSON_API bool jstring_equal2(jvalue_ref str, raw_buffer other);

/**
 * Creates a JSON number that uses this decimal string-representation as the backing value.
 * This is safe, as compared with jnumber_create_unsafe, in that the string buffer can be modified or freed after this call
 * (the reference will maintain it's own distinct copy)
 *
 * @param raw The string buffer to use.  Need not be null-terminated.
 * @return The JSON number reference
 *
 * @see jnumber_create_unsafe
 */
PJSON_API jvalue_ref jnumber_create(raw_buffer raw);

/**
 * Like jnumber_create except the provided buffer is used directly.  It may not be freed or modified
 * unless there are no ways that this object or any copies could possibly access this buffer - this generally means
 * that all copies have their ownership released or no attempt is made to inspect this DOM node (converting this or any parent
 * JSON node into a string has the side-effect of causing inspection)
 *
 * @param raw The buffer to use.  Need not be null-terminated.  Must be immutable for the lifetime of all copies of
 *               the created JSON reference.
 * @param strFree The deallocator to use on the string (if any) after this JSON object is freed (e.g. if you dynamically allocated
 *                the string and want this library to take care of automatically deallocating it).
 * @return The JSON number reference
 * @see jnumber_create
 */
PJSON_API jvalue_ref jnumber_create_unsafe(raw_buffer raw, jdeallocator strFree);

/*** JSON Number operations ***/
/**
 * Create a JSON reference to a value representing the requested number.
 *
 * @param number The number to use when initializing this JSON number.
 * @return A reference to a JSON number representing the requested value.
 *         NOTE: It is considered an error to try to create a reference to a NaN or +/- infinity value.  A null JSON reference will be returned in this case.
 *         NOTE: It is unspecified what happens if you try to use features of floating point such as subnormal numbers or -0.
 */
PJSON_API jvalue_ref jnumber_create_f64(double number);
/**
 * Create a JSON reference to a value representing the requested number.
 *
 * @return A reference to a JSON number representing the requested value.
 */
PJSON_API jvalue_ref jnumber_create_i32(int32_t number);
/**
 * Create a JSON reference to a value representing the requested number.
 * 
 * @param number The number the JSON value should represent
 * @return A reference to a JSON number representing the requested value.
 */
PJSON_API jvalue_ref jnumber_create_i64(int64_t number);

/**
 * Converts the string representation of the number into a DOM wrapper.
 * This actually stores the converted value of raw - if raw can be represented
 * as a 64-bit integer, than that is done - otherwise a double is used.
 *
 * NOTE: Behaviour is undefined if the raw value cannot be represented as a 64-bit integer
 *       or a double floating point number.
 *
 * @param raw
 * @return
 *
 * @see jnumber_create_i64
 * @see jnumber_create_f64
 */
PJSON_API jvalue_ref jnumber_create_converted(raw_buffer raw);

/**
 * Compare this number against another JSON number.
 *
 * @param number Must be a JSON number.
 * 				 NOTE: Behaviour is undefined if jis_number returns false
 *               NOTE: Behaviour is undefined if this number cannot convert without error to a 64-bit
 *       			   integer or a double floating point number.
 * @param toCompare The number to compare against.
 * 				 NOTE: Behaviour is undefined if jis_number returns false
 *               NOTE: Behaviour is undefined if this number cannot convert without error to a 64-bit
 *       			   integer or a double floating point number.
 * @return 1, 0, -1 if the JSON number is greater, equal to, less than the number to compareTo
 *         respectively.
 */
PJSON_API int jnumber_compare(jvalue_ref number, jvalue_ref toCompare) NON_NULL(1, 2);

/**
 * Compare this number against an integer.
 *
 * @param number Must be a JSON number.
 * 				 NOTE: Behaviour is undefined if jis_number returns false
 *               NOTE: Behaviour is undefined if this number cannot convert without error to a 64-bit
 *       			   integer or a double floating point number.
 * @param toCompare The number to compare against.
 * @return 1, 0, -1 if the JSON number is greater, equal to, less than the number to compareTo
 *         respectively.
 */
PJSON_API int jnumber_compare_i64(jvalue_ref number, int64_t toCompare) NON_NULL(1);

/**
 * Compare this number against a floating point number.
 *
 * @param number Must be a JSON number.
 * 				 NOTE: Behaviour is undefined if jis_number returns false
 *               NOTE: Behaviour is undefined if this number cannot convert without error to a 64-bit
 *       			   integer or a double floating point number.
 * @param toCompare The number to compare against.
 * @return 1, 0, -1 if the JSON number is greater, equal to, less than the number to compareTo
 *         respectively.
 */
PJSON_API int jnumber_compare_f64(jvalue_ref number, double toCompare) NON_NULL(1);

/**
 * Determines whether or not the JSON value is an actual number type.
 *
 * @param num The reference to the JSON value
 * @return True if num is some numeric type, false otherwise.
 */
PJSON_API bool jis_number(jvalue_ref num) NON_NULL(1);

/**
 * Determines whether or not this is a reference to a JSON number that internally has some kind of error code
 * set.
 *
 * @return True if there is some kind of error storing this number (i.e. not enough precision in the storage used, NaN or +/- infinity, etc).
 */
PJSON_API bool jnumber_has_error(jvalue_ref number) NON_NULL(1);

/**
 * Retrieve the JSON number as a native numeric integer.  The goal is to get number to represent the number
 * closest to the underlying storage type (which may be a raw string, a double, 64-bit integer, etc).
 *
 * The following return codes list the precise relationship if the 32-bit integer cannot accurately represent
 * the value in the underlying storage.
 *
 * CONV_OK --> the underlying storage can be correctly represented using a 32-bit signed integer (number contains an accurate value)
 *
 * CONV_POSITIVE_OVERFLOW --> the underlying storage contains a positive number outside what can be represented by a 32-bit signed integer
 *     number is set to the largest positive 32-bit signed integer
 * CONV_NEGATIVE_OVERFLOW --> CONV_POSITIVE_OVERFLOW except for negative numbers
 *     number is set to the largest negative 32-bit signed integer
 * CONV_OVERFLOW --> set if there is either a positive or negative overflow - binary OR of the two more specific return codes
 *     number is clamped to the value closest to the actual number
 *
 * CONV_POSITIVE_INFINITY --> the underlying storage is representing a +infinity
 *     number is set to the largest positive 32-bit signed integer
 * CONV_NEGATIVE_INFINITY --> CONV_POSITIVE_INFINITY except negative
 *     number is set to the smallest positive 32-bit signed integer
 * CONV_INFINITY --> set if there is either a positive or negative infinity - binary OR of the two more specific return codes
 *     number is clamped to the largest possible value closest to the infinity
 *
 * CONV_PRECISION_LOSS --> set if the underlying value is a floating point value with a non-0 floating-point portion that gets truncated
 *     number is the underlying value +/- 1.  It is unspecified whether truncation or rounding occurs.  Also set if the floating point
 *           contains a value that might have truncated the native integer type (e.g. for single floating point, a normal number not in [-2^24, 2^24]).
 *
 * CONV_NOT_A_NUM --> the underlying storage doesn't actually represent a number (or NaN somehow got into the floating point representation).
 *     number is set to 0
 *
 * CONV_BAD_ARGS --> num is an invalid JSON number reference or number is NULL.
 *     unspecified what value number will have
 *
 * CONV_GENERIC_ERROR --> some other conversion error occured (please contact the maintainer)
 *     unspecified what value number will have
 *
 * @param num The reference to the JSON number
 * @param number The pointer to where to write the value to
 * @return The conversion result of converting this JSON number value to a 32-bit signed integer.  CONV_OK (0) if
 *         there are no problems, otherwise there was a conversion error (binary OR of all the error bits).  In the error case,
 *         recommended to use the CONV_HAS or CONV_IS convenience macros.
 */
PJSON_API ConversionResultFlags jnumber_get_i32(jvalue_ref num, int32_t *number) NON_NULL(1, 2);

/**
 * Retrieve the JSON number as a native numeric integer.  The goal is to get number to represent the number
 * closest to the underlying storage type (which may be a raw string, a double, 32-bit integer, etc).
 *
 * The following return codes list the precise relationship if the 64-bit integer cannot accurately represent
 * the value in the underlying storage.
 *
 * CONV_OK --> the underlying storage can be correctly represented using a 64-bit signed integer (number contains an accurate value)
 *
 * CONV_POSITIVE_OVERFLOW --> the underlying storage contains a positive number outside what can be represented by a 64-bit signed integer
 *     number is set to the largest positive 64-bit signed integer
 * CONV_NEGATIVE_OVERFLOW --> CONV_POSITIVE_OVERFLOW except for negative numbers
 *     number is set to the largest negative 64-bit signed integer
 * CONV_OVERFLOW --> set if there is either a positive or negative overflow - binary OR of the two more specific return codes
 *     number is clamped to the value closest to the actual number
 *
 * CONV_POSITIVE_INFINITY --> the underlying storage is representing a +infinity
 *     number is set to the largest positive 64-bit signed integer
 * CONV_NEGATIVE_INFINITY --> CONV_POSITIVE_INFINITY except negative
 *     number is set to the smallest positive 64-bit signed integer
 * CONV_INFINITY --> set if there is either a positive or negative infinity - binary OR of the two more specific return codes
 *     number is clamped to the largest possible value closest to the infinity
 *
 * CONV_PRECISION_LOSS --> set if the underlying value is a floating point value with a non-0 floating-point portion that gets truncated
 *     number is the underlying value +/- 1.  It is unspecified whether truncation or rounding occurs.  Also set if the floating point
 *           contains a value that might have truncated the native integer type (e.g. for double floating point, a normal number not in [-2^53, 2^53]).
 *
 * CONV_NOT_A_NUM --> the underlying storage doesn't actually represent a number (or NaN somehow got into the floating point representation).
 *     number is set to 0
 *
 * CONV_BAD_ARGS --> num is an invalid JSON number reference or number is NULL.
 *     unspecified what value number will have
 *
 * CONV_GENERIC_ERROR --> some other conversion error occured (please contact the maintainer)
 *     unspecified what value number will have
 *
 * @param num The reference to the JSON number
 * @param number The pointer to where to write the value to
 * @return The conversion result of converting this JSON number value to a 64-bit signed integer.  CONV_OK (0) if
 *         there are no problems, otherwise there was a conversion error (binary OR of all the error bits).  In the error case,
 *         recommended to use the CONV_HAS or CONV_IS convenience macros.
 */
PJSON_API ConversionResultFlags jnumber_get_i64(jvalue_ref num, int64_t *number) NON_NULL(1, 2);

/**
 * Retrieve the JSON number as a native floating point value.  The goal is to get number to represent the number
 * closest to the underlying storage type (which may be a raw string, a double, 32-bit integer, etc).
 *
 * The following return codes list the precise relationship if the double floating point cannot accurately represent
 * the value in the underlying storage.  Multiple error codes may be set in the return code.
 *
 * CONV_OK --> the underlying storage can be correctly represented using a 64-bit signed integer (number contains an accurate value)
 *
 * CONV_POSITIVE_OVERFLOW --> the underlying storage contains a positive number outside what can be represented by a 64-bit signed integer
 *     number is set to the largest positive 64-bit signed integer
 * CONV_NEGATIVE_OVERFLOW --> CONV_POSITIVE_OVERFLOW except for negative numbers
 *     number is set to the largest negative 64-bit signed integer
 * CONV_OVERFLOW --> set if there is either a positive or negative overflow - binary OR of the two more specific return codes
 *     number is clamped to the value closest to the actual number
 *
 * CONV_POSITIVE_INFINITY --> the underlying storage is representing a +infinity
 *     number is set to the largest positive 64-bit signed integer
 * CONV_NEGATIVE_INFINITY --> CONV_POSITIVE_INFINITY except negative
 *     number is set to the smallest positive 64-bit signed integer
 * CONV_INFINITY --> set if there is either a positive or negative infinity - binary OR of the two more specific return codes
 *     number is clamped to the largest possible value closest to the infinity
 *
 * CONV_PRECISION_LOSS --> set if the underlying value is an integer value outside of the [-2^53, 2^53 range]
 *     number is the closest value a double floating point can have to the integer value.
 *
 * CONV_NOT_A_NUM --> the underlying storage doesn't actually represent a number (or NaN somehow got into the floating point representation).
 *     number is set to 0
 *
 * CONV_BAD_ARGS --> num is an invalid JSON number reference or number is NULL.
 *     unspecified what value number will have
 *
 * CONV_GENERIC_ERROR --> some other conversion error occured (please contact the maintainer)
 *     unspecified what value number will have
 *
 * @param num The reference to the JSON number
 * @param number The pointer to where to write the value to
 * @return The conversion result of converting this JSON number value to a 64-bit signed integer.  CONV_OK (0) if
 *         there are no problems, otherwise there was a conversion error.  In the error case,
 *         recommended to use the CONV_HAS or CONV_IS convenience macros.
 */
PJSON_API ConversionResultFlags jnumber_get_f64(jvalue_ref num, double *number) NON_NULL(1, 2);

/**
 * Retrieve the raw string representation of the number.
 *
 * NOTE: Only use this API if you actually, trully, really need this for performance reasons - otherwise, it is recommended you don't
 * because it's likely this won't be what you need (usually the numeric string will not be NULL-terminated).
 *
 * @param num The reference to the JSON value.
 * @param result The pointer to the structure to fill in
 *                 NOTE: The lifetime of result->m_str is at most the lifetime of num
 *                 NOTE: This might not be a null-terminated string - use the length field as well
 *                 NOTE: It is unspecified what value this takes if there is no backing raw buffer (i.e.
 *                       the JSON number is backed using a native numeric type).  If the pointer returned is not null, then
 *                       memory was allocated for a conversion - in any case, to be safe, make sure to always free the resultant string
 *                       (malloc or calloc will have been used to create the buffer).
 * @return CONV_OK or CONV_NOT_A_RAW_NUM.
 */
PJSON_API ConversionResultFlags jnumber_get_raw(jvalue_ref num, raw_buffer *result);

/*** JSON Boolean operations ***/
PJSON_API bool jis_boolean(jvalue_ref jval) NON_NULL(1);

/**
 * Create a JSON boolean with the requested value
 *
 * @param value The value of the boolean
 * @return The reference to the boolean.
 */
PJSON_API jvalue_ref jboolean_create(bool value);

/**
 * Retrieve the native boolean representation of this reference.
 *
 * The following equivalencies are made for the various JSON types & bool:
 * NUMBERS: 0, NaN = false, everything else = true
 * STRINGS: empty = false, non-empty = true
 * NULL: false
 * ARRAY: true
 * OBJECT: true
 *
 * @param val The reference to the JSON value
 * @param value Where to write the boolean value to.
 *              NOTE: It is safe for this to be a NULL.
 * @return CONV_OK if val represents a JSON boolean type, otherwise CONV_NOT_A_BOOLEAN.
 */
PJSON_API ConversionResultFlags jboolean_get(jvalue_ref val, bool *value) NON_NULL(1);

/**
 * Convience to construct a jobject_key_value structure.
 *
 * NOTE: Undefined behaviour if the key is NULL or not a string.
 *
 * NOTE TO IMPLEMENTOR: THIS MUST HAVE HIDDEN VISIBILITY TO INSURE THERE ARE NO CONFLICTS
 *     IN THE SYMBOL TABLE. IN THEORY, static inline SHOULD SUFFICE.
 *
 * @param key
 * @param value
 * @return
 */
static inline jobject_key_value jkeyval(jvalue_ref key, jvalue_ref value)
{
	assert(key != NULL);
	assert(jis_string(key));
	return (jobject_key_value){ (key), (value) };
}

/**
 * Convenience inline function that casts the C-string constant/literal to a raw_buffer
 * structure that is used for JSON strings.
 *
 * @param cstring A valid C-string literal or constant (safest to use with literals or global constants only unless
 *                you understand what you are doing).
 * @return A raw_buffer struct containing { cstring, strlen(cstring) }
 */
static inline raw_buffer j_cstr_to_buffer(const char *cstring)
{
	return ((raw_buffer) { cstring, strlen(cstring) } );
}

/**
 * Convenience inline function that creates a JSON string from a C-string constant/literal.
 *
 * @param cstring - Must be a valid C-string with a lifetime longer than the resultant JSON value will have.
 *                 Safest to use with string literals or string constants (e.g. constant for the life of the program).
 */
static inline jvalue_ref j_cstr_to_jval(const char *cstring)
{
	return jstring_create_nocopy( j_cstr_to_buffer(cstring) );
}

/**
 * Convenience macro to declare a JSON string from an arbitrary string.
 * Generally, you probably shouldn't need to use this unless you already have the length
 * parameter or it's not a UTF-8 string or it's not null-terminated.
 *
 * @param string Can have side-effects
 * @param length Can have side-effects
 * @see DECLARE_KEY
 */
static inline raw_buffer j_str_to_buffer(const char *string, size_t length)
{
	return ((raw_buffer){ (string), (length) });
}

/**
 * Optimized version for creating a buffer from a C-string literal or char array.
 *
 * NOTE: macro is not side-effect free for parameter string
 *
 * @param string A constant string literal or char array (for which the compiler knows the size)
 *               NOTE: Do not use this with variables unless you understand the lifetime requirements for the
 *               string.
 *               NOTE: Assumes that it is equivalent to a NULL-terminated UTF-8-compatible string.
 *
 * @return A raw_buffer structure
 */
#define J_CSTR_TO_BUF(string) j_str_to_buffer(string, sizeof(string) - 1)

/**
 * Converts a C-string literal to a jvalue_ref.
 *
 * @param string Refer to J_CSTR_TO_BUF - same requirements
 * @return A JSON string reference
 *
 * @see J_CSTR_TO_BUF(string)
 * @see pj_cstr_to_jval
 */
#define J_CSTR_TO_JVAL(string) jstring_create_nocopy( j_str_to_buffer(string, sizeof(string) - 1) )

#ifdef __cplusplus
}
#endif

#endif /* JOBJECT_H_ */

