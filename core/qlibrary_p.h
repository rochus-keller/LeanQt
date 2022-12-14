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

#ifndef QLIBRARY_P_H
#define QLIBRARY_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QLibrary class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include "QtCore/qlibrary.h"
#ifndef QT_NO_QOBJECT
#include "QtCore/qplugin.h"
#include "QtCore/qpointer.h"
#endif
#include "QtCore/qstringlist.h"
#include "QtCore/qsharedpointer.h"
#ifndef QT_NO_PLUGINS
#include "QtCore/qjsonobject.h"
#include "QtCore/qjsondocument.h"
#endif
#include "QtCore/qendian.h"
#ifdef Q_OS_WIN
#  include "QtCore/qt_windows.h"
#endif

#ifndef QT_NO_LIBRARY

QT_BEGIN_NAMESPACE

bool qt_debug_component();

class QLibraryStore;
class QLibraryPrivate
{
public:

#ifdef Q_OS_WIN
    HINSTANCE
#else
    void *
#endif
    pHnd;

    enum UnloadFlag { UnloadSys, NoUnloadSys };

    QString fileName, qualifiedFileName;
    QString fullVersion;

    bool load();
#ifndef QT_NO_QOBJECT
    bool loadPlugin(); // loads and resolves instance
#endif
    bool unload(UnloadFlag flag = UnloadSys);
    void release();
    QFunctionPointer resolve(const char *);

    QLibrary::LoadHints loadHints() const
    { return QLibrary::LoadHints(loadHintsInt.load()); }
    void setLoadHints(QLibrary::LoadHints lh);

    static QLibraryPrivate *findOrCreate(const QString &fileName, const QString &version = QString(),
                                         QLibrary::LoadHints loadHints = 0);
    static QStringList suffixes_sys(const QString &fullVersion);
    static QStringList prefixes_sys();

#ifndef QT_NO_QOBJECT
    QPointer<QObject> inst;
    QtPluginInstanceFunction instance;
#endif
#ifndef QT_NO_PLUGINS
    QJsonObject metaData;
#endif

    QString errorString;

    void updatePluginState();
    bool isPlugin();

#ifndef QT_NO_PLUGINS
    static inline QJsonDocument fromRawMetaData(const char *raw) {
        static const char* prefix = "QTMETADATA  ";
        const int len1 = strlen(raw);
        const int len2 = strlen(prefix);
        if( len1 < len2 || strncmp(raw,prefix,len2) != 0 )
            return QJsonDocument();
        raw += len2;
        // the size of the embedded JSON object can be found 8 bytes into the data (see qjson_p.h),
        // but doesn't include the size of the header (8 bytes)
        QByteArray json(raw, qFromLittleEndian<uint>(*(const uint *)(raw + 8)) + 8);
        return QJsonDocument::fromBinaryData(json);
    }
#endif

private:
    explicit QLibraryPrivate(const QString &canonicalFileName, const QString &version, QLibrary::LoadHints loadHints);
    ~QLibraryPrivate();
    void mergeLoadHints(QLibrary::LoadHints loadHints);

    bool load_sys();
    bool unload_sys();
    QFunctionPointer resolve_sys(const char *);

    QAtomicInt loadHintsInt;

    /// counts how many QLibrary or QPluginLoader are attached to us, plus 1 if it's loaded
    QAtomicInt libraryRefCount;
    /// counts how many times load() or loadPlugin() were called
    QAtomicInt libraryUnloadCount;

    enum { IsAPlugin, IsNotAPlugin, MightBeAPlugin } pluginState;
    friend class QLibraryStore;
};

QT_END_NAMESPACE

#endif // QT_NO_LIBRARY

#endif // QLIBRARY_P_H
