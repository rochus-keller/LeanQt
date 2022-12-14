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

#ifndef QPUSHBUTTON_P_H
#define QPUSHBUTTON_P_H

#include "private/qabstractbutton_p.h"
#include "qpushbutton.h"

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

QT_BEGIN_NAMESPACE

class QDialog;
class QPushButton;

class QPushButtonPrivate : public QAbstractButtonPrivate
{
    Q_DECLARE_PUBLIC(QPushButton)
public:
    enum AutoDefaultValue { Off = 0, On = 1, Auto = 2 };

    QPushButtonPrivate()
        : QAbstractButtonPrivate(QSizePolicy::PushButton), autoDefault(Auto),
          defaultButton(false), flat(false), menuOpen(false), lastAutoDefault(false) {}

    inline void init() { resetLayoutItemMargins(); }
    static QPushButtonPrivate* get(QPushButton *b) { return b->d_func(); }
#ifdef Q_DEAD_CODE_FROM_QT4_MAC
    bool hitButton(const QPoint &pos);
#endif
#ifndef QT_NO_MENU
    QPoint adjustedMenuPosition();
#endif
    void resetLayoutItemMargins();
    void _q_popupPressed();
    QDialog *dialogParent() const;

    QPointer<QMenu> menu;
    uint autoDefault : 2;
    uint defaultButton : 1;
    uint flat : 1;
    uint menuOpen : 1;
    mutable uint lastAutoDefault : 1;
};

QT_END_NAMESPACE

#endif // QPUSHBUTTON_P_H
