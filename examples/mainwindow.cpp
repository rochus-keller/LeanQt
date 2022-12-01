/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
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

#include "mainwindow.h"

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QApplication>
#include <QPainterPath>
#include <QMap>
#include <QDebug>
#include <QFrame>
#include <QMenu>
#include <QImage>
#include <QColor>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QBitmap>

#undef DEBUG_SIZEHINTS

QColor bgColorForName(const QString &name)
{
    if (name == "Black")
        return QColor("#D8D8D8");
    if (name == "White")
        return QColor("#F1F1F1");
    if (name == "Red")
        return QColor("#F1D8D8");
    if (name == "Green")
        return QColor("#D8E4D8");
    if (name == "Blue")
        return QColor("#D8D8F1");
    if (name == "Yellow")
        return QColor("#F1F0D8");
    return QColor(name).light(110);
}

QColor fgColorForName(const QString &name)
{
    if (name == "Black")
        return QColor("#6C6C6C");
    if (name == "White")
        return QColor("#F8F8F8");
    if (name == "Red")
        return QColor("#F86C6C");
    if (name == "Green")
        return QColor("#6CB26C");
    if (name == "Blue")
        return QColor("#6C6CF8");
    if (name == "Yellow")
        return QColor("#F8F76C");
    return QColor(name);
}

class ColorDock : public QFrame
{
    Q_OBJECT
public:
    explicit ColorDock(const QString &c, QWidget *parent);

    QSize sizeHint() const Q_DECL_OVERRIDE { return szHint; }
    QSize minimumSizeHint() const Q_DECL_OVERRIDE { return minSzHint; }

    void setCustomSizeHint(const QSize &size);

public slots:
    void changeSizeHints();

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    const QString color;
    QSize szHint;
    QSize minSzHint;
};

ColorDock::ColorDock(const QString &c, QWidget *parent)
    : QFrame(parent)
    , color(c)
    , szHint(-1, -1)
    , minSzHint(125, 75)
{
    QFont font = this->font();
    font.setPointSize(8);
    setFont(font);
}

void ColorDock::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(rect(), bgColorForName(color));

    p.save();

    extern void render_qt_text(QPainter *, int, int, const QColor &);
    render_qt_text(&p, width(), height(), fgColorForName(color));

    p.restore();

#ifdef DEBUG_SIZEHINTS
    p.setRenderHint(QPainter::Antialiasing, false);

    QSize sz = size();
    QSize szHint = sizeHint();
    QSize minSzHint = minimumSizeHint();
    QSize maxSz = maximumSize();
    QString text = QString::fromLatin1("sz: %1x%2\nszHint: %3x%4\nminSzHint: %5x%6\n"
                                        "maxSz: %8x%9")
                    .arg(sz.width()).arg(sz.height())
                    .arg(szHint.width()).arg(szHint.height())
                    .arg(minSzHint.width()).arg(minSzHint.height())
                    .arg(maxSz.width()).arg(maxSz.height());

    QRect r = fontMetrics().boundingRect(rect(), Qt::AlignLeft|Qt::AlignTop, text);
    r.adjust(-2, -2, 1, 1);
    p.translate(4, 4);
    QColor bg = Qt::yellow;
    bg.setAlpha(120);
    p.setBrush(bg);
    p.setPen(Qt::black);
    p.drawRect(r);
    p.drawText(rect(), Qt::AlignLeft|Qt::AlignTop, text);
#endif // DEBUG_SIZEHINTS
}

static QSpinBox *createSpinBox(int value, QWidget *parent, int max = 1000)
{
    QSpinBox *result = new QSpinBox(parent);
    result->setMinimum(-1);
    result->setMaximum(max);
    result->setValue(value);
    return result;
}

void ColorDock::changeSizeHints()
{
    QDialog dialog(this);
    dialog.setWindowFlags(dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    dialog.setWindowTitle(color);

    QVBoxLayout *topLayout = new QVBoxLayout(&dialog);

    QGridLayout *inputLayout = new QGridLayout();
    topLayout->addLayout(inputLayout);

    inputLayout->addWidget(new QLabel(tr("Size Hint:"), &dialog), 0, 0);
    inputLayout->addWidget(new QLabel(tr("Min Size Hint:"), &dialog), 1, 0);
    inputLayout->addWidget(new QLabel(tr("Max Size:"), &dialog), 2, 0);
    inputLayout->addWidget(new QLabel(tr("Dock Widget Max Size:"), &dialog), 3, 0);

    QSpinBox *szHintW = createSpinBox(szHint.width(), &dialog);
    inputLayout->addWidget(szHintW, 0, 1);
    QSpinBox *szHintH = createSpinBox(szHint.height(), &dialog);
    inputLayout->addWidget(szHintH, 0, 2);

    QSpinBox *minSzHintW = createSpinBox(minSzHint.width(), &dialog);
    inputLayout->addWidget(minSzHintW, 1, 1);
    QSpinBox *minSzHintH = createSpinBox(minSzHint.height(), &dialog);
    inputLayout->addWidget(minSzHintH, 1, 2);

    QSize maxSz = maximumSize();
    QSpinBox *maxSzW = createSpinBox(maxSz.width(), &dialog, QWIDGETSIZE_MAX);
    inputLayout->addWidget(maxSzW, 2, 1);
    QSpinBox *maxSzH = createSpinBox(maxSz.height(), &dialog, QWIDGETSIZE_MAX);
    inputLayout->addWidget(maxSzH, 2, 2);

    QSize dwMaxSz = parentWidget()->maximumSize();
    QSpinBox *dwMaxSzW = createSpinBox(dwMaxSz.width(), &dialog, QWIDGETSIZE_MAX);
    inputLayout->addWidget(dwMaxSzW, 3, 1);
    QSpinBox *dwMaxSzH = createSpinBox(dwMaxSz.height(), &dialog, QWIDGETSIZE_MAX);
    inputLayout->addWidget(dwMaxSzH, 3, 2);

    inputLayout->setColumnStretch(1, 1);
    inputLayout->setColumnStretch(2, 1);

    topLayout->addStretch();

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::reject);

    topLayout->addWidget(buttonBox);

    if (dialog.exec() != QDialog::Accepted)
        return;

    szHint = QSize(szHintW->value(), szHintH->value());
    minSzHint = QSize(minSzHintW->value(), minSzHintH->value());
    maxSz = QSize(maxSzW->value(), maxSzH->value());
    setMaximumSize(maxSz);
    dwMaxSz = QSize(dwMaxSzW->value(), dwMaxSzH->value());
    parentWidget()->setMaximumSize(dwMaxSz);
    updateGeometry();
    update();
}

