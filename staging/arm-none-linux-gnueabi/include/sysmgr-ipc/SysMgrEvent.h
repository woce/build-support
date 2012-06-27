/**
 *  Copyright (c) 2008 - 2012 Hewlett-Packard Development Company, L.P.
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


#ifndef SYSMGREVENT_H
#define SYSMGREVENT_H

#include <stdint.h>
#include <stdio.h>

#include <webosDeviceKeymap.h>

// This is a data only struct. Don't put any virtual
// functions in here.
struct SysMgrEvent
{
	enum EventMasks {
		KeyMask = 1 << 16,
		PenMask = 1 << 17,
		GestureMask = 1 << 18,
		OtherMask = 1 << 19
	};
	
	enum Type {
		InvalType = 0,
		KeyDown = KeyMask,
		KeyUp,
		PenDown = PenMask,
		PenUp,
		PenMove,
		PenFlick,
		PenPressAndHold,
		PenCancel,    // Canceling the "main" finger due to pre-emption by another finger
		PenCancelAll, // Cancelling all fingers
		PenSingleTap, //An additional "Up" event is sent if this tap no longer can generate a doubletap.
		GestureStart = GestureMask,
		GestureChange,
		GestureEnd,
		GestureCancel,
		Accelerometer = OtherMask,
		Light,
		Proximity,
		Shutdown,
		Compass,
		Gyro,
		User	  = 0xFF000000,
		LastType  = 0xFFFFFFFF
	};

	enum Button {
		InvalButton = 0,
		Left        = 1 << 0,
		Middle      = 1 << 1,
		Right       = 1 << 2,
		LastButton  = 1 << 31
	};

	enum Modifier {
		InvalModifier = 0,
		Shift        = 1 << 0,
		Control      = 1 << 1,
		Alt          = 1 << 2,
		Option       = 1 << 3,	// "Sym" on evt2, "Opt" on evt1
		InitialState = 1 << 4,	// Reporting initial state of "key" (switch)
		Meta         = 1 << 5, 	// Computed from core navi area.
		LastModifier = 0xFFFF
	};

	enum Attributes {
		Clicked       = 1 << 0,
		Rejected      = 1 << 1,
		MainFinger    = 1 << 2,
		GestureKey    = 1 << 3,
		LastAttribute = 0xFFFF
	};

	// Look in the luna-keymap-headers package
	#include <webosDeviceKeydefs.h>

	enum Orientation {
		Orientation_Invalid = 0,
		Orientation_FaceUp,
		Orientation_FaceDown,
		Orientation_Up,
		Orientation_Down,
		Orientation_Left,
		Orientation_Right,
		Orientation_Landscape,
		Orientation_Portrait,
		Orientation_Last = 1 << 31
	};	

	enum Shake {
		Shake_Invalid = 0,
		Shake_Start,
		Shake_Shaking,
		Shake_End,
		Shake_Last = 1 << 31
	};

	Type type;

	union {	
		struct {
			int x;
			int y;
			int z;

			int flickXVel;
			int flickYVel;

			Button button;
			int	clickCount; // clickCount is a misnomer, 1 for one press, 2 for double press, ...
		};

		struct {		
			float floatX;
			float floatY;
			float floatZ;
	
			Orientation orientation;
			float pitch;
			float roll;

			Shake shakeState;
			float shakeMagnitude;
		};

		struct {
			float gestureScale;
			float gestureRotate;

			int gestureCenterX;
			int gestureCenterY;
		};
		
		struct {
			float mx;
			float my;
			float mz;
			int mg;

			float ax;
			float ay;
			float az;

			int confidence;

			float mag_bearing;
			float true_bearing;
		};
	};
		
	Key      key;
	uint16_t modifiers;
	uint16_t attributes;
	uint32_t time;
	uint32_t id;
	bool     simulated;
};


struct SysMgrEventWrapper
{
	SysMgrEventWrapper()
		: event(0) {}

	SysMgrEventWrapper(SysMgrEvent* evt)
		: event(evt) {}

	SysMgrEvent* event;
};	

#endif // SYSMGREVENT_H
