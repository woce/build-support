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
 *  This file specifies a compiler-supported floating point class implementation
**/
#include <math.h>
#define PI 3.141592503f     // I know it's not accurate, but it IS bit-wise accurate for a 23-bit float
#define DEG2RAD(x) ((x) * (PI / 180.0f))
#define RAD2DEG(x) ((x) * (180.0f / PI))



inline PFloat::PFloat(const float value)    : Value(value) {}
inline PFloat::PFloat(const int value)      : Value(value) {}
inline PFloat::PFloat(const unsigned value) : Value((int)value / 65536.0f) {}



/**
 *  \return Inverse of the value
**/
inline PFloat PFloat::Inverse(const PFloat x)
{
    return PFloat(1.0f / x.Value);
}



/**
 *  \return Negative version of the value
**/
inline PFloat PFloat::operator-() const
{
    return PFloat(-Value);
}



/**
 *  \param v addend
 *  \return \f$ x + v \f$
**/
inline PFloat PFloat::operator+(const PFloat v) const
{
    return PFloat(Value + v.Value);
}



/**
 *  \param v minuend
 *  \return \f$ x - v \f$
**/
inline PFloat PFloat::operator-(const PFloat v) const
{
    return PFloat(Value - v.Value);
}



/**
 *  \param v multiplier
 *  \return \f$ x \cdot v \f$
**/
inline PFloat PFloat::operator*(const PFloat v) const
{
    return PFloat(Value * v.Value);
}



/**
 *  \param s scalar
 *  \return \f$ x * v \f$
**/
inline PFloat PFloat::operator*(const int s) const
{
    return PFloat(Value * s);
}



/**
 *  \param v divisor
 *  \return \f$ x \div v \f$
**/
inline PFloat PFloat::operator/(const PFloat v) const
{
    return PFloat(Value / v.Value);
}



