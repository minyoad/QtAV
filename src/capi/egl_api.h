/******************************************************************************
    mkapi dynamic load code generation for capi template
    Copyright (C) 2014 Wang Bin <wbsecg1@gmail.com>
    https://github.com/wang-bin/mkapi
    https://github.com/wang-bin/capi

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#ifndef EGL_API_H
#define EGL_API_H

// no need to include the C header if only functions declared there
#ifndef CAPI_LINK_EGL
namespace egl {
namespace capi {
#define EGLAPI // avoid warning and link error
#else
extern "C" {
#endif
// the following line will be replaced by the content of config/EGL/include if exists
#include "EGL/egl.h"
#ifndef CAPI_LINK_EGL
}
#endif
}

namespace egl {
#ifndef CAPI_LINK_EGL
using namespace capi; // original header is in namespace capi, types are changed
#endif // CAPI_LINK_EGL
class api_dll;
class api
{
    api_dll *dll;
public:
    api();
    virtual ~api();
    virtual bool loaded() const; // user may inherits multiple api classes: final::loaded() { return base1::loaded() && base2::loaded();}
#if !defined(CAPI_LINK_EGL) && !defined(EGL_CAPI_NS)
// mkapi code generation BEGIN
    EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint * attrib_list, EGLConfig * configs, EGLint config_size, EGLint * num_config);
    EGLBoolean eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
    EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint * attrib_list);
    EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint * attrib_list);
    EGLSurface eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint * attrib_list);
    EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint * attrib_list);
    EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
    EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface);
    EGLBoolean eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint * value);
    EGLBoolean eglGetConfigs(EGLDisplay dpy, EGLConfig * configs, EGLint config_size, EGLint * num_config);
    EGLDisplay eglGetCurrentDisplay();
    EGLSurface eglGetCurrentSurface(EGLint readdraw);
    EGLDisplay eglGetDisplay(EGLNativeDisplayType display_id);
    EGLint eglGetError();
    __eglMustCastToProperFunctionPointerType eglGetProcAddress(const char * procname);
    EGLBoolean eglInitialize(EGLDisplay dpy, EGLint * major, EGLint * minor);
    EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
    EGLBoolean eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint * value);
    const char * eglQueryString(EGLDisplay dpy, EGLint name);
    EGLBoolean eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint * value);
    EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);
    EGLBoolean eglTerminate(EGLDisplay dpy);
    EGLBoolean eglWaitGL();
    EGLBoolean eglWaitNative(EGLint engine);
    EGLBoolean eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
    EGLBoolean eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
    EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
    EGLBoolean eglSwapInterval(EGLDisplay dpy, EGLint interval);
    EGLBoolean eglBindAPI(EGLenum api);
    EGLenum eglQueryAPI();
    EGLSurface eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint * attrib_list);
    EGLBoolean eglReleaseThread();
    EGLBoolean eglWaitClient();
    EGLContext eglGetCurrentContext();
    EGLSync eglCreateSync(EGLDisplay dpy, EGLenum type, const EGLAttrib * attrib_list);
    EGLBoolean eglDestroySync(EGLDisplay dpy, EGLSync sync);
    EGLint eglClientWaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
    EGLBoolean eglGetSyncAttrib(EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib * value);
    EGLDisplay eglGetPlatformDisplay(EGLenum platform, void * native_display, const EGLAttrib * attrib_list);
    EGLSurface eglCreatePlatformWindowSurface(EGLDisplay dpy, EGLConfig config, void * native_window, const EGLAttrib * attrib_list);
    EGLSurface eglCreatePlatformPixmapSurface(EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLAttrib * attrib_list);
    EGLBoolean eglWaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags);
// mkapi code generation END
#endif // !defined(CAPI_LINK_EGL) && !defined(EGL_CAPI_NS)
};
} //namespace egl

#ifndef EGL_CAPI_BUILD
#ifdef EGL_CAPI_NS
using namespace egl::capi;
#else
using namespace egl;
#endif
#endif //EGL_CAPI_BUILD
#endif // EGL_API_H
//this file is generated by "mkapi.sh -I /Users/wangbin/dev/qtbase/src/3rdparty/angle/include -name egl -template capi /Users/wangbin/dev/qtbase/src/3rdparty/angle/include/EGL/egl.h"
