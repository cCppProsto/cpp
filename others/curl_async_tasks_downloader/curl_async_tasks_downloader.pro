TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread

unix{
  LIBS += -pthread -lcurl
  LIBS += -lstdc++fs
}

SOURCES += \
        main.cpp

HEADERS +=
