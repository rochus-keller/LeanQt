#ifndef QRUBBERBAND_P_H
#define QRUBBERBAND_P_H

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

#include "qrubberband.h"
#include <private/qwidget_p.h>
#include "qstyle.h"
#include "qstyleoption.h"

QT_BEGIN_NAMESPACE

//### a rubberband window type would be a more elegant solution
#define RUBBERBAND_WINDOW_TYPE Qt::ToolTip

class QRubberBandPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QRubberBand)
public:
    QRect rect;
    QRubberBand::Shape shape;
    QRegion clipping;
    void updateMask();
};





QT_END_NAMESPACE

#endif // QRUBBERBAND_H
