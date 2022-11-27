#ifndef QPROGRESSDIALOG_P_H
#define QPROGRESSDIALOG_P_H

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

#include "qprogressdialog.h"
#include <private/qdialog_p.h>
#include "qelapsedtimer.h"
#include "qshortcut.h"

QT_BEGIN_NAMESPACE

class QProgressDialogPrivate : public QDialogPrivate
{
    Q_DECLARE_PUBLIC(QProgressDialog)
    
public:
	enum { 
// If the operation is expected to take this long (as predicted by
// progress time), show the progress dialog.
		defaultShowTime = 4000, 
// Wait at least this long before attempting to make a prediction.
		minWaitTime = 50
		};
    QProgressDialogPrivate() : label(0), cancel(0), bar(0),
        shown_once(false),
        cancellation_flag(false),
        setValue_called(false),
        showTime(defaultShowTime),
#ifndef QT_NO_SHORTCUT
        escapeShortcut(0),
#endif
        useDefaultCancelText(false)
    {
    }

    void init(const QString &labelText, const QString &cancelText, int min, int max);
    void layout();
    void retranslateStrings();
    void setCancelButtonText(const QString &cancelButtonText);
    void adoptChildWidget(QWidget *c);
    void ensureSizeIsAtLeastSizeHint();
    void _q_disconnectOnClose();

    QLabel *label;
    QPushButton *cancel;
    QProgressBar *bar;
    QTimer *forceTimer;
    bool shown_once;
    bool cancellation_flag;
    bool setValue_called;
    QElapsedTimer starttime;
#ifndef QT_NO_CURSOR
    QCursor parentCursor;
#endif
    int showTime;
    bool autoClose;
    bool autoReset;
    bool forceHide;
#ifndef QT_NO_SHORTCUT
    QShortcut *escapeShortcut;
#endif
    bool useDefaultCancelText;
    QPointer<QObject> receiverToDisconnectOnClose;
    QByteArray memberToDisconnectOnClose;
};


QT_END_NAMESPACE

#endif // QPROGRESSDIALOG_H
