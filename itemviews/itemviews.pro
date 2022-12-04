# Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
# licensed under GPL/LGPL

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    qabstractitemdelegate_p.h \
    qabstractitemdelegate.h \
    qabstractitemmodel_p.h \
    qabstractitemmodel.h \
    qabstractitemview_p.h \
    qabstractitemview.h \
    qabstractproxymodel_p.h \
    qabstractproxymodel.h \
    qbsptree_p.h \
    qcalendarwidget_p.h \
    qcalendarwidget.h \
    qcolumnview_p.h \
    qcolumnview.h \
    qcolumnviewgrip_p.h \
    qcombobox_p.h \
    qcombobox.h \
    qcompleter_p.h \
    qcompleter.h \
    qdatawidgetmapper_p.h \
    qdatawidgetmapper.h \
    qdatetimeedit_p.h \
    qdatetimeedit.h \
    qdirmodel_p.h \
    qdirmodel.h \
    qfiledialog_p.h \
    qfiledialog.h \
    qfileiconprovider_p.h \
    qfileiconprovider.h \
    qfileinfogatherer_p.h \
    qfilesystemmodel_p.h \
    qfilesystemmodel.h \
    qfontcombobox_p.h \
    qfontcombobox.h \
    qfontdialog_p.h \
    qfontdialog.h \
    qfscompleter_p.h \
    qheaderview_p.h \
    qheaderview.h \
    qidentityproxymodel_p.h \
    qidentityproxymodel.h \
    qinputdialog_p.h \
    qinputdialog.h \
    qitemdelegate_p.h \
    qitemdelegate.h \
    qitemeditorfactory_p.h \
    qitemeditorfactory.h \
    qitemselectionmodel_p.h \
    qitemselectionmodel.h \
    qlistview_p.h \
    qlistview.h \
    qlistwidget_p.h \
    qlistwidget.h \
    qsidebar_p.h \
    qsortfilterproxymodel_p.h \
    qsortfilterproxymodel.h \
    qstandarditemmodel_p.h \
    qstandarditemmodel.h \
    qstringlistmodel.h \
    qstyleditemdelegate_p.h \
    qstyleditemdelegate.h \
    qtableview_p.h \
    qtableview.h \
    qtablewidget_p.h \
    qtablewidget.h \
    qtreeview_p.h \
    qtreeview.h \
    qtreewidget_p.h \
    qtreewidget.h \
    qtreewidgetitemiterator_p.h \
    qtreewidgetitemiterator.h \
    qundoview_p.h \
    qundoview.h \
    qwidgetitemdata_p.h \
    ui_qfiledialog.h

SOURCES += \
    qabstractitemdelegate.cpp \
    qabstractitemmodel.cpp \
    qabstractitemview.cpp \
    qabstractproxymodel.cpp \
    qbsptree.cpp \
    qcalendarwidget.cpp \
    qcolumnview.cpp \
    qcolumnviewgrip.cpp \
    qcombobox.cpp \
    qcompleter.cpp \
    qdatawidgetmapper.cpp \
    qdatetimeedit.cpp \
    qdirmodel.cpp \
    qfiledialog.cpp \
    qfileiconprovider.cpp \
    qfileinfogatherer.cpp \
    qfilesystemmodel.cpp \
    qfontcombobox.cpp \
    qfontdialog.cpp \
    qheaderview.cpp \
    qidentityproxymodel.cpp \
    qinputdialog.cpp \
    qitemdelegate.cpp \
    qitemeditorfactory.cpp \
    qitemselectionmodel.cpp \
    qlistview.cpp \
    qlistwidget.cpp \
    qsidebar.cpp \
    qsortfilterproxymodel.cpp \
    qstandarditemmodel.cpp \
    qstringlistmodel.cpp \
    qstyleditemdelegate.cpp \
    qtableview.cpp \
    qtablewidget.cpp \
    qtreeview.cpp \
    qtreewidget.cpp \
    qtreewidgetitemiterator.cpp \
    qundoview.cpp


