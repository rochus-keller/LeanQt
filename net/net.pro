# Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
# licensed under GPL/LGPL

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += QT_NO_REGULAREXPRESSION QT_NO_REGEXP_OPTIM QT_NO_THREAD QT_NO_BIG_CODECS QT_NO_ICONV \
                QT_NO_ANIMATION QT_NO_ITEMMODELS QT_NO_JSON QT_NO_GEOM_VARIANT

DEFINES += QT_NO_FILEENGINE QT_NO_COREAPPLICATION

INCLUDEPATH += ../includes ../includes/QtCore ../includes/QtNetwork

DISTFILES += \
    BUSY

HEADERS += \
    qabstractnetworkcache_p.h \
    qabstractnetworkcache.h \
    qabstractprotocolhandler_p.h \
    qabstractsocket_p.h \
    qabstractsocket.h \
    qabstractsocketengine_p.h \
    qauthenticator_p.h \
    qauthenticator.h \
    qbearerengine_p.h \
    qbearerplugin_p.h \
    qbytedata_p.h \
    qdnslookup_p.h \
    qdnslookup.h \
    qftp_p.h \
    qftp.h \
    qhostaddress_p.h \
    qhostaddress.h \
    qhostinfo_p.h \
    qhostinfo.h \
    qhttpmultipart_p.h \
    qhttpmultipart.h \
    qhttpnetworkconnection_p.h \
    qhttpnetworkconnectionchannel_p.h \
    qhttpnetworkheader_p.h \
    qhttpnetworkreply_p.h \
    qhttpnetworkrequest_p.h \
    qhttpprotocolhandler_p.h \
    qhttpsocketengine_p.h \
    qhttpthreaddelegate_p.h \
    qlocalserver_p.h \
    qlocalserver.h \
    qlocalsocket_p.h \
    qlocalsocket.h \
    qnativesocketengine_p.h \
    qnet_unix_p.h \
    qnetworkaccessauthenticationmanager_p.h \
    qnetworkaccessbackend_p.h \
    qnetworkaccesscache_p.h \
    qnetworkaccesscachebackend_p.h \
    qnetworkaccessdebugpipebackend_p.h \
    qnetworkaccessfilebackend_p.h \
    qnetworkaccessftpbackend_p.h \
    qnetworkaccessmanager_p.h \
    qnetworkaccessmanager.h \
    qnetworkconfigmanager_p.h \
    qnetworkconfigmanager.h \
    qnetworkconfiguration_p.h \
    qnetworkconfiguration.h \
    qnetworkcookie_p.h \
    qnetworkcookie.h \
    qnetworkcookiejar_p.h \
    qnetworkcookiejar.h \
    qnetworkinterface_p.h \
    qnetworkinterface.h \
    qnetworkproxy_p.h \
    qnetworkproxy.h \
    qnetworkreply_p.h \
    qnetworkreply.h \
    qnetworkreplydataimpl_p.h \
    qnetworkreplyfileimpl_p.h \
    qnetworkreplyhttpimpl_p.h \
    qnetworkreplyimpl_p.h \
    qnetworkrequest_p.h \
    qnetworkrequest.h \
    qnetworksession_p.h \
    qnetworksession.h \
    qnoncontiguousbytedevice_p.h \
    qsharednetworksession_p.h \
    qsocks5socketengine_p.h \
    qspdyprotocolhandler_p.h \
    qssl_p.h \
    qssl.h \
    qsslcertificate_p.h \
    qsslcertificate.h \
    qsslcertificateextension_p.h \
    qsslcertificateextension.h \
    qsslcipher_p.h \
    qsslcipher.h \
    qsslconfiguration_p.h \
    qsslconfiguration.h \
    qsslcontext_openssl_p.h \
    qsslellipticcurve.h \
    qsslerror.h \
    qsslkey_p.h \
    qsslkey.h \
    qsslpresharedkeyauthenticator_p.h \
    qsslpresharedkeyauthenticator.h \
    qsslsocket_openssl_p.h \
    qsslsocket_openssl_symbols_p.h \
    qsslsocket_p.h \
    qsslsocket.h \
    qtcpserver_p.h \
    qtcpserver.h \
    qtcpsocket_p.h \
    qtcpsocket.h \
    qudpsocket.h \
    qurlinfo_p.h

SOURCES += \
    qabstractnetworkcache.cpp \
    qabstractprotocolhandler.cpp \
    qabstractsocket.cpp \
    qabstractsocketengine.cpp \
    qauthenticator.cpp \
    qbearerengine.cpp \
    qbearerplugin.cpp \
    qdnslookup_unix.cpp \
    qdnslookup_win.cpp \
    qdnslookup.cpp \
    qftp.cpp \
    qhostaddress.cpp \
    qhostinfo_unix.cpp \
    qhostinfo_win.cpp \
    qhostinfo.cpp \
    qhttpmultipart.cpp \
    qhttpnetworkconnection.cpp \
    qhttpnetworkconnectionchannel.cpp \
    qhttpnetworkheader.cpp \
    qhttpnetworkreply.cpp \
    qhttpnetworkrequest.cpp \
    qhttpprotocolhandler.cpp \
    qhttpsocketengine.cpp \
    qhttpthreaddelegate.cpp \
    qlocalserver_unix.cpp \
    qlocalserver_win.cpp \
    qlocalserver.cpp \
    qlocalsocket_unix.cpp \
    qlocalsocket_win.cpp \
    qlocalsocket.cpp \
    qnativesocketengine_unix.cpp \
    qnativesocketengine_win.cpp \
    qnativesocketengine.cpp \
    qnetworkaccessauthenticationmanager.cpp \
    qnetworkaccessbackend.cpp \
    qnetworkaccesscache.cpp \
    qnetworkaccesscachebackend.cpp \
    qnetworkaccessdebugpipebackend.cpp \
    qnetworkaccessfilebackend.cpp \
    qnetworkaccessftpbackend.cpp \
    qnetworkaccessmanager.cpp \
    qnetworkconfigmanager_p.cpp \
    qnetworkconfigmanager.cpp \
    qnetworkconfiguration.cpp \
    qnetworkcookie.cpp \
    qnetworkcookiejar.cpp \
    qnetworkinterface_unix.cpp \
    qnetworkinterface_win.cpp \
    qnetworkinterface.cpp \
    qnetworkproxy_mac.cpp \
    qnetworkproxy_win.cpp \
    qnetworkproxy.cpp \
    qnetworkreply.cpp \
    qnetworkreplydataimpl.cpp \
    qnetworkreplyfileimpl.cpp \
    qnetworkreplyhttpimpl.cpp \
    qnetworkreplyimpl.cpp \
    qnetworkrequest.cpp \
    qnetworksession.cpp \
    qnoncontiguousbytedevice.cpp \
    qsharednetworksession.cpp \
    qsocks5socketengine.cpp \
    qspdyprotocolhandler.cpp \
    qssl.cpp \
    qsslcertificate_openssl.cpp \
    qsslcertificate.cpp \
    qsslcertificateextension.cpp \
    qsslcipher.cpp \
    qsslconfiguration.cpp \
    qsslcontext_openssl.cpp \
    qsslellipticcurve_openssl.cpp \
    qsslellipticcurve.cpp \
    qsslerror.cpp \
    qsslkey_openssl.cpp \
    qsslkey_p.cpp \
    qsslpresharedkeyauthenticator.cpp \
    qsslsocket_openssl_symbols.cpp \
    qsslsocket_openssl.cpp \
    qsslsocket.cpp \
    qtcpserver.cpp \
    qtcpsocket.cpp \
    qudpsocket.cpp \
    qurlinfo.cpp


