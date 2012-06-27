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
#ifndef SGLESSHADER_H
#define SGLESSHADER_H

#include "PGLESCommon.h"
#include "PCommon.h"

/// \defgroup GLSLBackend GLSL Backend
/// @{



/**
 *  GLSL Attribute Types
**/
enum SAttribType {
    SAByte          = GL_BYTE,
    SAUByte         = GL_UNSIGNED_BYTE,
    SAShort         = GL_SHORT,
    SAUShort        = GL_UNSIGNED_SHORT,
    SAInt           = GL_INT,
    SAUInt          = GL_UNSIGNED_INT,
    SAFloat         = GL_FLOAT,
};



/**
 *  GLSL Update Frequency
**/
enum SFrequencyType {
    SFStatic        = GL_STATIC_DRAW,
    SFStream        = GL_STREAM_DRAW,
    SFDynamic       = GL_DYNAMIC_DRAW,
};

#if defined(DOXYGEN) && (DOXYGEN==0)
/// @}
/// \defgroup GLSLInternal GLSL Internal Structures
/// @{
#endif


/**
 *  GLSL Attribute base Types
**/
enum {
    SValueType      = 0,
};



/**
 *  GLSL VBO Targets
**/
enum SVBOTarget {
    STBuffer        = GL_ARRAY_BUFFER,
    STIndex         = GL_ELEMENT_ARRAY_BUFFER,
};



/**
 *  GLSL Shader Types
**/
enum SShaderType {
    SSGeometry  = 0,
    SSVertex    = GL_VERTEX_SHADER,
    SSFragment  = GL_FRAGMENT_SHADER,
};


/// @}
#endif
