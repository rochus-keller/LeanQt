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

#ifndef QGRAPHICSSCENELINEARINDEX_H
#define QGRAPHICSSCENELINEARINDEX_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>

#if !defined(QT_NO_GRAPHICSVIEW)

#include <QtCore/qrect.h>
#include <QtCore/qlist.h>
#include <QtWidgets/qgraphicsitem.h>
#include <private/qgraphicssceneindex_p.h>

QT_BEGIN_NAMESPACE


class Q_AUTOTEST_EXPORT QGraphicsSceneLinearIndex : public QGraphicsSceneIndex
{
    Q_OBJECT

public:
    QGraphicsSceneLinearIndex(QGraphicsScene *scene = 0) : QGraphicsSceneIndex(scene), m_numSortedElements(0)
    { }

    QList<QGraphicsItem *> items(Qt::SortOrder order = Qt::DescendingOrder) const Q_DECL_OVERRIDE
    { Q_UNUSED(order); return m_items; }

    virtual QList<QGraphicsItem *> estimateItems(const QRectF &rect, Qt::SortOrder order) const Q_DECL_OVERRIDE
    {
        Q_UNUSED(rect);
        Q_UNUSED(order);
        return m_items;
    }

protected :
    virtual void clear() Q_DECL_OVERRIDE
    {
        m_items.clear();
        m_numSortedElements = 0;
    }

    virtual void addItem(QGraphicsItem *item) Q_DECL_OVERRIDE
    { m_items << item; }

    virtual void removeItem(QGraphicsItem *item) Q_DECL_OVERRIDE
    {
        // Sort m_items if needed
        if (m_numSortedElements < m_items.size())
        {
            std::sort(m_items.begin() + m_numSortedElements, m_items.end() );
            std::inplace_merge(m_items.begin(), m_items.begin() + m_numSortedElements, m_items.end());
            m_numSortedElements = m_items.size();
        }

        QList<QGraphicsItem*>::iterator element = std::lower_bound(m_items.begin(), m_items.end(), item);
        if (element != m_items.end() && *element == item)
        {
            m_items.erase(element);
            --m_numSortedElements;
        }
    }

private:
    QList<QGraphicsItem*> m_items;
    int m_numSortedElements;
};

#endif // QT_NO_GRAPHICSVIEW

QT_END_NAMESPACE

#endif // QGRAPHICSSCENELINEARINDEX_H
