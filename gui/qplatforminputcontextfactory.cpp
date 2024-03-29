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

#include <qpa/qplatforminputcontextfactory_p.h>
#include <qpa/qplatforminputcontextplugin_p.h>
#include <qpa/qplatforminputcontext.h>
#include "private/qfactoryloader_p.h"

#include "qguiapplication.h"
#include "qdebug.h"
#include <stdlib.h>

#ifdef Q_OS_LINUX
#include "xcb/qcomposeplatforminputcontext.h"
#endif

QT_BEGIN_NAMESPACE

#if !defined(QT_NO_PLUGINS) && !defined(QT_NO_SETTINGS)
Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QPlatformInputContextFactoryInterface_iid, QLatin1String("/platforminputcontexts"), Qt::CaseInsensitive))
#endif

QStringList QPlatformInputContextFactory::keys()
{
#if !defined(QT_NO_PLUGINS) && !defined(QT_NO_SETTINGS)
    return loader()->keyMap().values();
#else
    return QStringList();
#endif
}

QString QPlatformInputContextFactory::requested()
{
    QByteArray env = qgetenv("QT_IM_MODULE");
    return env.isNull() ? QString() : QString::fromLocal8Bit(env);
}

QPlatformInputContext *QPlatformInputContextFactory::create(const QString& key)
{
    if (!key.isEmpty()) {
        QStringList paramList = key.split(QLatin1Char(':'));
        const QString platform = paramList.takeFirst().toLower();

        QPlatformInputContext *ic = 0;

#if !defined(QT_NO_PLUGINS) && !defined(QT_NO_SETTINGS)
        ic = qLoadPlugin1<QPlatformInputContext, QPlatformInputContextPlugin>
                                                 (loader(), platform, paramList);
#endif
        if (ic && ic->isValid())
            return ic;

        delete ic;

#ifdef Q_OS_LINUX
        if( platform == "compose" )
            return new QComposeInputContext();
#endif
    }
    return 0;
}

QPlatformInputContext *QPlatformInputContextFactory::create()
{
    return create(requested());
}

QT_END_NAMESPACE

