//  @@@LICENSE
//
//      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  LICENSE@@@

#ifndef __HJSON__
#define __HJSON__

#ifdef __cplusplus
extern "C" {
#endif

#include "HString.h"

typedef struct HJson HJson;

// create and init an HJson pointer. This will parse the
// json string. If it can't parse, it will return NULL. You
// are responsible for calling HJson_free on the returned value
// if it is not NULL.
HJson *HJson_create(const char *jsonStr);

// extract a value from an HJson pointer. It will return NULL
// if the value doesn't exist. You are responsible for calling
// HString_free() on the result when you are done with it.
HString *HJson_getValue(HJson *hjson, const char *valueName);

// extract various types from the json. Will return 0 if the
// value doesn't exist. Use HJson_valuExists to verify if
// a value is there at all. in cases of "bool" it will return 1
// for true, 0 for false
int HJson_valueExists(HJson *hjson, const char *valueName);
int HJson_getInt(HJson *hjson, const char *valueName);
double HJson_getDouble(HJson *hjson, const char *valueName);
int HJson_getBool(HJson *hjson, const char *valueName);

// call to deallocate a HJson instance that you created with
// HJson_create()
void HJson_free(HJson *hjson);

// one-stop shopping function to extract a value directly from a
// string. Uses HJson_create, HJson_getValue, and HJson_free
HString *HJson_getValueFromStr(const char *jsonStr, const char *valueName);

// function to fill an array with the int values of an int array in the json
// returns the number of fields filled out, or -1 if there was an error.
// you must send in an allocated int array, and the number of ints that
// array can hold.
int HJson_getIntArray(HJson *hjson, const char *valueName, int *array, int allocLen);

// direct polling of values
int HJson_getNumFields(HJson *hjson); // returns the number of (top level) fields in this json
HString *HJson_getNameByIdx(HJson *hjson, int idx); // returns the name of the idx'th field. Caller is responsible for calling HString_free on the returned value
HString *HJson_getValueByIdx(HJson *hjson, int idx); // returns the value of the idx'th field. Caller is responsible for calling HString_free on the returned value

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
// available only in c++ apps, a convenience container
class HJsonContainer
{
public:
	HJsonContainer() { m_contain = NULL; }
	HJsonContainer(HJson *contain) { m_contain = contain; }
	~HJsonContainer() { HJson_free(m_contain); m_contain=NULL; }
	HJson *m_contain;
};
#endif


#endif

