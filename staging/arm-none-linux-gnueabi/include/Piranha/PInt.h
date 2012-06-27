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
#ifndef PINT_H
#define PINT_H

/// \addtogroup Backend
///  @{

inline unsigned long    BitClear(const unsigned long val, const unsigned long mask);    ///< \brief Clears the select mask from the value
inline unsigned         Log2    (unsigned x);                       ///< \brief Computes the integer log2 of a number
inline long             Div     (register long a, register long b); ///< \brief Computes the integer division between two numbers

#include "PCommon.h"



/**
 *  Fixeding point type
**/
struct PEXPORT PInt {
    friend struct Tests;

    PInt() {}
    PInt(const int value);

    inline  PInt  operator-   ()                    const;                                      ///< Computes the negation \f$ (-x) \f$
    inline  PInt  operator+   (const PInt v)        const;                                      ///< Adds two PInt
    inline  PInt  operator-   (const PInt v)        const;                                      ///< Subtracts two PInt
    inline  PInt  operator*   (const PInt v)        const;                                      ///< Multiplies two PInt
    inline  PInt  operator/   (const PInt v)        const;                                      ///< Divides two PInt
    inline  PInt  operator%   (const PInt v)        const;                                      ///< Modulos a PInt with a PInt
    inline  PInt  operator^   (const PInt v)        const;                                      ///< Computes the exponential \f$ (x^v) \f$
    inline  PInt  operator<<  (const unsigned v)    const;                                      ///< Multiplies a PInt by \f$ 2^v \f$ ie: \f$ (x * 2^v)\f$
    inline  PInt  operator>>  (const unsigned v)    const;                                      ///< Divides a PInt by \f$ 2^v \f$ ie: \f$ (x / 2^v)\f$

    inline  PInt &operator+=  (const PInt v);                                                   ///< Adds two PInt and store
    inline  PInt &operator-=  (const PInt v);                                                   ///< Subtracts two PInt and store
    inline  PInt &operator*=  (const PInt v);                                                   ///< Multiplies two PInt and store
    inline  PInt &operator/=  (const PInt v);                                                   ///< Divides two PInt and store
    inline  PInt &operator%=  (const PInt v);                                                   ///< Modulos a PInt with a PInt and store
    inline  PInt &operator^=  (const PInt v);                                                   ///< Computes the exponential\f$ (x^v) \f$ and store
    inline  PInt &operator<<= (const unsigned v);                                               ///< Multiplies a PInt by \f$ 2^v \f$ ie: \f$ (x * 2^v)\f$ and store
    inline  PInt &operator>>= (const unsigned v);                                               ///< Divides a PInt by \f$ 2^v \f$ ie: \f$ (x / 2^v)\f$ and store

    inline  bool    operator>   (const PInt v)      const;                                      ///< Compares to see if a PInt > v
    inline  bool    operator>=  (const PInt v)      const;                                      ///< Compares to see if a PInt >= v
    inline  bool    operator<   (const PInt v)      const;                                      ///< Compares to see if a PInt < v
    inline  bool    operator<=  (const PInt v)      const;                                      /// < Compares to see if a PInt <= v
    inline  bool    operator==  (const PInt v)      const;                                      ///< Compares to see if a PInt is equal to v
    inline  bool    operator!=  (const PInt v)      const;                                      ///< Compares tos ee if a PInt is not-equal to v

    inline  PInt &operator=   (const int v);                                                    ///< Sets the float to an integer

    inline          operator    int     ()          const;                                      ///< Converts a PInt to an int

    inline static  PInt  Abs              (const PInt v);                                       ///< Returns the absolute value

    int     Value;                                                                              ///< int representation
} PPACKED;

#include "PInt.inl"

/// @}
#endif
