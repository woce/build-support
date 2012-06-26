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
#ifndef PGLESCONTEXT_H
#define PGLESCONTEXT_H

#include "PStroker.h"
#include "PGLESColorRamp.h"
#include "PGLESPath.h"
#include "PFont.h"

#include "PInt.h"
#include "PVertex4D.h"
#include "LRUList.h"



/// \defgroup GLESBackend GLES Backend
///  @{

struct PId;
struct PEGLFb;
struct PStyleContext2D;
struct PProgram;



#define P_SOFT_VERSION  0
#define MAX_PIPES       4



/**
 *  GLESware Rendering Context
**/
struct PEXPORT PGLESContext2D : public PStroker, public PFTFontContext {
	friend struct PLAGContext2D;
    friend struct PSkiaContext2D;
    friend struct PMdpContext2D;

    // Declare the types that will be used for the given font type
    typedef PFTFontContext              PFontContext;
    typedef PFTCacheData<PGLESPixmap>   PCacheData;
    typedef PFontAtlasGlyph<PGLESPixmap>PAtlasData;

           PGLESContext2D  (PBackend Backend = GetBackend(), unsigned Version = GetVersion());
           ~PGLESContext2D ();

/**
 *  \name Context Information Functions
**/
    inline  static PBackend GetBackend      (void);                                                                                 ///< Returns the rendering backend
    inline  static unsigned GetVersion      (void);                                                                                 ///< Returns the rendering backend version
            static unsigned GetCores        (void);                                                                                 ///< Returns the number of cores this engine is configured to use
            void            ReportGLES      (void);                                                                                 ///< Reports information details about the GL implementation

            bool            SetDisplay      (const PDisplay Display = PPrimary, const unsigned Layer = 0,
                                             const PFormat Format = PFORMAT_8880, const unsigned Buffers = 2);                      ///< Sets the display for this context
            bool            RenderToWindow  (void* NativeWindowHandle);                                                             ///< Sets the display to render to a window
            bool            RenderToTexture (PGLESPixmap *const Texture, bool ClipReset = true);                                    ///< Sets the display to render to a texture
            void            Flip            (const bool Preserve = false, const PRect *const DirtyRegion = NULL);                   ///< Flips to the next onscreen buffer.

            void            GetPixels       (const PRect Source, void *Data) const;                                                 ///< Gets a sub-portion of the primary surface pixels

/**
 *  \name Data Generator Functions
**/
    inline  PGLESPixmap    *CreatePixmap    (const unsigned Width, const unsigned Height) const;                                    ///< Creates a new Pixmap
            PGLESPixmap    *CreatePixmap    (const unsigned Width, const unsigned Height, const PFormat Format, void *const Data = NULL) const;    ///< Creates a new Pixmap
    inline  void            DestroyPixmap   (PGLESPixmap *const Pix) const;                                                         ///< Destroys a pixmap

            PGLESPath      *CreatePath      (void) const;                                                                           ///< Creates a path.
            void            DestroyPath     (PGLESPath* Path) const;                                                                ///< Destroys a path.
            void            GetBBox         (PRect &Rect, const PSoftPath *const Path);                                             ///< Retrieves the bounding box of a path


/**
 *  \name Clipping Functions
**/
            void            ResetClip       (void);                                                                                 ///< Remove all clipping regions.
            void            SetClipRegion   (const PRect Region);                                                                   ///< Sets the rectangular clipping region
            void            SetClipPath     (PGLESPath *Path = NULL, const PFillRule FillRule = PNonZero);                    ///< Sets an non-rectangular clipping region

/**
 *  \name Drawing Functions
**/
            void            Clear           (const PColor32 Color, const PRect* Rect = NULL);                                       ///< Clear the screen with a given color
            void            DrawText        (UTFChar *Text, unsigned Length, PVertex2D Pos, PVertex2D *PosArray = NULL);            ///< Draws a string in a single-line starting a given position, or at the position specified for each glyph
            void            DrawLine        (PVertex2D Start, PVertex2D End);                                                       ///< Draws a line from Start to End
            void            DrawRectangle   (PVertex2D Start, PVertex2D End, PVertex2D Radius = PVertex2D::Origin);                 ///< Draws a rounded rectangle
            void            DrawPolygon     (PVertex2D *Pts, unsigned Count, bool Closed = true);                                   ///< Draws a polygon
            void            DrawPath        (PGLESPath *Path);                                                                      ///< Draws a path
    inline  void            DrawEllipse     (PVertex2D Center, PVertex2D Radii);                                                    ///< Draws a ellipse
            void            DrawArc         (PVertex2D Center, PVertex2D Radii, PValue SAngle, PValue EAngle, bool Pie = true, bool Closed = true);  ///< Draws an elliptical arc
            void            DrawPixmap      (PGLESPixmap *Pixmap, PVertex2D Start, PVertex2D End);                                  ///< Draws a pixmap
            void            DrawSubPixmap   (PGLESPixmap *Pixmap, PVertex2D DstStart, PVertex2D DstEnd, PVertex2D SrcStart, PVertex2D SrcEnd);  ///< Draws a subportion of a pixmap

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
            void            SetStrokeLGrad  (const PGLESColorRamp *const ColorRamp);                                                ///< Sets the stroke to a linear gradient
            void            SetStrokeRGrad  (const PGLESColorRamp *const ColorRamp);                                                ///< Sets the stroke to a radial gradient
            void            SetStrokeRGrad  (const PGLESColorRamp *const ColorRamp, PVertex2D Center, PVertex2D Focii, PValue Radius);                                                ///< Sets the stroke to a radial gradient
            void            SetStrokePixmap (const PGLESPixmap *const Pixmap);                                                      ///< Sets the stroke to a given pixmap
            void            SetStrokePick   (const PVertex2D Pt, bool *const Hit);                                                  ///< Sets the stroke to picking mode given a pick of <x, y>

