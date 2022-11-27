#ifndef QTABWIDGET_P_H
#define QTABWIDGET_P_H

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

#include "qtabwidget.h"
#include "private/qwidget_p.h"
#include "private/qtabbar_p.h"


QT_BEGIN_NAMESPACE

class QStackedWidget;

class QTabWidgetPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QTabWidget)

public:
    QTabWidgetPrivate();
    ~QTabWidgetPrivate();
    void updateTabBarPosition();
    void _q_showTab(int);
    void _q_removeTab(int);
    void _q_tabMoved(int from, int to);
    void init();

    QTabBar *tabs;
    QStackedWidget *stack;
    QRect panelRect;
    bool dirty;
    QTabWidget::TabPosition pos;
    QTabWidget::TabShape shape;
    int alignment;
    QWidget *leftCornerWidget;
    QWidget *rightCornerWidget;
};

QT_END_NAMESPACE

#endif // QTABWIDGET_H
