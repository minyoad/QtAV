/******************************************************************************
    QtAV:  Media play library based on Qt and FFmpeg
    Copyright (C) 2014-2015 Wang Bin <wbsecg1@gmail.com>

*   This file is part of QtAV

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

#ifndef QTAV_SURFACEINTEROPVAAPI_H
#define QTAV_SURFACEINTEROPVAAPI_H

#include <QtCore/QMap>
#include <QtCore/QSharedPointer>
#include <QtCore/QMutex>
#include "QtAV/SurfaceInterop.h"
#include "vaapi_helper.h"

#if defined(QT_OPENGL_ES_2)
#include <EGL/egl.h>
#else
#include <GL/glx.h>
#ifdef Bool
#undef Bool
#endif //Bool
#ifdef CursorShape
#undef CursorShape //used in qvariant and x11
#endif //CursorShape
#ifdef Status
#undef Status // qtextstream
#endif //Status
#endif //defined(QT_OPENGL_ES_2)

namespace QtAV {
namespace vaapi {

class SurfaceInteropVAAPI : public VideoSurfaceInterop
{
public:
    virtual void setSurface(const surface_ptr& surface) = 0;
protected:
    //surface_ptr m_surface; //FIXME: why vaTerminate() crash (in ~display_t()) if put m_surface here?
    QMutex mutex;
};
// TODO: move create glx surface to decoder, interop only map/unmap, 1 interop per frame
// load/resolve symbols only once in decoder and pass a VAAPI_XXX ptr
// or use pool
class VAAPI_GLX_Interop Q_DECL_FINAL: public SurfaceInteropVAAPI, public VAAPI_GLX
{
public:
    VAAPI_GLX_Interop();
    void setSurface(const surface_ptr& surface) { //in decoding thread. map in rendering thread
        QMutexLocker lock(&mutex);
        m_surface = surface;
    }
    // return glx surface
    surface_glx_ptr createGLXSurface(void* handle);
    virtual void* map(SurfaceType type, const VideoFormat& fmt, void* handle, int plane);
    virtual void unmap(void *handle);
    virtual void* createHandle(SurfaceType type, const VideoFormat& fmt, int plane = 0);
private:
    QMap<GLuint*,surface_glx_ptr> glx_surfaces, tmp_surfaces;
    surface_ptr m_surface;
};
typedef QSharedPointer<VAAPI_GLX_Interop> VAAPI_GLX_InteropPtr;

#ifndef QT_OPENGL_ES_2
class VAAPI_X_GLX_Interop Q_DECL_FINAL: public SurfaceInteropVAAPI, public VAAPI_X11
{
public:
    VAAPI_X_GLX_Interop();
    ~VAAPI_X_GLX_Interop();
    void setSurface(const surface_ptr& surface) { //in decoding thread. map in rendering thread
        QMutexLocker lock(&mutex);
        m_surface = surface;
    }
    void* map(SurfaceType type, const VideoFormat& fmt, void* handle, int plane) Q_DECL_OVERRIDE;
    void unmap(void *handle) Q_DECL_OVERRIDE;
private:
    bool ensureGLX();
    bool ensurePixmaps(int w, int h);
    Display *xdisplay;
    GLXFBConfig fbc;
    Pixmap pixmap;
    GLXPixmap glxpixmap;
    int width, height;
    surface_ptr m_surface;

    typedef void (*glXBindTexImage_t)(Display *dpy, GLXDrawable draw, int buffer, int *a);
    typedef void (*glXReleaseTexImage_t)(Display *dpy, GLXDrawable draw, int buffer);
    static glXBindTexImage_t glXBindTexImage;
    static glXReleaseTexImage_t glXReleaseTexImage;
};
#endif //QT_OPENGL_ES_2
} //namespace QtAV
} //namespace vaapi

#endif // QTAV_SURFACEINTEROPVAAPI_H
