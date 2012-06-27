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

#ifndef HDATAREADER_H_
#define HDATAREADER_H_

#include "HCommon.h"
#include "HData.h"

// Use HDataWriter to stream data into a buffer. Note: You MUST call one of the init functions
// before doing any other operations.

struct HEXPORT HDataReader
{
	HDataReader();
	~HDataReader();

	// init with an HData. Remember HDatareader *never* owns allocations. Returns false
	// if the buffer is corrupt
	bool init(HData *data);

	// init with a pointer. len is the length of the valid data stored therein. Remember HDatareader *never* owns allocations
	// Returns false if the buffer is corrupt
	bool init(void *data, int len);

	// the various ways to get data in from the buffer. If there's
	// an error, they will return a default value, and you can detect it with
	// isSuccessful() when you want
	int readInt();
	char readChar();
	bool readBool();
	double readDouble();
	void readStr(char *buffer, int bufferLen);
	char *allocReadStr(); // allocates memory by using new[]. You are responsible for deleting it with delete[]
	void readData(void *buffer, int bytesToRead);

	// returns false if there were any errors at any time since the last call to an init() function.
	// handy if you just want to check at the end of a bunch of reads, rather than after each read
	bool isSuccessful();

	// potentially helpful debugging tool. Dumps a text description of the
	// entire data set tracking
	void dumpInfo(const char *category); // non-static version to dump this instance's data
	static void dumpInfo(const char *category, void *data, int len);
	static void dumpInfo(const char *category, HData *data);


protected:
	void doDumpInfo(const char *category);
	void internalDumpInfo(const char *category);
	void checkIdent();
	int readType();
	void doReadData(void *buffer, int bytesToRead);
	bool confirmType(int type);

	unsigned char *m_data;
	int m_pos; // offset to the next location to read within the data
	int m_dataLen;
	bool m_bIsSuccessful;
};

#endif



