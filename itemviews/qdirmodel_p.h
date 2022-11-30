/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtWidgets module of the Qt Toolkit.
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

#ifndef QDIRMODEL_P_H
#define QDIRMODEL_P_H

#include "qdirmodel.h"
#include <private/qabstractitemmodel_p.h>

QT_BEGIN_NAMESPACE

class QDirModelPrivate : public QAbstractItemModelPrivate
{
    Q_DECLARE_PUBLIC(QDirModel)

public:
    struct QDirNode
    {
        QDirNode() : parent(0), populated(false), stat(false) {}
        QDirNode *parent;
        QFileInfo info;
        QIcon icon; // cache the icon
        mutable QVector<QDirNode> children;
        mutable bool populated; // have we read the children
        mutable bool stat;
    };

    QDirModelPrivate()
        : resolveSymlinks(true),
          readOnly(true),
          lazyChildCount(false),
          allowAppendChild(true),
          iconProvider(&defaultProvider),
          shouldStat(true) // ### This is set to false by QFileDialog
    { }

    void init();
    QDirNode *node(int row, QDirNode *parent) const;
    QVector<QDirNode> children(QDirNode *parent, bool stat) const;

    void _q_refresh();

    void savePersistentIndexes();
    void restorePersistentIndexes();

    QFileInfoList entryInfoList(const QString &path) const;
    QStringList entryList(const QString &path) const;

    QString name(const QModelIndex &index) const;
    QString size(const QModelIndex &index) const;
    QString type(const QModelIndex &index) const;
    QString time(const QModelIndex &index) const;

    void appendChild(QDirModelPrivate::QDirNode *parent, const QString &path) const;
    static QFileInfo resolvedInfo(QFileInfo info);

    inline QDirNode *node(const QModelIndex &index) const;
    inline void populate(QDirNode *parent) const;
    inline void clear(QDirNode *parent) const;

    void invalidate();

    mutable QDirNode root;
    bool resolveSymlinks;
    bool readOnly;
    bool lazyChildCount;
    bool allowAppendChild;

    QDir::Filters filters;
    QDir::SortFlags sort;
    QStringList nameFilters;

    QFileIconProvider *iconProvider;
    QFileIconProvider defaultProvider;

    struct SavedPersistent {
        QString path;
        int column;
        QPersistentModelIndexData *data;
        QPersistentModelIndex index;
    };
    QList<SavedPersistent> savedPersistent;
    QPersistentModelIndex toBeRefreshed;

    bool shouldStat; // use the "carefull not to stat directories" mode
};


QT_END_NAMESPACE

#endif // QDIRMODEL_H
