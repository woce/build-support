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
#include  <stdlib.h>



inline PSoftPixmap::PSoftPixmap()
{
	Allocated   = false;
	SetRepeatRule();
	SetQuality();
}



/**
 *  \param Width Pixmap's width
 *  \param Height Pixmap's height
**/
inline PSoftPixmap::PSoftPixmap(unsigned Width, unsigned Height)
{
    Bounds.Start.X = Bounds.Start.Y = 0;
    Bounds.End.X = Width;
    Bounds.End.Y = Height;

    this->Width     = Width;
    this->Height    = Height;
    Allocated       = false;
	SetRepeatRule();
	SetQuality();
}



inline PSoftPixmap::~PSoftPixmap()
{
    if (Allocated)
        free(Data);
}



/**
 *  \param p Pixmap to copy from
**/
inline PSoftPixmap& PSoftPixmap::operator=(const PSoftPixmap& p)
{
    Bounds.Start.X      = Bounds.Start.Y = 0;
    Bounds.End.X        = Width;
    Bounds.End.Y        = Height;
    Width               = p.Width;
    Height              = p.Height;
    Matrix              = p.Matrix;
    Format              = p.Format;
    Repeat              = p.Repeat;
    BytesPerPel         = p.BytesPerPel;
    Pitch               = p.Pitch;
    Quality             = p.Quality;
    Data                = p.Data;
    Allocated           = false;
    SrcAlpha            = p.SrcAlpha;
    BufferAccessAllowed = p.BufferAccessAllowed;

    return *this;
}



/**
 * \return True if buffer wrapping is supported; false otherwise.
**/
inline bool PSoftPixmap::MayWrap()
{
    return true;
}



/**
 *  \param Repeat Repeat rule to use for sampling
**/
inline void PSoftPixmap::SetRepeatRule(const PRepeatRule Repeat)
{
    this->Repeat = Repeat;
}



/**
 *  \param Mat Transformation matrix
**/
inline void PSoftPixmap::SetTransform(const PMatrix3D *const Mat)
{
	if (Mat) {
		this->Matrix = *Mat;
		// Invert the matrix.
		this->Matrix.Inverse();
	}
	else {
		this->Matrix.Identity();
	}
}



/**
 *  \return Pointer to the pixmap buffer, or NULL if buffer access is not allowed.
**/
inline void* PSoftPixmap::GetBuffer(void) const
{
	return (this->BufferAccessAllowed ? this->Data : NULL);
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \param Y Y coordinate
 *  \return Pixmap[0, Y]
**/
#endif
inline void *PSoftPixmap::GetPtr(const unsigned Y) const
{
    PASSERT(!Height || (Y < Height), "Y coordinate for the pixmap is out of range (%d >= %d)", Y, Height);

    return (char *)Data + Y * Pitch;
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \param X X coordinate
 *  \param Y Y coordinate
 *  \return pointer to Pixmap[X, Y]
**/
#endif
inline void *PSoftPixmap::GetPtr(const unsigned X, const unsigned Y) const
{
    PASSERT(Y <= Height, "Y coordinate for the pixmap is out of range (%d >= %d)", Y, Height);
    PASSERT(X <= Width, "X coordinate for the pixmap is out of range (%d >= %d)", X, Width);

    return (char *)Data + (Y * Pitch ) + (X * BytesPerPel);
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \param Ptr Pointer inside the pixmap
 *  \return Ptr{Y + 1}
**/
#endif
inline void *PSoftPixmap::NextRow(void *const Ptr) const
{
    return (char *)Ptr + Pitch;
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \param Ptr Pointer inside the pixmap
 *  \param Offset X-Offset into the pixmap (assumed to be valid)
 *  \return Ptr{X + Ofs}
**/
#endif
inline void *PSoftPixmap::GetPtrOfs(void *const Ptr, int Offset) const
{
    return (char *)Ptr + (Offset * BytesPerPel);
}

/**
 *  \return The pixmap pitch (row size in bytes)
**/
inline unsigned int PSoftPixmap::GetPitch(void) const
{
    return this->Pitch;
}

/**
 *  \return The pixmap size in bytes
**/
inline unsigned int PSoftPixmap::GetSize() const
{
    return (Width * Height) * BytesPerPel;
}
