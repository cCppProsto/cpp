TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CFLAGS += -std=c11

SOURCES += main.cpp \
    cpp_string.cpp

HEADERS += \
    cpp_string.h

DISTFILES += \
    notes.txt
