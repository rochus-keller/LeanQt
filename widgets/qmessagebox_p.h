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

#ifndef QMESSAGEBOX_P_H
#define QMESSAGEBOX_P_H

#include "qmessagebox.h"
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qmenu.h>
#include "qdialog_p.h"
#include <QContextMenuEvent>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE

enum Button { Old_Ok = 1, Old_Cancel = 2, Old_Yes = 3, Old_No = 4, Old_Abort = 5, Old_Retry = 6,
              Old_Ignore = 7, Old_YesAll = 8, Old_NoAll = 9, Old_ButtonMask = 0xFF,
              NewButtonMask = 0xFFFFFC00 };

enum DetailButtonLabel { ShowLabel = 0, HideLabel = 1 };

#ifndef QT_NO_TEXTEDIT
class QMessageBoxDetailsText : public QWidget
{
    Q_OBJECT
public:
    class TextEdit : public QTextEdit
    {
    public:
        TextEdit(QWidget *parent=0) : QTextEdit(parent) { }
        void contextMenuEvent(QContextMenuEvent * e) Q_DECL_OVERRIDE
        {
#ifndef QT_NO_CONTEXTMENU
            QMenu *menu = createStandardContextMenu();
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->popup(e->globalPos());
#else
            Q_UNUSED(e);
#endif
        }
    };

    QMessageBoxDetailsText(QWidget *parent=0)
        : QWidget(parent)
        , copyAvailable(false)
    {
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setMargin(0);
        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(line);
        textEdit = new TextEdit();
        textEdit->setFixedHeight(100);
        textEdit->setFocusPolicy(Qt::NoFocus);
        textEdit->setReadOnly(true);
        layout->addWidget(textEdit);
        setLayout(layout);

        connect(textEdit, SIGNAL(copyAvailable(bool)),
                this, SLOT(textCopyAvailable(bool)));
    }
    void setText(const QString &text) { textEdit->setPlainText(text); }
    QString text() const { return textEdit->toPlainText(); }

    bool copy()
    {
#ifdef QT_NO_CLIPBOARD
        return false;
#else
        if (!copyAvailable)
            return false;
        textEdit->copy();
        return true;
#endif
    }

    void selectAll()
    {
        textEdit->selectAll();
    }

private slots:
    void textCopyAvailable(bool available)
    {
        copyAvailable = available;
    }

private:
    bool copyAvailable;
    TextEdit *textEdit;
};
#endif // QT_NO_TEXTEDIT

class DetailButton;
class QDialogButtonBox;

class QMessageBoxPrivate : public QDialogPrivate
{
    Q_DECLARE_PUBLIC(QMessageBox)

public:
    QMessageBoxPrivate() : escapeButton(0), defaultButton(0), checkbox(0), clickedButton(0), detailsButton(0),
#ifndef QT_NO_TEXTEDIT
                           detailsText(0),
#endif
                           compatMode(false), autoAddOkButton(true),
                           detectedEscapeButton(0), informativeLabel(0),
                           options(new QMessageDialogOptions) { }

    void init(const QString &title = QString(), const QString &text = QString());
    void setupLayout();
    void _q_buttonClicked(QAbstractButton *);
    void _q_clicked(QPlatformDialogHelper::StandardButton button, QPlatformDialogHelper::ButtonRole role);

    QAbstractButton *findButton(int button0, int button1, int button2, int flags);
    void addOldButtons(int button0, int button1, int button2);

    QAbstractButton *abstractButtonForId(int id) const;
    int execReturnCode(QAbstractButton *button);

    void detectEscapeButton();
    void updateSize();
    int layoutMinimumWidth();
    void retranslateStrings();

#ifdef Q_OS_WINCE
    void hideSpecial();
#endif
    static int showOldMessageBox(QWidget *parent, QMessageBox::Icon icon,
                                 const QString &title, const QString &text,
                                 int button0, int button1, int button2);
    static int showOldMessageBox(QWidget *parent, QMessageBox::Icon icon,
                                 const QString &title, const QString &text,
                                 const QString &button0Text,
                                 const QString &button1Text,
                                 const QString &button2Text,
                                 int defaultButtonNumber,
                                 int escapeButtonNumber);

    static QMessageBox::StandardButton showNewMessageBox(QWidget *parent,
                QMessageBox::Icon icon, const QString& title, const QString& text,
                QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton);

    static QPixmap standardIcon(QMessageBox::Icon icon, QMessageBox *mb);

    QLabel *label;
    QMessageBox::Icon icon;
    QLabel *iconLabel;
    QDialogButtonBox *buttonBox;
    QList<QAbstractButton *> customButtonList;
    QAbstractButton *escapeButton;
    QPushButton *defaultButton;
    QCheckBox *checkbox;
    QAbstractButton *clickedButton;
    DetailButton *detailsButton;
#ifndef QT_NO_TEXTEDIT
    QMessageBoxDetailsText *detailsText;
#endif
    bool compatMode;
    bool autoAddOkButton;
    QAbstractButton *detectedEscapeButton;
    QLabel *informativeLabel;
    QPointer<QObject> receiverToDisconnectOnClose;
    QByteArray memberToDisconnectOnClose;
    QByteArray signalToDisconnectOnClose;
    QSharedPointer<QMessageDialogOptions> options;
private:
    void initHelper(QPlatformDialogHelper *) Q_DECL_OVERRIDE;
    void helperPrepareShow(QPlatformDialogHelper *) Q_DECL_OVERRIDE;
    void helperDone(QDialog::DialogCode, QPlatformDialogHelper *) Q_DECL_OVERRIDE;
};


QT_END_NAMESPACE

#endif // QMESSAGEBOX_H
