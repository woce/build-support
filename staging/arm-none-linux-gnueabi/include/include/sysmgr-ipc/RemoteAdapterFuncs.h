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

#ifndef __REMOTEADAPTERFUNCS__
#define __REMOTEADAPTERFUNCS__

#include "RemoteAdapterTypes.h"

// simple function to return a string for an IPC code
const char *ipcCodeToStr(int code)
{
	switch ( code )
	{
		case IPC_ERROR: return "IPC_ERROR";
		case IPC_SET_WINDOW: return "IPC_SET_WINDOW";
		case IPC_PAINT: return "IPC_PAINT";
		case IPC_WINDOW_BUFFER_ACK: return "IPC_WINDOW_BUFFER_ACK";
		case IPC_KEYDOWN: return "IPC_KEYDOWN";
		case IPC_KEYUP: return "IPC_KEYUP";
		case IPC_PENDOWN: return "IPC_PENDOWN";
		case IPC_PENUP: return "IPC_PENUP";
		case IPC_PENMOVE: return "IPC_PENMOVE";
		case IPC_GET_METHODS: return "IPC_GET_METHODS";
		case IPC_CUSTOM_METHOD: return "IPC_CUSTOM_METHOD";
		case IPC_TERMINATE: return "IPC_TERMINATE";
		case IPC_JSCALL: return "IPC_JSCALL";
		case IPC_INVALIDATE: return "IPC_INVALIDATE";
		case IPC_RESPONSE: return "IPC_RESPONSE";
		case IPC_METHODLIST: return "IPC_METHODLIST";
	}
	return "UNKNOWN IPC CODE";
}
	
#endif
