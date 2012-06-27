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
#ifndef PRECT_H
#define PRECT_H

/**
 *  Simple rectangular structure
**/

#include "PCommon.h"



/**
 *  2D integer coordinate structure
**/
struct PCoord {
    PCoord() {}                             ///< No-op constructor
    PCoord(const int value);                ///< single-word copy constructor
    PCoord(const short x, const short y);   ///< <x, y> copy constructor

    union {
        struct {
            short X;                        ///< X coordinate value
            short Y;                        ///< Y coordinate value
        } PPACKED;
        int Value;                          // Word-length Combined <y, x>
    } PPACKED;
} PPACKED;



/**
 *  Absolute integer rectangle structure
**/
struct PRect {
    PRect   () {}                                                               ///< No-op construtor
    PRect   (const PRect *const Rect);                                          ///< Pointer-based copy constructor
    PRect   (const short x1, const short y1,   const short x2, const short y2); ///< left, top, right, bottom constructor
    PRect   (const PCoord start,               const PCoord end);               ///< Top-left, bottom-right coordinate constructor
    PRect   (const int start,                  const int end);                  ///< Top-left, bottom-right int constructor

    bool Intersects (const PCoord SrcPt)                                const;  ///< Determines if a point is within the rectangle
    bool Intersects (const PRect SrcRect)                               const;  ///< Determines the existance of an intersection with another rectangle
    bool Intersects (const PCoord TopLeft,   const PCoord BottomRight)  const;  ///< Determines the existance of an intersection with another rectangle
    bool Intersect  (const PRect Src1,       const PRect Src2);                 ///< Computes the intersection with another rectangle

    inline bool operator==(const PRect& Rect);                                  ///< Determines if two rectangles are equal.

    // Variables have the strict requirement that (X1 < X2) && (Y1 < Y2)
    PCoord Start;                                                               ///< Top-left coordinate
    PCoord End;                                                                 ///< Bottom-right coordinate
} PPACKED;



#include "PRect.inl"

#endif
