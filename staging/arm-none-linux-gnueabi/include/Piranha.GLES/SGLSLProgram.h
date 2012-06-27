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
#ifndef SGLSLPROGRAM_H
#define SGLSLPROGRAM_H

#include "SGLSLShader.h"
#include "SGLSLUniform.h"
#include "SGLSLAttribute.h"


/// \addtogroup GLSLBackend
/// @{



/**
 *  GLSL Program
 *  \tparam AttribType packed structure of SGLSLAttribute \sa SGLSLAttribute
**/
struct SGLSLProgram : public SGLSLAttribute {
    friend struct PGLESContext2D;

    SGLSLProgram();
    ~SGLSLProgram();

    void        SetShader       (const SGLSLShader *const Shader);          ///< Assigns a shader to this program
    void        UnsetShader     (const SGLSLShader *const Shader);          ///< Removes the shader from the program

    void        Validate        (char *Log) const;                          ///< Validates the program
    unsigned    GetLog          (char *Log) const;                          ///< Returns the shader's error

    void        Add             (SGLSLUniform *const Uniform);              ///< Adds a uniform to the program
    void        Add             (SGLSLAttribute *const Attribute, const unsigned Pipe); ///< Adds an attribute to the program

    bool        Link            (void);                                     ///< Links and binds the shader
    void        Use             (unsigned Force = 3);                       ///< Updates the set of uniforms

private:
    GLuint  ID;                                                             ///< Shader's unique identifier

    SGLSLUniform   *Uniforms;                                               ///< List of dynamic uniforms
    SGLSLAttribute *Attributes[1];                                          ///< List of dynamic attributes

    char    Error[256];                                                     ///< Error reporting string
};



/// @}
#endif
