/* ============================================================
 * Date  : 2008-09-24
 * Copyright 2008 Palm, Inc. All rights reserved.
 * ============================================================ */

#ifndef WEBOSWEBTYPES_H
#define WEBOSWEBTYPES_H

#include <string>
#include <list>
#include <stdint.h>
#include "palmwebdefines.h"

namespace Palm
{

struct WEBKIT_API WebRect {
	int left;
	int top;
	int right;
	int bottom;
};

struct WEBKIT_API WebSmartZoomBox {
	WebRect rect;
	double scale;
	int contentX;
	int contentY;
};

enum ShakeEventType {
    ShakeInvalid = -1,
    ShakeStart,
    Shaking,
    ShakeEnd
};

enum GestureEventType {
	GestureStart,
	GestureChange,
	GestureEnd,
	GestureSingleTap
};

enum TouchEventType {
	TouchStart,
    TouchMove,
    TouchEnd,
    TouchCancel
};

enum SensorType {
    SensorInvalid,
    SensorAcceleration,
    SensorOrientation,
    SensorShake,
    SensorBearing,
    SensorALS,
    SensorAngularVelocity,
    SensorGravity,
    SensorLinearAcceleration,
    SensorMagneticField,
    SensorScreenProximity,
    SensorRotation,
    SensorLogicalDeviceOrientation,
    SensorLogicalDeviceMotion,
    SensorLast
};

/** Sensor Names */
class SensorNames
{
public:
    static const char* strAccelerometer()               { return "accelerometer"; }
    static const char* strOrientation()                 { return "orientation"; }
    static const char* strShake()                       { return "shake"; }
    static const char* strALS()                         { return "als"; }
    static const char* strAngularVelocity()             { return "angularVelocity"; }
    static const char* strBearing()                     { return "bearing"; }
    static const char* strGravity()                     { return "gravity"; }
    static const char* strLinearAcceleration()          { return "linearAcceleration"; }
    static const char* strMagneticField()               { return "magneticField"; }
    static const char* strScreenProximity()             { return "screenProximity"; }
    static const char* strRotation()                    { return "rotation"; }
    static const char* strLogicalDeviceMotion()         { return "logicalDeviceMotion"; }
    static const char* strLogicalDeviceOrientation()    { return "logicalDeviceOrientation"; }
};

/**
 * HAL Json Strings
 */
class HALJsonStringConst
{
public:
    static const char* strW()                       { return "w"; }
    static const char* strX()                       { return "x"; }
    static const char* strY()                       { return "y"; }
    static const char* strZ()                       { return "z"; }
    static const char* strRawX()                    { return "rowX"; }
    static const char* strRawY()                    { return "rowY"; }
    static const char* strRawZ()                    { return "rowZ"; }
    static const char* strWorldX()                  { return "worldX"; }
    static const char* strWorldY()                  { return "worldY"; }
    static const char* strWorldZ()                  { return "worldX"; }
    static const char* strPosition()                { return "position"; }
    static const char* strShakeState()              { return "shakeState"; }
    static const char* strShakeMagnitude()          { return "shakeMagnitude"; }
    static const char* strShakeStart()              { return "Start"; }
    static const char* strShaking()                 { return "Shaking"; }
    static const char* strShakeEnd()                { return "End"; }
    static const char* strRotationMatrix()          { return "rotationMatrix"; }
    static const char* strQuaternionVector()        { return "quaternionVector"; }
    static const char* strEulerAngle()              { return "eulerAngle"; }
    static const char* strRoll()                    { return "roll"; }
    static const char* strPitch()                   { return "pitch"; }
    static const char* strYaw()                     { return "yaw"; }
    static const char* strLightIntensity()          { return "lightIntensity"; }
    static const char* strMagnetic()                { return "magnetic"; }
    static const char* strTrueBearing()             { return "trueBearing"; }
    static const char* strConfidence()              { return "confidence"; }
    static const char* strOrientationFaceUp()       { return "Face Up"; }
    static const char* strOrientationFaceDown()     { return "Face Down"; }
    static const char* strOrientationFaceForward()  { return "Face Forward"; }
    static const char* strOrientationFaceBack()     { return "Face Back"; }
    static const char* strOrientationLeft()         { return "Left"; }
    static const char* strOrientationRight()        { return "Right"; }
    static const char* strEmpty()                   { return ""; }
};

enum SensorRate {
    RATE_DEFAULT = 0,
    RATE_LOW,
    RATE_MEDIUM,
    RATE_HIGH,
    RATE_HIGHEST
};

struct TouchPointPalm {
	enum State {
		TouchReleased,
		TouchPressed,
		TouchMoved,
		TouchStationary,
		TouchCancelled
	};

	TouchPointPalm()
		: id(0)
        , x(0)
		, y(0)
		, state(TouchStationary)
		{ }

	TouchPointPalm(unsigned _id, State st, int screen_x, int screen_y)
		: id(_id)
        , x(screen_x)
		, y(screen_y)
		, state(st)
		{ }

    unsigned id;
	int x;
	int y;
	State state;
};


enum TextCaretType {
	TextCaretNormal,
	TextCaretShift,
	TextCaretShiftLocked,
	TextCaretAlt,
	TextCaretAltLocked		
};

enum MouseEventType {
	MouseDown,
	MouseUp,
	MouseMove
};

/**
 * The mode when mouse down/move/up events are received.
 */
enum MouseMode {
	/** Select contents of page. */
	MouseModeSelect = 0,
	/** Scroll node at mouse */
	MouseModeScroll = 1
};

enum InteractiveRectType {
    InteractiveRectDefault,
    InteractiveRectPlugin  //< Interactive rect is a plugin rect
};

/**
 * All the data for a single menu item.
 */
struct PopupMenuItem
{
	std::string	title; ///< The item title (can be empty).
	bool isEnabled;    ///< true if item is enabled.
	bool isSeparator;  ///< true if item is a separator.
	bool isLabel;      ///< true if item is a label.
};

/**
 * All the data for a popup menu.
 */
struct PopupMenuData
{
	std::list<PopupMenuItem*> items;
	int	selectedIdx;

	PopupMenuData() : selectedIdx(0) {}
	virtual ~PopupMenuData()
	{
		std::list<PopupMenuItem*>::iterator i;
		for (i = items.begin(); i != items.end(); ++i) {
			delete *i;
		}
	}
};

struct WEBKIT_API ScrollableBarData
{
    int value;
    int visible;
    int total;
};

struct WEBKIT_API ScrollableLayerItem
{
    uintptr_t id;
    WebRect absoluteBounds;
    bool hasHorizontalBar;
    bool hasVerticalBar;
    ScrollableBarData horizontalBarData;
    ScrollableBarData verticalBarData;
};

// handle to the opaque Sensor data
typedef void * SensorHandle;

/**
 * Sensor data Callback function
 *
 * @param aType     : Sensor Type
 * @param aJsonData : Valid Sensor Data, "" otherwise
 * @param pUserData : User data
 */
typedef void (*fnSensorDataCallback)(SensorType aType, std::string& aJsonData, void *pUserData);

/**
 * Sensor error Callback function
 *
 * @param aType             : Sensor Type
 * @param aErrorDescription : Error Description
 * @param pUserData         : User data
 */
typedef void (*fnSensorErrorCallback)(SensorType aType, std::string& aErrorDescription, void *pUserData);

/**
 * Sensor Object deletion function
 *
 * @param apHandle  : Pointer to the sensor handle object
 */
typedef void (*fnSensorHandleDelete)(SensorHandle* apHandle);
}

#endif /* WEBOSWEBTYPES_H */
