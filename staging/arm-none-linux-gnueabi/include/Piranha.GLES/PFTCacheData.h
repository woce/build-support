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
#ifndef PFT_CACHE_DATA
#define PFT_CACHE_DATA

#include "PFTTypes.h"
#include "PVertex2D.h"



template <class PFTPixmap> struct PFTCacheData {
    PFTPixmap Pixmap;                                                   ///< Pixmap for the glyph
    PVertex2D TopLeft;                                                  ///< Top left coordinate of the glyph
    PVertex2D Advance;                                                  ///< Glyph spacing

    inline int Size();                                                  ///< Glyph data size

    static inline PFTCacheData* Alloc();                                ///<
    static inline void          Dealloc(PFTCacheData<PFTPixmap>* Data); ///<
};



/**
 *  Structure containing the glyph's information within the atlas
**/
template <class PFTPixmap> struct PFontAtlasGlyph {
    PFTPixmap  *Pixmap;                                         ///< Pixmap for the glyph
    PVertex2D   TopLeft;                                        ///< Top left coordinate of the glyph
    PVertex2D   Advance;                                        ///< Glyph spacing

    float       Top;                                            ///< Texture's top
    float       Bottom;                                         ///< Texture's bottom
    float       Left;                                           ///< Texture' left
    float       Right;                                          ///< Texture's right

    short       Width;                                          ///< Pixel width
    short       Height;                                         ///< Pixel height
    bool        Exists;                                         ///< true if the glyph exists in this font
};



#include "PFTCacheData.inl"


#endif
