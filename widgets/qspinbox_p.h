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

#ifndef QSPINBOX_P_H
#define QSPINBOX_P_H

#include "qspinbox.h"
#include <private/qabstractspinbox_p.h>

QT_BEGIN_NAMESPACE

class QSpinBoxPrivate : public QAbstractSpinBoxPrivate
{
    Q_DECLARE_PUBLIC(QSpinBox)
public:
    QSpinBoxPrivate();
    void emitSignals(EmitPolicy ep, const QVariant &) Q_DECL_OVERRIDE;

    virtual QVariant valueFromText(const QString &n) const Q_DECL_OVERRIDE;
    virtual QString textFromValue(const QVariant &n) const Q_DECL_OVERRIDE;
    QVariant validateAndInterpret(QString &input, int &pos,
                                  QValidator::State &state) const;

    inline void init() {
        Q_Q(QSpinBox);
        q->setInputMethodHints(Qt::ImhDigitsOnly);
        setLayoutItemMargins(QStyle::SE_SpinBoxLayoutItem);
    }

    int displayIntegerBase;
};

class QDoubleSpinBoxPrivate : public QAbstractSpinBoxPrivate
{
    Q_DECLARE_PUBLIC(QDoubleSpinBox)
public:
    QDoubleSpinBoxPrivate();
    void emitSignals(EmitPolicy ep, const QVariant &) Q_DECL_OVERRIDE;

    virtual QVariant valueFromText(const QString &n) const Q_DECL_OVERRIDE;
    virtual QString textFromValue(const QVariant &n) const Q_DECL_OVERRIDE;
    QVariant validateAndInterpret(QString &input, int &pos,
                                  QValidator::State &state) const;
    double round(double input) const;
    // variables
    int decimals;

    inline void init() {
        Q_Q(QDoubleSpinBox);
        q->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
    }

    // When fiddling with the decimals property, we may lose precision in these properties.
    double actualMin;
    double actualMax;
};


QT_END_NAMESPACE

#endif // QSPINBOX_H
