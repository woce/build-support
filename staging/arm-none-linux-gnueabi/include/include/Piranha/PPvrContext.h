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
#ifndef PPVRCONTEXT_H_
#define PPVRCONTEXT_H_

#include <PVR/pvr2d.h>
#include "PPvrPixmap.h"

#define P_PVR_VERSION  0

enum PPvrRotation
{
    P_PVR_ROT_0,
    P_PVR_ROT_90
};

/**
 *  PVR2D Rendering Context
**/
struct PEXPORT PPvrContext2D {

    PPvrContext2D();
    ~PPvrContext2D();

    bool PvrInit(const unsigned Layer);

    PPvrPixmap* WrapPvrPixmap (const unsigned Width, const unsigned Height, const PFormat Format, void *const Data);    ///< Creates a new Pixmap
    void        DestroyPvrPixmap(PPvrPixmap* Pixmap);

    void        DrawPvrPixmap (PPvrPixmap *Src, PPvrPixmap* Dst, PPvrRotation Rotation=P_PVR_ROT_0);                             ///< Draws a pixmap

protected:

protected:
    PVR2DCONTEXTHANDLE m_hContext;
};


#include <stdio.h>
#define TRACE  printf


PPvrContext2D::PPvrContext2D()
    : m_hContext(0)
{
}

PPvrContext2D::~PPvrContext2D()
{
    if (m_hContext) {
        if (PVR2DDestroyDeviceContext(m_hContext) != PVR2D_OK) {
            TRACE( "PVR2DDestroyDeviceContext failed\n");
        }

        m_hContext = 0;
    }
}

bool PPvrContext2D::PvrInit(const unsigned Layer)
{
    if (m_hContext) {
        if (PVR2DDestroyDeviceContext(m_hContext) != PVR2D_OK) {
            TRACE( "PVR2DDestroyDeviceContext failed\n");
        }
        m_hContext = 0;
    }

    PVR2DDEVICEINFO *pDevInfo;
    PVR2DERROR    pvrerr;
    unsigned long ui32DevId;
    int nDevices;

    /*
    // Get the number of devices in the system
    */
    nDevices = PVR2DEnumerateDevices(0);
    if (nDevices <= 0)
    {
        TRACE( "nDevices %d\n", nDevices);

        /* No devices or a PVR2DERROR occurred */
        return false;
    }

    pDevInfo = (PVR2DDEVICEINFO *)malloc(nDevices*sizeof(PVR2DDEVICEINFO));
    if (!pDevInfo) {
        return false;
    }

    /*
    // Enumerate the devices
    */
    if (PVR2DEnumerateDevices(pDevInfo) != PVR2D_OK) {
        TRACE( "PVR2DEnumerateDevices failed: %d\n", PVR2DEnumerateDevices(pDevInfo));

        free(pDevInfo);

        return false;
    }

    /*
    // Default to the first display device
    */
    ui32DevId = pDevInfo[0].ulDevID;

    char DeviceName[sizeof(pDevInfo[0].szDeviceName)];

    snprintf(DeviceName, sizeof(DeviceName), "omaplfb:%d", Layer);

    for (int i = 0; i < nDevices; i++) {
        TRACE( "Looking for device '%s', found '%s'\n", DeviceName, pDevInfo[i].szDeviceName);

        if (strcmp(pDevInfo[i].szDeviceName, DeviceName) == 0) {
            ui32DevId = pDevInfo[i].ulDevID;
            break;
        }
    }

    free(pDevInfo);

    /*
    // Create a PVR2D context
    */
    if (PVR2DCreateDeviceContext(ui32DevId, &m_hContext, 0) != PVR2D_OK) {
        return false;
    }

    return true;
}


PPvrPixmap* PPvrContext2D::WrapPvrPixmap (const unsigned Width, const unsigned Height, const PFormat Format, void *const Data)
{
    if (!m_hContext) {
        return NULL;
    }

    return new PPvrPixmap(Width, Height, Format, Data, m_hContext);
}

void PPvrContext2D::DestroyPvrPixmap(PPvrPixmap* Pixmap)
{
    delete Pixmap;
}


void PPvrContext2D::DrawPvrPixmap(PPvrPixmap *Src, PPvrPixmap* Dst, PPvrRotation Rotation)
{
    PVR2DBLTINFO BltInfo;
    PVR2DERROR    pvrerr;

    memset(&BltInfo, 0, sizeof(BltInfo));

    BltInfo.CopyCode 		= PVR2DROPcopy;
    BltInfo.BlitFlags 		= PVR2D_BLIT_DISABLE_ALL;

    switch (Rotation) {
        case P_PVR_ROT_0:
            break;

        case P_PVR_ROT_90:
            BltInfo.BlitFlags = PVR2D_BLIT_ROT_90;
            break;

        default:
            printf( "Unhandled rotation %d\n", Rotation);
            return;
    }


    BltInfo.pSrcMemInfo 	= Src->m_memInfo;
    BltInfo.SrcStride 		= Src->m_width * 4;
    BltInfo.pDstMemInfo 	= Dst->m_memInfo;
    BltInfo.DstStride 		= Dst->m_width * 4;

    BltInfo.SizeX 			= Src->m_width;
    BltInfo.SizeY 			= Src->m_height;
    BltInfo.DSizeX 		    = Dst->m_width;
    BltInfo.DSizeY 		    = Dst->m_height;

    BltInfo.SrcFormat       = PVR2D_ARGB8888;
    BltInfo.DstFormat       = PVR2D_ARGB8888;

    pvrerr = PVR2DBlt(m_hContext, &BltInfo);
    if (pvrerr != PVR2D_OK) {
        printf( "PVR2DBlt failed\n");
        return;
    }

    pvrerr = PVR2DQueryBlitsComplete(m_hContext, BltInfo.pDstMemInfo, 1);
    if (pvrerr != PVR2D_OK) {
        printf( "PVR2DQueryBlitsComplete failed\n");
        return;
    }
}

#endif
