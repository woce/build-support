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
#ifndef SGLSLATTRIBUTE_H
#define SGLSLATTRIBUTE_H

#include "SGLSL.h"
#include "SGLSLVBO.h"



#if defined(DOXYGEN) && (DOXYGEN==0)
/// \addtogroup GLSLInternal
/// @{
#else
/// \addtogroup GLSLBackend
/// @{
#endif

struct SGLSLVBO;



/**
 *  GLSL Attribute virtual base class
**/
struct SGLSLAttribute {
    friend struct SGLSLProgram;

    inline SGLSLAttribute(const char *const Name, const unsigned Component);

    inline void    Set         (const SGLSLVBO *const VBO,     unsigned Type, unsigned Index = 0, unsigned Stride = 0, bool Normalized = false);
    inline void    Set         (const void *const VertexData,  unsigned Type, unsigned Index = 0, unsigned Stride = 0, bool Normalized = false);

protected:
    inline void    SetLocation (const GLint Program, const unsigned Loc);  ///< Sets the Attribute ID before link
    inline bool    GetLocation (const GLint Program);                      ///< Retrieves the Attribute ID after link
    inline void    Enable      (void);                                     ///< Enables this attribute
    inline void    Disable     (void);                                     ///< Disables this attribute

    unsigned            ID;                                         ///< Member ID
    const char *const   Attribute;                                  ///< Attribute's name
    const unsigned      Components;                                 ///< Number of components
};



#include "SGLSLAttribute.cxx"

/// @}

#endif
