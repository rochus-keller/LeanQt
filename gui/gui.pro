# Copyright (C) 2022 Rochus Keller (me@rochus-keller.ch) for LeanQt
# licensed under GPL/LGPL

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../includes ../includes/QtCore ../includes/QtGui . ..


HEADERS += \
    qabstracttextdocumentlayout_p.h \
    qabstracttextdocumentlayout.h \
    qbackingstore.h \
    qbitmap.h \
    qblittable_p.h \
    qbrush.h \
    qclipboard.h \
    qcosmeticstroker_p.h \
    qcssparser_p.h \
    qcssutil_p.h \
    qcursor_p.h \
    qcursor.h \
    qdistancefield_p.h \
    qdnd_p.h \
    qdrag.h \
    qemulationpaintengine_p.h \
    qevent_p.h \
    qevent.h \
    qfixed_p.h \
    qfont_p.h \
    qfont.h \
    qfontdatabase.h \
    qfontengine_ft_p.h \
    qfontengine_p.h \
    qfontengine_qpf2_p.h \
    qfontengineglyphcache_p.h \
    qfontinfo.h \
    qfontmetrics.h \
    qfontsubset_p.h \
    qfragmentmap_p.h \
    qgenericplugin.h \
    qgenericpluginfactory.h \
    qglyphrun_p.h \
    qglyphrun.h \
    qguiapplication_p.h \
    qguiapplication.h \
    qharfbuzzng_p.h \
    qhighdpiscaling_p.h \
    qicon_p.h \
    qicon.h \
    qiconengine.h \
    qiconengineplugin.h \
    qiconloader_p.h \
    qimagepixmapcleanuphooks_p.h \
    qinputcontrol_p.h \
    qinputdevicemanager_p_p.h \
    qinputdevicemanager_p.h \
    qinputmethod_p.h \
    qinputmethod.h \
    qkeymapper_p.h \
    qkeysequence_p.h \
    qkeysequence.h \
    qnativeimage_p.h \
    qoffscreensurface.h \
    qoutlinemapper_p.h \
    qpagedpaintdevice_p.h \
    qpagedpaintdevice.h \
    qpagelayout.h \
    qpagesize.h \
    qpaintdevicewindow_p.h \
    qpaintdevicewindow.h \
    qpaintengine_blitter_p.h \
    qpaintengine_p.h \
    qpaintengine_pic_p.h \
    qpaintengine_raster_p.h \
    qpaintengine.h \
    qpaintengineex_p.h \
    qpainter_p.h \
    qpainter.h \
    qpalette.h \
    qpathsimplifier_p.h \
    qpdf_p.h \
    qpdfwriter.h \
    qpen_p.h \
    qpen.h \
    qpicture_p.h \
    qpicture.h \
    qpictureformatplugin.h \
    qpixmap_blitter_p.h \
    qpixmap_raster_p.h \
    qpixmap.h \
    qpixmapcache_p.h \
    qpixmapcache.h \
    qplatformaccessibility.h \
    qplatformbackingstore.h \
    qplatformclipboard.h \
    qplatformcursor.h \
    qplatformdialoghelper.h \
    qplatformdrag.h \
    qplatformfontdatabase.h \
    qplatformgraphicsbuffer.h \
    qplatformgraphicsbufferhelper.h \
    qplatforminputcontext_p.h \
    qplatforminputcontext.h \
    qplatforminputcontextfactory_p.h \
    qplatforminputcontextplugin_p.h \
    qplatformintegration.h \
    qplatformintegrationfactory_p.h \
    qplatformintegrationplugin.h \
    qplatformmenu.h \
    qplatformnativeinterface.h \
    qplatformoffscreensurface.h \
    qplatformpixmap.h \
    qplatformscreen_p.h \
    qplatformscreen.h \
    qplatformservices.h \
    qplatformsessionmanager.h \
    qplatformsharedgraphicscache.h \
    qplatformsurface.h \
    qplatformsystemtrayicon.h \
    qplatformtheme_p.h \
    qplatformtheme.h \
    qplatformthemefactory_p.h \
    qplatformthemeplugin.h \
    qplatformwindow_p.h \
    qplatformwindow.h \
    qpolygonclipper_p.h \
    qrasterizer_p.h \
    qrasterwindow.h \
    qrawfont_p.h \
    qrawfont.h \
    qscreen_p.h \
    qscreen.h \
    qsessionmanager_p.h \
    qsessionmanager.h \
    qshapedpixmapdndwindow_p.h \
    qshortcutmap_p.h \
    qsimpledrag_p.h \
    qstatictext_p.h \
    qstatictext.h \
    qstylehints.h \
    qsurface.h \
    qsurfaceformat.h \
    qsyntaxhighlighter.h \
    qtextcursor_p.h \
    qtextcursor.h \
    qtextdocument_p.h \
    qtextdocument.h \
    qtextdocumentfragment_p.h \
    qtextdocumentfragment.h \
    qtextdocumentlayout_p.h \
    qtextdocumentwriter.h \
    qtextengine_p.h \
    qtextformat_p.h \
    qtextformat.h \
    qtexthtmlparser_p.h \
    qtextimagehandler_p.h \
    qtextlayout.h \
    qtextlist.h \
    qtextobject_p.h \
    qtextobject.h \
    qtextodfwriter_p.h \
    qtextoption.h \
    qtexttable_p.h \
    qtexttable.h \
    qtextureglyphcache_p.h \
    qtouchdevice_p.h \
    qtouchdevice.h \
    qwindow_p.h \
    qwindow.h \
    qwindowdefs_win.h \
    qwindowdefs.h \
    qwindowsysteminterface_p.h \
    qwindowsysteminterface.h \
    ../image/qbezier_p.h \
    ../image/qblendfunctions_p.h \
    ../image/qbmphandler_p.h \
    ../image/qcolor_p.h \
    ../image/qcolor.h \
    ../image/qdatabuffer_p.h \
    ../image/qdrawhelper_neon_p.h \
    ../image/qdrawhelper_p.h \
    ../image/qdrawhelper_x86_p.h \
    ../image/qdrawingprimitive_sse2_p.h \
    ../image/qgifhandler_p.h \
    ../image/qimage_p.h \
    ../image/qimage.h \
    ../image/qimageiohandler.h \
    ../image/qimagereader.h \
    ../image/qimagescale_p.h \
    ../image/qimagewriter.h \
    ../image/qjpeghandler_p.h \
    ../image/qmath_p.h \
    ../image/qmatrix.h \
    ../image/qmemrotate_p.h \
    ../image/qpaintdevice.h \
    ../image/qpainterpath_p.h \
    ../image/qpainterpath.h \
    ../image/qpathclipper_p.h \
    ../image/qpixelformat.h \
    ../image/qpnghandler_p.h \
    ../image/qpolygon.h \
    ../image/qppmhandler_p.h \
    ../image/qrasterdefs_p.h \
    ../image/qregion.h \
    ../image/qrgb.h \
    ../image/qrgba64_p.h \
    ../image/qrgba64.h \
    ../image/qstroker_p.h \
    ../image/qtransform.h \
    ../image/qvectorpath_p.h \
    ../image/qxbmhandler_p.h \
    ../image/qxpmhandler_p.h \
    qhexstring_p.h \
    qmimedata.h \
    qsyntaxhighlighter_p.h \
    qvector2d.h \
    qgenericmatrix.h \
    qgrayraster_p.h \
    qharfbuzz_p.h \
    qmatrix4x4.h \
    qquaternion.h \
    qrbtree_p.h \
    qtextboundaryfinder.h \
    qvector3d.h \
    qvector4d.h \
    qzipreader_p.h \
    qzipwriter_p.h

