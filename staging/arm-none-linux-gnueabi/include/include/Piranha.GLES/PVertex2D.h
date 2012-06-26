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
#ifndef PVERTEX2D_H
#define PVERTEX2D_H

#include "PTypes.h"

/// \addtogroup Backend
///  @{



/**
 *  2D coordinate/vector
**/
struct PEXPORT PVertex2D {
    PVertex2D() {}
    PVertex2D(PValue x, PValue y) : X(x), Y(y) {}                               ///< \param x X cartesian coordinate \param y Y cartesian coordinate

    inline  PVertex2D   operator~   ()                  const;                  ///< Computes the left orthogonal-comlement vector \f$ \vec{x}^\bot \f$
    inline  PVertex2D   operator-   ()                  const;                  ///< Computes the opposite vector \f$ -\vec{x} \f$
    inline  PVertex2D   operator+   (const PVertex2D v) const;                  ///< Adds two vertices
    inline  PVertex2D   operator-   (const PVertex2D v) const;                  ///< Subtracts two vertices
    inline  PValue      operator/   (const PVertex2D v) const;                  ///< Computes the length of the cross product
    inline  PValue      operator*   (const PVertex2D v) const;                  ///< Computes the dot product
    inline  PVertex2D   operator*   (const PValue v)    const;                  ///< Scales a vertex \f$ v\vec{x} \f$
    inline  PVertex2D   operator/   (const PValue v)    const;                  ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex2D   operator^   (const PVertex2D v) const;                  ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex2D   operator<<  (const unsigned v)  const;                  ///< Scales a PVertex2D by \f$ 2^v\vec{x} \f$
    inline  PVertex2D   operator>>  (const unsigned v)  const;                  ///< Scales a PVertex2D by \f$ 2^{-v}\vec{x} \f$

    inline  PVertex2D  &operator+=  (const PVertex2D v);                        ///< Adds two vertices
    inline  PVertex2D  &operator-=  (const PVertex2D v);                        ///< Subtracts two vertices
    inline  PVertex2D  &operator*=  (const PValue v);                           ///< Scales a vertex \f$ v\vec{x} \f$
    inline  PVertex2D  &operator/=  (const PValue v);                           ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex2D  &operator^=  (const PVertex2D v);                        ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex2D  &operator<<= (const unsigned v);                         ///< Scales a PVertex2D by \f$ 2^v\vec{x} \f$
    inline  PVertex2D  &operator>>= (const unsigned v);                         ///< Scales a PVertex2D by \f$ 2^{-v}\vec{x} \f$

    inline  bool        operator==  (const PVertex2D v) const;                  ///< Compares to see if two vertices are the same
    inline  bool        operator!=  (const PVertex2D v) const;                  ///< Compares tos ee if two vertices are different
    inline  bool        operator<   (const PVertex2D v) const;                  ///< Compares to see if one vertex is smaller than another
    inline  bool        operator<=  (const PVertex2D v) const;                  ///< Compares to see if one vertex is smaller or equal than another
    inline  bool        operator>   (const PVertex2D v) const;                  ///< Compares to see if one vertex is greater than another
    inline  bool        operator>=  (const PVertex2D v) const;                  ///< Compares to see if one vertex is greater or equal

    inline  void        Normalize   (void);                                     ///< Normalizes a vector
    inline  PValue      InfNorm     (void)              const;                  ///< Computes the \f$ \infty\f$-norm
            PValue      Norm        (void)              const;                  ///< Computes the 2-norm of a vertex
    inline  bool        IsAligned   (void)              const;                  ///< \return True if the coordinate is non-fractional

    PValue X;                                                                   ///< X Cartesian component
    PValue Y;                                                                   ///< Y Cartesian component

    static    const PVertex2D Origin;                                           ///< 2D Origin is <0, 0>

private:
            bool        GetIntercept(/*Intersept *Int*/);                       ///< Cmoputes the intersection of 2 lines

} PPACKED;

#include "PVertex2D.inl"

/// @}
#endif
