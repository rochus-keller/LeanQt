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

#ifndef QSTYLESHEETSTYLE_P_H
#define QSTYLESHEETSTYLE_P_H

#include "private/qwindowsstyle_p.h"

#ifndef QT_NO_STYLE_STYLESHEET

#include "QtWidgets/qstyleoption.h"
#include "QtCore/qhash.h"
#include "QtGui/qevent.h"
#include "QtCore/qvector.h"
#include "QtWidgets/qapplication.h"
#include "private/qcssparser_p.h"
#include "QtGui/qbrush.h"

QT_BEGIN_NAMESPACE

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

class QAbstractScrollArea;
class QStyleSheetStylePrivate;
class QStyleOptionTitleBar;

struct QStyleSheetBorderImageData : public QSharedData
{
    QStyleSheetBorderImageData()
        : horizStretch(QCss::TileMode_Unknown), vertStretch(QCss::TileMode_Unknown)
    {
        for (int i = 0; i < 4; i++)
            cuts[i] = -1;
    }
    int cuts[4];
    QPixmap pixmap;
    QImage image;
    QCss::TileMode horizStretch, vertStretch;
};

struct QStyleSheetBackgroundData : public QSharedData
{
    QStyleSheetBackgroundData(const QBrush& b, const QPixmap& p, QCss::Repeat r,
                              Qt::Alignment a, QCss::Origin o, QCss::Attachment t, QCss::Origin c)
        : brush(b), pixmap(p), repeat(r), position(a), origin(o), attachment(t), clip(c) { }

    bool isTransparent() const {
        if (brush.style() != Qt::NoBrush)
            return !brush.isOpaque();
        return pixmap.isNull() ? false : pixmap.hasAlpha();
    }
    QBrush brush;
    QPixmap pixmap;
    QCss::Repeat repeat;
    Qt::Alignment position;
    QCss::Origin origin;
    QCss::Attachment attachment;
    QCss::Origin clip;
};

struct QStyleSheetBorderData : public QSharedData
{
    QStyleSheetBorderData() : bi(0)
    {
        for (int i = 0; i < 4; i++) {
            borders[i] = 0;
            styles[i] = QCss::BorderStyle_None;
        }
    }

    QStyleSheetBorderData(int *b, QBrush *c, QCss::BorderStyle *s, QSize *r) : bi(0)
    {
        for (int i = 0; i < 4; i++) {
            borders[i] = b[i];
            styles[i] = s[i];
            colors[i] = c[i];
            radii[i] = r[i];
        }
    }

    int borders[4];
    QBrush colors[4];
    QCss::BorderStyle styles[4];
    QSize radii[4]; // topleft, topright, bottomleft, bottomright

    const QStyleSheetBorderImageData *borderImage() const
    { return bi; }
    bool hasBorderImage() const { return bi!=0; }

    QSharedDataPointer<QStyleSheetBorderImageData> bi;

    bool isOpaque() const
    {
        for (int i = 0; i < 4; i++) {
            if (styles[i] == QCss::BorderStyle_Native || styles[i] == QCss::BorderStyle_None)
                continue;
            if (styles[i] >= QCss::BorderStyle_Dotted && styles[i] <= QCss::BorderStyle_DotDotDash
                && styles[i] != QCss::BorderStyle_Solid)
                return false;
            if (!colors[i].isOpaque())
                return false;
            if (!radii[i].isEmpty())
                return false;
        }
        if (bi != 0 && bi->pixmap.hasAlpha())
            return false;
        return true;
    }
};


struct QStyleSheetOutlineData : public QStyleSheetBorderData
{
    QStyleSheetOutlineData()
    {
        for (int i = 0; i < 4; i++) {
            offsets[i] = 0;
        }
    }

    QStyleSheetOutlineData(int *b, QBrush *c, QCss::BorderStyle *s, QSize *r, int *o)
            : QStyleSheetBorderData(b, c, s, r)
    {
        for (int i = 0; i < 4; i++) {
            offsets[i] = o[i];
        }
    }

    int offsets[4];
};

struct QStyleSheetBoxData : public QSharedData
{
    QStyleSheetBoxData(int *m, int *p, int s) : spacing(s)
    {
        for (int i = 0; i < 4; i++) {
            margins[i] = m[i];
            paddings[i] = p[i];
        }
    }

    int margins[4];
    int paddings[4];

    int spacing;
};

struct QStyleSheetPaletteData : public QSharedData
{
    QStyleSheetPaletteData(const QBrush &fg, const QBrush &sfg, const QBrush &sbg,
                           const QBrush &abg)
        : foreground(fg), selectionForeground(sfg), selectionBackground(sbg),
          alternateBackground(abg) { }

