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

#ifndef QWINDOWCONTAINER_P_H
#define QWINDOWCONTAINER_P_H

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

#include "qwindowcontainer_p.h"
#include "qwidget_p.h"
#include <QtGui/qwindow.h>
#include <QtGui/private/qguiapplication_p.h>
#include <qpa/qplatformintegration.h>
#include <QMdiSubWindow>
#include <QAbstractScrollArea>

QT_BEGIN_NAMESPACE

class QWindowContainerPrivate : public QWidgetPrivate
{
public:
    Q_DECLARE_PUBLIC(QWindowContainer)

    QWindowContainerPrivate()
        : window(0)
        , oldFocusWindow(0)
        , usesNativeWidgets(false)
    {
    }

    ~QWindowContainerPrivate() { }

    static QWindowContainerPrivate *get(QWidget *w) {
        QWindowContainer *wc = qobject_cast<QWindowContainer *>(w);
        if (wc)
            return wc->d_func();
        return 0;
    }

    void updateGeometry() {
        Q_Q(QWindowContainer);
        if (!q->isWindow() && (q->geometry().bottom() <= 0 || q->geometry().right() <= 0))
            /* Qt (e.g. QSplitter) sometimes prefer to hide a widget by *not* calling
               setVisible(false). This is often done by setting its coordinates to a sufficiently
               negative value so that its clipped outside the parent. Since a QWindow is not clipped
               to widgets in general, it needs to be dealt with as a special case.
            */
            window->setGeometry(q->geometry());
        else if (usesNativeWidgets)
            window->setGeometry(q->rect());
        else
            window->setGeometry(QRect(q->mapTo(q->window(), QPoint()), q->size()));
    }

    void updateUsesNativeWidgets()
    {
        if (usesNativeWidgets || window->parent() == 0)
            return;
        Q_Q(QWindowContainer);
        if (q->internalWinId()) {
            // Allow use native widgets if the window container is already a native widget
            usesNativeWidgets = true;
            return;
        }
        QWidget *p = q->parentWidget();
        while (p) {
            if (
#ifndef QT_NO_MDIAREA
                qobject_cast<QMdiSubWindow *>(p) != 0 ||
#endif
                qobject_cast<QAbstractScrollArea *>(p) != 0) {
                q->winId();
                usesNativeWidgets = true;
                break;
            }
            p = p->parentWidget();
        }
    }

    void markParentChain() {
        Q_Q(QWindowContainer);
        QWidget *p = q;
        while (p) {
            QWidgetPrivate *d = static_cast<QWidgetPrivate *>(QWidgetPrivate::get(p));
            d->createExtra();
            d->extra->hasWindowContainer = true;
            p = p->parentWidget();
        }
    }

    bool isStillAnOrphan() const {
        return window->parent() == &fakeParent;
    }

    QPointer<QWindow> window;
    QWindow *oldFocusWindow;
    QWindow fakeParent;

    uint usesNativeWidgets : 1;
};

QT_END_NAMESPACE

#endif // QWINDOWCONTAINER_H
