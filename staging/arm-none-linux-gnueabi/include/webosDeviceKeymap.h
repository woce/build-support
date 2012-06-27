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

#ifndef __webosDeviceKeymap_h__
#define __webosDeviceKeymap_h__

typedef struct {
	int devicekey;
	int normal;			// keycode if no modifiers
	int shift;			// keycode if shift
	int opt;			// keycode if opt/sym
	int qtKey;
	int qtKeyOpt;
	int virtualkeycode; // VK_
} KeyMapType;

#define LAST_KEY			(0xffffffff)

typedef enum KeyLayoutType {
	KeyLayoutTypeQwerty,
	KeyLayoutTypeAzerty,
	KeyLayoutTypeQwertz,
	KeyLayoutTypeQwertzDe,
	KeyLayoutTypeAzertyFr,
	KeyLayoutTypeQwertyEvt1,
} KeyLayoutType;

enum KeyMapDevice {
	DeviceCastle,
	DevicePixie,
	DeviceWindsor,
	DeviceBroadway,
	DeviceGtk,
	DeviceQemu,
	DeviceMantaray,
	DeviceTwain,
	DeviceLast
};

#ifdef __cplusplus
 extern "C" {
#endif
	
const KeyMapType* webosGetDeviceKeymap( void );
/// For testing purposes only. Apps should use webosGetDeviceKeymap and let the lib select keymap.
const KeyMapType* webosGetDeviceKeymapForDevice( KeyMapDevice device, KeyLayoutType keyboard );
KeyLayoutType webosGetKeyLayoutType( void );

#ifdef __cplusplus
}
#endif

#endif // __webosDeviceKeymap_h__

