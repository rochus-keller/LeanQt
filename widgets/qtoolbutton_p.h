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

#ifndef QTOOLBUTTON_P_H
#define QTOOLBUTTON_P_H

#include "qtoolbutton.h"
#include <private/qabstractbutton_p.h>
#include <private/qaction_p.h>
#include <private/qmenu_p.h>

QT_BEGIN_NAMESPACE

class QToolButtonPrivate : public QAbstractButtonPrivate
{
    Q_DECLARE_PUBLIC(QToolButton)
public:
    void init();
#ifndef QT_NO_MENU
    void _q_buttonPressed();
    void _q_buttonReleased();
    void popupTimerDone();
    void _q_updateButtonDown();
    void _q_menuTriggered(QAction *);
#endif
    bool updateHoverControl(const QPoint &pos);
    void _q_actionTriggered();
    QStyle::SubControl newHoverControl(const QPoint &pos);
    QStyle::SubControl hoverControl;
    QRect hoverRect;
    QPointer<QAction> menuAction; //the menu set by the user (setMenu)
    QBasicTimer popupTimer;
    int delay;
    Qt::ArrowType arrowType;
    Qt::ToolButtonStyle toolButtonStyle;
    QToolButton::ToolButtonPopupMode popupMode;
    enum { NoButtonPressed=0, MenuButtonPressed=1, ToolButtonPressed=2 };
    uint buttonPressed : 2;
    uint menuButtonDown          : 1;
    uint autoRaise             : 1;
    uint repeat                : 1;
    QAction *defaultAction;
#ifndef QT_NO_MENU
    bool hasMenu() const;
    //workaround for task 177850
    QList<QAction *> actionsCopy;
#endif
};


QT_END_NAMESPACE

#endif // QTOOLBUTTON_H
