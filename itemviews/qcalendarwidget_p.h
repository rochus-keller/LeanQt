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

#ifndef QCALENDARWIDGET_P_H
#define QCALENDARWIDGET_P_H

#include "qcalendarwidget.h"
#include <private/qwidget_p.h>

QT_BEGIN_NAMESPACE

class QCalendarModel;
class QCalendarView;
class QCalendarDelegate;
class QItemSelectionModel;
class QCalendarTextNavigator;
class QToolButton;
class QCalToolButton;
class QMenu;
class QSpinBox;
class QSpacerItem;

class QCalendarWidgetPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QCalendarWidget)
public:
    QCalendarWidgetPrivate();

    void showMonth(int year, int month);
    void update();
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

    void _q_slotShowDate(const QDate &date);
    void _q_slotChangeDate(const QDate &date);
    void _q_slotChangeDate(const QDate &date, bool changeMonth);
    void _q_editingFinished();
    void _q_monthChanged(QAction*);
    void _q_prevMonthClicked();
    void _q_nextMonthClicked();
    void _q_yearEditingFinished();
    void _q_yearClicked();

    void createNavigationBar(QWidget *widget);
    void updateButtonIcons();
    void updateMonthMenu();
    void updateMonthMenuNames();
    void updateNavigationBar();
    void updateCurrentPage(const QDate &newDate);
    inline QDate getCurrentDate();
    void setNavigatorEnabled(bool enable);

    QCalendarModel *m_model;
    QCalendarView *m_view;
    QCalendarDelegate *m_delegate;
    QItemSelectionModel *m_selection;
    QCalendarTextNavigator *m_navigator;
    bool m_dateEditEnabled;

    QToolButton *nextMonth;
    QToolButton *prevMonth;
    QCalToolButton *monthButton;
    QMenu *monthMenu;
    QMap<int, QAction *> monthToAction;
    QCalToolButton *yearButton;
    QSpinBox *yearEdit;
    QWidget *navBarBackground;
    QSpacerItem *spaceHolder;

    bool navBarVisible;
    mutable QSize cachedSizeHint;
    Qt::FocusPolicy oldFocusPolicy;
};

QT_END_NAMESPACE

#endif // QCALENDARWIDGET_H

