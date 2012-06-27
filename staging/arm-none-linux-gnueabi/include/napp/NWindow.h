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


#ifndef NWINDOW_H_
#define NWINDOW_H_

#include <list>
#include "NWindowBuffer.h"
#include "NCommon.h"

struct HMutex;
struct NCompositingWindow;

// A window is a collection of abstract window buffers
struct NEXPORT NWindow
{
    NWindow();
    virtual ~NWindow();

    virtual void    Set(int Width, int Height);
	virtual bool    Set(int Width, int Height, int NumBuffers);
    virtual bool    AttachBuffers(int NumBuffers, unsigned int Handles[]); // Deprecated; Handles not used

    virtual void    SetBuffer(int Index, NWindowBuffer* Buffer);

    int NumBuffers() {
        return m_numBuffers;
    }
    int Width() {
        return m_width;
    }
    int Height() {
        return m_height;
    }
    
    NWindowBuffer* GetBuffer(int index) {
        return m_buffers[index];
    }

    virtual void Post(int Buffer) = 0;
    virtual void Wait(int* Buffer) = 0;
    
    // Empty impl to prevent sysmgr build break
    virtual void Ack(int Buffer) {}

    static void NeedsAck(NWindow* window, int Buffer);

protected:
    virtual void    Free();
    void            FreeBuffers();

protected:
    int     m_width;
    int     m_height;
    
    unsigned int*   m_unused_0;
    NWindowBuffer** m_buffers;
    int             m_numBuffers;

    static NCompositingWindow* CompositingWindow;
};


struct NEXPORT NCompositingWindow : public NWindow
{
    static NCompositingWindow* Create(int NumBuffers);
    static NCompositingWindow* Instance();
    static void Destroy();

    virtual void Post(int Buffer);
    virtual void Wait(int *Buffer);

    virtual void Ack(int Buffer) {
    }

    virtual void NeedsAck(NWindow* window, int Buffer);

protected:
    NCompositingWindow(int NumBuffers);
    ~NCompositingWindow();

protected:
    typedef std::pair<NWindow*, int> NWindowAckItem;

    std::list<NWindowAckItem>* m_ackList;
    int m_currentBuffer;
    HMutex* m_mutex;
};

#endif /* NWINDOW_H_ */
