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
#ifndef SGLSLVBO_H
#define SGLSLVBO_H

#include "SGLSL.h"

#if defined(DOXYGEN) && (DOXYGEN==0)
/// \addtogroup GLSLInternal
/// @{
#else
/// \addtogroup GLSLBackend
/// @{
#endif



/**
 *  GLSL Vertex Buffer Objects
**/
struct SGLSLVBO {
    friend struct SGLSLAttribute;
    template <class Type> friend struct SGLSLAInterleaved;

    void Create(SVBOTarget Target, SFrequencyType Freq, unsigned Size, void *Data = NULL);  ///< Initializes the VBO
    void Update(unsigned Offset, unsigned Size, void *Data);                                ///< Update the VBO's data

protected:
    SGLSLVBO();
    ~SGLSLVBO();

    GLuint      ID;
    SVBOTarget  Target;
};
#if defined(DOXYGEN) && (DOXYGEN==0)
/// @}
/// \addtogroup GLSLBackend
/// @{
#endif




/**
 *  GLSL Attribute Buffer
**/
struct SGLSLABuffer : public SGLSLVBO {
    void Create(SFrequencyType Freq, unsigned Size, void *Data = NULL);                     ///< Initializes the VBO
};



/**
 *  GLSL Attribute Index Buffer
**/
struct SGLSLAIndex : public SGLSLVBO {
    void Create(SFrequencyType Freq, unsigned Size, void *Data = NULL);                     ///< Initializes the VBO
};



/// @}
#endif
