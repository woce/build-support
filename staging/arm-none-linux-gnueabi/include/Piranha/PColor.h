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
#ifndef PCOLOR_H
#define PCOLOR_H

#include "PTypes.h"



typedef unsigned NativeDepth;           ///< Type used to write pixels

/**
 *  Defines the supported pixel formats
**/
typedef enum {
    PFORMAT_8       = 0,                ///< 8bit luminance

PFORMAT_8BIT        = 0,                ///< Marker for 8bit modes

    PFORMAT_444     = 1,                ///< 16-bit RGBA 4444
    PFORMAT_565     = 2,                ///< 16-bit RGB 565
    PFORMAT_5658    = 3,                ///< biplanar 8bit alpha + 16bit RGB 565

PFORMAT_16BIT       = 3,                ///< Marker for 16bit modes

    PFORMAT_8880    = 4,                ///< 32-bit XRGB 888
    PFORMAT_8888    = 5,                ///< 32-bit ARGB 8888 (premultiplied)
    PFORMAT_8880_NM = 6,                ///< 32-bit ARGB 8888 (non-multiplied)
    PFORMAT_8888_NM = 7,                ///< 32-bit ARGB 8888 (non-multiplied)

PFORMAT_32BIT       = 7,                ///< Marker for 32bit modes

    PFORMAT_888     = 8,                ///< 24-bit RGB 888
    PFORMAT_888A    = 9,                ///< 24-bit ARGB 888 - no idea how to generate this.
PFORMAT_24BIT	    = 9,
PFORMAT_MAX				///< Max format value.  
					///< Since it's always 1 more than the number of
} PFormat;



/**
 *  Defines what to do when the color we are trying to sample is out of range
**/
typedef enum {
    PClamp  = 0,                                            ///< Clamp the coordinate to the bounds
    PRepeat = 1,                                            ///< Wrap aroudn the bounds
} PRepeatRule;



/**
 *  Defines the composition modes
**/
typedef enum {
    PCopyMode       = 0,
    PKeepMode       = 1,
    PXorMode        = 2,
    PPlusMode       = 3,

    PSrcOverMode    = 4,
    PSrcInMode      = 5,
    PSrcOutMode     = 6,
    PSrcATopMode    = 7,

    PDstOverMode    = 8,
    PDstInMode      = 9,
    PDstOutMode     = 10,
    PDstATopMode    = 11,

    PMultiplyMode   = 12,
    PScreenMode     = 13,
    PDarkenMode     = 14,
    PLightenMode    = 15,

    PMaxMode,
} PCompRule;



/**
 *  single-color definition
**/
struct PEXPORT PColor32 {
    union {
        struct {
            unsigned char B;                                ///< Blue Component [0..255]
            unsigned char G;                                ///< Green Component [0..255]
            unsigned char R;                                ///< Red Component [0..255]
            unsigned char A;                                ///< Alpha Component [0..255]
        } PPACKED;

        unsigned Value;                                     ///< Color read as a 32-bit value
    };

    PColor32( unsigned R=0, unsigned G=0, unsigned B=0, unsigned A=0xff );
    PColor32 PreMultiply    (void)                  const;  ///< Premultiplies the color
    PColor32 Weight         (const unsigned Alpha)  const;  ///< Scales the color by an alpha value
    void     GetColor       (PValue &Red, PValue &Green, PValue &Blue) const;                 ///< Retrieves the color in PValue format
    void     GetColor       (PValue &Red, PValue &Green, PValue &Blue, PValue &Alpha) const;  ///< Retrieve the color in PValue format
    void     GetNormalizedColor(PValue &Red, PValue &Green, PValue &Blue, PValue &Alpha) const;  ///< Retrieve the color components converted to the range [0,1].
} PPACKED;

#endif
