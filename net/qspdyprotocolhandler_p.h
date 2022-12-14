/****************************************************************************
**
** Copyright (C) 2014 BlackBerry Limited. All rights reserved.
** Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
**
** This file is part of the QtNetwork module of the Qt Toolkit.
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

#ifndef QSPDYPROTOCOLHANDLER_H
#define QSPDYPROTOCOLHANDLER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the Network Access API.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <private/qabstractprotocolhandler_p.h>
#include <QtNetwork/qnetworkreply.h>
#include <private/qbytedata_p.h>

#if !defined(QT_NO_HTTP) && !defined(QT_NO_SSL)

QT_BEGIN_NAMESPACE

class QHttpNetworkRequest;

#ifndef HttpMessagePair
typedef QPair<QHttpNetworkRequest, QHttpNetworkReply*> HttpMessagePair;
#endif

class QSpdyProtocolHandler : public QObject, public QAbstractProtocolHandler {
    Q_OBJECT
public:
    QSpdyProtocolHandler(QHttpNetworkConnectionChannel *channel);
    ~QSpdyProtocolHandler();

    enum DataFrameFlag {
        DataFrame_FLAG_FIN = 0x01,
        DataFrame_FLAG_COMPRESS = 0x02
    };

    Q_DECLARE_FLAGS(DataFrameFlags, DataFrameFlag)

    enum ControlFrameFlag {
        ControlFrame_FLAG_FIN = 0x01,
        ControlFrame_FLAG_UNIDIRECTIONAL = 0x02
    };

    Q_DECLARE_FLAGS(ControlFrameFlags, ControlFrameFlag)

    enum SETTINGS_Flag {
        FLAG_SETTINGS_CLEAR_SETTINGS = 0x01
    };

    Q_DECLARE_FLAGS(SETTINGS_Flags, SETTINGS_Flag)

    enum SETTINGS_ID_Flag {
        FLAG_SETTINGS_PERSIST_VALUE = 0x01,
        FLAG_SETTINGS_PERSISTED = 0x02
    };

    Q_DECLARE_FLAGS(SETTINGS_ID_Flags, SETTINGS_ID_Flag)

    virtual void _q_receiveReply() Q_DECL_OVERRIDE;
    virtual void _q_readyRead() Q_DECL_OVERRIDE;
    virtual bool sendRequest() Q_DECL_OVERRIDE;

private slots:
    void _q_uploadDataReadyRead();
    void _q_replyDestroyed(QObject*);

private:

    enum FrameType {
        FrameType_SYN_STREAM = 1,
        FrameType_SYN_REPLY = 2,
        FrameType_RST_STREAM = 3,
        FrameType_SETTINGS = 4,
        FrameType_PING = 6,
        FrameType_GOAWAY = 7,
        FrameType_HEADERS = 8,
        FrameType_WINDOW_UPDATE = 9,
        FrameType_CREDENTIAL // has a special type
    };

    enum StatusCode {
        StatusCode_PROTOCOL_ERROR = 1,
        StatusCode_INVALID_STREAM = 2,
        StatusCode_REFUSED_STREAM = 3,
        StatusCode_UNSUPPORTED_VERSION = 4,
        StatusCode_CANCEL = 5,
        StatusCode_INTERNAL_ERROR = 6,
        StatusCode_FLOW_CONTROL_ERROR = 7,
        StatusCode_STREAM_IN_USE = 8,
        StatusCode_STREAM_ALREADY_CLOSED = 9,
        StatusCode_INVALID_CREDENTIALS = 10,
        StatusCode_FRAME_TOO_LARGE = 11
    };

    enum SETTINGS_ID {
        SETTINGS_UPLOAD_BANDWIDTH = 1,
        SETTINGS_DOWNLOAD_BANDWIDTH = 2,
        SETTINGS_ROUND_TRIP_TIME = 3,
        SETTINGS_MAX_CONCURRENT_STREAMS = 4,
        SETTINGS_CURRENT_CWND = 5,
        SETTINGS_DOWNLOAD_RETRANS_RATE = 6,
        SETTINGS_INITIAL_WINDOW_SIZE = 7,
        SETTINGS_CLIENT_CERTIFICATE_VECTOR_SIZE = 8
    };

    enum GOAWAY_STATUS {
        GOAWAY_OK = 0,
        GOAWAY_PROTOCOL_ERROR = 1,
        GOAWAY_INTERNAL_ERROR = 11
    };

    enum RST_STREAM_STATUS_CODE {
        RST_STREAM_PROTOCOL_ERROR = 1,
        RST_STREAM_INVALID_STREAM = 2,
        RST_STREAM_REFUSED_STREAM = 3,
        RST_STREAM_UNSUPPORTED_VERSION = 4,
        RST_STREAM_CANCEL = 5,
        RST_STREAM_INTERNAL_ERROR = 6,
        RST_STREAM_FLOW_CONTROL_ERROR = 7,
        RST_STREAM_STREAM_IN_USE = 8,
        RST_STREAM_STREAM_ALREADY_CLOSED = 9,
        RST_STREAM_INVALID_CREDENTIALS = 10,
        RST_STREAM_FRAME_TOO_LARGE = 11
    };

    quint64 bytesAvailable() const;
    bool readNextChunk(qint64 length, char *sink);

    void sendControlFrame(FrameType type, ControlFrameFlags flags, const char *data, quint32 length);

    void sendSYN_STREAM(HttpMessagePair pair, qint32 streamID,
                        qint32 associatedToStreamID);
    void sendRST_STREAM(qint32 streamID, RST_STREAM_STATUS_CODE statusCode);
    void sendPING(quint32 pingID);

    bool uploadData(qint32 streamID);
    Q_INVOKABLE void sendWINDOW_UPDATE(qint32 streamID, quint32 deltaWindowSize);

    qint64 sendDataFrame(qint32 streamID, DataFrameFlags flags, quint32 length,
                       const char *data);

    QByteArray composeHeader(const QHttpNetworkRequest &request);
    bool uncompressHeader(const QByteArray &input, QByteArray *output);

    void handleControlFrame(const QByteArray &frameHeaders);
    void handleDataFrame(const QByteArray &frameHeaders);

    void handleSYN_STREAM(char, quint32, const QByteArray &frameData);
    void handleSYN_REPLY(char flags, quint32, const QByteArray &frameData);
    void handleRST_STREAM(char flags, quint32 length, const QByteArray &frameData);
    void handleSETTINGS(char flags, quint32 length, const QByteArray &frameData);
    void handlePING(char, quint32 length, const QByteArray &frameData);
    void handleGOAWAY(char flags, quint32, const QByteArray &frameData);
    void handleHEADERS(char flags, quint32, const QByteArray &frameData);
    void handleWINDOW_UPDATE(char, quint32, const QByteArray &frameData);

    qint32 generateNextStreamID();
    void parseHttpHeaders(char flags, const QByteArray &frameData);

    void replyFinished(QHttpNetworkReply *httpReply, qint32 streamID);
    void replyFinishedWithError(QHttpNetworkReply *httpReply, qint32 streamID,
                                QNetworkReply::NetworkError errorCode, const char *errorMessage);

    qint32 m_nextStreamID;
    QHash<quint32, HttpMessagePair> m_inFlightStreams;
    qint32 m_maxConcurrentStreams;
    quint32 m_initialWindowSize;
    QByteDataBuffer m_spdyBuffer;
    bool m_waitingForCompleteStream;
#ifndef QT_NO_COMPRESS
    QCompressor m_deflateStream;
    QUncompressor m_inflateStream;
#endif
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QSpdyProtocolHandler::DataFrameFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(QSpdyProtocolHandler::ControlFrameFlags)
Q_DECLARE_OPERATORS_FOR_FLAGS(QSpdyProtocolHandler::SETTINGS_Flags)
Q_DECLARE_OPERATORS_FOR_FLAGS(QSpdyProtocolHandler::SETTINGS_ID_Flags)

QT_END_NAMESPACE

#endif // !defined(QT_NO_HTTP) && !defined(QT_NO_SSL)

#endif // QSPDYPROTOCOLHANDLER_H
