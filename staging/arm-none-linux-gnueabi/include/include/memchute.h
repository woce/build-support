// @@@LICENSE
//
//      Copyright (c) 2008-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#define MEMCHUTE_DEVICE    "/dev/memnotify"
#define MEMCHUTE_NORMAL   0x0000
#define MEMCHUTE_MEDIUM   0xcfee
#define MEMCHUTE_LOW      0xfaac
#define MEMCHUTE_CRITICAL 0xdead
#define MEMCHUTE_REBOOT   0xb00f

#ifndef _MEMCHUTE_H_
#define _MEMCHUTE_H_

enum {
    MEMCHUTE_OOM_ADJ_IMMUNE  = 0, 
    MEMCHUTE_OOM_ADJ_DEFAULT = 6, 
    MEMCHUTE_OOM_ADJ_8MB     = 8, 
    MEMCHUTE_OOM_ADJ_16MB    = 16, 
    MEMCHUTE_OOM_ADJ_64MB    = 64, 
};
typedef int MemchuteOomAdj;

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long MemchuteThreshold;
typedef struct MemchuteWatcher MemchuteWatcher;

typedef void (*MemchuteWatcherFunc)(MemchuteThreshold threshold);

MemchuteWatcher * MemchuteWatcherNew(MemchuteWatcherFunc func);
void MemchuteWatcherDestroy(MemchuteWatcher *watcher);

void MemchuteGmainAttach(MemchuteWatcher *watcher, GMainLoop *mainLoop);
void MemchuteGmainDetach(MemchuteWatcher *watcher);
void MemchuteGmainSetPriority(MemchuteWatcher *watcher, int priority);

MemchuteThreshold MemchuteRead(MemchuteWatcher *watcher);

char * MemchuteThresholdString(MemchuteThreshold threshold);

void MemchuteSetPriority(MemchuteWatcher *watcher,
                     MemchuteOomAdj memoryThresholdMB);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MEMCHUTE_H_