void ColorDock::setCustomSizeHint(const QSize &size)
{
    if (szHint != size) {
        szHint = size;
        updateGeometry();
    }
}

ColorSwatch::ColorSwatch(const QString &colorName, QMainWindow *parent, Qt::WindowFlags flags)
    : QDockWidget(parent, flags), mainWindow(parent)
{
    setObjectName(colorName + QLatin1String(" Dock Widget"));
    setWindowTitle(objectName() + QLatin1String(" [*]"));

    ColorDock *swatch = new ColorDock(colorName, this);
    swatch->setFrameStyle(QFrame::Box | QFrame::Sunken);

    setWidget(swatch);

    closableAction = new QAction(tr("Closable"), this);
    closableAction->setCheckable(true);
    connect(closableAction, &QAction::triggered, this, &ColorSwatch::changeClosable);

    movableAction = new QAction(tr("Movable"), this);
    movableAction->setCheckable(true);
    connect(movableAction, &QAction::triggered, this, &ColorSwatch::changeMovable);

    floatableAction = new QAction(tr("Floatable"), this);
    floatableAction->setCheckable(true);
    connect(floatableAction, &QAction::triggered, this, &ColorSwatch::changeFloatable);

    verticalTitleBarAction = new QAction(tr("Vertical title bar"), this);
    verticalTitleBarAction->setCheckable(true);
    connect(verticalTitleBarAction, &QAction::triggered,
            this, &ColorSwatch::changeVerticalTitleBar);

    floatingAction = new QAction(tr("Floating"), this);
    floatingAction->setCheckable(true);
    connect(floatingAction, &QAction::triggered, this, &ColorSwatch::changeFloating);

    allowedAreasActions = new QActionGroup(this);
    allowedAreasActions->setExclusive(false);

    allowLeftAction = new QAction(tr("Allow on Left"), this);
    allowLeftAction->setCheckable(true);
    connect(allowLeftAction, &QAction::triggered, this, &ColorSwatch::allowLeft);

    allowRightAction = new QAction(tr("Allow on Right"), this);
    allowRightAction->setCheckable(true);
    connect(allowRightAction, &QAction::triggered, this, &ColorSwatch::allowRight);

    allowTopAction = new QAction(tr("Allow on Top"), this);
    allowTopAction->setCheckable(true);
    connect(allowTopAction, &QAction::triggered, this, &ColorSwatch::allowTop);

    allowBottomAction = new QAction(tr("Allow on Bottom"), this);
    allowBottomAction->setCheckable(true);
    connect(allowBottomAction, &QAction::triggered, this, &ColorSwatch::allowBottom);

    allowedAreasActions->addAction(allowLeftAction);
    allowedAreasActions->addAction(allowRightAction);
    allowedAreasActions->addAction(allowTopAction);
    allowedAreasActions->addAction(allowBottomAction);

    areaActions = new QActionGroup(this);
    areaActions->setExclusive(true);

    leftAction = new QAction(tr("Place on Left") , this);
    leftAction->setCheckable(true);
    connect(leftAction, &QAction::triggered, this, &ColorSwatch::placeLeft);

    rightAction = new QAction(tr("Place on Right") , this);
    rightAction->setCheckable(true);
    connect(rightAction, &QAction::triggered, this, &ColorSwatch::placeRight);

    topAction = new QAction(tr("Place on Top") , this);
    topAction->setCheckable(true);
    connect(topAction, &QAction::triggered, this, &ColorSwatch::placeTop);

    bottomAction = new QAction(tr("Place on Bottom") , this);
    bottomAction->setCheckable(true);
    connect(bottomAction, &QAction::triggered, this, &ColorSwatch::placeBottom);

    areaActions->addAction(leftAction);
    areaActions->addAction(rightAction);
    areaActions->addAction(topAction);
    areaActions->addAction(bottomAction);

    connect(movableAction, &QAction::triggered, areaActions, &QActionGroup::setEnabled);

    connect(movableAction, &QAction::triggered, allowedAreasActions, &QActionGroup::setEnabled);

    connect(floatableAction, &QAction::triggered, floatingAction, &QAction::setEnabled);

    connect(floatingAction, &QAction::triggered, floatableAction, &QAction::setDisabled);
    connect(movableAction, &QAction::triggered, floatableAction, &QAction::setEnabled);

    tabMenu = new QMenu(this);
    tabMenu->setTitle(tr("Tab into"));
    connect(tabMenu, &QMenu::triggered, this, &ColorSwatch::tabInto);

    splitHMenu = new QMenu(this);
    splitHMenu->setTitle(tr("Split horizontally into"));
    connect(splitHMenu, &QMenu::triggered, this, &ColorSwatch::splitInto);

    splitVMenu = new QMenu(this);
    splitVMenu->setTitle(tr("Split vertically into"));
    connect(splitVMenu, &QMenu::triggered, this, &ColorSwatch::splitInto);

    QAction *windowModifiedAction = new QAction(tr("Modified"), this);
    windowModifiedAction->setCheckable(true);
    windowModifiedAction->setChecked(false);
    connect(windowModifiedAction, &QAction::toggled, this, &QWidget::setWindowModified);

    menu = new QMenu(colorName, this);
    menu->addAction(toggleViewAction());
    menu->addAction(tr("Raise"), this, SLOT(raise()));
    menu->addAction(tr("Change Size Hints..."), swatch, SLOT(changeSizeHints()));

    menu->addSeparator();
    menu->addAction(closableAction);
    menu->addAction(movableAction);
    menu->addAction(floatableAction);
    menu->addAction(floatingAction);
    menu->addAction(verticalTitleBarAction);
    menu->addSeparator();
    menu->addActions(allowedAreasActions->actions());
    menu->addSeparator();
    menu->addActions(areaActions->actions());
    menu->addSeparator();
    menu->addMenu(splitHMenu);
    menu->addMenu(splitVMenu);
    menu->addMenu(tabMenu);
    menu->addSeparator();
    menu->addAction(windowModifiedAction);

    connect(menu, &QMenu::aboutToShow, this, &ColorSwatch::updateContextMenu);

    if (colorName == QLatin1String("Black")) {
        leftAction->setShortcut(Qt::CTRL | Qt::Key_W);
        rightAction->setShortcut(Qt::CTRL | Qt::Key_E);
        toggleViewAction()->setShortcut(Qt::CTRL | Qt::Key_R);
    }
}

