#-------------------------------------------------
#
# Project created by QtCreator 2018-02-02T08:34:17
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = socobanGL
TEMPLATE = app

CONFIG += c++1z

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
    socoban.cpp \
    appsettings.cpp \
    drawer.cpp \
    level.cpp

HEADERS += \
    socoban.hpp \
    appsettings.hpp \
    drawer.hpp \
    level.hpp

FORMS +=