/**
 *  \param v divisor
 *  \return \f$ x \div v \f$
**/
inline PFloat PFloat::operator/(const int v) const
{
    return *this / PFloat(v);
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PFloat PFloat::operator%(const PFloat v) const
{
    return PFloat(fmodf(Value, v.Value));
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PFloat PFloat::operator%(const int v) const
{
    return PFloat(fmodf(Value, v));
}



/**
 *  \param v Exponent
 *  \return \f$ x^v \f$
**/
inline PFloat PFloat::operator^(const PFloat v) const
{
    return PFloat(expf(v.Value * log(Value)));
}



/**
 *  \param v Base-2 Exponent
 *  \return \f$ x2^v \f$
**/
inline PFloat PFloat::operator<<(const unsigned v) const
{
    return PFloat(ldexpf(Value, v));
}



/**
 *  \param v Base-2 Negative Exponent
 *  \return \f$ x/2^v \f$
**/
inline PFloat PFloat::operator>>(const unsigned v) const
{
    return PFloat(ldexpf(Value, -v));
}



/**
 *  \param v Addend
 *  \return \f$ x + v \f$
**/
inline PFloat &PFloat::operator+=(const PFloat v)
{
    Value += v.Value;

    return *this;
}



/**
 *  \param v Minuend
 *  \return \f$ x - v \f$
**/
inline PFloat &PFloat::operator-=(const PFloat v)
{
    Value -= v.Value;

    return *this;
}



/**
 *  \param v Multiplier
 *  \return \f$ x \cdot v \f$
**/
inline PFloat &PFloat::operator*=(const PFloat v)
{
    Value *= v.Value;

    return *this;
}



/**
 *  \param s Scalar
 *  \return \f$ x * s \f$
**/
inline PFloat &PFloat::operator*=(const int s)
{
    Value *= s;

    return *this;
}



/**
 *  \param v Divisor
 *  \return \f$ x / v \f$
**/
inline PFloat &PFloat::operator/=(const PFloat v)
{
    Value /= v.Value;

    return *this;
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PFloat &PFloat::operator%=(const PFloat v)
{
    Value = fmodf(Value, v.Value);

    return *this;
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PFloat &PFloat::operator%=(const int v)
{
    Value = fmodf(Value, v);

    return *this;
}



/**
 *  \param v Exponent
 *  \return \f$ x^v \f$
**/
inline PFloat &PFloat::operator^=(const PFloat v)
{
    Value = expf(v.Value * log(Value));

    return *this;
}



/**
 *  \param v Base-2 exponent
 *  \return \f$ x2^v \f$
**/
inline PFloat &PFloat::operator<<=(const unsigned v)
{
    Value *= exp2f(-v);

    return *this;
}



/**
 *  \param v Base-2 negative exponent
 *  \return \f$ x/2^v \f$
**/
inline PFloat &PFloat::operator>>=(const unsigned v)
{
    Value *= exp2f(v);

    return *this;
}



/**
 *  \param v Value
 *  \return \f$ x > v \f$
**/
inline bool PFloat::operator>(const PFloat v) const
{
    return Value > v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \ge v \f$
**/
inline bool PFloat::operator>=(const PFloat v) const
{
    return Value >= v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x < v \f$
**/
inline bool PFloat::operator<(const PFloat v) const
{
    return Value < v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \le v \f$
**/
inline bool PFloat::operator<=(const PFloat v) const
{
    return Value <= v.Value;
}



#include <stdio.h>
/**
 *  \param v Value
 *  \return \f$ x = v \f$
**/
inline bool PFloat::operator==(const PFloat v) const
{
    return Value == v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \ne v \f$
**/
inline bool PFloat::operator!=(const PFloat v) const
{
    return Value != v.Value;
}



/**
 *  \return \f$ [v] \f$
**/
inline PFloat::operator int() const
{
    return (int)Value;
}



/**
 *  \param v Value
 *  \return this
**/
inline PFloat &PFloat::operator=(const int v)
{
    Value = v;

    return *this;
}



/**
 *  \param v Value
 *  \return this
**/
inline PFloat &PFloat::operator=(const float v)
{
    Value = v;

    return *this;
}



/**
 *  \return float version of the value
**/
inline PFloat::operator float() const
{
    return Value;
}



/**
 *  \param MulD Multiplicand
 *  \param MulR Multiplier
 *  \param Div Divisor
 *  \return \f$ (MulD \cdot MulR) / Div \f$
**/
inline PFloat PFloat::MulDiv(const PFloat MulD, const PFloat MulR, const PFloat Div)
{
    return PFloat(MulD.Value * MulR.Value / Div.Value);
}



/**
 *  \param MulD Multiplicand
 *  \param MulR Multiplier
 *  \param Div Divisor
 *  \return \f$ (MulD \cdot MulR) / Div \f$
**/
inline PFloat PFloat::MulSHR(const PFloat MulD, const PFloat MulR, const unsigned Div)
{
    return PFloat(MulD.Value * MulR.Value / (1 << Div));
}



/**
 *  \param MulD Multiplicand
 *  \param MulR Multiplier
 *  \param Div Divisor
 *  \return \f$ (MulD \cdot MulR) / Div \f$
**/
inline PFloat PFloat::MulSHR(const PFloat MulD, const int MulR, const unsigned Div)
{
    return PFloat(MulD.Value * MulR / (1 << Div));
}



/**
 *  \param Angle Angle [0, 360)
 *  \return \f$ \cos(a) \f$
**/
inline PFloat PFloat::Cos(const PFloat Angle)
{
    return PFloat(cosf(DEG2RAD(Angle.Value)));
}



/**
 *  \param Angle Angle [0, 360)
 *  \return \f$ \sin(a) \f$
**/
inline PFloat PFloat::Sin(const PFloat Angle)
{
    return PFloat(sinf(DEG2RAD(Angle.Value)));
}



/**
 *  \param Angle Angle [0, 360)
 *  \param S Reference to the sine result \f$ sin(a) \f$
 *  \param C Reference to the cosine result \f$ cos(a) \f$
**/
inline void PFloat::SinCos(const PFloat Angle, PFloat &S, PFloat &C)
{
    sincosf(DEG2RAD(Angle.Value), &S.Value, &C.Value);
}



/**
 *  \param Angle Angle [0, 360)
 *  \return \f$ \tan(a) \f$
**/
inline PFloat PFloat::Tan(const PFloat Angle)
{
    return PFloat(tanf(DEG2RAD(Angle.Value)));
}



/**
 *  \param x value in x
 *  \param y value in y
 *  \return \f$ \arctan(x, y) \f$
**/
inline PFloat PFloat::ArcTan(const PFloat x, PFloat y)
{
    return PFloat(RAD2DEG(atan2f(y.Value, x.Value)));
}



/**
 *  \param v value
 *  \return \f$ \arcsin(v) \f$
**/
inline PFloat PFloat::ArcSin(const PFloat v)
{
    return PFloat(RAD2DEG(asinf(v.Value)));
}



/**
 *  \param v value
 *  \return \f$ \arccos(v) \f$
**/
inline PFloat PFloat::ArcCos(const PFloat v)
{
    return PFloat(RAD2DEG(acosf(v.Value)));
}



/**
 *  \param v Value
 *  \return \f$ \sqrt{v} \f$
**/
inline PFloat PFloat::Sqrt(const PFloat v)
{
    return PFloat(sqrtf(v.Value));
}



/**
 *  \param v Value
 *  \return \f$ \log_2(v) \f$
**/
inline PFloat PFloat::Pow2(const PFloat v)
{
    return PFloat(powf(2.0f, v.Value));
}



/**
 *  \param v Highest-ordered bit
 *  \return \f$ 2^{v - 127} \f$
**/
inline PFloat PFloat::Pow2i(const int v)
{
    const int F = (v << 23);

    return PFloat(*(float *)&F);
}



/**
 *  \param v Value
 *  \return \f$ \log_2(v) \f$
**/
inline PFloat PFloat::Log2(const PFloat v)
{
    return PFloat(log2f(v.Value));
}



/**
 *  \param v Value
 *  \param Base Logarithm base
 *  \return \f$ \log_b(v) \f$
**/
inline PFloat PFloat::Log(const PFloat v, const PFloat Base)
{
    return PFloat(log2f(v.Value) * log2f(Base.Value));
}



/**
 *  \param v Value
 *  \return Position of the highest set bit in Floating point format (Bit + 127)
 **/
inline int PFloat::Log2i(const PFloat v)
{
    return (*(unsigned *)&v >> 23) & 0xFF;
}



/**
 *  \param v Value
 *  \return \f$ [v] \f$
**/
inline int PFloat::Trunc(const PFloat v)
{
    return (int)truncf(v.Value);
}



/**
 *  \param v Value
 *  \return \f$ v - [v] \f$
**/
inline PFloat PFloat::Frac(const PFloat v)
{
    return PFloat(v - PFloat(Trunc(v)));
}



/**
 *  \param v Value
 *  \return \f$ \lceil v \rceil \f$
**/
inline int PFloat::Ceil(const PFloat v)
{
    return (int)ceilf(v.Value);
}



/**
 *  \param v Value
 *  \return \f$ \lfloor v \rfloor \f$
**/
inline int PFloat::Floor(const PFloat v)
{
    return (int)floorf(v.Value);
}



/**
 *  \param v Value
 *  \return \f$ x; \forall y \in \{\lfloor v \rfloor, \lceil v \rceil\}; |x-v| \le |y-v| \f$
**/
inline int PFloat::Round(const PFloat v)
{
    return (int)roundf(v.Value);
}



/**
 *  \param v Value
 *  \return Alpha [0, 256]
**/
inline int PFloat::ToAlpha(const PFloat v)
{
    return Round(v * 256);
}



/**
 *  \param Alpha [0, 256]
**/
inline void PFloat::FromAlpha(const int Alpha)
{
	PASSERT(false, "Untested");
    Value = Alpha * 0.00390625f;
}


/**
 *  \param v Value
 *  \return Absolute value of v
**/
inline PFloat PFloat::Abs(const PFloat v)
{
    return (v < PFloat(0)) ? -v : v;
}



/**
 *  \param v Value
 *  \return true/false if the value is NaN
**/
inline bool PFloat::IsNan(const PFloat v)
{
    return isnanf(v.Value);
}



/**
 *  \param v raw-byte value to set the value to
 *  \note One should generally not use this function
**/
inline void PFloat::SetRaw(const unsigned v)
{
    *(unsigned *)&Value = v;
}



/**
 *  \param v Fixed point to retrieve the raw value from
 *  \return Raw-byte value
 *  \note One should generally not use this function
**/
inline unsigned PFloat::GetRaw(const PFloat &v)
{
    return *(unsigned *)&v.Value;
}
