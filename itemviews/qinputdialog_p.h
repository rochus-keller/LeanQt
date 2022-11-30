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

#ifndef QINPUTDIALOG_P_H
#define QINPUTDIALOG_P_H

#include "qinputdialog.h"
#include "private/qdialog_p.h"
#include "qcombobox.h"

QT_BEGIN_NAMESPACE

class QLabel;
class QDialogButtonBox;
class QPlainTextEdit;
class QSpinBox;
class QDoubleSpinBox;
class QListView;
class QVBoxLayout;

class QInputDialogPrivate : public QDialogPrivate
{
    Q_DECLARE_PUBLIC(QInputDialog)

public:
    QInputDialogPrivate();

    void ensureLayout();
    void ensureLineEdit();
    void ensurePlainTextEdit();
    void ensureComboBox();
    void ensureListView();
    void ensureIntSpinBox();
    void ensureDoubleSpinBox();
    void ensureEnabledConnection(QAbstractSpinBox *spinBox);
    void setInputWidget(QWidget *widget);
    void chooseRightTextInputWidget();
    void setComboBoxText(const QString &text);
    void setListViewText(const QString &text);
    QString listViewText() const;
    void ensureLayout() const { const_cast<QInputDialogPrivate *>(this)->ensureLayout(); }
    bool useComboBoxOrListView() const { return comboBox && comboBox->count() > 0; }
    void _q_textChanged(const QString &text);
    void _q_plainTextEditTextChanged();
    void _q_currentRowChanged(const QModelIndex &newIndex, const QModelIndex &oldIndex);

    mutable QLabel *label;
    mutable QDialogButtonBox *buttonBox;
    mutable QLineEdit *lineEdit;
    mutable QPlainTextEdit *plainTextEdit;
    mutable QSpinBox *intSpinBox;
    mutable QDoubleSpinBox *doubleSpinBox;
    mutable QComboBox *comboBox;
    mutable QListView *listView;
    mutable QWidget *inputWidget;
    mutable QVBoxLayout *mainLayout;
    QInputDialog::InputDialogOptions opts;
    QString textValue;
    QPointer<QObject> receiverToDisconnectOnClose;
    QByteArray memberToDisconnectOnClose;
};

QT_END_NAMESPACE

#endif // QINPUTDIALOG_H
