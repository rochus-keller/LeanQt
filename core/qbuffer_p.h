#ifndef Q_BUFFER_P
#define Q_BUFFER_P
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

#include "qbuffer.h"
#include "private/qiodevice_p.h"

QT_BEGIN_NAMESPACE

/** QBufferPrivate **/
class QBufferPrivate : public QIODevicePrivate
{
    Q_DECLARE_PUBLIC(QBuffer)

public:
    QBufferPrivate()
    : buf(0)
#ifndef QT_NO_QOBJECT
        , writtenSinceLastEmit(0), signalConnectionCount(0), signalsEmitted(false)
#endif
    { }
    ~QBufferPrivate() { }

    QByteArray *buf;
    QByteArray defaultBuf;

    virtual qint64 peek(char *data, qint64 maxSize) Q_DECL_OVERRIDE;
    virtual QByteArray peek(qint64 maxSize) Q_DECL_OVERRIDE;

#ifndef QT_NO_QOBJECT
    // private slots
    void _q_emitSignals();

    qint64 writtenSinceLastEmit;
    int signalConnectionCount;
    bool signalsEmitted;
#endif
};

QT_END_NAMESPACE

#endif
