/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2015 Klaralvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author David Faure <david.faure@kdab.com>
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
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

#ifndef QMIMEDATABASE_H
#define QMIMEDATABASE_H

#include <QtCore/qmimetype.h>

#ifndef QT_NO_MIMETYPE

#include <QtCore/qstringlist.h>

QT_BEGIN_NAMESPACE

class QByteArray;
class QFileInfo;
class QIODevice;
class QUrl;

class QMimeDatabasePrivate;
class QMimeMagicRulesMap;

class Q_CORE_EXPORT QMimeDatabase
{
    Q_DISABLE_COPY(QMimeDatabase)

public:
    QMimeDatabase();
    ~QMimeDatabase();

    QMimeType mimeTypeForName(const QString &nameOrAlias) const;

    enum MatchMode {
        MatchDefault = 0x0,
        MatchExtension = 0x1,
        MatchContent = 0x2
    };

    QMimeType mimeTypeForFile(const QString &fileName, MatchMode mode = MatchDefault) const;
#ifndef QT_NO_FILEENGINE
    QMimeType mimeTypeForFile(const QFileInfo &fileInfo, MatchMode mode = MatchDefault) const;
#endif
    QList<QMimeType> mimeTypesForFileName(const QString &fileName) const;

    QMimeType mimeTypeForData(const QByteArray &data) const;
    QMimeType mimeTypeForData(QIODevice *device) const;

#ifndef QT_NO_URL_VARIANT
    QMimeType mimeTypeForUrl(const QUrl &url) const;
#endif
    QMimeType mimeTypeForFileNameAndData(const QString &fileName, QIODevice *device) const;
    QMimeType mimeTypeForFileNameAndData(const QString &fileName, const QByteArray &data) const;

    QString suffixForFileName(const QString &fileName) const;

    QList<QMimeType> allMimeTypes() const;

    // Qt Creator additions
    static void addMimeTypes(const QString &fileName);
    static QString allFiltersString(QString *allFilesFilter = 0);
    static QStringList allGlobPatterns();
    static void setGlobPatternsForMimeType(const QMimeType &mimeType, const QStringList &patterns);
    static void magicRulesForMimeType(const QMimeType &mimeType, QMimeMagicRulesMap& out); // priority -> rules
    static void setMagicRulesForMimeType(const QMimeType &mimeType, const QMimeMagicRulesMap &rules); // priority -> rules
private:
    QMimeDatabasePrivate *d;
};

QT_END_NAMESPACE

#endif // QT_NO_MIMETYPE
#endif // QMIMEDATABASE_H
