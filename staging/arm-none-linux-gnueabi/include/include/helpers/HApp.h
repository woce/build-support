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
//  LICENSE@@@ */

#ifndef __HAPP__
#define __HAPP__

#ifdef __cplusplus
extern "C" {
#endif

// Note - in all cases where a directory is returned, a trailing '/' is at the end of the directory name.

// fills outBuffer with the full path to the executable for a given
// appID. Returns 1 on success, 0 on failure
int HApp_GetAppPath(const char *appID, char *outBuffer, int outBufferLen);

// given an appID, fills outBuffer with the top level directory
// of the app suite (the directory that has the appinfo file in it)
// Returns 1 on success, 0 on failure
int HApp_GetDirectoryFromAppID(const char *appId, char *outBuffer, int outBufferLen);

// given a full path to an executable, fills outBuffer with the top level directory
// of the app suite (the directory that has the appinfo file in it)
// Returns 1 on success, 0 on failure
int HApp_GetDirectoryFromExe(const char *exePath, char *outBuffer, int outBufferLen);

// given a path to a file, reurns the appID of the suite it is in. The file can be
// anywhere in the suite. This function will walk up the path from the function
// until it finds an appinfo.json file to get the appID from.
// Returns 1 on success, 0 on failure
int HApp_GetAppIDFromPath(const char *exePath, char *outBuffer, int outBufferLen);

// given a full path, gives the base file name of the file. In other
// words, it strips the path. Returns 1 on success, 0 on failure.
int HApp_GetBaseFile(const char *fullPath, char *outBuffer, int outBufferLen);

// gets the appID of the process that called it
// all this does is call  HApp_GetCallingPath and then
// run the result through HApp_GetAppIDFromPath.
int HApp_GetCurrentAppID(char *outBuffer, int outBufferLen);

// gets the path to the currently running executable
int HApp_GetCallingPath(char *outBuffer, int outBufferLen);

// returns true if the jailer is currently active;
// false if it is not. It manually checks for /etc/nojail
// and if it's there, checks to see ifi t starts with
// "pardon". IT does this every time its called.
// returns 1 if the jailer is active, 0 if not.
int HApp_IsJailerActive();


#ifdef __cplusplus
}
#endif


#endif