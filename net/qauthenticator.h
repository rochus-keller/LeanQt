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

#ifndef QAUTHENTICATOR_H
#define QAUTHENTICATOR_H

#include <QtCore/qstring.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_AUTHENTICATOR

class QAuthenticatorPrivate;
class QUrl;

class Q_NETWORK_EXPORT QAuthenticator
{
public:
    QAuthenticator();
    ~QAuthenticator();

    QAuthenticator(const QAuthenticator &other);
    QAuthenticator &operator=(const QAuthenticator &other);

    bool operator==(const QAuthenticator &other) const;
    inline bool operator!=(const QAuthenticator &other) const { return !operator==(other); }

    QString user() const;
    void setUser(const QString &user);

    QString password() const;
    void setPassword(const QString &password);

    QString realm() const;
    void setRealm(const QString &realm);

    QVariant option(const QString &opt) const;
    QVariantHash options() const;
    void setOption(const QString &opt, const QVariant &value);

    bool isNull() const;
    void detach();
private:
    friend class QAuthenticatorPrivate;
    QAuthenticatorPrivate *d;
};

#else
class QAuthenticator;
#endif // QT_NO_AUTHENTICATOR

QT_END_NAMESPACE

#endif
