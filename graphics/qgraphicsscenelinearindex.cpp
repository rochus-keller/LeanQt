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

/*!
    \class QGraphicsSceneLinearIndex
    \brief The QGraphicsSceneLinearIndex class provides an implementation of
    a linear indexing algorithm for discovering items in QGraphicsScene.
    \since 4.6
    \ingroup graphicsview-api
    \internal

    QGraphicsSceneLinearIndex index is default linear implementation to discover items.
    It basically store all items in a list and return them to the scene.

    \sa QGraphicsScene, QGraphicsView, QGraphicsSceneIndex, QGraphicsSceneBspTreeIndex
*/

#include <private/qgraphicsscenelinearindex_p.h>

/*!
    \fn QGraphicsSceneLinearIndex::QGraphicsSceneLinearIndex(QGraphicsScene *scene = 0):

    Construct a linear index for the given \a scene.
*/

/*!
    \fn QList<QGraphicsItem *> QGraphicsSceneLinearIndex::items(Qt::SortOrder order = Qt::DescendingOrder) const;

    Return all items in the index and sort them using \a order.
*/


/*!
    \fn virtual QList<QGraphicsItem *> QGraphicsSceneLinearIndex::estimateItems(const QRectF &rect, Qt::SortOrder order) const

    Returns an estimation visible items that are either inside or
    intersect with the specified \a rect and return a list sorted using \a order.
*/

/*!
    \fn void QGraphicsSceneLinearIndex::clear()
    \internal
    Clear the all the BSP index.
*/

/*!
    \fn virtual void QGraphicsSceneLinearIndex::addItem(QGraphicsItem *item)

    Add the \a item into the index.
*/

/*!
    \fn virtual void QGraphicsSceneLinearIndex::removeItem(QGraphicsItem *item)

    Add the \a item from the index.
*/

//#include "moc_qgraphicsscenelinearindex_p.cpp"
