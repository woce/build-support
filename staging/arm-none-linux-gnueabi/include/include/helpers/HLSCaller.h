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

#ifndef __HLSCALL__
#define __HLSCALL__

#include <sys/types.h>
#include "HCommon.h"
#include "HLinkedList.h"


// forward declaration of GMainLoop
extern "C"
{
	struct _GMainLoop;
	typedef struct _GMainLoop GMainLoop;
}

// the function prototype for the callback. The id will be the same value
// that was returned by the lsCall. Reploy will be a json-formated string.
// context will be the pointer passed in to the lsCall (user-defined pointer)
typedef void (*HLSCallback) (int id, const char *reply, void *context);

//HLSHandle forward declaration
class HLSHandle;
class HInternalCallbackContext;

class HEXPORT HLSCaller
{
public:
	HLSCaller();
	~HLSCaller();

	// you must call this before calling lsCall or lsCallWithResponse. This will initalize the internals.
	// Luna Service responses are dispatched through a GMainLoop instance. You may specify your own. If you
	// have one, this is recommended.
	// If you don't, or don't wish to use yours, you can send NULL and this library will spawn a thread
	// and make the GMainLoop internally.
	// For the appID, you shoudl send the appID you want to register with ther
	// service bus (some services care about this field a lot). You may send NULL.
	void init(GMainLoop *mainLoop);

	// simply call this to make a Luna Services call
	// destinationUri: the uri (including method name) that you're sending the LS Call to
	// payload: the json formated payload for the call
	// isPrivate: true to send this on the private bus. False to send it on the public bus
	// returns a unique identifier for this LS call, or -1 if there was a failure
	int lsCall(const char *destinationUri, const char *payload, bool isPrivate);

	// call this version if you want to specify a callback.
	// the first three parameters are the same as HLSCall. callback is
	// the callback function to be called with the reply from the service call, and
	// context is a user-defined value that is passed in to the callback.
	// returns a unique identifier for this LS call, or -1 if there was a failure
	// this will get you ONE response. If you want multiple responses, use
	// lsCallWithSubscription.
	int lsCallWithResponse(const char *destinationUri, const char *payload, bool isPrivate, HLSCallback callback, void *context);

	// call this version if you expect multiple replies to your call.
	// other than that, it's the same as lsCallWithResponse.
	int lsCallWithSubscription(const char *destinationUri, const char *payload, bool isPrivate, HLSCallback callback, void *context);

	// call this to cancel a specific call (and thus any callback behavior) based on the
	// ID that was returned when the call was made. returns 0 on success. Returns 1 if
	// there were no pending calls with that id.
	int lsCancelCall(int callID);

	// internal use. no touchey.
	bool callback(void *voidSH, void *voidReply, HInternalCallbackContext *ctx);
	HInternalCallbackContext *getContextByID(int id);

	// use this to get information about the role file currently in place
	// for the executing app. If you're having a problem with services being
	// declined or ignored, or if you're getting output from the service bus
	// telling you it has errors, your role file is the likely cause.
	// will output to tracking under the category "hlsc_1"
	static void outputRoleFileInfo();

protected:

	// internal helper function to register the callback and perform the call
	int lsCallInternal(const char *destinationUri, const char *payload, void *context, HLSCallback callback, bool usePrivateHandle, bool bRemoveAfterResponse);
	static void outputRoleFile(const char *callPath, const char *roleDir);

	HLinkedList m_callbacks;
	bool m_bCalledInit;
	bool m_bShutDown;
	bool m_bExternalMainLoop;
	GMainLoop *m_mainLoop;
	pthread_t m_thread;

	HLSHandle *m_lunaHandle;
};

#endif


