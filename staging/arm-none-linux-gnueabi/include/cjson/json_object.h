/*
 * $Id: json_object.h,v 1.12 2006/01/30 23:07:57 mclark Exp $
 *
 * Copyright (c) 2004, 2005 Metaparadigm Pte. Ltd.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See COPYING for details.
 *
 */

#ifndef _json_object_h_
#define _json_object_h_

#define JSON_OBJECT_DEF_HASH_ENTIRES 16

#include <stdbool.h>

#undef FALSE
#define FALSE ((bool)0)

#undef TRUE
#define TRUE ((bool)1)

extern char *json_number_chars;
extern char *json_hex_chars;

/* forward structure definitions */

struct printbuf;
struct lh_table;
struct array_list;
struct json_object;
struct json_object_iter;

/* supported object types */

enum json_type {
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
};

/* reference counting functions */

/**
 * Increment the reference count of json_object, thereby grabbing shared ownership of obj.
 * @param obj the json_object instance
 */
extern struct json_object* json_object_get(struct json_object *obj);

/**
 * Decrement the reference count of json_object and free if it reaches zero.  You must have ownership
 * of obj prior to doing this or you will cause an imbalance in the reference count.
 * @param obj the json_object instance
 */
extern void json_object_put(struct json_object *obj);


/**
 * Check if the json_object is of a given type
 * @param obj the json_object instance
 * @param type one of:
     json_type_boolean,
     json_type_double,
     json_type_int,
     json_type_object,
     json_type_array,
     json_type_string,
 */
extern int json_object_is_type(const struct json_object *obj, enum json_type type);

/**
 * Get the type of the json_object
 * @param obj the json_object instance
 * @returns type being one of:
     json_type_boolean,
     json_type_double,
     json_type_int,
     json_type_object,
     json_type_array,
     json_type_string,
 */
extern enum json_type json_object_get_type(const struct json_object *obj);


/** Stringify object to json format
 * @param obj the json_object instance
 * @returns a string in JSON format
 */
extern char* json_object_to_json_string(struct json_object *obj);


/* object type methods */

/** Create a new empty object with a reference count of 1.  The caller of this object
 * initially has sole ownership.  Remember, when using json_object_object_add or json_object_array_put_idx,
 * ownership will transfer to the object/array.  Call json_object_get if you want to maintain shared ownership
 * or also add this object as a child of multiple objects/arrays.  Any ownerships you acquired but did not transfer
 * must be released through json_object_put.
 *
 * @returns a json_object of type json_type_object
 */
extern struct json_object* json_object_new_object(void);

/** Get the hashtable of a json_object of type json_type_object
 * @param obj the json_object instance
 * @returns a linkhash
 */
extern struct lh_table* json_object_get_object(struct json_object *obj);

/** Add an object field to a json_object of type json_type_object
 *
 * The reference count will *not* be incremented. This is to make adding
 * fields to objects in code more compact. If you want to retain a reference
 * to an added object, independant of the lifetime of obj, you must wrap the passed object 
 * with json_object_get.
 *
 * Upon calling this, the ownership of val transfers to obj.  Thus you must make sure that you do in fact
 * have ownership over this object.  For instance, json_object_new_object will give you ownership until you transfer it,
 * whereas json_object_object_get does not.
 *
 * @param obj the json_object instance
 * @param key the object field name (a private copy will be duplicated)
 * @param val a json_object or NULL member to associate with the given field
 */
extern void json_object_object_add(struct json_object* obj, const char *key,
				   struct json_object *val);

/** Get the json_object associate with a given object field
 *
 * *No* reference counts will be changed.  There is no need to manually adjust reference counts through the
 * json_object_put/json_object_get methods unless you need to have the child (value) reference maintain a different
 * lifetime than the owning parent (obj). Ownership of the returned value is retained by obj (do not do json_object_put
 * unless you have done a json_object_get).  If you delete the value from obj (json_object_object_del) and wish to access
 * the returned reference afterwards, make sure you have first gotten shared ownership through json_object_get (& don't forget to
 * do a json_object_put or transfer ownership to prevent a memory leak).
 *
 * @param obj the json_object instance
 * @param key the object field name
 * @returns the json_object associated with the given field name
 * @deprecated Please use json_object_object_get_ex
 */
