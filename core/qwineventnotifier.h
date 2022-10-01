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

#ifndef QWINEVENTNOTIFIER_H
#define QWINEVENTNOTIFIER_H

#include "QtCore/qobject.h"

//#ifdef Q_OS_WIN

QT_BEGIN_NAMESPACE

class QWinEventNotifierPrivate;
class QEvent;
class Q_CORE_EXPORT QWinEventNotifier : public QObject
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
#endif
    Q_DECLARE_PRIVATE(QWinEventNotifier)
    typedef Qt::HANDLE HANDLE;

public:
    explicit QWinEventNotifier(QObject *parent = Q_NULLPTR);
    explicit QWinEventNotifier(HANDLE hEvent, QObject *parent = Q_NULLPTR);
    ~QWinEventNotifier();

    void setHandle(HANDLE hEvent);
    HANDLE handle() const;

    bool isEnabled() const;

public Q_SLOTS:
    void setEnabled(bool enable);

#ifndef QT_NO_QOBJECT
Q_SIGNALS:
    void activated(HANDLE hEvent, QPrivateSignal);
#endif

protected:
    bool event(QEvent * e);
};

QT_END_NAMESPACE

//#endif // Q_OS_WIN

#endif // QWINEVENTNOTIFIER_H
