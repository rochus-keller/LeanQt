#ifndef QMOVIE_P_H
#define QMOVIE_P_H


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

#include "qmovie.h"
#include "qimage.h"
#include "qimagereader.h"
#include "qpixmap.h"
#include "qrect.h"
#include "qdatetime.h"
#include "qtimer.h"
#include "qpair.h"
#include "qmap.h"
#include "qlist.h"
#include "qbuffer.h"
#include "qdir.h"
#include "private/qobject_p.h"

QT_BEGIN_NAMESPACE

#define QMOVIE_INVALID_DELAY -1

class QFrameInfo
{
public:
    QPixmap pixmap;
    int delay;
    bool endMark;
    inline QFrameInfo(bool endMark)
        : pixmap(QPixmap()), delay(QMOVIE_INVALID_DELAY), endMark(endMark)
    { }

    inline QFrameInfo()
        : pixmap(QPixmap()), delay(QMOVIE_INVALID_DELAY), endMark(false)
    { }

    inline QFrameInfo(const QPixmap &pixmap, int delay)
        : pixmap(pixmap), delay(delay), endMark(false)
    { }

    inline bool isValid()
    {
        return endMark || !(pixmap.isNull() && (delay == QMOVIE_INVALID_DELAY));
    }

    inline bool isEndMarker()
    { return endMark; }

    static inline QFrameInfo endMarker()
    { return QFrameInfo(true); }
};

class QMoviePrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QMovie)

public:
    QMoviePrivate(QMovie *qq);
    bool isDone();
    bool next();
    int speedAdjustedDelay(int delay) const;
    bool isValid() const;
    bool jumpToFrame(int frameNumber);
    int frameCount() const;
    bool jumpToNextFrame();
    QFrameInfo infoForFrame(int frameNumber);
    void reset();

    inline void enterState(QMovie::MovieState newState) {
        movieState = newState;
        emit q_func()->stateChanged(newState);
    }

    // private slots
    void _q_loadNextFrame();
    void _q_loadNextFrame(bool starting);

    QImageReader *reader;
    int speed;
    QMovie::MovieState movieState;
    QRect frameRect;
    QPixmap currentPixmap;
    int currentFrameNumber;
    int nextFrameNumber;
    int greatestFrameNumber;
    int nextDelay;
    int playCounter;
    qint64 initialDevicePos;
    QMovie::CacheMode cacheMode;
    bool haveReadAll;
    bool isFirstIteration;
    QMap<int, QFrameInfo> frameMap;
    QString absoluteFilePath;

    QTimer nextImageTimer;
};

QT_END_NAMESPACE

#endif