    inline  void            SetStrokeOpacity(const unsigned Opacity = P_OPACITY_MAX);                                               ///< Sets the stroke opacity [0, P_OPACITY_MAX]

/**
 *  \name Fill Style Modifier Functions
**/
            void            SetNoFill       (void);                                                                                 ///< Removes the fill
            void            SetFillColor    (const PColor32 Color);                                                                 ///< Sets the fill to a given color
            void            SetFillLGrad    (const PGLESColorRamp *const ColorRamp);                                                ///< Sets the fill to a linear gradient
            void            SetFillRGrad    (const PGLESColorRamp *const ColorRamp);                                                ///< Sets the fill to a radial gradient
            void            SetFillRGrad    (const PGLESColorRamp *const ColorRamp, PVertex2D Center, PVertex2D Focii, PValue Radius);                                                ///< Sets the fill to a radial gradient
            void            SetFillPixmap   (const PGLESPixmap *const Pixmap);                                                      ///< Sets the fill to a given pixmap
            void            SetFillPick     (const PVertex2D Pt, bool *const Hit);                                                  ///< Sets the fill to picking mode given a pick of <x, y>

    inline  void            SetFillOpacity  (const POpacity Opacity = P_OPACITY_MAX);                                               ///< Sets the fill opacity [0, P_OPACITY_MAX]
    inline  void            SetFillRule     (const PFillRule FillRule = PNonZero);                                                  ///< Sets the fill rule

            void            SetAttribute    (const unsigned ID, const unsigned Value);                                              ///< Sets internal values in the engine (backend-specific only)
    static  void            SetGlobalAttribute(const unsigned ID, const unsigned Value);                                            ///< Sets internal values in the engine (not backend-specific)



/**
 *  \name Context Global Style Modifier Functions
**/
            bool            SetCompMode     (const PCompRule Rule = PSrcOverMode);                                                  ///< Sets the alpha composition rule



/**
 *  \name Private attributes
**/
private:
    /**
     *  Filling style
    **/
    struct PFillStyle {
        PFillStyle() {}

        bool        SrcAlpha;                                                                                                   ///< Use SrcAlpha in the computations
        int         Type;                                                                                                       ///< Fill's fill type

    /**
     *  \name Color style data
    **/
        PColor32            Color;                                                                                              ///< 32-bit color description
        unsigned            Opacity;                                                                                            ///< Global opacity [0, 256]


    /**
     *  \name Pattern style Data
    **/
        struct {
            const PGLESPixmap  *Pixmap;                                                                                         ///< Pattern pixmap
        } Pattern;

    /**
     *  \name Linear gradient style data
    **/
        struct {
            const PGLESColorRamp *ColorRamp;                                                                                    ///< Color ramp to be applied to the gradient
        } Linear;

    /**
     *  \name Radial gradient style data
    **/
        struct {
            const PGLESColorRamp *ColorRamp;                                                                                    ///< Color ramp to be applied to the gradient
        } Radial;

    /**
     *  \name Bifocal radial gradient style data
    **/
        struct {
            const PGLESColorRamp *ColorRamp;                                                                                    ///< Color ramp to be applied to the gradient
            PVertex2D   Center;
            PVertex2D   Focii;
            PValue      Radius;
        } Bifocal;

    /**
     *  \name Picking style data
    **/
        struct {
            PVertex2D Point;                                                                                                    ///< Point to hit detect against
            bool *PickHit;                                                                                                      ///< Pointer for a positive  result
        } Picking;
    };



    /// GLES Context State
    struct PShaderState {
        PShaderState() : CMRWeight(NULL) {}

        PMatrix3D   VTrans;             ///< Vertex transformation matrix

        PValue      Alpha;              ///< Global Opacity

        // Mask
        PMatrix3D   OTrans;             ///< Per-pixel opacity transform
        PInt        OpMask;             ///< Mask ID

