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
#ifndef PSTROKER_H
#define PSTROKER_H

#include "PTypes.h"
#include "PMatrix3D.h"
#include "PPath.h"
#include "PBezier.h"


struct PStack;
struct PIntercept;

/// \defgroup Backend Generic Backend
///  @{


/**
 *  Polygon Stroker (Computes the polygon that serves as a stroke for another polygon)
**/
struct PEXPORT PStroker : public PBezier {
    PStroker();
    ~PStroker();

/**
 *  \name Stroke combination rules
**/
    inline void     SetCapRule       (const PCapRule CapRule = PButtCap);                                                   ///< Sets the cap rule
    inline void     SetStartCapRule  (const PCapRule CapRule = PButtCap);                                                   ///< Sets the starting cap rule
    inline void     SetEndCapRule    (const PCapRule CapRule = PButtCap);                                                   ///< Sets the ending cap rule
    inline void     SetJoinRule      (const PJoinRule JoinRule = PBevelJoin);                                               ///< Sets the join rule

/**
 *  \name Stroke parameters
**/
    void            SetStrokeWidth  (const PValue Width = PValue(1));                                                       ///< Specifies the width of the stroke
    void            SetMiterLimit   (const PValue Limit = PValue(4));                                                       ///< Specifies the limit of the miter join

    void            SetDashArray    (const PValue *const Array = NULL, const unsigned Count = 0);                           ///< Specifies an alternating list of lengths for the stroke
    void            SetDashOffset   (const PValue Offset = PValue(0));                                                      ///< Specifies the starting offset inside the dash array
    void            GetBBox         (PRect &Rect, const PPath *const Path);                                                 ///< Gets the bounding box of a path



/**
 *  \name Stroker core functions
**/
protected:
    PPath          *OffsetPath      (const PPath *const Path);                                                              ///< Strokes the path and returns the stroke path

    unsigned        StrokePath      (const PPath *const Path, PVertex2D **&Dst, const PMatrix3D *const Transform, bool AllocStack = false);                                  ///< Strokes a path
    unsigned        StrokePoly      (const PVertex2D *Pts, unsigned Count, PVertex2D **&Dst, const PMatrix3D *const Transform, bool Closed = false, bool AllocStack = false);    ///< Strokes a transformed path

    void            FreeStroke      (PVertex2D **Dst, unsigned Count, bool AllocStack = false);                             ///< Frees the stroke that was allocated by StrokePoly

    inline unsigned GetMaxPts4Cap   (PCapRule Cap);                                                                         ///< Retrieves the maximum number of points that can come out of a single cap
    inline unsigned GetMaxPts4Join  (PJoinRule Join);                                                                       ///< Retrieves the maximum number of points that can come out of a single join
    inline unsigned GetMaxBez4Bez3  (void);                                                                                 ///< Retrieves the maximum number of quadratic beziers that can come out of an offset quadratic bezier
    inline unsigned GetMaxBez4Bez4  (void);                                                                                 ///< Retrieves the maximum number of cubic beziers that can come out of an offset cubic bezier
    inline unsigned GetMaxPts4Bez3  (void);                                                                                 ///< Retrieves the maximum number of points that can come out of a quadratic bezier
    inline unsigned GetMaxPts4Bez4  (void);                                                                                 ///< Retrieves the maximum number of points that can come out of a cubic bezier
    inline unsigned GetMaxPts4Shape (unsigned *Beziers);                                                                    ///< Retrieves the maximum number of points that can come out of a cubic bezier

    inline void     StrokePoly      (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Dashes a set of linear bezier
    inline void     StrokeBez3      (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Dashes a set of cubic bezier
    inline void     StrokeBez4      (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Dashes a set of cubic bezier

    void            DashPoly        (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Dashes a set of linear bezier
    void            DashBez3        (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Dashes a set of cubic bezier
    void            DashBez4        (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Dashes a set of cubic bezier

    void            OffsetPoly      (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Offset a set of linear bezier
    unsigned        OffsetBezier3   (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Offset a set of quadratic bezier
    unsigned        OffsetBezier4   (PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform);           ///< Offset a set of cubic bezier


public:
/**
 *  \name Stroker-specific variables
**/
    PStack         *Stack;                                                                                                  ///< Stack memory mananger

protected:
    PCapRule        StartCapRule;                                                                                           ///< Stroke starting cap rule
    PCapRule        EndCapRule;                                                                                             ///< Stroke ending cap rule

    PJoinRule       JoinRule;                                                                                               ///< Context join rule
    PValue          MiterLimit;                                                                                             ///< Context miter limit
    PValue          MLimit;                                                                                                 ///< Width-skewed miter limit
    PValue          StrokeWidth;                                                                                            ///< Context stroke width

    PValue         *DashArray;                                                                                              ///< Dash array of length
    unsigned        DashCount;                                                                                              ///< Number of lengths in the dash array
    PValue          DashOffset;                                                                                             ///< Offset of the dash array to start reading from

    bool            ComputeInit     (PIntercept *const Int);                                                                ///< Initializes the stroke
    void            ComputeJoin     (PIntercept *const Int, const PMatrix3D *const Transform, bool Intersect = true);   ///< Computes and adds the points for a join of 2 vectors
    void            ComputeCap      (PIntercept *const Int, const PMatrix3D *const Transform);                          ///< Computes and adds the points for a cap
    void            ComputeClose    (PIntercept *const Int, const PMatrix3D *const Transform, bool Closed = false);     ///< Closes the stroke subpath
};
/// @}

#include "PStroker.inl"

#endif
