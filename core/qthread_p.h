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

#ifndef QTHREAD_P_H
#define QTHREAD_P_H

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
//

#include "qplatformdefs.h"
#include "QtCore/qthread.h"
#include "QtCore/qmutex.h"
#include "QtCore/qstack.h"
#include "QtCore/qwaitcondition.h"
#include "QtCore/qmap.h"
#ifndef QT_NO_COREAPPLICATION
#include "QtCore/qcoreapplication.h"
#endif
#ifndef QT_NO_QOBJECT
#include "private/qobject_p.h"
#else
#include "NoObject.h"
#endif

#include <algorithm>

#ifdef Q_OS_WINRT
namespace ABI {
    namespace Windows {
        namespace Foundation {
            struct IAsyncAction;
        }
    }
}
#endif // Q_OS_WINRT

QT_BEGIN_NAMESPACE

#ifndef QT_NO_QOBJECT
class QAbstractEventDispatcher;
class QEventLoop;

class QPostEvent
{
public:
    QObject *receiver;
    QEvent *event;
    int priority;
    inline QPostEvent()
        : receiver(0), event(0), priority(0)
    { }
    inline QPostEvent(QObject *r, QEvent *e, int p)
        : receiver(r), event(e), priority(p)
    { }
};
Q_DECLARE_TYPEINFO(QPostEvent, Q_MOVABLE_TYPE);

inline bool operator<(const QPostEvent &first, const QPostEvent &second)
{
    return first.priority > second.priority;
}

// This class holds the list of posted events.
//  The list has to be kept sorted by priority
class QPostEventList : public QVector<QPostEvent>
{
public:
    // recursion == recursion count for sendPostedEvents()
    int recursion;

    // sendOffset == the current event to start sending
    int startOffset;
    // insertionOffset == set by sendPostedEvents to tell postEvent() where to start insertions
    int insertionOffset;

    QMutex mutex;

    inline QPostEventList()
        : QVector<QPostEvent>(), recursion(0), startOffset(0), insertionOffset(0)
    { }

    void addEvent(const QPostEvent &ev) {
        int priority = ev.priority;
        if (isEmpty() ||
            last().priority >= priority ||
            insertionOffset >= size()) {
            // optimization: we can simply append if the last event in
            // the queue has higher or equal priority
            append(ev);
        } else {
            // insert event in descending priority order, using upper
            // bound for a given priority (to ensure proper ordering
            // of events with the same priority)
            QPostEventList::iterator at = std::upper_bound(begin() + insertionOffset, end(), ev);
            insert(at, ev);
        }
    }
private:
    //hides because they do not keep that list sorted. addEvent must be used
    using QVector<QPostEvent>::append;
    using QVector<QPostEvent>::insert;
};
#endif

#ifndef QT_NO_THREAD

class Q_CORE_EXPORT QDaemonThread : public QThread
{
public:
    QDaemonThread(QObject *parent = 0);
    ~QDaemonThread();
};

class QThreadPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QThread)

public:
    QThreadPrivate(QThreadData *d = 0);
    ~QThreadPrivate();

    void setPriority(QThread::Priority prio);

    mutable QMutex mutex;
    QAtomicInt quitLockRef;

    bool running;
    bool finished;
    bool isInFinish; //when in QThreadPrivate::finish
    bool interruptionRequested;

    bool exited;
    int returnCode;

    uint stackSize;
    QThread::Priority priority;

    static QThread *threadForId(int id);

#ifdef Q_OS_UNIX
    QWaitCondition thread_done;

    static void *start(void *arg);
    static void finish(void *);

#endif // Q_OS_UNIX

#ifdef Q_OS_WIN
    static unsigned int __stdcall start(void *);
    static void finish(void *, bool lockAnyway=true);

    Qt::HANDLE handle;
    unsigned int id;
    int waiters;
    bool terminationEnabled, terminatePending;
#endif // Q_OS_WIN
    QThreadData *data;

    static void createEventDispatcher(QThreadData *data);

    void ref()
    {
        quitLockRef.ref();
    }

    void deref()
    {
        if (!quitLockRef.deref() && running) {
#if !defined(QT_NO_COREAPPLICATION) && !defined(QT_NO_QOBJECT)
            QCoreApplication::instance()->postEvent(q_ptr, new QEvent(QEvent::Quit));
#endif
        }
    }
};

class QThreadData
{
public:
    QThreadData(int initialRefCount = 1);
    ~QThreadData();

    static Q_AUTOTEST_EXPORT QThreadData *current(bool createIfNecessary = true);
    static void clearCurrentThreadData();
    static QThreadData *get2(QThread *thread)
    { Q_ASSERT_X(thread != 0, "QThread", "internal error"); return thread->d_func()->data; }


    void ref();
    void deref();
#ifndef QT_NO_QOBJECT
    inline bool hasEventDispatcher() const
    { return eventDispatcher.load() != 0; }
#endif

    bool canWaitLocked()
    {
#ifndef QT_NO_QOBJECT
        QMutexLocker locker(&postEventList.mutex);
#endif
        return canWait;
    }

    // This class provides per-thread (by way of being a QThreadData
    // member) storage for qFlagLocation()
    class FlaggedDebugSignatures
    {
        static const uint Count = 2;

        uint idx;
        const char* locations[Count];

    public:
        FlaggedDebugSignatures() : idx(0)
        { std::fill_n(locations, Count, static_cast<char*>(0)); }

        void store(const char* method)
        { locations[idx++ % Count] = method; }

        bool contains(const char *method) const
        { return std::find(locations, locations + Count, method) != locations + Count; }
    };

private:
    QAtomicInt _ref;

public:
    int loopLevel;

#ifndef QT_NO_QOBJECT
    QStack<QEventLoop *> eventLoops;
    QPostEventList postEventList;
    QAtomicPointer<QAbstractEventDispatcher> eventDispatcher;
#endif
    QAtomicPointer<QThread> thread;
    Qt::HANDLE threadId;
    QVector<void *> tls;
    FlaggedDebugSignatures flaggedSignatures;

    bool quitNow;
    bool canWait;
    bool isAdopted;
    bool requiresCoreApplication;
};

class QScopedLoopLevelCounter
{
    QThreadData *threadData;
public:
    inline QScopedLoopLevelCounter(QThreadData *threadData)
        : threadData(threadData)
    { ++threadData->loopLevel; }
    inline ~QScopedLoopLevelCounter()
    { --threadData->loopLevel; }
};

// thread wrapper for the main() thread
class QAdoptedThread : public QThread
{
    Q_DECLARE_PRIVATE(QThread)

public:
    QAdoptedThread(QThreadData *data = 0);
    ~QAdoptedThread();
    void init();

private:
    void run() Q_DECL_OVERRIDE;
};


#else // QT_NO_THREAD

class QThreadData;

class QThreadPrivate : public QObjectPrivate
{
public:
    QThreadPrivate(QThreadData *d = 0) {}
    ~QThreadPrivate() {}

    // TODO RK QThreadData *data; // nowhere required so far

    static void setCurrentThread(QThread*) {}
    static QThread *threadForId(int) { return QThread::currentThread(); }
    static void createEventDispatcher(QThreadData *data);

    void ref() {}
    void deref() {}

    Q_DECLARE_PUBLIC(QThread)
};

#endif // QT_NO_THREAD



QT_END_NAMESPACE

#endif // QTHREAD_P_H
