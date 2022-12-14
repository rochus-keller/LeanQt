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

#ifndef QTHREAD_H
#define QTHREAD_H

#include <QtCore/qobject.h>

#include <limits.h>

QT_BEGIN_NAMESPACE


class QThreadData;
class QThreadPrivate;
class QAbstractEventDispatcher;

#ifndef QT_NO_THREAD
class Q_CORE_EXPORT QThread : public QObject
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
#endif
public:
    static Qt::HANDLE currentThreadId() Q_DECL_NOTHROW;
    static QThread *currentThread();
    static int idealThreadCount() Q_DECL_NOTHROW;
    static void yieldCurrentThread();

    explicit QThread(QObject *parent = Q_NULLPTR);
    ~QThread();

    enum Priority {
        IdlePriority,

        LowestPriority,
        LowPriority,
        NormalPriority,
        HighPriority,
        HighestPriority,

        TimeCriticalPriority,

        InheritPriority
    };

    void setPriority(Priority priority);
    Priority priority() const;

    bool isFinished() const;
    bool isRunning() const;

    void requestInterruption();
    bool isInterruptionRequested() const;

    void setStackSize(uint stackSize);
    uint stackSize() const;

    void exit(int retcode = 0);

#ifndef QT_NO_QOBJECT
    QAbstractEventDispatcher *eventDispatcher() const;
    void setEventDispatcher(QAbstractEventDispatcher *eventDispatcher);
    bool event(QEvent *event) Q_DECL_OVERRIDE;
#endif

    int loopLevel() const;

public Q_SLOTS:
    void start(Priority = InheritPriority);
    void terminate();
    void quit();

public:
    // default argument causes thread to block indefinetely
    bool wait(unsigned long time = ULONG_MAX);

    static void sleep(unsigned long);
    static void msleep(unsigned long);
    static void usleep(unsigned long);

#ifndef QT_NO_QOBJECT
Q_SIGNALS:
    void started(QPrivateSignal);
    void finished(QPrivateSignal);
#endif

protected:
    virtual void run();
    int exec();

    static void setTerminationEnabled(bool enabled = true);

protected:
    QThread(QThreadPrivate &dd, QObject *parent = Q_NULLPTR);

private:
    Q_DECLARE_PRIVATE(QThread)

    friend class QCoreApplication;
    friend class QThreadData;
};

#else // QT_NO_THREAD

class Q_CORE_EXPORT QThread : public QObject
{
public:
    static Qt::HANDLE currentThreadId() { return Qt::HANDLE(currentThread()); }
    static QThread* currentThread();

protected:
    QThread(QThreadPrivate &dd, QObject *parent = 0);

private:
    explicit QThread(QObject *parent = 0);
    static QThread *instance;

    friend class QCoreApplication;
    friend class QThreadData;
    friend class QAdoptedThread;
    Q_DECLARE_PRIVATE(QThread)
};

#endif // QT_NO_THREAD

QT_END_NAMESPACE

#endif // QTHREAD_H
