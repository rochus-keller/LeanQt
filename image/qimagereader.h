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

#ifndef QIMAGEREADER_H
#define QIMAGEREADER_H

#include <QtCore/qbytearray.h>
#ifndef QT_NO_COREAPPLICATION
#include <QtCore/qcoreapplication.h>
#endif
#include <QtGui/qimage.h>
#include <QtGui/qimageiohandler.h>

QT_BEGIN_NAMESPACE


class QColor;
class QIODevice;
class QRect;
class QSize;
class QStringList;

class QImageReaderPrivate;
class Q_GUI_EXPORT QImageReader
{
public:
#ifndef QT_NO_COREAPPLICATION
    Q_DECLARE_TR_FUNCTIONS(QImageReader)
#else
    static QString tr(const char* text) { return QString::fromUtf8(text); }
#endif
public:
    enum ImageReaderError {
        UnknownError,
        FileNotFoundError,
        DeviceError,
        UnsupportedFormatError,
        InvalidDataError
    };

    QImageReader();
    explicit QImageReader(QIODevice *device, const QByteArray &format = QByteArray());
#ifndef QT_NO_FILEENGINE
    explicit QImageReader(const QString &fileName, const QByteArray &format = QByteArray());
#endif
    ~QImageReader();

    void setFormat(const QByteArray &format);
    QByteArray format() const;

    void setAutoDetectImageFormat(bool enabled);
    bool autoDetectImageFormat() const;

    void setDecideFormatFromContent(bool ignored);
    bool decideFormatFromContent() const;

    void setDevice(QIODevice *device);
    QIODevice *device() const;

    void setFileName(const QString &fileName);
    QString fileName() const;

    QSize size() const;

    QImage::Format imageFormat() const;

    QStringList textKeys() const;
    QString text(const QString &key) const;

    void setClipRect(const QRect &rect);
    QRect clipRect() const;

    void setScaledSize(const QSize &size);
    QSize scaledSize() const;

    void setQuality(int quality);
    int quality() const;

    void setScaledClipRect(const QRect &rect);
    QRect scaledClipRect() const;

    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    bool supportsAnimation() const;

    QImageIOHandler::Transformations transformation() const;

    void setAutoTransform(bool enabled);
    bool autoTransform() const;

    void setGamma(float gamma);
    float gamma() const;

    QByteArray subType() const;
    QList<QByteArray> supportedSubTypes() const;

    bool canRead() const;
    QImage read();
    bool read(QImage *image);

    bool jumpToNextImage();
    bool jumpToImage(int imageNumber);
    int loopCount() const;
    int imageCount() const;
    int nextImageDelay() const;
    int currentImageNumber() const;
    QRect currentImageRect() const;

    ImageReaderError error() const;
    QString errorString() const;

    bool supportsOption(QImageIOHandler::ImageOption option) const;

    static QByteArray imageFormat(const QString &fileName);
    static QByteArray imageFormat(QIODevice *device);
    static QList<QByteArray> supportedImageFormats();
    static QList<QByteArray> supportedMimeTypes();

private:
    Q_DISABLE_COPY(QImageReader)
    QImageReaderPrivate *d;
};

QT_END_NAMESPACE

#endif // QIMAGEREADER_H
