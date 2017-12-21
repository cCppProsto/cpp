TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    bubblesort.cpp \
    selectionsort.cpp \
    insertionsort.cpp

HEADERS += \
    bubblesort.hpp \
    selectionsort.hpp \
    insertionsort.hpp
