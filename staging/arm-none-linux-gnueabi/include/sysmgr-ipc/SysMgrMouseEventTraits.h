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


#ifndef SYSMGRMOUSEEVENTTRAITS_H
#define SYSMGRMOUSEEVENTTRAITS_H

#include <string.h>

#include <QKeyEvent>
#include <QMouseEvent>

#include <PIpcMessageUtils.h>

// Packing important. Also no virtual functions here
struct SysMgrMouseEvent
{
	// For reading
	SysMgrMouseEvent() {
	}

	// For writing
	SysMgrMouseEvent(QMouseEvent* e)
		: type(e->type())
		, button(e->button())
		, x(e->pos().x())
		, y(e->pos().y())
		, modifiers(e->modifiers()) {
	}

	inline QMouseEvent qtEvent() const {
		return QMouseEvent((QEvent::Type)type, QPoint(x, y),
						   (Qt::MouseButton) button,
						   (Qt::MouseButton) button,
						   (Qt::KeyboardModifiers) modifiers);
	}

	// Ordering important here to preserve compact packing
	// (4 shorts + 1 word = 3 words)
	uint16_t type;
	uint16_t button;
	uint16_t x;
	uint16_t y;
	uint32_t modifiers;
};

template<>
struct ParamTraits<SysMgrMouseEvent> {

	typedef SysMgrMouseEvent param_type;

	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeBytes(&p, sizeof(SysMgrMouseEvent));
	}
	
	static bool Read(const PIpcMessage* m, param_type* r) {
		const char* data;
		int dataSize = sizeof(SysMgrMouseEvent);
		if (!m->readBytes((const char**) &data, dataSize))
			return false;
		::memcpy(r, data, dataSize);
		return true;
	}
	
	static uint32_t Length(const param_type& p) {
		return sizeof(SysMgrMouseEvent);
	}
};	

#endif /* SYSMGRMOUSEEVENTTRAITS_H */
