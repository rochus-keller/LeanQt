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

#ifndef QBUFFER_H
#define QBUFFER_H

#include <QtCore/qiodevice.h>
#include <QtCore/qbytearray.h>

QT_BEGIN_NAMESPACE


class QObject;
class QBufferPrivate;

class Q_CORE_EXPORT QBuffer : public QIODevice
{
#ifndef QT_NO_QOBJECT
    Q_OBJECT
#endif

public:
     explicit QBuffer(QObject *parent = Q_NULLPTR);
     QBuffer(QByteArray *buf, QObject *parent = Q_NULLPTR);
    ~QBuffer();

    QByteArray &buffer();
    const QByteArray &buffer() const;
    void setBuffer(QByteArray *a);

    void setData(const QByteArray &data);
    inline void setData(const char *data, int len);
    const QByteArray &data() const;

    bool open(OpenMode openMode) Q_DECL_OVERRIDE;

    void close() Q_DECL_OVERRIDE;
    qint64 size() const Q_DECL_OVERRIDE;
    qint64 pos() const Q_DECL_OVERRIDE;
    bool seek(qint64 off) Q_DECL_OVERRIDE;
    bool atEnd() const Q_DECL_OVERRIDE;
    bool canReadLine() const Q_DECL_OVERRIDE;

protected:
#ifndef QT_NO_QOBJECT
    void connectNotify(const QMetaMethod &) Q_DECL_OVERRIDE;
    void disconnectNotify(const QMetaMethod &) Q_DECL_OVERRIDE;
#endif
    qint64 readData(char *data, qint64 maxlen) Q_DECL_OVERRIDE;
    qint64 writeData(const char *data, qint64 len) Q_DECL_OVERRIDE;

private:
    Q_DECLARE_PRIVATE(QBuffer)
    Q_DISABLE_COPY(QBuffer)

#ifndef QT_NO_QOBJECT
    Q_PRIVATE_SLOT(d_func(), void _q_emitSignals())
#endif
};

inline void QBuffer::setData(const char *adata, int alen)
{ setData(QByteArray(adata, alen)); }

QT_END_NAMESPACE

#endif // QBUFFER_H
