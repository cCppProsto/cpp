QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = qtGraphicViewExample
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++1z

SOURCES += \
        main.cpp \
    mainscene.cpp \
    graphicsView.cpp \
    mainfield.cpp \
    primaryfield.cpp \
    dragdropinfo.cpp \
    field.cpp \
    dragdrawobj.cpp

HEADERS += \
    mainscene.hpp \
    graphicsView.hpp \
    mainfield.hpp \
    primaryfield.hpp \
    common.h \
    dragdropinfo.hpp \
    field.hpp \
    dragdrawobj.hpp

FORMS +=

RESOURCES +=
