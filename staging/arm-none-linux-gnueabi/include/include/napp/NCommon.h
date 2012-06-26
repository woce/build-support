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
#ifndef NCOMMON_H
#define NCOMMON_H

#include "helpers/HTracker.h"

#ifdef __cplusplus
	class HDataWriter;
	class HDataReader;
#endif

typedef enum 
{
    NKeypad,
    NUnused,
    NTouchpanel,
    // Insert more here
    
    NNumDevices
    
} NInputDevice;

typedef enum 
{
    NActivate = 10,
    NDeactivate,
    NDeactivateAck,
    NBufferUpdate,
    NBufferUpdateAck,
    NEventEnable,
    
} NMessageType;

typedef struct
{
    NMessageType Type;
    
} NMessageBuffer;

typedef void (*NActivateCbTy)(void* UserData, int Active);
typedef void (*NInputEventCbTy)(void);
typedef void (*NQuitCbTy)(void);
typedef void (*NFocusedCbTy)(int Focused);
typedef void (*NPausedCbTy)(int Paused);
typedef void (*NResizeCbTy)(int newW, int newH);

// called by NApp to tell PDL about compass changes
typedef void (*NCompassCbTy)(int confidence, double magneticBearing, double trueBearing);

#ifdef __cplusplus
	typedef bool (*NApp_GetMethodsCB) (HDataWriter *out);
	typedef int (*NApp_MojoCB) (HDataReader *in, HDataWriter *out);
#endif
// Deprecated
typedef void (*NOverlayCbTy)(int Active);

#ifdef __arm__
#define NTRAP (*(volatile unsigned int*)0x0 = 99)
#else
#define NTRAP asm("int $3")
#endif

#if defined(NDEBUG)
#include <stdio.h>

#define NASSERT(x, format, ...) if (!(x)) do {   \
    printf("ASSERT [%s:%d] ", __FILE__, __LINE__);         \
    printf(format, ## __VA_ARGS__);                        \
    printf("\n");                                          \
    NTRAP;                                                 \
} while (0)

#define NTRACE(format, ...) do {                        \
    printf("[%s:%4d] ", __FILE__, __LINE__ );           \
    printf(format, ## __VA_ARGS__);                     \
    printf("\n");                                          \
} while(0)

#endif

#ifndef NASSERT
#define NASSERT(x, format, ...) do {} while (0)
#endif

#ifndef NTRACE
// changing to use tracker
// #define NTRACE(format, ...) do {} while (0)
#define NTRACE(format, ...) HTracker_track("napp_ntrace", format, ## __VA_ARGS__)

#endif

#define NEXPORT    __attribute__((visibility("default")))

#endif /* NCOMMON_H */