void ColorSwatch::updateContextMenu()
{
    const Qt::DockWidgetArea area = mainWindow->dockWidgetArea(this);
    const Qt::DockWidgetAreas areas = allowedAreas();

    closableAction->setChecked(features() & QDockWidget::DockWidgetClosable);
    if (windowType() == Qt::Drawer) {
        floatableAction->setEnabled(false);
        floatingAction->setEnabled(false);
        movableAction->setEnabled(false);
        verticalTitleBarAction->setChecked(false);
    } else {
        floatableAction->setChecked(features() & QDockWidget::DockWidgetFloatable);
        floatingAction->setChecked(isWindow());
        // done after floating, to get 'floatable' correctly initialized
        movableAction->setChecked(features() & QDockWidget::DockWidgetMovable);
        verticalTitleBarAction
            ->setChecked(features() & QDockWidget::DockWidgetVerticalTitleBar);
    }

    allowLeftAction->setChecked(isAreaAllowed(Qt::LeftDockWidgetArea));
    allowRightAction->setChecked(isAreaAllowed(Qt::RightDockWidgetArea));
    allowTopAction->setChecked(isAreaAllowed(Qt::TopDockWidgetArea));
    allowBottomAction->setChecked(isAreaAllowed(Qt::BottomDockWidgetArea));

    if (allowedAreasActions->isEnabled()) {
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }

    {
        const QSignalBlocker blocker(leftAction);
        leftAction->setChecked(area == Qt::LeftDockWidgetArea);
    }
    {
        const QSignalBlocker blocker(rightAction);
        rightAction->setChecked(area == Qt::RightDockWidgetArea);
    }
    {
        const QSignalBlocker blocker(topAction);
        topAction->setChecked(area == Qt::TopDockWidgetArea);
    }
    {
        const QSignalBlocker blocker(bottomAction);
        bottomAction->setChecked(area == Qt::BottomDockWidgetArea);
    }

    if (areaActions->isEnabled()) {
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }

    tabMenu->clear();
    splitHMenu->clear();
    splitVMenu->clear();
    QList<ColorSwatch*> dock_list = mainWindow->findChildren<ColorSwatch*>();
    foreach (ColorSwatch *dock, dock_list) {
        tabMenu->addAction(dock->objectName());
        splitHMenu->addAction(dock->objectName());
        splitVMenu->addAction(dock->objectName());
    }
}

static ColorSwatch *findByName(const QMainWindow *mainWindow, const QString &name)
{
    foreach (ColorSwatch *dock, mainWindow->findChildren<ColorSwatch*>()) {
        if (name == dock->objectName())
            return dock;
    }
    return Q_NULLPTR;
}

void ColorSwatch::splitInto(QAction *action)
{
    ColorSwatch *target = findByName(mainWindow, action->text());
    if (!target)
        return;

    const Qt::Orientation o = action->parent() == splitHMenu
        ? Qt::Horizontal : Qt::Vertical;
    mainWindow->splitDockWidget(target, this, o);
}

