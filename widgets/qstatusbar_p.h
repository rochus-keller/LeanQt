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

#ifndef QSTATUSBAR_P_H
#define QSTATUSBAR_P_H

#include "qstatusbar.h"
#include <private/qlayoutengine_p.h>
#include <private/qwidget_p.h>
#include "qlayout.h"
#include "qsizegrip.h"


QT_BEGIN_NAMESPACE

class QStatusBarPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QStatusBar)
public:
    QStatusBarPrivate() {}

    struct SBItem {
        SBItem(QWidget* widget, int stretch, bool permanent)
            : s(stretch), w(widget), p(permanent) {}
        int s;
        QWidget * w;
        bool p;
    };

    QList<SBItem *> items;
    QString tempItem;

    QBoxLayout * box;
    QTimer * timer;

#ifndef QT_NO_SIZEGRIP
    QSizeGrip * resizer;
    bool showSizeGrip;
#endif

    int savedStrut;

#ifdef Q_DEAD_CODE_FROM_QT4_MAC
    QPoint dragStart;
#endif

    int indexToLastNonPermanentWidget() const
    {
        int i = items.size() - 1;
        for (; i >= 0; --i) {
            SBItem *item = items.at(i);
            if (!(item && item->p))
                break;
        }
        return i;
    }

#ifndef QT_NO_SIZEGRIP
    void tryToShowSizeGrip()
    {
        if (!showSizeGrip)
            return;
        showSizeGrip = false;
        if (!resizer || resizer->isVisible())
            return;
        resizer->setAttribute(Qt::WA_WState_ExplicitShowHide, false);
        QMetaObject::invokeMethod(resizer, "_q_showIfNotHidden", Qt::DirectConnection);
        resizer->setAttribute(Qt::WA_WState_ExplicitShowHide, false);
    }
#endif

    QRect messageRect() const;
};


QT_END_NAMESPACE

#endif // QSTATUSBAR_H
