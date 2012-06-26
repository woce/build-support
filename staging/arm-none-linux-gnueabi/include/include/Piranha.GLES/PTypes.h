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
#ifndef PTYPES_H
#define PTYPES_H

#include "PCommon.h"

#define P_FIXED 0
#define P_FLOAT 1

#ifndef P_VALUES
 #define P_VALUES P_FIXED
#endif

#if (P_VALUES == P_FLOAT)
 #include "PFloat.h"
 /**
  *  \var typedef PFloat PValue
  *  System's native fractional number representation
 **/
 typedef PFloat PValue;

#elif (P_VALUES == P_FIXED)
 #include "PFixed.h"
 /**
  *  \var typedef PFixed PValue
  *  System's native fractional number representation
 **/
 typedef PFixed PValue;

#else
 #error "P_VALUES unknown, must be one of P_FIXED or P_FLOAT"
#endif



/**
 *  Defines the backend rendering engine
**/
typedef enum {
    PSoftware,                      ///< Software rendering backend
    POpenGLES,                      ///< OpenGL-ES rendering backend
    POpenVG,                        ///< OpenVG rendering backend
    PAntiGrainGeometry,             ///< AGG rendering backend
    PSkia,                          ///< Google Skia backend

// Hybrids
    PLessAntiGrain,                 ///< Hybrid AGG-Soft backend
    PMdp,                           ///< Qualcomm MSM MDP backend
} PBackend;



/**
 *  Defines the font loading engine
**/
typedef enum {
    PFontFreeType,                      ///< FreeType 2
    PFontMiniGraphics,                  ///< MiniGraphics font engine
} PFontEng;



/**
 *  Defines the target display to render to
**/
typedef enum {
    PPrimary,                       ///< Primary screen
    PSecondary,                     ///< Secondary screen
    PTertiary,                      ///< Tertiary screen
    PTVOut,                         ///< TV out
    PTexture,                       ///< Render to texture

    PShared,                        ///< Render using shared buffers
} PDisplay;



/**
 *  Defines the list of fill rules
**/
typedef enum {
    PNonZero = -1,                  ///< Fills accross crossing edges
    PEvenOdd = 1,                   ///< Alternates the fill with every crossing edge
} PFillRule;



/**
 *  Defines the list of cap rules
**/
typedef enum {
    PButtCap    = 0,                ///< Adds nothing at the end of the stroke
    PSquareCap  = 1,                ///< Adds a rectangle to the end of the stroke
    PRoundCap   = 2,                ///< Adds a half-circle to the end of the stroke
} PCapRule;



/**
 *  Defines the list of join rules
**/
typedef enum {
    PMiterJoin = 0,                 ///< Joins two strokes with a diamond
    PBevelJoin = 1,                 ///< Joins two strokes with a triangle
    PRoundJoin = 2,                 ///< Joins two strokes with a circle
} PJoinRule;



/**
 * List of sampling methods available
**/
typedef enum {
    PSNearest   = 0,
    PSBilinear  = 1,
    PSBicubic   = 2,
    PSLanzcos   = 3,

    PImageLevels= 4,

    PSNone      = 5,
} PSampling;



/**
 *  Defines the type to be used for Opacity.
**/
typedef unsigned POpacity;

#define P_OPACITY_MAX  255
#define P_OPACITY_MIN  0



/**
 *  Level of quality
**/
typedef unsigned PQuality;

#define P_QUALITY_MAX  255
#define P_QUALITY_MIN  0



/**
 *  Defines the UTF type to use for fonts
**/
typedef unsigned short UTFChar;       ///< type to store the UTF character



#endif
