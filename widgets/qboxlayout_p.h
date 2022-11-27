#ifndef QBOXLAYOUT_P_H
#define QBOXLAYOUT_P_H
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

#include "qboxlayout.h"
#include "qlayout_p.h"
#include "qlayoutengine_p.h"
#include "qwidget.h"

QT_BEGIN_NAMESPACE

struct QBoxLayoutItem
{
    QBoxLayoutItem(QLayoutItem *it, int stretch_ = 0)
        : item(it), stretch(stretch_), magic(false) { }
    ~QBoxLayoutItem() { delete item; }

    int hfw(int w) {
        if (item->hasHeightForWidth()) {
            return item->heightForWidth(w);
        } else {
            return item->sizeHint().height();
        }
    }
    int mhfw(int w) {
        if (item->hasHeightForWidth()) {
            return item->heightForWidth(w);
        } else {
            return item->minimumSize().height();
        }
    }
    int hStretch() {
        if (stretch == 0 && item->widget()) {
            return item->widget()->sizePolicy().horizontalStretch();
        } else {
            return stretch;
        }
    }
    int vStretch() {
        if (stretch == 0 && item->widget()) {
            return item->widget()->sizePolicy().verticalStretch();
        } else {
            return stretch;
        }
    }

    QLayoutItem *item;
    int stretch;
    bool magic;
};

class QBoxLayoutPrivate : public QLayoutPrivate
{
    Q_DECLARE_PUBLIC(QBoxLayout)
public:
    QBoxLayoutPrivate() : hfwWidth(-1), dirty(true), spacing(-1) { }
    ~QBoxLayoutPrivate();

    void setDirty() {
        geomArray.clear();
        hfwWidth = -1;
        hfwHeight = -1;
        dirty = true;
    }

    QList<QBoxLayoutItem *> list;
    QVector<QLayoutStruct> geomArray;
    int hfwWidth;
    int hfwHeight;
    int hfwMinHeight;
    QSize sizeHint;
    QSize minSize;
    QSize maxSize;
    int leftMargin, topMargin, rightMargin, bottomMargin;
    Qt::Orientations expanding;
    uint hasHfw : 1;
    uint dirty : 1;
    QBoxLayout::Direction dir;
    int spacing;

    inline void deleteAll() { while (!list.isEmpty()) delete list.takeFirst(); }

    void setupGeom();
    void calcHfw(int);

    void effectiveMargins(int *left, int *top, int *right, int *bottom) const;
    QLayoutItem* replaceAt(int index, QLayoutItem*) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif

