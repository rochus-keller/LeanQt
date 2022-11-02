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

#ifndef QGENERICPLUGIN_H
#define QGENERICPLUGIN_H

#include <QtCore/qplugin.h>
#include <QtCore/qfactoryinterface.h>

QT_BEGIN_NAMESPACE


#ifndef QT_NO_PLUGINS

#define QGenericPluginFactoryInterface_iid "org.qt-project.Qt.QGenericPluginFactoryInterface"

class Q_GUI_EXPORT QGenericPlugin : public QObject
{
    Q_OBJECT
public:
    explicit QGenericPlugin(QObject *parent = Q_NULLPTR);
    ~QGenericPlugin();

    virtual QObject* create(const QString& name, const QString &spec) = 0;
};

#endif // QT_NO_LIBRARY

QT_END_NAMESPACE

#endif // QGENERICPLUGIN_H
