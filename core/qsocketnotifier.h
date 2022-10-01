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

#ifndef QSOCKETNOTIFIER_H
#define QSOCKETNOTIFIER_H

#include <QtCore/qobject.h>

QT_BEGIN_NAMESPACE

class QSocketNotifierPrivate;
class QEvent;
class Q_CORE_EXPORT QSocketNotifier : public QObject
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
#endif
    Q_DECLARE_PRIVATE(QSocketNotifier)

public:
    enum Type { Read, Write, Exception };

    QSocketNotifier(qintptr socket, Type, QObject *parent = Q_NULLPTR);
    ~QSocketNotifier();

    qintptr socket() const;
    Type type() const;

    bool isEnabled() const;

public Q_SLOTS:
    void setEnabled(bool);

#ifndef QT_NO_QOBJECT
Q_SIGNALS:
    void activated(int socket, QPrivateSignal);
#endif

protected:
    bool event(QEvent *); // Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QSocketNotifier)
};

QT_END_NAMESPACE

#endif // QSOCKETNOTIFIER_H
