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
#ifndef PSOFTCONTEXT_H
#define PSOFTCONTEXT_H

#include <pthread.h>
#include "PStroker.h"
#include "PSoftColorRamp.h"
#include "PSoftPixmap.h"
#include "PSoftPath.h"
#include "PFont.h"
#include "PSMP.h"



/// \defgroup SoftBackend Software Backend
///  @{

struct PId;
struct PFb;
struct PStyleContext2D;



#if !defined(DOXYGEN) || (DOXYGEN==1)
/**
 *  Filling style
**/
struct PFillStyle {
    bool        SrcAlpha;                                                                                                   ///< Use SrcAlpha in the computations
    int         Type;                                                                                                       ///< Fill's fill type

/**
 *  \name Color style data
**/
    PColor32    Color;                                                                                                      ///< 32-bit color description
    unsigned    Opacity;                                                                                                    ///< Global opacity [0, 256]


/**
 *  \name Pattern style Data
**/
    struct {
        const PSoftPixmap  *Pixmap;                                                                                         ///< Pattern pixmap
    } Pattern;

/**
 *  \name Linear gradient style data
**/
    struct {
        const PSoftColorRamp *ColorRamp;                                                                                    ///< Color ramp to be applied to the gradient
    } Linear;

/**
 *  \name Radial gradient style data
**/
    struct {
        const PSoftColorRamp *ColorRamp;                                                                                    ///< Color ramp to be applied to the gradient
    } Radial;

/**
 *  \name Picking style data
**/
    struct {
        PVertex2D Point;                                                                                                    ///< Point to hit detect against
        bool *PickHit;                                                                                                      ///< Pointer for a positive  result
    } Picking;

    PRect *BBox;

    PCompRule   CompRule;                                                                                                   ///< Composition rule
};
#endif

#define P_SOFT_VERSION  0

/**
 *  Software Rendering Context
**/
struct PEXPORT PSoftContext2D : public PStroker, public PFTFontContext, public PSMP {
    friend struct PLAGContext2D;
    friend struct PSkiaContext2D;
    friend struct PMdpContext2D;

    // Declare the types that will be used for the given font type
    typedef PFTFontContext              PFontContext;
    typedef PFTCacheData<PSoftPixmap>   PCacheData;


           PSoftContext2D  (PBackend Backend = GetBackend(), unsigned Version = GetVersion());
           ~PSoftContext2D ();

//    void TriagMonotone      (PVertex2D *Src, unsigned Count, PStack *const Stack);
//    void Triangulate        (PVertex2D **Src, PVertex2D **const LastPt, PFillRule FillRule, PStack* const Stack);


/**
 *  \name Context Information Functions
**/
    inline  static PBackend        GetBackend      (void);                                                                          ///< Returns the rendering backend
    inline  static unsigned        GetVersion      (void);                                                                          ///< Returns the rendering backend version

            bool            SetDisplay      (const PDisplay Display = PPrimary, const unsigned Layer = 0,
                                             const PFormat Format = PFORMAT_8880, const unsigned Buffers = 1);                      ///< Sets the display for this context
            bool            RenderToTexture (PSoftPixmap *const Texture);                                                           ///< Sets the display to render to a texture
            void            Flip            (const bool Preserve = false, const PRect *const DirtyRegion = NULL);                   ///< Flips to the next onscreen buffer.

            void            GetPixels       (const PRect Source, void *Data) const;                                                 ///< Gets a sub-portion of the primary surface pixels

/**
 *  \name Data Generator Functions
**/
    inline  PSoftPixmap    *CreatePixmap    (const unsigned Width, const unsigned Height) const;                                    ///< Creates a new Pixmap
    inline  PSoftPixmap    *CreatePixmap    (const unsigned Width, const unsigned Height, const PFormat Format, void *const Data = NULL) const;    ///< Creates a new Pixmap
    inline  void            DestroyPixmap   (PSoftPixmap *const Pix) const;                                                         ///< Destroys a pixmap

