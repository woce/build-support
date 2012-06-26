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

#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include "HCommon.h"

// a single list element
class HEXPORT ll_elem
{
public:
	ll_elem();

	void *m_data;
	ll_elem *m_next;
};

class HEXPORT HLinkedList
{
public:
	HLinkedList();
	virtual ~HLinkedList();

	// insertion
	void append(void *data); // adds the element at the end of the list
	void prepend(void *data); // adds the element to the beginning of the list
	void insert(int idx, void *data); // inserts the element at the specified location

	// removal
	void remove(void *data); // remove the first element that has this pointer for data
	void remove(int idx); // remove the element at this index
	void clear(); // remove all elements

	// access
	int size(); // returns the number of elements in the list
	void *get(int idx); // returns the element at the sent-in address

	// for more advanced use, you can access the ll_elem values themselves
	ll_elem *getLLElem(int idx);
	ll_elem *getLLElem(void *data);

protected:

	ll_elem *m_head;
	int m_size; // cached for performance
};

#endif


