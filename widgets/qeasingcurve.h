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

#ifndef QEASINGCURVE_H
#define QEASINGCURVE_H

#include <QtCore/qglobal.h>
#include <QtCore/qobjectdefs.h>
#include <QtCore/qvector.h>
#include <QMetaType>
#if QT_DEPRECATED_SINCE(5, 0)
# include <QtCore/qlist.h>
# include <QtCore/qpoint.h>
#endif

QT_BEGIN_NAMESPACE


class QEasingCurvePrivate;
class QPointF;

class Q_WIDGETS_EXPORT QEasingCurve
{
    Q_GADGET
public:
    enum Type {
        Linear,
        InQuad, OutQuad, InOutQuad, OutInQuad,
        InCubic, OutCubic, InOutCubic, OutInCubic,
        InQuart, OutQuart, InOutQuart, OutInQuart,
        InQuint, OutQuint, InOutQuint, OutInQuint,
        InSine, OutSine, InOutSine, OutInSine,
        InExpo, OutExpo, InOutExpo, OutInExpo,
        InCirc, OutCirc, InOutCirc, OutInCirc,
        InElastic, OutElastic, InOutElastic, OutInElastic,
        InBack, OutBack, InOutBack, OutInBack,
        InBounce, OutBounce, InOutBounce, OutInBounce,
        InCurve, OutCurve, SineCurve, CosineCurve,
        BezierSpline, TCBSpline, Custom, NCurveTypes
    };
    Q_ENUM(Type)

    QEasingCurve(Type type = Linear);
    QEasingCurve(const QEasingCurve &other);
    ~QEasingCurve();

    QEasingCurve &operator=(const QEasingCurve &other)
    { if ( this != &other ) { QEasingCurve copy(other); swap(copy); } return *this; }
#ifdef Q_COMPILER_RVALUE_REFS
    QEasingCurve(QEasingCurve &&other) : d_ptr(other.d_ptr) { other.d_ptr = Q_NULLPTR; }
    QEasingCurve &operator=(QEasingCurve &&other)
    { qSwap(d_ptr, other.d_ptr); return *this; }
#endif

    inline void swap(QEasingCurve &other) { qSwap(d_ptr, other.d_ptr); }

    bool operator==(const QEasingCurve &other) const;
    inline bool operator!=(const QEasingCurve &other) const
    { return !(this->operator==(other)); }

    qreal amplitude() const;
    void setAmplitude(qreal amplitude);

    qreal period() const;
    void setPeriod(qreal period);

    qreal overshoot() const;
    void setOvershoot(qreal overshoot);

    void addCubicBezierSegment(const QPointF & c1, const QPointF & c2, const QPointF & endPoint);
    void addTCBSegment(const QPointF &nextPoint, qreal t, qreal c, qreal b);
    QVector<QPointF> toCubicSpline() const;
#if QT_DEPRECATED_SINCE(5, 0)
    QT_DEPRECATED QList<QPointF> cubicBezierSpline() const { return toCubicSpline().toList(); }
#endif

    Type type() const;
    void setType(Type type);
    typedef qreal (*EasingFunction)(qreal progress);
    void setCustomType(EasingFunction func);
    EasingFunction customType() const;

    qreal valueForProgress(qreal progress) const;
private:
    QEasingCurvePrivate *d_ptr;
#ifndef QT_NO_DEBUG_STREAM
    friend Q_WIDGETS_EXPORT QDebug operator<<(QDebug debug, const QEasingCurve &item);
#endif
#ifndef QT_NO_DATASTREAM
    friend Q_WIDGETS_EXPORT QDataStream &operator<<(QDataStream &, const QEasingCurve&);
    friend Q_WIDGETS_EXPORT QDataStream &operator>>(QDataStream &, QEasingCurve &);
#endif
};
Q_DECLARE_TYPEINFO(QEasingCurve, Q_MOVABLE_TYPE);

#ifndef QT_NO_DEBUG_STREAM
Q_WIDGETS_EXPORT QDebug operator<<(QDebug debug, const QEasingCurve &item);
#endif

#ifndef QT_NO_DATASTREAM
Q_WIDGETS_EXPORT QDataStream &operator<<(QDataStream &, const QEasingCurve&);
Q_WIDGETS_EXPORT QDataStream &operator>>(QDataStream &, QEasingCurve &);
#endif

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QEasingCurve)

#endif
