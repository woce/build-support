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
 *  \return 2D Translation offset
**/
inline PVertex2D PMatrix3D::GetTranslation(void) const
{
    return PVertex2D(MAT(2, 0), MAT(2, 1));
}



/// \return true if the matrix is a half-identity
inline bool PMatrix3D::IsHalfIdentity(void) const
{
    return HalfIdentity;
}



/// \return true if the matrix is the identity
inline bool PMatrix3D::IsIdentity(void) const
{
    return FullIdentity;
}



/**
 *  \return \f$ M \cdot Vert \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f{align*} M \cdot Vert &=  \begin{pmatrix} a & d & g \\ b & e & h \\ 0 & 0 & 1 \end{pmatrix}
 *                              \begin{pmatrix} x \\ y \\ 1 \end{pmatrix} \\
 *                          &=  \begin{pmatrix} ax + dy + g \\ bx + ey + h \\ 1 \end{pmatrix} \f}
**/
#endif
inline PVertex2D PMatrix3D::operator*(const PVertex2D Vert) const
{
    // If it's the identity, forget about doing any work
    if (FullIdentity)
        return Vert;

    else if (HalfIdentity)
    	return PVertex2D(Vert.X + MAT(2,0), Vert.Y + MAT(2,1));

    // Otherwise, do the long multiplication
    return PVertex2D(MAT(0, 0) * Vert.X + MAT(1, 0) * Vert.Y + MAT(2, 0), MAT(0, 1) * Vert.X + MAT(1, 1) * Vert.Y + MAT(2, 1));
}



/**
 *  \param Vert Vertex to multiply with the matrix
 *  \return \f$ M \cdot Vert \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f{align*} M \cdot Vert &=  \begin{pmatrix} a & d & g \\ b & e & h \\ 0 & 0 & 1 \end{pmatrix}
 *                              \begin{pmatrix} x \\ y \\ 0 \end{pmatrix} \\
 *                          &=  \begin{pmatrix} ax + dy \\ bx + ey \\ 0 \end{pmatrix} \f}
**/
#endif
inline PVertex2D PMatrix3D::ShortMul(const PVertex2D Vert) const
{
    // If it's the identity, forget about doing any work
    if (HalfIdentity)
    	return PVertex2D(Vert.X + MAT(2,0), Vert.Y + MAT(2,1));

    // Otherwise, do the long multiplication
    return PVertex2D(MAT(0, 0) * Vert.X + MAT(1, 0) * Vert.Y, MAT(0, 1) * Vert.X + MAT(1, 1) * Vert.Y);
}



/**
 *  \param Mat Matrix to compare against
 *  \return true if the matrices are equivalent and/or equal
**/
inline bool PMatrix3D::operator==(const PMatrix3D *Mat) const
{
    //const PValue Error = PValue(1) >> 14u;

    if (PValue::Abs(Ele[0][0] - Mat->Ele[0][0]) > Error)
        return false;
    if (PValue::Abs(Ele[0][1] - Mat->Ele[0][1]) > Error)
        return false;
    if (PValue::Abs(Ele[0][2] - Mat->Ele[0][2]) > Error)
        return false;

    if (PValue::Abs(Ele[1][0] - Mat->Ele[1][0]) > Error)
        return false;
    if (PValue::Abs(Ele[1][1] - Mat->Ele[1][1]) > Error)
        return false;
    if (PValue::Abs(Ele[1][2] - Mat->Ele[1][2]) > Error)
        return false;

    if (PValue::Abs(Ele[2][0] - Mat->Ele[2][0]) > Error)
        return false;
    if (PValue::Abs(Ele[2][1] - Mat->Ele[2][1]) > Error)
        return false;
    if (PValue::Abs(Ele[2][2] - Mat->Ele[2][2]) > Error)
        return false;

    return true;
}
