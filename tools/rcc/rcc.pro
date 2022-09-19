QT       -= core gui

TARGET = rcc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#DEFINES += QT_NO_CAST_FROM_ASCII
DEFINES += QT_RCC QT_USE_QSTRINGBUILDER

include(../../core/LeanQt.pri)

SOURCES += main.cpp rcc.cpp \
    ../../core/qcommandlineoption.cpp \
    ../../core/qcommandlineparser.cpp \
    ../../core/qxmlstream.cpp \
    ../../core/qxmlutils.cpp


