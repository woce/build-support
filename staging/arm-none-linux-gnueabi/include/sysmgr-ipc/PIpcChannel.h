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


#ifndef PIPCCHANNEL_H
#define PIPCCHANNEL_H

#include <glib.h>

#include <list>
#include <queue>
#include <string>
#include <stdint.h>
#include <pthread.h>

#include "PIpcMessageUtils.h"
#include "PIpcAsyncCaller.h"

struct PIpcSocketSource;
class PIpcChannelListener;
class PIpcMessage;

class PIPC_API PIpcChannel
{
public:

	PIpcChannel(GMainLoop* loop, int socketFd);
	~PIpcChannel();

	// Not thread-safe
	void setListener(PIpcChannelListener* listener);
	// Not thread-safe
	PIpcChannelListener* listener() const;

	// thread-safe
	void sendAsyncMessage(PIpcMessage* msg);
	void queueAsyncMessage(PIpcMessage* msg);

	// Not thread-safe
	bool sendSyncMessage(PIpcMessage* msg, PIpcMessage*& reply, int timeoutMs=5000);
	// Not thread-safe
	void sendReply(PIpcMessage* msg);

	void setRemoteIsSuspended(bool val);
	bool remoteIsSuspended() const;

	// Not thread-safe
	template<class SendParamType, class ReplyParamType>
	bool sendSyncMessage(PIpcMessageWithReply<SendParamType, ReplyParamType>* msg, int timeoutMs=5000) {
		ReplyParamType replyParam = msg->reply_; 
		PIpcMessage* reply = 0;
		if (sendSyncMessage(msg, reply, timeoutMs) && reply) {
			ReadParam(reply, &replyParam);
			delete reply;
			return true;
		}
		return false;
	}

	// Not thread-safe
	template<class SendParamType, class ReplyParamType>
	bool sendSyncSuspendMessage(PIpcMessageWithReply<SendParamType, ReplyParamType>* msg, int timeoutMs=5000) {
		ReplyParamType replyParam = msg->reply_;
		PIpcMessage* reply = 0;
		msg->set_suspend();
		if (sendSyncMessage(msg, reply, timeoutMs) && reply) {
			ReadParam(reply, &replyParam);
			delete reply;
			setRemoteIsSuspended(true);
			return true;
		}
		setRemoteIsSuspended(true);
		return false;
	}

private:

	void init();
	static gboolean ioCallback(PIpcSocketSource* src, GIOCondition condition, gpointer userData);
	void socketCallback(PIpcSocketSource* src, GIOCondition condition);
	void disconnected();
	void processOutgoingMessages();
	bool processIncomingMessages();
	bool processOneOutgoingMessage();
	void handleIncomingMessageInNestedMode(PIpcMessage* msg);
	void handleIncomingMessageInNormalMode(PIpcMessage* msg);
	void handleIncomingSyncMessage(PIpcMessage* msg);
	bool dispatchIncomingAsyncMessages();
	void asyncCallerDispatch();

	int writeToSocket(char* buffer, int len);
	int readFromSocket(char* buffer, int len, bool& noError);

	static gboolean dispatchIncomingAsyncMessagesCallback(gpointer arg);
	static gboolean nestedLoopTimeoutCallback(gpointer arg);

	struct MessageHandledInfo {
		void reset() {
			m_lengthBytesHandled = 0;
			m_payloadBytesHandled = 0;
		}

		int m_lengthBytesHandled;
		int m_payloadBytesHandled;
	};
	
	GMainLoop* m_mainLoop;
	int m_socketFd;
	GSource* m_socketSource;
	PIpcChannelListener* m_listener;
	bool m_blockedOnWrite;
	bool m_remoteIsSuspended;

	GMainContext* m_nestedMainContext;
	GMainLoop* m_nestedMainLoop;
	GSource* m_nestedSocketSource;
	GSource* m_nestedTimeoutSource;
	bool m_inNestedLoop;
	bool m_syncCallTimedOut;
	uint32_t m_currSyncMessageId;
	PIpcMessage* m_currSyncReply;

	PIpcMessage* m_replyForIncomingSyncMessage;
	
	std::queue<PIpcMessage*> m_outgoingMessages;
	MessageHandledInfo m_currOutgoingMessageInfo;

	std::queue<PIpcMessage*> m_otherThreadOutgoingMessages;
	pthread_mutex_t m_otherThreadOutgoingMessagesMutex;
	pthread_t m_creatingThread;
	
	std::list<PIpcMessage*> m_incomingAsyncMessages;
	PIpcMessage* m_incomingMessage;
	int m_incomingMessagePayloadLength;
	MessageHandledInfo m_currIncomingMessageInfo;
	GSource* m_incomingAsyncMessagesDispatcherSrc;

	PIpcAsyncCaller<PIpcChannel>* m_asyncCaller;
	
private:

	DISALLOW_COPY_AND_ASSIGN(PIpcChannel);
};

#endif /* PIPCCHANNEL_H */
