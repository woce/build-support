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
 *  \returns \f$ -\vec{X} \f$
**/
inline PVertex4D PVertex4D::operator-() const
{
    return PVertex4D(-X, -Y, -Z, -W);
}



/**
 *  \param v addend
 *  \return \f$ \vec{X} + \vec{v} \f$
**/
inline PVertex4D PVertex4D::operator+(const PVertex4D v) const
{
    return PVertex4D(X + v.X, Y + v.Y, Z + v.Z, W + v.W);
}



/**
 *  \param v minued
 *  \return \f$ \vec{X} - \vec{v} \f$
**/
inline PVertex4D PVertex4D::operator-(const PVertex4D v) const
{
    return PVertex4D(X - v.X, Y - v.Y, Z - v.Z, W - v.W);
}



/**
 *  \param v crossand
 *  \return \f$ \vec{X} \bullet \vec{v} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \vec{X} \bullet \vec{v} = X_xv_x + X_yv_y + X_zv_z + X_wv_w \f]
**/
#endif
inline PValue PVertex4D::operator*(const PVertex4D v) const
{
    return X * v.X + Y * v.Y + Z * v.Z + W * v.W;
}



/**
 *  \param v crossand
 *  \return \f$ v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ v\vec{X} = <vX_x, vX_y, vX_z, vX_w> \f]
**/
#endif
inline PVertex4D PVertex4D::operator*(const PValue v) const
{
    return PVertex4D(X * v, Y * v, Z * v, W * v);
}



/**
 *  \param v crossand
 *  \return \f$ \frac{1}{v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}, \frac{X_z}{v}, \frac{X_w}{v}> \f]
**/
#endif
inline PVertex4D PVertex4D::operator/(const PValue v) const
{
    const PValue Inv = PValue::Inverse(v);

    return PVertex4D(X * Inv, Y * Inv, Z * Inv, W * Inv);
}



/**
 *  \param v multiplicand
 *  \return \f$ <X_x * v_x, X_y * v_y> \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}, \frac{X_z}{v}, \frac{X_w}{v},> \f]
**/
#endif
inline PVertex4D PVertex4D::operator^(const PVertex4D v) const
{
    return PVertex4D(X * v.X, Y * v.Y, Z * v.Z, W * v.W);
}



/**
 *  \param v scalar
 *  \return \f$ 2^v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^v\vec{X} = <2^vX_x, 2^vX_y, 2^vX_z, 2^vX_w> \f]
**/
#endif
inline PVertex4D PVertex4D::operator<<(const unsigned v) const
{
    return PVertex4D(X << v, Y << v, Z << v, W << v);
}



/**
 *  \param v scalar
 *  \return \f$ 2^{-v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^{-v}\vec{X} = <2^{-v}X_x, 2^{-v}X_y, 2^{-v}X_z, 2^{-v}X_w> \f]
**/
#endif
inline PVertex4D PVertex4D::operator>>(const unsigned v) const
{
    return PVertex4D(X >> v, Y >> v, Z >> v, W >> v);
}



/**
 *  \param v addend
 *  \return \f$ \vec{X} + \vec{v} \f$
**/
inline PVertex4D &PVertex4D::operator+=(const PVertex4D v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    W += v.W;

    return *this;
}



/**
 *  \param v minued
 *  \return \f$ \vec{X} - \vec{v} \f$
**/
inline PVertex4D &PVertex4D::operator-=(const PVertex4D v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    W -= v.W;

    return *this;
}



/**
 *  \param v scalar
 *  \return \f$ v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ v\vec{X} = <vX_x, vX_y, vX_z, vX_w> \f]
**/
#endif
inline PVertex4D &PVertex4D::operator*=(const PValue v)
{
    X *= v;
    Y *= v;
    Z *= v;
    W *= v;

    return *this;
}



