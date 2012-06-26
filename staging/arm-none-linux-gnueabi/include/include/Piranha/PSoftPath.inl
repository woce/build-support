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



inline bool PSoftPathIterator::IsEnd(void)
{
    return Data == NULL;
}



inline bool PSoftPathIterator::IsNewSub(void)
{
    return Data[0] & (1 << PPATH_NEW);
}



inline bool PSoftPathIterator::IsClosed(void)
{
     return Data[0] & (1 << PPATH_CLOSED);
}



inline unsigned PSoftPathIterator::GetPathType(void)
{
    return (Data[0] >> PPATH_TYPE) & 3;
}



inline unsigned PSoftPathIterator::GetPathCount(void)
{
    return Data[0] >> PPATH_COUNT;
}



inline PVertex2D *PSoftPathIterator::GetPoints(void)
{
    return (PVertex2D *)&Data[2];
}



inline void PSoftPathIterator::Next(void)
{
    Data = (unsigned *)Data[1];
}



inline PSoftPathIterator &PSoftPathIterator::operator=(const PSoftPathIterator &Iter)
{
    Data = Iter.Data;

    return *this;
}



inline PSoftPath::PSoftPath() : TotSub(0), Data(NULL), First(NULL), Last(NULL), StartPt(0, 0), NewSub(true)
{
    SetQuality();
}



inline PSoftPath::PSoftPath(const PSoftPath &Path)
{
    Data = NULL;
    *this = Path;
}



inline PSoftPath::~PSoftPath()
{
    Reset();
}



/// \return true if the path is empty (false otherwise)
inline bool PSoftPath::IsEmpty() const
{
    return Data == NULL;
}



/**
 *  \param Pt Vertex to begin the subpath at
 *  \return false if we're out of memory, true otherwise
**/
inline bool PSoftPath::MoveTo(PVertex2D *const Pt)
{
    StartPt = *Pt;
    NewSub  = true;

	return true;
}



/**
 *  \param Pt List of vertices
 *  \param Num Total number of vertices
 *  \return false if we're out of memory, true otherwise
**/
inline bool PSoftPath::LineTo(PVertex2D *const Pt, const unsigned Num)
{
    return BezierTo(1, Pt, Num);
}



/// \return false if we're out of memory, true otherwise
inline bool PSoftPath::Close(void)
{
    if (!First)
        return true;

    *(unsigned *)First |= (1 << PPATH_CLOSED);

	return false;
}



inline void PSoftPath::SetIterator(PSoftPathIterator *Iter) const
{
    Iter->Data = Data;
}



/**
 *  \param Quality Quality factor [0..Inf]
**/
inline void PSoftPath::SetQuality(const PValue Quality)
{
#if (P_VALUES == P_FIXED)
    this->Quality = Quality;
#else
    this->Quality = Quality * Quality;
#endif
}
