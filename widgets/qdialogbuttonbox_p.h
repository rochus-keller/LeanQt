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

#ifndef QDIALOGBUTTONBOX_P_H
#define QDIALOGBUTTONBOX_P_H

#include "qdialogbuttonbox.h"
#include <private/qwidget_p.h>
#include <QtWidgets/qlayout.h>

QT_BEGIN_NAMESPACE

class QDialogButtonBoxPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QDialogButtonBox)

public:
    QDialogButtonBoxPrivate(Qt::Orientation orient);

    QList<QAbstractButton *> buttonLists[QDialogButtonBox::NRoles];
    QHash<QPushButton *, QDialogButtonBox::StandardButton> standardButtonHash;

    Qt::Orientation orientation;
    QDialogButtonBox::ButtonLayout layoutPolicy;
    QBoxLayout *buttonLayout;
    bool internalRemove;
    bool center;

    void createStandardButtons(QDialogButtonBox::StandardButtons buttons);

    void layoutButtons();
    void initLayout();
    void resetLayout();
    QPushButton *createButton(QDialogButtonBox::StandardButton button, bool doLayout = true);
    void addButton(QAbstractButton *button, QDialogButtonBox::ButtonRole role, bool doLayout = true);
    void _q_handleButtonDestroyed();
    void _q_handleButtonClicked();
    void addButtonsToLayout(const QList<QAbstractButton *> &buttonList, bool reverse);
    void retranslateStrings();
};

QT_END_NAMESPACE

#endif // QDIALOGBUTTONBOX_H
