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
 *  \param val Value to operate on
 *  \param mask Mask of bits to be cleared
 *  \return \f$ (val \& (~mask)) \f$
**/
inline unsigned long BitClear(const unsigned long val, const unsigned long mask)
{
    unsigned long z;
#ifdef __arm__
    asm( "bic   %[z], %[x], %[y]    \n\t" : [z] "=r" (z) : [x] "r" (val), [y] "r" (mask) : );
#else
    z = (val & ~mask);
#endif
    return z;
}



/**
 *  Computes the integer log2 of a number
 *  \param x Value
 *  \return \f$ log_2(x) \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \n Let:
 *  \f{align*}
 *  n           &= 5 \\
 *  Result_n    &= 0 \\
 *  x_n         &= x \\
 *  \f}
 *  Slow method:
 *  \f$ \forall i=4..0 \f$, If \f$ (x > 2^{2i}) \f$\n
 *  \f{align*}
 *  Result_i    &= Result_{i+1} + 2^i \\
 *  x_i         &= \left[x_{i+1}2^{-i}\right] \\
 *  \f}
**/
#endif
/// \todo This only works for gcc
inline unsigned Log2(register unsigned x)
{
    return 31 - __builtin_clz(x);
}





inline PInt::PInt(const int value)      : Value(value) {}



/**
 *  \return Negative version of the value
**/
inline PInt PInt::operator-() const
{
    return PInt(-Value);
}



/**
 *  \param v addend
 *  \return \f$ x + v \f$
**/
inline PInt PInt::operator+(const PInt v) const
{
    return PInt(Value + v.Value);
}



/**
 *  \param v minuend
 *  \return \f$ x - v \f$
**/
inline PInt PInt::operator-(const PInt v) const
{
    return PInt(Value - v.Value);
}



/**
 *  \param v multiplier
 *  \return \f$ x \cdot v \f$
**/
inline PInt PInt::operator*(const PInt v) const
{
    return PInt(Value * v.Value);
}



/**
 *  \param v divisor
 *  \return \f$ x \div v \f$
**/
inline PInt PInt::operator/(const PInt v) const
{
    return PInt(Value / v.Value);
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PInt PInt::operator%(const PInt v) const
{
    return PInt(Value % v.Value);
}



/**
 *  \param v Exponent
 *  \return \f$ x^v \f$
**/
inline PInt PInt::operator^(const PInt ) const
{
    PASSERT(0, "Not implemented");
    return PInt(0);
}



/**
 *  \param v Base-2 Exponent
 *  \return \f$ x2^v \f$
**/
inline PInt PInt::operator<<(const unsigned ) const
{
    PASSERT(0, "Not implemented");
    return PInt(0);
}



/**
 *  \param v Base-2 Negative Exponent
 *  \return \f$ x/2^v \f$
**/
inline PInt PInt::operator>>(const unsigned ) const
{
    PASSERT(0, "Not implemented");
    return PInt(0);
}



/**
 *  \param v Addend
 *  \return \f$ x + v \f$
**/
inline PInt &PInt::operator+=(const PInt v)
{
    Value += v.Value;

    return *this;
}



/**
 *  \param v Minuend
 *  \return \f$ x - v \f$
**/
inline PInt &PInt::operator-=(const PInt v)
{
    Value -= v.Value;

    return *this;
}



/**
 *  \param v Multiplier
 *  \return \f$ x \cdot v \f$
**/
inline PInt &PInt::operator*=(const PInt v)
{
    Value *= v.Value;

    return *this;
}



/**
 *  \param v Divisor
 *  \return \f$ x / v \f$
**/
inline PInt &PInt::operator/=(const PInt v)
{
    Value /= v.Value;

    return *this;
}



/**
 *  \param v Modulo
 *  \return \f$ x \pmod v \f$
**/
inline PInt &PInt::operator%=(const PInt v)
{
    Value = Value % v.Value;

    return *this;
}



/**
 *  \param v Exponent
 *  \return \f$ x^v \f$
**/
inline PInt &PInt::operator^=(const PInt )
{
    PASSERT(0, "Not implemented");
    return *this;
}



/**
 *  \param v Base-2 exponent
 *  \return \f$ x2^v \f$
**/
inline PInt &PInt::operator<<=(const unsigned v)
{
    Value <<= -v;

    return *this;
}



/**
 *  \param v Base-2 negative exponent
 *  \return \f$ x/2^v \f$
**/
inline PInt &PInt::operator>>=(const unsigned v)
{
    Value >>= v;

    return *this;
}



/**
 *  \param v Value
 *  \return \f$ x > v \f$
**/
inline bool PInt::operator>(const PInt v) const
{
    return Value > v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \ge v \f$
**/
inline bool PInt::operator>=(const PInt v) const
{
    return Value >= v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x < v \f$
**/
inline bool PInt::operator<(const PInt v) const
{
    return Value < v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \le v \f$
**/
inline bool PInt::operator<=(const PInt v) const
{
    return Value <= v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x = v \f$
**/
inline bool PInt::operator==(const PInt v) const
{
    return Value == v.Value;
}



/**
 *  \param v Value
 *  \return \f$ x \ne v \f$
**/
inline bool PInt::operator!=(const PInt v) const
{
    return Value != v.Value;
}



/**
 *  \return \f$ [v] \f$
**/
inline PInt::operator int() const
{
    return Value;
}



/**
 *  \param v Value
 *  \return this
**/
inline PInt &PInt::operator=(const int v)
{
    Value = v;

    return *this;
}



/**
 *  \param v Value
 *  \return Absolute value of v
**/
inline PInt PInt::Abs(const PInt v)
{
    return (v < PInt(0)) ? -v : v;
}

