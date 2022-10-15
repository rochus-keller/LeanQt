/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2014 Intel Corporation.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtCore module of the Qt Toolkit.
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
#include "qbytearray.h"
#include <QBuffer>
#include <QScopedPointer>
#include <thirdparty/zlib.h>
#include <QtDebug>

QT_BEGIN_NAMESPACE

QByteArray qCompress(const uchar* data, int nbytes, int compressionLevel)
{
    if (nbytes == 0) {
        return QByteArray(4, '\0');
    }
    if (!data) {
        qWarning("qCompress: Data is null");
        return QByteArray();
    }
    if (compressionLevel < -1 || compressionLevel > 9)
        compressionLevel = -1;

    ulong len = nbytes + nbytes / 100 + 13;
    QByteArray bazip;
    int res;
    do {
        bazip.resize(len + 4);
        res = ::compress2((uchar*)bazip.data()+4, &len, data, nbytes, compressionLevel);

        switch (res) {
        case Z_OK:
            bazip.resize(len + 4);
            bazip[0] = (nbytes & 0xff000000) >> 24;
            bazip[1] = (nbytes & 0x00ff0000) >> 16;
            bazip[2] = (nbytes & 0x0000ff00) >> 8;
            bazip[3] = (nbytes & 0x000000ff);
            break;
        case Z_MEM_ERROR:
            qWarning("qCompress: Z_MEM_ERROR: Not enough memory");
            bazip.resize(0);
            break;
        case Z_BUF_ERROR:
            len *= 2;
            break;
        }
    } while (res == Z_BUF_ERROR);

    return bazip;
}

QByteArray qUncompress(const uchar* data, int nbytes)
{
    if (!data) {
        qWarning("qUncompress: Data is null");
        return QByteArray();
    }
    if (nbytes <= 4) {
        if (nbytes < 4 || (data[0]!=0 || data[1]!=0 || data[2]!=0 || data[3]!=0))
            qWarning("qUncompress: Input data is corrupted");
        return QByteArray();
    }
    ulong expectedSize = uint((data[0] << 24) | (data[1] << 16) |
                              (data[2] <<  8) | (data[3]      ));
    ulong len = qMax(expectedSize, 1ul);
    QScopedPointer<QByteArray::Data, QScopedPointerPodDeleter> d;

    forever {
        ulong alloc = len;
        if (len  >= (1u << 31u) - sizeof(QByteArray::Data)) {
            //QByteArray does not support that huge size anyway.
            qWarning("qUncompress: Input data is corrupted");
            return QByteArray();
        }
        QByteArray::Data *p = static_cast<QByteArray::Data *>(::realloc(d.data(), sizeof(QByteArray::Data) + alloc + 1));
        if (!p) {
            // we are not allowed to crash here when compiling with QT_NO_EXCEPTIONS
            qWarning("qUncompress: could not allocate enough memory to uncompress data");
            return QByteArray();
        }
        d.take(); // realloc was successful
        d.reset(p);
        d->offset = sizeof(QByteArrayData);
        d->size = 0; // Shut up valgrind "uninitialized variable" warning

        int res = ::uncompress((uchar*)d->data(), &len,
                               data+4, nbytes-4);

        switch (res) {
        case Z_OK:
            if (len != alloc) {
                if (len  >= (1u << 31u) - sizeof(QByteArray::Data)) {
                    //QByteArray does not support that huge size anyway.
                    qWarning("qUncompress: Input data is corrupted");
                    return QByteArray();
                }
                QByteArray::Data *p = static_cast<QByteArray::Data *>(::realloc(d.data(), sizeof(QByteArray::Data) + len + 1));
                if (!p) {
                    // we are not allowed to crash here when compiling with QT_NO_EXCEPTIONS
                    qWarning("qUncompress: could not allocate enough memory to uncompress data");
                    return QByteArray();
                }
                d.take(); // realloc was successful
                d.reset(p);
            }
            d->ref.initializeOwned();
            d->size = len;
            d->alloc = uint(len) + 1u;
            d->capacityReserved = false;
            d->offset = sizeof(QByteArrayData);
            d->data()[len] = 0;

            {
                QByteArrayDataPtr dataPtr = { d.take() };
                return QByteArray(dataPtr);
            }

        case Z_MEM_ERROR:
            qWarning("qUncompress: Z_MEM_ERROR: Not enough memory");
            return QByteArray();

        case Z_BUF_ERROR:
            len *= 2;
            continue;

        case Z_DATA_ERROR:
            qWarning("qUncompress: Z_DATA_ERROR: Input data is corrupted");
            return QByteArray();
        }
    }
}

