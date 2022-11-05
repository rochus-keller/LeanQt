/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
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

#ifndef QWINDOWSFONTDATABASEFT_H
#define QWINDOWSFONTDATABASEFT_H

#include <qbasicfontdatabase_p.h>
#include <QtCore/QSharedPointer>
#include "qtwindows_additional.h"

QT_BEGIN_NAMESPACE

class QWindowsFontDatabaseFT : public QBasicFontDatabase
{
public:
    void populateFontDatabase() Q_DECL_OVERRIDE;
    void populateFamily(const QString &familyName) Q_DECL_OVERRIDE;
    QFontEngine *fontEngine(const QFontDef &fontDef, void *handle) Q_DECL_OVERRIDE;
    QFontEngine *fontEngine(const QByteArray &fontData, qreal pixelSize,
                            QFont::HintingPreference hintingPreference) Q_DECL_OVERRIDE;

    QStringList fallbacksForFamily(const QString &family, QFont::Style style,
                                   QFont::StyleHint styleHint,
                                   QChar::Script script) const Q_DECL_OVERRIDE;

    QString fontDir() const Q_DECL_OVERRIDE;
    QFont defaultFont() const Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE

#endif // QWINDOWSFONTDATABASEFT_H
