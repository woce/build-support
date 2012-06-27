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

/**
 *  \return Backend rasterizer that is being used
**/
inline PBackend PSoftContext2D::GetBackend (void)
{
    return PSoftware;
}



/**
 *  \return Version of the backend rasterizer
**/
inline unsigned PSoftContext2D::GetVersion(void)
{
    return P_SOFT_VERSION;
}



/**
 *  \param Width Pixmaps' width
 *  \param Height Pixmaps' height
 *  \return Software pixmap
**/
inline PSoftPixmap *PSoftContext2D::CreatePixmap(const unsigned Width, const unsigned Height) const
{
    return new PSoftPixmap(Width, Height);
}



/**
 *  \param Width Pixmaps' width
 *  \param Height Pixmaps' height
 *  \param Format Pixmap pixel format
 *  \param Data Pixel information for the pixmap
 *  \return Software pixmap
**/
inline PSoftPixmap *PSoftContext2D::CreatePixmap(const unsigned Width, const unsigned Height, const PFormat Format, void *const Data) const
{
    PSoftPixmap *Pixmap = new PSoftPixmap();

    PFormat DstFormat = Format;

    if (DstFormat == PFORMAT_8888_NM)
        DstFormat = PFORMAT_8888;

    Pixmap->Set(DstFormat, Data, Format, Width, Height);

    return Pixmap;
}



/**
 *  \param Pix Pixmap to kill
**/
inline void PSoftContext2D::DestroyPixmap(PSoftPixmap *const Pix) const
{
    PASSERT(Surface.Data != Pix->Data, "Cannot free the screen.  First change the screen's destination surface");

    delete Pix;
}



/**
 *  \param Quality Quality level [0, 256]
**/
inline void PSoftContext2D::SetEdgeQuality(const PQuality Quality)
{
    PUNUSED(Quality);
    PASSERT(0, "Deprecated function");
}



/**
 *  \param Matrix transformation matrix
**/
inline void PSoftContext2D::SetTransform(const PMatrix3D *const Matrix)
{
	if (Matrix) {
		Transform = *Matrix;
	}
	else {
		Transform.Identity();
	}
}



/**
 *  \param Opacity Opacity [0, P_OPACITY_MAX]
**/
inline void PSoftContext2D::SetStrokeOpacity(const unsigned Opacity)
{
    StrokeStyle.Opacity = (Opacity < P_OPACITY_MAX ? Opacity : P_OPACITY_MAX);

    if (Opacity >= 128)
        StrokeStyle.Opacity++;
}



/**
 *  \param Opacity Opacity [0, P_OPACITY_MAX]
**/
inline void PSoftContext2D::SetFillOpacity(const POpacity Opacity)
{
    FillStyle.Opacity = (Opacity < P_OPACITY_MAX ? Opacity : P_OPACITY_MAX);

    if (Opacity >= 128)
        FillStyle.Opacity++;
}



/**
 *  \param FillRule Fill rule to use
**/
inline void PSoftContext2D::SetFillRule(const PFillRule FillRule)
{
    this->FillRule = FillRule;
}



/**
 *  \param Center Center point of the ellipse
 *  \param Radii Ellipse's 2D radii
**/
inline void PSoftContext2D::DrawEllipse(PVertex2D Center, PVertex2D Radii)
{
    PASSERT(Radii.X >= PValue(0), "X Radius cannot be negative");
    PASSERT(Radii.Y >= PValue(0), "Y Radius cannot be negative");

    DrawRectangle(Center - Radii, Center + Radii, Radii);
}

