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

#ifndef QAUTHENTICATOR_P_H
#define QAUTHENTICATOR_P_H

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

#include <qhash.h>
#include <qbytearray.h>
#include <qstring.h>
#include <qauthenticator.h>
#include <qvariant.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_AUTHENTICATOR

class QHttpResponseHeader;
#ifdef Q_OS_WIN
class QNtlmWindowsHandles;
#endif

class Q_AUTOTEST_EXPORT QAuthenticatorPrivate
{
public:
    enum Method { None, Basic, Plain, Login, Ntlm, CramMd5, DigestMd5 };
    QAuthenticatorPrivate();
    ~QAuthenticatorPrivate();

    QString user;
    QString extractedUser;
    QString password;
    QVariantHash options;
    Method method;
    QString realm;
    QByteArray challenge;
#ifdef Q_OS_WIN
    QNtlmWindowsHandles *ntlmWindowsHandles;
#endif
    bool hasFailed; //credentials have been tried but rejected by server.

    enum Phase {
        Start,
        Phase2,
        Done,
        Invalid
    };
    Phase phase;

    // digest specific
    QByteArray cnonce;
    int nonceCount;

    // ntlm specific
    QString workstation;
    QString userDomain;

    QByteArray calculateResponse(const QByteArray &method, const QByteArray &path);

    inline static QAuthenticatorPrivate *getPrivate(QAuthenticator &auth) { return auth.d; }
    inline static const QAuthenticatorPrivate *getPrivate(const QAuthenticator &auth) { return auth.d; }

    QByteArray digestMd5Response(const QByteArray &challenge, const QByteArray &method, const QByteArray &path);
    static QHash<QByteArray, QByteArray> parseDigestAuthenticationChallenge(const QByteArray &challenge);

    void parseHttpResponse(const QList<QPair<QByteArray, QByteArray> >&, bool isProxy);
    void updateCredentials();
};

#endif

QT_END_NAMESPACE

#endif
