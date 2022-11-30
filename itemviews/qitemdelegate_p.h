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

#ifndef QITEMDELEGATE_P_H
#define QITEMDELEGATE_P_H

#include "qitemdelegate.h"
#include <private/qabstractitemdelegate_p.h>
#include <qtextlayout.h>
#include <qitemeditorfactory.h>

QT_BEGIN_NAMESPACE

class QItemDelegatePrivate : public QAbstractItemDelegatePrivate
{
    Q_DECLARE_PUBLIC(QItemDelegate)

public:
    QItemDelegatePrivate() : f(0), clipPainting(true) {}

    inline const QItemEditorFactory *editorFactory() const
        { return f ? f : QItemEditorFactory::defaultFactory(); }

    inline QIcon::Mode iconMode(QStyle::State state) const
        {
            if (!(state & QStyle::State_Enabled)) return QIcon::Disabled;
            if (state & QStyle::State_Selected) return QIcon::Selected;
            return QIcon::Normal;
        }

    inline QIcon::State iconState(QStyle::State state) const
        { return state & QStyle::State_Open ? QIcon::On : QIcon::Off; }

    inline static QString replaceNewLine(QString text)
        {
            const QChar nl = QLatin1Char('\n');
            for (int i = 0; i < text.count(); ++i)
                if (text.at(i) == nl)
                    text[i] = QChar::LineSeparator;
            return text;
        }

    QString valueToText(const QVariant &value, const QStyleOptionViewItem &option) const;

    QItemEditorFactory *f;
    bool clipPainting;

    QRect textLayoutBounds(const QStyleOptionViewItem &options) const;
    QSizeF doTextLayout(int lineWidth) const;
    mutable QTextLayout textLayout;
    mutable QTextOption textOption;

    const QWidget *widget(const QStyleOptionViewItem &option) const
    {
        return option.widget;
    }

    // ### temporary hack until we have QStandardItemDelegate
    mutable struct Icon {
        QIcon icon;
        QIcon::Mode mode;
        QIcon::State state;
    } tmp;
};


QT_END_NAMESPACE

#endif // QITEMDELEGATE_H
