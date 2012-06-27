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
#ifndef PFIXED_H
#define PFIXED_H

#include "PCommon.h"

/// \addtogroup Backend
///  @{



/**
 *  Fixeding point type
**/
struct PEXPORT PFixed {
    friend struct Tests;
    friend struct PVertex2D;

    inline  PFixed() {}
    inline  PFixed              (const float value);
    inline  PFixed              (const int value);

    inline  PFixed  operator-   ()                  const;                                          ///< Computes the negation \f$ (-x) \f$
    inline  PFixed  operator+   (const PFixed v)    const;                                          ///< Adds two PFixed
    inline  PFixed  operator-   (const PFixed v)    const;                                          ///< Subtracts two PFixed
    inline  PFixed  operator*   (const PFixed v)    const;                                          ///< Multiplies two PFixed
    inline  PFixed  operator*   (const int s)       const;                                          ///< Scales one PFixed
            PFixed  operator/   (const PFixed v)    const;                                          ///< Divides two PFixed
    inline  PFixed  operator/   (const int v)       const;                                          ///< Divides a PFixed with an integer
    inline  PFixed  operator%   (const PFixed v)    const;                                          ///< Modulos a PFixed with a PFixed
    inline  PFixed  operator%   (const int v)       const;                                          ///< Modulos a PFixed with an integer
    inline  PFixed  operator^   (const PFixed v)    const;                                          ///< Computes the exponential \f$ (x^v) \f$
    inline  PFixed  operator<<  (const unsigned v)  const;                                          ///< Multiplies a PFixed by \f$ 2^v \f$ ie: \f$ (x * 2^v)\f$
    inline  PFixed  operator>>  (const unsigned v)  const;                                          ///< Divides a PFixed by \f$ 2^v \f$ ie: \f$ (x / 2^v)\f$

    inline  PFixed &operator+=  (const PFixed v);                                                   ///< Adds two PFixed and store
    inline  PFixed &operator-=  (const PFixed v);                                                   ///< Subtracts two PFixed and store
    inline  PFixed &operator*=  (const PFixed v);                                                   ///< Multiplies two PFixed and store
    inline  PFixed &operator*=  (const int v);                                                      ///< Scales one PFixed and store
    inline  PFixed &operator/=  (const PFixed v);                                                   ///< Divides two PFixed and store
    inline  PFixed &operator%=  (const PFixed v);                                                   ///< Modulos a PFixed with a PFixed and store
    inline  PFixed &operator%=  (const int v);                                                      ///< Modulos a PFixed with an integer and store
    inline  PFixed &operator^=  (const PFixed v);                                                   ///< Computes the exponential\f$ (x^v) \f$ and store
    inline  PFixed &operator<<= (const unsigned v);                                                 ///< Multiplies a PFixed by \f$ 2^v \f$ ie: \f$ (x * 2^v)\f$ and store
    inline  PFixed &operator>>= (const unsigned v);                                                 ///< Divides a PFixed by \f$ 2^v \f$ ie: \f$ (x / 2^v)\f$ and store

    inline  bool    operator>   (const PFixed v)    const;                                          ///< Compares to see if a PFixed > v
    inline  bool    operator>=  (const PFixed v)    const;                                          ///< Compares to see if a PFixed >= v
    inline  bool    operator<   (const PFixed v)    const;                                          ///< Compares to see if a PFixed < v
    inline  bool    operator<=  (const PFixed v)    const;                                          /// < Compares to see if a PFixed <= v
    inline  bool    operator==  (const PFixed v)    const;                                          ///< Compares to see if a PFixed is equal to v
    inline  bool    operator!=  (const PFixed v)    const;                                          ///< Compares tos ee if a PFixed is not-equal to v

    inline  PFixed &operator=   (const int v);                                                      ///< Sets the fixed to an integer
            PFixed &operator=   (const float v);                                                    ///< Sets the fixed to a float
    inline  void    SetRaw      (const unsigned v);                                                 ///< Sets a raw-byte value

    inline          operator    int     ()          const;                                          ///< Converts a PFixed to an int
                    operator    float   ()          const;                                          ///< Converts a PFixed to a float

            static  PFixed      Inverse (const PFixed x);                                           ///< Computes the inverse \f$ (1/x) \f$
            static  PFixed      MulDiv  (PFixed MulD, PFixed MulR, PFixed Div);                     ///< Multiplies, then divides ie: \f$ (MulD * MulR / Div) \f$
    inline  static  PFixed      MulSHR  (PFixed MulD, PFixed MulR, const unsigned Div);             ///< Multiplies, then shift rights ie: \f$ (MulD * MulR >> Div) \f$
            static  PFixed      MulSHR  (PFixed MulD, int MulR, const unsigned Div);                ///< Multiplies, then shift right ie : \f$ (MulD * MulR >> Div) \f$

            static  PFixed      Cos     (PFixed Angle);                                             ///< Computes the cosine
            static  PFixed      Sin     (PFixed Angle);                                             ///< Computes the sine
            static  PFixed      Tan     (PFixed Angle);                                             ///< Computes the tangent
    inline  static  void        SinCos  (PFixed Angle, PFixed &S, PFixed &C);                       ///< Computes sine and cosine simultaneously
            static  PFixed      ArcTan  (const PFixed x, PFixed y);                                 ///< Computes the arctangent
            static  PFixed      ArcSin  (const PFixed v);                                           ///< Computes the arcsinus
    inline  static  PFixed      ArcCos  (const PFixed v);                                           ///< Computes the arccosine
            static  PFixed      Sqrt    (const PFixed v);                                           ///< Computes the square root

            static  PFixed      Pow2    (const PFixed v);                                           ///< Computes the power of 2
    inline  static  PFixed      Pow2i   (const int v);                                              ///< Computes the power of 2 given the highest-order bit
    inline  static  PFixed      Log     (const PFixed v, const PFixed Base);                        ///< Computes any base logarithm
            static  PFixed      Log2    (const PFixed v);                                           ///< Computes the base-2 logarithm
    inline  static  int         Log2i   (const PFixed v);                                           ///< Computes the highest-order base-2 logarithm

    inline  static  int         Trunc   (const PFixed v);                                           ///< Returns the integer part
    inline  static  PFixed      Frac    (const PFixed v);                                           ///< Returns the fractional part
    inline  static  int         Ceil    (const PFixed v);                                           ///< Smallest integer value greater or equal to a PFixed
    inline  static  int         Floor   (const PFixed v);                                           ///< Largest integer value smaller or equal to a PFixed
    inline  static  int         Round   (const PFixed v);                                           ///< Rounds to the nearest integer
    inline  static  PFixed      Abs     (const PFixed v);                                           ///< Returns the absolute value
    inline  static  bool        IsNan   (const PFixed v);                                           ///< Returns true/false if the value is NaN
    inline  static  unsigned    GetRaw  (const PFixed &v);                                          ///< Returns the raw-byte value

    static  int     ToAlpha             (const PFixed v);                                           ///< Converts a fixed point into an alpha value [0, 256]
            void    FromAlpha           (const int Alpha);                                          ///< Converts an alpha value into a fixed point


    static const PFixed NaN;                                                                        ///< Representation of Not A Number

private:
    inline  PFixed              (const unsigned value);                                             ///< Constructor that takes a raw fixed-point value
    inline  PFixed &operator=   (const unsigned v);                                                 ///< Sets the fixed to a raw fixedpoint format

    int Value;                                                                                      ///< Fixed representation
} PPACKED;



#include "PFixed.inl"

/// @}
#endif
