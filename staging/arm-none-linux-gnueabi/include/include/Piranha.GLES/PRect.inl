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
 *  \param value Initial coordinate in combined <x, y>
**/
inline PCoord::PCoord(const int value) : Value(value)
{
}



/**
 *  \param x Initial width
 *  \param y Initial height
**/
inline PCoord::PCoord(const short x, const short y) : X(x), Y(y)
{
}



/**
 *  \param Rect Rectangle to copy
**/
inline PRect::PRect(const PRect *const Rect)
{
    *this = *Rect;
}



/**
 *  \param x1 Left X value
 *  \param y1 Top Y value
 *  \param x2 Right X value
 *  \param y2 Bottom Y value
**/
inline PRect::PRect(const short x1, const short y1, const short x2, const short y2)
{
/*
    PASSERT(x1 <= x2, "Rects aren't socks; you can't put them inside-out");
    PASSERT(y1 <= y2, "Rects aren't socks; you can't put them inside-out");
*/
    Start.X = x1;
    Start.Y = y1;
    End.X   = x2;
    End.Y   = y2;
}



/**
 *  \param start Top-Left corner
 *  \param end Bottom-right corner
**/
inline PRect::PRect(const PCoord start, const PCoord end) : Start(start), End(end)
{
/*
    PASSERT(Start.X <= End.X, "Rects aren't socks; you can't put them inside-out");
    PASSERT(Start.Y <= End.Y, "Rects aren't socks; you can't put them inside-out");
*/
}



/**
 *  \param start Top-Left corner
 *  \param end Bottom-right corner
**/
inline PRect::PRect(const int start, const int end)
{
    Start.Value = start;
    End.Value   = end;
/*
    PASSERT(Start.X <= End.X, "Rects aren't socks; you can't put them inside-out");
    PASSERT(Start.Y <= End.Y, "Rects aren't socks; you can't put them inside-out");
*/
}



/**
 *  \param TopLeft Top-Left corner
 *  \param BottomRight Bottom-right corner
 *  \return existance of the intersection (true/false)
**/
inline bool PRect::Intersects(const PCoord TopLeft, const PCoord BottomRight) const
{
    return ((Start.X < BottomRight.X) & (Start.Y < BottomRight.Y) &
            (TopLeft.X < End.X) & (TopLeft.Y < End.Y));
}



/**
 *  \param SrcRect Rectangle to intersect with
 *  \return Existance of the intersection (true/false)
**/
inline bool PRect::Intersects(const PRect SrcRect) const
{
    return ((Start.X < SrcRect.End.X) & (Start.Y < SrcRect.End.Y) &
            (SrcRect.Start.X < End.X) & (SrcRect.Start.Y < End.Y));
}



/**
 *  \param SrcPt 2D Point
 *  \return existance of the intersection (true/false)
**/
inline bool PRect::Intersects(const PCoord SrcPt) const
{
    return ((SrcPt.X >= Start.X) & (SrcPt.X < End.X) &
            (SrcPt.Y >= Start.Y) & (SrcPt.Y < End.Y));
}



/**
 *  \param Src1 First rectangle
 *  \param Src2 Second rectangle
 *  \return Existance of the intersection (true/false)
**/
inline bool PRect::Intersect(const PRect Src1, const PRect Src2)
{
    // Sorting {Start, End}, we identify the 2 middle terms
    Start.X = PMAX(Src1.Start.X, Src2.Start.X);
    End.X   = PMIN(Src1.End.X, Src2.End.X);
    Start.Y = PMAX(Src1.Start.Y, Src2.Start.Y);
    End.Y   = PMIN(Src1.End.Y, Src2.End.Y);

    // If it's a valid rect, it intersected
    return ((End.X > Start.X) & (End.Y > Start.Y));
}



/**
 *  \param Rect Rectangle being compared
 *  \return True if the recangles are equal; false otherwise
**/
inline bool PRect::operator==(const PRect& Rect)
{
    return (Start.Value == Rect.Start.Value && End.Value == Rect.End.Value);
}

