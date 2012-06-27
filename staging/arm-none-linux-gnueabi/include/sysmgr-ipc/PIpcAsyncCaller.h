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


#ifndef PIPCASYNCCALLER_H
#define PIPCASYNCCALLER_H

#include <glib.h>
#include <pthread.h>

class PIpcAsyncCallerBase
{
public:

	PIpcAsyncCallerBase(GMainLoop* loop);
	virtual ~PIpcAsyncCallerBase();

	void call();

protected:

	virtual void dispatch() = 0;	
	
private:

	static gboolean callback(GIOChannel* channel, GIOCondition condition, gpointer arg);

	int m_pipeFd[2];
	GIOChannel* m_ioChannel;
	GSource* m_ioSource;
	pthread_mutex_t m_mutex;
};

template <class Target>
class PIpcAsyncCaller : public PIpcAsyncCallerBase
{
public:

	typedef void (Target::*DispatchFunction)();

	PIpcAsyncCaller(Target* target, DispatchFunction function, GMainLoop* loop)
		: PIpcAsyncCallerBase(loop)
		, m_target(target)
		, m_function(function) {}

private:

	virtual void dispatch() { return (m_target->*m_function)(); }

	Target* m_target;
	DispatchFunction m_function;
};


#endif /* ASYNCCALLER_H */