    QBrush foreground;
    QBrush selectionForeground;
    QBrush selectionBackground;
    QBrush alternateBackground;
};

struct QStyleSheetGeometryData : public QSharedData
{
    QStyleSheetGeometryData(int w, int h, int minw, int minh, int maxw, int maxh)
        : minWidth(minw), minHeight(minh), width(w), height(h), maxWidth(maxw), maxHeight(maxh) { }

    int minWidth, minHeight, width, height, maxWidth, maxHeight;
};

struct QStyleSheetPositionData : public QSharedData
{
    QStyleSheetPositionData(int l, int t, int r, int b, QCss::Origin o, Qt::Alignment p, QCss::PositionMode m, Qt::Alignment a = 0)
        : left(l), top(t), bottom(b), right(r), origin(o), position(p), mode(m), textAlignment(a) { }

    int left, top, bottom, right;
    QCss::Origin origin;
    Qt::Alignment position;
    QCss::PositionMode mode;
    Qt::Alignment textAlignment;
};

struct QStyleSheetImageData : public QSharedData
{
    QStyleSheetImageData(const QIcon &i, Qt::Alignment a, const QSize &sz)
        : icon(i), alignment(a), size(sz) { }

    QIcon icon;
    Qt::Alignment alignment;
    QSize size;
};
class QRenderRule
{
public:
    QRenderRule() : features(0), hasFont(false), pal(0), b(0), bg(0), bd(0), ou(0), geo(0), p(0), img(0), clipset(0) { }
    QRenderRule(const QVector<QCss::Declaration> &, const QObject *);

    QRect borderRect(const QRect &r) const;
    QRect outlineRect(const QRect &r) const;
    QRect paddingRect(const QRect &r) const;
    QRect contentsRect(const QRect &r) const;

    enum { Margin = 1, Border = 2, Padding = 4, All=Margin|Border|Padding };
    QRect boxRect(const QRect &r, int flags = All) const;
    QSize boxSize(const QSize &s, int flags = All) const;
    QRect originRect(const QRect &rect, QCss::Origin origin) const;

    QPainterPath borderClip(QRect rect);
    void drawBorder(QPainter *, const QRect&);
    void drawOutline(QPainter *, const QRect&);
    void drawBorderImage(QPainter *, const QRect&);
    void drawBackground(QPainter *, const QRect&, const QPoint& = QPoint(0, 0));
    void drawBackgroundImage(QPainter *, const QRect&, QPoint = QPoint(0, 0));
    void drawFrame(QPainter *, const QRect&);
    void drawImage(QPainter *p, const QRect &rect);
    void drawRule(QPainter *, const QRect&);
    void configurePalette(QPalette *, QPalette::ColorGroup, const QWidget *, bool);
    void configurePalette(QPalette *p, QPalette::ColorRole fr, QPalette::ColorRole br);

    const QStyleSheetPaletteData *palette() const { return pal; }
    const QStyleSheetBoxData *box() const { return b; }
    const QStyleSheetBackgroundData *background() const { return bg; }
    const QStyleSheetBorderData *border() const { return bd; }
    const QStyleSheetOutlineData *outline() const { return ou; }
    const QStyleSheetGeometryData *geometry() const { return geo; }
    const QStyleSheetPositionData *position() const { return p; }

    bool hasPalette() const { return pal != 0; }
    bool hasBackground() const { return bg != 0 && (!bg->pixmap.isNull() || bg->brush.style() != Qt::NoBrush); }
    bool hasGradientBackground() const { return bg && bg->brush.style() >= Qt::LinearGradientPattern
                                                   && bg->brush.style() <= Qt::ConicalGradientPattern; }

    bool hasNativeBorder() const {
        return bd == 0
               || (!bd->hasBorderImage() && bd->styles[0] == QCss::BorderStyle_Native);
    }

    bool hasNativeOutline() const {
        return (ou == 0
                || (!ou->hasBorderImage() && ou->styles[0] == QCss::BorderStyle_Native));
    }

    bool baseStyleCanDraw() const {
        if (!hasBackground() || (background()->brush.style() == Qt::NoBrush && bg->pixmap.isNull()))
            return true;
        if (bg && !bg->pixmap.isNull())
            return false;
        if (hasGradientBackground())
            return features & QCss::StyleFeature_BackgroundGradient;
        return features & QCss::StyleFeature_BackgroundColor;
    }