/**
 *  \param v scalar
 *  \return \f$ \frac{1}{v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}, \frac{X_z}{v}, \frac{X_w}{v}> \f]
**/
#endif
inline PVertex4D &PVertex4D::operator/=(const PValue v)
{
    const PValue Inv = PValue::Inverse(v);

    X *= Inv;
    Y *= Inv;
    Z *= Inv;
    W *= Inv;

    return *this;
}



/**
 *  \param v multiplicand
 *  \return \f$ <X + v_X, Y + v_Y, Z + v_Z, W + v_W> \f$
**/
inline PVertex4D &PVertex4D::operator^=(const PVertex4D v)
{
    X *= v.X;
    Y *= v.Y;
    Z *= v.Z;
    W *= v.W;

    return *this;
}



/**
 *  \param v power
 *  \return \f$ 2^v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^v\vec{X} = <2^vX_x, 2^vX_y, 2^vX_z, 2^vX_w> \f]
**/
#endif
inline PVertex4D &PVertex4D::operator<<=(const unsigned v)
{
    X <<= v;
    Y <<= v;
    Z <<= v;
    W <<= v;

    return *this;
}



/**
 *  \param v power
 *  \return \f$ 2^{-v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^{-v}\vec{X} = <2^{-v}X_x, 2^{-v}X_y, 2^{-v}X_z, 2^{-v}X_w> \f]
**/
#endif
inline PVertex4D &PVertex4D::operator>>=(const unsigned v)
{
    X >>= v;
    Y >>= v;
    Z >>= v;
    W >>= v;

    return *this;
}



/**
 *  \param v Vertex to compare against
 *  \return \f$ x = v \f$
**/
inline bool PVertex4D::operator==(const PVertex4D v) const
{
    return (X == v.X) & (Y == v.Y) & (Z == v.Z) & (W == v.W);
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x \ne v \f$
**/
inline bool PVertex4D::operator!=(const PVertex4D v) const
{
    return (X != v.X) | (Y != v.Y) | (Z != v.Z) | (W != v.W);
}



/**
 *  \return \f$ ||v||_\infty \f$
**/
inline PValue PVertex4D::InfNorm(void) const
{
    const PValue a = PValue::Abs(X);
    const PValue b = PValue::Abs(Y);
    const PValue c = PValue::Abs(Z);
    const PValue d = PValue::Abs(W);

    const PValue ab = a > b ? a : b;
    const PValue cd = c > d ? c : d;

    return ab > cd ? ab : cd;
}



/*
 *  Theses functions apply to floating points only
 */
/**
 *  \return \f$ ||\vec{v}||_2 \f$
**/
inline PValue PVertex4D::Norm() const
{
    return PValue::Sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \return
 *  \f{align*}
 *   V_x &= \frac{V_x}{\sqrt{V_x^2 + V_y^2 + V_z^2 + V_w^2}} \\
 *   V_y &= \frac{V_y}{\sqrt{V_x^2 + V_y^2 + V_z^2 + V_w^2}} \\
 *   V_z &= \frac{V_y}{\sqrt{V_x^2 + V_y^2 + V_z^2 + V_w^2}} \\
 *   V_w &= \frac{V_y}{\sqrt{V_x^2 + V_y^2 + V_z^2 + V_w^2}} \\
 *  \f}
**/
#endif
inline void PVertex4D::Normalize(void)
{
    const PValue InvSqrt = PValue::Inverse((X * X) + (Y * Y) + (Z * Z) + (W * W));

    X *= InvSqrt;
    Y *= InvSqrt;
    Z *= InvSqrt;
    W *= InvSqrt;
}



inline bool PVertex4D::IsAligned(void) const
{
    if (PValue::Frac(X) >= (PValue(1) >> 8u))
        return false;

    if (PValue::Frac(Y) >= (PValue(1) >> 8u))
        return false;

    if (PValue::Frac(Z) >= (PValue(1) >> 8u))
        return false;

    if (PValue::Frac(W) >= (PValue(1) >> 8u))
        return false;

    return true;
}

