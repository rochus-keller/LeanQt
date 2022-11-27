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

#ifndef QFORMLAYOUT_P_H
#define QFORMLAYOUT_P_H

#include "qformlayout.h"
#include "qlayout_p.h"
#include "qlayoutengine_p.h"

QT_BEGIN_NAMESPACE

// Fixed column matrix, stores items as [i11, i12, i21, i22...],
// with FORTRAN-style index operator(r, c).
template <class T, int NumColumns>
class FixedColumnMatrix {
public:
    typedef QVector<T> Storage;

    FixedColumnMatrix() { }

    void clear() { m_storage.clear(); }

    const T &operator()(int r, int c) const { return m_storage[r * NumColumns + c]; }
    T &operator()(int r, int c) { return m_storage[r * NumColumns + c]; }

    int rowCount() const { return m_storage.size() / NumColumns; }
    void addRow(const T &value);
    void insertRow(int r, const T &value);
    void removeRow(int r);

    bool find(const T &value, int *rowPtr, int *colPtr) const ;
    int count(const T &value) const { return m_storage.count(value);  }

    // Hmmpf.. Some things are faster that way.
    const Storage &storage() const { return m_storage; }

    static void storageIndexToPosition(int idx, int *rowPtr, int *colPtr);

private:
    Storage m_storage;
};

template <class T, int NumColumns>
void FixedColumnMatrix<T, NumColumns>::addRow(const T &value)
{
    for (int i = 0; i < NumColumns; ++i)
        m_storage.append(value);
}

template <class T, int NumColumns>
void FixedColumnMatrix<T, NumColumns>::insertRow(int r, const T &value)
{
    typename Storage::iterator it = m_storage.begin();
    it += r * NumColumns;
    m_storage.insert(it, NumColumns, value);
}

template <class T, int NumColumns>
void FixedColumnMatrix<T, NumColumns>::removeRow(int r)
{
    m_storage.remove(r * NumColumns, NumColumns);
}

template <class T, int NumColumns>
bool FixedColumnMatrix<T, NumColumns>::find(const T &value, int *rowPtr, int *colPtr) const
{
    const int idx = m_storage.indexOf(value);
    if (idx == -1)
        return false;
    storageIndexToPosition(idx, rowPtr, colPtr);
    return true;
}

template <class T, int NumColumns>
void FixedColumnMatrix<T, NumColumns>::storageIndexToPosition(int idx, int *rowPtr, int *colPtr)
{
    *rowPtr = idx / NumColumns;
    *colPtr = idx % NumColumns;
}

class QFormLayoutItem;

enum { ColumnCount = 2 };

class QFormLayoutPrivate : public QLayoutPrivate
{
    Q_DECLARE_PUBLIC(QFormLayout)

public:
    typedef FixedColumnMatrix<QFormLayoutItem *, ColumnCount> ItemMatrix;

    QFormLayoutPrivate();
    ~QFormLayoutPrivate() { }

    int insertRow(int row);
    void insertRows(int row, int count);
    bool setItem(int row, QFormLayout::ItemRole role, QLayoutItem *item);
    void setLayout(int row, QFormLayout::ItemRole role, QLayout *layout);
    void setWidget(int row, QFormLayout::ItemRole role, QWidget *widget);

    void arrangeWidgets(const QVector<QLayoutStruct>& layouts, QRect &rect);

    void updateSizes();

    void setupVerticalLayoutData(int width);
    void setupHorizontalLayoutData(int width);

    QStyle* getStyle() const;

    inline bool haveHfwCached(int width) const
    {
        return (hfw_width == width) || (width == sh_width && hfw_sh_height >= 0);
    }

    void recalcHFW(int w);
    void setupHfwLayoutData();

    uint fieldGrowthPolicy : 8;
    uint rowWrapPolicy : 8;
    uint has_hfw : 2;
    uint dirty : 2; // have we laid out yet?
    uint sizesDirty : 2; // have we (not) gathered layout item sizes?
    uint expandVertical : 1; // Do we expand vertically?
    uint expandHorizontal : 1; // Do we expand horizonally?
    Qt::Alignment labelAlignment;
    Qt::Alignment formAlignment;

    ItemMatrix m_matrix;
    QList<QFormLayoutItem *> m_things;

    int layoutWidth;    // the last width that we called setupVerticalLayoutData on (for vLayouts)

    int hfw_width;  // the last width we calculated HFW for
    int hfw_height; // what that height was
    int hfw_minheight;  // what that minheight was

    int hfw_sh_height;  // the hfw for sh_width
    int hfw_sh_minheight;   // the minhfw for sh_width

    int min_width;  // the width that gets turned into minSize (from updateSizes)
    int sh_width;   // the width that gets turned into prefSize (from updateSizes)
    int thresh_width; // the width that we start splitting label/field pairs at (from updateSizes)
    QSize minSize;
    QSize prefSize;
    int formMaxWidth;
    void calcSizeHints();

    QVector<QLayoutStruct> vLayouts; // set by setupVerticalLayoutData;
    int vLayoutCount;               // Number of rows we calculated in setupVerticalLayoutData
    int maxLabelWidth;              // the label width we calculated in setupVerticalLayoutData

    QVector<QLayoutStruct> hfwLayouts;

    int hSpacing;
    int vSpacing;
    QLayoutItem* replaceAt(int index, QLayoutItem*) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif
