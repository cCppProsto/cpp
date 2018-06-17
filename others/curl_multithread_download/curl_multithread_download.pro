TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

unix{
  LIBS += -pthread -lcurl
}

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        main.cpp \
    curl_tool.cpp \
    curl_downloader.cpp

HEADERS += \
    curl_tool.hpp \
    curl_downloader.hpp
