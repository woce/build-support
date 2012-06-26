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

#define DABS(x) ((x) < 0 ? -(x) : (x))
#define DERROR(a, b, E) (round(DABS(a - b)) <= E)



/**
 *  \param value float to store
**/
inline PFixed::PFixed(const float value)
{
    *this = value;
}



/**
 *  \param value integer to store
**/
inline PFixed::PFixed(const int value)
{
    Value = value << 16;
}



/**
 *  \param value RAW unsigned to store
**/
inline PFixed::PFixed(const unsigned value)
{
    Value = value;
}



/**
 *  \return Negative version of the value
**/
inline PFixed PFixed::operator-() const
{
    return PFixed((unsigned)-Value);
}



/**
 *  \param v addend
 *  \return \f$ x + v \f$
**/
inline PFixed PFixed::operator+(const PFixed v) const
{
    return PFixed((unsigned)(Value + v.Value));
}



/**
 *  \param v minuend
 *  \return \f$ x - v \f$
**/
inline PFixed PFixed::operator-(const PFixed v) const
{
    return PFixed((unsigned)(Value - v.Value));
}



/**
 *  \param v multiplier
 *  \return \f$ x \cdot v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ a \cdot b   &= ab2^{-16} \f]
**/
#endif
inline PFixed PFixed::operator*(const PFixed v) const
{
#if defined(__arm__)
	unsigned product;
	unsigned temp;
	DRUN(long long Perfect = ((long long)v.Value * (long long)Value) >> 16; (void)Perfect);
	FASSERT(DABS(Perfect) < 0x80000000, "Multiplication overflow");
	asm volatile (
			"smull %0, %1, %2, %3\n\t"
			"lsr %0, %0, #16\n\t"
			"orr %0, %0, %1, lsl #16\n\t"
			: "=r" (product), "=r" (temp)
			: "r" (this->Value), "r" (v.Value)
			: );
	
	FASSERT(DERROR((int)product, Perfect, 1), "Fixed* is not precise");
	return PFixed(product);
#else
    return PFixed((unsigned)(((long long)Value * (long long)v.Value) >> 16));
#endif
}



/**
 *  \param s scalar
 *  \return \f$ x * v \f$
**/
inline PFixed PFixed::operator*(const int s) const
{
    return PFixed((unsigned)(Value * s));
}



