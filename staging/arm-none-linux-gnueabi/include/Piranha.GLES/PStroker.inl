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
#include "PMem.h"



/**
 *  \param Width Full width of the stroke
**/
inline void PStroker::SetStrokeWidth(PValue Width)
{
    StrokeWidth = Width >> 1u;
    MLimit      = MiterLimit * StrokeWidth;
}



/**
 *  \param Limit Length of the miter join
**/
inline void PStroker::SetMiterLimit(PValue Limit)
{
    MiterLimit  = Limit;
    MLimit      = MiterLimit * StrokeWidth;
}



/**
 *  \param CapRule Specifies how to end the line caps
**/
inline void PStroker::SetCapRule(const PCapRule CapRule)
{
    StartCapRule = EndCapRule = CapRule;
}



/**
 *  \param CapRule Specifies how to start the line caps
**/
inline void PStroker::SetStartCapRule(const PCapRule CapRule)
{
    StartCapRule = CapRule;
}



/**
 *  \param CapRule Specifies how to end the line caps
**/
inline void PStroker::SetEndCapRule(const PCapRule CapRule)
{
    EndCapRule = CapRule;
}



/**
 * \param JoinRule Specifies how to join two lines
**/
inline void PStroker::SetJoinRule(const PJoinRule JoinRule)
{
    this->JoinRule = JoinRule;
}



/**
 *  \param Cap Cap rule to use
 *  \return Maximum number of points that can be generated
**/
inline unsigned PStroker::GetMaxPts4Cap(PCapRule Cap)
{
    switch (Cap) {
        // These provides two additional points per cap
        case PButtCap:
        case PSquareCap:
            return 2;

        // This one generates at most x points per cap
        case PRoundCap:
            return 128;

        default:
            return 0;
    }
}



/**
 *  \param Join Join rule to use
 *  \return Maximum number of points that can be generated
**/
inline unsigned PStroker::GetMaxPts4Join(PJoinRule Join)
{
    switch (Join) {
        // Theses ones generate at most 2 points on each side per vertex
        case PMiterJoin:
        case PBevelJoin:
            return 2 + 3;   // Worst case has 3 inside & 2 outside

        // This one generates at most x points per vertex
        case PRoundJoin:
            return 128 + 3;

        default:
            return 0;
    }
}



/**
 *  \return Maximum count of quadratics
**/
inline unsigned PStroker::GetMaxBez4Bez3(void)
{
    return 100;
}



/**
 *  \return Maximum count of quadratics
**/
inline unsigned PStroker::GetMaxBez4Bez4(void)
{
    return 170;
}




/**
 *  \return Maximum count of quadratics
**/
inline unsigned PStroker::GetMaxPts4Bez3(void)
{
    return 2 * 256;
}




/**
 *  \return Maximum count of quadratics
**/
inline unsigned PStroker::GetMaxPts4Bez4(void)
{
    return 2 * 256;
}



/**
 *  \param Array Array of lengths (NULL disables dashes)
 *  \param Count Number of elements in the array (0 disables dashes)
**/
inline void PStroker::SetDashArray(const PValue *const Array, const unsigned Count)
{
    if (DashArray) {
        delete [] DashArray;
        DashArray = NULL;
    }

	if (Array != NULL && Count > 0) {
	    DashArray = new PValue[Count];
	    PMem::Memcpy((char *)DashArray, (char *)Array, Count * sizeof(PValue));
	}

    DashCount = Count;
}



/**
 *  \param Beziers Array specifying the number of beziers
 *
 *  <center><table border=1 cellspacing=0 align=center class="main">
 *  <tr><th>Index</th><th>Meaning
 *
 *  <tr><td>0</td><td>Closed path or not
 *  <tr><td>1</td><td>Number of Linear Beziers
 *  <tr><td>2</td><td>Number of Quadratic Beziers
 *  <tr><td>3</td><td>Number of Cubic Beziers
 *  </td></tr></table></center>
**/
inline unsigned PStroker::GetMaxPts4Shape(unsigned *Beziers)
{
    if (Beziers[0])
        return  GetMaxPts4Join(JoinRule) * (Beziers[1] + Beziers[2] + Beziers[3] + 1) +
                GetMaxPts4Bez3() * Beziers[2] + GetMaxPts4Bez4() * Beziers[3];

    else
        return  GetMaxPts4Cap(StartCapRule) + GetMaxPts4Cap(EndCapRule) + GetMaxPts4Join(JoinRule) * (Beziers[1] + Beziers[2] + Beziers[3] - 1) +
                GetMaxPts4Bez3() * Beziers[2] + GetMaxPts4Bez4() * Beziers[3];
}



/**
 *  \param Offset Length of offset where dash is to start
**/
inline void PStroker::SetDashOffset(const PValue Offset)
{
    DashOffset = Offset;
}



inline void PStroker::StrokePoly(PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform)
{
    if (!DashArray)
        OffsetPoly(Int, Pts, Count, Transform);
    else
        DashPoly(Int, Pts, Count, Transform);
}



inline void PStroker::StrokeBez3(PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform)
{
    if (!DashArray)
        OffsetBezier3(Int, Pts, Count, Transform);
    else
        DashBez3(Int, Pts, Count, Transform);
}



inline void PStroker::StrokeBez4(PIntercept *const Int, const PVertex2D *Pts, unsigned Count, const PMatrix3D *const Transform)
{
    if (!DashArray)
        OffsetBezier4(Int, Pts, Count, Transform);
    else
        DashBez4(Int, Pts, Count, Transform);
}
