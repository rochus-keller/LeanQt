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

#include "qplatformdefs.h"

#include "qsharedmemory.h"
#include "qsharedmemory_p.h"
#include "qsystemsemaphore.h"
#ifndef QT_NO_FILEENGINE
#include <qdir.h>
#endif
#include <qdebug.h>

#include <errno.h>

#ifndef QT_POSIX_IPC

#ifndef QT_NO_SHAREDMEMORY
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif //QT_NO_SHAREDMEMORY

#include "private/qcore_unix_p.h"

#ifndef QT_NO_SHAREDMEMORY
QT_BEGIN_NAMESPACE

/*!
    \internal

    If not already made create the handle used for accessing the shared memory.
*/
key_t QSharedMemoryPrivate::handle()
{
    // already made
    if (unix_key)
        return unix_key;

    // don't allow making handles on empty keys
    if (nativeKey.isEmpty()) {
        errorString = QSharedMemory::tr("%1: key is empty").arg(QLatin1String("QSharedMemory::handle:"));
        error = QSharedMemory::KeyError;
        return 0;
    }

    // ftok requires that an actual file exists somewhere
    if (!QFile::exists(nativeKey)) {
        errorString = QSharedMemory::tr("%1: UNIX key file doesn't exist").arg(QLatin1String("QSharedMemory::handle:"));
        error = QSharedMemory::NotFound;
        return 0;
    }

    unix_key = qt_safe_ftok(QFile::encodeName(nativeKey), 'Q');
    if (-1 == unix_key) {
        errorString = QSharedMemory::tr("%1: ftok failed").arg(QLatin1String("QSharedMemory::handle:"));
        error = QSharedMemory::KeyError;
        unix_key = 0;
    }
    return unix_key;
}

#endif // QT_NO_SHAREDMEMORY

#if !(defined(QT_NO_SHAREDMEMORY) && defined(QT_NO_SYSTEMSEMAPHORE))
/*!
    \internal
    Creates the unix file if needed.
    returns \c true if the unix file was created.

    -1 error
     0 already existed
     1 created
  */
int QSharedMemoryPrivate::createUnixKeyFile(const QString &fileName)
{
    int fd = qt_safe_open(QFile::encodeName(fileName).constData(),
            O_EXCL | O_CREAT | O_RDWR, 0640);
    if (-1 == fd) {
        if (errno == EEXIST)
            return 0;
        return -1;
    } else {
        close(fd);
    }
    return 1;
}
#endif // QT_NO_SHAREDMEMORY && QT_NO_SYSTEMSEMAPHORE

#ifndef QT_NO_SHAREDMEMORY

bool QSharedMemoryPrivate::cleanHandle()
{
    unix_key = 0;
    return true;
}

bool QSharedMemoryPrivate::create(int size)
{
    // build file if needed
    bool createdFile = false;
    int built = createUnixKeyFile(nativeKey);
    if (built == -1) {
        errorString = QSharedMemory::tr("%1: unable to make key").arg(QLatin1String("QSharedMemory::handle:"));
        error = QSharedMemory::KeyError;
        return false;
    }
    if (built == 1) {
        createdFile = true;
    }

    // get handle
    if (!handle()) {
        if (createdFile)
            QFile::remove(nativeKey);
        return false;
    }

    // create
    if (-1 == shmget(unix_key, size, 0600 | IPC_CREAT | IPC_EXCL)) {
        const QLatin1String function("QSharedMemory::create");
        switch (errno) {
        case EINVAL:
            errorString = QSharedMemory::tr("%1: system-imposed size restrictions").arg(QLatin1String("QSharedMemory::handle"));
            error = QSharedMemory::InvalidSize;
            break;
        default:
            setErrorString(function);
        }
        if (createdFile && error != QSharedMemory::AlreadyExists)
            QFile::remove(nativeKey);
        return false;
    }

    return true;
}

bool QSharedMemoryPrivate::attach(QSharedMemory::AccessMode mode)
{
    // grab the shared memory segment id
    int id = shmget(unix_key, 0, (mode == QSharedMemory::ReadOnly ? 0400 : 0600));
    if (-1 == id) {
        setErrorString(QLatin1String("QSharedMemory::attach (shmget)"));
        return false;
    }

    // grab the memory
    memory = shmat(id, 0, (mode == QSharedMemory::ReadOnly ? SHM_RDONLY : 0));
    if ((void*) - 1 == memory) {
        memory = 0;
        setErrorString(QLatin1String("QSharedMemory::attach (shmat)"));
        return false;
    }

    // grab the size
    shmid_ds shmid_ds;
    if (!shmctl(id, IPC_STAT, &shmid_ds)) {
        size = (int)shmid_ds.shm_segsz;
    } else {
        setErrorString(QLatin1String("QSharedMemory::attach (shmctl)"));
        return false;
    }

    return true;
}

bool QSharedMemoryPrivate::detach()
{
    // detach from the memory segment
    if (-1 == shmdt(memory)) {
        const QLatin1String function("QSharedMemory::detach");
        switch (errno) {
        case EINVAL:
            errorString = QSharedMemory::tr("%1: not attached").arg(function);
            error = QSharedMemory::NotFound;
            break;
        default:
            setErrorString(function);
        }
        return false;
    }
    memory = 0;
    size = 0;

    // Get the number of current attachments
    int id = shmget(unix_key, 0, 0400);
    cleanHandle();

    struct shmid_ds shmid_ds;
    if (0 != shmctl(id, IPC_STAT, &shmid_ds)) {
        switch (errno) {
        case EINVAL:
            return true;
        default:
            return false;
        }
    }
    // If there are no attachments then remove it.
    if (shmid_ds.shm_nattch == 0) {
        // mark for removal
        if (-1 == shmctl(id, IPC_RMID, &shmid_ds)) {
            setErrorString(QLatin1String("QSharedMemory::remove"));
            switch (errno) {
            case EINVAL:
                return true;
            default:
                return false;
            }
        }

        // remove file
        if (!QFile::remove(nativeKey))
            return false;
    }
    return true;
}


QT_END_NAMESPACE

#endif // QT_NO_SHAREDMEMORY

#endif // QT_POSIX_IPC
