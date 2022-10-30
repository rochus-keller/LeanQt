/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
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

#include "qvectorpath_p.h"
#include <private/qpainterpath_p.h>

// moved here from qpaintengineex.cpp

QT_BEGIN_NAMESPACE

QVectorPath::~QVectorPath()
{
#ifndef QT_NO_GUI
    if (m_hints & ShouldUseCacheHint) {
        CacheEntry *e = m_cache;
        while (e) {
            if (e->data)
                e->cleanup(e->engine, e->data);
            CacheEntry *n = e->next;
            delete e;
            e = n;
        }
    }
#endif
}


QRectF QVectorPath::controlPointRect() const
{
    if (m_hints & ControlPointRect)
        return QRectF(QPointF(m_cp_rect.x1, m_cp_rect.y1), QPointF(m_cp_rect.x2, m_cp_rect.y2));

    if (m_count == 0) {
        m_cp_rect.x1 = m_cp_rect.x2 = m_cp_rect.y1 = m_cp_rect.y2 = 0;
        m_hints |= ControlPointRect;
        return QRectF(QPointF(m_cp_rect.x1, m_cp_rect.y1), QPointF(m_cp_rect.x2, m_cp_rect.y2));
    }
    Q_ASSERT(m_points && m_count > 0);

    const qreal *pts = m_points;
    m_cp_rect.x1 = m_cp_rect.x2 = *pts;
    ++pts;
    m_cp_rect.y1 = m_cp_rect.y2 = *pts;
    ++pts;

    const qreal *epts = m_points + (m_count << 1);
    while (pts < epts) {
        qreal x = *pts;
        if (x < m_cp_rect.x1) m_cp_rect.x1 = x;
        else if (x > m_cp_rect.x2) m_cp_rect.x2 = x;
        ++pts;

        qreal y = *pts;
        if (y < m_cp_rect.y1) m_cp_rect.y1 = y;
        else if (y > m_cp_rect.y2) m_cp_rect.y2 = y;
        ++pts;
    }

    m_hints |= ControlPointRect;
    return QRectF(QPointF(m_cp_rect.x1, m_cp_rect.y1), QPointF(m_cp_rect.x2, m_cp_rect.y2));
}


#ifndef QT_NO_GUI
QVectorPath::CacheEntry *QVectorPath::addCacheData(QPaintEngineEx *engine, void *data,
                                                   qvectorpath_cache_cleanup cleanup) const{
    Q_ASSERT(!lookupCacheData(engine));
    if ((m_hints & IsCachedHint) == 0) {
        m_cache = 0;
        m_hints |= IsCachedHint;
    }
    CacheEntry *e = new CacheEntry;
    e->engine = engine;
    e->data = data;
    e->cleanup = cleanup;
    e->next = m_cache;
    m_cache = e;
    return m_cache;
}
#endif


const QVectorPath &qtVectorPathForPath(const QPainterPath &path)
{
    Q_ASSERT(path.d_func());
    return path.d_func()->vectorPath();
}

#ifndef QT_NO_DEBUG_STREAM
QDebug Q_GUI_EXPORT &operator<<(QDebug &s, const QVectorPath &path)
{
    QRectF rf = path.controlPointRect();
    s << "QVectorPath(size:" << path.elementCount()
      << " hints:" << hex << path.hints()
      << rf << ')';
    return s;
}
#endif

QT_END_NAMESPACE
