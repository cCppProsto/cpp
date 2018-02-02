QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = socobanQGL
TEMPLATE = app

CONFIG += c++1z

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        socoban.cpp \
        appsettings.cpp \
        level.cpp \
        drawer.cpp

HEADERS += \
    socoban.hpp \
    appsettings.hpp \
    level.hpp \
    drawer.hpp

