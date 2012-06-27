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
inline PVertex3D   PVertex3D::operator-() const
{
    return PVertex3D(-X, -Y, -Z);
}



/**
 *  \param v addend
 *  \return \f$ \vec{X} + \vec{v} \f$
**/
inline PVertex3D PVertex3D::operator+(const PVertex3D v) const
{
    return PVertex3D(X + v.X, Y + v.Y, Z + v.Z);
}



/**
 *  \param v minued
 *  \return \f$ \vec{X} - \vec{v} \f$
**/
inline PVertex3D PVertex3D::operator-(const PVertex3D v) const
{
    return PVertex3D(X - v.X, Y - v.Y, Z - v.Z);
}



/**
 *  \return \f$ \vec{X} x \vec{v} \f$
**/
inline PVertex3D PVertex3D::operator/(const PVertex3D v) const
{
    return PVertex3D(Y * v.Z - v.Y * Z, Z * v.X - v.Z * X, X * v.Y - v.X * Y);
}



/**
 *  \param v crossand
 *  \return \f$ \vec{X} \bullet \vec{v} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \vec{X} \bullet \vec{v} = X_xv_x + X_yv_y + X_zv_z \f]
**/
#endif
inline PValue PVertex3D::operator*(const PVertex3D v) const
{
    return X * v.X + Y * v.Y + Z * v.Z;
}



/**
 *  \param v crossand
 *  \return \f$ v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ v\vec{X} = <vX_x, vX_y, vX_z> \f]
**/
#endif
inline PVertex3D PVertex3D::operator*(const PValue v) const
{
    return PVertex3D(X * v, Y * v, Z * v);
}



/**
 *  \param v crossand
 *  \return \f$ \frac{1}{v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}, \frac{X_z}{v}> \f]
**/
#endif
inline PVertex3D PVertex3D::operator/(const PValue v) const
{
    const PValue Inv = PValue::Inverse(v);

    return PVertex3D(X * Inv, Y * Inv, Z * Inv);
}



/**
 *  \param v multiplicand
 *  \return \f$ <X_x * v_x, X_y * v_y> \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}, \frac{X_z}{v}> \f]
**/
#endif
inline PVertex3D PVertex3D::operator^(const PVertex3D v) const
{
    return PVertex3D(X * v.X, Y * v.Y, Z * v.Z);
}



/**
 *  \param v scalar
 *  \return \f$ 2^v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^v\vec{X} = <2^vX_x, 2^vX_y, 2^vX_z> \f]
**/
#endif
inline PVertex3D PVertex3D::operator<<(const unsigned v) const
{
    return PVertex3D(X << v, Y << v, Z << v);
}



/**
 *  \param v scalar
 *  \return \f$ 2^{-v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^{-v}\vec{X} = <2^{-v}X_x, 2^{-v}X_y, 2^{-v}X_z> \f]
**/
#endif
inline PVertex3D PVertex3D::operator>>(const unsigned v) const
{
    return PVertex3D(X >> v, Y >> v, Z >> v);
}



/**
 *  \param v addend
 *  \return \f$ \vec{X} + \vec{v} \f$
**/
inline PVertex3D &PVertex3D::operator+=(const PVertex3D v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;

    return *this;
}



/**
 *  \param v minued
 *  \return \f$ \vec{X} - \vec{v} \f$
**/
inline PVertex3D &PVertex3D::operator-=(const PVertex3D v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;

    return *this;
}



/**
 *  \param v scalar
 *  \return \f$ v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ v\vec{X} = <vX_x, vX_y, vX_z> \f]
**/
#endif
inline PVertex3D &PVertex3D::operator*=(const PValue v)
{
    X *= v;
    Y *= v;
    Z *= v;

    return *this;
}



/**
 *  \param v scalar
 *  \return \f$ \frac{1}{v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ \frac{1}{v}\vec{X} = <\frac{X_x}{v}, \frac{X_y}{v}, \frac{X_z}{v}> \f]
**/
#endif
inline PVertex3D &PVertex3D::operator/=(const PValue v)
{
    const PValue Inv = PValue::Inverse(v);

    X *= Inv;
    Y *= Inv;
    Z *= Inv;

    return *this;
}



/**
 *  \param v multiplicand
 *  \return \f$ <X + v_X, Y + v_Y, Z + v_Z> \f$
**/
inline PVertex3D &PVertex3D::operator^=(const PVertex3D v)
{
    X *= v.X;
    Y *= v.Y;
    Z *= v.Z;

    return *this;
}



/**
 *  \param v power
 *  \return \f$ 2^v\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^v\vec{X} = <2^vX_x, 2^vX_y, 2^vX_z> \f]
**/
#endif
inline PVertex3D &PVertex3D::operator<<=(const unsigned v)
{
    X <<= v;
    Y <<= v;
    Z <<= v;

    return *this;
}



/**
 *  \param v power
 *  \return \f$ 2^{-v}\vec{X} \f$
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \f[ 2^{-v}\vec{X} = <2^{-v}X_x, 2^{-v}X_y, 2^{-v}X_z> \f]
**/
#endif
inline PVertex3D &PVertex3D::operator>>=(const unsigned v)
{
    X >>= v;
    Y >>= v;
    Z >>= v;

    return *this;
}



/**
 *  \param v Vertex to compare against
 *  \return \f$ x = v \f$
**/
inline bool PVertex3D::operator==(const PVertex3D v) const
{
    return (X == v.X) & (Y == v.Y) & (Z == v.Z);
}



/**
 *  \param v Vertext to compare against
 *  \return \f$ x \ne v \f$
**/
inline bool PVertex3D::operator!=(const PVertex3D v) const
{
    return (X != v.X) | (Y != v.Y) | (Z != v.Z);
}



/**
 *  \return \f$ ||v||_\infty \f$
**/
inline PValue PVertex3D::InfNorm(void) const
{
    const PValue a = PValue::Abs(X);
    const PValue b = PValue::Abs(Y);
    const PValue c = PValue::Abs(Z);

    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}



/*
 *  Theses functions apply to floating points only
 */
/**
 *  \return \f$ ||\vec{v}||_2 \f$
**/
inline PValue PVertex3D::Norm() const
{
    return PValue::Sqrt((X * X) + (Y * Y) + (Z * Z));
}



#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  \return
 *  \f{align*}
 *   V_x &= \frac{V_x}{\sqrt{V_x^2 + V_y^2 + V_z^2}} \\
 *   V_y &= \frac{V_y}{\sqrt{V_x^2 + V_y^2 + V_z^2}} \\
 *   V_z &= \frac{V_y}{\sqrt{V_x^2 + V_y^2 + V_z^2}} \\
 *  \f}
**/
#endif
inline void PVertex3D::Normalize(void)
{
    const PValue InvSqrt = PValue::Inverse((X * X) + (Y * Y) + (Z * Z));

    X *= InvSqrt;
    Y *= InvSqrt;
    Z *= InvSqrt;
}



inline bool PVertex3D::IsAligned(void) const
{
    if (PValue::Frac(X) >= (PValue(1) >> 8u))
        return false;

    if (PValue::Frac(Y) >= (PValue(1) >> 8u))
        return false;

    if (PValue::Frac(Z) >= (PValue(1) >> 8u))
        return false;

    return true;
}

