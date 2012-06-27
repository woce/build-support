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

//#public
#ifndef PMEM_H_
#define PMEM_H_

#include "PCommon.h"

/**
 *  Optimized memcpy and memset
**/
struct PEXPORT PMem
{
    static void Memcpy32(unsigned long* Dst, const unsigned long* Src, unsigned int NumWords);    ///< Copy 32-bit words from Src to Dst
    static void Memset32(unsigned long* Dst, const unsigned long Value, unsigned int NumWords);   ///< Set 32-bit words starting at Dst

    static void Memcpy(char* Dst, const char* Src, unsigned int NumBytes);                        ///< Copy bytes from Src to Dst
    static void Memset(char* Dst, const char Value, unsigned int NumBytes);                       ///< Set bytes starting at Dst

};

#endif /*PMEM_H_*/
