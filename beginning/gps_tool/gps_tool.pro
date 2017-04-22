TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp \
    gps_tool.cpp

HEADERS += \
    gps_tool.h

DISTFILES += \
    task.txt
