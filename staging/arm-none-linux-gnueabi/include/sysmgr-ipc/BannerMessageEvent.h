/**
 *  Copyright (c) 2010 - 2012 Hewlett-Packard Development Company, L.P.
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


#ifndef BANNERMESSAGEEVENT_H
#define BANNERMESSAGEEVENT_H

#include <string>

struct BannerMessageEvent
{
	enum MessageType {
		Add = 0,
		Remove,
		Clear,
		PlaySound,
		Invalid = 0xFF00
	};

	MessageType msgType;
	std::string msgId;
	std::string appId;
	std::string msg;
	std::string launchParams;
	std::string icon;
	std::string soundClass;
	std::string soundFile;
	int duration;
	bool wakeupScreen;
	bool doNotSuppress;

    BannerMessageEvent() 
        : msgType(Invalid), duration(0), wakeupScreen(false), doNotSuppress(false) {}
};	


struct BannerMessageEventWrapper
{
	BannerMessageEventWrapper()
		: event(0) {}

	BannerMessageEventWrapper(BannerMessageEvent* evt)
		: event(evt) {}

	BannerMessageEvent* event;
};

#endif /* BANNERMESSAGEEVENT_H */
