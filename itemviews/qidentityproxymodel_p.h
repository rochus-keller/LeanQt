/****************************************************************************
**
** Copyright (C) 2011 Klarälvdalens Datakonsult AB, a KDAB Group company, 
** 				 info@kdab.com, author Stephen Kelly <stephen.kelly@kdab.com>
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


#ifndef QIDENTITYPROXYMODEL_P_H
#define QIDENTITYPROXYMODEL_P_H

#include <private/qabstractproxymodel_p.h>
#include "qidentityproxymodel.h"

#ifndef QT_NO_IDENTITYPROXYMODEL

QT_BEGIN_NAMESPACE

class QIdentityProxyModelPrivate : public QAbstractProxyModelPrivate
{
    QIdentityProxyModelPrivate()
    {

    }

    Q_DECLARE_PUBLIC(QIdentityProxyModel)

    QList<QPersistentModelIndex> layoutChangePersistentIndexes;
    QModelIndexList proxyIndexes;

    void _q_sourceRowsAboutToBeInserted(const QModelIndex &parent, int start, int end);
    void _q_sourceRowsInserted(const QModelIndex &parent, int start, int end);
    void _q_sourceRowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    void _q_sourceRowsRemoved(const QModelIndex &parent, int start, int end);
    void _q_sourceRowsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);
    void _q_sourceRowsMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);

    void _q_sourceColumnsAboutToBeInserted(const QModelIndex &parent, int start, int end);
    void _q_sourceColumnsInserted(const QModelIndex &parent, int start, int end);
    void _q_sourceColumnsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    void _q_sourceColumnsRemoved(const QModelIndex &parent, int start, int end);
    void _q_sourceColumnsAboutToBeMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);
    void _q_sourceColumnsMoved(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destParent, int dest);

    void _q_sourceDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void _q_sourceHeaderDataChanged(Qt::Orientation orientation, int first, int last);

    void _q_sourceLayoutAboutToBeChanged(const QList<QPersistentModelIndex> &sourceParents, QAbstractItemModel::LayoutChangeHint hint);
    void _q_sourceLayoutChanged(const QList<QPersistentModelIndex> &sourceParents, QAbstractItemModel::LayoutChangeHint hint);
    void _q_sourceModelAboutToBeReset();
    void _q_sourceModelReset();

};

QT_END_NAMESPACE

#endif // QT_NO_IDENTITYPROXYMODEL

#endif // QIDENTITYPROXYMODEL_H

