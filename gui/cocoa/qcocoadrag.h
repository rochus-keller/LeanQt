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

#ifndef QCOCOADRAG_H
#define QCOCOADRAG_H

#include <Cocoa/Cocoa.h>
#include <QDrag>
#include <qpa/qplatformdrag.h>
#include <private/qsimpledrag_p.h>

#include <QtGui/private/qdnd_p.h>

QT_BEGIN_NAMESPACE

class QCocoaDrag : public QPlatformDrag
{
public:
    QCocoaDrag();
    ~QCocoaDrag();

    QMimeData *platformDropData() Q_DECL_OVERRIDE;
    Qt::DropAction drag(QDrag *m_drag) Q_DECL_OVERRIDE;

    Qt::DropAction defaultAction(Qt::DropActions possibleActions,
                                 Qt::KeyboardModifiers modifiers) const Q_DECL_OVERRIDE;

    /**
    * to meet NSView dragImage:at guarantees, we need to record the original
    * event and view when handling an event in QNSView
    */
    void setLastMouseEvent(NSEvent *event, NSView *view);

    void setAcceptedAction(Qt::DropAction act);
private:
    QDrag *m_drag;
    NSEvent *m_lastEvent;
    NSView *m_lastView;
    Qt::DropAction m_executed_drop_action;

    QPixmap dragPixmap(QDrag *drag, QPoint &hotSpot) const;
};

class QCocoaDropData : public QInternalMimeData
{
public:
    QCocoaDropData(NSPasteboard *pasteboard);
    ~QCocoaDropData();
protected:
    bool hasFormat_sys(const QString &mimeType) const;
    QStringList formats_sys() const;
    QVariant retrieveData_sys(const QString &mimeType, QVariant::Type type) const;
public:
    CFStringRef dropPasteboard;
};


QT_END_NAMESPACE

#endif
