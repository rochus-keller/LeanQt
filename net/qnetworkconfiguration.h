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

#ifndef QNETWORKCONFIGURATION_H
#define QNETWORKCONFIGURATION_H

# include <QtCore/qglobal.h>

#include <QtCore/qshareddata.h>
#include <QtCore/qstring.h>
#include <QtCore/qlist.h>
#include <QtCore/qmetatype.h>

#ifndef QT_NO_BEARERMANAGEMENT

QT_BEGIN_NAMESPACE

class QNetworkConfigurationPrivate;
class Q_NETWORK_EXPORT QNetworkConfiguration
{
public:
    QNetworkConfiguration();
    QNetworkConfiguration(const QNetworkConfiguration& other);
#ifdef Q_COMPILER_RVALUE_REFS
    QNetworkConfiguration &operator=(QNetworkConfiguration &&other) Q_DECL_NOTHROW { swap(other); return *this; }
#endif
    QNetworkConfiguration &operator=(const QNetworkConfiguration &other);
    ~QNetworkConfiguration();

    void swap(QNetworkConfiguration &other) Q_DECL_NOTHROW { qSwap(d, other.d); }

    bool operator==(const QNetworkConfiguration &other) const;
    inline bool operator!=(const QNetworkConfiguration &other) const
    { return !operator==(other); }

    enum Type {
        InternetAccessPoint = 0,
        ServiceNetwork,
        UserChoice,
        Invalid
    };

    enum Purpose {
        UnknownPurpose = 0,
        PublicPurpose,
        PrivatePurpose,
        ServiceSpecificPurpose
    };

    enum StateFlag {
        Undefined        = 0x0000001,
        Defined          = 0x0000002,
        Discovered       = 0x0000006,
        Active           = 0x000000e
    };
    Q_DECLARE_FLAGS(StateFlags, StateFlag)

    enum BearerType {
        BearerUnknown,
        BearerEthernet,
        BearerWLAN,
        Bearer2G,
        BearerCDMA2000,
        BearerWCDMA,
        BearerHSPA,
        BearerBluetooth,
        BearerWiMAX,
        BearerEVDO,
        BearerLTE,
        Bearer3G,
        Bearer4G
    };

    StateFlags state() const;
    Type type() const;
    Purpose purpose() const;

    BearerType bearerType() const;
    BearerType bearerTypeFamily() const;
    QString bearerTypeName() const;

    QString identifier() const;
    bool isRoamingAvailable() const;
    QList<QNetworkConfiguration> children() const;

    QString name() const;
    bool isValid() const;

private:
    friend class QNetworkConfigurationPrivate;
    friend class QNetworkConfigurationManager;
    friend class QNetworkConfigurationManagerPrivate;
    friend class QNetworkSessionPrivate;
    QExplicitlySharedDataPointer<QNetworkConfigurationPrivate> d;
};

Q_DECLARE_SHARED(QNetworkConfiguration)

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QNetworkConfiguration)
#endif

#endif // QNETWORKCONFIGURATION_H
