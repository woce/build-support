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
#ifndef SGLSLUNIFORM_H
#define SGLSLUNIFORM_H

#include "SGLSL.h"
#include "PInt.h"
#include "PVertex2D.h"
#include "PMatrix2D.h"
#include "PVertex3D.h"
#include "PMatrix3D.h"
#include "PVertex4D.h"
#include "PMatrix4D.h"

#if defined(DOXYGEN) && (DOXYGEN==0)
/// \addtogroup GLSLInternal
/// @{
#else
/// \addtogroup GLSLBackend
/// @{
#endif



/**
 *  GLSL Uniform virtual base class
**/
struct PEXPORT SGLSLUniform {
    friend struct SGLSLProgram;

protected:
    SGLSLUniform(const char *const Name, const unsigned StrucSize);

    virtual bool        GetLocation (const GLint Program, const char *const Parent = NULL) = 0; ///< Retrieves the Uniform ID after link
    virtual void        Update(bool Force = true) = 0;                                                 ///< Updates the program's uniform

    unsigned    Size;                                                                           ///< Structure's size
    const char *const Uniform;                                                                  ///< Uniform's name
    SGLSLUniform *Next;                                                                         ///< Linked list of uniforms's next element
};



/**
 *  GLSL Typed Uniform pointer template
 *  \tparam Type DataType for the Uniform
**/
template <class Type> struct PEXPORT SGLSLUPType : public SGLSLUniform {
    SGLSLUPType(const char *const Name);
    SGLSLUPType(const char *const Name, Type *Ptr);

    SGLSLUPType &operator=(const Type *v);                                                       ///< Sets the value for the uniform

protected:
    virtual bool        GetLocation (const GLint Program, const char *const Parent = NULL);     ///< Retrieves the Uniform ID after link
    virtual void        Update(bool Force = true) ;                                                     ///< Updates the program's uniform

    Type        Old;                                                                            ///< Value of the last update
    Type       *Pointer;                                                                        ///< Pointer to the most current value
    GLint       ID;                                                                             ///< Uniform's unique identifier
};
#if defined(DOXYGEN) && (DOXYGEN==0)
/// @}
/// \addtogroup GLSLBackend
/// @{
#endif



/**
 *  GLSL Uniform structure template
 *  \tparam Type Structure of SGLSLUniform \sa SGLSLUniform
**/
template <class Type> struct PEXPORT SGLSLUStruct : public SGLSLUniform, public Type {
    SGLSLUStruct(const char *const Name);

protected:
    virtual void        Update(bool Force = true) ;                                                     ///< Updates the program's uniform
    virtual bool        GetLocation (const GLint Program, const char *const Parent = NULL);     ///< Retrieves the Uniform ID after link
};



/**
 *  GLSL Uniform array
 *  \tparam Type Uniform datatype for the array \sa SGLSLUniform
**/
template <class Type> struct PEXPORT SGLSLUArray : public SGLSLUniform {
    SGLSLUArray(const char *const Name, const unsigned Size);
    ~SGLSLUArray();

    Type &operator[] (const unsigned Index);

protected:
    virtual void        Update(bool Force = true);                                                     ///< Updates the program's uniform
    virtual bool        GetLocation (const GLint Program, const char *const Parent = NULL);     ///< Retrieves the Uniform ID after link

    const Type     *Value;                                                                      ///< Array of Uniforms
    const unsigned  Count;                                                                      ///< Number of elements in the array
    GLint           ID;                                                                         ///< Uniform's unique identifier
};



/// \name Base Uniforms
/// @{

// Pointers
typedef SGLSLUPType<PValue>     SGLSLUPValue;                                                   ///< float *uniform
typedef SGLSLUPType<PVertex2D>  SGLSLUPVertex2D;                                                ///< vec2 Float *uniform
typedef SGLSLUPType<PVertex3D>  SGLSLUPVertex3D;                                                ///< vec3 Float *uniform
typedef SGLSLUPType<PVertex4D>  SGLSLUPVertex4D;                                                ///< vec4 Float *uniform
typedef SGLSLUPType<PInt>       SGLSLUPInt;                                                     ///< int *uniform
/*
typedef SGLSLUPArray<PValue>    SGLSLUPValueA;                                                  ///< float[] *uniform
typedef SGLSLUPArray<PVertex2D> SGLSLUPVertex2DA;                                               ///< vec2f[] *uniform
typedef SGLSLUPArray<PVertex3D> SGLSLUPVertex3DA;                                               ///< vec3f[] *uniform
typedef SGLSLUPArray<PVertex4D> SGLSLUPVertex4DA;                                               ///< vec4f[] *uniform
*/
typedef SGLSLUPType<PMatrix2D>  SGLSLUPMatrix2D;                                                ///< mat2f *uniform
typedef SGLSLUPType<PMatrix3D>  SGLSLUPMatrix3D;                                                ///< mat3f *uniform
typedef SGLSLUPType<PMatrix4D>  SGLSLUPMatrix4D;                                                ///< mat4f *uniform

/// @}



#include "SGLSLUniform.cxx"

/// @}
#endif
