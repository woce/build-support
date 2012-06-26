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


#ifndef PIPCBUFFER_H
#define PIPCBUFFER_H

#include <stdint.h>
#include <glib.h>
#include <pthread.h>

#include "basictypes.h"

class PIPC_API PIpcBuffer
{
public:

	static PIpcBuffer* create(int size);
	static PIpcBuffer* attach(int key, int size=-1);
	~PIpcBuffer();

	int key() const { return m_key; }
	void* data() const;
	int size() const;
	
	int getTransitionBufferKey() const;
	void setTransitionBufferKey(int key);

	int getResizedBufferKey() const;
	void setResizedBufferKey(int key);

	bool trylock();
	bool lock();
	bool unlock();

	bool trylock2();
	bool lock2();
	bool unlock2();
	
private:

	PIpcBuffer();
	bool isValid() const;

	bool trylock(pthread_mutex_t* mutex, int& lockCount);
	bool lock(pthread_mutex_t* mutex, int& lockCount);
	bool unlock(pthread_mutex_t* mutex, int& lockCount);

private:

	int m_key;
	void* m_data;
	void* m_usableData;
	int m_size;
	int m_lockCount;
	int m_lockCount2;

private:

	DISALLOW_COPY_AND_ASSIGN(PIpcBuffer);
};

#endif /* PIPCBUFFER_H */
