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
#ifndef PFLOAT_H
#define PFLOAT_H

#include "PCommon.h"

/// \addtogroup Backend
///  @{



/**
 *  Fixeding point type
**/
struct PEXPORT PFloat {
    friend struct Tests;

    PFloat() {}
    PFloat(const float value);
    PFloat(const int value);
    PFloat(const unsigned value);

    inline  PFloat  operator-   ()                  const;                                          ///< Computes the negation \f$ (-x) \f$
    inline  PFloat  operator+   (const PFloat v)    const;                                          ///< Adds two PFloat
    inline  PFloat  operator-   (const PFloat v)    const;                                          ///< Subtracts two PFloat
    inline  PFloat  operator*   (const PFloat v)    const;                                          ///< Multiplies two PFloat
    inline  PFloat  operator*   (const int s)       const;                                          ///< Scales one PFloat
    inline  PFloat  operator/   (const PFloat v)    const;                                          ///< Divides two PFloat
    inline  PFloat  operator/   (const int v)       const;                                          ///< Divides a PFloat with an integer
    inline  PFloat  operator%   (const PFloat v)    const;                                          ///< Modulos a PFloat with a PFloat
    inline  PFloat  operator%   (const int v)       const;                                          ///< Modulos a PFloat with an integer
    inline  PFloat  operator^   (const PFloat v)    const;                                          ///< Computes the exponential \f$ (x^v) \f$
    inline  PFloat  operator<<  (const unsigned v)  const;                                          ///< Multiplies a PFloat by \f$ 2^v \f$ ie: \f$ (x * 2^v)\f$
    inline  PFloat  operator>>  (const unsigned v)  const;                                          ///< Divides a PFloat by \f$ 2^v \f$ ie: \f$ (x / 2^v)\f$

    inline  PFloat &operator+=  (const PFloat v);                                                   ///< Adds two PFloat and store
    inline  PFloat &operator-=  (const PFloat v);                                                   ///< Subtracts two PFloat and store
    inline  PFloat &operator*=  (const PFloat v);                                                   ///< Multiplies two PFloat and store
    inline  PFloat &operator*=  (const int s);                                                      ///< Scales one PFloat and store
    inline  PFloat &operator/=  (const PFloat v);                                                   ///< Divides two PFloat and store
    inline  PFloat &operator%=  (const PFloat v);                                                   ///< Modulos a PFloat with a PFloat and store
    inline  PFloat &operator%=  (const int v);                                                      ///< Modulos a PFloat with an integer and store
    inline  PFloat &operator^=  (const PFloat v);                                                   ///< Computes the exponential\f$ (x^v) \f$ and store
    inline  PFloat &operator<<= (const unsigned v);                                                 ///< Multiplies a PFloat by \f$ 2^v \f$ ie: \f$ (x * 2^v)\f$ and store
    inline  PFloat &operator>>= (const unsigned v);                                                 ///< Divides a PFloat by \f$ 2^v \f$ ie: \f$ (x / 2^v)\f$ and store

    inline  bool    operator>   (const PFloat v)    const;                                          ///< Compares to see if a PFloat > v
    inline  bool    operator>=  (const PFloat v)    const;                                          ///< Compares to see if a PFloat >= v
    inline  bool    operator<   (const PFloat v)    const;                                          ///< Compares to see if a PFloat < v
    inline  bool    operator<=  (const PFloat v)    const;                                          /// < Compares to see if a PFloat <= v
    inline  bool    operator==  (const PFloat v)    const;                                          ///< Compares to see if a PFloat is equal to v
    inline  bool    operator!=  (const PFloat v)    const;                                          ///< Compares tos ee if a PFloat is not-equal to v

    inline  PFloat &operator=   (const int v);                                                      ///< Sets the float to an integer
    inline  PFloat &operator=   (const float v);                                                    ///< Sets the float to a float
    inline  void    SetRaw      (const unsigned v);                                                 ///< Sets a raw-byte value

    inline          operator    int     ()          const;                                          ///< Converts a PFloat to an int
    inline          operator    float   ()          const;                                          ///< Converts a PFloat to a float

    inline static  PFloat  Inverse          (const PFloat x);                                       ///< Computes the inverse \f$ (1/x) \f$
    inline static  PFloat  MulDiv           (PFloat MulD, PFloat MulR, PFloat Div);                 ///< Multiplies, then divides ie: \f$ (MulD * MulR / Div) \f$
    inline static  PFloat  MulSHR           (PFloat MulD, PFloat MulR, const unsigned Div);         ///< Multiplies, then shift rights ie: \f$ (MulD * MulR >> Div) \f$
    inline static  PFloat  MulSHR           (PFloat MulD, int MulR, const unsigned Div);            ///< Multiplies, then shift rights ie: \f$ (MulD * MulR >> Div) \f$

    inline static  PFloat   Cos             (PFloat Angle);                                         ///< Computes the cosine
    inline static  PFloat   Sin             (PFloat Angle);                                         ///< Computes the sine
    inline static  PFloat   Tan             (PFloat Angle);                                         ///< Computes the tangent
    inline static  void     SinCos          (PFloat Angle, PFloat &S, PFloat &C);                   ///< Computes sine and cosine simultaneously
    inline static  PFloat   ArcTan          (const PFloat x, PFloat y);                             ///< Computes the arctangent
    inline static  PFloat   ArcSin          (const PFloat v);                                       ///< Computes the arcsinus
    inline static  PFloat   ArcCos          (const PFloat v);                                       ///< Computes the arccosine
    inline static  PFloat   Sqrt            (const PFloat v);                                       ///< Computes the square root


    inline static  PFloat   Pow2            (const PFloat v);                                       ///< Computes the power of 2
    inline static  PFloat   Pow2i           (const int v);                                          ///< Computes the power of 2 given the highest-order bit
    inline static  PFloat   Log             (const PFloat v, const PFloat Base);                    ///< Computes any base logarithm
    inline static  PFloat   Log2            (const PFloat v);                                       ///< Computes the base-2 logarithm
    inline static  int      Log2i           (const PFloat v);                                       ///< Computes the highest-order base-2 logarithm

    inline static  int      Trunc           (const PFloat v);                                       ///< Returns the integer part
    inline static  PFloat   Frac            (const PFloat v);                                       ///< Returns the fractional part
    inline static  int      Ceil            (const PFloat v);                                       ///< Smallest integer value greater or equal to a PFloat
    inline static  int      Floor           (const PFloat v);                                       ///< Largest integer value smaller or equal to a PFloat
    inline static  int      Round           (const PFloat v);                                       ///< Rounds to the nearest integer
    inline static  PFloat   Abs             (const PFloat v);                                       ///< Returns the absolute value
    inline static  bool     IsNan           (const PFloat v);                                       ///< Return true/false if the value is NaN
    inline static  unsigned GetRaw          (const PFloat &v);                                      ///< Returns the raw-byte value

    inline static  int     ToAlpha          (const PFloat v);                                       ///< Converts a floating point into an alpha value [0, 256]
    inline         void    FromAlpha        (const int Alpha);                                      ///< Converts an alpha value into a floating point

    static const PFloat   NaN;                                                                      ///< Representation of Not A Number

private:
    float   Value;                                                                                  ///< Float representation
} PPACKED;

#include "PFloat.inl"

/// @}
#endif
