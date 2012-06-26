//  @@@LICENSE
//
//      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  LICENSE@@@

#ifndef HDATAWRITER_H_
#define HDATAWRITER_H_

#include "HCommon.h"
#include "HData.h"

// Use HDataWriter to stream data into a buffer. Note: You MUST call one of the init functions
// before doing any other operations.

struct HEXPORT HDataWriter
{
	HDataWriter();
	~HDataWriter();

	// init using a freshly allocated internal HData structure
	void init();

	// init using the sent-in HData structure. Note that the allocation size of the sent-in structure may grow
	void init(HData *toUse);

	// return an HData with the accumnulated buffer. This ends the use of this instance of HDataWriter.
	// All future calls will be ignored. The HData you get back from this will be your responsibility
	// to deallocate with HData_free(). Note that if you initted with init(HData *) the returned HData will
	// be the one you sent in in the first place.
	// the only time HDataWriter deallocates anything is if you never call getData *and* you initted with init().
	// Note - returns NULL if there was an error during writing at any point.
	HData *getData();

	// the various ways to pile data in to the buffer
	// these all return true on success, false on failure
	bool writeInt(int toWrite);
	bool writeChar(char toWrite);
	bool writeBool(bool toWrite);
	bool writeDouble(double toWrite);
	bool writeStr(const char *toWrite);
	bool writeData(const void *data, int len);

	// returns false if there were any errors at any time since the last call to an init() function.
	// handy if you just want to check at the end of a bunch of writes, rather than after each write
	bool isSuccessful();

protected:
	bool writeType(int type);
	bool doWriteData(const void *data, int len);
	bool doWriteSizedData(const void *data, int len);
	void clear(); // internal

	bool m_bOwnData;
	HData *m_data;
	int m_pos; // offset to the next location to write within the data

	bool m_bIsSuccessful;
};

#endif



