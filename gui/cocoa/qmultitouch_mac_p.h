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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#ifndef QMULTITOUCH_MAC_P_H
#define QMULTITOUCH_MAC_P_H

#include <QtCore/qglobal.h>

#import <Cocoa/Cocoa.h>

#include <qpa/qwindowsysteminterface.h>
#include <qhash.h>
#include <QVariant>

QT_BEGIN_NAMESPACE

class QCocoaTouch
{
    public:
        static QList<QWindowSystemInterface::TouchPoint> getCurrentTouchPointList(NSEvent *event, bool acceptSingleTouch);
        static void setMouseInDraggingState(bool inDraggingState);

    private:
        static QHash<qint64, QCocoaTouch*> _currentTouches;
        static QPointF _screenReferencePos;
        static QPointF _trackpadReferencePos;
        static int _idAssignmentCount;
        static int _touchCount;
        static bool _updateInternalStateOnly;

        QWindowSystemInterface::TouchPoint _touchPoint;
        qint64 _identity;

        QCocoaTouch(NSTouch *nstouch);
        ~QCocoaTouch();

        void updateTouchData(NSTouch *nstouch, NSTouchPhase phase);
        static QCocoaTouch *findQCocoaTouch(NSTouch *nstouch);
        static Qt::TouchPointState toTouchPointState(NSTouchPhase nsState);
};

QT_END_NAMESPACE

#endif // QMULTITOUCH_MAC_P_H

