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
#ifndef PMATRIX3D_H
#define PMATRIX3D_H

#include "PVertex2D.h"

/// \addtogroup Backend
///  @{



#ifdef ROWMAJOR
    #define mat(x, y)    Mat->Ele[y][x]
    #define MAT(x, y)    Ele[y][x]
    #define MaT(M, x, y) (M).Ele[y][x]
#else
    #define mat(x, y)    Mat->Ele[x][y]
    #define MAT(x, y)    Ele[x][y]
    #define MaT(M, x, y) (M).Ele[x][y]
#endif



#if !defined(DOXYGEN) || (DOXYGEN == 1)
/**
 *  3D matrix container
**/
struct PMatrixData {
    PValue Ele[3][3];                                                   ///< Matrix components

    bool ShortForm;                                                     ///< Last row is \f$ \begin{pmatrix} 0 & 0 & 1 \end{pmatrix} \f$
    bool FullIdentity;                                                  ///< 3x3-Identity matrix 'I'
    bool HalfIdentity;                                                  ///< 2x2-Identity matrix 'I'

#ifdef IDEBUG
    void Print() const;                                                 ///< Prints the full matrix to the screen
#endif
};
#endif



/**
 *  Software 3D matrix
**/
struct PEXPORT PMatrix3D : public PMatrixData {
    PMatrix3D       ();

    void operator-  (void);                                             ///< Computes the negation
    void operator+= (const PMatrix3D *Mat);                         ///< Adds two matrices
    void operator-= (const PMatrix3D *Mat);                         ///< Subtracts two matrices
    void operator*= (const PValue Scale);                               ///< Multiplies the matrix by a factor
    void operator*= (const PMatrix3D *Mat);                         ///< Multiplies two matrices, where Mat comes logically before 'this'
    void Combine    (const PMatrix3D *Mat);                         ///< Multiplies two matrices, where Mat comes logically after 'this'
    void Combine    (PVertex2D *Pts);                               ///< Multiplies two matrices, where Mat comes logically after 'this'

    inline PVertex2D operator* (const PVertex2D Vert) const;            ///< Multiplies the matrix with a vertex

    inline bool operator== (const PMatrix3D *Mat) const;             ///< Compares two matrices for equality

    void    Identity    (void);                                         ///< Sets the matrix to the identity
    void    Set         (const PValue a, const PValue b, const PValue c,
                         const PValue d, const PValue e, const PValue f,
                         const PValue g, const PValue h, const PValue i);   ///< Sets a matrix given its components
    void    Set         (const PValue a, const PValue b,
                         const PValue d, const PValue e,
                         const PValue g, const PValue h);               ///< Sets a matrix given its components
	void    Get         (PValue& a, PValue& b, PValue& c,
                         PValue& d, PValue& e, PValue& f,
                         PValue& g, PValue& h, PValue& i) const;        ///< Gets the matrix components

    inline PVertex2D ShortMul(const PVertex2D Vert) const;              ///< Multiplies the 2x2 matrix with a vertex

    void    Inverse     (void);                                         ///< Computes the inverse
    void    operator~   (void);                                         ///< \deprecated Computes the inverse (Call Inverse instead)
    void    PreTranslate(const PVertex2D Delta);                        ///< Applies a translation before all other transforms
    void    Translate   (const PVertex2D Delta);                        ///< Applies a translation after all other transforms

    void    PreScale    (const PVertex2D Factors);                      ///< Applies a scale before all other transforms
    void    Scale       (const PVertex2D Factors);                      ///< Applies a scale after all other transforms

    void    PreSkew     (const PVertex2D Delta);                        ///< Applies a skew before all other transforms
    void    Skew        (const PVertex2D Delta);                        ///< Applies a skew after all other transforms

    void    PreRotate   (const PValue Angle);                           ///< Applies a rotation before all other transforms (counter-clockwise)
    void    Rotate      (const PValue Angle);                           ///< Applies a rotation after all other transforms (counter-clockwise)

    const   PValue Determinant  (void) const;                           ///< Computes the matrix determinant
    inline PVertex2D GetTranslation(void) const;                        ///< Retrieves the translation component of the matrix
    inline  bool IsHalfIdentity(void) const;                            ///< Tells wether or not the matrix is the half identity or not
    inline bool IsIdentity(void) const;                                 ///< Tells wether or not the matrix is the identity matrix or not

    bool IsOrth      (void) const;                                   ///< Computes wether or not the matrix is orthogonal with the screen

    PValue Error;
    struct PMatrixData GetMatrixData(void) const;                   ///< For internal use only!
};



#include "PMatrix3D.inl"

/// @}
#endif
