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
#ifndef SUNIFORM_H
#define SUNIFORM_H

#include "PCommon.h"
#include BACKEND_INCLUDE(S, S_SHADER_NAME, Uniform.h)


// Define the shader basic uniform types
BACKEND_TYPE(S, S_SHADER_NAME, UPValue SUPValue)
BACKEND_TYPE(S, S_SHADER_NAME, UPVertex2D SUPVertex2D)
BACKEND_TYPE(S, S_SHADER_NAME, UPVertex3D SUPVertex3D)
BACKEND_TYPE(S, S_SHADER_NAME, UPVertex4D SUPVertex4D)
BACKEND_TYPE(S, S_SHADER_NAME, UPInt SUPInt)
BACKEND_TYPE(S, S_SHADER_NAME, UPMatrix2D SUPMatrix2D)
BACKEND_TYPE(S, S_SHADER_NAME, UPMatrix3D SUPMatrix3D)
BACKEND_TYPE(S, S_SHADER_NAME, UPMatrix4D SUPMatrix4D)



// Define the attribute building structures
#define SUStruct    ALIAS(S, S_SHADER_NAME, UStruct)
#define SUArray     ALIAS(S, S_SHADER_NAME, UArray)

#endif
