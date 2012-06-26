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



inline SGLSLAttribute::SGLSLAttribute(const char *const Name, const unsigned Component) : Attribute(Name), Components(Component) {}



/**
 *  \param Program Program's ID
 *  \param Loc Attribute's Index
**/
inline void SGLSLAttribute::SetLocation(const GLint Program, const unsigned Loc)
{
    glBindAttribLocation(Program, Loc, Attribute);

    ID = Loc;
}



/**
 *  \param Program Program's ID
 *  \return Success (true/false)
**/
inline bool SGLSLAttribute::GetLocation(const GLint Program)
{
    ID  = glGetAttribLocation(Program, Attribute);

    return ((int)ID != -1);
}



/**
 *  \param VBO Vertex Buffer Object which contains the data
 *  \param Type attribute type
 *  \param Index Attribute's Index or Pointer
 *  \param Stride Data's stride in bytes
 *  \param Normalized Wether or not we need to normalize the input data
**/
inline void SGLSLAttribute::Set(const SGLSLVBO *const VBO, unsigned Type, unsigned Index, unsigned Stride, bool Normalized)
{
    glBindBuffer            (GL_ARRAY_BUFFER, VBO->ID);
    glVertexAttribPointer   (ID, Components, Type, Normalized, Stride, (const GLvoid *)Index);
}



/**
 *  \param VertexData Vertex Data
 *  \param Type attribute type
 *  \param Index Attribute's Index or Pointer
 *  \param Stride Data's stride in bytes
 *  \param Normalized Wether or not we need to normalize the input data
**/
inline void SGLSLAttribute::Set(const void *const VertexData, unsigned Type, unsigned Index, unsigned Stride, bool Normalized)
{
    glVertexAttribPointer   (ID, Components, Type, Normalized, Stride, (const GLvoid *)(((char*)VertexData) + Index));
}




inline void SGLSLAttribute::Enable(void)
{
    glEnableVertexAttribArray(ID);
}



inline void SGLSLAttribute::Disable(void)
{
    glDisableVertexAttribArray(ID);
}