extern struct json_object* json_object_object_get(struct json_object* obj,
						  const char *key) /* __attribute__ ((deprecated)) */;

/** Get the json_object associate with a given object field.  This returns
 * true if the key is found, false in all other cases (including if obj isn't a json_type_object).
 *
 * *No* reference counts will be changed.  There is no need to manually adjust reference counts through the
 * json_object_put/json_object_get methods unless you need to have the child (value) reference maintain a different
 * lifetime than the owning parent (obj).  Ownership of value is retained by obj.
 *
 * @param obj the json_object instance
 * @param key the object field name
 * @param value a pointer where to store a reference to the json_object associated with the given field name
 *              It is safe to pass a NULL value.
 * @returns whether or not the key exists
 */
extern bool json_object_object_get_ex(struct json_object* obj,
						  const char *key,
                                                  struct json_object **value);

/** Delete the given json_object field
 *
 * The reference count will be decremented for the deleted object.  If there are no more owners of the value
 * represented by this key, then the value is freed.  Otherwise, the reference to the value will remain in
 * memory.
 *
 * @param obj the json_object instance
 * @param key the object field name
 */
extern void json_object_object_del(struct json_object* obj, char *key);

/** Iterate through all keys and values of an object
 * @param obj the json_object instance
 * @param key the local name for the char* key variable defined in the body
 * @param val the local name for the json_object* object variable defined in the body
 */
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)

# define json_object_object_foreach(obj,key,val) \
 char *key; struct json_object *val; \
 for(struct lh_entry *entry = json_object_get_object(obj)->head; ({ if(entry) { key = (char*)entry->k; val = (struct json_object*)entry->v; } ; entry; }); entry = entry->next )

#else /* ANSI C or MSC */

# define json_object_object_foreach(obj,key,val) \
 char *key; struct json_object *val; struct lh_entry *entry; \
 for(entry = json_object_get_object(obj)->head; (entry ? (key = (char*)entry->k, val = (struct json_object*)entry->v, entry) : 0); entry = entry->next)

#endif /* defined(__GNUC__) && !defined(__STRICT_ANSI__) */

/** Iterate through all keys and values of an object (ANSI C Safe)
 * @param obj the json_object instance
 * @param iter the object iterator
 */
#define json_object_object_foreachC(obj,iter) \
 for(iter.entry = json_object_get_object(obj)->head; (iter.entry ? (iter.key = (char*)iter.entry->k, iter.val = (struct json_object*)iter.entry->v, iter.entry) : 0); iter.entry = iter.entry->next)

/* Array type methods */

/** Create a new empty json_object of type json_type_array
 * @returns a json_object of type json_type_array
 */
extern struct json_object* json_object_new_array(void);

/** Get the arraylist of a json_object of type json_type_array
 * @param obj the json_object instance
 * @returns an arraylist
 */
extern struct array_list* json_object_get_array(struct json_object *obj);

/** Get the length of a json_object of type json_type_array
 * @param obj the json_object instance
 * @returns an int
 */
extern int json_object_array_length(struct json_object *obj);

/** Add an element to the end of a json_object of type json_type_array
 *
 * The reference count will *not* be incremented. This is to make adding
 * fields to objects in code more compact. If you want to retain a reference
 * to an added object you must wrap the passed object with json_object_get
 *
 * @param obj the json_object instance
 * @param val the json_object to be added
 */
extern int json_object_array_add(struct json_object *obj,
				 struct json_object *val);

/** Insert or replace an element at a specified index in an array (a json_object of type json_type_array)
 *
 * The reference count will *not* be incremented. This is to make adding
 * fields to objects in code more compact. If you want to retain a reference
 * to an added object you must wrap the passed object with json_object_get
 *
 * The reference count of a replaced object will be decremented.
 *
 * The array size will be automatically be expanded to the size of the
 * index if the index is larger than the current size.
 *
 * @param obj the json_object instance
 * @param idx the index to insert the element at
 * @param val the json_object to be added
 */
extern int json_object_array_put_idx(struct json_object *obj, int idx,
				     struct json_object *val);

