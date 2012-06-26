/**
 *  Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#ifndef PIPCMUTEX_H
#define PIPCMUTEX_H

#include <stdint.h>
#include <glib.h>

#include "basictypes.h"

class PIpcMutexData;

class PIPC_API PIpcMutex
{
public:

	static PIpcMutex* create();
	static PIpcMutex* attach(int key);
	~PIpcMutex();

	int key() const { return m_key; }

	bool lock();
	bool tryLock();
	bool unlock();

private:

	PIpcMutex();
	bool isValid() const;

private:
	
	int m_key;
	PIpcMutexData* m_data;

private:

	DISALLOW_COPY_AND_ASSIGN(PIpcMutex);
};

#endif /* PIPCMUTEX_H */
