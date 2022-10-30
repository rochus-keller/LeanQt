# Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
# licensed under GPL/LGPL

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


INCLUDEPATH += ../includes ../includes/QtCore ../includes/QtGui

DEFINES += QT_NO_GUI QT_NO_IMAGEFORMATPLUGIN QT_BUILD_GUI_LIB

HEADERS += \
    qbezier_p.h \
    qbmphandler_p.h \
    qcolor_p.h \
    qcolor.h \
    qdatabuffer_p.h \
    qdrawhelper_neon_p.h \
    qdrawhelper_p.h \
    qdrawhelper_x86_p.h \
    qdrawingprimitive_sse2_p.h \
    qgifhandler_p.h \
    qimage_p.h \
    qimage.h \
    qimageiohandler.h \
    qimagereader.h \
    qimagescale_p.h \
    qimagewriter.h \
    qjpeghandler_p.h \
    qmatrix.h \
    qmemrotate_p.h \
    qpaintdevice.h \
    qpainterpath_p.h \
    qpainterpath.h \
    qpathclipper_p.h \
    qpixelformat.h \
    qpnghandler_p.h \
    qpolygon.h \
    qppmhandler_p.h \
    qrasterdefs_p.h \
    qregion.h \
    qrgb.h \
    qrgba64_p.h \
    qrgba64.h \
    qstroker_p.h \
    qtransform.h \
    qvectorpath_p.h \
    qxbmhandler_p.h \
    qxpmhandler_p.h \
    qdrawhelper_neon_asm.S

SOURCES += \
    qbezier.cpp \
    qbmphandler.cpp \
    qcolor_p.cpp \
    qcolor.cpp \
    qdrawhelper_avx2.cpp \
    qdrawhelper_neon.cpp \
    qdrawhelper_sse2.cpp \
    qdrawhelper_sse4.cpp \
    qdrawhelper_ssse3.cpp \
    qdrawhelper.cpp \
    qdrawhelper1.cpp \
    qgifhandler.cpp \
    qimage_avx2.cpp \
    qimage_compat.cpp \
    qimage_conversions.cpp \
    qimage_neon.cpp \
    qimage_sse2.cpp \
    qimage_sse4.cpp \
    qimage_ssse3.cpp \
    qimage.cpp \
    qimageiohandler.cpp \
    qimagereader.cpp \
    qimagescale_sse4.cpp \
    qimagescale.cpp \
    qimagewriter.cpp \
    qjpeghandler.cpp \
    qmatrix.cpp \
    qmemrotate.cpp \
    qpaintdevice.cpp \
    qpainterpath.cpp \
    qpathclipper.cpp \
    qpixelformat.cpp \
    qpnghandler.cpp \
    qpolygon.cpp \
    qppmhandler.cpp \
    qregion.cpp \
    qstroker.cpp \
    qtransform.cpp \
    qvectorpath.cpp \
    qxbmhandler.cpp \
    qxpmhandler.cpp




