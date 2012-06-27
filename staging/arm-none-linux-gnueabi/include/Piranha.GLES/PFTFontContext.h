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
#ifndef PFTFONTCONTEXT_H_
#define PFTFONTCONTEXT_H_

#include "PVertex2D.h"
#include "PRect.h"
#include "PFTTypes.h"
#include "PFTFont.h"
#include "PFTCacheData.h"

#define MAX_GLYPH_CACHE_SIZE PValue(40)

struct FT_Matrix_;
struct PFTFallback;
struct PFTCacheKey;



/**
 *  Font context
**/
struct PEXPORT PFTFontContext {
    friend struct PFTFont;

    PFTFontContext();
    ~PFTFontContext();

    inline static  PFontEng        GetFontEng      (void);                                              ///< Returns the font rendering engine
    inline         void            SetFont         (PFTFont* Font);                                     ///< Sets the font.

    void    SetFallbackFont        (PFTFont* Font = NULL);                                              ///< Sets the substitution font.
    void    SetFallbackFonts       (PFTFontArray* Fonts = NULL, PFTFontRangeArray* Overrides = NULL );  ///< Sets the substitution fonts.

    // Cache management
    int     GetCacheSize           (void);                                                              ///< Returns the current size of the font cache.
    void    DumpFontCache          (void);                                                              ///< Dumps the font cache to stdout.
    void    ResetCacheStats        (void);                                                              ///< Reset cache statistics.
    void    GetCacheStats          (int* Hits, int* Misses, int* Evictions, int* HashWatermark,
                                    int* AvgNonZeroHashCount);                                          ///< Returns cache statistics.
    void    ClearCache();                                                                               ///< Releases the cached information

protected:
    inline bool ValidFont           (void);                                                             ///< Returns true if the context has a valid font.

    PFTFont*    GetFallback         (UTFChar CharCode);                                                 ///< Returns the fallback font for the given character.
    void        GetHeight           (PValue* Primary, PValue* Fallback);                                ///< Returns the current font height.
    void        SetTransform        (PFTMatrix3D* Matrix);                                              ///< Applies the given transform to the font context.
    void        LoadChar            (PFTPath *Path, const unsigned Char);                               ///< Loads a character and returns its path equivalent
    template <class PFTPixmap> PFTCacheData<PFTPixmap>     *LoadMask        (const unsigned Char);      ///< Loads a character and returns an alpha mask pixmap.
    template <class PFTPixmap> PFontAtlasGlyph<PFTPixmap>  *LoadAtlasMask   (const unsigned Char);      ///< Loads a character and returns an alpha mask pixmap from an atlas.

    bool    GetApproxBounds         (PRect* Bounds, unsigned Length, PVertex2D Pos, PVertex2D *PosArray,
                                     const PFTMatrix3D& Transform);                                     ///< Returns an approximate transformed bounding box.

    void    DebugDumpStats();                                                                           ///< Prints a stack of debug info

protected:
    PFTFont*        Font;                                                                               ///< The primary font object for rendering text.
    PFTFont*        FallbackFont;                                                                       ///< The fallback font object for rendering glyphs not present in the primary font.

    PFTFontArray    FallbackArray;
    PFTFallback*    FallbackTable;

#ifdef P_FEATURE_PATH_CACHE
    // brute force cache: 4 * 65536 bytes, one font face only
    PPath*  PathCache[1 << 16];
#endif

    FT_Matrix_     *Transform;                                                                          ///< FreeType local transformation matrix

//    bool    GetGlyph                (const usngined Char, PFTFont *Font, PFTCacheKey &Key, PFTCacheData *GlyphData); ///< Retrieves glyph data from the cache
};



#include "PFTFontContext.inl"

#endif /*PFTFONTCONTEXT_H_*/
#endif