/**
 *  \param v Divisor
 *  \return \f$ x \div v \f$
**/
inline PFixed PFixed::operator/(const int v) const
{
    PASSERT(v != 0, "Division by zero");

    return PFixed((unsigned)(Value / v));
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PFixed PFixed::operator%(const PFixed v) const
{
    PASSERT(v.Value != 0, "Division by zero");

    if (Value < 0)
        return PFixed((unsigned)(Value % v.Value + v.Value));

    return PFixed((unsigned)(Value % v.Value));
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PFixed PFixed::operator%(const int v) const
{
    return PFixed((unsigned)(Value % (v << 16)));
}



/**
 *  \param MulD Multiplicand
 *  \param MulR Multiplier
 *  \param Div 1 << Divisor
 *  \return \f$ (MulD /cdot MulR) >> Div \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ a \cdot b >> d   &= ab2^{-Div-16} \f]
**/
#endif
inline PFixed PFixed::MulSHR(PFixed MulD, int MulR, const unsigned Div)
{
    return PFixed((unsigned)((MulD.Value * MulR) >> Div));
}



/**
 *  \param MulD Multiplicand
 *  \param MulR Multiplier
 *  \param Div 1 << Divisor
 *  \return \f$ (MulD /cdot MulR) >> Div \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ a \cdot b >> d   &= ab2^{-Div-16} \f]
**/
#endif
inline PFixed PFixed::MulSHR(PFixed MulD, PFixed MulR, const unsigned Div)
{
    return PFixed((unsigned)((MulD.Value * MulR.Value) >> (16 + Div)));
}



/**
 *  \param v Exponent
 *  \return \f$ x^v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ x^y = 2^{y\log_2(x)} \f]
**/
#endif
inline PFixed PFixed::operator^(const PFixed v) const
{
    return Pow2(v * Log2(*this));
}



/**
 *  \param v Base-2 Exponent
 *  \return \f$ x2^v \f$
**/
inline PFixed PFixed::operator<<(const unsigned v) const
{
    return PFixed((unsigned)(Value << v));
}



/**
 *  \param v Base-2 Negative Exponent
 *  \return \f$ x/2^v \f$
**/
inline PFixed PFixed::operator>>(const unsigned v) const
{
    return PFixed((unsigned)(Value >> v));
}



/**
 *  \param v Addend
 *  \return \f$ x + v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator+
**/
#endif
inline PFixed &PFixed::operator+=(const PFixed v)
{
    Value += v.Value;

    return *this;
}



/**
 *  \param v Minuend
 *  \return \f$ x - v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator-
**/
#endif
inline PFixed &PFixed::operator-=(const PFixed v)
{
    Value -= v.Value;

    return *this;
}



/**
 *  \param v Multiplier
 *  \return \f$ x \cdot v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator*
**/
#endif
inline PFixed &PFixed::operator*=(const PFixed v)
{
    Value = (*this * v).Value;

    return *this;
}



/**
 *  \param s Scalar
 *  \return \f$ x * s \f$
**/
inline PFixed &PFixed::operator*=(const int s)
{
    Value *= s;

    return *this;
}



/**
 *  \param v Divisor
 *  \return \f$ x / v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator/
**/
#endif
inline PFixed &PFixed::operator/=(const PFixed v)
{
    PASSERT(v.Value != 0, "Division by zero");

    Value = (*this / v).Value;

    return *this;
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator%
**/
#endif
inline PFixed &PFixed::operator%=(const PFixed v)
{
    PASSERT(v.Value != 0, "Division by zero");

    Value = (*this % v).Value;

    return *this;
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator%
**/
#endif
inline PFixed &PFixed::operator%=(const int v)
{
    Value = (*this % v).Value;

    return *this;
}



/**
 *  \param v Exponent
 *  \return \f$ x^v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator^
**/
#endif
inline PFixed &PFixed::operator^=(const PFixed v)
{
    Value = (*this ^ v).Value;

    return *this;
}



/**
 *  \param v Base-2 exponent
 *  \return \f$ x2^v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator<<
**/
#endif
inline PFixed &PFixed::operator<<=(const unsigned v)
{
    Value <<= v;

    return *this;
}



/**
 *  \param v Base-2 negative exponent
 *  \return \f$ x/2^v \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \sa PFixed::operator>>
**/
#endif
inline PFixed &PFixed::operator>>=(const unsigned v)
{
    Value >>= v;

    return *this;
}



/**
 *  \param v Value
 *  \return \f$ x > v \f$
**/
inline bool PFixed::operator>(const PFixed v) const
{
    return Value > v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \ge v \f$
**/
inline bool PFixed::operator>=(const PFixed v) const
{
    return Value >= v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x < v \f$
**/
inline bool PFixed::operator<(const PFixed v) const
{
    return Value < v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \le v \f$
**/
inline bool PFixed::operator<=(const PFixed v) const
{
    return Value <= v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x = v \f$
**/
inline bool PFixed::operator==(const PFixed v) const
{
    return Value == v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \ne v \f$
**/
inline bool PFixed::operator!=(const PFixed v) const
{
    return Value != v.Value;
}



/**
 *  \return \f$ [v] \f$
**/
inline PFixed::operator int() const
{
    return Round(*this);
}



/**
 *  \param v Value
 *  \return this
**/
inline PFixed &PFixed::operator=(const int v)
{
    Value = v << 16;

    return *this;
}



/**
 *  \param v Value
 *  \return this
**/
inline PFixed &PFixed::operator=(const unsigned v)
{
    Value = v;

    return *this;
}



/**
 *  \param Angle Angle
 *  \param S Reference to the sine result \f$ \sin(a) \f$
 *  \param C Reference to the cosine result \f$ \cos(a) \f$
**/
inline void PFixed::SinCos(const PFixed Angle, PFixed &S, PFixed &C)
{
    if (Angle == PFixed(90)) {
        S = PFixed(1);
        C = PFixed(0);
    }
    else if (Angle == PFixed(270)) {
        S = PFixed(-1);
        C = PFixed(0);
    }
    else if (Angle == PFixed(180)) {
        S = PFixed(0);
        C = PFixed(-1);
    }
    else {
        S = Sin(Angle);
        C = Cos(Angle);
    }
}



/**
 *  \param Angle Angle
 *  \return \f$ \tan(a) \f$
**/
inline PFixed PFixed::Tan(const PFixed Angle)
{
    return Sin(Angle) / Cos(Angle);
}



/**
 *  \param v Value
 *  \return \f$ \arccos(v) \f$
**/
inline PFixed PFixed::ArcCos(PFixed v)
{
    return ArcSin(-v);
}



/**
 *  \param v Value
 *  \param Base Logarithm base
 *  \return \f$ \log_b(v) \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \log_b(x) = \frac{\log_2(x)}{\log_2(b)} \f}
**/
#endif
inline PFixed PFixed::Log(const PFixed v, const PFixed Base)
{
    return Log2(v) / Log2(Base);
}


/**
 *  \param v Highest-order bit
 *  \return \f$ 2^{v-127} \f$
**/
inline PFixed PFixed::Pow2i(const int v)
{
    return PFixed(1u << v);
}



/**
 *  \param v Value
 *  \return Position of the highest set bit in Fixed-point format (ie: Bit + 16)
**/
inline int PFixed::Log2i(const PFixed v)
{
    return 31 - __builtin_clz(v.Value);
}



/**
 *  \param v Value
 *  \return \f$ |v| \f$
**/
inline PFixed PFixed::Abs(const PFixed v)
{
    return v.Value > 0 ? v : -v;
}


/**
 *  \param v Value
 *  \return true/false if the value is NaN
**/
inline bool PFixed::IsNan(const PFixed v)
{
    return v == NaN;
}



/**
 *  \param v Value
 *  \return \f$ [v] \f$
**/
inline int PFixed::Trunc(const PFixed v)
{
    return Floor(v);
}



/**
 *  \param v Value
 *  \return \f$ v - [v] \f$
**/
inline PFixed PFixed::Frac(const PFixed v)
{
    return PFixed((unsigned)(v.Value - (v.Value & 0xFFFF0000)));
}



/**
 *  \param v Value
 *  \return \f$ \lceil v \rceil \f$
**/
inline int PFixed::Ceil(const PFixed v)
{
    return (v.Value + 0xFFFF) >> 16;
}



/**
 *  \param v Value
 *  \return \f$ \lfloor v \rfloor \f$
**/
inline int PFixed::Floor(const PFixed v)
{
    return v.Value >> 16;
}



/**
 *  \param v Value
 *  \return \f$ x; \forall y \in \{\lfloor v \rfloor, \lceil v \rceil\}; |x-v| \le |y-v| \f$
**/
inline int PFixed::Round(const PFixed v)
{
    return (v.Value + 0x7F00) >> 16;
}



/**
 *  \param v Value
 *  \return Alpha [0, 256]
**/
inline int PFixed::ToAlpha(const PFixed v)
{
    return (v.Value + 0x80) >> 8;
}



/**
 *  \param Alpha [0, 256]
**/
inline void PFixed::FromAlpha(const int Alpha)
{
    Value = (Alpha << 8) - 0x80;
}



/**
 *  \param v Fixed point to retrieve the raw value from
 *  \return Raw-byte value
 *  \note One should generally not use this function
**/
inline unsigned PFixed::GetRaw(const PFixed &v)
{
    return v.Value;
}



/**
 *  \param v raw-byte value to set the value to
 *  \note One should generally not use this function
**/
inline void PFixed::SetRaw(const unsigned v)
{
    Value = v;
}



#undef DABS
#undef DERROR
