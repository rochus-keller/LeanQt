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

#include "qsystemsemaphore.h"
#include "qsystemsemaphore_p.h"

#include <qdebug.h>
#ifndef QT_NO_COREAPPLICATION
#include <qcoreapplication.h>
#define _TRANSLATE(ctx,str) QCoreApplication::translate(ctx,str)
#else
#define _TRANSLATE(ctx,str) QString(str)
#endif

#ifndef QT_NO_SYSTEMSEMAPHORE

#include <sys/types.h>
#ifndef QT_POSIX_IPC
#include <sys/ipc.h>
#include <sys/sem.h>
#endif
#include <fcntl.h>
#include <errno.h>

#include "private/qcore_unix_p.h"

QT_BEGIN_NAMESPACE

QSystemSemaphorePrivate::QSystemSemaphorePrivate() :
#ifndef QT_POSIX_IPC
    unix_key(-1), semaphore(-1), createdFile(false),
#else
    semaphore(SEM_FAILED),
#endif // QT_POSIX_IPC
    createdSemaphore(false), error(QSystemSemaphore::NoError)
{
}

void QSystemSemaphorePrivate::setErrorString(const QString &function)
{
    // EINVAL is handled in functions so they can give better error strings
    switch (errno) {
    case EPERM:
    case EACCES:
        errorString = _TRANSLATE("QSystemSemaphore", "%1: permission denied").arg(function);
        error = QSystemSemaphore::PermissionDenied;
        break;
    case EEXIST:
        errorString = _TRANSLATE("QSystemSemaphore", "%1: already exists").arg(function);
        error = QSystemSemaphore::AlreadyExists;
        break;
    case ENOENT:
        errorString = _TRANSLATE("QSystemSemaphore", "%1: does not exist").arg(function);
        error = QSystemSemaphore::NotFound;
        break;
    case ERANGE:
    case ENOSPC:
        errorString = _TRANSLATE("QSystemSemaphore", "%1: out of resources").arg(function);
        error = QSystemSemaphore::OutOfResources;
        break;
    default:
        errorString = _TRANSLATE("QSystemSemaphore", "%1: unknown error %2").arg(function).arg(errno);
        error = QSystemSemaphore::UnknownError;
#if defined QSYSTEMSEMAPHORE_DEBUG
        qDebug() << errorString << "key" << key << "errno" << errno << EINVAL;
#endif
    }
}

QT_END_NAMESPACE

#endif // QT_NO_SYSTEMSEMAPHORE
