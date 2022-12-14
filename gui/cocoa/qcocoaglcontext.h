/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QCOCOAGLCONTEXT_H
#define QCOCOAGLCONTEXT_H

#include <QtCore/QPointer>
//#include <qpa/qplatformopenglcontext.h>
//#include <QtGui/QOpenGLContext>
#include <QtGui/QWindow>

#undef slots
#include <Cocoa/Cocoa.h>

QT_BEGIN_NAMESPACE

class QCocoaGLContext : public QPlatformOpenGLContext
{
public:
    QCocoaGLContext(const QSurfaceFormat &format, QPlatformOpenGLContext *share, const QVariant &nativeHandle);
    ~QCocoaGLContext();

    QSurfaceFormat format() const Q_DECL_OVERRIDE;

    void swapBuffers(QPlatformSurface *surface) Q_DECL_OVERRIDE;

    bool makeCurrent(QPlatformSurface *surface) Q_DECL_OVERRIDE;
    void doneCurrent() Q_DECL_OVERRIDE;

    void (*getProcAddress(const QByteArray &procName)) () Q_DECL_OVERRIDE;

    void update();

    static NSOpenGLPixelFormat *createNSOpenGLPixelFormat(const QSurfaceFormat &format);
    NSOpenGLContext *nsOpenGLContext() const;

    bool isSharing() const Q_DECL_OVERRIDE;
    bool isValid() const Q_DECL_OVERRIDE;

    void windowWasHidden();

    QVariant nativeHandle() const;

private:
    void setActiveWindow(QWindow *window);
    void updateSurfaceFormat();

    NSOpenGLContext *m_context;
    NSOpenGLContext *m_shareContext;
    QSurfaceFormat m_format;
    QPointer<QWindow> m_currentWindow;
};

QT_END_NAMESPACE

#endif // QCOCOAGLCONTEXT_H
