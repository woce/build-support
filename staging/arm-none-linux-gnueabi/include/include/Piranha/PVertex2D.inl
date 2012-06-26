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


#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \return \f$ <X_y, -X_x> \f$
**/
#endif
inline PVertex2D PVertex2D::operator~() const
{
    return PVertex2D(Y, -X);
}



/**
 *  \returns \f$ -\vec{X} \f$
**/
inline PVertex2D   PVertex2D::operator-() const
{
    return PVertex2D(-X, -Y);
}



/**
 *  \param v addend
 *  \return \f$ \vec{X} + \vec{v} \f$
**/
inline PVertex2D PVertex2D::operator+(const PVertex2D v) const
{
    return PVertex2D(X + v.X, Y + v.Y);
}



/**
 *  \param v minued
 *  \return \f$ \vec{X} - \vec{v} \f$
**/
inline PVertex2D PVertex2D::operator-(const PVertex2D v) const
{
    return PVertex2D(X - v.X, Y - v.Y);
}



/**
 *  \param v crossand
 *  \return \f$ \vec{X} \times \vec{v} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \vec{X} \times \vec{v} = X_xv_y - X_yv_x \f]
**/
#endif
inline PValue PVertex2D::operator/(const PVertex2D v) const
{
    return X * v.Y - Y * v.X;
}



/**
 *  \param v crossand
 *  \return \f$ \vec{X} \bullet \vec{v} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \vec{X} \bullet \vec{v} = X_xv_x + X_yv_y \f]
**/
#endif
inline PValue PVertex2D::operator*(const PVertex2D v) const
{
    return X * v.X + Y * v.Y;
}



/**
 *  \param v crossand
 *  \return \f$ v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ v\vec{X} = <vX_x, vX_y> \f]
**/
#endif
inline PVertex2D PVertex2D::operator*(const PValue v) const
{
    return PVertex2D(X * v, Y * v);
}



/**
 *  \param v crossand
 *  \return \f$ \frac{1}{v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}> \f]
**/
#endif
inline PVertex2D PVertex2D::operator/(const PValue v) const
{
    const PValue Inv = PValue::Inverse(v);

    return PVertex2D(X * Inv, Y * Inv);
}



/**
 *  \param v multiplicand
 *  \return \f$ <X_x * v_x, X_y * v_y> \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}> \f]
**/
#endif
inline PVertex2D PVertex2D::operator^(const PVertex2D v) const
{
    return PVertex2D(X * v.X, Y * v.Y);
}



/**
 *  \param v scalar
 *  \return \f$ 2^v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^v\vec{X} = <2^vX_x, 2^vX_y> \f]
**/
#endif
inline PVertex2D PVertex2D::operator<<(const unsigned v) const
{
    return PVertex2D(X << v, Y << v);
}



/**
 *  \param v scalar
 *  \return \f$ 2^{-v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^{-v}\vec{X} = <2^{-v}X_x, 2^{-v}X_y> \f]
**/
#endif
inline PVertex2D PVertex2D::operator>>(const unsigned v) const
{
    return PVertex2D(X >> v, Y >> v);
}



/**
 *  \param v addend
 *  \return \f$ \vec{X} + \vec{v} \f$
**/
inline PVertex2D &PVertex2D::operator+=(const PVertex2D v)
{
    X += v.X;
    Y += v.Y;

    return *this;
}



/**
 *  \param v minued
 *  \return \f$ \vec{X} - \vec{v} \f$
**/
inline PVertex2D &PVertex2D::operator-=(const PVertex2D v)
{
    X -= v.X;
    Y -= v.Y;

    return *this;
}



/**
 *  \param v scalar
 *  \return \f$ v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ v\vec{X} = <vX_x, vX_y> \f]
**/
#endif
inline PVertex2D &PVertex2D::operator*=(const PValue v)
{
    X *= v;
    Y *= v;

    return *this;
}



/**
 *  \param v scalar
 *  \return \f$ \frac{1}{v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}> \f]
**/
#endif
inline PVertex2D &PVertex2D::operator/=(const PValue v)
{
    const PValue Inv = PValue::Inverse(v);

    X *= Inv;
    Y *= Inv;

    return *this;
}



