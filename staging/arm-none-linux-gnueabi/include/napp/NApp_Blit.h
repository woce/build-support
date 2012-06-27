/* @@@LICENSE
*
*      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */

#ifndef NAPP_BLIT_H_
#define NAPP_BLIT_H_

#include "NCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

enum NApp_BlitCacheOp
{
    NAPP_BLIT_CACHE_NOOP,
    NAPP_BLIT_CACHE_INVALIDATE,
};

struct NApp_BlitSurface
{
    void* Mem;
    int   Fd;
    int   Offset;
    int   CacheOp;

    int   Width;
    int   Height;
    int   Pitch;
    int   RectX;
    int   RectY;
    int   RectWidth;
    int   RectHeight;
};

NEXPORT void NApp_Blit(struct NApp_BlitSurface* Dst, struct NApp_BlitSurface* Src, int RotateAngle);

#ifdef __cplusplus
}
#endif

#endif /* NAPP_BLIT_H_ */
