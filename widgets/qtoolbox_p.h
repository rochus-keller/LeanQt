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

#ifndef QTOOLBOX_P_H
#define QTOOLBOX_P_H

#include "qtoolbox.h"
#include "qframe_p.h"
#include <qscrollarea.h>
#include <qlayout.h>

QT_BEGIN_NAMESPACE

class QToolBoxButton;

class QToolBoxPrivate : public QFramePrivate
{
    Q_DECLARE_PUBLIC(QToolBox)
public:
    struct Page
    {
        QToolBoxButton *button;
        QScrollArea *sv;
        QWidget *widget;

        void setText(const QString &text);
        void setIcon(const QIcon &is);
#ifndef QT_NO_TOOLTIP
        void setToolTip(const QString &tip);
        QString toolTip() const;
#endif
        QString text() const;
        QIcon icon() const;

        inline bool operator==(const Page& other) const
        {
            return widget == other.widget;
        }
    };
    typedef QList<Page> PageList;

    inline QToolBoxPrivate()
        : currentPage(0)
    {
    }
    void _q_buttonClicked();
    void _q_widgetDestroyed(QObject*);

    const Page *page(const QObject *widget) const;
    const Page *page(int index) const;
    Page *page(int index);

    void updateTabs();
    void relayout();

    PageList pageList;
    QVBoxLayout *layout;
    Page *currentPage;
};


QT_END_NAMESPACE

#endif // QTOOLBOX_H