/**
 *  \param v multiplicand
 *  \return \f$ <X + v_X, Y + v_Y> \f$
**/
inline PVertex2D &PVertex2D::operator^=(const PVertex2D v)
{
    X *= v.X;
    Y *= v.Y;

    return *this;
}



/**
 *  \param v power
 *  \return \f$ 2^v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^v\vec{X} = <2^vX_x, 2^vX_y> \f]
**/
#endif
inline PVertex2D &PVertex2D::operator<<=(const unsigned v)
{
    X <<= v;
    Y <<= v;

    return *this;
}



/**
 *  \param v power
 *  \return \f$ 2^{-v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^{-v}\vec{X} = <2^{-v}X_x, 2^{-v}X_y> \f]
**/
#endif
inline PVertex2D &PVertex2D::operator>>=(const unsigned v)
{
    X >>= v;
    Y >>= v;

    return *this;
}



/**
 *  \param v Vertex to compare against
 *  \return \f$ x = v \f$
**/
inline bool PVertex2D::operator==(const PVertex2D v) const
{
    return (X == v.X) & (Y == v.Y);
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x \ne v \f$
**/
inline bool PVertex2D::operator!=(const PVertex2D v) const
{
    return (X != v.X) | (Y != v.Y);
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x > v \f$
**/
inline bool PVertex2D::operator>(const PVertex2D v) const
{
    return (Y > v.Y) || ((Y == v.Y) && (X > v.X));
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x >= v \f$
**/
inline bool PVertex2D::operator>=(const PVertex2D v) const
{
    return (Y > v.Y) || ((Y == v.Y) && (X >= v.X));
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x < v \f$
**/
inline bool PVertex2D::operator<(const PVertex2D v) const
{
    return (Y < v.Y) || ((Y == v.Y) && (X < v.X));
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x <= v \f$
**/
inline bool PVertex2D::operator<=(const PVertex2D v) const
{
    return (Y < v.Y) || ((Y == v.Y) && (X <= v.X));
}



/**
 *  \return \f$ ||v||_\infty \f$
**/
inline PValue PVertex2D::InfNorm(void) const
{
    const PValue a = PValue::Abs(X);
    const PValue b = PValue::Abs(Y);

    return a > b ? a : b;
}



/*
 *  Theses functions apply to floating points only
 */
#if (P_VALUES == P_FLOAT)
/**
 *  \return \f$ ||\vec{v}||_2 \f$
**/
inline PValue PVertex2D::Norm() const
{
    return PValue::Sqrt((X * X) + (Y * Y));
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \return
 *  \f{align*}
 *   V_x &= \frac{V_x}{\sqrt{V_x^2 + V_y^2}} \\
 *   V_y &= \frac{V_y}{\sqrt{V_x^2 + V_y^2}} \\
 *  \f}
**/
#endif
inline void PVertex2D::Normalize(void)
{
    const PValue InvSqrt = PValue::Inverse(Norm());

    X *= InvSqrt;
    Y *= InvSqrt;
}



/*
 *  Theses functions apply to fixed-points only
 */
#else

#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  A simple trick I never saw to compute this:
 *  \f{align*}
 *   V_x &= \frac{V_x}{\sqrt{V_x^2 + V_y^2}} = \cos(\arctan(V_x, V_y)) \\
 *   V_y &= \frac{V_y}{\sqrt{V_x^2 + V_y^2}} = \sin(\arctan(V_x, V_y)) \\
 *  \f}
**/
#endif
inline void PVertex2D::Normalize(void)
{
    const PValue Angle = PValue::ArcTan(X, Y);

    PValue::SinCos(Angle, Y, X);
}
#endif



inline bool PVertex2D::IsAligned(void) const
{
    if (PValue::Frac(X) >= (PValue(1) >> 8u))
        return false;

    if (PValue::Frac(Y) >= (PValue(1) >> 8u))
        return false;

    return true;
}

