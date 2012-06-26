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
#ifndef PSOFTPIXMAP_H
#define PSOFTPIXMAP_H

#include "PRect.h"
#include "PColor.h"
#include "PMatrix3D.h"

/// \addtogroup SoftBackend
///  @{



/**
 *  Software implementation of a pixmap
**/
struct PEXPORT PSoftPixmap {
    friend struct PSoftContext2D;

    ///< /todo The following are only friends due to an incomplete implementation of the following backends
    friend struct PAGGContext2D;
    friend struct PAGGContextImpl;
    friend struct PAGGPixmap;
    friend struct PAGGRendererBase;
    friend struct PLAGContext2D;
    friend struct PMGFontContext;
    friend struct PSkiaContext2D;
    friend struct PMdpContext2D;

    template <class PFTType> friend struct PFTCacheData;
    friend struct PPatternSampleContext;
    friend struct PFilters;

    template<class DataType, bool UseAA, bool Opacity, bool SrcAlpha> friend struct PFastPatternStrip;
    template<class DataType, bool UseAA, bool Opacity, bool SrcAlpha, PRepeatRule Repeat> friend struct PPatternSampling;
    template<class DataType, bool UseAA, bool Opacity, bool SrcAlpha, PSampling Sampling, PRepeatRule Repeat> friend struct PPatternStrip;

    template <class DataType> friend struct PStrips;
    template <class DataType, bool SrcAlpha, PSampling Sampling, PRepeatRule Repeat, bool ConstY> friend struct PPatternSample;

            void Set            (const PFormat DstFormat, const void *Data, PFormat SrcFormat,
                                 const unsigned Width, const unsigned Height);                                          ///< Sets the pixel format of the image by converting them from another format
//            void Set            (const PFormat DstFormat, const void *Data, PFormat SrcFormat = (PFormat)-1,
//                                 const unsigned Width = ~0, const unsigned Height = ~0);                                ///< Sets the pixel format of the image by converting them from another format

            void Set            (const PFormat DstFormat, const void *Data, const PFormat SrcFormat,
                                 unsigned Pitch = 0, bool BufferAccessAllowed = false);                                 ///< Sets the pixel format of the image by converting them from another format
            bool Set            (const PFormat Format, const void *Data = NULL,
                                 unsigned Pitch = 0, bool BufferAccessAllowed = false);                                 ///< Sets the pixel format of the image and optionally sets the pixels for the entire image
            void Get            (void *Data)                                                        const;              ///< Gets the pixels for the entire image

            void Set            (const PRect Source, const void *const Data);                                           ///< Sets a sub-portion of the pixmap pixels
            void Get            (const PRect Source, void *Data)                                    const;              ///< Gets a sub-portion of the pixmap pixels

            bool Wrap           (const PFormat Format, void* Ptr, unsigned Pitch = 0,
                                 bool BufferAccessAllowed = false);                                                     ///< Wraps the provided data buffer (no copies).  Returns false if ths operation is unsupported.
    inline  static bool MayWrap ();                                                                                     ///< Indicates whether buffer wrapping is supported.

            void SetQuality     (const PSampling Quality = PSBilinear);                                                 ///< Sets the image sampling quality
    inline  void SetRepeatRule  (const PRepeatRule Repeat = PClamp);                                                    ///< Sets the image sampling overflow rule
    inline  void SetTransform   (const PMatrix3D *const Mat);                                                       ///< Sets the sampling transformation matrix

    inline  void *GetBuffer     (void) const;                                                                           ///< Gets a pointer to the pixmap buffer, if buffer access is allowed.

    inline  unsigned int GetPitch (void) const;                                                                         ///< Returns the pixmap pitch (row size in bytes).
    inline  unsigned int GetSize(void) const;                                                                           ///< Returns the pixmap size in bytes

protected:
    unsigned        Width;                                                                                              ///< Pixmap width (in pixels)
    unsigned        Height;                                                                                             ///< Pixmap height (in pixels)

    inline  PSoftPixmap    (const unsigned Width, const unsigned Height);
    inline  PSoftPixmap    ();
    inline ~PSoftPixmap    ();

    void Create     (const unsigned Width, const unsigned Height, const PFormat Format,
                     void *Ptr = NULL, unsigned Pitch = 0);                                                             ///< Creates a software rendering surface

    void CreateFromAlphaMask(const PFormat Format, const unsigned Width, const unsigned Height,
            				 PColor32 Color, const void *Data, unsigned Pitch);
    void CreateAlphaMask(const unsigned Width, const unsigned Height, const void *Data, unsigned Pitch);                ///< Deprecated.

    inline  void *GetPtr    (const unsigned Y)                                                  const;                  ///< Retrieves the pointer of a given pixel in the pixmap
    inline  void *GetPtr    (const unsigned X, const unsigned Y)                                const;                  ///< Retrieves the pointer of a given pixel in the pixmap
    inline  void *NextRow   (void *const Ptr)                                                   const;                  ///< Retrieves the pointer to the next row given a pointer
    inline  void *GetPtrOfs (void *const Ptr, int Offset)                                       const;                  ///< Adds an X-offset to the pointer

	// Prevent the compiler generating a default.
	PSoftPixmap(const PSoftPixmap& p);
	inline PSoftPixmap& operator=(const PSoftPixmap& p);                                                                ///< Copies the parameters of the pixmap (not the content)

    PMatrix3D       Matrix;                                                                                             ///< Pixmap transformation
    PFormat         Format;                                                                                             ///< Pixel format
    PRepeatRule     Repeat;                                                                                             ///< Sampling overflow rule
    unsigned        BytesPerPel;                                                                                        ///< Bytes per pixel
    unsigned        Pitch;                                                                                              ///< Pixmap width (in bytes)
    PSampling       Quality;                                                                                            ///< Pixel's sampling quality
    void           *Data;                                                                                               ///< Pointer to the pixels
    bool            Allocated;                                                                                          ///< Determines if we allocated the buffer ourself
    bool            SrcAlpha;                                                                                           ///< Defines if we should use the pixmap's alpha channel
    bool            BufferAccessAllowed;                                                                                ///< If true, pixmap buffer access is allowed.
    PRect           Bounds;                                                                                             ///< Pixmap's sampling bound
};

#include "PSoftPixmap.inl"



/// @}
#endif
