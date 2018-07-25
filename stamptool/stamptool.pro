#-------------------------------------------------
#
# Project created by QtCreator 2018-06-20T16:05:38
#
#-------------------------------------------------

QT       += core gui sql network multimedia xml webkitwidgets
QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


RCC_DIR += ./tmp
MOC_DIR += ./tmp
UI_DIR  += ./tmp
OBJECTS_DIR += ./tmp
CONFIG += C++11

TARGET = stamptool
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    uiobject/mainwidget.cpp \
    pubfun.cpp \
    protocolobject.cpp \
    pushdataobject.cpp

HEADERS  += mainwindow.h \
    uiobject/mainwidget.h \
    pubfun.h \
    protocolobject.h \
    pushdataobject.h

INCLUDEPATH += \
    uiobject/ \
    include_cpp/ \

include(./base/base.pri)
include(./pubgui/pubgui.pri)

RESOURCES += \
    image.qrc

LIBS +=./lib/libxl.lib
