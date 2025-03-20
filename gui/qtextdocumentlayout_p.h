/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2025 Rochus Keller (me@rochus-keller.ch) for LeanQt
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

#ifndef QTEXTDOCUMENTLAYOUT_P_H
#define QTEXTDOCUMENTLAYOUT_P_H

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

#include "QtGui/qabstracttextdocumentlayout.h"
#include "QtGui/qtextoption.h"
#include "QtGui/qtextobject.h"

QT_BEGIN_NAMESPACE

class QTextListFormat;
class QTextTableCell;
class QTextDocumentLayoutPrivate;

class Q_GUI_EXPORT QTextDocumentLayout : public QAbstractTextDocumentLayout
{
    Q_DECLARE_PRIVATE(QTextDocumentLayout)
    Q_OBJECT
    Q_PROPERTY(int cursorWidth READ cursorWidth WRITE setCursorWidth)
    Q_PROPERTY(qreal idealWidth READ idealWidth)
    Q_PROPERTY(bool contentHasAlignment READ contentHasAlignment)
    Q_PROPERTY(bool timeoutHit READ timeoutHit)
public:
    explicit QTextDocumentLayout(QTextDocument *doc, quint32 timeout = 0);

    // from the abstract layout
    void draw(QPainter *painter, const PaintContext &context) Q_DECL_OVERRIDE;
    int hitTest(const QPointF &point, Qt::HitTestAccuracy accuracy) const Q_DECL_OVERRIDE;

    int pageCount() const Q_DECL_OVERRIDE;
    QSizeF documentSize() const Q_DECL_OVERRIDE;

    void setCursorWidth(int width);
    int cursorWidth() const;

    // internal, to support the ugly FixedColumnWidth wordwrap mode in QTextEdit
    void setFixedColumnWidth(int width);

    // internal for QTextEdit's NoWrap mode
    void setViewport(const QRectF &viewport);

    virtual QRectF frameBoundingRect(QTextFrame *frame) const Q_DECL_OVERRIDE;
    virtual QRectF blockBoundingRect(const QTextBlock &block) const Q_DECL_OVERRIDE;
    QRectF tableBoundingRect(QTextTable *table) const;
    QRectF tableCellBoundingRect(QTextTable *table, const QTextTableCell &cell) const;

    // ####
    int layoutStatus() const;
    int dynamicPageCount() const;
    QSizeF dynamicDocumentSize() const;
    void ensureLayouted(qreal);

    qreal idealWidth() const;

    bool contentHasAlignment() const;

    bool timeoutHit() const;

protected:
    void documentChanged(int from, int oldLength, int length) Q_DECL_OVERRIDE;
    void resizeInlineObject(QTextInlineObject item, int posInDocument, const QTextFormat &format) Q_DECL_OVERRIDE;
    void positionInlineObject(QTextInlineObject item, int posInDocument, const QTextFormat &format) Q_DECL_OVERRIDE;
    void drawInlineObject(QPainter *p, const QRectF &rect, QTextInlineObject item,
                          int posInDocument, const QTextFormat &format) Q_DECL_OVERRIDE;
    virtual void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;
private:
    QRectF doLayout(int from, int oldLength, int length);
    void layoutFinished();
};

QT_END_NAMESPACE

#endif // QTEXTDOCUMENTLAYOUT_P_H
