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

#ifndef QDATAWIDGETMAPPER_P_H
#define QDATAWIDGETMAPPER_P_H

#include "qdatawidgetmapper.h"
#include "qabstractitemmodel.h"
#include "qitemdelegate.h"
#include "qmetaobject.h"
#include "qwidget.h"
#include "private/qobject_p.h"
#include "private/qabstractitemmodel_p.h"

#include <iterator>

#ifndef QT_NO_DATAWIDGETMAPPER

QT_BEGIN_NAMESPACE

class QDataWidgetMapperPrivate: public QObjectPrivate
{
public:
    Q_DECLARE_PUBLIC(QDataWidgetMapper)

    QDataWidgetMapperPrivate()
        : model(QAbstractItemModelPrivate::staticEmptyModel()), delegate(0),
          orientation(Qt::Horizontal), submitPolicy(QDataWidgetMapper::AutoSubmit)
    {
    }

    QAbstractItemModel *model;
    QAbstractItemDelegate *delegate;
    Qt::Orientation orientation;
    QDataWidgetMapper::SubmitPolicy submitPolicy;
    QPersistentModelIndex rootIndex;
    QPersistentModelIndex currentTopLeft;

    inline int itemCount()
    {
        return orientation == Qt::Horizontal
            ? model->rowCount(rootIndex)
            : model->columnCount(rootIndex);
    }

    inline int currentIdx() const
    {
        return orientation == Qt::Horizontal ? currentTopLeft.row() : currentTopLeft.column();
    }

    inline QModelIndex indexAt(int itemPos)
    {
        return orientation == Qt::Horizontal
            ? model->index(currentIdx(), itemPos, rootIndex)
            : model->index(itemPos, currentIdx(), rootIndex);
    }

    inline void flipEventFilters(QAbstractItemDelegate *oldDelegate,
                                 QAbstractItemDelegate *newDelegate)
    {
        for (QList<WidgetMapper>::const_iterator it = widgetMap.cbegin(), end = widgetMap.cend(); it != end; ++it) {
            QWidget *w = it->widget;
            if (!w)
                continue;
            w->removeEventFilter(oldDelegate);
            w->installEventFilter(newDelegate);
        }
    }

    void populate();

    // private slots
    void _q_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &);
    void _q_commitData(QWidget *);
    void _q_closeEditor(QWidget *, QAbstractItemDelegate::EndEditHint);
    void _q_modelDestroyed();

    struct WidgetMapper
    {
        inline WidgetMapper(QWidget *w = 0, int c = 0, const QModelIndex &i = QModelIndex())
            : widget(w), section(c), currentIndex(i) {}
        inline WidgetMapper(QWidget *w, int c, const QModelIndex &i, const QByteArray &p)
            : widget(w), section(c), currentIndex(i), property(p) {}

        QPointer<QWidget> widget;
        int section;
        QPersistentModelIndex currentIndex;
        QByteArray property;
    };

    void populate(WidgetMapper &m);
    int findWidget(QWidget *w) const;

    bool commit(const WidgetMapper &m);

    QList<WidgetMapper> widgetMap;
};


QT_END_NAMESPACE

#endif // QT_NO_DATAWIDGETMAPPER
#endif

