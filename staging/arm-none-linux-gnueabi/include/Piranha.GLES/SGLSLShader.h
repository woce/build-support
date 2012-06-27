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
#ifndef SGLSLSHADER_H
#define SGLSLSHADER_H

#include "SGLSL.h"

#if defined(DOXYGEN) && (DOXYGEN==0)
/// \addtogroup GLSLInternal
/// @{
#else
/// \addtogroup GLSLBackend
/// @{
#endif




/**
 *  GLSL Shader
**/
struct PEXPORT SGLSLShader {
    friend struct SGLSLProgram;

    bool        Load    (const char *const File);                           ///< Loads a shader from a file
    bool        Set     (const char *const Source);                         ///< Sets the source for the shader
    bool        Append  (const char *const Source);                         ///< Append source to the shader

    bool        Compile (void);                                             ///< Compiles the shader

    unsigned    GetLog  (char *Log)  const;                                 ///< Returns the shader's error
    void        Print   (void);                                             ///< Prints the shader to the console

protected:
    SGLSLShader     (SShaderType type);
    ~SGLSLShader    ();

private:
    GLuint      ID;                                                         ///< Shader's unique identifier
    GLuint      Type;                                                       ///< Type of shader this represents
    char       *Src;                                                        ///< Source code for the shader
    const char**Ptrs;                                                       ///< List of source pointers
    unsigned    PtrAt;                                                      ///< Pointer Index
};
#if defined(DOXYGEN) && (DOXYGEN==0)
/// @}
/// \addtogroup GLSLBackend
/// @{
#endif



/**
 *  GLSL Vertex shader program
**/
struct PEXPORT SGLSLVertexShader : public SGLSLShader {
    SGLSLVertexShader() : SGLSLShader(SSVertex) {}
};



/**
 *  GLSL Fragment shader program
**/
struct PEXPORT SGLSLFragmentShader : public SGLSLShader {
    SGLSLFragmentShader() : SGLSLShader(SSFragment) {}
};

/// @}

/// @}
#endif
