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

#ifndef __HLOGGER__
#define __HLOGGER__


#ifdef __cplusplus
extern "C" {
#endif

// this is the maximum size a single log output line can be
// if you exceed this with creative print formatting, you will
// crash the logger.
#define MAX_BUFFER_SIZE 16384

// simplest use. Requires no setup. Just give it a full path
// and what to append to that file. If you send NULL for
// the file name, it will print to stdout
void loggerLogEx(const char *fileName, const char *format, ...);

// more direct logging, with no formatted output.
void loggerLogRaw(const char *fileName, const char *toLog);

#ifdef __cplusplus
}
#endif


#endif

