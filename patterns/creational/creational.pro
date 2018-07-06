TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp \
    factory_method.cpp \
    abstract_factory.cpp \
    singleton.cpp \
    builder.cpp \
    prototype.cpp \
    object_pool.cpp
