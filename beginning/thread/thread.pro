TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

unix{
  LIBS += -pthread
}

SOURCES += \
        main.cpp