class QUncompressor::Imp
{
public:
    Imp(const QByteArray& dict = QByteArray())
    {
        this->dict = dict;
        inflateStrm.zalloc = Z_NULL;
        inflateStrm.zfree = Z_NULL;
        inflateStrm.opaque = Z_NULL;
        inflateStrm.avail_in = 0;
        inflateStrm.next_in = Z_NULL;
        // "windowBits can also be greater than 15 for optional gzip decoding.
        // Add 32 to windowBits to enable zlib and gzip decoding with automatic header detection"
        // http://www.zlib.net/manual.html
        int ret = Z_OK;
        if( !dict.isEmpty() )
            ret = inflateInit(&inflateStrm);
        else
            ret = inflateInit2(&inflateStrm, MAX_WBITS+32);
        Q_ASSERT(ret == Z_OK);
    }

    z_stream_s inflateStrm;
    QByteArray dict;
};

QUncompressor::QUncompressor(const QByteArray& dict):d(0)
{
    if( !dict.isEmpty() )
        d = new Imp(dict);
}

QUncompressor::~QUncompressor()
{
    reset();
}

QList<QByteArray> QUncompressor::process(QList<QByteArray> data)
{
    if (!d)
        d = new Imp();

    bool triedRawDeflate = false;
    QList<QByteArray> result;
    for (int i = 0; i < data.size(); i++) {
        QByteArray &bIn = data[i];

        d->inflateStrm.avail_in = bIn.size();
        d->inflateStrm.next_in = reinterpret_cast<Bytef*>(bIn.data());

        do {
            QByteArray bOut;
            // make a wild guess about the uncompressed size.
            bOut.reserve(d->inflateStrm.avail_in * 3 + 512);
            d->inflateStrm.avail_out = bOut.capacity();
            d->inflateStrm.next_out = reinterpret_cast<Bytef*>(bOut.data());

            int ret = inflate(&d->inflateStrm, Z_NO_FLUSH);
            //All negative return codes are errors, in the context of HTTP compression, Z_NEED_DICT is also an error.
            // in the case where we get Z_DATA_ERROR this could be because we received raw deflate compressed data.
            if (ret == Z_DATA_ERROR && !triedRawDeflate) {
                inflateEnd(&d->inflateStrm);
                triedRawDeflate = true;
                d->inflateStrm.zalloc = Z_NULL;
                d->inflateStrm.zfree = Z_NULL;
                d->inflateStrm.opaque = Z_NULL;
                d->inflateStrm.avail_in = 0;
                d->inflateStrm.next_in = Z_NULL;
                int ret = inflateInit2(&d->inflateStrm, -MAX_WBITS);
                if (ret != Z_OK) {
                    return QList<QByteArray>();
                } else {
                    d->inflateStrm.avail_in = bIn.size();
                    d->inflateStrm.next_in = reinterpret_cast<Bytef*>(bIn.data());
                    continue;
                }
            } else if (ret < 0 || ret == Z_NEED_DICT) {
                return QList<QByteArray>();
            }
            bOut.resize(bOut.capacity() - d->inflateStrm.avail_out);
            result.append(bOut);
            if (ret == Z_STREAM_END)
                return result;
        } while (d->inflateStrm.avail_in > 0);
    }

    return result;
}