void ColorSwatch::tabInto(QAction *action)
{
    if (ColorSwatch *target = findByName(mainWindow, action->text()))
        mainWindow->tabifyDockWidget(target, this);
}

void ColorSwatch::contextMenuEvent(QContextMenuEvent *event)
{
    event->accept();
    menu->exec(event->globalPos());
}

void ColorSwatch::resizeEvent(QResizeEvent *e)
{
    if (BlueTitleBar *btb = qobject_cast<BlueTitleBar*>(titleBarWidget()))
        btb->updateMask();

    QDockWidget::resizeEvent(e);
}

void ColorSwatch::allow(Qt::DockWidgetArea area, bool a)
{
    Qt::DockWidgetAreas areas = allowedAreas();
    areas = a ? areas | area : areas & ~area;
    setAllowedAreas(areas);

    if (areaActions->isEnabled()) {
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }
}

void ColorSwatch::place(Qt::DockWidgetArea area, bool p)
{
    if (!p)
        return;

    mainWindow->addDockWidget(area, this);

    if (allowedAreasActions->isEnabled()) {
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }
}

void ColorSwatch::setCustomSizeHint(const QSize &size)
{
    if (ColorDock *dock = qobject_cast<ColorDock*>(widget()))
        dock->setCustomSizeHint(size);
}

void ColorSwatch::changeClosable(bool on)
{ setFeatures(on ? features() | DockWidgetClosable : features() & ~DockWidgetClosable); }

void ColorSwatch::changeMovable(bool on)
{ setFeatures(on ? features() | DockWidgetMovable : features() & ~DockWidgetMovable); }

void ColorSwatch::changeFloatable(bool on)
{ setFeatures(on ? features() | DockWidgetFloatable : features() & ~DockWidgetFloatable); }

void ColorSwatch::changeFloating(bool floating)
{ setFloating(floating); }

void ColorSwatch::allowLeft(bool a)
{ allow(Qt::LeftDockWidgetArea, a); }

void ColorSwatch::allowRight(bool a)
{ allow(Qt::RightDockWidgetArea, a); }

void ColorSwatch::allowTop(bool a)
{ allow(Qt::TopDockWidgetArea, a); }

void ColorSwatch::allowBottom(bool a)
{ allow(Qt::BottomDockWidgetArea, a); }

void ColorSwatch::placeLeft(bool p)
{ place(Qt::LeftDockWidgetArea, p); }

void ColorSwatch::placeRight(bool p)
{ place(Qt::RightDockWidgetArea, p); }

void ColorSwatch::placeTop(bool p)
{ place(Qt::TopDockWidgetArea, p); }

void ColorSwatch::placeBottom(bool p)
{ place(Qt::BottomDockWidgetArea, p); }

void ColorSwatch::changeVerticalTitleBar(bool on)
{
    setFeatures(on ? features() | DockWidgetVerticalTitleBar
                    : features() & ~DockWidgetVerticalTitleBar);
}

QSize BlueTitleBar::minimumSizeHint() const
{
    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);
    QSize result(leftPm.width() + rightPm.width(), centerPm.height());
    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
        result.transpose();
    return result;
}

BlueTitleBar::BlueTitleBar(QWidget *parent)
    : QWidget(parent)
    , leftPm(QPixmap(":/res/titlebarLeft.png"))
    , centerPm(QPixmap(":/res/titlebarCenter.png"))
    , rightPm(QPixmap(":/res/titlebarRight.png"))
{
}

void BlueTitleBar::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect = this->rect();

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) {
        QSize s = rect.size();
        s.transpose();
        rect.setSize(s);

        painter.translate(rect.left(), rect.top() + rect.width());
        painter.rotate(-90);
        painter.translate(-rect.left(), -rect.top());
    }

    painter.drawPixmap(rect.topLeft(), leftPm);
    painter.drawPixmap(rect.topRight() - QPoint(rightPm.width() - 1, 0), rightPm);
    QBrush brush(centerPm);
    painter.fillRect(rect.left() + leftPm.width(), rect.top(),
                        rect.width() - leftPm.width() - rightPm.width(),
                        centerPm.height(), centerPm);
}

void BlueTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();

    QRect rect = this->rect();

    QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
    Q_ASSERT(dw != 0);

    if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) {
        QPoint p = pos;
        pos.setX(rect.left() + rect.bottom() - p.y());
        pos.setY(rect.top() + p.x() - rect.left());

        QSize s = rect.size();
        s.transpose();
        rect.setSize(s);
    }

    const int buttonRight = 7;
    const int buttonWidth = 20;
    int right = rect.right() - pos.x();
    int button = (right - buttonRight)/buttonWidth;
    switch (button) {
        case 0:
            event->accept();
            dw->close();
            break;
        case 1:
            event->accept();
            dw->setFloating(!dw->isFloating());
            break;
        case 2: {
            event->accept();
            QDockWidget::DockWidgetFeatures features = dw->features();
            if (features & QDockWidget::DockWidgetVerticalTitleBar)
                features &= ~QDockWidget::DockWidgetVerticalTitleBar;
            else
                features |= QDockWidget::DockWidgetVerticalTitleBar;
            dw->setFeatures(features);
            break;
        }
        default:
            event->ignore();
            break;
    }
}

