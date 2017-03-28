#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T12:11:56
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11 c++14 c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blackEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(src/core/core.pri)
include(src/utils/utils.pri)

SOURCES += main.cpp\
    diffuseshader.cpp

FORMS    +=
    forms/blmainwindow.ui

DISTFILES += \
    codestyle.md \
    docs/CODESTYLE.md \
    ../build-blackEngine-Desktop_Qt_5_8_0_GCC_64bit-Debug/resources/shaders/simple_fragment.frag \
    ../build-blackEngine-Desktop_Qt_5_8_0_GCC_64bit-Debug/resources/shaders/simple_vertex.vert \
    ../build-blackEngine-Desktop_Qt_5_8_0_GCC_64bit-Debug/resources/shaders/diffuse.frag \
    ../build-blackEngine-Desktop_Qt_5_8_0_GCC_64bit-Debug/resources/shaders/diffuse.vert

HEADERS += \
    diffuseshader.h
