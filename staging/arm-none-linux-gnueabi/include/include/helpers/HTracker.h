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

#ifndef __HTRACKER__
#define __HTRACKER__

#ifdef __cplusplus
extern "C" {
#endif

/* the maximum allowable size of the trackign config file */
#define MAX_CONFIG_SIZE 4096

/* done with #defines to keep the __FUNCTION__ tag inside the function that calls it.
 * call this to have the current functions name logged with the category x
 *
 * The tracker will track based on the values in "/media/internal/tconfig.txt"
 * It will track to the file "/media/internal/track.txt".
 * The category string (with the config file) determines if it should be tracked, and
 * also labels it.
 */
#define HTracker_track(category, format, ...) HTracker_funcTrack(category, __FUNCTION__, format, ## __VA_ARGS__)

/* Dumps the current stack trace into the log (if the category is being listened to)
 * The stack trace is for the calling thread.
 * WARNING: This function is slow. If you put it in a frequently-called chunk of code, you can
 * expect EPIC slowdown.
 * Though as always, if the category isbeing ignored, the function returns immediately.
 */
#define HTracker_stackTrace(category) HTracker_funcStackTrace(category, __FUNCTION__)

/* helper function to turn a boolean value into "true" or "false" */
#define BOOL_TO_STR(x) (x?"true":"false")

/* Functionalized version of the stackDump. Most likely you will want to
 * use HTracker_stackTrace instead of this. See HTracker_stackTrace for a
 * dire warnign about this functions performance.
 */
void HTracker_funcStackTrace(const char *category, const char *funcName);

/* presumes you'll send the function name in after the category. Assembles the string from
 * there. Really no reason to call this directly. Just use HTracker_track and it will call
 * this, adding the function name in for you.
 */
void HTracker_funcTrack(const char *category, const char *funcName, const char *format, ...);

/* Like HTracker_track, but doesn't add in the function name. */
void HTracker_rawTrack(const char *category, const char *format, ...);

/* returns nonzero if it has the category. zero if it does not */
int HTracker_isTracking(const char *category);

/* Forces HTracker to re-init (re-read the tconfig.txt file) */
void HTracker_ReInit(void);


#ifdef __cplusplus
}
#endif


#endif