void BlueTitleBar::updateMask()
{
    QDockWidget *dw = qobject_cast<QDockWidget*>(parent());
    Q_ASSERT(dw != 0);

    QRect rect = dw->rect();
    QPixmap bitmap(dw->size());

    {
        QPainter painter(&bitmap);

        // initialize to transparent
        painter.fillRect(rect, Qt::color0);

        QRect contents = rect;
        contents.setTopLeft(geometry().bottomLeft());
        contents.setRight(geometry().right());
        contents.setBottom(contents.bottom()-y());
        painter.fillRect(contents, Qt::color1);

        // let's paint the titlebar
        QRect titleRect = this->geometry();

        if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) {
            QSize s = rect.size();
            s.transpose();
            rect.setSize(s);

            QSize s2 = size();
            s2.transpose();
            titleRect.setSize(s2);

            painter.translate(rect.left(), rect.top() + rect.width());
            painter.rotate(-90);
            painter.translate(-rect.left(), -rect.top());
        }

        contents.setTopLeft(titleRect.bottomLeft());
        contents.setRight(titleRect.right());
        contents.setBottom(rect.bottom()-y());

        QRect rect = titleRect;

        painter.drawPixmap(rect.topLeft(), leftPm.mask());
        painter.fillRect(rect.left() + leftPm.width(), rect.top(),
            rect.width() - leftPm.width() - rightPm.width(),
            centerPm.height(), Qt::color1);
        painter.drawPixmap(rect.topRight() - QPoint(rightPm.width() - 1, 0), rightPm.mask());

        painter.fillRect(contents, Qt::color1);
    }

    dw->setMask(bitmap);
}

static const char message[] =
    "<p><b>Qt Main Window Example</b></p>"

    "<p>This is a demonstration of the QMainWindow, QToolBar and "
    "QDockWidget classes.</p>"

    "<p>The tool bar and dock widgets can be dragged around and rearranged "
    "using the mouse or via the menu.</p>"

    "<p>Each dock widget contains a colored frame and a context "
    "(right-click) menu.</p>"

#ifdef Q_OS_MAC
    "<p>On OS X, the \"Black\" dock widget has been created as a "
    "<em>Drawer</em>, which is a special kind of QDockWidget.</p>"
#endif
    ;

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

MainWindow::MainWindow(const CustomSizeHintMap &customSizeHints,
                       QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("Qt Main Window Example");

    QTextEdit *center = new QTextEdit(this);
    center->setReadOnly(true);
    center->setMinimumSize(400, 205);
    setCentralWidget(center);

    setupMenuBar();
    setupDockWidgets(customSizeHints);

    statusBar()->showMessage(tr("Status Bar"));
}

void MainWindow::actionTriggered(QAction *action)
{
    qDebug("action '%s' triggered", action->text().toLocal8Bit().data());
}

