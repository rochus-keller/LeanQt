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

#include "qcocoaclipboard.h"
#include <QGuiApplication>

QT_BEGIN_NAMESPACE

QCocoaClipboard::QCocoaClipboard()
    :m_clipboard(new QMacPasteboard(kPasteboardClipboard, QMacInternalPasteboardMime::MIME_CLIP))
    ,m_find(new QMacPasteboard(kPasteboardFind, QMacInternalPasteboardMime::MIME_CLIP))
{
    connect(qGuiApp, &QGuiApplication::applicationStateChanged, this, &QCocoaClipboard::handleApplicationStateChanged);
}

QMimeData *QCocoaClipboard::mimeData(QClipboard::Mode mode)
{
    if (QMacPasteboard *pasteBoard = pasteboardForMode(mode)) {
        pasteBoard->sync();
        return pasteBoard->mimeData();
    }
    return 0;
}

void QCocoaClipboard::setMimeData(QMimeData *data, QClipboard::Mode mode)
{
    if (QMacPasteboard *pasteBoard = pasteboardForMode(mode)) {
        if (data == 0) {
            pasteBoard->clear();
        }

        pasteBoard->sync();
        pasteBoard->setMimeData(data);
        emitChanged(mode);
    }
}

bool QCocoaClipboard::supportsMode(QClipboard::Mode mode) const
{
    return (mode == QClipboard::Clipboard || mode == QClipboard::FindBuffer);
}

bool QCocoaClipboard::ownsMode(QClipboard::Mode mode) const
{
    Q_UNUSED(mode);
    return false;
}

QMacPasteboard *QCocoaClipboard::pasteboardForMode(QClipboard::Mode mode) const
{
    if (mode == QClipboard::Clipboard)
        return m_clipboard.data();
    else if (mode == QClipboard::FindBuffer)
        return m_find.data();
    else
        return 0;
}

void QCocoaClipboard::handleApplicationStateChanged(Qt::ApplicationState state)
{
    if (state != Qt::ApplicationActive)
        return;

    if (m_clipboard->sync())
        emitChanged(QClipboard::Clipboard);
    if (m_find->sync())
        emitChanged(QClipboard::FindBuffer);
}

//#include "moc_qcocoaclipboard.cpp"

QT_END_NAMESPACE
