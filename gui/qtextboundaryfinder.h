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

#ifndef QTEXTBOUNDARYFINDER_H
#define QTEXTBOUNDARYFINDER_H

#include <QtCore/qchar.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE


class QTextBoundaryFinderPrivate;

class Q_GUI_EXPORT QTextBoundaryFinder
{
public:
    QTextBoundaryFinder();
    QTextBoundaryFinder(const QTextBoundaryFinder &other);
    QTextBoundaryFinder &operator=(const QTextBoundaryFinder &other);
    ~QTextBoundaryFinder();

    enum BoundaryType {
        Grapheme,
        Word,
        Sentence,
        Line
    };

    enum BoundaryReason {
        NotAtBoundary = 0,
        BreakOpportunity = 0x1f,
        StartOfItem = 0x20,
        EndOfItem = 0x40,
        MandatoryBreak = 0x80,
        SoftHyphen = 0x100
    };
    Q_DECLARE_FLAGS( BoundaryReasons, BoundaryReason )

    QTextBoundaryFinder(BoundaryType type, const QString &string);
    QTextBoundaryFinder(BoundaryType type, const QChar *chars, int length, unsigned char *buffer = Q_NULLPTR, int bufferSize = 0);

    inline bool isValid() const { return d; }

    inline BoundaryType type() const { return t; }
    QString string() const;

    void toStart();
    void toEnd();
    int position() const;
    void setPosition(int position);

    int toNextBoundary();
    int toPreviousBoundary();

    bool isAtBoundary() const;
    BoundaryReasons boundaryReasons() const;

private:
    BoundaryType t;
    QString s;
    const QChar *chars;
    int length;
    int pos;
    uint freePrivate : 1;
    uint unused : 31;
    QTextBoundaryFinderPrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QTextBoundaryFinder::BoundaryReasons)

QT_END_NAMESPACE

#endif

