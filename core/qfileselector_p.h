/***************************************************************************
**
** Copyright (C) 2013 BlackBerry Limited. All rights reserved.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QFILESELECTOR_P_H
#define QFILESELECTOR_P_H

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

#include <QtCore/QString>
#include <QtCore/QFileSelector>
#ifndef QT_NO_QOBJECT
#include <private/qobject_p.h>
#endif

QT_BEGIN_NAMESPACE

struct QFileSelectorSharedData //Not QSharedData because currently is just a global store
{
    QStringList staticSelectors;
    QStringList preloadedStatics;
};

class Q_CORE_EXPORT QFileSelectorPrivate
	: QObjectPrivate //Exported for use in other modules (like QtGui)
{
    Q_DECLARE_PUBLIC(QFileSelector)
public:
    static void updateSelectors();
    static QStringList platformSelectors();
    static void addStatics(const QStringList &); //For loading GUI statics from other Qt modules
    QFileSelectorPrivate();
    QString select(const QString &filePath) const;

    QStringList extras;
};

QT_END_NAMESPACE

#endif

