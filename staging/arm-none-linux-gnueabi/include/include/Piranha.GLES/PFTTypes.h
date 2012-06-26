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
#ifndef Q_MOC_RUN
#ifndef PFTTYPES_H_
#define PFTTYPES_H_

#include "PTypes.h"
#include "PBackend.h"
#include "PArray.h"
#include "PMatrix3D.h"



/**
 *  Glyph range structure
**/
struct PFTFontRange {
    UTFChar         First;                          ///< First character in the range
    UTFChar         Last;                           ///< Last character in the range
    unsigned short  Index;                          ///<

    bool operator==(const PFTFontRange& Range)      ///< Compares two structures
    {
        return (First == Range.First && Last == Range.Last && Index == Range.Index);
    }

} PPACKED;



typedef PArray<PFTFontRange> PFTFontRangeArray;

typedef PFTFontRange		 PFTRange;      // deprecated
typedef PArray<PFTFontRange> PFTRangeArray; // deprecated



// Backend agnostic types
#include "PSoftPath.h"

typedef PSoftPath   PFTPath;
typedef PMatrix3D   PFTMatrix3D;



#endif /*PFTTYPES_H_*/
#endif
