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
#ifndef PPVRPIXMAP_H_
#define PPVRPIXMAP_H_

#include <PVR/pvr2d.h>

struct PEXPORT PPvrPixmap {

    friend struct PPvrContext2D;

    enum {
        P_PVR_ROT_0,
        P_PVR_ROT_90
    };

protected:
    PPvrPixmap(int Width, int Height, PFormat Format, void* Data, PVR2DCONTEXTHANDLE hContext);
    ~PPvrPixmap();

protected:
    int           m_width;
    int           m_height;
    PFormat       m_format;
    PVR2DMEMINFO* m_memInfo;
    PVR2DCONTEXTHANDLE m_hContext;
};


PPvrPixmap::PPvrPixmap(int Width, int Height, PFormat Format, void* Data, PVR2DCONTEXTHANDLE hContext)
    : m_width(Width)
    , m_height(Height)
    , m_format(Format)
    , m_hContext(hContext)
{
    PVR2DERROR    pvrerr;

    int Size;
    switch(Format) {
        case PFORMAT_8880:
        case PFORMAT_8888:
            Size = Width * Height * 4;
            break;

        default:
            printf( "Bad format %d\n", Format);
            return;
    }

    pvrerr = PVR2DMemWrap(m_hContext,
                          (PVR2D_VOID*)Data,
                          PVR2D_WRAPFLAG_NONCONTIGUOUS,
                          Size,
                          0, /* no physical mappings */
                          &m_memInfo);
    if (pvrerr != PVR2D_OK) {
        printf( "PVR2DMemWrap failed\n");
    }

}

PPvrPixmap::~PPvrPixmap()
{
    PVR2DMemFree(m_hContext, m_memInfo);
}

#endif
