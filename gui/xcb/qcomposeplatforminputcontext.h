/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2023 Rochus Keller (me@rochus-keller.ch) for LeanQt
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

#ifndef QCOMPOSEPLATFORMINPUTCONTEXT_H
#define QCOMPOSEPLATFORMINPUTCONTEXT_H

#include <qpa/qplatforminputcontext.h>

#include <QtCore/QList>

#include "qtablegenerator.h"

QT_BEGIN_NAMESPACE

class QEvent;

class QComposeInputContext : public QPlatformInputContext
{
    Q_OBJECT

public:
    QComposeInputContext();
    ~QComposeInputContext();

    bool isValid() const Q_DECL_OVERRIDE;
    void setFocusObject(QObject *object) Q_DECL_OVERRIDE;
    void reset() Q_DECL_OVERRIDE;
    void update(Qt::InputMethodQueries) Q_DECL_OVERRIDE;
    bool filterEvent(const QEvent *event) Q_DECL_OVERRIDE;

protected:
    void clearComposeBuffer();
    bool ignoreKey(int keyval) const;
    bool composeKey(int keyval) const;
    bool checkComposeTable();
    void commitText(uint character) const;

private:
    QObject *m_focusObject;
    QVector<QComposeTableElement> m_composeTable;
    uint m_composeBuffer[QT_KEYSEQUENCE_MAX_LEN + 1];
    TableGenerator::TableState m_tableState;
    bool m_compositionTableInitialized;
};

QT_END_NAMESPACE

#endif // QCOMPOSEPLATFORMINPUTCONTEXT_H
