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

#ifndef QFONTCOMBOBOX_P_H
#define QFONTCOMBOBOX_P_H

#include "qfontcombobox.h"
#include <private/qcombobox_p.h>

#ifndef QT_NO_FONTCOMBOBOX

QT_BEGIN_NAMESPACE

class QFontComboBoxPrivate : public QComboBoxPrivate
{
public:
    inline QFontComboBoxPrivate() { filters = QFontComboBox::AllFonts; }

    QFontComboBox::FontFilters filters;
    QFont currentFont;

    void _q_updateModel();
    void _q_currentChanged(const QString &);

    Q_DECLARE_PUBLIC(QFontComboBox)
};


QT_END_NAMESPACE

#endif // QT_NO_FONTCOMBOBOX
#endif
