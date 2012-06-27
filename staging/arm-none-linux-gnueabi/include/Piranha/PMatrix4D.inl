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
inline PVertex3D PMatrix4D::GetTranslation(void) const
{
    return PVertex3D(MAT(3, 0), MAT(3, 1), MAT(3, 2));
}



/**
 *  \return \f$ M \cdot Vert \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f{align*} M \cdot Vert &=  \begin{pmatrix} a & e & i & m \\ b & f & j & n \\ c & g & k & o \\ 0 & 0 & 0 & 1 \end{pmatrix}
 *                              \begin{pmatrix} x \\ y \\ z \\ 1 \end{pmatrix} \\
 *                          &=  \begin{pmatrix} ax + ey + iz + m \\ bx + fy + jz + n \\ cx + gy + kz + o \end{pmatrix} \f}
**/
#endif
inline PVertex3D PMatrix4D::operator*(const PVertex3D Vert) const
{
    return PVertex3D(   MAT(0, 0) * Vert.X + MAT(1, 0) * Vert.Y + MAT(2, 0) * Vert.Z + MAT(3, 0),
                        MAT(0, 1) * Vert.X + MAT(1, 1) * Vert.Y + MAT(2, 1) * Vert.Z + MAT(3, 1),
                        MAT(0, 2) * Vert.X + MAT(1, 2) * Vert.Y + MAT(2, 2) * Vert.Z + MAT(3, 2));
}



/**
 *  \return \f$ M \cdot Vert \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f{align*} M \cdot Vert &=  \begin{pmatrix} a & e & i & m \\ b & f & j & n \\ c & g & k & o \\ d & h & l & p \end{pmatrix}
 *                              \begin{pmatrix} x \\ y \\ z \\ w \end{pmatrix} \\
 *                          &=  \begin{pmatrix} ax + ey + iz + mw \\ bx + fy + jz + nw \\ cx + gy + kz + ow \\ dx + hy + lz + p \end{pmatrix} \f}
**/
#endif
inline PVertex4D PMatrix4D::operator*(const PVertex4D Vert) const
{
    return PVertex4D(   MAT(0, 0) * Vert.X + MAT(1, 0) * Vert.Y + MAT(2, 0) * Vert.Z + MAT(3, 0) * Vert.W,
                        MAT(0, 1) * Vert.X + MAT(1, 1) * Vert.Y + MAT(2, 1) * Vert.Z + MAT(3, 1) * Vert.W,
                        MAT(0, 2) * Vert.X + MAT(1, 2) * Vert.Y + MAT(2, 2) * Vert.Z + MAT(3, 2) * Vert.W,
                        MAT(0, 3) * Vert.X + MAT(1, 1) * Vert.Y + MAT(2, 1) * Vert.Z + MAT(3, 1) * Vert.W   );
}



/**
 *  \param Mat Matrix to compare against
 *  \return true if the matrices are equivalent and/or equal
**/
inline bool PMatrix4D::operator==(const PMatrix4D *Mat) const
{
    //const PValue Error = PValue(1) >> 14u;

    if (PValue::Abs(Ele[0][0] - Mat->Ele[0][0]) > Error)
        return false;
    if (PValue::Abs(Ele[0][1] - Mat->Ele[0][1]) > Error)
        return false;
    if (PValue::Abs(Ele[0][2] - Mat->Ele[0][2]) > Error)
        return false;
    if (PValue::Abs(Ele[0][3] - Mat->Ele[0][3]) > Error)
        return false;

    if (PValue::Abs(Ele[1][0] - Mat->Ele[1][0]) > Error)
        return false;
    if (PValue::Abs(Ele[1][1] - Mat->Ele[1][1]) > Error)
        return false;
    if (PValue::Abs(Ele[1][2] - Mat->Ele[1][2]) > Error)
        return false;
    if (PValue::Abs(Ele[1][3] - Mat->Ele[1][3]) > Error)
        return false;

    if (PValue::Abs(Ele[2][0] - Mat->Ele[2][0]) > Error)
        return false;
    if (PValue::Abs(Ele[2][1] - Mat->Ele[2][1]) > Error)
        return false;
    if (PValue::Abs(Ele[2][2] - Mat->Ele[2][2]) > Error)
        return false;
    if (PValue::Abs(Ele[2][3] - Mat->Ele[2][3]) > Error)
        return false;

    if (PValue::Abs(Ele[3][0] - Mat->Ele[3][0]) > Error)
        return false;
    if (PValue::Abs(Ele[3][1] - Mat->Ele[3][1]) > Error)
        return false;
    if (PValue::Abs(Ele[3][2] - Mat->Ele[3][2]) > Error)
        return false;
    if (PValue::Abs(Ele[3][3] - Mat->Ele[3][3]) > Error)
        return false;

    return true;
}
