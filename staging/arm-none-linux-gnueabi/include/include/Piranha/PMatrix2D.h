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
#ifndef PSOFTMATRIX2D_H
#define PSOFTMATRIX2D_H

#include "PVertex2D.h"

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
 *  2D matrix
**/
struct PEXPORT PMatrix2D {
    PMatrix2D       ();

    void operator-  (void);                                             ///< Computes the negation
    void operator+= (const PMatrix2D *Mat);                             ///< Adds two matrices
    void operator-= (const PMatrix2D *Mat);                             ///< Subtracts two matrices
    void operator*= (const PValue Scale);                               ///< Multiplies the matrix by a factor
    void operator*= (const PMatrix2D *Mat);                             ///< Multiplies two matrices, where Mat comes logically before 'this'
    void Combine    (const PMatrix2D *Mat);                             ///< Multiplies two matrices, where Mat comes logically after 'this'

    inline PVertex2D operator* (const PVertex2D Vert) const;            ///< Multiplies the matrix with a vertex

    inline bool operator== (const PMatrix2D *Mat) const;                ///< Compares two matrices for equality

    void    Identity    (void);                                         ///< Sets the matrix to the identity
    void    Set         (const PValue a, const PValue b,
                         const PValue c, const PValue d);               ///< Sets a matrix given its components
    void    Get         (PValue& a, PValue& b,
                         PValue& c, PValue& d) const;                   ///< Gets the matrix components
	
    void    Inverse     (void);                                         ///< Computes the inverse

    const   PValue Determinant  (void) const;                           ///< Computes the matrix determinant
    inline bool IsIdentity(void) const;                                 ///< Tells wether or not the matrix is the identity matrix or not

    bool IsOrth      (void) const;                                      ///< Computes wether or not the matrix is orthogonal with the screen

    PValue Ele[3][3];                                                   ///< Matrix components

private:
    PValue Error;

};



#include "PMatrix2D.inl"

/// @}
#endif
