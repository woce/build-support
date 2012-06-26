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


#ifndef SYSMGRTOUCHEVENTTRAITS_H
#define SYSMGRTOUCHEVENTTRAITS_H

#include <string.h>
#include <stdio.h>

#include <QKeyEvent>
#include <QTouchEvent>

#include <PIpcMessageUtils.h>

// structure to store the information in QTouchEvent::TouchPoint
struct SysMgrTouchPoint
{
	int32_t id;
	uint32_t state;
    bool isPrimary;
	int32_t x;
	int32_t y;
};

// Packing important. Also no virtual functions here
struct SysMgrTouchEvent
{
public:

	uint32_t type;
	uint32_t state;
	uint32_t modifiers;
	uint32_t numTouchPoints;
	SysMgrTouchPoint* touchPoints;


	// For reading
	SysMgrTouchEvent() :
		touchPoints(0)
	{
	}

	// For writing
	SysMgrTouchEvent(QTouchEvent* e, int offsetX, int offsetY)
		: type (e->type())
		, state (e->touchPointStates())
		, modifiers (e->modifiers())
		, numTouchPoints(0)
		, touchPoints(0)
	{
		numTouchPoints = e->touchPoints().size();
		touchPoints = new SysMgrTouchPoint[numTouchPoints];

		int index = 0;
		
		QList<QTouchEvent::TouchPoint>::const_iterator iter;
		for (iter = e->touchPoints().begin(); iter != e->touchPoints().end(); ++iter) {

			SysMgrTouchPoint& tp = touchPoints[index++];
			tp.id = (*iter).id();
			tp.state = (*iter).state();
			tp.x = (*iter).pos().x() + offsetX;
			tp.y = (*iter).pos().y() + offsetY;
            tp.isPrimary = (*iter).isPrimary();
		}		
	}

	~SysMgrTouchEvent() {
		if (touchPoints)
			delete [] touchPoints;
	}

	SysMgrTouchEvent(const SysMgrTouchEvent& other)
	{
		type = other.type;
		state = other.state;
		modifiers = other.modifiers;
		numTouchPoints = other.numTouchPoints;
		if (numTouchPoints > 0) {
			touchPoints = new SysMgrTouchPoint[numTouchPoints];
			::memcpy(touchPoints, other.touchPoints, numTouchPoints * sizeof(SysMgrTouchPoint));
		}
		else {
			touchPoints = 0;
		}
	}
	
	SysMgrTouchEvent& operator=(const SysMgrTouchEvent& other)
	{
		if (this != &other) {
			type = other.type;
			state = other.state;
			modifiers = other.modifiers;
			numTouchPoints = other.numTouchPoints;
			if (numTouchPoints > 0) {
				touchPoints = new SysMgrTouchPoint[numTouchPoints];
				::memcpy(touchPoints, other.touchPoints, numTouchPoints * sizeof(SysMgrTouchPoint));
			}
			else {
				touchPoints = 0;
			}
		}

		return *this;		
	}
};

template<>
struct ParamTraits<SysMgrTouchEvent> {

	typedef SysMgrTouchEvent param_type;

	static void Write(PIpcMessage* m, const param_type& p) {
		m->writeInt32 (p.type);
		m->writeInt32 (p.state);
		m->writeInt32 (p.modifiers);
		m->writeInt32 (p.numTouchPoints);
		m->writeBytes (p.touchPoints, sizeof (SysMgrTouchPoint) * p.numTouchPoints);
	}
	
	static bool Read(const PIpcMessage* m, param_type* r) {
		m->readInt32 ((int32_t*)&(r->type));
		m->readInt32 ((int32_t*)&(r->state));
		m->readInt32 ((int32_t*)&(r->modifiers));
		m->readInt32 ((int32_t*)&(r->numTouchPoints));
		if (r->numTouchPoints > 0) {
			r->touchPoints = new SysMgrTouchPoint[r->numTouchPoints];
			const char* data;			
			m->readBytes ((const char**) &data, sizeof (SysMgrTouchPoint) * r->numTouchPoints);
			::memcpy(r->touchPoints, data, sizeof (SysMgrTouchPoint) * r->numTouchPoints);
		}

		return true;
	}
	
	static uint32_t Length(const param_type& p) {
		uint32_t len = sizeof(SysMgrTouchEvent) - sizeof(void*) + p.numTouchPoints * sizeof (SysMgrTouchPoint);
		return len;
	}
};	

#endif /* SYSMGRMOUSEEVENTTRAITS_H */
