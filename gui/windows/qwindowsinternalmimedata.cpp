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

#include "qwindowsinternalmimedata.h"
#include "qwindowscontext.h"
//#include "qplatformfunctions_wince.h"
#include "qwindowsmime.h"
#include <QDebug>
/*!
    \class QWindowsInternalMimeDataBase
    \brief Base for implementations of QInternalMimeData using a IDataObject COM object.

    In clipboard handling and Drag and drop, static instances
    of QInternalMimeData implementations are kept and passed to the client.

    QInternalMimeData provides virtuals that query the formats and retrieve
    mime data on demand when the client invokes functions like QMimeData::hasHtml(),
    QMimeData::html() on the instance returned. Otherwise, expensive
    construction of a new QMimeData object containing all possible
    formats would have to be done in each call to mimeData().

    The base class introduces new virtuals to obtain and release
    the instances IDataObject from the clipboard or Drag and Drop and
    does conversion using QWindowsMime classes.

    \sa QInternalMimeData, QWindowsMime, QWindowsMimeConverter
    \internal
    \ingroup qt-lighthouse-win
*/

bool QWindowsInternalMimeData::hasFormat_sys(const QString &mime) const
{
    IDataObject *pDataObj = retrieveDataObject();
    if (!pDataObj)
        return false;

    const QWindowsMimeConverter &mc = QWindowsContext::instance()->mimeConverter();
    const bool has = mc.converterToMime(mime, pDataObj) != 0;
    releaseDataObject(pDataObj);
    qCDebug(lcQpaMime) << __FUNCTION__ <<  mime << has;
    return has;
}

QStringList QWindowsInternalMimeData::formats_sys() const
{
    IDataObject *pDataObj = retrieveDataObject();
    if (!pDataObj)
        return QStringList();

    const QWindowsMimeConverter &mc = QWindowsContext::instance()->mimeConverter();
    const QStringList fmts = mc.allMimesForFormats(pDataObj);
    releaseDataObject(pDataObj);
    qCDebug(lcQpaMime) << __FUNCTION__ <<  fmts;
    return fmts;
}

QVariant QWindowsInternalMimeData::retrieveData_sys(const QString &mimeType,
                                                        QVariant::Type type) const
{
    IDataObject *pDataObj = retrieveDataObject();
    if (!pDataObj)
        return QVariant();

    QVariant result;
    const QWindowsMimeConverter &mc = QWindowsContext::instance()->mimeConverter();
    if (const QWindowsMime *converter = mc.converterToMime(mimeType, pDataObj))
        result = converter->convertToMime(mimeType, pDataObj, type);
    releaseDataObject(pDataObj);
    if (QWindowsContext::verbose) {
        qCDebug(lcQpaMime) <<__FUNCTION__ << ' '  << mimeType << ' ' << type
            << " returns " << result.type()
            << (result.type() != QVariant::ByteArray ? result.toString() : QStringLiteral("<data>"));
    }
    return result;
}
