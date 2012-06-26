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


#ifndef NWINDOWBUFFER_H_
#define NWINDOWBUFFER_H_

#include "NCommon.h"
#include <ostream>
#include <cstddef>

struct NEXPORT NWindowBuffer
{
    virtual int             TryLock()   = 0;
    virtual int             Lock()      = 0;
    virtual int             Unlock()    = 0;
    virtual unsigned int    Handle()    = 0;
    virtual void            Free()      = 0;
    virtual void*           Vaddr()     = 0;
    virtual int             Size()      = 0;
    
protected:
    virtual ~NWindowBuffer(); 
};


struct NWindow;
struct PIpcBuffer;
struct NPixmapHeader;

struct NEXPORT NSharedWindowBuffer : public NWindowBuffer
{
    static NSharedWindowBuffer* Create(int size) {
        return new NSharedWindowBuffer(0, size, 0);
    }
    static NSharedWindowBuffer* Create(int size, int reserve) {
        return new NSharedWindowBuffer(0, size, reserve);
    }
    static NSharedWindowBuffer* Attach(unsigned int Handle) {
        return new NSharedWindowBuffer((int)Handle, 0, 0);
    }

    virtual int  TryLock();
    virtual int  Lock();
    virtual int  Unlock();
    virtual unsigned int Handle();
    virtual void Free();
    virtual void FreeNoDelete();
    virtual void*  Vaddr();
    virtual int    Size();

    void setLockFree(bool lockFree);
    
protected:
    NSharedWindowBuffer(int size);  // doesn't create PIpcBuffer
    NSharedWindowBuffer(int key, int size, int reserve); // reserve is an amount to prepend to the front.
    
    bool setSize(int newSize); // can not set to larger than the allcoated size
    int calcSize(int requestedSize); // returns the required size of allocation for the sent-in size of memory
    void*  RawVaddr(); // returns the address of the start of the actual buffer (does not offset for reserve)

protected:
    PIpcBuffer* m_ipcBuffer;
    int         m_lockCount;
    int         m_reportSize; // the size to actually report (may be smaller than the buffer size)
    int         m_reserveSize; // the amount of prepending. This may be different than the amount requested (to page-align)
    bool        m_lockFree;
    
    friend class NGameCard;
};


enum NYuvFormat
{
    NYUVFORMAT_NOT_YUV,
    NYUVFORMAT_NV12_TILED,
    NYUVFORMAT_NV21,
    NYUVFORMAT_YV12
};

struct NEXPORT NPixmap : public NSharedWindowBuffer
{
    // by itself, NPixmap allocates with no reserve
    static NPixmap* Create(int width, int height, int pitch=0) {
        return new NPixmap(0, width, height, (pitch ? pitch : (width * 4)), 0);
    }
    static NPixmap* Attach(unsigned int handle, int width, int height, int pitch=0) {
        return new NPixmap(handle, width, height, (pitch ? pitch : (width * 4)), 0);
    }
    
    static NPixmap* Create(int width, int height, NYuvFormat format);
    static NPixmap* Attach(unsigned int handle, int width, int height, NYuvFormat format);

    static void Calc(int width, int height, int* pPitch, int* pBufferSize);    
    static void CalcNv12Tiled(int width, int height, int* pPitch, int* pPlaneOffset, int* pBufferSize);
    static void CalcNv21(int width, int height, int* pPitch, int* pPlaneOffset, int* pBufferSize);
    static void CalcYv12(int width, int height, int* pPitch, int* pUplaneOffset, int* pVplaneOffset, int* pBufferSize);

    virtual bool   Resize(int width, int height, int pitch=0);
    virtual int    Width();
    virtual int    Height();
    virtual int    Pitch();
    
    virtual int    Unlock();
    
    virtual NYuvFormat YuvFormat();
    
protected:
    static NPixmap* New(unsigned int handle, int width, int height, NYuvFormat format);
    
    NPixmap(int width, int height, NYuvFormat format, int pitch, int bufferSize);  //This calls down into an NSharedWindowBuffer constructor that does nothing
    NPixmap(unsigned int key, int width, int height, int pitch, int reserve);
    NPixmap(unsigned int key, int width, int height, NYuvFormat format, int pitch, int bufferSize);
    
    int m_width;
    int m_height;
    int m_pitch;
    NYuvFormat m_format;
};


struct NEXPORT NHeaderedPixmap : public NPixmap
{
    static NHeaderedPixmap* Create(int width, int height, int pitch=0) {
        return new NHeaderedPixmap(0, width, height, (pitch ? pitch : (width * 4)));
    }
    static NHeaderedPixmap* Attach(unsigned int handle, int width, int height, int pitch=0) {
        return new NHeaderedPixmap(handle, width, height, (pitch ? pitch : (width * 4)));
    }

    virtual bool   Resize(int width, int height, int pitch=0);
    
    virtual int  Unlock();

    NPixmapHeader* GetHeader();
    
protected:
    NHeaderedPixmap(unsigned int key, int width, int height, int pitch);
    void UpdatePixmapHeader();
};


struct NEXPORT NPixmapPrivate : public NPixmap
{
    static NPixmapPrivate* Create(int width, int height, int pitch=0) {
        return new NPixmapPrivate(width, height, (pitch ? pitch : (width * 4)));
    }
    static void MemStats(std::ostream &output);
    static void MallocTrim(std::size_t pad);

    virtual void*  Vaddr(); 
    virtual void   Free();

    int     Mlock();
    int     Munlock();

protected:
    NPixmapPrivate(int width, int height, int pitch);

    void*  m_data;
    bool   m_mLocked;
};


struct NEXPORT NPixmapWrapped : public NPixmap
{
    static NPixmapWrapped* Create(void* vaddr, int width, int height, int pitch=0);
    static NPixmapWrapped* Create(void* vaddr, int width, int height, NYuvFormat format);

    static void* PageAlign(void* addr);
    
    virtual unsigned int Handle();
    virtual void* Vaddr();

    ~NPixmapWrapped();
    
protected:
    NPixmapWrapped(void* addr, int width, int height, NYuvFormat format, int pitch, int bufferSize);
    
protected:
    void* m_vAddr;
    int m_size;
};

#endif /* NWINDOWBUFFER_H_ */
