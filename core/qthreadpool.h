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

#ifndef QTHREADPOOL_H
#define QTHREADPOOL_H

#include <QtCore/qglobal.h>

#include <QtCore/qthread.h>
#include <QtCore/qrunnable.h>

#ifndef QT_NO_THREAD

QT_BEGIN_NAMESPACE


class QThreadPoolPrivate;
class Q_CORE_EXPORT QThreadPool : public QObject
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
    Q_PROPERTY(int expiryTimeout READ expiryTimeout WRITE setExpiryTimeout)
    Q_PROPERTY(int maxThreadCount READ maxThreadCount WRITE setMaxThreadCount)
    Q_PROPERTY(int activeThreadCount READ activeThreadCount)
#endif
    Q_DECLARE_PRIVATE(QThreadPool)
    friend class QFutureInterfaceBase;

public:
    QThreadPool(QObject *parent = Q_NULLPTR);
    ~QThreadPool();

    static QThreadPool *globalInstance();

    void start(QRunnable *runnable, int priority = 0);
    bool tryStart(QRunnable *runnable);

    int expiryTimeout() const;
    void setExpiryTimeout(int expiryTimeout);

    int maxThreadCount() const;
    void setMaxThreadCount(int maxThreadCount);

    int activeThreadCount() const;

    void reserveThread();
    void releaseThread();

    bool waitForDone(int msecs = -1);

    void clear();
    void cancel(QRunnable *runnable);
};

QT_END_NAMESPACE

#endif // QT_NO_THREAD

#endif
