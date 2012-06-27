/* @@@LICENSE
*
*      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */

#ifndef NAPP_C_H
#define NAPP_C_H

/* C interface to NApp */
#ifdef __cplusplus
extern "C" 
{
#endif

#include "NCommon.h"

#include <linux/input.h>
	
/* Validated to be equal to webOS keys by compile time assert */    
#define NAPP_KEY_SHIFT      0x80
#define NAPP_KEY_ALT        0x81
#define NAPP_KEY_CTRL       0x82
#define NAPP_KEY_OPTION     0x83

// these are the keycodes we get from the system
#define NAPP_GESTURE_AREA    0xE0E7
#define NAPP_GESTURE_BACK    0x1B
#define NAPP_GESTURE_FORWARD 0xE0E5

// palm-specific SDL-usable keycodes. We send these along to the client app
#define SDLK_EX_GESTURE_AREA    0xE7
#define SDLK_EX_GESTURE_BACK    0x1B
#define SDLK_EX_GESTURE_FORWARD 0xE5
#define SDLK_EX_GESTURE_DISMISS_KEYBOARD 0x18
	
// errors that NAPP can return
#define NAPP_NOERROR 1
#define NAPP_ERROR 0
#define NAPP_STRINGTOOSMALL 100
#define NAPP_PARSEERROR 101
#define NAPP_APPINFO 102
	
// values returned by NApp_GetGfxInitState
#define NAPP_GFXINIT_UNKNOWN (-1)    // The init state has not been initted
#define NAPP_GFXINIT_PLUGIN 0        // initting as a plugin for the first time
#define NAPP_GFXINIT_NATIVE 1        // Initting as native for the first time
#define NAPP_GFXINIT_PLUGINRETURN 2  // returning to plugin mode after having been native for a while 
#define NAPP_GFXINIT_NATIVERETURN 3  // returning to native mode after having been plugin, then returned to native 

	
int     NApp_Init(NQuitCbTy Callback);
int 	NApp_PrepForFullscreen(void); // creates the LSM IPC when in plugin mode. Used when fullscreening a plugin
int 	NApp_ReturnToPlugin(void); // Returns to plugin mode from fullscreened-plugin mode
void    NApp_Quit(void);

int		NApp_ConfirmIPCConnection();
int 	NApp_GetPortalSize(int hardwareWidth, int hardwareHeight, int *portalWidth, int *portalHeight);
int 	NApp_GetRatioedPositions(int pixelX, int pixelY, float *ratioX, float *ratioY);
int     NApp_CreateWindow(int Width, int Height, int BytesPerPixel, int Offscreen, void** WindowHandle);

/* Returns NPixmap object */
void*   NApp_OffscreenLock(void** Buffer, int* SizeInBytes);
void    NApp_OffscreenUnlock(int Updated);

int     NApp_GetInputEventFd(NInputDevice Device);
int     NApp_ReadEvents(NInputDevice Device, struct input_event* Event, int MaxEvent);
// void    NApp_EnableEvent(NInputDevice Device, int Enable);

void    NApp_RegisterActivateCb(NActivateCbTy Callback, void* UserData);
void    NApp_RegisterFocusedCb(NFocusedCbTy Callback);
void    NApp_RegisterPausedCb(NPausedCbTy Callback);
void    NApp_RegisterResizeCb(NResizeCbTy Callback);

void    NApp_EnterEventLoop(NInputEventCbTy Callback);
void    NApp_QuitEventLoop(void);

int     NApp_ScreenTimeoutEnable(int Enable);
int     NApp_GesturesEnable(int Enable);
int 	NApp_SetOrientation(const char *Orientation);
int 	NApp_BannerMessagesEnable(int Enable);
int     NApp_CustomPauseUiEnable(int Enable);
int		NApp_SetTouchAggression(int aggression); // note -- Send -1 to set to system default
int		NApp_EnableCompass(int compassOn); // 1 = enabled, 0 = disabled

void    NApp_LayerEnable(int Enable, int Fd);

int		NApp_CheckLicense(); // returns 1 if the license is valid, 0 if it is not

void 	NApp_SetGfxInitState(int state); // expects a NAPP_GFXINIT_XXXX constant. 
int 	NApp_GetGfxInitState(); // returns a NAPP_GFXINIT_XXXX constant
int		NApp_LaunchedAsPlugin(); // returns 1 if the3 app was *launched* as a plugin
int		NApp_IsCurrentlyPlugin(); // returns 1 if the app is *currently* a plugin
int		NApp_IsFullscreenedPlugin(); // returns 1 if the app was launched as a plugin and is currently fullscreen.
int		NApp_IsPluginEx(); // returns 1 if the environment variables from remote-adapter are present. Can tell if the app will be a plugin even before the IPC is set up.

int		NApp_IsKillTransparency(); // returns 1 if transparency should be stripped, 0 if transparency should be preserved

#ifdef __cplusplus
	int		NApp_RegisterMojoHandlers(NApp_GetMethodsCB getMethodsCB, NApp_MojoCB mojoCB); // returns 1 on success, 0 on failure
#endif
	
int		NApp_JSCall(const char *function, const char **args, int argCount);
int		NApp_Minimize();
	
// used for restricted c-interfaces (like within SDL) to send fire and forget LS Calls
int		NApp_lsFireAndForget(const char *uri, const char *payload, int isPrivate);	

// returns nonzero if "resolution=..." is set in the appinfo file. Returns 0 if it is not.
// value is cached - this can be called in high-performance areas.
int 	NApp_IsResolutionScaling(void);

// returns the resolution scaling in progress. If "resolution=..." is not set in the appinfo
// file, it does not modify the sent-in values. returns nonzero if resolution scaling is in
// progress, sero if not. 
// values are cached - this can be called in high-performance areas.
int 	NApp_GetResolutionScaling(int *width, int *height);

// gives you the pixel size of the screen hardware. Nothing to do with the software
// or the os or anything else. This is the width and height of the actual hardware screen
// fills out the values. returns 1 on success, 0 on failure.
int		NApp_GetHardwareResolution(int *outWidth, int *outHeight);

// returns scale, rotation flag, and dy/dx factors to fit a window of the given size on the display
int     NApp_FitRectOnDisplay(int WindowWidth, int WindowHeight, float* Scale, int* Rotated, int* Dy, int* Dx);
    
// adjusts a touch event to compensate for scaling and centering; Outside set if the touch is outside the window
int     NApp_AdjustTouchEvent(int* X, int* Y, int* Outside);
    
// bring up or dismisses the software keyboard
int		NApp_SetKeyboardState(int visible);

// functions implemented in NPaths.cpp
int 	NApp_GetDataFilePath(const char *dataFileName, char *buffer, int bufferLen);
int 	NApp_GetAppinfoValue(const char *name, char *buffer, int bufferLen);
int 	NApp_GetJsonValue(const char *jsonStr, const char *valueName, char *outBuffer, int outBufferLen);
int 	NApp_GetProcSelfExe(char *callPath, int size); // returns the length of the path string it put in to the buffer.

// sound pause management
// nonzero means automatically pause sounds. 0 means don't. Defaults to 1.
int 	NApp_SetAutomaticSoundPausing(int automaticallyPause); // returns nonzero on success, 0 on failure.  
int 	NApp_GetAutomaticSoundPausing(void); 

// access for portability layer values. Returns a const char * to an internally 
// managed buffer. Returns NULL if the field doesn't exist
const char *NApp_GetPortabilityValue(const char *name);

// calld by SDL when the window size is known.
void NApp_SetPortabilityWindowStats(int width, int height, int isOGL);

// sets affinity of the calling thread to the given cpu    
int     NApp_SetProcAffinity(int tid, int cpu);
    

#ifdef __cplusplus
}
#endif

#endif
