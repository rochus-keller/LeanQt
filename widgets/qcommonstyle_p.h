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

#ifndef QCOMMONSTYLE_P_H
#define QCOMMONSTYLE_P_H

#include "qcommonstyle.h"
#include "qstyle_p.h"

#include "qstyleoption.h"

QT_BEGIN_NAMESPACE

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of qapplication_*.cpp, qwidget*.cpp and qfiledialog.cpp.  This header
// file may change from version to version without notice, or even be removed.
//
// We mean it.
//

class QStringList;
class QStyleAnimation;

// Private class
class QCommonStylePrivate : public QStylePrivate
{
    Q_DECLARE_PUBLIC(QCommonStyle)
public:
    inline QCommonStylePrivate() :
#ifndef QT_NO_ITEMVIEWS
    cachedOption(0),
#endif
    animationFps(30)
    { }

    ~QCommonStylePrivate()
    {
#ifndef QT_NO_ANIMATION
        qDeleteAll(animations);
#endif
#ifndef QT_NO_ITEMVIEWS
        delete cachedOption;
#endif
    }

#ifndef QT_NO_ITEMVIEWS
    void viewItemDrawText(QPainter *p, const QStyleOptionViewItem *option, const QRect &rect) const;
    void viewItemLayout(const QStyleOptionViewItem *opt,  QRect *checkRect,
                        QRect *pixmapRect, QRect *textRect, bool sizehint) const;
    QSize viewItemSize(const QStyleOptionViewItem *option, int role) const;

    mutable QRect decorationRect, displayRect, checkRect;
    mutable QStyleOptionViewItem *cachedOption;
    bool isViewItemCached(const QStyleOptionViewItem &option) const {
        return cachedOption && (option.widget == cachedOption->widget
               && option.index == cachedOption->index
               && option.state == cachedOption->state
               && option.rect == cachedOption->rect
               && option.text == cachedOption->text
               && option.direction == cachedOption->direction
               && option.displayAlignment == cachedOption->displayAlignment
               && option.decorationAlignment == cachedOption->decorationAlignment
               && option.decorationPosition == cachedOption->decorationPosition
               && option.decorationSize == cachedOption->decorationSize
               && option.features == cachedOption->features
               && option.icon.isNull() == cachedOption->icon.isNull()
               && option.font == cachedOption->font
               && option.viewItemPosition == cachedOption->viewItemPosition);
    }
#endif
    mutable QIcon tabBarcloseButtonIcon;
#ifndef QT_NO_TABBAR
    void tabLayout(const QStyleOptionTab *opt, const QWidget *widget, QRect *textRect, QRect *pixmapRect) const;
#endif

    int animationFps;
#ifndef QT_NO_ANIMATION
    void _q_removeAnimation();

    QList<const QObject*> animationTargets() const;
    QStyleAnimation* animation(const QObject *target) const;
    void startAnimation(QStyleAnimation *animation) const;
    void stopAnimation(const QObject *target) const;

private:
    mutable QHash<const QObject*, QStyleAnimation*> animations;
#endif // QT_NO_ANIMATION
};

QT_END_NAMESPACE

#endif //QCOMMONSTYLE_P_H
