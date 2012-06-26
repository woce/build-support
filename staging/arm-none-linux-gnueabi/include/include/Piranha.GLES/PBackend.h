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
#ifndef PBACKEND_H
#define PBACKEND_H

#define P_BACKEND_SOFT    0
#define P_BACKEND_VG      1
#define P_BACKEND_GLES    2
#define P_BACKEND_GL      3
#define P_BACKEND_AGG     4
#define P_BACKEND_LAG     5
#define P_BACKEND_SKIA    6



/**
 *  P_BACKEND must be defined to select a backend.
**/
#if !defined(P_BACKEND)
 #define P_BACKEND P_BACKEND_SOFT
#endif

#if (P_BACKEND == P_BACKEND_SOFT)
 #define P_BACKEND_NAME Soft

#elif (P_BACKEND == P_BACKEND_VG)
 #define P_BACKEND_NAME VG

#elif (P_BACKEND == P_BACKEND_GLES)
 #define P_BACKEND_NAME GLES

#elif (P_BACKEND == P_BACKEND_AGG)
 #define P_BACKEND_NAME AGG

#elif (P_BACKEND == P_BACKEND_LAG)
 #define P_BACKEND_NAME LAG

#elif (P_BACKEND == P_BACKEND_SKIA)
 #define P_BACKEND_NAME Skia

#else
 #error "P_BACKEND unknown, must be one of { P_BACKEND_SOFT, P_BACKEND_VG,  P_BACKEND_GLES, P_BACKEND_AGG, P_BACKEND_LAG, P_BACKEND_SKIA }"
#endif



// This macro creates a backend-specific filename to refer to
#define BACKEND_INCLUDE2(x)         #x
#define BACKEND_INCLUDE1(P, x, S)   BACKEND_INCLUDE2(P##x##S)
#define BACKEND_INCLUDE(P, x, S)    BACKEND_INCLUDE1(P, x, S)

// This macro creates a backend-specific type to 'genericize'
#define BACKEND_TYPE1(P, x, S)      typedef P ## x ## S;
#define BACKEND_TYPE(P, x, S)       BACKEND_TYPE1(P, x, S)

#define ALIAS1(P, x, S)             P##x##S
#define ALIAS(P, x, S)              ALIAS1(P, x, S)


/**
 *  Font backends
**/
#define P_FREETYPE      1
#define P_MINIGRAPHICS  2

#endif
