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

#ifndef QWIZARD_P_H
#define QWIZARD_P_H

#include "qwizard.h"
#include "private/qdialog_p.h"

QT_BEGIN_NAMESPACE

class QWizardAntiFlickerWidget;
class QWizardHeader;
class QWatermarkLabel;
class QFrame;
class QLabel;
class QWizardRuler;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class QWizardDefaultProperty
{
public:
    QByteArray className;
    QByteArray property;
    QByteArray changedSignal;

    inline QWizardDefaultProperty() {}
    inline QWizardDefaultProperty(const char *className, const char *property,
                                   const char *changedSignal)
        : className(className), property(property), changedSignal(changedSignal) {}
};

class QWizardLayoutInfo
{
public:
    inline QWizardLayoutInfo()
    : topLevelMarginLeft(-1), topLevelMarginRight(-1), topLevelMarginTop(-1),
      topLevelMarginBottom(-1), childMarginLeft(-1), childMarginRight(-1),
      childMarginTop(-1), childMarginBottom(-1), hspacing(-1), vspacing(-1),
      wizStyle(QWizard::ClassicStyle), header(false), watermark(false), title(false),
      subTitle(false), extension(false), sideWidget(false) {}

    int topLevelMarginLeft;
    int topLevelMarginRight;
    int topLevelMarginTop;
    int topLevelMarginBottom;
    int childMarginLeft;
    int childMarginRight;
    int childMarginTop;
    int childMarginBottom;
    int hspacing;
    int vspacing;
    int buttonSpacing;
    QWizard::WizardStyle wizStyle;
    bool header;
    bool watermark;
    bool title;
    bool subTitle;
    bool extension;
    bool sideWidget;

    bool operator==(const QWizardLayoutInfo &other);
    inline bool operator!=(const QWizardLayoutInfo &other) { return !operator==(other); }
};

class QWizardField
{
public:
    inline QWizardField() {}
    QWizardField(QWizardPage *page, const QString &spec, QObject *object, const char *property,
                  const char *changedSignal);

    void resolve(const QVector<QWizardDefaultProperty> &defaultPropertyTable);
    void findProperty(const QWizardDefaultProperty *properties, int propertyCount);

    QWizardPage *page;
    QString name;
    bool mandatory;
    QObject *object;
    QByteArray property;
    QByteArray changedSignal;
    QVariant initialValue;
};
class QWizardPrivate : public QDialogPrivate
{
    Q_DECLARE_PUBLIC(QWizard)

public:
    typedef QMap<int, QWizardPage *> PageMap;

    enum Direction {
        Backward,
        Forward
    };

    inline QWizardPrivate()
        : start(-1)
        , startSetByUser(false)
        , current(-1)
        , canContinue(false)
        , canFinish(false)
        , disableUpdatesCount(0)
        , wizStyle(QWizard::ClassicStyle)
        , opts(0)
        , buttonsHaveCustomLayout(false)
        , titleFmt(Qt::AutoText)
        , subTitleFmt(Qt::AutoText)
        , placeholderWidget1(0)
        , placeholderWidget2(0)
        , headerWidget(0)
        , watermarkLabel(0)
        , sideWidget(0)
        , pageFrame(0)
        , titleLabel(0)
        , subTitleLabel(0)
        , bottomRuler(0)
#if !defined(QT_NO_STYLE_WINDOWSVISTA)
        , vistaHelper(0)
        , vistaInitPending(false)
        , vistaState(QVistaHelper::Dirty)
        , vistaStateChanged(false)
        , inHandleAeroStyleChange(false)
#endif
        , minimumWidth(0)
        , minimumHeight(0)
        , maximumWidth(QWIDGETSIZE_MAX)
        , maximumHeight(QWIDGETSIZE_MAX)
    {
        std::fill(btns, btns + QWizard::NButtons, static_cast<QAbstractButton *>(0));

#if !defined(QT_NO_STYLE_WINDOWSVISTA)
        if (QSysInfo::WindowsVersion >= QSysInfo::WV_VISTA
            && (QSysInfo::WindowsVersion & QSysInfo::WV_NT_based))
            vistaInitPending = true;
#endif
    }

