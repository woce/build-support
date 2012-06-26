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
#ifndef PFTFONT_H_
#define PFTFONT_H_

#include "PTypes.h"
#include "PVertex2D.h"
#include "PRect.h"
#include "PArray.h"
#include "PFTFontFile.h"



struct FT_FaceRec_;
typedef struct FT_FaceRec_*  FT_Face;

struct FT_LibraryRec_;
typedef struct FT_LibraryRec_  *FT_Library;

template <class PFTPixmap> struct PFTCache;
struct PFTFontContext;



/**
 *  Font structure
**/
struct PEXPORT PFTFont {
	friend struct PFTFontContext;
	template <class PFTPixmap> friend struct PFTCache;
	friend struct PFTFallback;
    friend struct PGLESContext2D;
	
	PFTFont();
	~PFTFont();
	
/**
 *  \name Font parameters
**/
    bool    LoadFont        (const char *const Filename, int FaceIndex = 0);                            ///< Loads a given font with the given face index

    void    AdvancePen      (PVertex2D *const Pen, const UTFChar CurChar, const UTFChar NextChar,
                             PFTFont* Fallback = NULL);                                                 ///< Advances the text pen to the next character
    void    AdvancePen      (PVertex2D *const Pen, const UTFChar CurChar, const UTFChar NextChar,
                             PFTFontContext* Context);                                                  ///< Advances the text pen to the next character
    void    SetFontSize     (const PValue PointSize);                                                   ///< Sets the font size
    bool    Exists          (UTFChar Char);                                                             ///< Checks if the given char has a glyph.

/**
 *  \name Font information
**/
    void    GetBound        (PRect &Bound, const UTFChar *const String, const unsigned Length);         ///< Retrieves the untransformed boundary of the text
    void    GetBound        (PRect &Bound);                                                             ///< Returns the maximum bounding box for any character
    PValue  GetFontHeight   (void);                                                                     ///< Retrieves the height of the text
    PValue  GetAscend       (void);                                                                     ///< Retrieves the ascend of the text
    PValue  GetDescend      (void);                                                                     ///< Retrieves the descend of the text

protected:
    void    AdvancePenImpl  (PVertex2D *const Pen, const UTFChar CurChar, const UTFChar NextChar,
                             PFTFont* Fallback, PFTFontContext* Context);                               ///< Internal AdvancePen impl.
protected:
    FT_Face         Face;                                                                               ///< Freetype's font face
    int             FaceIndex;                                                                          ///< Index of the face in the font file
    PValue          PointSize;                                                                          ///< Font's point size
    PValue          Height;                                                                             ///< Font's height
    PFTFontFilePtr  File;                                                                               ///< Font's file
};



typedef PArray<PFTFont*> PFTFontArray;

#endif /*PFTFONT_H_*/
