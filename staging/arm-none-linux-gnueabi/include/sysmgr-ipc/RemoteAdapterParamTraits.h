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


#ifndef REMOTEADAPTERPARAMTRAITS_H
#define REMOTEADAPTERPARAMTRAITS_H

#include <string.h>
#include "PIpcMessageUtils.h"

// NpPalmGeneric - dynamic sized data transport
template <> struct ParamTraits<NpPalmGeneric> 
{ 
	static void Write(PIpcMessage* m, const NpPalmGeneric& p) 
	{ 
		m->writeInt32(p.type);
		
		// write out the buffer
		size_t len = p.buffer.length(); 
		m->writeSize(len); 
		void *str = p.buffer.get(); 
		m->writeBytes(str, len); 
	}
	
	static bool Read(const PIpcMessage* m, NpPalmGeneric* r) 
	{ 
		if (!m->readInt32(&(r->type))) return false;
		
		// read in the buffer
		size_t len;
		if ( !m->readSize(&len) ) return false;
		char* data;
		if (!m->readBytes((const char**) &data, len)) 
		{ 
			return false; 
		} 
		r->buffer.set(data, len);
		
		return true; 
	} 
	
	static uint32_t Length(const NpPalmGeneric& p) 
	{
		// start with the length of the type value
		uint32_t ret = Pickle::lengthOf(p.type); 
		
		// add the length of the buffer
		size_t len;
		ret += Pickle::lengthOf(len);
		len = p.buffer.length();
		ret += Pickle::lengthOf((const char *)p.buffer.get(), len);
		
		return ret;
	} 
};

#endif // REMOTEADAPTERPARAMTRAITS_H
