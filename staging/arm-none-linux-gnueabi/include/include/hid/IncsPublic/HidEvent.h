// @@@LICENSE
//
//      Copyright (c) 2008-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

/** 
 *******************************************************************************
 * @file HidEvent.h
 * 
 * @brief Public header file for HID events.
 *******************************************************************************
 */

#ifndef __HID_EVENT_H
#define __HID_EVENT_H

#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <linux/input.h>

/** 
 * An EV_SYN event that is a flag to indicate that we've just started a plugin
 * and anything expecting us to be in a certain state should clear its state 
 */
#define SYN_START       8


/*
 * TODO: These don't get included from <linux/input.h> because the OE build
 * picks up the include files from the codesourcery toolchain, not our 
 * modified headers
 */
#ifndef SW_HEADPHONE_INSERT
    #define SW_HEADPHONE_INSERT         0x02
#endif

#ifndef SW_HEADPHONE_MIC_INSERT
    #define SW_HEADPHONE_MIC_INSERT	0x04
#endif

#ifndef SW_RINGER
    #define SW_RINGER                   0x5
#endif

#ifndef SW_SLIDER
    #define SW_SLIDER	                0x6
#endif

#ifndef SW_OPTICAL_SLIDER
    #define SW_OPTICAL_SLIDER           0x7
#endif

#ifndef KEY_SLIDER_OPEN
    #define KEY_SLIDER_OPEN     247
#endif

#ifndef KEY_SLIDER_CLOSE
    #define KEY_SLIDER_CLOSE     248
#endif

/* types */
#define EV_GESTURE      0x06
#define EV_FINGERID     0x07
#define EV_DEV_ID       0x08     
#define EV_DEV_ATTR     0x09


/*
 * The "value" reported by hidd when a headset with mic is inserted
 */
#define HID_HEADSET_MIC_VAL     2

/**
 * State of shake. value = SHAKE_START means start, SHAKE_END means stop
 */
#define MSC_SHAKE_STATE 0x05

#define SHAKE_START     0x01        /**< "value" for start shake */
#define SHAKE_END       0x00        /**< "value" for end shake */

/**
 * Magnitude of shake, where value = magnitude
 */
#define ABS_SHAKE       0x31


/* codes */
#define DEV_ID_ADD                 0x00
#define DEV_ID_REMOVE              0x01
#define DEV_ID_UPDATE              0x02

#define DEV_ATTR_COUNTRY           0x00
#define DEV_ATTR_TYPE              0x01

/* values */
#define DEV_TYPE_KEYBOARD          0x00
#define DEV_TYPE_MOUSE             0x01
#define DEV_TYPE_JOYSTICK          0x02

/*
 * Accelerometer orientations
 * 
 * TODO: This really doesn't belong here, but until the proper linux header
 * files are included by the build system this will have to do.
 */
#ifndef ABS_ORIENTATION
    #define ABS_ORIENTATION	    0x30
#endif

#ifndef ABS_MT_ORIENTATION
	#define ABS_MT_ORIENTATION	0x34
#endif

#ifndef ORIENTATION_UNKNOWN
    #define ORIENTATION_UNKNOWN	    0
#endif

#ifndef ORIENTATION_FACE_UP
    #define ORIENTATION_FACE_UP     1
#endif

#ifndef ORIENTATION_FACE_DOWN
    #define ORIENTATION_FACE_DOWN   2
#endif

#ifndef ORIENTATION_UP
    #define ORIENTATION_UP          3
#endif

#ifndef ORIENTATION_DOWN
    #define ORIENTATION_DOWN        4
#endif

#ifndef ORIENTATION_RIGHT
    #define ORIENTATION_RIGHT       5
#endif

#ifndef ORIENTATION_LEFT
    #define ORIENTATION_LEFT        6
#endif

#ifndef ABS_CONFIDENCE
	#define ABS_CONFIDENCE 0x80
#endif


// fusion types
#define EV_FUSION_MAGNETOMETER 0x18
#define EV_FUSION_HEADING 0x19
#define EV_FUSION_ACCEL 0x1A
#define EV_FUSION_QUATERNION 0x1B
#define EV_FUSION_ROTATION_MATRIX 0x1C
#define EV_FUSION_EULER_ANGLES 0x1D
#define EV_FUSION_LINEAR_ACCELERATION 0x1E
#define EV_FUSION_GRAVITY 0x1F
#define EV_FUSION_ANGULAR_VELOCITY 0x20
#define EV_FUSION_RAW 0x21
#define EV_FUSION_GYRO 0x22

