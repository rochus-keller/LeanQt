/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtWidgets module of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
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

#ifndef QWIDGETTEXTCONTROL_P_P_H
#define QWIDGETTEXTCONTROL_P_P_H

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

#include "QtGui/qtextdocumentfragment.h"
#include "QtWidgets/qscrollbar.h"
#include "QtGui/qtextcursor.h"
#include "QtGui/qtextformat.h"
#include "QtWidgets/qmenu.h"
#include "QtGui/qabstracttextdocumentlayout.h"
#include "QtCore/qbasictimer.h"
#include "QtCore/qpointer.h"
#include "private/qobject_p.h"
#include "qwidgettextcontrol_p.h"

QT_BEGIN_NAMESPACE

class QMimeData;
class QAbstractScrollArea;

class QWidgetTextControlPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QWidgetTextControl)
public:
    QWidgetTextControlPrivate();

    bool cursorMoveKeyEvent(QKeyEvent *e);

    void updateCurrentCharFormat();

    void indent();
    void outdent();

    void gotoNextTableCell();
    void gotoPreviousTableCell();

    void createAutoBulletList();

    void init(Qt::TextFormat format = Qt::RichText, const QString &text = QString(),
              QTextDocument *document = 0);
    void setContent(Qt::TextFormat format = Qt::RichText, const QString &text = QString(),
                    QTextDocument *document = 0);
    void startDrag();

    void paste(const QMimeData *source);

    void setCursorPosition(const QPointF &pos);
    void setCursorPosition(int pos, QTextCursor::MoveMode mode = QTextCursor::MoveAnchor);

    void repaintCursor();
    inline void repaintSelection()
    { repaintOldAndNewSelection(QTextCursor()); }
    void repaintOldAndNewSelection(const QTextCursor &oldSelection);

    void selectionChanged(bool forceEmitSelectionChanged = false);

    void _q_updateCurrentCharFormatAndSelection();

#ifndef QT_NO_CLIPBOARD
    void setClipboardSelection();
#endif

    void _q_emitCursorPosChanged(const QTextCursor &someCursor);
    void _q_contentsChanged(int from, int charsRemoved, int charsAdded);

    void setBlinkingCursorEnabled(bool enable);

    void extendWordwiseSelection(int suggestedNewPosition, qreal mouseXPosition);
    void extendBlockwiseSelection(int suggestedNewPosition);

    void _q_deleteSelected();

    void _q_setCursorAfterUndoRedo(int undoPosition, int charsAdded, int charsRemoved);

    QRectF cursorRectPlusUnicodeDirectionMarkers(const QTextCursor &cursor) const;
    QRectF rectForPosition(int position) const;
    QRectF selectionRect(const QTextCursor &cursor) const;
    inline QRectF selectionRect() const
    { return selectionRect(this->cursor); }

    QString anchorForCursor(const QTextCursor &anchor) const;

    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QEvent *e, Qt::MouseButton button, const QPointF &pos,
                         Qt::KeyboardModifiers modifiers,
                         Qt::MouseButtons buttons,
                         const QPoint &globalPos);
    void mouseMoveEvent(QEvent *e, Qt::MouseButton button, const QPointF &pos,
                        Qt::KeyboardModifiers modifiers,
                        Qt::MouseButtons buttons,
                        const QPoint &globalPos);
    void mouseReleaseEvent(QEvent *e, Qt::MouseButton button, const QPointF &pos,
                           Qt::KeyboardModifiers modifiers,
                           Qt::MouseButtons buttons,
                           const QPoint &globalPos);
    void mouseDoubleClickEvent(QEvent *e, Qt::MouseButton button, const QPointF &pos,
                               Qt::KeyboardModifiers modifiers,
                               Qt::MouseButtons buttons,
                               const QPoint &globalPos);
    bool sendMouseEventToInputContext(QEvent *e,  QEvent::Type eventType, Qt::MouseButton button,
                                      const QPointF &pos,
                                      Qt::KeyboardModifiers modifiers,
                                      Qt::MouseButtons buttons,
                                      const QPoint &globalPos);
    void contextMenuEvent(const QPoint &screenPos, const QPointF &docPos, QWidget *contextWidget);
    void focusEvent(QFocusEvent *e);
#ifdef QT_KEYPAD_NAVIGATION
    void editFocusEvent(QEvent *e);
#endif
    bool dragEnterEvent(QEvent *e, const QMimeData *mimeData);
    void dragLeaveEvent();
    bool dragMoveEvent(QEvent *e, const QMimeData *mimeData, const QPointF &pos);
    bool dropEvent(const QMimeData *mimeData, const QPointF &pos, Qt::DropAction dropAction, QObject *source);

    void inputMethodEvent(QInputMethodEvent *);

    void activateLinkUnderCursor(QString href = QString());

#ifndef QT_NO_TOOLTIP
    void showToolTip(const QPoint &globalPos, const QPointF &pos, QWidget *contextWidget);
#endif

    bool isPreediting() const;
    void commitPreedit();

    void append(const QString &text, Qt::TextFormat format = Qt::AutoText);

    QTextDocument *doc;
    bool cursorOn;
    QTextCursor cursor;
    bool cursorIsFocusIndicator;
    QTextCharFormat lastCharFormat;

    QTextCursor dndFeedbackCursor;

    Qt::TextInteractionFlags interactionFlags;

    QBasicTimer cursorBlinkTimer;
    QBasicTimer trippleClickTimer;
    QPointF trippleClickPoint;

    bool dragEnabled;

    bool mousePressed;

    bool mightStartDrag;
    QPoint mousePressPos;
    QPointer<QWidget> contextWidget;

    int lastSelectionPosition;
    int lastSelectionAnchor;

    bool ignoreAutomaticScrollbarAdjustement;

    QTextCursor selectedWordOnDoubleClick;
    QTextCursor selectedBlockOnTrippleClick;

    bool overwriteMode;
    bool acceptRichText;

    int preeditCursor;
    bool hideCursor; // used to hide the cursor in the preedit area

    QVector<QAbstractTextDocumentLayout::Selection> extraSelections;

    QPalette palette;
    bool hasFocus;
#ifdef QT_KEYPAD_NAVIGATION
    bool hasEditFocus;
#endif
    bool isEnabled;

    QString highlightedAnchor; // Anchor below cursor
    QString anchorOnMousePress;
    bool hadSelectionOnMousePress;

    bool ignoreUnusedNavigationEvents;
    bool openExternalLinks;

    bool wordSelectionEnabled;

    QString linkToCopy;
    void _q_copyLink();
    void _q_updateBlock(const QTextBlock &);
    void _q_documentLayoutChanged();
};

QT_END_NAMESPACE

#endif // QWidgetTextControl_P_H
