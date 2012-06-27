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



/// \return true if the matrix is the identity
inline bool PMatrix2D::IsIdentity(void) const
{
    return false;
}



/**
 *  \return \f$ M \cdot Vert \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f{align*} M \cdot Vert &=  \begin{pmatrix} a & d \\ b & e \end{pmatrix}
 *                              \begin{pmatrix} x \\ y \end{pmatrix} \\
 *                          &=  \begin{pmatrix} ax + dy \\ bx + ey \end{pmatrix} \f}
**/
#endif
inline PVertex2D PMatrix2D::operator*(const PVertex2D Vert) const
{
    // Otherwise, do the long multiplication
    return PVertex2D(MAT(0, 0) * Vert.X + MAT(1, 0) * Vert.Y, MAT(0, 1) * Vert.X + MAT(1, 1) * Vert.Y);
}



/**
 *  \param Mat Matrix to compare against
 *  \return true if the matrices are equivalent and/or equal
**/
inline bool PMatrix2D::operator==(const PMatrix2D *Mat) const
{
    //const PValue Error = PValue(1) >> 14u;

    if (PValue::Abs(Ele[0][0] - Mat->Ele[0][0]) > Error)
        return false;
    if (PValue::Abs(Ele[0][1] - Mat->Ele[0][1]) > Error)
        return false;

    if (PValue::Abs(Ele[1][0] - Mat->Ele[1][0]) > Error)
        return false;
    if (PValue::Abs(Ele[1][1] - Mat->Ele[1][1]) > Error)
        return false;

    return true;
}