// fusion codes
#define FUSION_MAGNETOMETER_X 0x01
#define FUSION_MAGNETOMETER_Y 0x02
#define FUSION_MAGNETOMETER_Z 0x03

#define FUSION_HEADING_DEG 0x01

#define FUSION_ACCEL_X 0x01
#define FUSION_ACCEL_Y 0x02
#define FUSION_ACCEL_Z 0x03

#define FUSION_QUATERNION_W 0x01
#define FUSION_QUATERNION_X 0x02
#define FUSION_QUATERNION_Y 0x03
#define FUSION_QUATERNION_Z 0x04

#define FUSION_ROTATION_MATRIX_R11 0x01
#define FUSION_ROTATION_MATRIX_R12 0x02
#define FUSION_ROTATION_MATRIX_R13 0x03
#define FUSION_ROTATION_MATRIX_R21 0x04
#define FUSION_ROTATION_MATRIX_R22 0x05
#define FUSION_ROTATION_MATRIX_R23 0x06
#define FUSION_ROTATION_MATRIX_R31 0x07
#define FUSION_ROTATION_MATRIX_R32 0x08
#define FUSION_ROTATION_MATRIX_R33 0x09

#define FUSION_EULER_ANGLE_ROLL 0x01
#define FUSION_EULER_ANGLE_PITCH 0x02
#define FUSION_EULER_ANGLE_YAW 0x03

#define FUSION_LINEAR_ACCELERATION_X 0x01
#define FUSION_LINEAR_ACCELERATION_Y 0x02
#define FUSION_LINEAR_ACCELERATION_Z 0x03

#define FUSION_LINEAR_ACCELERATION_WX 0x01
#define FUSION_LINEAR_ACCELERATION_WY 0x02
#define FUSION_LINEAR_ACCELERATION_WZ 0x03

#define FUSION_GRAVITY_X 0x01
#define FUSION_GRAVITY_Y 0x02
#define FUSION_GRAVITY_Z 0x03

#define FUSION_ANGULAR_VELOCITY_X 0x01
#define FUSION_ANGULAR_VELOCITY_Y 0x02
#define FUSION_ANGULAR_VELOCITY_Z 0x03

#define FUSION_RAW_GYRO_X 0x01
#define FUSION_RAW_GYRO_Y 0x02
#define FUSION_RAW_GYRO_Z 0x03

#define FUSION_RAW_ACCEL_X 0x01
#define FUSION_RAW_ACCEL_Y 0x02
#define FUSION_RAW_ACCEL_Z 0x03

#define FUSION_RAW_COMPASS_X 0x01
#define FUSION_RAW_COMPASS_Y 0x02
#define FUSION_RAW_COMPASS_Z 0x03

#define FUSION_GYRO_X 0x01
#define FUSION_GYRO_Y 0x02
#define FUSION_GYRO_Z 0x03


/**
 * This is modeled after the linux input event interface events.
 * See linux/input.h for the original definition.
 */
typedef struct InputEvent 
{
    struct timeval time;  /**< time event was generated */
    uint16_t type;        /**< type of event, EV_ABS, EV_MSC, etc. */
    uint16_t code;        /**< event code, ABS_X, ABS_Y, etc. */
    int32_t value;        /**< event value: coordinate, intensity,etc. */
} InputEvent_t;

/**
 * This struct allows us to add additional information to the events
 */
typedef struct DebugEvent
{
    InputEvent_t event;     /**< event */
    struct timeval time;    /**< extra time stamp for timing */
} DebugEvent_t;

/**
 * Distinguish between the various event formats. 
 * e.g., the normal Linux input event will be a struct input_event, but
 *       other devices may report things in a different manner
 */
typedef enum {
    kInputEvent,    /**< standard linux struct input_event */
    kCustomEvent1,  /**< device 1 event format */
    kCustomEvent2,  /**< another event format */
    kDebugEvent,    /**< format for debugging */
} EventType_t;

inline size_t HidGetEventTypeSize(EventType_t type);
inline InputEvent_t* HidGetInputEventMember(void* pEvent, EventType_t type, int index);
inline const char* HidGetInputEventTypeString(uint16_t type);

#endif  /* __HID_EVENT_H */
