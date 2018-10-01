TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    observer.cpp \
    command.cpp \
    state.cpp \
    state/heroinestate.cpp \
    state/heroine.cpp \
    state/duckingstate.cpp \
    state/standingstate.cpp \
    state/jumpingstate.cpp \
    state/divingstate.cpp

HEADERS += \
    state/heroinestate.hpp \
    state/heroine.hpp \
    state/duckingstate.hpp \
    state/standingstate.hpp \
    state/jumpingstate.hpp \
    state/divingstate.hpp
