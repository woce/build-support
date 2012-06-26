//  @@@LICENSE
//
//      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  LICENSE@@@ 

#ifndef NREMOTEWINDOW_H_
#define NREMOTEWINDOW_H_

#include <pthread.h>
#include "NWindow.h"
#include "NRemoteWindowTypes.h"

// This is here only because we used to include EGL headers here,
// and webkit depended on that.
extern "C" {
NEglDisplay eglGetCurrentDisplay(void);
}

struct NEXPORT NRemoteTexture
{
    NRemoteTexture();
    bool exists();
    bool create(NEglDisplay display, NWindowBuffer* window, int texture);
    bool create(NEglDisplay display, NWindowBuffer* window, int texture, int mode);    
    void destroy(NEglDisplay display);

protected:
    static NEglCreateImageKHR_f  EglCreateImageKHR;
    static NEglDestroyImageKHR_f EglDestroyImageKHR;
    
    NEglImageKHR m_eglImage;
};


struct NEXPORT NRemoteWindow : public NWindow
{
    static const int MaxRemoteTexture = 3;

    NRemoteWindow();
    ~NRemoteWindow();

    virtual void Post(int Buffer);
    virtual void Wait(int* Buffer);
    bool textureExists(int buffer);
    bool textureCreate(int buffer, int texture);
    void textureDestroy(int buffer);

    void setEglDisplay(NEglDisplay display) {
        m_eglDisplay = display;
    }

protected:
    NRemoteTexture  m_remoteTexture[MaxRemoteTexture];
    NEglDisplay     m_eglDisplay;
};


// An NRemoteWindow with attached window buffers
struct NEXPORT NBufferedRemoteWindow : public NRemoteWindow
{
public:	
	NBufferedRemoteWindow(int width, int height, int numBuffers, unsigned int handle[], bool headered);
	virtual ~NBufferedRemoteWindow();

    virtual void Ack(int buffer);

    bool Lock(int* buffer); 
    void Unlock(int buffer);
    bool MapTexture(int Buffer, int Texture);
    void Invalidate(int buffer);
    bool IsDirty();
    
    int NumBuffers() {
        return m_numBuffers;
    }

    bool textureCreate(int buffer, int texture);
    void textureDestroy(int buffer);
    
    // Override to send buffer ack message
    virtual void sendBufferAck(int buffer);

    // Override to schedule a call to Ack(Buffer) in the context of the given thread
    virtual void threadScheduleAck(pthread_t threadId, int buffer);
    
protected:
    bool    m_unlockOnAck;
    unsigned int m_textureId[MaxRemoteTexture];
    int     m_numBuffers;
    int     m_currentBuffer;
    bool    m_needsAck[MaxRemoteTexture];
    bool    m_dirty[MaxRemoteTexture];
    int     m_lastDirty;
    
    pthread_t m_threadId;
};

#endif /* NREMOTEWINDOW_H_ */
