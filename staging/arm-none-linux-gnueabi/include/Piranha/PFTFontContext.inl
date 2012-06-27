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

/**
 *  \return Font engine that is being used
**/
inline PFontEng PFTFontContext::GetFontEng()
{
    return PFontFreeType;
}



/**
 *  \return true/false if the font is valid or not
**/
inline bool PFTFontContext::ValidFont()
{
    return (Font != NULL && Font->Face != NULL);
}



/**
 *  \param Font The font to be used for rendering text.
**/
inline void PFTFontContext::SetFont(PFTFont* Font)
{
    this->Font = Font;
}