    bool hasBox() const { return b != 0; }
    bool hasBorder() const { return bd != 0; }
    bool hasOutline() const { return ou != 0; }
    bool hasPosition() const { return p != 0; }
    bool hasGeometry() const { return geo != 0; }
    bool hasDrawable() const { return !hasNativeBorder() || hasBackground() || hasImage(); }
    bool hasImage() const { return img != 0; }

    QSize minimumContentsSize() const
    { return geo ? QSize(geo->minWidth, geo->minHeight) : QSize(0, 0); }
    QSize minimumSize() const
    { return boxSize(minimumContentsSize()); }

    QSize contentsSize() const
    { return geo ? QSize(geo->width, geo->height)
                 : ((img && img->size.isValid()) ? img->size : QSize()); }
    QSize contentsSize(const QSize &sz) const
    {
        QSize csz = contentsSize();
        if (csz.width() == -1) csz.setWidth(sz.width());
        if (csz.height() == -1) csz.setHeight(sz.height());
        return csz;
    }
    bool hasContentsSize() const
    { return (geo && (geo->width != -1 || geo->height != -1)) || (img && img->size.isValid()); }

    QSize size() const { return boxSize(contentsSize()); }
    QSize size(const QSize &sz) const { return boxSize(contentsSize(sz)); }
    QSize adjustSize(const QSize &sz)
    {
        if (!geo)
            return sz;
        QSize csz = contentsSize();
        if (csz.width() == -1) csz.setWidth(sz.width());
        if (csz.height() == -1) csz.setHeight(sz.height());
        if (geo->maxWidth != -1 && csz.width() > geo->maxWidth) csz.setWidth(geo->maxWidth);
        if (geo->maxHeight != -1 && csz.height() > geo->maxHeight) csz.setHeight(geo->maxHeight);
        csz=csz.expandedTo(QSize(geo->minWidth, geo->minHeight));
        return csz;
    }

    bool hasStyleHint(const QString &sh) const { return styleHints.contains(sh); }
    QVariant styleHint(const QString &sh) const { return styleHints.value(sh); }

    void fixupBorder(int);

    // Shouldn't be here
    void setClip(QPainter *p, const QRect &rect);
    void unsetClip(QPainter *);

public:
    int features;
    QBrush defaultBackground;
    QFont font;
    bool hasFont;

    QHash<QString, QVariant> styleHints;

    QSharedDataPointer<QStyleSheetPaletteData> pal;
    QSharedDataPointer<QStyleSheetBoxData> b;
    QSharedDataPointer<QStyleSheetBackgroundData> bg;
    QSharedDataPointer<QStyleSheetBorderData> bd;
    QSharedDataPointer<QStyleSheetOutlineData> ou;
    QSharedDataPointer<QStyleSheetGeometryData> geo;
    QSharedDataPointer<QStyleSheetPositionData> p;
    QSharedDataPointer<QStyleSheetImageData> img;

    int clipset;
    QPainterPath clipPath;
};
Q_DECLARE_TYPEINFO(QRenderRule, Q_MOVABLE_TYPE);

class Q_AUTOTEST_EXPORT QStyleSheetStyle : public QWindowsStyle
{
    typedef QWindowsStyle ParentStyle;

    Q_OBJECT
public:
    QStyleSheetStyle(QStyle *baseStyle);
    ~QStyleSheetStyle();

