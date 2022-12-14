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

#ifndef QDATETIMEEDIT_P_H
#define QDATETIMEEDIT_P_H

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

#include "QtWidgets/qcombobox.h"
#include "QtWidgets/qcalendarwidget.h"
#include "QtWidgets/qspinbox.h"
#include "QtWidgets/qtoolbutton.h"
#include "QtWidgets/qmenu.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qdatetimeedit.h"
#include "private/qabstractspinbox_p.h"
#include "private/qdatetimeparser_p.h"

#include "qdebug.h"

#ifndef QT_NO_DATETIMEEDIT

QT_BEGIN_NAMESPACE

class QCalendarPopup;
class Q_AUTOTEST_EXPORT QDateTimeEditPrivate : public QAbstractSpinBoxPrivate, public QDateTimeParser
{
    Q_DECLARE_PUBLIC(QDateTimeEdit)
public:
    QDateTimeEditPrivate();
    ~QDateTimeEditPrivate();

    void init(const QVariant &var);
    void readLocaleSettings();

    QDateTime validateAndInterpret(QString &input, int &, QValidator::State &state,
                                   bool fixup = false) const;
    void clearSection(int index);

    // Override QAbstractSpinBoxPrivate:
    void emitSignals(EmitPolicy ep, const QVariant &old) Q_DECL_OVERRIDE;
    QString textFromValue(const QVariant &f) const Q_DECL_OVERRIDE;
    QVariant valueFromText(const QString &f) const Q_DECL_OVERRIDE;
    void _q_editorCursorPositionChanged(int oldpos, int newpos) Q_DECL_OVERRIDE;
    void interpret(EmitPolicy ep) Q_DECL_OVERRIDE;
    void clearCache() const Q_DECL_OVERRIDE;
    QStyle::SubControl newHoverControl(const QPoint &pos) Q_DECL_OVERRIDE;
    void updateEditFieldGeometry() Q_DECL_OVERRIDE;
    QVariant getZeroVariant() const Q_DECL_OVERRIDE;
    void setRange(const QVariant &min, const QVariant &max) Q_DECL_OVERRIDE;
    void updateEdit() Q_DECL_OVERRIDE;

    // Override QDateTimeParser:
    QString displayText() const Q_DECL_OVERRIDE { return edit->text(); }
    QDateTime getMinimum() const Q_DECL_OVERRIDE { return minimum.toDateTime(); }
    QDateTime getMaximum() const Q_DECL_OVERRIDE { return maximum.toDateTime(); }
    QLocale locale() const Q_DECL_OVERRIDE { return q_func()->locale(); }
    QString getAmPmText(AmPm ap, Case cs) const Q_DECL_OVERRIDE;
    int cursorPosition() const Q_DECL_OVERRIDE { return edit ? edit->cursorPosition() : -1; }

    int absoluteIndex(QDateTimeEdit::Section s, int index) const;
    int absoluteIndex(const SectionNode &s) const;
    QDateTime stepBy(int index, int steps, bool test = false) const;
    int sectionAt(int pos) const;
    int closestSection(int index, bool forward) const;
    int nextPrevSection(int index, bool forward) const;
    void setSelected(int index, bool forward = false);

    void updateCache(const QVariant &val, const QString &str) const;

    void updateTimeSpec();
    QString valueToText(const QVariant &var) const { return textFromValue(var); }

    void _q_resetButton();
    void updateArrow(QStyle::StateFlag state);
    bool calendarPopupEnabled() const;
    void syncCalendarWidget();

    bool isSeparatorKey(const QKeyEvent *k) const;

    static QDateTimeEdit::Sections convertSections(QDateTimeParser::Sections s);
    static QDateTimeEdit::Section convertToPublic(QDateTimeParser::Section s);

    void initCalendarPopup(QCalendarWidget *cw = 0);
    void positionCalendarPopup();

    QDateTimeEdit::Sections sections;
    mutable bool cacheGuard;

    QString defaultDateFormat, defaultTimeFormat, defaultDateTimeFormat, unreversedFormat;
    mutable QVariant conflictGuard;
    bool hasHadFocus, formatExplicitlySet, calendarPopup;
    QStyle::StateFlag arrowState;
    QCalendarPopup *monthCalendar;

#ifdef QT_KEYPAD_NAVIGATION
    bool focusOnButton;
#endif
};


class QCalendarPopup : public QWidget
{
    Q_OBJECT
public:
    explicit QCalendarPopup(QWidget *parent = 0, QCalendarWidget *cw = 0);
    QDate selectedDate() { return verifyCalendarInstance()->selectedDate(); }
    void setDate(const QDate &date);
    void setDateRange(const QDate &min, const QDate &max);
    void setFirstDayOfWeek(Qt::DayOfWeek dow) { verifyCalendarInstance()->setFirstDayOfWeek(dow); }
    QCalendarWidget *calendarWidget() const { return const_cast<QCalendarPopup*>(this)->verifyCalendarInstance(); }
    void setCalendarWidget(QCalendarWidget *cw);
Q_SIGNALS:
    void activated(const QDate &date);
    void newDateSelected(const QDate &newDate);
    void hidingCalendar(const QDate &oldDate);
    void resetButton();

private Q_SLOTS:
    void dateSelected(const QDate &date);
    void dateSelectionChanged();

protected:
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    bool event(QEvent *e);

private:
    QCalendarWidget *verifyCalendarInstance();

    QPointer<QCalendarWidget> calendar;
    QDate oldDate;
    bool dateChanged;
};

QT_END_NAMESPACE

#endif // QT_NO_DATETIMEEDIT

#endif // QDATETIMEEDIT_P_H
