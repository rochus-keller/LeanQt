# Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
# licensed under GPL/LGPL

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../includes ../includes/QtCore ../includes/QtGui ./includes/QtWidgets


HEADERS += \
    qgraph_p.h \
    qgraphicsanchorlayout_p.h \
    qgraphicsanchorlayout.h \
    qgraphicsgridlayout.h \
    qgraphicsgridlayoutengine_p.h \
    qgraphicsitem_p.h \
    qgraphicsitem.h \
    qgraphicsitemanimation.h \
    qgraphicslayout_p.h \
    qgraphicslayout.h \
    qgraphicslayoutitem_p.h \
    qgraphicslayoutitem.h \
    qgraphicslayoutstyleinfo_p.h \
    qgraphicslinearlayout.h \
    qgraphicsproxywidget_p.h \
    qgraphicsproxywidget.h \
    qgraphicsscene_bsp_p.h \
    qgraphicsscene_p.h \
    qgraphicsscene.h \
    qgraphicsscenebsptreeindex_p.h \
    qgraphicssceneevent.h \
    qgraphicssceneindex_p.h \
    qgraphicsscenelinearindex_p.h \
    qgraphicstransform_p.h \
    qgraphicstransform.h \
    qgraphicsview_p.h \
    qgraphicsview.h \
    qgraphicswidget_p.h \
    qgraphicswidget.h \
    qsimplex_p.h

SOURCES += \
    qgraphicsanchorlayout_p.cpp \
    qgraphicsanchorlayout.cpp \
    qgraphicsgridlayout.cpp \
    qgraphicsgridlayoutengine.cpp \
    qgraphicsitem.cpp \
    qgraphicsitemanimation.cpp \
    qgraphicslayout_p.cpp \
    qgraphicslayout.cpp \
    qgraphicslayoutitem.cpp \
    qgraphicslayoutstyleinfo.cpp \
    qgraphicslinearlayout.cpp \
    qgraphicsproxywidget.cpp \
    qgraphicsscene_bsp.cpp \
    qgraphicsscene.cpp \
    qgraphicsscenebsptreeindex.cpp \
    qgraphicssceneevent.cpp \
    qgraphicssceneindex.cpp \
    qgraphicsscenelinearindex.cpp \
    qgraphicstransform.cpp \
    qgraphicsview.cpp \
    qgraphicswidget_p.cpp \
    qgraphicswidget.cpp \
    qsimplex_p.cpp


