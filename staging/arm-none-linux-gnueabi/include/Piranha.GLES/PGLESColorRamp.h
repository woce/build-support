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
#ifndef PGLESCOLORRAMP_H
#define PGLESCOLORRAMP_H

#include "PColor.h"
#include "PGLESPixmap.h"

/// \addtogroup GLESBackend
///  @{



/**
 *  GLESware implementation of a color ramp
**/
struct PEXPORT PGLESColorRamp : private PGLESPixmap {
    friend struct PGLESContext2D;

    inline PGLESColorRamp();

           void    SetStopPoints   (const PColor32 *const Cols, const PValue *const Dsts, const unsigned Count);    ///< Defines the stop points
    inline void    SetQuality      (const PQuality Qual = 1);                                                       ///< Sets the raster quality
    inline void    SetRepeatRule   (const PRepeatRule Rule = PClamp);                                               ///< Sets the repeating rule
    inline void    SetTransform    (const PMatrix3D *const Mat = NULL);                                         ///< Sets the transformation matrix

private:
	// Prevent compiler from generating any copy methods.
	PGLESColorRamp(const PGLESColorRamp&);
	PGLESColorRamp& operator=(const PGLESColorRamp&);
	
protected:
    PQuality        Quality;            ///< Quality of the raster
    PValue          Length;             ///< Maximum length of the span
};

#include "PGLESColorRamp.inl"

/// @}
#endif
