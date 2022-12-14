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

#ifndef QPLATFORMINTEGRATION_H
#define QPLATFORMINTEGRATION_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtGui/qwindowdefs.h>
#include <qpa/qplatformscreen.h>
#include <QtGui/qsurfaceformat.h>
//#include <QtGui/qopenglcontext.h>

QT_BEGIN_NAMESPACE


class QPlatformWindow;
class QWindow;
class QPlatformBackingStore;
class QPlatformFontDatabase;
class QPlatformClipboard;
class QPlatformNativeInterface;
class QPlatformDrag;
class QPlatformOpenGLContext;
class QGuiGLFormat;
class QAbstractEventDispatcher;
class QPlatformInputContext;
class QPlatformAccessibility;
class QPlatformTheme;
class QPlatformDialogHelper;
class QPlatformSharedGraphicsCache;
class QPlatformServices;
class QPlatformSessionManager;
class QKeyEvent;
class QPlatformOffscreenSurface;
class QOffscreenSurface;

class Q_GUI_EXPORT QPlatformIntegration
{
public:
    enum Capability {
        ThreadedPixmaps = 1,
        OpenGL,
        ThreadedOpenGL,
        SharedGraphicsCache,
        BufferQueueingOpenGL,
        WindowMasks,
        MultipleWindows,
        ApplicationState,
        ForeignWindows,
        NonFullScreenWindows,
        NativeWidgets,
        WindowManagement,
        SyncState,
        RasterGLSurface,
        AllGLFunctionsQueryable,
        ApplicationIcon,
        SwitchableWidgetComposition
    };

    virtual ~QPlatformIntegration() { }

    virtual bool hasCapability(Capability cap) const;

    virtual QPlatformPixmap *createPlatformPixmap(QPlatformPixmap::PixelType type) const;
    virtual QPlatformWindow *createPlatformWindow(QWindow *window) const = 0;
    virtual QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const = 0;
#ifndef QT_NO_OPENGL
    virtual QPlatformOpenGLContext *createPlatformOpenGLContext(QOpenGLContext *context) const;
#endif
    virtual QPlatformSharedGraphicsCache *createPlatformSharedGraphicsCache(const char *cacheId) const;
    virtual QPaintEngine *createImagePaintEngine(QPaintDevice *paintDevice) const;

// Event dispatcher:
    virtual QAbstractEventDispatcher *createEventDispatcher() const = 0;
    virtual void initialize();
    virtual void destroy();

//Deeper window system integrations
    virtual QPlatformFontDatabase *fontDatabase() const;
#ifndef QT_NO_CLIPBOARD
    virtual QPlatformClipboard *clipboard() const;
#endif
#ifndef QT_NO_DRAGANDDROP
    virtual QPlatformDrag *drag() const;
#endif
    virtual QPlatformInputContext *inputContext() const;
#ifndef QT_NO_ACCESSIBILITY
    virtual QPlatformAccessibility *accessibility() const;
#endif

    // Access native handles. The window handle is already available from Wid;
    virtual QPlatformNativeInterface *nativeInterface() const;

    virtual QPlatformServices *services() const;

    enum StyleHint {
        CursorFlashTime,
        KeyboardInputInterval,
        MouseDoubleClickInterval,
        StartDragDistance,
        StartDragTime,
        KeyboardAutoRepeatRate,
        ShowIsFullScreen,
        PasswordMaskDelay,
        FontSmoothingGamma,
        StartDragVelocity,
        UseRtlExtensions,
        PasswordMaskCharacter,
        SetFocusOnTouchRelease,
        ShowIsMaximized,
        MousePressAndHoldInterval,
        TabFocusBehavior,
        ReplayMousePressOutsidePopup,
        ItemViewActivateItemOnSingleClick
    };

    virtual QVariant styleHint(StyleHint hint) const;
    virtual Qt::WindowState defaultWindowState(Qt::WindowFlags) const;

    virtual Qt::KeyboardModifiers queryKeyboardModifiers() const;
    virtual QList<int> possibleKeys(const QKeyEvent *) const;

    virtual QStringList themeNames() const;
    virtual QPlatformTheme *createPlatformTheme(const QString &name) const;

    virtual QPlatformOffscreenSurface *createPlatformOffscreenSurface(QOffscreenSurface *surface) const;

#ifndef QT_NO_SESSIONMANAGER
    virtual QPlatformSessionManager *createPlatformSessionManager(const QString &id, const QString &key) const;
#endif

    virtual void sync();

#ifndef QT_NO_OPENGL
    virtual QOpenGLContext::OpenGLModuleType openGLModuleType();
#endif
    virtual void setApplicationIcon(const QIcon &icon) const;

    void removeScreen(QScreen *screen);

protected:
    void screenAdded(QPlatformScreen *screen, bool isPrimary = false);
    void destroyScreen(QPlatformScreen *screen);
    void setPrimaryScreen(QPlatformScreen *newPrimary);
};

QT_END_NAMESPACE

#endif // QPLATFORMINTEGRATION_H
