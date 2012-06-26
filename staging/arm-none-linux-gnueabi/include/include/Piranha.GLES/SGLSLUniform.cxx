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
#include <string.h>
#include "PMem.h"



///////////////////////////////////////////////////////////////////////////////
/**
 *  \param Name Variable's name
**/
template<class Type> SGLSLUStruct<Type>::SGLSLUStruct(const char *const Name) : SGLSLUniform(Name, sizeof(SGLSLUStruct<Type>))
{
}



template<class Type> void SGLSLUStruct<Type>::Update(bool Force)
{
    SGLSLUniform *Member    = reinterpret_cast<SGLSLUniform *>((Type *)this);
    SGLSLUniform *Stop      = (SGLSLUniform *)((unsigned)Member + sizeof(Type));

    // Update every member of the Type
    do {
        Member->Update(Force);

        Member = (SGLSLUniform *)((unsigned)Member + Member->Size);
    } while (Member < Stop);
}



/**
 *  \param Program Program's ID
 *  \param Parent Parent's name
 *  \return Success (true/false)
**/
template<class Type> bool SGLSLUStruct<Type>::GetLocation(const GLint Program, const char *const Parent)
{
    SGLSLUniform *Member    = reinterpret_cast<SGLSLUniform *>((Type *)this);
    SGLSLUniform *Stop      = (SGLSLUniform *)((unsigned)Member + sizeof(Type));
    bool Status             = true;

    // Update every member of the Type
    do {
        Status &= Member->GetLocation(Program, Parent);

        Member = (SGLSLUniform *)((unsigned)Member + Member->Size);
    } while (Member < Stop);

    return Status;
}



///////////////////////////////////////////////////////////////////////////////
/**
 *  \param Name Variable's name
 *  \param Size Array's size
**/
template<typename Type> SGLSLUArray<Type>::SGLSLUArray(const char *const Name, const unsigned Size) : SGLSLUniform(Name, sizeof(SGLSLUArray<Type>))
{
    Count = Size;
    Value = (Type *)malloc(Count * sizeof(Type));
}



template<typename Type> Type &SGLSLUArray<Type>::operator[](const unsigned Index)
{
    PASSERT(Index < Count, "Index out of bounds");

    return Value[Index];
}



/**
 *  \param Program Program's ID
 *  \param Parent Parent's name
 *  \return Success (true/false)
**/
template<class Type> bool SGLSLUArray<Type>::GetLocation(const GLint Program, const char *const Parent)
{
    if (Parent && !Parent[0]) {
        char Name[256];
        const unsigned Len = strlen(Parent);

        // Create the name
        if (Len) {
            PMem::Memcpy(Name, Parent, Len);
            Name[Len] = '.';
        }

        PMem::Memcpy(&Name[Len + 1], Uniform, strlen(Uniform) + 1);

        ID = glGetUniformLocation(Program, Name);

    } else
        ID = glGetUniformLocation(Program, Uniform);

    return ID != -1;
}



///////////////////////////////////////////////////////////////////////////////
/**
 *  \param Program Program's ID
 *  \param Parent Parent's name
 *  \return Success (true/false)
**/
template<class Type> bool SGLSLUPType<Type>::GetLocation(const GLint Program, const char *const Parent)
{
    if (Parent && !Parent[0]) {
        char Name[256];
        const unsigned Len = strlen(Parent);

        // Create the name
        if (Len) {
            PMem::Memcpy(Name, Parent, Len);
            Name[Len] = '.';
        }

        PMem::Memcpy(&Name[Len + 1], Uniform, strlen(Uniform) + 1);

        ID = glGetUniformLocation(Program, Name);

    } else
        ID = glGetUniformLocation(Program, Uniform);

    return ID != -1;
}



/**
 *  \param Name Variable's name
**/
template<class Type> SGLSLUPType<Type>::SGLSLUPType(const char *const Name) : SGLSLUniform(Name, sizeof(SGLSLUPType<Type>)), ID(-1)
{
}



template<class Type> SGLSLUPType<Type>::SGLSLUPType(const char *const Name, Type *Ptr) : SGLSLUniform(Name, sizeof(SGLSLUStruct<Type>)), Pointer(Ptr), ID(-1)
{
}


