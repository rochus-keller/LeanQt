/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QCOREAPPLICATION_P_H
#define QCOREAPPLICATION_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "QtCore/qcoreapplication.h"
#include "QtCore/qtranslator.h"
#include "QtCore/qsettings.h"
#ifndef QT_NO_QOBJECT
#include "private/qobject_p.h"
#endif
#ifndef QT_NO_THREAD
#include "QtCore/qthread.h"
#endif

QT_BEGIN_NAMESPACE

typedef QList<QTranslator*> QTranslatorList;

class QAbstractEventDispatcher;

class Q_CORE_EXPORT QCoreApplicationPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QCoreApplication)

public:
    enum Type {
        Tty,
        Gui
    };

    QCoreApplicationPrivate(int &aargc,  char **aargv, uint flags);
    ~QCoreApplicationPrivate();

    void init();

    QString appName() const;

#ifdef Q_OS_MAC
    static QString macMenuBarName();
#endif

    static void initLocale();

    static bool checkInstance(const char *method);

#ifndef QT_NO_QOBJECT
    bool sendThroughApplicationEventFilters(QObject *, QEvent *);
    static bool sendThroughObjectEventFilters(QObject *, QEvent *);
    static bool notify_helper(QObject *, QEvent *);
    static inline void setEventSpontaneous(QEvent *e, bool spontaneous) { e->spont = spontaneous; }

    virtual void createEventDispatcher();
    virtual void eventDispatcherReady();
    static void removePostedEvent(QEvent *);
#ifdef Q_OS_WIN
    static void removePostedTimerEvent(QObject *object, int timerId);
#endif

    QAtomicInt quitLockRef;
    void ref();
    void deref();
    virtual bool shouldQuit() {
      return true;
    }
    void maybeQuit();

    static void sendPostedEvents(QObject *receiver, int event_type, QThreadData *data);

    static void checkReceiverThread(QObject *receiver);
    void cleanupThreadData();
#endif // QT_NO_QOBJECT

#ifndef QT_NO_THREAD
    static QBasicAtomicPointer<QThread> theMainThread;
    static QThread *mainThread();
    static bool threadRequiresCoreApplication();
#endif

    int &argc;
    char **argv;
#if defined(Q_OS_WIN) && !defined(Q_OS_WINRT)
    int origArgc;
    char **origArgv; // store unmodified arguments for QCoreApplication::arguments()
#endif
    void appendApplicationPathToLibraryPaths(void);

#ifndef QT_NO_TRANSLATION
    QTranslatorList translators;

    static bool isTranslatorInstalled(QTranslator *translator);
#endif

    QCoreApplicationPrivate::Type application_type;

    QString cachedApplicationDirPath;
    static QString *cachedApplicationFilePath;
    static void setApplicationFilePath(const QString &path);
    static inline void clearApplicationFilePath() { delete cachedApplicationFilePath; cachedApplicationFilePath = 0; }

#ifndef QT_NO_QOBJECT
    bool in_exec;
    bool aboutToQuitEmitted;
    bool threadData_clean;

    static QAbstractEventDispatcher *eventDispatcher;
    static bool is_app_running;
    static bool is_app_closing;
#endif

    static bool setuidAllowed;
    static uint attribs;
    static inline bool testAttribute(uint flag) { return attribs & (1 << flag); }
    static int app_compile_version;

    void processCommandLineArguments();
    QString qmljs_debug_arguments; // a string containing arguments for js/qml debugging.
    inline QString qmljsDebugArgumentsString() { return qmljs_debug_arguments; }
};

QT_END_NAMESPACE

#endif // QCOREAPPLICATION_P_H
