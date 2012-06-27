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
#ifndef PCONTEXT_H
#define PCONTEXT_H

#include "PMatrix3D.h"
#include "PColorRamp.h"
#include "PPixmap.h"
#include "PPath.h"
#include "PFont.h"
#include BACKEND_INCLUDE(P, P_BACKEND_NAME, Context.h)

/**
 *  \mainpage
 *  \image html piranha.png
 *  \htmlonly <font size="+3"><center>It really bites!</center></font> \endhtmlonly
 *  \section Definition
 *  Piranha is a high-fidelity 2D vector rasterization engine.
 *  It supports multiple backends and can be compiled for multiple platforms
 *  \section FeatureSet
 *
 * <center><table border=1 cellspacing=0 align=center class="main">
 * <tr><th colspan=2>Features<th>Software<th>OpenVG<th>OpenGL-ES<th>AGG<th>LAG<th>Skia
 *
 * <tr><th colspan=9>Fill Styles
 *
 * <tr><td rowspan=2>Single Color</td>
 * <td>Solid            <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Translucent  <td>Yes <td>-   <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><td rowspan=8>Pattern Fill</td>
 * <td>Clamping         <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Repeating    <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Projection   <td>No  <td>Yes <td>-   <td>Yes <td>No  <td>No</tr>
 * <tr><td>Nearest      <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Bilinear     <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Bicubic      <td>Yes <td>No  <td>Yes <td>-   <td>Yes <td>No</tr>
 * <tr><td>Lanzcos      <td>Yes <td>No  <td>-   <td>-   <td>Yes <td>No</tr>
 * <tr><td>Opacity      <td>Yes <td>-   <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><td rowspan=4>Linear Gradient</td>
 * <td>Clamping         <td>Yes <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 * <tr><td>Repeating    <td>Yes <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 * <tr><td>Projection   <td>No  <td>Yes <td>-   <td>-   <td>-   <td>-   </tr>
 * <tr><td>Opacity      <td>Yes <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 *
 * <tr><td rowspan=4>Radial Gradient</td>
 * <td>Clamping         <td>Yes <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 * <tr><td>Repeating    <td>Yes <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 * <tr><td>Projection   <td>No  <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 * <tr><td>Opacity      <td>Yes <td>Yes <td>Yes <td>-   <td>-   <td>-   </tr>
 *
 * <tr><th colspan=9>Stroking
 *
 * <tr><td rowspan=3>End Cap</td>
 * <td>Butt             <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Square       <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Round        <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><td rowspan=3>Line Join</td>
 * <td>Bevel            <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Miter        <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Round        <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><td rowspan=2>Dashes</td>
 * <td>Array            <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Offset       <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><th colspan=9>Shapes
 *
 * <tr><td colspan=2>Lines              <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td rowspan=2>Rectangles         </td>
 * <td>Regular                          <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>Rounded                      <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td colspan=2>Monotone Polygon   <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><td rowspan=2>Complex Polygon</td>
 * <td>EvenOdd          <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>NonZero      <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 *
 * <tr><td rowspan=4>Path</td>
 * <td>MoveTo           <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>LineTo       <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>BezierTo     <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td>ArcTo        <td>Yes <td>-   <td>Yes <td>Yes <td>Yes <td>-  </tr>
 *
 * <tr><td colspan=2>Ellipse            <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td colspan=2>Elliptical Arcs    <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td colspan=2>Image              <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td colspan=2>SubImage           <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes</tr>
 * <tr><td colspan=2>Quality Setting    <td>Yes <td>-   <td>Yes <td>No  <td>Yes <td>-  </tr>
 *
 * <tr><th colspan=9>Clipping
 *
 * <tr><td colspan=2>Rectangle          <td>1   <td>1   <td>1   <td>1   <td>1   <td>1  </tr>
 * <tr><td colspan=2>Path               <td>Yes <td>Yes <td>Yes <td>Yes <td>Yes <td>-  </tr>
 *
 * </table></center>
 *
 * \section FontFeatureSet Font Feature Set
 *
 * <center><table border=1 cellspacing=0 align=center class="main">
 * <tr><th>Features<th>MG<th>FreeType</tr>
 *
 * <tr><td>Glyph Loading                <td>Yes   <td>Yes  </tr>
 * <tr><td>Glyph Caching                <td>Yes   <td>Yes  </tr>
 *
 * </table></center>
 *
 * \section ColorCoding Color Coding for Bitmap Operation Visualization
 *
 * <center><table border=1 cellspacing=0 align=center class="main">
 * <tr><th>Color<th>Transformed<th>Source Alpha<th>Anti-Aliasing</tr>
 *
 * <tr><td>Blue    <td>No   <td>No   <td>Yes  </tr>
 * <tr><td>Green   <td>No   <td>Yes  <td>No   </tr>
 * <tr><td>Teal    <td>No   <td>Yes  <td>Yes  </tr>
 * <tr><td>Red     <td>Yes  <td>No   <td>No   </tr>
 * <tr><td>Purple  <td>Yes  <td>No   <td>Yes  </tr>
 * <tr><td>Yellow  <td>Yes  <td>Yes  <td>No   </tr>
 * <tr><td>White   <td>Yes  <td>Yes  <td>Yes  </tr>
 *
 * </table></center>
**/



/*
 *  Define the context's type
 */
BACKEND_TYPE(P, P_BACKEND_NAME, Context2D PContext2D)



// Include PFont.h after getting the font type defs provided in the backend headers

#endif
