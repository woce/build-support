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
#include <memory.h>


inline PGLESColorRamp::PGLESColorRamp()
{
    SetQuality();
}



/**
 *  \param Qual Quality level of the ramp
**/
inline void PGLESColorRamp::SetQuality(const PQuality Qual)
{
    Quality = Qual + (Qual >= 128);
}



/**
 *  \param Rule Repeat rule of the ramp
**/
inline void PGLESColorRamp::SetRepeatRule(const PRepeatRule Rule)
{
    PGLESPixmap::SetRepeatRule(Rule);
}


/**
 *  \param Mat Transformation matrix
**/
inline void PGLESColorRamp::SetTransform(const PMatrix3D *const Mat)
{
	if (Mat) {
		Matrix = *Mat;
		// Invert the matrix.
		Matrix.Inverse();

	} else
		Matrix.Identity();
}

