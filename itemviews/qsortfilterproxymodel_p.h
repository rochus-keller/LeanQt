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

#ifndef QSORTFILTERPROXYMODEL_P_H
#define QSORTFILTERPROXYMODEL_P_H

#include <private/qabstractitemmodel_p.h>
#include <private/qabstractproxymodel_p.h>
#include "qsortfilterproxymodel.h"

#ifndef QT_NO_SORTFILTERPROXYMODEL

QT_BEGIN_NAMESPACE

typedef QList<QPair<QModelIndex, QPersistentModelIndex> > QModelIndexPairList;

//this struct is used to store what are the rows that are removed
//between a call to rowsAboutToBeRemoved and rowsRemoved
//it avoids readding rows to the mapping that are currently being removed
struct QRowsRemoval
{
    QRowsRemoval(const QModelIndex &parent_source, int start, int end) : parent_source(parent_source), start(start), end(end)
    {
    }

    QRowsRemoval() : start(-1), end(-1)
    {
    }

    bool contains(QModelIndex parent, int row)
    {
        do {
            if (parent == parent_source)
                return row >= start && row <= end;
            row = parent.row();
            parent = parent.parent();
        } while (row >= 0);
        return false;
    }
private:
    QModelIndex parent_source;
    int start;
    int end;
};

class QSortFilterProxyModelPrivate : public QAbstractProxyModelPrivate
{
    Q_DECLARE_PUBLIC(QSortFilterProxyModel)

public:
    struct Mapping {
        QVector<int> source_rows;
        QVector<int> source_columns;
        QVector<int> proxy_rows;
        QVector<int> proxy_columns;
        QVector<QModelIndex> mapped_children;
        QHash<QModelIndex, Mapping *>::const_iterator map_iter;
    };

    mutable QHash<QModelIndex, Mapping*> source_index_mapping;

    int source_sort_column;
    int proxy_sort_column;
    Qt::SortOrder sort_order;
    Qt::CaseSensitivity sort_casesensitivity;
    int sort_role;
    bool sort_localeaware;

    int filter_column;
    QRegExp filter_regexp;
    int filter_role;

    bool dynamic_sortfilter;
    QRowsRemoval itemsBeingRemoved;

    QModelIndexPairList saved_persistent_indexes;

    QHash<QModelIndex, Mapping *>::const_iterator create_mapping(
        const QModelIndex &source_parent) const;
    QModelIndex proxy_to_source(const QModelIndex &proxyIndex) const;
    QModelIndex source_to_proxy(const QModelIndex &sourceIndex) const;
    bool can_create_mapping(const QModelIndex &source_parent) const;

    void remove_from_mapping(const QModelIndex &source_parent);

    inline QHash<QModelIndex, Mapping *>::const_iterator index_to_iterator(
        const QModelIndex &proxy_index) const
    {
        Q_ASSERT(proxy_index.isValid());
        Q_ASSERT(proxy_index.model() == q_func());
        const void *p = proxy_index.internalPointer();
        Q_ASSERT(p);
        QHash<QModelIndex, Mapping *>::const_iterator it =
            static_cast<const Mapping*>(p)->map_iter;
        Q_ASSERT(it != source_index_mapping.constEnd());
        Q_ASSERT(it.value());
        return it;
    }

    inline QModelIndex create_index(int row, int column,
                                    QHash<QModelIndex, Mapping*>::const_iterator it) const
    {
        return q_func()->createIndex(row, column, *it);
    }

    void _q_sourceDataChanged(const QModelIndex &source_top_left,
                              const QModelIndex &source_bottom_right,
                              const QVector<int> &roles);
    void _q_sourceHeaderDataChanged(Qt::Orientation orientation, int start, int end);

    void _q_sourceAboutToBeReset();
    void _q_sourceReset();

    void _q_sourceLayoutAboutToBeChanged(const QList<QPersistentModelIndex> &sourceParents, QAbstractItemModel::LayoutChangeHint hint);
    void _q_sourceLayoutChanged(const QList<QPersistentModelIndex> &sourceParents, QAbstractItemModel::LayoutChangeHint hint);

