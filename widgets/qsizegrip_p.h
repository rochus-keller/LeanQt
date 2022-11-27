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

#ifndef QSIZEGRIP_P_H
#define QSIZEGRIP_P_H

#include "qsizegrip.h"
#include <private/qwidget_p.h>

QT_BEGIN_NAMESPACE

class QSizeGripPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QSizeGrip)
public:
    QSizeGripPrivate();
    void init();
    QPoint p;
    QRect r;
    int d;
    int dxMax;
    int dyMax;
    Qt::Corner m_corner;
    bool gotMousePress;
    QPointer<QWidget> tlw;
#ifdef Q_DEAD_CODE_FROM_QT4_MAC
    void updateMacSizer(bool hide) const;
#endif
    Qt::Corner corner() const;
    inline bool atBottom() const
    {
        return m_corner == Qt::BottomRightCorner || m_corner == Qt::BottomLeftCorner;
    }

    inline bool atLeft() const
    {
        return m_corner == Qt::BottomLeftCorner || m_corner == Qt::TopLeftCorner;
    }

    void updateTopLevelWidget();

    // This slot is invoked by QLayout when the size grip is added to
    // a layout or reparented after the tlw is shown. This re-implementation is basically
    // the same as QWidgetPrivate::_q_showIfNotHidden except that it checks
    // for Qt::WindowFullScreen and Qt::WindowMaximized as well.
    void _q_showIfNotHidden();

    bool m_platformSizeGrip;
};


QT_END_NAMESPACE

#endif // QSIZEGRIP_H
