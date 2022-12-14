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

#ifndef QFILEDEVICE_P_H
#define QFILEDEVICE_P_H

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

#include "private/qiodevice_p.h"
#include "private/qringbuffer_p.h"
#include "qfiledevice.h"

QT_BEGIN_NAMESPACE

class QAbstractFileEngine;
class QFSFileEngine;

class QFileDevicePrivate : public QIODevicePrivate
{
    Q_DECLARE_PUBLIC(QFileDevice)
protected:
    QFileDevicePrivate();
    ~QFileDevicePrivate();

    virtual QAbstractFileEngine *engine() const;

    inline bool ensureFlushed() const;

    bool putCharHelper(char c) Q_DECL_OVERRIDE;

    void setError(QFileDevice::FileError err);
    void setError(QFileDevice::FileError err, const QString &errorString);
    void setError(QFileDevice::FileError err, int errNum);

    mutable QAbstractFileEngine *fileEngine;
    QRingBuffer writeBuffer;
    mutable qint64 cachedSize;

    QFileDevice::FileHandleFlags handleFlags;
    QFileDevice::FileError error;

    bool lastWasWrite;
};

inline bool QFileDevicePrivate::ensureFlushed() const
{
    // This function ensures that the write buffer has been flushed (const
    // because certain const functions need to call it.
    if (lastWasWrite) {
        const_cast<QFileDevicePrivate *>(this)->lastWasWrite = false;
        if (!const_cast<QFileDevice *>(q_func())->flush())
            return false;
    }
    return true;
}

QT_END_NAMESPACE

#endif // QFILEDEVICE_P_H
