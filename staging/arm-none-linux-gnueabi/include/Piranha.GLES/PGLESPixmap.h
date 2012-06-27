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
#ifndef PGLESPIXMAP_H
#define PGLESPIXMAP_H

#include "PRect.h"
#include "PColor.h"
#include "PMatrix3D.h"

/// \addtogroup GLESBackend
/// @{

namespace ALIAS(P, P_BACKEND_NAME, Font) {
    struct PFTCacheData;
    struct PFTCache;
    struct PFontAtlas;
}



/**
 *  OpenGLES implementation of a pixmap
**/
struct PEXPORT PGLESPixmap {
    friend struct PGLESContext2D;

    template <class PFTType> friend struct PFTCacheData;
    template <class PFTType> friend struct PFontAtlas;


    bool Set            (const PFormat DstFormat, const void *Data, PFormat SrcFormat = (PFormat)-1,
                         const unsigned Width = ~0, const unsigned Height = ~0);                                ///< Sets the pixel format of the image by converting them from another format
	
    void Get            (void *Data)                                                        const;              ///< Gets the pixels for the entire image

    void Set            (const PRect Source, const void *const Data);                                           ///< Sets a sub-portion of the pixmap pixels
    void Get            (const PRect Source, void *Data)                                    const;              ///< Gets a sub-portion of the pixmap pixels

    void SetQuality     (const PSampling Quality = PSBilinear);                                                 ///< Sets the image sampling quality
    void SetRepeatRule  (const PRepeatRule Repeat = PClamp);                                                    ///< Sets the image sampling overflow rule
    void SetTransform   (const PMatrix3D *const Mat = NULL);                                                    ///< Sets the sampling transformation matrix


protected:
    unsigned        Width;                                                                                      ///< Pixmap width (in pixels)
    unsigned        Height;                                                                                     ///< Pixmap height (in pixels)
    PSampling       Quality;                                                                                    ///< Pixel's sampling quality
    PRepeatRule     Repeat;                                                                                     ///< Sampling overflow rule
    PMatrix3D       Matrix;                                                                                     ///< Pixmap transformation
    bool            SrcAlpha;                                                                                   ///< Whether or not this pixmap contains alpha
    bool            Flip;                                                                                       ///< Whether we should flip it horizontally

    unsigned        ID;                                                                                         ///< GLES Texture ID
    unsigned        Format;                                                                                     ///< GLES Internal texture format

    PGLESPixmap    (const unsigned Width, const unsigned Height);
    PGLESPixmap    ();
    ~PGLESPixmap    ();

    unsigned GetSize(void) const;

    static unsigned Formats[PFORMAT_32BIT + 1];
    static unsigned Sizes[PFORMAT_32BIT + 1];
    static unsigned Types[PFORMAT_32BIT + 1];
    static bool     Alphas[PFORMAT_32BIT + 1];
};



/// @}
#endif
