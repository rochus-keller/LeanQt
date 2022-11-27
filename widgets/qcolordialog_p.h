#ifndef QCOLORDIALOG_P_H
#define QCOLORDIALOG_P_H

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

#include "qcolordialog.h"
#include "private/qdialog_p.h"
#include "qdialogbuttonbox.h"
#include "qtimer.h"
#include "qlabel.h"
#include "qlayout.h"

QT_BEGIN_NAMESPACE

class QColorLuminancePicker;
class QColorPicker;
class QColorShower;
class QWellArray;
class QColorPickingEventFilter;

class QColorDialogPrivate : public QDialogPrivate
{
    Q_DECLARE_PUBLIC(QColorDialog)

public:
    enum SetColorMode {
        ShowColor = 0x1,
        SelectColor = 0x2,
        SetColorAll = ShowColor | SelectColor
    };

    QColorDialogPrivate() : options(new QColorDialogOptions)
#ifdef Q_OS_WIN32
        , updateTimer(0)
#endif
    {}

    QPlatformColorDialogHelper *platformColorDialogHelper() const
        { return static_cast<QPlatformColorDialogHelper *>(platformHelper()); }

    void init(const QColor &initial);
    void initWidgets();
    QRgb currentColor() const;
    QColor currentQColor() const;
    void setCurrentColor(const QColor &color, SetColorMode setColorMode = SetColorAll);
    void setCurrentRgbColor(QRgb rgb);
    void setCurrentQColor(const QColor &color);
    bool selectColor(const QColor &color);
    QColor grabScreenColor(const QPoint &p);

    int currentAlpha() const;
    void setCurrentAlpha(int a);
    void showAlpha(bool b);
    bool isAlphaVisible() const;
    void retranslateStrings();

    void _q_addCustom();

    void _q_newHsv(int h, int s, int v);
    void _q_newColorTypedIn(QRgb rgb);
    void _q_nextCustom(int, int);
    void _q_newCustom(int, int);
    void _q_newStandard(int, int);
    void _q_pickScreenColor();
    void _q_updateColorPicking();
    void updateColorLabelText(const QPoint &);
    void updateColorPicking(const QPoint &pos);
    void releaseColorPicking();
    bool handleColorPickingMouseMove(QMouseEvent *e);
    bool handleColorPickingMouseButtonRelease(QMouseEvent *e);
    bool handleColorPickingKeyPress(QKeyEvent *e);

    bool canBeNativeDialog() const Q_DECL_OVERRIDE;

    QWellArray *custom;
    QWellArray *standard;

    QDialogButtonBox *buttons;
    QVBoxLayout *leftLay;
    QColorPicker *cp;
    QColorLuminancePicker *lp;
    QColorShower *cs;
    QLabel *lblBasicColors;
    QLabel *lblCustomColors;
    QLabel *lblScreenColorInfo;
    QPushButton *ok;
    QPushButton *cancel;
    QPushButton *addCusBt;
    QPushButton *screenColorPickerButton;
    QColor selectedQColor;
    int nextCust;
    bool smallDisplay;
    bool screenColorPicking;
    QColorPickingEventFilter *colorPickingEventFilter;
    QRgb beforeScreenColorPicking;
    QSharedPointer<QColorDialogOptions> options;

    QPointer<QObject> receiverToDisconnectOnClose;
    QByteArray memberToDisconnectOnClose;
#ifdef Q_OS_WIN32
    QTimer *updateTimer;
    QWindow dummyTransparentWindow;
#endif

private:
    virtual void initHelper(QPlatformDialogHelper *h) Q_DECL_OVERRIDE;
    virtual void helperPrepareShow(QPlatformDialogHelper *h) Q_DECL_OVERRIDE;
};

QT_END_NAMESPACE


#endif