    void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
                            const QWidget *w = 0) const Q_DECL_OVERRIDE;
    void drawControl(ControlElement element, const QStyleOption *opt, QPainter *p,
                     const QWidget *w = 0) const Q_DECL_OVERRIDE;
    void drawItemPixmap(QPainter *painter, const QRect &rect, int alignment, const QPixmap &pixmap) const Q_DECL_OVERRIDE;
    void drawItemText(QPainter *painter, const QRect& rect, int alignment, const QPalette &pal,
              bool enabled, const QString& text, QPalette::ColorRole textRole  = QPalette::NoRole) const Q_DECL_OVERRIDE;
    void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                       const QWidget *w = 0) const Q_DECL_OVERRIDE;
    QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap,
                                const QStyleOption *option) const Q_DECL_OVERRIDE;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *opt,
                                     const QPoint &pt, const QWidget *w = 0) const Q_DECL_OVERRIDE;
    QRect itemPixmapRect(const QRect &rect, int alignment, const QPixmap &pixmap) const Q_DECL_OVERRIDE;
    QRect itemTextRect(const QFontMetrics &metrics, const QRect &rect, int alignment, bool enabled,
                       const QString &text) const Q_DECL_OVERRIDE;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = 0, const QWidget *widget = 0) const Q_DECL_OVERRIDE;
    void polish(QWidget *widget) Q_DECL_OVERRIDE;
    void polish(QApplication *app) Q_DECL_OVERRIDE;
    void polish(QPalette &pal) Q_DECL_OVERRIDE;
    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt,
                           const QSize &contentsSize, const QWidget *widget = 0) const Q_DECL_OVERRIDE;
    QPalette standardPalette() const Q_DECL_OVERRIDE;
    QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *opt = 0,
                       const QWidget *widget = 0) const Q_DECL_OVERRIDE;
    QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *option = 0,
                           const QWidget *w = 0 ) const Q_DECL_OVERRIDE;
    int layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2,
                          Qt::Orientation orientation, const QStyleOption *option = 0,
                          const QWidget *widget = 0) const Q_DECL_OVERRIDE;
    int styleHint(StyleHint sh, const QStyleOption *opt = 0, const QWidget *w = 0,
                  QStyleHintReturn *shret = 0) const Q_DECL_OVERRIDE;
    QRect subElementRect(SubElement r, const QStyleOption *opt, const QWidget *widget = 0) const Q_DECL_OVERRIDE;
    QRect subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
                         const QWidget *w = 0) const Q_DECL_OVERRIDE;

    // These functions are called from QApplication/QWidget. Be careful.
    QStyle *baseStyle() const;
    void repolish(QWidget *widget);
    void repolish(QApplication *app);

    void unpolish(QWidget *widget) Q_DECL_OVERRIDE;
    void unpolish(QApplication *app) Q_DECL_OVERRIDE;

    QStyle *base;
    void ref() { ++refcount; }
    void deref() { Q_ASSERT(refcount > 0); if (!--refcount) delete this; }

    void updateStyleSheetFont(QWidget* w) const;
    void saveWidgetFont(QWidget* w, const QFont& font) const;
    void clearWidgetFont(QWidget* w) const;

    bool styleSheetPalette(const QWidget* w, const QStyleOption* opt, QPalette* pal);

protected:
    bool event(QEvent *e) Q_DECL_OVERRIDE;

private:
    int refcount;

    friend class QRenderRule;
    int nativeFrameWidth(const QWidget *);
    QRenderRule renderRule(const QObject *, int, quint64 = 0) const;
    QRenderRule renderRule(const QObject *, const QStyleOption *, int = 0) const;
    QSize defaultSize(const QWidget *, QSize, const QRect&, int) const;
    QRect positionRect(const QWidget *, const QRenderRule&, const QRenderRule&, int,
                       const QRect&, Qt::LayoutDirection) const;
    QRect positionRect(const QWidget *w, const QRenderRule &rule2, int pe,
                       const QRect &originRect, Qt::LayoutDirection dir) const;

    mutable QCss::Parser parser;

    void setPalette(QWidget *);
    void unsetPalette(QWidget *);
    void setProperties(QWidget *);
    void setGeometry(QWidget *);
    QVector<QCss::StyleRule> styleRules(const QObject *obj) const;
    bool hasStyleRule(const QObject *obj, int part) const;

    QHash<QStyle::SubControl, QRect> titleBarLayout(const QWidget *w, const QStyleOptionTitleBar *tb) const;

    QCss::StyleSheet getDefaultStyleSheet() const;

    static Qt::Alignment resolveAlignment(Qt::LayoutDirection, Qt::Alignment);
    static bool isNaturalChild(const QObject *obj);
    bool initObject(const QObject *obj) const;
public:
    static int numinstances;

private:
    Q_DISABLE_COPY(QStyleSheetStyle)
    Q_DECLARE_PRIVATE(QStyleSheetStyle)
};

class QStyleSheetStyleCaches : public QObject
{
    Q_OBJECT
public Q_SLOTS:
    void objectDestroyed(QObject *);
    void styleDestroyed(QObject *);
public:
    QHash<const QObject *, QVector<QCss::StyleRule> > styleRulesCache;
    QHash<const QObject *, QHash<int, bool> > hasStyleRuleCache;
    typedef QHash<int, QHash<quint64, QRenderRule> > QRenderRules;
    QHash<const QObject *, QRenderRules> renderRulesCache;
    QHash<const QWidget *, QPalette> customPaletteWidgets; // widgets whose palette we tampered
    QHash<const void *, QCss::StyleSheet> styleSheetCache; // parsed style sheets
    QSet<const QWidget *> autoFillDisabledWidgets;
};


QT_END_NAMESPACE
#endif // QT_NO_STYLE_STYLESHEET
#endif // QSTYLESHEETSTYLE_P_H
