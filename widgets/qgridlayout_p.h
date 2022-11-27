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

#ifndef QGRIDLAYOUT_P_H
#define QGRIDLAYOUT_P_H

#include "qgridlayout.h"
#include "qlayoutengine_p.h"
#include "qlayout_p.h"

QT_BEGIN_NAMESPACE

class QGridBox;

struct QGridLayoutSizeTriple
{
    QSize minS;
    QSize hint;
    QSize maxS;
};

class QGridLayoutPrivate : public QLayoutPrivate
{
    Q_DECLARE_PUBLIC(QGridLayout)
public:
    QGridLayoutPrivate();

    void add(QGridBox*, int row, int col);
    void add(QGridBox*, int row1, int row2, int col1, int col2);
    QSize sizeHint(int hSpacing, int vSpacing) const;
    QSize minimumSize(int hSpacing, int vSpacing) const;
    QSize maximumSize(int hSpacing, int vSpacing) const;

    Qt::Orientations expandingDirections(int hSpacing, int vSpacing) const;

    void distribute(QRect rect, int hSpacing, int vSpacing);
    inline int numRows() const { return rr; }
    inline int numCols() const { return cc; }
    inline void expand(int rows, int cols)
        { setSize(qMax(rows, rr), qMax(cols, cc)); }
    inline void setRowStretch(int r, int s)
        { expand(r + 1, 0); rStretch[r] = s; setDirty(); }
    inline void setColStretch(int c, int s)
        { expand(0, c + 1); cStretch[c] = s; setDirty(); }
    inline int rowStretch(int r) const { return rStretch.at(r); }
    inline int colStretch(int c) const { return cStretch.at(c); }
    inline void setRowMinimumHeight(int r, int s)
        { expand(r + 1, 0); rMinHeights[r] = s; setDirty(); }
    inline void setColumnMinimumWidth(int c, int s)
        { expand(0, c + 1); cMinWidths[c] = s; setDirty(); }
    inline int rowSpacing(int r) const { return rMinHeights.at(r); }
    inline int colSpacing(int c) const { return cMinWidths.at(c); }

    inline void setReversed(bool r, bool c) { hReversed = c; vReversed = r; }
    inline bool horReversed() const { return hReversed; }
    inline bool verReversed() const { return vReversed; }
    inline void setDirty() { needRecalc = true; hfw_width = -1; }
    inline bool isDirty() const { return needRecalc; }
    bool hasHeightForWidth(int hSpacing, int vSpacing);
    int heightForWidth(int width, int hSpacing, int vSpacing);
    int minimumHeightForWidth(int width, int hSpacing, int vSpacing);

    inline void getNextPos(int &row, int &col) { row = nextR; col = nextC; }
    inline int count() const { return things.count(); }
    QRect cellRect(int row, int col) const;

    QLayoutItem *itemAt(int index) const;
    inline QLayoutItem *takeAt(int index);
    QLayoutItem* replaceAt(int index, QLayoutItem *newitem) Q_DECL_OVERRIDE;

    void getItemPosition(int index, int *row, int *column, int *rowSpan, int *columnSpan) const;
    void deleteAll();

private:
    void setNextPosAfter(int r, int c);
    void recalcHFW(int w);
    void addHfwData(QGridBox *box, int width);
    void init();
    QSize findSize(int QLayoutStruct::*, int hSpacing, int vSpacing) const;
    void addData(QGridBox *b, const QGridLayoutSizeTriple &sizes, bool r, bool c);
    void setSize(int rows, int cols);
    void setupSpacings(QVector<QLayoutStruct> &chain, QGridBox *grid[], int fixedSpacing,
                       Qt::Orientation orientation);
    void setupLayoutData(int hSpacing, int vSpacing);
    void setupHfwLayoutData();
    void effectiveMargins(int *left, int *top, int *right, int *bottom) const;

    int rr;
    int cc;
    QVector<QLayoutStruct> rowData;
    QVector<QLayoutStruct> colData;
    QVector<QLayoutStruct> *hfwData;
    QVector<int> rStretch;
    QVector<int> cStretch;
    QVector<int> rMinHeights;
    QVector<int> cMinWidths;
    QList<QGridBox *> things;

    int hfw_width;
    int hfw_height;
    int hfw_minheight;
    int nextR;
    int nextC;

    int horizontalSpacing;
    int verticalSpacing;
    int leftMargin;
    int topMargin;
    int rightMargin;
    int bottomMargin;

    uint hReversed : 1;
    uint vReversed : 1;
    uint needRecalc : 1;
    uint has_hfw : 1;
    uint addVertical : 1;
};

QT_END_NAMESPACE

#endif // QGRIDLAYOUT_H
