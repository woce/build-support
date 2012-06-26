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

#ifndef __HSTRING__
#define __HSTRING__

#include <stdlib.h>
#include "HData.h"

/* A simple string management class. Usually used for straight-c modules who don't
 * have access to C++'s string class */
#ifdef __cplusplus
extern "C" {
#endif

// the HData structure
typedef struct _HString
{
	HData *str;
	int length;
} HString;

/* allocate a new string structure and return the pointer to it. */
HString *HString_alloc(void);

/* append a formatted string. Ensures proper memory allocation and growth of the internal allocations
 * returns 0 on success. nonzero on an error. */
int HString_append(HString *str, const char *fmt, ...);

/* set a formatted string. Same as HString_append, but clears the string first */
int HString_set(HString *str, const char *fmt, ...);

/* return a const char * of this string */
const char *HString_toStr(HString *str);

/* deallocate the string */
void HString_free(HString *str);


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
// available only in c++ apps, a convenience container
class HStringContainer
{
public:
	HStringContainer() { m_contain = NULL; }
	HStringContainer(HString *contain) { m_contain = contain; }
	~HStringContainer() { HString_free(m_contain); m_contain=NULL; }
	HString *m_contain;
};
#endif

#endif

