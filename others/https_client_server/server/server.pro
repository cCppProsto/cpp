TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


unix
{
  LIBS += -lssl -lcrypto
  LIBS += -lstdc++fs
}

SOURCES += \
        main.cpp \
    server.cpp \
    ../common/http_request.cpp

HEADERS += \
    server.hpp \
    ../common/http_request.hpp
