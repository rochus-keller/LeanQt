/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtNetwork module of the Qt Toolkit.
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

#ifndef QNETWORKCONFIGURATIONPRIVATE_H
#define QNETWORKCONFIGURATIONPRIVATE_H

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

#include "qnetworkconfiguration.h"

#include <QtCore/qshareddata.h>
#include <QtCore/qmutex.h>
#include <QtCore/qmap.h>

#ifdef Q_OS_BLACKBERRY
#include <bps/netstatus.h>
#endif

#ifndef QT_NO_BEARERMANAGEMENT
QT_BEGIN_NAMESPACE

typedef QExplicitlySharedDataPointer<QNetworkConfigurationPrivate> QNetworkConfigurationPrivatePointer;
class QNetworkConfigurationPrivate : public QSharedData
{
public:
    QNetworkConfigurationPrivate() :
        mutex(QMutex::Recursive),
        type(QNetworkConfiguration::Invalid),
        purpose(QNetworkConfiguration::UnknownPurpose),
        bearerType(QNetworkConfiguration::BearerUnknown),
#ifdef Q_OS_BLACKBERRY
        oldIpStatus(NETSTATUS_IP_STATUS_ERROR_UNKNOWN),
#endif
        isValid(false), roamingSupported(false)
    {}
    virtual ~QNetworkConfigurationPrivate()
    {
        //release pointers to member configurations
        serviceNetworkMembers.clear();
    }

    QMap<unsigned int, QNetworkConfigurationPrivatePointer> serviceNetworkMembers;

    mutable QMutex mutex;

    QString name;
    QString id;

    QNetworkConfiguration::StateFlags state;
    QNetworkConfiguration::Type type;
    QNetworkConfiguration::Purpose purpose;
    QNetworkConfiguration::BearerType bearerType;

#ifdef Q_OS_BLACKBERRY
    netstatus_ip_status_t oldIpStatus;
#endif

    bool isValid;
    bool roamingSupported;

private:
    Q_DISABLE_COPY(QNetworkConfigurationPrivate)
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QNetworkConfigurationPrivatePointer)
#endif 

#endif // QNETWORKCONFIGURATIONPRIVATE_H
