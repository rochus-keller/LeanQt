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

#ifndef QDND_P_H
#define QDND_P_H

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

#include "QtCore/qobject.h"
#include "QtCore/qmap.h"
#include "QtGui/qmimedata.h"
#include "QtGui/qdrag.h"
#include "QtGui/qpixmap.h"
#include "QtGui/qcursor.h"
#include "QtGui/qwindow.h"
#include "QtCore/qpoint.h"
#include "private/qobject_p.h"
#include "QtGui/qbackingstore.h"
QT_BEGIN_NAMESPACE

class QEventLoop;
class QMouseEvent;
class QPlatformDrag;

#if !(defined(QT_NO_DRAGANDDROP) && defined(QT_NO_CLIPBOARD))

class Q_GUI_EXPORT QInternalMimeData : public QMimeData
{
    Q_OBJECT
public:
    QInternalMimeData();
    ~QInternalMimeData();

    bool hasFormat(const QString &mimeType) const Q_DECL_OVERRIDE;
    QStringList formats() const Q_DECL_OVERRIDE;
    static bool canReadData(const QString &mimeType);


    static QStringList formatsHelper(const QMimeData *data);
    static bool hasFormatHelper(const QString &mimeType, const QMimeData *data);
    static QByteArray renderDataHelper(const QString &mimeType, const QMimeData *data);

protected:
    QVariant retrieveData(const QString &mimeType, QVariant::Type type) const Q_DECL_OVERRIDE;

    virtual bool hasFormat_sys(const QString &mimeType) const = 0;
    virtual QStringList formats_sys() const = 0;
    virtual QVariant retrieveData_sys(const QString &mimeType, QVariant::Type type) const = 0;
};

#endif // !(defined(QT_NO_DRAGANDDROP) && defined(QT_NO_CLIPBOARD))

#ifndef QT_NO_DRAGANDDROP

class QDragPrivate : public QObjectPrivate
{
public:
    QDragPrivate()
        : source(0)
        , target(0)
        , data(0)
    { }
    QObject *source;
    QObject *target;
    QMimeData *data;
    QPixmap pixmap;
    QPoint hotspot;
    Qt::DropAction executed_action;
    Qt::DropActions supported_actions;
    Qt::DropAction default_action;
    QMap<Qt::DropAction, QPixmap> customCursors;
};

class Q_GUI_EXPORT QDragManager : public QObject {
    Q_OBJECT

public:
    QDragManager();
    ~QDragManager();
    static QDragManager *self();

    Qt::DropAction drag(QDrag *);

    void setCurrentTarget(QObject *target, bool dropped = false);
    QObject *currentTarget() const;

    QDrag *object() const { return m_object; }
    QObject *source() const;

private:
    QMimeData *m_platformDropData;
    QObject *m_currentDropTarget;
    QPlatformDrag *m_platformDrag;
    QDrag *m_object;

    static QDragManager *m_instance;
    Q_DISABLE_COPY(QDragManager)
};


#endif // !QT_NO_DRAGANDDROP


QT_END_NAMESPACE

#endif // QDND_P_H
