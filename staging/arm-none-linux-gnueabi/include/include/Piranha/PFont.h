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
#ifndef PFONT_H
#define PFONT_H

#include "PCommon.h"
#include "PBackend.h"

#ifndef P_FONT_SOFT
 #define P_FONT_SOFT P_FREETYPE
#endif
#ifndef P_FONT_GLES
 #define P_FONT_GLES P_FREETYPE
#endif
#ifndef P_FONT_VG
 #define P_FONT_VG P_FREETYPE
#endif



#if (P_FONT_SOFT == P_FREETYPE)
 #include "PFTFontContext.h"
 #include "PFTFont.h"
#endif


/*
typedef PFTFontContext      ALIAS(P, P_BACKEND_NAME, FontContextTy);
typedef PFTFont             ALIAS(P, P_BACKEND_NAME, FontTy);
typedef PFTCacheData        ALIAS(P, P_BACKEND_NAME, CacheDataTy);
typedef PFTFontArray        ALIAS(P, P_BACKEND_NAME, FontArray);
typedef PFTFontRange        ALIAS(P, P_BACKEND_NAME, FontRange);
typedef PFTFontRangeArray   ALIAS(P, P_BACKEND_NAME, FontRangeArray);

typedef ALIAS(P, P_BACKEND_NAME, Font)::PFTFontContext      ALIAS(P, P_BACKEND_NAME, FontContextTy);
typedef ALIAS(P, P_BACKEND_NAME, Font)::PFTFont             ALIAS(P, P_BACKEND_NAME, FontTy);
typedef ALIAS(P, P_BACKEND_NAME, Font)::PFTCacheData        ALIAS(P, P_BACKEND_NAME, CacheDataTy);
typedef ALIAS(P, P_BACKEND_NAME, Font)::PFTFontArray        ALIAS(P, P_BACKEND_NAME, FontArray);
typedef ALIAS(P, P_BACKEND_NAME, Font)::PFTFontRange        ALIAS(P, P_BACKEND_NAME, FontRange);
typedef ALIAS(P, P_BACKEND_NAME, Font)::PFTFontRangeArray   ALIAS(P, P_BACKEND_NAME, FontRangeArray);



BACKEND_TYPE(P, P_BACKEND_NAME, FontTy PFont)
BACKEND_TYPE(P, P_BACKEND_NAME, FontArray PFontArray)
BACKEND_TYPE(P, P_BACKEND_NAME, FontRange PFontRange)
BACKEND_TYPE(P, P_BACKEND_NAME, FontRangeArray PFontRangeArray)
*/


typedef PFTFont             PFont;
typedef PFTFontArray        PFontArray;
typedef PFTFontRange        PFontRange;
typedef PFTFontRangeArray   PFontRangeArray;



#endif