bool QUncompressor::process2(const QByteArray& input, QByteArray& output)
{
    const size_t chunkSize = 1024;
    char outputRaw[chunkSize];
    // input bytes will not be changed by zlib, so it is safe to const_cast here
    d->inflateStrm.next_in = const_cast<Bytef *>(reinterpret_cast<const Bytef *>(input.constData()));
    d->inflateStrm.avail_in = input.count();
    d->inflateStrm.total_in = input.count();
    int zlibRet;

    do {
        d->inflateStrm.next_out = reinterpret_cast<Bytef *>(outputRaw);
        d->inflateStrm.avail_out = chunkSize;
        zlibRet = inflate(&d->inflateStrm, Z_SYNC_FLUSH);
        if (zlibRet == Z_NEED_DICT) {
            zlibRet = inflateSetDictionary(&d->inflateStrm,
                                           reinterpret_cast<const Bytef*>(d->dict.constData()),
                                           /* dictionaryLength = */ d->dict.size());
            Q_ASSERT(zlibRet == Z_OK);
            continue;
        }
        switch (zlibRet) {
        case Z_BUF_ERROR: {
            if (d->inflateStrm.avail_in == 0) {
                int outputSize = chunkSize - d->inflateStrm.avail_out;
                output.append(outputRaw, outputSize);
                d->inflateStrm.avail_out = chunkSize;
            }
            break;
        }
        case Z_OK: {
            int outputSize = chunkSize - d->inflateStrm.avail_out;
            output.append(outputRaw, outputSize);
            break;
        }
        default: {
            qWarning() << "got unexpected zlib return value:" << zlibRet;
            return false;
        }
        }
    } while (d->inflateStrm.avail_in > 0 && zlibRet != Z_STREAM_END);

    Q_ASSERT(d->inflateStrm.avail_in == 0);
    return true;
}

void QUncompressor::reset()
{
    if( d )
    {
        inflateEnd(&d->inflateStrm);
        d = 0;
    }
}

class QCompressor::Imp
{
public:
    Imp()
    {
        m_deflateStream.zalloc = Z_NULL;
        m_deflateStream.zfree = Z_NULL;
        m_deflateStream.opaque = Z_NULL;

        // Do actually not compress (i.e. compression level = 0)
        // when sending the headers because of the CRIME attack
        int zlibRet = deflateInit(&m_deflateStream, /* compression level = */ 0);
        Q_ASSERT(zlibRet == Z_OK);
        Q_UNUSED(zlibRet); // silence -Wunused-variable
    }

    z_stream_s m_deflateStream;
};

QCompressor::QCompressor()
{
    d = new Imp();
}

QCompressor::~QCompressor()
{
    deflateEnd(&d->m_deflateStream);
    delete d;
}

QByteArray QCompressor::process(const QByteArray& in)
{
    d->m_deflateStream.total_in = in.count();
    d->m_deflateStream.avail_in = in.count();
    d->m_deflateStream.next_in = const_cast<unsigned char*>(reinterpret_cast<const unsigned char *>(in.constData()));
    int outputBytes = in.count() + 30; // 30 bytes of compression header overhead
    d->m_deflateStream.avail_out = outputBytes;
    unsigned char *out = new unsigned char[outputBytes];
    d->m_deflateStream.next_out = out;
    int availOutBefore = d->m_deflateStream.avail_out;
    int zlibRet = deflate(&d->m_deflateStream, Z_SYNC_FLUSH); // do everything in one go since we use no compression
    int compressedHeaderSize = availOutBefore - d->m_deflateStream.avail_out;
    Q_ASSERT(zlibRet == Z_OK); // otherwise, we need to allocate more outputBytes
    Q_UNUSED(zlibRet); // silence -Wunused-variable
    Q_ASSERT(d->m_deflateStream.avail_in == 0);
    QByteArray compressedHeader(reinterpret_cast<char *>(out), compressedHeaderSize);
    delete[] out;

    return compressedHeader;
}

QT_END_NAMESPACE