SOURCES += \
    qabstracttextdocumentlayout.cpp \
    qbackingstore.cpp \
    qbitmap.cpp \
    qblittable.cpp \
    qbrush.cpp \
    qclipboard.cpp \
    qcompositionfunctions.cpp \
    qcosmeticstroker.cpp \
    qcssparser.cpp \
    qcssscanner.cpp \
    qcssutil.cpp \
    qcursor.cpp \
    qdistancefield.cpp \
    qdnd.cpp \
    qdrag.cpp \
    qemulationpaintengine.cpp \
    qevent.cpp \
    qfont.cpp \
    qfontdatabase.cpp \
    qfontengine_ft.cpp \
    qfontengine_qpf2.cpp \
    qfontengine.cpp \
    qfontengineglyphcache.cpp \
    qfontmetrics.cpp \
    qfontsubset_agl.cpp \
    qfontsubset.cpp \
    qfragmentmap.cpp \
    qgammatables.cpp \
    qgenericplugin.cpp \
    qgenericpluginfactory.cpp \
    qglyphrun.cpp \
    qguiapplication.cpp \
    qguivariant.cpp \
    qharfbuzzng.cpp \
    qhighdpiscaling.cpp \
    qicon.cpp \
    qiconengine.cpp \
    qiconengineplugin.cpp \
    qiconloader.cpp \
    qimagepixmapcleanuphooks.cpp \
    qinputcontrol.cpp \
    qinputdevicemanager.cpp \
    qinputmethod.cpp \
    qkeymapper.cpp \
    qkeysequence.cpp \
    qnativeimage.cpp \
    qoffscreensurface.cpp \
    qoutlinemapper.cpp \
    qpagedpaintdevice.cpp \
    qpagelayout.cpp \
    qpagesize.cpp \
    qpaintdevicewindow.cpp \
    qpaintengine_blitter.cpp \
    qpaintengine_pic.cpp \
    qpaintengine_raster.cpp \
    qpaintengineex.cpp \
    qpainter.cpp \
    qpalette.cpp \
    qpathsimplifier.cpp \
    qpdf.cpp \
    qpdfwriter.cpp \
    qpen.cpp \
    qpicture.cpp \
    qpictureformatplugin.cpp \
    qpixmap_blitter.cpp \
    qpixmap_raster.cpp \
    qpixmap_win.cpp \
    qpixmap.cpp \
    qpixmapcache.cpp \
    qplatformaccessibility.cpp \
    qplatformbackingstore.cpp \
    qplatformclipboard.cpp \
    qplatformcursor.cpp \
    qplatformdialoghelper.cpp \
    qplatformdrag.cpp \
    qplatformfontdatabase.cpp \
    qplatformgraphicsbuffer.cpp \
    qplatformgraphicsbufferhelper.cpp \
    qplatforminputcontext.cpp \
    qplatforminputcontextfactory.cpp \
    qplatforminputcontextplugin.cpp \
    qplatformintegration.cpp \
    qplatformintegrationfactory.cpp \
    qplatformintegrationplugin.cpp \
    qplatformmenu.cpp \
    qplatformnativeinterface.cpp \
    qplatformoffscreensurface.cpp \
    qplatformpixmap.cpp \
    qplatformscreen.cpp \
    qplatformservices.cpp \
    qplatformsessionmanager.cpp \
    qplatformsharedgraphicscache.cpp \
    qplatformsurface.cpp \
    qplatformsystemtrayicon.cpp \
    qplatformtheme.cpp \
    qplatformthemefactory.cpp \
    qplatformthemeplugin.cpp \
    qplatformwindow.cpp \
    qrasterizer.cpp \
    qrasterwindow.cpp \
    qrawfont.cpp \
    qscreen.cpp \
    qsessionmanager.cpp \
    qshapedpixmapdndwindow.cpp \
    qshortcutmap.cpp \
    qsimpledrag.cpp \
    qstatictext.cpp \
    qstylehints.cpp \
    qsurface.cpp \
    qsurfaceformat.cpp \
    qsyntaxhighlighter.cpp \
    qtextcursor.cpp \
    qtextdocument_p.cpp \
    qtextdocument.cpp \
    qtextdocumentfragment.cpp \
    qtextdocumentlayout.cpp \
    qtextdocumentwriter.cpp \
    qtextengine.cpp \
    qtextformat.cpp \
    qtexthtmlparser.cpp \
    qtextimagehandler.cpp \
    qtextlayout.cpp \
    qtextlist.cpp \
    qtextobject.cpp \
    qtextodfwriter.cpp \
    qtextoption.cpp \
    qtexttable.cpp \
    qtextureglyphcache.cpp \
    qtouchdevice.cpp \
    qwindow.cpp \
    qwindowsysteminterface.cpp \
    ../image/qbezier.cpp \
    ../image/qblendfunctions.cpp \
    ../image/qbmphandler.cpp \
    ../image/qcolor_p.cpp \
    ../image/qcolor.cpp \
    ../image/qdrawhelper_avx2.cpp \
    ../image/qdrawhelper_neon.cpp \
    ../image/qdrawhelper_sse2.cpp \
    ../image/qdrawhelper_sse4.cpp \
    ../image/qdrawhelper_ssse3.cpp \
    ../image/qdrawhelper.cpp \
    ../image/qgifhandler.cpp \
    ../image/qimage_avx2.cpp \
    ../image/qimage_compat.cpp \
    ../image/qimage_conversions.cpp \
    ../image/qimage_neon.cpp \
    ../image/qimage_sse2.cpp \
    ../image/qimage_sse4.cpp \
    ../image/qimage_ssse3.cpp \
    ../image/qimage.cpp \
    ../image/qimageiohandler.cpp \
    ../image/qimagereader.cpp \
    ../image/qimagescale_sse4.cpp \
    ../image/qimagescale.cpp \
    ../image/qimagewriter.cpp \
    ../image/qjpeghandler.cpp \
    ../image/qmatrix.cpp \
    ../image/qmemrotate.cpp \
    ../image/qpaintdevice.cpp \
    ../image/qpainterpath.cpp \
    ../image/qpathclipper.cpp \
    ../image/qpixelformat.cpp \
    ../image/qpnghandler.cpp \
    ../image/qpolygon.cpp \
    ../image/qppmhandler.cpp \
    ../image/qregion.cpp \
    ../image/qstroker.cpp \
    ../image/qtransform.cpp \
    ../image/qvectorpath.cpp \
    ../image/qxbmhandler.cpp \
    ../image/qxpmhandler.cpp \
    qmimedata.cpp \
    qvector2d.cpp \
    qharfbuzz.cpp \
    qgenericmatrix.cpp \
    qmatrix4x4.cpp \
    qquaternion.cpp \
    qtextboundaryfinder.cpp \
    qvector3d.cpp \
    qvector4d.cpp \
    qzip.cpp \
    qgrayraster.c