            PSoftPath      *CreatePath      (void) const;                                                                           ///< Creates a path.
            void            DestroyPath     (PSoftPath* Path) const;                                                                ///< Destroys a path.
            void            GetBBox         (PRect &Rect, const PSoftPath *const Path);                                             ///< Retrieves the bounding box of a path

/**
 *  \name Clipping Functions
**/
            void            ResetClip       (void);                                                                                 ///< Remove all clipping regions.
            void            SetClipRegion   (const PRect Region);                                                                   ///< Sets the rectangular clipping region
            void            SetClipPath     (const PSoftPath *Path = NULL, const PFillRule FillRule = PNonZero);                    ///< Sets an non-rectangular clipping region

/**
 *  \name Drawing Functions
**/
            void            Clear           (const PColor32 Color, const PRect* Rect = NULL);                                       ///< Clear the screen with a given color
            void            DrawText        (UTFChar *Text, unsigned Length, PVertex2D Pos, PVertex2D *PosArray = NULL);            ///< Draws a string in a single-line starting a given position, or at the position specified for each glyph
            void            DrawLine        (PVertex2D Start, PVertex2D End);                                                       ///< Draws a line from Start to End
            void            DrawRectangle   (PVertex2D Start, PVertex2D End, PVertex2D Radius = PVertex2D::Origin);                 ///< Draws a rounded rectangle
            void            DrawPolygon     (PVertex2D *Pts, unsigned Count, bool Closed = true);                                   ///< Draws a polygon
            void            DrawPath        (PSoftPath *Path);                                                                      ///< Draws a path
    inline  void            DrawEllipse     (PVertex2D Center, PVertex2D Radii);                                                    ///< Draws a ellipse
            void            DrawArc         (PVertex2D Center, PVertex2D Radii, PValue SAngle, PValue EAngle, bool Pie = true, bool Closed = true);  ///< Draws an elliptical arc
            void            DrawPixmap      (PSoftPixmap *Pixmap, PVertex2D Start, PVertex2D End);                                  ///< Draws a pixmap
            void            DrawSubPixmap   (PSoftPixmap *Pixmap, PVertex2D DstStart, PVertex2D DstEnd, PVertex2D SrcStart, PVertex2D SrcEnd);  ///< Draws a subportion of a pixmap

/**
 *  \name Geometrical Modifiers
**/
    inline  void            SetTransform    (const PMatrix3D *const Matrix = NULL);                                             ///< Sets the transformation matrix to apply to the world
    inline  void            SetEdgeQuality  (const PQuality Quality = 2);                                                           ///< \deprecated Sets the quality of the edge antialiasing

/**
 *  \name Stroke Style Modifier Functions
**/
            void            SetNoStroke     (void);                                                                                 ///< Removes the stroke
            void            SetStrokeColor  (const PColor32 Color);                                                                 ///< Sets the stroke to a given color
            void            SetStrokeLGrad  (const PSoftColorRamp *const ColorRamp);                                                ///< Sets the stroke to a linear gradient
            void            SetStrokeRGrad  (const PSoftColorRamp *const ColorRamp);                                                ///< Sets the stroke to a radial gradient
            void            SetStrokeRGrad  (const PSoftColorRamp *const ColorRamp, PVertex2D Center, PVertex2D Focii, PValue Radius);                                                ///< Sets the stroke to a radial gradient
            void            SetStrokePixmap (const PSoftPixmap *const Pixmap);                                                      ///< Sets the stroke to a given pixmap
            void            SetStrokePick   (const PVertex2D Pt, bool *const Hit);                                                  ///< Sets the stroke to picking mode given a pick of <x, y>
            void            SetStrokeBBox   (PRect *const Rect);                                                                    ///< Sets the stroke to picking mode given a pick of <x, y>

    inline  void            SetStrokeOpacity(const unsigned Opacity = P_OPACITY_MAX);                                               ///< Sets the stroke opacity [0, P_OPACITY_MAX]

/**
 *  \name Fill Style Modifier Functions
**/
            void            SetNoFill       (void);                                                                                 ///< Removes the fill
            void            SetFillColor    (const PColor32 Color);                                                                 ///< Sets the fill to a given color
            void            SetFillLGrad    (const PSoftColorRamp *const ColorRamp);                                                ///< Sets the fill to a linear gradient
            void            SetFillRGrad    (const PSoftColorRamp *const ColorRamp);                                                ///< Sets the fill to a radial gradient
            void            SetFillRGrad    (const PSoftColorRamp *const ColorRamp, PVertex2D Center, PVertex2D Focii, PValue Radius);                                                ///< Sets the fill to a radial gradient
            void            SetFillPixmap   (const PSoftPixmap *const Pixmap);                                                      ///< Sets the fill to a given pixmap
            void            SetFillPick     (const PVertex2D Pt, bool *const Hit);                                                  ///< Sets the fill to picking mode given a pick of <x, y>
            void            SetFillBBox     (PRect *const Rect);                                                                    ///< Sets the stroke to picking mode given a pick of <x, y>

    inline  void            SetFillOpacity  (const POpacity Opacity = P_OPACITY_MAX);                                               ///< Sets the fill opacity [0, P_OPACITY_MAX]
    inline  void            SetFillRule     (const PFillRule FillRule = PNonZero);                                                  ///< Sets the fill rule

