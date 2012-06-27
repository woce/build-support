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

#ifndef __REMOTEADAPTERTYPES__
#define __REMOTEADAPTERTYPES__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
	
// message types
// error message. will contain a string
#define IPC_ERROR	 			-1
	
// standardized messages from AdapterBase
#define IPC_SET_WINDOW 			10001
#define IPC_PAINT 				10002
#define IPC_WINDOW_BUFFER_ACK 	10003
#define IPC_KEYDOWN			 	10004
#define IPC_KEYUP				10005
#define IPC_PENDOWN 			10006
#define IPC_PENUP 				10007
#define IPC_PENMOVE 			10008

// custom messages used by remote adapter
#define IPC_GET_METHODS 		11001
#define IPC_CUSTOM_METHOD 		11002
#define IPC_TERMINATE 			11003
	
// messages FROM the native app to remote-adapter
#define IPC_JSCALL	 			12001
#define IPC_INVALIDATE 			12002
#define IPC_METHODLIST 			12003

// response message for a blocking call
#define IPC_RESPONSE	 		13001
	
struct IPCBuffer
{
	IPCBuffer() 
	{ 
		buffer = NULL;
		bufferLen = 0;
	}
	
	IPCBuffer(const IPCBuffer &copy) 
	{ 
		buffer = NULL;
		bufferLen = 0;
		set(copy.buffer, copy.bufferLen);
	}
	
	~IPCBuffer() 
	{ 
		if ( buffer != NULL )
		{
			delete[] buffer;
			buffer = NULL;
		}
		bufferLen = 0;
	}
	
	IPCBuffer &operator=(const IPCBuffer &in)
	{
		// copy it all over, making our own duplicate
		set(in.buffer, in.bufferLen);
		return *this;
	}
	
	void set(void *val, int len)
	{
		// kill any old allocations
		if ( buffer != NULL )
		{
			delete[] buffer;
		}
		
		// copy over the data
		buffer = new char[len];
		bufferLen = len;
		memcpy(buffer, val, len);
	}
	
	void *get() const
	{
		return buffer;
	}
	
	int length() const
	{
		return bufferLen;
	}
	
	char *buffer;
	int bufferLen;
};
	
// used for messages that don't presently require data
typedef struct NpReserved
{
	int32_t reserved;  
} NpReserved;

// used in all generic transport messages
typedef struct NpPalmGeneric
{
	int type;
	IPCBuffer buffer;
} NpPalmGeneric;

// this structure is at the front of the shared pixmap buffer. 
// the Vaddr() function returns the pointer to the byte *after*
// this structure in the actual allocated memory. This structure is
// used internally in NApp, and references in remote-adapter
typedef struct NPixmapHeader
{
	int m_headerSize; // size of this header
	int m_width; // pxmap width
	int m_height; // pxmap height
	int m_pitch; // pxmap pitch
	
	// these values are the values that were in play the last time
	// the pixels were updated. These should be used for wrapping
	// in to a surface
	int m_lastUpdateWidth;
	int m_lastUpdateHeight;
	int m_lastUpdatePitch;
	
} NPixmapHeader;

#ifdef __cplusplus
}
#endif

#endif


