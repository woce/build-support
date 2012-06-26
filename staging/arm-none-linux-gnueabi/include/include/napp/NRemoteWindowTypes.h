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

// Public defines because we can't be guaranteed the egl/gles headers
// exist on all platforms.
#define NEglDisplay           void*
#define NEglImageKHR          void*

#if HAVEGLES

#include <EGL/egl.h>
#define EGL_EGLEXT_PROTOTYPES
#include <EGL/eglext.h>

#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>

typedef EGLImageKHR (*eglCreateImageKHR_t)(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
typedef EGLBoolean  (*eglDestroyImageKHR_t)(EGLDisplay dpy, EGLImageKHR image);

#define NEglCreateImageKHR_f   eglCreateImageKHR_t
#define NEglDestroyImageKHR_f  eglDestroyImageKHR_t

#else

#define NEglCreateImageKHR_f   void*
#define NEglDestroyImageKHR_f  void*

#endif