        // Clip Path
        PMatrix3D   CTrans;             ///< Per-pixel opacity transform
        PInt        ClipPath;           ///< Mask ID

        // Color Shader
        PVertex4D   Color;              ///< Translucent Color

        // Texturing Shader
        PInt        Texture;            ///< Texture ID
        PMatrix3D   TTrans;             ///< Texture transformation matrix

        // Bilinear
        PInt        CMR;                ///< Catmull-Rom ID
        PVertex2D   TOffset;            ///< Texture offsets
        PGLESPixmap*CMRWeight;          ///< Catmull-Rom spline bi-partite weighs

        // Radial Offset
        PValue      ROffset;            ///< Radial gradient texture offset

        // Bifocal Offset
        PVertex2D   Center;             ///< Circle center
        PVertex2D   Focii;              ///< Conic Focii
        PValue      Radius;             ///< Circle radii
        PValue      Multiplier;         ///< Percenatge multiplier
    };



    PMatrix3D       Transform;                                                                                              ///< Context transformation matrix

    PFillRule       FillRule;                                                                                               ///< Fill's fill rule to use
    PFillStyle      FillStyle;                                                                                              ///< Filling style
    PFillStyle      StrokeStyle;                                                                                            ///< Stroke's fililng style
    PFillStyle     *Data;                                                                                                   ///< Immediate render setting

    PGLESPixmap    *OpMask;                                                                                                 ///< Modulation mask
    PGLESPixmap    *ClipPath;                                                                                               ///< Per-pixel opacity mask

    PEGLFb         *Fb;                                                                                                     ///< Frame Buffer abstraction
    unsigned        FBO;                                                                                                    ///< Frame Buffer Object
    unsigned        FBOStencil;                                                                                             ///< Frame Buffer Object Stencil
    PGLESPixmap    *Tex;                                                                                                    ///< Frame Buffer Texture
    bool            ClipPathOn;                                                                                             ///< Clip Path on?

    unsigned        Width;                                                                                                  ///< Frame's width
    unsigned        Height;                                                                                                 ///< Frame's height

    static PId      Id;

/**
 *  \name Internal functions
**/
public:
    void            Reset               (void);                                                                             ///< Resets the context's state
private:
    void            FreeVertices        (PVertex2D **Pts, unsigned Count, bool AllocStack = false);                         ///< Frees the allocated chunk of vertices

    void            RasterPolygon       (PVertex2D *Pts, unsigned Count, bool DoTrans = true);                              ///< Rasterizes a polygon
    void            RasterPolygon       (PVertex2D **Pts, unsigned Count);                                                  ///< Rasterizes a set of polygons
    void            RasterPolyline      (const PVertex2D *Pts, unsigned Count, bool Closed = true);                         ///< Draws a polygon's stroke

    void            DrawEllipticalRect  (const PVertex2D Center, PVertex2D RectRadius, PVertex2D EllipRadius);              ///< Renders an elliptical rectangle
    void            DrawAlphaMask       (PGLESPixmap* Mask, int StartX, int StartY, int EndX, int EndY);                    ///< Renders an alpha mask pixmap for font glyphs.

    void            DrawMask            (PAtlasData *Pixmap, PVertex2D Start);                                              ///< Draws an alpha mask
    void            DrawMask            (PGLESPixmap *Pixmap, PVertex2D Start);                                             ///< Draws an alpha mask

    bool            RectAA;                                                                                                 ///< If the rectangles should have antialiasing on or off

    void            DrawTextAtlas       (UTFChar *Text, unsigned Length, PVertex2D Pos, PVertex2D *PosArray = NULL);        ///< Draws a string in a single-line starting a given position, or at the position specified for each glyph

    // Newly added
    PShaderState    State;                                                                                                  ///< Internal shader state

    LRUList<PProgram>       Programs;                                                                                       ///< LL of programs
    PRect           ClipRegion;                                                                                             ///< Context rectangular clipping region

    PProgram       *SetStyle        (PFillStyle *Data, bool DoTrans = true);                                                ///< Sets a program
    PProgram       *CreateProgram   (PFillStyle *Data);                                                                     ///< Create a program
    unsigned        HashState       (PFillStyle *Data);                                                                     ///< Hash a program
    void            FreePrograms    (void);                                                                                 ///< Free all programs
    void            Enable          (const PGLESPixmap *const Pixmap, const unsigned Pipe);                                 ///< Enables a pixmap to draw with
    void            Enable          (const unsigned AttribMask);                                                            ///< Enables a vertex pipe

    // Cached values
    PMatrix3D       VTrans;                                                                                                 ///< Vertex Transform
    unsigned int    CurAttribs;                                                                                             ///< Currently enabled attributes

    void            CacheVTrans     (void);                                                                                 ///< Cache the vertex transform
};
/// @}

#include "PGLESContext.inl"



#endif
