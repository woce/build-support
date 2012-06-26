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



inline PSoftColorRamp::PSoftColorRamp()
{
    Colors  = NULL;
    Dists   = NULL;

    SetQuality();
    SetRepeatRule();
}



inline PSoftColorRamp::~PSoftColorRamp()
{
    if (Colors)
        free(Colors);
    if (Dists)
        free(Dists);
}



/**
 *  \param Cols List of colors
 *  \param Dsts List of distances
 *  \param Count Number of color/distance pairs
**/
inline void PSoftColorRamp::SetStopPoints(const PColor32 *const Cols, const PValue *const Dsts, const unsigned Count)
{
    if (Colors)
        free(Colors);
    if (Dists)
        free(Dists);

    this->Count = Count;
    this->Colors= (PColor32 *)malloc(Count * sizeof(PColor32));
    this->Dists = (PValue *)malloc(Count * sizeof(PValue));
    SrcAlpha    = false;

    PMem::Memcpy((char *)Dists, (char *)Dsts, Count * sizeof(PValue));

    // Premultiply the alpha
    for (unsigned i = 0; i < Count; i++) {
        SrcAlpha |= (Cols[i].A != 255);

        Colors[i]   = Cols[i].PreMultiply();
    }
}



/**
 *  \param Qual Quality level of the ramp
**/
inline void PSoftColorRamp::SetQuality(const PQuality Qual)
{
    Quality = Qual + (Qual >= 128);
}



/**
 *  \param Rule Repeat rule of the ramp
**/
inline void PSoftColorRamp::SetRepeatRule(const PRepeatRule Rule)
{
    RepeatRule = Rule;
}


/**
 *  \param Mat Transformation matrix
**/
inline void PSoftColorRamp::SetTransform(const PMatrix3D *const Mat)
{
	if (Mat) {
		Matrix      = *Mat;
        Offset.X    = mat(2, 0);
        Offset.Y    = mat(2, 1);

		// Invert the matrix.
		Matrix.Inverse();

	} else {
		Matrix.Identity();
        Offset      = PVertex2D(0, 0);
    }
}

