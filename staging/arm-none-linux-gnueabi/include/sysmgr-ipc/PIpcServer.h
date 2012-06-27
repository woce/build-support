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


#ifndef PIPCSERVER_H
#define PIPCSERVER_H

#include <glib.h>

#include <string>

#include "basictypes.h"

class PIpcChannel;
struct PIpcSocketSource;

class PIPC_API PIpcServer
{
public:

	PIpcServer(const std::string& name, GMainLoop* loop);
	virtual ~PIpcServer();

	GMainLoop* mainLoop() const;

	virtual void clientConnected(int pid, const std::string& name, PIpcChannel* proxy) = 0;

private:

	void init();
	static gboolean ioCallback(PIpcSocketSource* src, GIOCondition condition, gpointer userData);
	void socketCallback(GIOCondition condition);

	std::string m_socketPath;
	GMainLoop* m_mainLoop;
	int m_socketFd;
	GSource* m_socketSource;
		
private:

	DISALLOW_COPY_AND_ASSIGN(PIpcServer);
};


#endif /* PIPCSERVER_H */
