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


#ifndef SYSMGRKEYEVENTTRAITS_H
#define SYSMGRKEYEVENTTRAITS_H

#include <string.h>

#include <QKeyEvent>

#include <PIpcMessageUtils.h>

// Packing important. Also no virtual functions here
struct SysMgrKeyEvent
{
	// For reading
	SysMgrKeyEvent() {
	}
	
	// For writing
	SysMgrKeyEvent(QKeyEvent* e)
		: type(e->type())
		, key(e->key())
		, modifiers(e->modifiers())
		, s(e->text().toStdString())
	{
	}

	inline QKeyEvent qtEvent() const {
		return QKeyEvent((QEvent::Type) type, (Qt::Key) key,
						 (Qt::KeyboardModifiers) modifiers, (QString)QString::fromStdString(s));
	}

	uint16_t type;
	int key;
	uint32_t modifiers;
	std::string s;
};

template<>
struct ParamTraits<SysMgrKeyEvent> {

	typedef SysMgrKeyEvent param_type;

	static void Write(PIpcMessage* m, const param_type& p) {
/*		m->writeBytes(&p, sizeof(SysMgrKeyEvent));
 *		*/
		m->writeInt16(p.type);
		m->writeInt32(p.key);
		m->writeInt32(p.modifiers);
		m->writeString(p.s);
	}
	
	static bool Read(const PIpcMessage* m, param_type* r) {
/*		const char* data;
		int dataSize = sizeof(SysMgrKeyEvent);
		if (!m->readBytes((const char**) &data, dataSize))
			return false;
		::memcpy(r, data, dataSize);
		return true;
		*/
		m->readInt16((int16_t*)&(r->type));
		m->readInt32((int32_t*)&(r->key));
		m->readInt32((int32_t*)&(r->modifiers));
		m->readString(&(r->s));
		return true;
	}
	
	static uint32_t Length(const param_type& p) {
		return sizeof(uint16_t)+sizeof(int)+sizeof(uint32_t)+PIpcMessage::lengthOf(p.s);
	}
};	


#endif /* SYSMGRKEYEVENTTRAITS_H */