    void init();
    void reset();
    void cleanupPagesNotInHistory();
    void addField(const QWizardField &field);
    void removeFieldAt(int index);
    void switchToPage(int newId, Direction direction);
    QWizardLayoutInfo layoutInfoForCurrentPage();
    void recreateLayout(const QWizardLayoutInfo &info);
    void updateLayout();
    void updateMinMaxSizes(const QWizardLayoutInfo &info);
    void updateCurrentPage();
    bool ensureButton(QWizard::WizardButton which) const;
    void connectButton(QWizard::WizardButton which) const;
    void updateButtonTexts();
    void updateButtonLayout();
    void setButtonLayout(const QWizard::WizardButton *array, int size);
    bool buttonLayoutContains(QWizard::WizardButton which);
    void updatePixmap(QWizard::WizardPixmap which);
#if !defined(QT_NO_STYLE_WINDOWSVISTA)
    bool vistaDisabled() const;
    bool isVistaThemeEnabled(QVistaHelper::VistaState state) const;
    bool handleAeroStyleChange();
#endif
    bool isVistaThemeEnabled() const;
    void disableUpdates();
    void enableUpdates();
    void _q_emitCustomButtonClicked();
    void _q_updateButtonStates();
    void _q_handleFieldObjectDestroyed(QObject *);
    void setStyle(QStyle *style);
#ifdef Q_OS_MACX
    static QPixmap findDefaultBackgroundPixmap();
#endif

    PageMap pageMap;
    QVector<QWizardField> fields;
    QMap<QString, int> fieldIndexMap;
    QVector<QWizardDefaultProperty> defaultPropertyTable;
    QList<int> history;
    QSet<int> initialized; // ### remove and move bit to QWizardPage?
    int start;
    bool startSetByUser;
    int current;
    bool canContinue;
    bool canFinish;
    QWizardLayoutInfo layoutInfo;
    int disableUpdatesCount;

    QWizard::WizardStyle wizStyle;
    QWizard::WizardOptions opts;
    QMap<int, QString> buttonCustomTexts;
    bool buttonsHaveCustomLayout;
    QList<QWizard::WizardButton> buttonsCustomLayout;
    Qt::TextFormat titleFmt;
    Qt::TextFormat subTitleFmt;
    mutable QPixmap defaultPixmaps[QWizard::NPixmaps];

    union {
        // keep in sync with QWizard::WizardButton
        mutable struct {
            QAbstractButton *back;
            QAbstractButton *next;
            QAbstractButton *commit;
            QAbstractButton *finish;
            QAbstractButton *cancel;
            QAbstractButton *help;
        } btn;
        mutable QAbstractButton *btns[QWizard::NButtons];
    };
    QWizardAntiFlickerWidget *antiFlickerWidget;
    QWidget *placeholderWidget1;
    QWidget *placeholderWidget2;
    QWizardHeader *headerWidget;
    QWatermarkLabel *watermarkLabel;
    QWidget *sideWidget;
    QFrame *pageFrame;
    QLabel *titleLabel;
    QLabel *subTitleLabel;
    QWizardRuler *bottomRuler;

    QVBoxLayout *pageVBoxLayout;
    QHBoxLayout *buttonLayout;
    QGridLayout *mainLayout;

#if !defined(QT_NO_STYLE_WINDOWSVISTA)
    QVistaHelper *vistaHelper;
    bool vistaInitPending;
    QVistaHelper::VistaState vistaState;
    bool vistaStateChanged;
    bool inHandleAeroStyleChange;
#endif
    int minimumWidth;
    int minimumHeight;
    int maximumWidth;
    int maximumHeight;
};

class QWizardPagePrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QWizardPage)

public:
    enum TriState { Tri_Unknown = -1, Tri_False, Tri_True };

    inline QWizardPagePrivate()
        : wizard(0), completeState(Tri_Unknown), explicitlyFinal(false), commit(false) {}

    bool cachedIsComplete() const;
    void _q_maybeEmitCompleteChanged();
    void _q_updateCachedCompleteState();

    QWizard *wizard;
    QString title;
    QString subTitle;
    QPixmap pixmaps[QWizard::NPixmaps];
    QVector<QWizardField> pendingFields;
    mutable TriState completeState;
    bool explicitlyFinal;
    bool commit;
    QMap<int, QString> buttonCustomTexts;
};

QT_END_NAMESPACE

#endif // QWIZARD_H
