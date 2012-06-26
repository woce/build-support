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
#ifndef PSOFTCOLORRAMP_H
#define PSOFTCOLORRAMP_H

#include "PColor.h"
#include "PMatrix3D.h"

/// \addtogroup SoftBackend
///  @{



/**
 *  Software implementation of a color ramp
**/
struct PEXPORT PSoftColorRamp {
    friend struct PSoftContext2D;
    friend struct PVGFillStyle;
    template<class DataType> friend struct PStrips;

    inline PSoftColorRamp();
    inline ~PSoftColorRamp();

    inline void    SetStopPoints   (const PColor32 *const Cols, const PValue *const Dsts, const unsigned Count);   ///< Defines the stop points
    inline void    SetQuality      (const PQuality Qual = 1);                                                      ///< Sets the raster quality
    inline void    SetRepeatRule   (const PRepeatRule Rule = PClamp);                                              ///< Sets the repeating rule
    inline void    SetTransform    (const PMatrix3D *const Mat);                                               ///< Sets the transformation matrix

private:
	// Prevent compiler from generating any copy methods.
	PSoftColorRamp(const PSoftColorRamp&);
	PSoftColorRamp& operator=(const PSoftColorRamp&);
	
protected:
    PMatrix3D       Matrix;             ///< Transformation matrix
    PVertex2D       Offset;             ///< Translation
    PColor32       *Colors;             ///< List of colors per stop point
    PValue         *Dists;              ///< List of distances per stop point
    unsigned        Count;              ///< Total number of stop points
    PQuality        Quality;            ///< Quality of the raster
    PRepeatRule     RepeatRule;         ///< How to handle out-of-bound colors
    bool            SrcAlpha;           ///< If the colors use alpha or not
};

#include "PSoftColorRamp.inl"

/// @}
#endif