/** Get the element at specificed index of the array (a json_object of type json_type_array)
 * @param obj the json_object instance
 * @param idx the index to get the element at
 * @returns the json_object at the specified index (or NULL)
 */
extern struct json_object* json_object_array_get_idx(struct json_object *obj,
						     int idx);

/* boolean type methods */

/** Create a new empty json_object of type json_type_boolean
 * @param b a boolean TRUE or FALSE (0 or 1)
 * @returns a json_object of type json_type_boolean
 */
extern struct json_object* json_object_new_boolean(bool b);

/** Get the boolean value of a json_object
 *
 * The type is coerced to a boolean if the passed object is not a boolean.
 * integer and double objects will return FALSE if there value is zero
 * or TRUE otherwise. If the passed object is a string it will return
 * TRUE if it has a non zero length. If any other object type is passed
 * TRUE will be returned if the object is not NULL.
 *
 * @param obj the json_object instance
 * @returns a boolean
 */
extern bool json_object_get_boolean(struct json_object *obj);


/* int type methods */

/** Create a new empty json_object of type json_type_int
 * @param i the integer
 * @returns a json_object of type json_type_int
 */
extern struct json_object* json_object_new_int(int i);

/** Get the int value of a json_object
 *
 * The type is coerced to a int if the passed object is not a int.
 * double objects will return their integer conversion. If no conversion exists then 0 is returned and errno is set to EINVAL.
 * null is equivalent to 0 (no error values set)
 *
 * If the value is too big to fit in an int, then the value is clamped at the closest value (i.e. INT_MIN for negative infinity) and
 * errno is set to ERANGE.
 * 
 * A NaN double value is cast to an int and errno is set to EINVAL.  This cast value is platform dependant.
 *
 * Strings are parsed as doubles and then follow the above conversion rules.
 *
 * Arrays of length 0 are interpreted as 0 (with no error flags set).  Arrays of length 1 are effectively cast to the equivalent object
 * converted using the above rules.  All other arrays are the equivalent of converting a double NaN value to an int.
 *
 * NOTE: Set errno to 0 directly before a call to this function to determine whether or not
 * conversion was successful (it does not clear the value for you).
 *
 * @param obj the json_object instance
 * @returns an int
 */
extern int json_object_get_int(struct json_object *obj);


/* double type methods */

/** Create a new empty json_object of type json_type_double
 * @param d the double
 * @returns a json_object of type json_type_double
 */
extern struct json_object* json_object_new_double(double d);

/** Get the double floating point value of a json_object
 *
 * The type is coerced to a double if the passed object is not a double.
 * integer objects will return their double conversion. If no conversion exists then 0 is returned and errno is set to EINVAL.
 * null is equivalent to 0 (no error values set)
 *
 * If the value is too big to fit in a double, then the value is set to the closest infinity with errno set to ERANGE.
 * 
 * If strings cannot be converted to their double value, then EINVAL is set & NaN is returned.
 *
 * Arrays of length 0 are interpreted as 0 (with no error flags set).  Arrays of length 1 are effectively cast to the equivalent object
 * converted using the above rules.  All other arrays set the error to EINVAL & return NaN.
 *
 * NOTE: Set errno to 0 directly before a call to this function to determine whether or not 
 * conversion was successful (it does not clear the value for you).
 *
 * @param obj the json_object instance
 * @returns a double floating point number
 */
extern double json_object_get_double(struct json_object *obj);


/* string type methods */

/** Create a new empty json_object of type json_type_string
 *
 * A copy of the string is made and the memory is managed by the json_object
 *
 * @param s the string
 * @returns a json_object of type json_type_string
 */
extern struct json_object* json_object_new_string(const char *s);

extern struct json_object* json_object_new_string_len(char *s, int len);

/** Get the string value of a json_object
 *
 * If the passed object is not of type json_type_string then the JSON
 * representation of the object is returned.
 *
 * The returned string memory is managed by the json_object and will
 * be freed when the reference count of the json_object drops to zero.
 *
 * @param obj the json_object instance
 * @returns a string
 */
extern char* json_object_get_string(struct json_object *obj);

#endif
