#ifndef QCOMMANDLINKBUTTON_P_H
#define QCOMMANDLINKBUTTON_P_H

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

#include "qcommandlinkbutton.h"
#include "private/qpushbutton_p.h"

QT_BEGIN_NAMESPACE

class QCommandLinkButtonPrivate : public QPushButtonPrivate
{
    Q_DECLARE_PUBLIC(QCommandLinkButton)

public:
    QCommandLinkButtonPrivate()
        : QPushButtonPrivate(){}

    void init();
    qreal titleSize() const;
    bool usingVistaStyle() const;

    QFont titleFont() const;
    QFont descriptionFont() const;

    QRect titleRect() const;
    QRect descriptionRect() const;

    int textOffset() const;
    int descriptionOffset() const;
    int descriptionHeight(int width) const;
    QColor mergedColors(const QColor &a, const QColor &b, int value) const;

    int topMargin() const { return 10; }
    int leftMargin() const { return 7; }
    int rightMargin() const { return 4; }
    int bottomMargin() const { return 10; }

    QString description;
    QColor currentColor;
};

QT_END_NAMESPACE

#endif // QCOMMANDLINKBUTTON