void MainWindow::setupMenuBar()
{
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    menu->addAction(tr("Save layout..."), this, SLOT(saveLayout()));
    menu->addAction(tr("Load layout..."), this, SLOT(loadLayout()));
    menu->addAction(tr("Switch layout direction"),this, SLOT(switchLayoutDirection()));

    menu->addSeparator();
    menu->addAction(tr("&Quit"), this, SLOT(close()));

    mainWindowMenu = menuBar()->addMenu(tr("Main window"));

    QAction *action = mainWindowMenu->addAction(tr("Animated docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AnimatedDocks);
    connect(action, &QAction::toggled, this, &MainWindow::setDockOptions);

    action = mainWindowMenu->addAction(tr("Allow nested docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AllowNestedDocks);
    connect(action, &QAction::toggled, this, &MainWindow::setDockOptions);

    action = mainWindowMenu->addAction(tr("Allow tabbed docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & AllowTabbedDocks);
    connect(action, &QAction::toggled, this, &MainWindow::setDockOptions);

    action = mainWindowMenu->addAction(tr("Force tabbed docks"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & ForceTabbedDocks);
    connect(action, &QAction::toggled, this, &MainWindow::setDockOptions);

    action = mainWindowMenu->addAction(tr("Vertical tabs"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & VerticalTabs);
    connect(action, &QAction::toggled, this, &MainWindow::setDockOptions);

    /*
    action = mainWindowMenu->addAction(tr("Grouped dragging"));
    action->setCheckable(true);
    action->setChecked(dockOptions() & GroupedDragging);
    connect(action, &QAction::toggled, this, &MainWindow::setDockOptions);
    */

#ifdef Q_OS_OSX
    toolBarMenu->addSeparator();

    action = toolBarMenu->addAction(tr("Unified"));
    action->setCheckable(true);
    action->setChecked(unifiedTitleAndToolBarOnMac());
    connect(action, &QAction::toggled, this, &QMainWindow::setUnifiedTitleAndToolBarOnMac);
#endif

    dockWidgetMenu = menuBar()->addMenu(tr("&Dock Widgets"));
}

void MainWindow::setDockOptions()
{
    DockOptions opts;
    QList<QAction*> actions = mainWindowMenu->actions();

    if (actions.at(0)->isChecked())
        opts |= AnimatedDocks;
    if (actions.at(1)->isChecked())
        opts |= AllowNestedDocks;
    if (actions.at(2)->isChecked())
        opts |= AllowTabbedDocks;
    if (actions.at(3)->isChecked())
        opts |= ForceTabbedDocks;
    if (actions.at(4)->isChecked())
        opts |= VerticalTabs;
    /*
    if (actions.at(5)->isChecked())
        opts |= GroupedDragging;
        */

    QMainWindow::setDockOptions(opts);
}

void MainWindow::saveLayout()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) {
        QString msg = tr("Error writing to %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void MainWindow::loadLayout()
{
    QString fileName
        = QFileDialog::getOpenFileName(this, tr("Load layout"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(QDir::toNativeSeparators(fileName), file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = restoreGeometry(geo_data);
    if (ok)
        ok = restoreState(layout_data);

    if (!ok) {
        QString msg = tr("Error reading %1").arg(QDir::toNativeSeparators(fileName));
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

class DockWidgetAreaCornerFunctor {
public:
    explicit DockWidgetAreaCornerFunctor(QMainWindow *mw, Qt::Corner c, Qt::DockWidgetArea a)
        : m_mainWindow(mw), m_area(a), m_corner(c) {}

    void operator()() const { m_mainWindow->setCorner(m_corner, m_area); }

private:
    QMainWindow *m_mainWindow;
    Qt::DockWidgetArea m_area;
    Qt::Corner m_corner;
};

static QAction *addCornerAction(const QString &text, QMainWindow *mw, QMenu *menu, QActionGroup *group,
                                Qt::Corner c, Qt::DockWidgetArea a)
{
    // QAction *result = menu->addAction(text, mw, DockWidgetAreaCornerFunctor(mw, c, a));
    QAction *result = menu->addAction(text, mw, SLOT(dummy()));
    result->setCheckable(true);
    group->addAction(result);
    return result;
}

void MainWindow::setupDockWidgets(const CustomSizeHintMap &customSizeHints)
{
    qRegisterMetaType<QDockWidget::DockWidgetFeatures>();

    QMenu *cornerMenu = dockWidgetMenu->addMenu(tr("Top left corner"));
    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);
    QAction *cornerAction = addCornerAction(tr("Top dock area"), this, cornerMenu, group, Qt::TopLeftCorner, Qt::TopDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("Left dock area"), this, cornerMenu, group, Qt::TopLeftCorner, Qt::LeftDockWidgetArea);

    cornerMenu = dockWidgetMenu->addMenu(tr("Top right corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    cornerAction = addCornerAction(tr("Top dock area"), this, cornerMenu, group, Qt::TopRightCorner, Qt::TopDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("Right dock area"), this, cornerMenu, group, Qt::TopRightCorner, Qt::RightDockWidgetArea);

    cornerMenu = dockWidgetMenu->addMenu(tr("Bottom left corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    cornerAction = addCornerAction(tr("Bottom dock area"), this, cornerMenu, group, Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("Left dock area"), this, cornerMenu, group, Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    cornerMenu = dockWidgetMenu->addMenu(tr("Bottom right corner"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    cornerAction = addCornerAction(tr("Bottom dock area"), this, cornerMenu, group, Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
    cornerAction->setChecked(true);
    addCornerAction(tr("Right dock area"), this, cornerMenu, group, Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    dockWidgetMenu->addSeparator();

    static const struct Set {
        const char * name;
        uint flags;
        Qt::DockWidgetArea area;
    } sets [] = {
#ifndef Q_OS_MAC
        { "Black", 0, Qt::LeftDockWidgetArea },
#else
        { "Black", Qt::Drawer, Qt::LeftDockWidgetArea },
#endif
        { "White", 0, Qt::RightDockWidgetArea },
        { "Red", 0, Qt::TopDockWidgetArea },
        { "Green", 0, Qt::TopDockWidgetArea },
        { "Blue", 0, Qt::BottomDockWidgetArea },
        { "Yellow", 0, Qt::BottomDockWidgetArea }
    };
    const int setCount = sizeof(sets) / sizeof(Set);

    const QIcon qtIcon(QPixmap(":/res/qt.png"));
    for (int i = 0; i < setCount; ++i) {
        ColorSwatch *swatch = new ColorSwatch(tr(sets[i].name), this, Qt::WindowFlags(sets[i].flags));
        if (i % 2)
            swatch->setWindowIcon(qtIcon);
        if (qstrcmp(sets[i].name, "Blue") == 0) {
            BlueTitleBar *titlebar = new BlueTitleBar(swatch);
            swatch->setTitleBarWidget(titlebar);
            connect(swatch, &QDockWidget::topLevelChanged, titlebar, &BlueTitleBar::updateMask);
            connect(swatch, &QDockWidget::featuresChanged, titlebar, &BlueTitleBar::updateMask, Qt::QueuedConnection);
        }

        QString name = QString::fromLatin1(sets[i].name);
        if (customSizeHints.contains(name))
            swatch->setCustomSizeHint(customSizeHints.value(name));

        addDockWidget(sets[i].area, swatch);
        dockWidgetMenu->addMenu(swatch->colorSwatchMenu());
    }

    destroyDockWidgetMenu = new QMenu(tr("Destroy dock widget"), this);
    destroyDockWidgetMenu->setEnabled(false);
    connect(destroyDockWidgetMenu, SIGNAL(triggered(QAction*)), this, SLOT(destroyDockWidget(QAction*)));

    dockWidgetMenu->addSeparator();
    dockWidgetMenu->addAction(tr("Add dock widget..."), this, SLOT(createDockWidget()));
    dockWidgetMenu->addMenu(destroyDockWidgetMenu);
}

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        QApplication::setLayoutDirection(Qt::RightToLeft);
    else
        QApplication::setLayoutDirection(Qt::LeftToRight);
}

class CreateDockWidgetDialog : public QDialog
{
public:
    explicit CreateDockWidgetDialog(QWidget *parent = Q_NULLPTR);

    QString enteredObjectName() const { return m_objectName->text(); }
    Qt::DockWidgetArea location() const;

private:
    QLineEdit *m_objectName;
    QComboBox *m_location;
};

CreateDockWidgetDialog::CreateDockWidgetDialog(QWidget *parent)
    : QDialog(parent)
    , m_objectName(new QLineEdit(this))
    , m_location(new QComboBox(this))
{
    setWindowTitle(tr("Add Dock Widget"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QGridLayout *layout = new QGridLayout(this);

    layout->addWidget(new QLabel(tr("Object name:")), 0, 0);
    layout->addWidget(m_objectName, 0, 1);

    layout->addWidget(new QLabel(tr("Location:")), 1, 0);
    m_location->setEditable(false);
    m_location->addItem(tr("Top"));
    m_location->addItem(tr("Left"));
    m_location->addItem(tr("Right"));
    m_location->addItem(tr("Bottom"));
    m_location->addItem(tr("Restore"));
    layout->addWidget(m_location, 1, 1);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout->addWidget(buttonBox, 2, 0, 1, 2);
}

Qt::DockWidgetArea CreateDockWidgetDialog::location() const
{
    switch (m_location->currentIndex()) {
        case 0: return Qt::TopDockWidgetArea;
        case 1: return Qt::LeftDockWidgetArea;
        case 2: return Qt::RightDockWidgetArea;
        case 3: return Qt::BottomDockWidgetArea;
        default:
            break;
    }
    return Qt::NoDockWidgetArea;
}

void MainWindow::createDockWidget()
{
    CreateDockWidgetDialog dialog(this);
    if (dialog.exec() == QDialog::Rejected)
        return;

    QDockWidget *dw = new QDockWidget;
    const QString name = dialog.enteredObjectName();
    dw->setObjectName(name);
    dw->setWindowTitle(name);
    dw->setWidget(new QTextEdit);

    Qt::DockWidgetArea area = dialog.location();
    switch (area) {
        case Qt::LeftDockWidgetArea:
        case Qt::RightDockWidgetArea:
        case Qt::TopDockWidgetArea:
        case Qt::BottomDockWidgetArea:
            addDockWidget(area, dw);
            break;
        default:
            if (!restoreDockWidget(dw)) {
                QMessageBox::warning(this, QString(), tr("Failed to restore dock widget"));
                delete dw;
                return;
            }
            break;
    }

    extraDockWidgets.append(dw);
    destroyDockWidgetMenu->setEnabled(true);
    destroyDockWidgetMenu->addAction(new QAction(name, this));
}

void MainWindow::destroyDockWidget(QAction *action)
{
    int index = destroyDockWidgetMenu->actions().indexOf(action);
    delete extraDockWidgets.takeAt(index);
    destroyDockWidgetMenu->removeAction(action);
    action->deleteLater();

    if (destroyDockWidgetMenu->isEmpty())
        destroyDockWidgetMenu->setEnabled(false);
}

void MainWindow::dummy()
{
    qDebug() << "dummy called";
}

void render_qt_text(QPainter *painter, int w, int h, const QColor &color)
{
    QPainterPath path;
    path.moveTo(-0.083695, 0.283849);
    path.cubicTo(-0.049581, 0.349613, -0.012720, 0.397969, 0.026886, 0.428917);
    path.cubicTo(0.066493, 0.459865, 0.111593, 0.477595, 0.162186, 0.482108);
    path.lineTo(0.162186, 0.500000);
    path.cubicTo(0.115929, 0.498066, 0.066565, 0.487669, 0.014094, 0.468810);
    path.cubicTo(-0.038378, 0.449952, -0.088103, 0.423839, -0.135082, 0.390474);
    path.cubicTo(-0.182061, 0.357108, -0.222608, 0.321567, -0.256722, 0.283849);
    path.cubicTo(-0.304712, 0.262250, -0.342874, 0.239362, -0.371206, 0.215184);
    path.cubicTo(-0.411969, 0.179078, -0.443625, 0.134671, -0.466175, 0.081963);
    path.cubicTo(-0.488725, 0.029255, -0.500000, -0.033043, -0.500000, -0.104932);
    path.cubicTo(-0.500000, -0.218407, -0.467042, -0.312621, -0.401127, -0.387573);
    path.cubicTo(-0.335212, -0.462524, -0.255421, -0.500000, -0.161752, -0.500000);
    path.cubicTo(-0.072998, -0.500000, 0.003903, -0.462444, 0.068951, -0.387331);
    path.cubicTo(0.133998, -0.312218, 0.166522, -0.217440, 0.166522, -0.102998);
    path.cubicTo(0.166522, -0.010155, 0.143394, 0.071325, 0.097138, 0.141441);
    path.cubicTo(0.050882, 0.211557, -0.009396, 0.259026, -0.083695, 0.283849);
    path.moveTo(-0.167823, -0.456963);
    path.cubicTo(-0.228823, -0.456963, -0.277826, -0.432624, -0.314831, -0.383946);
    path.cubicTo(-0.361665, -0.323340, -0.385082, -0.230335, -0.385082, -0.104932);
    path.cubicTo(-0.385082, 0.017569, -0.361376, 0.112025, -0.313964, 0.178433);
    path.cubicTo(-0.277248, 0.229368, -0.228534, 0.254836, -0.167823, 0.254836);
    path.cubicTo(-0.105088, 0.254836, -0.054496, 0.229368, -0.016045, 0.178433);
    path.cubicTo(0.029055, 0.117827, 0.051605, 0.028691, 0.051605, -0.088975);
    path.cubicTo(0.051605, -0.179562, 0.039318, -0.255803, 0.014744, -0.317698);
    path.cubicTo(-0.004337, -0.365409, -0.029705, -0.400548, -0.061362, -0.423114);
    path.cubicTo(-0.093018, -0.445680, -0.128505, -0.456963, -0.167823, -0.456963);
    path.moveTo(0.379011, -0.404739);
    path.lineTo(0.379011, -0.236460);
    path.lineTo(0.486123, -0.236460);
    path.lineTo(0.486123, -0.197292);
    path.lineTo(0.379011, -0.197292);
    path.lineTo(0.379011, 0.134913);
    path.cubicTo(0.379011, 0.168117, 0.383276, 0.190442, 0.391804, 0.201886);
    path.cubicTo(0.400332, 0.213330, 0.411246, 0.219052, 0.424545, 0.219052);
    path.cubicTo(0.435531, 0.219052, 0.446227, 0.215264, 0.456635, 0.207689);
    path.cubicTo(0.467042, 0.200113, 0.474993, 0.188910, 0.480486, 0.174081);
    path.lineTo(0.500000, 0.174081);
    path.cubicTo(0.488436, 0.210509, 0.471957, 0.237911, 0.450564, 0.256286);
    path.cubicTo(0.429170, 0.274662, 0.407054, 0.283849, 0.384215, 0.283849);
    path.cubicTo(0.368893, 0.283849, 0.353859, 0.279094, 0.339115, 0.269584);
    path.cubicTo(0.324371, 0.260074, 0.313530, 0.246534, 0.306592, 0.228965);
    path.cubicTo(0.299653, 0.211396, 0.296184, 0.184075, 0.296184, 0.147002);
    path.lineTo(0.296184, -0.197292);
    path.lineTo(0.223330, -0.197292);
    path.lineTo(0.223330, -0.215667);
    path.cubicTo(0.241833, -0.224049, 0.260697, -0.237992, 0.279922, -0.257495);
    path.cubicTo(0.299147, -0.276999, 0.316276, -0.300129, 0.331310, -0.326886);
    path.cubicTo(0.338826, -0.341070, 0.349523, -0.367021, 0.363400, -0.404739);
    path.lineTo(0.379011, -0.404739);
    path.moveTo(-0.535993, 0.275629);

    painter->translate(w / 2, h / 2);
    double scale = qMin(w, h) * 8 / 10.0;
    painter->scale(scale, scale);

    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    painter->translate(.1, .1);
    painter->fillPath(path, QColor(0, 0, 0, 63));
    painter->restore();

    painter->setBrush(color);
    painter->setPen(QPen(Qt::black, 0.02, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    painter->drawPath(path);
}

static void usage()
{
    qWarning() << "Usage: mainwindow [-SizeHint<color> <width>x<height>] ...";
    exit(1);
}

enum ParseCommandLineArgumentsResult {
    CommandLineArgumentsOk,
    CommandLineArgumentsError,
    HelpRequested
};

static ParseCommandLineArgumentsResult
    parseCustomSizeHints(const QStringList &arguments, MainWindow::CustomSizeHintMap *result)
{
    result->clear();
    const int argumentCount = arguments.size();
    for (int i = 1; i < argumentCount; ++i) {
        const QString &arg = arguments.at(i);
        if (arg.startsWith(QLatin1String("-SizeHint"))) {
            const QString name = arg.mid(9);
            if (name.isEmpty())
                return CommandLineArgumentsError;
            if (++i == argumentCount)
                return CommandLineArgumentsError;
            const QString sizeStr = arguments.at(i);
            const int idx = sizeStr.indexOf(QLatin1Char('x'));
            if (idx == -1)
                return CommandLineArgumentsError;
            bool ok;
            const int w = sizeStr.leftRef(idx).toInt(&ok);
            if (!ok)
                return CommandLineArgumentsError;
            const int h = sizeStr.midRef(idx + 1).toInt(&ok);
            if (!ok)
                return CommandLineArgumentsError;
            result->insert(name, QSize(w, h));
        } else if (arg == QLatin1String("-h") || arg == QLatin1String("--help")) {
            return HelpRequested;
        } else {
            return CommandLineArgumentsError;
        }
    }

    return CommandLineArgumentsOk;
}

#include "mainwindow.moc"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow::CustomSizeHintMap customSizeHints;
    switch (parseCustomSizeHints(QCoreApplication::arguments(), &customSizeHints)) {
    case CommandLineArgumentsOk:
        break;
    case CommandLineArgumentsError:
        usage();
        return -1;
    case HelpRequested:
        usage();
        return 0;
    }
    MainWindow mainWin(customSizeHints);
    mainWin.resize(800, 600);
    mainWin.show();
    return app.exec();
}
