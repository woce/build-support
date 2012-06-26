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

#ifndef HEVENT_H_
#define HEVENT_H_

#include "HSemaphore.h"
#include "HTracker.h"

struct HEXPORT HEvent
{
	HEvent()
		: m_sem(0)
		, m_bPosted(false)
    {
    }

    void Post()
    {
    	// already posted = ignore
    	if ( m_bPosted ) return;

    	// post, and make note of it
    	m_bPosted = true;
    	m_sem.Post();
    }

    bool Wait(int timeout = 0)
    {
    	// if it's already posted, you're good to go
    	if ( m_bPosted ) return true;
    	return m_sem.Wait(timeout);
    }

    void reset()
    {
    	m_bPosted = false;
    }

protected:
	bool m_bPosted;
    HSemaphore m_sem;
};

#endif /* NSEMAPHORE_H_ */
