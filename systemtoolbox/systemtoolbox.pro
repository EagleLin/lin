#-------------------------------------------------
#
# Project created by QtCreator 2016-09-09T14:52:37
#
#-------------------------------------------------

QT       += core gui

TARGET = systemtoolbox
TEMPLATE = app

TRANSLATIONS = systemtoolbox.ts

SOURCES += main.cpp\
        mainwindow.cpp \
    datahandle.cpp \
    toolbutton.cpp \
    flowlayout.cpp \
    autohideobject.cpp \
    ../publib/pubclass/qkeyvaluelist.cpp

HEADERS  += mainwindow.h \
    datahandle.h \
    toolbutton.h \
    flowlayout.h \
    autohideobject.h \
    ../publib/pubclass/qkeyvaluelist.h

RESOURCES += \
    ../res/icon.qrc \
    ../res/gatewaytool.qrc

include(../publib/pubclass/pubclass.pri)
include(../publib/pubgui/pubgui.pri)
include(../publib/pubfun/pubfun.pri)

include(../pubplatform/app/qsingleapp.pri)
include(../pubplatform/platformvars/platformvars.pri)
include(../pubplatform/pubfun/platformfun.pri)

include(../pubbusiness/businessvars/businessvars.pri)
