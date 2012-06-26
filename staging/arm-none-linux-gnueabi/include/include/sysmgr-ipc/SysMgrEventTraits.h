/**
 *  Copyright (c) 2009 - 2012 Hewlett-Packard Development Company, L.P.
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


#ifndef SYSMGREVENTTRAITS_H
#define SYSMGREVENTTRAITS_H

#include <string.h>

#include "SysMgrEvent.h"
#include "PIpcMessageUtils.h"
#include "NewContentIndicatorEvent.h"
#include "BannerMessageEvent.h"
#include "ActiveCallBannerEvent.h"
#include "AppLaunchOptionsEvent.h"
#include <ime/palmimedefines.h>

template <>
struct ParamTraits<PalmIME::EditorState> {
	typedef PalmIME::EditorState param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeBytes(&p.type, sizeof(PalmIME::EditorState));
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		const char* data;
		int dataSize = sizeof(PalmIME::EditorState);
		if (!m->readBytes((const char**) &data, dataSize))
			return false;
		memcpy(&r->type, data, dataSize);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(PalmIME::EditorState);
	}
};

template <>
struct ParamTraits<SysMgrEvent> {
	typedef SysMgrEvent param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeBytes(&p.type, sizeof(SysMgrEvent));
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		const char* data;
		int dataSize = sizeof(SysMgrEvent);
		if (!m->readBytes((const char**) &data, dataSize))
			return false;
		memcpy(&r->type, data, dataSize);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(SysMgrEvent);
	}
};

template <>
struct ParamTraits<SysMgrEventWrapper> {
	typedef SysMgrEventWrapper param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeBytes(&p.event->type, sizeof(SysMgrEvent));
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		const char* data;
		int dataSize = sizeof(SysMgrEvent);
		if (!m->readBytes((const char**) &data, dataSize))
			return false;
		r->event = (SysMgrEvent*) data;
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(SysMgrEvent);
	}
};

template <>
struct ParamTraits<NewContentIndicatorEvent> {
	typedef NewContentIndicatorEvent param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32((int32_t)p.eventType);
		m->writeString(p.appId);
		m->writeString(p.requestId);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		m->readInt32((int32_t*)&r->eventType);
		m->readString(&r->appId);
		m->readString(&r->requestId);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.appId) +
			   PIpcMessage::lengthOf(p.appId) ;
	}
};

template <>
struct ParamTraits<NewContentIndicatorEventWrapper> {
	typedef NewContentIndicatorEventWrapper param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32((int32_t)p.event->eventType);
		m->writeString(p.event->appId);
		m->writeString(p.event->requestId);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		r->event = new NewContentIndicatorEvent;
		m->readInt32((int32_t*)&r->event->eventType);
		m->readString(&r->event->appId);
		m->readString(&r->event->requestId);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.event->appId) +
			   PIpcMessage::lengthOf(p.event->appId) ;
	}
};


template <>
struct ParamTraits<AppLaunchOptionsEvent> {
	typedef AppLaunchOptionsEvent param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeString(p.splashBackground);
		m->writeBool(p.launchInNewGroup);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		m->readString(&r->splashBackground);
		m->readBool(&r->launchInNewGroup);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.splashBackground) +
			   PIpcMessage::lengthOf(p.launchInNewGroup);
	}
};

template <>
struct ParamTraits<AppLaunchOptionsEventWrapper> {
	typedef AppLaunchOptionsEventWrapper param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeString(p.event->splashBackground);
		m->writeBool(p.event->launchInNewGroup);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		r->event = new AppLaunchOptionsEvent;
		m->readString(&r->event->splashBackground);
		m->readBool(&r->event->launchInNewGroup);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.event->splashBackground) +
			   PIpcMessage::lengthOf(p.event->launchInNewGroup);
	}
};

template <>
struct ParamTraits<BannerMessageEvent> {
	typedef BannerMessageEvent param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32((int32_t)p.msgType);
		m->writeString(p.msgId);
		m->writeString(p.appId);
		m->writeString(p.msg);
		m->writeString(p.launchParams);
		m->writeString(p.icon);
		m->writeString(p.soundClass);
		m->writeString(p.soundFile);
		m->writeInt32(p.duration);
		m->writeBool(p.wakeupScreen);
		m->writeBool(p.doNotSuppress);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		m->readInt32((int32_t*)&r->msgType);
		m->readString(&r->msgId);
		m->readString(&r->appId);
		m->readString(&r->msg);
		m->readString(&r->launchParams);
		m->readString(&r->icon);
		m->readString(&r->soundClass);
		m->readString(&r->soundFile);
		m->readInt32(&r->duration);
		m->readBool(&r->wakeupScreen);
		m->readBool(&r->doNotSuppress);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.msgId) +
			   PIpcMessage::lengthOf(p.appId) +
			   PIpcMessage::lengthOf(p.msg) +
			   PIpcMessage::lengthOf(p.launchParams) +
			   PIpcMessage::lengthOf(p.icon) +
			   PIpcMessage::lengthOf(p.soundClass) +
			   PIpcMessage::lengthOf(p.soundFile) +
			   PIpcMessage::lengthOf(p.duration) +
			   PIpcMessage::lengthOf(p.wakeupScreen) +
			   PIpcMessage::lengthOf(p.doNotSuppress);
	}
};

template <>
struct ParamTraits<BannerMessageEventWrapper> {
	typedef BannerMessageEventWrapper param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32((int32_t)p.event->msgType);
		m->writeString(p.event->msgId);
		m->writeString(p.event->appId);
		m->writeString(p.event->msg);
		m->writeString(p.event->launchParams);
		m->writeString(p.event->icon);
		m->writeString(p.event->soundClass);
		m->writeString(p.event->soundFile);
		m->writeInt32(p.event->duration);
		m->writeBool(p.event->wakeupScreen);
		m->writeBool(p.event->doNotSuppress);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		r->event = new BannerMessageEvent;
		m->readInt32((int32_t*)&r->event->msgType);
		m->readString(&r->event->msgId);
		m->readString(&r->event->appId);
		m->readString(&r->event->msg);
		m->readString(&r->event->launchParams);
		m->readString(&r->event->icon);
		m->readString(&r->event->soundClass);
		m->readString(&r->event->soundFile);
		m->readInt32(&r->event->duration);
		m->readBool(&r->event->wakeupScreen);
		m->readBool(&r->event->doNotSuppress);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.event->msgId) +
			   PIpcMessage::lengthOf(p.event->appId) +
			   PIpcMessage::lengthOf(p.event->msg) +
			   PIpcMessage::lengthOf(p.event->launchParams) +
			   PIpcMessage::lengthOf(p.event->icon) +
			   PIpcMessage::lengthOf(p.event->soundClass) +
			   PIpcMessage::lengthOf(p.event->soundFile) +
			   PIpcMessage::lengthOf(p.event->duration) +
			   PIpcMessage::lengthOf(p.event->wakeupScreen) +
			   PIpcMessage::lengthOf(p.event->doNotSuppress);
	}
};

template <>
struct ParamTraits<ActiveCallBannerEvent> {
	typedef ActiveCallBannerEvent param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32((int32_t)p.type);
		m->writeString(p.msg);
		m->writeString(p.icon);
		m->writeInt32((int32_t)p.time);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		m->readInt32((int32_t*)&r->type);
		m->readString(&r->msg);
		m->readString(&r->icon);
		m->readInt32((int32_t*)&r->time);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.msg) +
			   PIpcMessage::lengthOf(p.icon) +
			   sizeof(int32_t);
	}
};

template <>
struct ParamTraits<ActiveCallBannerEventWrapper> {
	typedef ActiveCallBannerEventWrapper param_type;
	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32((int32_t)p.event->type);
		m->writeString(p.event->msg);
		m->writeString(p.event->icon);
		m->writeInt32((int32_t)p.event->time);
	}
	static bool Read(const PIpcMessage* m, param_type* r) {
		r->event = new ActiveCallBannerEvent;
		m->readInt32((int32_t*)&r->event->type);
		m->readString(&r->event->msg);
		m->readString(&r->event->icon);
		m->readInt32((int32_t*)&r->event->time);
		return true;
	}
	static uint32_t Length(const param_type& p) {
		return sizeof(int32_t)  +
			   PIpcMessage::lengthOf(p.event->msg) +
			   PIpcMessage::lengthOf(p.event->icon) +
			   sizeof(int32_t);
	}
};

#endif // SYSMGREVENTTRAITS_H