    void _q_sourceRowsAboutToBeInserted(const QModelIndex &source_parent,
                                        int start, int end);
    void _q_sourceRowsInserted(const QModelIndex &source_parent,
                               int start, int end);
    void _q_sourceRowsAboutToBeRemoved(const QModelIndex &source_parent,
                                       int start, int end);
    void _q_sourceRowsRemoved(const QModelIndex &source_parent,
                              int start, int end);
    void _q_sourceRowsAboutToBeMoved(const QModelIndex &sourceParent,
                                     int sourceStart, int sourceEnd,
                                     const QModelIndex &destParent, int dest);
    void _q_sourceRowsMoved(const QModelIndex &sourceParent,
                            int sourceStart, int sourceEnd,
                            const QModelIndex &destParent, int dest);
    void _q_sourceColumnsAboutToBeInserted(const QModelIndex &source_parent,
                                           int start, int end);
    void _q_sourceColumnsInserted(const QModelIndex &source_parent,
                                  int start, int end);
    void _q_sourceColumnsAboutToBeRemoved(const QModelIndex &source_parent,
                                          int start, int end);
    void _q_sourceColumnsRemoved(const QModelIndex &source_parent,
                                 int start, int end);
    void _q_sourceColumnsAboutToBeMoved(const QModelIndex &sourceParent,
                                        int sourceStart, int sourceEnd,
                                        const QModelIndex &destParent, int dest);
    void _q_sourceColumnsMoved(const QModelIndex &sourceParent,
                               int sourceStart, int sourceEnd,
                               const QModelIndex &destParent, int dest);

    void _q_clearMapping();

    void sort();
    bool update_source_sort_column();
    void sort_source_rows(QVector<int> &source_rows,
                          const QModelIndex &source_parent) const;
    QVector<QPair<int, QVector<int > > > proxy_intervals_for_source_items_to_add(
        const QVector<int> &proxy_to_source, const QVector<int> &source_items,
        const QModelIndex &source_parent, Qt::Orientation orient) const;
    QVector<QPair<int, int > > proxy_intervals_for_source_items(
        const QVector<int> &source_to_proxy, const QVector<int> &source_items) const;
    void insert_source_items(
        QVector<int> &source_to_proxy, QVector<int> &proxy_to_source,
        const QVector<int> &source_items, const QModelIndex &source_parent,
        Qt::Orientation orient, bool emit_signal = true);
    void remove_source_items(
        QVector<int> &source_to_proxy, QVector<int> &proxy_to_source,
        const QVector<int> &source_items, const QModelIndex &source_parent,
        Qt::Orientation orient, bool emit_signal = true);
    void remove_proxy_interval(
        QVector<int> &source_to_proxy, QVector<int> &proxy_to_source,
        int proxy_start, int proxy_end, const QModelIndex &proxy_parent,
        Qt::Orientation orient, bool emit_signal = true);
    void build_source_to_proxy_mapping(
        const QVector<int> &proxy_to_source, QVector<int> &source_to_proxy) const;
    void source_items_inserted(const QModelIndex &source_parent,
                               int start, int end, Qt::Orientation orient);
    void source_items_about_to_be_removed(const QModelIndex &source_parent,
                                          int start, int end, Qt::Orientation orient);
    void source_items_removed(const QModelIndex &source_parent,
                              int start, int end, Qt::Orientation orient);
    void proxy_item_range(
        const QVector<int> &source_to_proxy, const QVector<int> &source_items,
        int &proxy_low, int &proxy_high) const;

    QModelIndexPairList store_persistent_indexes();
    void update_persistent_indexes(const QModelIndexPairList &source_indexes);

    void filter_about_to_be_changed(const QModelIndex &source_parent = QModelIndex());
    void filter_changed(const QModelIndex &source_parent = QModelIndex());
    QSet<int> handle_filter_changed(
        QVector<int> &source_to_proxy, QVector<int> &proxy_to_source,
        const QModelIndex &source_parent, Qt::Orientation orient);

    void updateChildrenMapping(const QModelIndex &source_parent, Mapping *parent_mapping,
                               Qt::Orientation orient, int start, int end, int delta_item_count, bool remove);

    virtual void _q_sourceModelDestroyed() Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QT_NO_SORTFILTERPROXYMODEL

#endif // QSORTFILTERPROXYMODEL_H