            void            SetAttribute    (const unsigned ID, const unsigned Value);                                              ///< Sets internal values in the engine (backend-specific only)
    static  void            SetGlobalAttribute(const unsigned ID, const unsigned Value);                                            ///< Sets internal values in the engine (not backend-specific)


/**
 *  \name Context Global Style Modifier Functions
**/
            void            SetCompMode     (const PCompRule Rule = PSrcOverMode);                                                  ///< Sets the alpha composition rule



/**
 *  \name Private attributes
**/
private:
    PMatrix3D       Transform;                                                                                              ///< Context transformation matrix

    PRect           ClipRect;                                                                                               ///< Clipping rectangle
    PVertex2D     **ClipPath;                                                                                               ///< Context additional path clipping region
    unsigned        ClipCount;                                                                                              ///< Number of points in the clip math merge vertex list
    PFillRule       ClipRule;                                                                                               ///< Clipipng path's fill rule
    PVertex2D     **ClipMerge;                                                                                              ///< Context additional path clipping region
    unsigned        ClipMergeCount;                                                                                         ///< Number of merge points in the clipping path


    PSoftPixmap     Surface;                                                                                                ///< Rendering surface

    PFillRule       FillRule;                                                                                               ///< Fill's fill rule to use
    PFillStyle      FillStyle;                                                                                              ///< Filling style
    PFillStyle      StrokeStyle;                                                                                            ///< Stroke's fililng style

    PStyleContext2D*Privates;                                                                                               ///< Context's intenal members
//    pthread_barrier_t   Barrier;                                                                                          ///< Thread sync
    PBarrier        Barrier;

    PFb            *Fb;                                                                                                     ///< Frame Buffer abstraction
    bool            RenderTargetTexture;

    static PId      Id;

    template <class DataType> friend struct PStrips;

/**
 *  \name Internal functions
**/
public:
    void            Reset               (void);                                                                             ///< Resets the context's state
private:
    static void     ThreadCB            (PSoftContext2D *Context);                                                          ///< Thread pool callback
    void            ThreadWorker        (void);                                                                             ///< Thread work dispatcher
    PStyleContext2D*GetPrivate          (void) const;                                                                       ///< Retrieves the thread-specific private structure
    void            SetCoreSlice        (PRect Region, int TaskID);                                                         ///< Evenly split the core slice in Y

    void            FreeVertices        (PVertex2D **Pts, unsigned Count, bool AllocStack = false) const;                   ///< Frees the allocated chunk of vertices

    void            RasterPolygon       (PVertex2D *Pts, unsigned Count);                                                   ///< Rasterizes a polygon
    void            RasterPolygon       (PVertex2D **Pts, unsigned Count);                                                  ///< Rasterizes a set of polygons
    void            RasterPolyline      (const PVertex2D *Pts, unsigned Count, bool Closed = true);                         ///< Draws a polygon's stroke

    void            DrawEllipticalRect  (const PVertex2D Center, PVertex2D RectRadius, PVertex2D EllipRadius);              ///< Renders an elliptical rectangle

    void            DrawTextWithPaths(UTFChar *Text, unsigned Length, PVertex2D Pos, PVertex2D *PosArray);                  ///< Renders text using a path glyph representation.
    void            DrawTextWithMasks(UTFChar *Text, unsigned Length, PVertex2D Pos, PVertex2D *PosArray);                  ///< Renders text using a transformed alpha mask representation.

    void            RasterTRectangle    (PVertex2D Start, PVertex2D End);                                                   ///< Rasterizes and transforms a rectangle
    void            DrawSimpleRectGeneric(PVertex2D Start, PVertex2D End) const;
    void            DrawSimplePatternRectRotateNoScale(PVertex2D Start, PVertex2D End, unsigned int Angle) const;
    void            DrawSimpleRectOutline(bool UseAA, int StartY, int EndY) const;                                          ///< Draws an outline around the simple rect to indicate the type of operation (for debug).
    void            DrawSimpleRectangle (PVertex2D Start, PVertex2D End) const;                                             ///< Renders a simple rectangle fill
    void            DrawSimplePolygon   (const PVertex2D *const MergePt) const;                                             ///< Renders a monotone polygon
    void            DrawComplexPolygon  (PVertex2D  **MergePt, PVertex2D **const LastPt) const;                             ///< Renders a complex polygon
    void            DrawAlphaMask(PSoftPixmap* Mask, int StartX, int StartY) const;                                         ///< Renders an alpha mask pixmap for font glyphs.
    void            RasterClear         (const PRect* Rect) const;                                                          ///< Clear the screen with a given color

    bool            RectAA;                                                                                                 ///< If the rectangles should have antialiasing on or off
    PCompRule       CompRule;                                                                                               ///< Composition mode
};
/// @}

#include "PSoftContext.inl"

#endif
