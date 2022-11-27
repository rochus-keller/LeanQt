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

#ifndef QWIDGETWINDOW_P_P_H
#define QWIDGETWINDOW_P_P_H

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

#include "private/qwindow_p.h"
#include "qwidgetwindow_p.h"
#include "qlayout.h"
#include "private/qwidget_p.h"

QT_BEGIN_NAMESPACE

class QWidgetWindowPrivate : public QWindowPrivate
{
    Q_DECLARE_PUBLIC(QWidgetWindow)
public:
    QWindow *eventReceiver() Q_DECL_OVERRIDE {
        Q_Q(QWidgetWindow);
        QWindow *w = q;
        while (w->parent() && qobject_cast<QWidgetWindow *>(w) && qobject_cast<QWidgetWindow *>(w->parent())) {
            w = w->parent();
        }
        return w;
    }

    void clearFocusObject() Q_DECL_OVERRIDE
    {
        Q_Q(QWidgetWindow);
        QWidget *widget = q->widget();
        if (widget && widget->focusWidget())
            widget->focusWidget()->clearFocus();
    }

    QRectF closestAcceptableGeometry(const QRectF &rect) const Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QWIDGETWINDOW_P_H
