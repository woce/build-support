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
#ifndef PSOFTMATRIX4D_H
#define PSOFTMATRIX4D_H

#include "PVertex3D.h"
#include "PVertex4D.h"

/// \addtogroup Backend
///  @{



#ifdef ROWMAJOR
    #define mat(x, y) Mat->Ele[y][x]
    #define MAT(x, y) Ele[y][x]
#else
    #define mat(x, y) Mat->Ele[x][y]
    #define MAT(x, y) Ele[x][y]
#endif



/**
 *  4D matrix
**/
struct PEXPORT PMatrix4D {
    PMatrix4D       ();

    void operator-  (void);                                             ///< Computes the negation
    void operator+= (const PMatrix4D *Mat);                             ///< Adds two matrices
    void operator-= (const PMatrix4D *Mat);                             ///< Subtracts two matrices
    void operator*= (const PValue Scale);                               ///< Multiplies the matrix by a factor
    void operator*= (const PMatrix4D *Mat);                             ///< Multiplies two matrices, where Mat comes logically before 'this'
    void Combine    (const PMatrix4D *Mat);                             ///< Multiplies two matrices, where Mat comes logically after 'this'

    inline PVertex3D operator* (const PVertex3D Vert) const;            ///< Multiplies the matrix with a vertex
    inline PVertex4D operator* (const PVertex4D Vert) const;            ///< Multiplies the matrix with a vertex

    inline bool operator== (const PMatrix4D *Mat) const;                ///< Compares two matrices for equality

    void    Identity    (void);                                         ///< Sets the matrix to the identity
    void    Inverse     (void);                                         ///< Computes the inverse
    void    PreTranslate(const PVertex3D Delta);                        ///< Applies a translation before all other transforms
    void    Translate   (const PVertex3D Delta);                        ///< Applies a translation after all other transforms

    void    PreScale    (const PVertex3D Factors);                      ///< Applies a scale before all other transforms
    void    Scale       (const PVertex3D Factors);                      ///< Applies a scale after all other transforms

    void    PreSkew     (const PVertex3D Delta);                        ///< Applies a skew before all other transforms
    void    Skew        (const PVertex3D Delta);                        ///< Applies a skew after all other transforms

    void    PreRotateX  (const PValue Angle);                           ///< Applies a rotation around the X-axis before all other transforms
    void    RotateX     (const PValue Angle);                           ///< Applies a rotation around the X-axis after all other transforms

    void    PreRotateY  (const PValue Angle);                           ///< Applies a rotation around the Y-axis before all other transforms
    void    RotateY     (const PValue Angle);                           ///< Applies a rotation around the Y-axis after all other transforms

    void    PreRotateZ  (const PValue Angle);                           ///< Applies a rotation around the Z-axis before all other transforms
    void    RotateZ     (const PValue Angle);                           ///< Applies a rotation around the Z-axis after all other transforms

    const   PValue Determinant  (void) const;                           ///< Computes the matrix determinant
    inline  PVertex3D GetTranslation(void) const;                       ///< Retrieves the translation component of the matrix
    inline  bool IsHalfIdentity(void) const;                            ///< Tells wether or not the matrix is the half identity or not
    inline bool IsIdentity(void) const;                                 ///< Tells wether or not the matrix is the identity matrix or not

    PValue Ele[4][4];                                                   ///< Matrix components
    PValue Error;
};



#include "PMatrix4D.inl"

/// @}
#endif
