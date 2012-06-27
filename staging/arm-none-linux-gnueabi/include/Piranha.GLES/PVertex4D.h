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
#ifndef PVERTEX4D_H
#define PVERTEX4D_H

#include "PTypes.h"

/// \addtogroup Backend
///  @{



/**
 *  4D coordinate/vector
**/
struct PEXPORT PVertex4D {
    PVertex4D() {}
    PVertex4D(PValue x, PValue y, PValue z, PValue w) : X(x), Y(y), Z(z), W(w) {}   ///< \param x X cartesian coordinate \param y Y cartesian coordinate \param z Z cartesian coordinate \param w W cartesian coordinate

    inline  PVertex4D   operator-   ()                  const;                  ///< Computes the opposite vector \f$ -\vec{x} \f$
    inline  PVertex4D   operator+   (const PVertex4D v) const;                  ///< Adds two vertices
    inline  PVertex4D   operator-   (const PVertex4D v) const;                  ///< Subtracts two vertices
    inline  PValue      operator*   (const PVertex4D v) const;                  ///< Computes the dot product
    inline  PVertex4D   operator*   (const PValue v)    const;                  ///< Scales a vertex \f$ v\vec{x} \f$
    inline  PVertex4D   operator/   (const PValue v)    const;                  ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex4D   operator^   (const PVertex4D v) const;                  ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex4D   operator<<  (const unsigned v)  const;                  ///< Scales a PVertex4D by \f$ 2^v\vec{x} \f$
    inline  PVertex4D   operator>>  (const unsigned v)  const;                  ///< Scales a PVertex4D by \f$ 2^{-v}\vec{x} \f$

    inline  PVertex4D  &operator+=  (const PVertex4D v);                        ///< Adds two vertices
    inline  PVertex4D  &operator-=  (const PVertex4D v);                        ///< Subtracts two vertices
    inline  PVertex4D  &operator*=  (const PValue v);                           ///< Scales a vertex \f$ v\vec{x} \f$
    inline  PVertex4D  &operator/=  (const PValue v);                           ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex4D  &operator^=  (const PVertex4D v);                        ///< Scales a vertex \f$ \vec{x}/v \f$
    inline  PVertex4D  &operator<<= (const unsigned v);                         ///< Scales a PVertex4D by \f$ 2^v\vec{x} \f$
    inline  PVertex4D  &operator>>= (const unsigned v);                         ///< Scales a PVertex4D by \f$ 2^{-v}\vec{x} \f$

    inline  bool        operator==  (const PVertex4D v) const;                  ///< Compares to see if two vertices are the same
    inline  bool        operator!=  (const PVertex4D v) const;                  ///< Compares tos ee if two vertices are different

    inline  void        Normalize   (void);                                     ///< Normalizes a vector
    inline  PValue      InfNorm     (void)              const;                  ///< Computes the \f$ \infty\f$-norm
            PValue      Norm        (void)              const;                  ///< Computes the 2-norm of a vertex
    inline  bool        IsAligned   (void)              const;                  ///< \return True if the coordinate is non-fractional

    PValue X;                                                                   ///< X Cartesian component
    PValue Y;                                                                   ///< Y Cartesian component
    PValue Z;                                                                   ///< Z Cartesian component
    PValue W;                                                                   ///< W Cartesian component
} PPACKED;

#include "PVertex4D.inl"

/// @}
#endif
