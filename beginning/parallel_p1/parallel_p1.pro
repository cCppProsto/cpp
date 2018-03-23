TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

CONFIG += c++1z


#QMAKE_CXXFLAGS += -Werror

SOURCES += main.cpp

HEADERS +=
