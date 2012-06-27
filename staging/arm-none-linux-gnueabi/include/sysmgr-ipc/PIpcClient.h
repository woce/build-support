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


#ifndef PIPCCLIENT_H
#define PIPCCLIENT_H

#include <glib.h>
#include <string>

#include "basictypes.h"

class PIpcChannel;

class PIPC_API PIpcClient
{
public:

	PIpcClient(const std::string& serverName, const std::string& name,
			   GMainLoop* loop);
	virtual ~PIpcClient();

	GMainLoop* mainLoop() const { return m_mainLoop; }

	virtual void serverConnected(PIpcChannel* channel) = 0;
	virtual void serverDisconnected() = 0;

private:

	void init();
	static gboolean initTimeoutCallback(gpointer arg);

	std::string m_socketPath;
	std::string m_name;
	GMainLoop* m_mainLoop;
		
private:

	DISALLOW_COPY_AND_ASSIGN(PIpcClient);
};

#endif /* PIPCCLIENT_H */
