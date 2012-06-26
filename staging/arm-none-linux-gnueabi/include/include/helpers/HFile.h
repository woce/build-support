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

#ifndef __HFILE__
#define __HFILE__

#include "HData.h"
#include "HString.h"

#ifdef __cplusplus
extern "C" {
#endif

// open a file, and load all the data in to the sent-in buffer
// returns 0 on success. returns 1 if it couldn't find the file or
// if the buffer was too small to hold the contents. If you want to know the size
// of the file, call HFile_getFileSize
int HFile_getFileContentsToBuffer(const char *filePath, void *buffer, int bufferLen);

// open a file, allocate memory to hold the data, then load the data
// returns a pointer to the file. The HData will be an allocation exactly large
// enough to hold the file data. In other words, You can use the allocSize
// field of the returned HData structure to find out the size of the file you just loaded
// alternately you could call HFile_getFileSize.
//
// ALLOCATION: This allocates an HData structure that you must eventually
// free with HData_free().
HData *HFile_getFileContents(const char *filePath);

// loads the file contents in to an HString
HString *HFile_getFileContentsAsString(const char *filePath);

// get the number of bytes in the file. returns -1 if the file can not be found
int HFile_getFileSize(const char *filePath);

// returns 1 if the file exists; 0 if it does not
int HFile_fileExists(const char *filePath);


#ifdef __cplusplus
}
#endif


#endif

