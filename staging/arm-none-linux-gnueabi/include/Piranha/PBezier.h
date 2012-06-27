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
#ifndef PBEZIER_H
#define PBEZIER_H

#include "PVertex2D.h"

/// \addtogroup Backend
///  @{

#if (P_VALUES == P_FIXED)
    #define DEFAULT 0.5f
#else
    #define DEFAULT 0.25f
#endif

#define MAX_BEZ_PTS 256



/**
 *  Container for all of the mathematical functions that can be applied onto bezier splines
**/
struct PBezier {
    static unsigned GetPts  (PVertex2D *Dst, PVertex2D A, PVertex2D B, PVertex2D C, const int Dir = 1, PValue Quality = DEFAULT);                 ///< Tesselates a quadratic bezier curve
    static unsigned GetPts  (PVertex2D *Dst, PVertex2D A, PVertex2D B, PVertex2D C, PVertex2D D, const int Dir = 1, PValue Quality = DEFAULT);    ///< Tesselates a cubic bezier curve
    static PValue   GetLen  (PValue &Len, PVertex2D A, PVertex2D B, PVertex2D C, PVertex2D D, PValue Quality = DEFAULT);                          ///< Computes the length of a quadratic bezier curve
    static PValue   GetLen  (PValue &Len, PVertex2D A, PVertex2D B, PVertex2D C, PValue Quality = DEFAULT);                                       ///< Computes the length of a cubic bezier curve

    static void     ReParamBez3     (PValue Start, PValue End, PVertex2D *const Dst, const PVertex2D *const Src);       ///< Reparametrize a bezier curve
    static void     ReParamBez4     (PValue Start, PValue End, PVertex2D *const Dst, const PVertex2D *const Src);       ///< Reparametrize a bezier curve
};



#undef DEFAULT

/// @}
#endif
