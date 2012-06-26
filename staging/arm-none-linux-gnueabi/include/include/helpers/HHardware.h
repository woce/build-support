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

#ifndef __HHARDWARE__
#define __HHARDWARE__


#ifdef __cplusplus
extern "C" {
#endif

// returns a string with the machine type.
// Ex: "topaz", "mantaray", "pre", etc.
const char *HHardware_getMachine();

// fills outWidth and outHeight with the raw screen resolution.
// this is the sheer number of pixels on the display. Portability
// does not enter in to it. It's a facet ot the hardware itself.
// returns 1 on success, 0 on failure.
int HHardware_getDisplaySize(int *outWidth, int *outHeight);


#ifdef __cplusplus
}
#endif



#endif


