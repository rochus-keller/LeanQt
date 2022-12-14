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

#include <qpa/qplatformintegrationfactory_p.h>
#include <qpa/qplatformintegrationplugin.h>
#include "private/qfactoryloader_p.h"
#include "qmutex.h"
#include "qdir.h"

#include "qguiapplication.h"
#include "qdebug.h"

#if defined(Q_OS_LINUX)
#include <xcb/qxcbintegration.h>
#elif defined(Q_OS_WIN)
#include <windows/qwindowsgdiintegration.h>
#elif defined(Q_OS_MAC)
#include <cocoa/qcocoaintegrationfactory.h>
#endif

QT_BEGIN_NAMESPACE

#ifndef QT_NO_PLUGINS
Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, loader,
    (QPlatformIntegrationFactoryInterface_iid, QLatin1String("/platforms"), Qt::CaseInsensitive))
Q_GLOBAL_STATIC_WITH_ARGS(QFactoryLoader, directLoader,
                          (QPlatformIntegrationFactoryInterface_iid, QLatin1String(""), Qt::CaseInsensitive))

static inline QPlatformIntegration *loadIntegration(QFactoryLoader *loader, const QString &key, const QStringList &parameters, int &argc, char ** argv)
{
    const int index = loader->indexOf(key);
    if (index != -1) {
        if (QPlatformIntegrationPlugin *factory = qobject_cast<QPlatformIntegrationPlugin *>(loader->instance(index)))
            if (QPlatformIntegration *result = factory->create(key, parameters, argc, argv))
                return result;
    }
    return 0;
}

#endif // !QT_NO_LIBRARY

QPlatformIntegration *QPlatformIntegrationFactory::create(const QString &platform, const QStringList &paramList, int &argc, char **argv, const QString &platformPluginPath)
{
#ifndef QT_NO_PLUGINS
    // Try loading the plugin from platformPluginPath first:
    if (!platformPluginPath.isEmpty()) {
        QCoreApplication::addLibraryPath(platformPluginPath);
        if (QPlatformIntegration *ret = loadIntegration(directLoader(), platform, paramList, argc, argv))
            return ret;
    }
    if (QPlatformIntegration *ret = loadIntegration(loader(), platform, paramList, argc, argv))
        return ret;
#else
    Q_UNUSED(platform);
    Q_UNUSED(paramList);
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    Q_UNUSED(platformPluginPath);
#endif
#if defined(Q_OS_LINUX)
    return new QXcbIntegration(paramList, argc, argv);
#elif defined(Q_OS_WIN)
    return new QWindowsGdiIntegration(paramList);
#elif defined(Q_OS_MAC)
    return QCocoaIntegrationFactory::create(paramList);
#else
    return 0;
#endif
}

/*!
    Returns the list of valid keys, i.e. the keys this factory can
    create styles for.

    \sa create()
*/

QStringList QPlatformIntegrationFactory::keys(const QString &platformPluginPath)
{
    QStringList list;
#if defined(Q_OS_LINUX)
    list << "xcb";
#elif defined(Q_OS_WIN)
    list << "windows";
#elif defined(Q_OS_MAC)
    list << "cocoa";
#endif
#ifndef QT_NO_PLUGINS
    if (!platformPluginPath.isEmpty()) {
        QCoreApplication::addLibraryPath(platformPluginPath);
        list = directLoader()->keyMap().values();
        if (!list.isEmpty()) {
            const QString postFix = QStringLiteral(" (from ")
                                    + QDir::toNativeSeparators(platformPluginPath)
                                    + QLatin1Char(')');
            const QStringList::iterator end = list.end();
            for (QStringList::iterator it = list.begin(); it != end; ++it)
                (*it).append(postFix);
        }
    }
    list.append(loader()->keyMap().values());
#endif
    return list;
}

QT_END_NAMESPACE

