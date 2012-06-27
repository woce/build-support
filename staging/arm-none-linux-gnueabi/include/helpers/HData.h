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

#ifndef __HDATA__
#define __HDATA__


#ifdef __cplusplus
extern "C" {
#endif


// the HData structure
typedef struct _HData
{
	void *data; // the data
	int allocSize; // the size of this allocation
} HData;

// allocate data. returns NULL on failure. Special use: You may
// send 0 in as the size to only allocate the HData structure with a
// NULL pointer on the inside. This structure can be used as normal
// when sent to other HData functions
HData *HData_alloc(int size);

// free data
void HData_free(HData *data);

// ensure this hdata has at least "size" bytes of allocation,
// reallocate if necessary. Returns 0 on success. returns nonzero
// on failure
int HData_ensure(HData *data, int size);


// allocate a buffer

#ifdef __cplusplus
}
#endif


#endif

