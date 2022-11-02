#ifndef QSYNTAXHIGHLIGHTER_P_H
#define QSYNTAXHIGHLIGHTER_P_H

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

#include "qsyntaxhighlighter.h"
#include <private/qobject_p.h>

QT_BEGIN_NAMESPACE

class QSyntaxHighlighterPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QSyntaxHighlighter)
public:
    inline QSyntaxHighlighterPrivate()
        : rehighlightPending(false), inReformatBlocks(false)
    {}

    QPointer<QTextDocument> doc;

    void _q_reformatBlocks(int from, int charsRemoved, int charsAdded);
    void reformatBlocks(int from, int charsRemoved, int charsAdded);
    void reformatBlock(const QTextBlock &block);

    inline void rehighlight(QTextCursor &cursor, QTextCursor::MoveOperation operation) {
        inReformatBlocks = true;
        cursor.beginEditBlock();
        int from = cursor.position();
        cursor.movePosition(operation);
        reformatBlocks(from, 0, cursor.position() - from);
        cursor.endEditBlock();
        inReformatBlocks = false;
    }

    inline void _q_delayedRehighlight() {
        if (!rehighlightPending)
            return;
        rehighlightPending = false;
        q_func()->rehighlight();
    }

    void applyFormatChanges();
    QVector<QTextCharFormat> formatChanges;
    QTextBlock currentBlock;
    bool rehighlightPending;
    bool inReformatBlocks;
};

QT_END_NAMESPACE


#endif
