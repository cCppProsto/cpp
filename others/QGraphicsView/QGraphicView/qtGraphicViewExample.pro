#-------------------------------------------------
#
# Project created by QtCreator 2018-02-14T16:40:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = qtGraphicViewExample
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    button.cpp \
    zombieattack.cpp \
    zombiemoving.cpp \
    zombie.cpp \
    zombiestanding.cpp \
    graphicviewexample.cpp

HEADERS += \
    button.hpp \
    zombieattack.hpp \
    zombiemoving.hpp \
    zombie.hpp \
    zombiestanding.hpp \
    graphicviewexample.hpp

FORMS +=

RESOURCES += \
    pics.qrc
