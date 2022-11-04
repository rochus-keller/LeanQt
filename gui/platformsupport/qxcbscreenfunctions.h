/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef QXCBSCREENFUNCTIONS_H
#define QXCBSCREENFUNCTIONS_H

#include <qplatformheaderhelper.h>

QT_BEGIN_NAMESPACE

class QScreen;

class QXcbScreenFunctions
{
public:
    typedef bool (*VirtualDesktopNumber)(const QScreen *screen);
    static const QByteArray virtualDesktopNumberIdentifier() { return QByteArrayLiteral("XcbVirtualDesktopNumber"); }
    static int virtualDesktopNumber(const QScreen *screen)
    {
        return QPlatformHeaderHelper::callPlatformFunction<int, VirtualDesktopNumber, const QScreen *>(virtualDesktopNumberIdentifier(), screen);
    }
};

QT_END_NAMESPACE

#endif  /*QXCBSCREENFUNCTIONS_H*/
