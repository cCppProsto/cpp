TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CFLAGS += -std=c11

INCLUDEPATH += ../../../tools_src/
INCLUDEPATH += ../../../external_libs/glfw/include/
INCLUDEPATH += ../../../external_libs/glut/include/
INCLUDEPATH += ../../../tools_src/graphical_library/

SOURCES += main.cpp \
    ../../../tools_src/glfw_engine2D.cpp \
    ../../../tools_src/fpstool.cpp \
    glmain.cpp \
    benderword.cpp \
    bendermap.cpp \
    bender.cpp \
    benderworldposition.cpp \
    ../../../tools_src/graphical_library/gpgrid.cpp \
    ../../../tools_src/graphical_library/color.cpp \
    ../../../tools_src/graphical_library/gpcircle.cpp \
    ../../../tools_src/graphical_library/gpclosedlines.cpp \
    ../../../tools_src/graphical_library/gpline.cpp \
    ../../../tools_src/graphical_library/gplines.cpp \
    ../../../tools_src/graphical_library/gpopenlines.cpp \
    ../../../tools_src/graphical_library/gpplane.cpp \
    ../../../tools_src/graphical_library/gppoint.cpp \
    ../../../tools_src/graphical_library/gprimitive.cpp \
    ../../../tools_src/graphical_library/gptriangle.cpp

HEADERS += \
    ../../../external_libs/glfw/include/glfw3.h \
    ../../../external_libs/glfw/include/glfw3native.h \
    ../../../external_libs/glut/include/glut.h \
    ../../../tools_src/glfw_engine2D.hpp \
    ../../../tools_src/fpstool.hpp \
    glmain.h \
    benderword.h \
    bendermap.h \
    bender.h \
    common.h \
    benderworldposition.h \
    ../../../tools_src/graphical_library/gpgrid.hpp \
    ../../../tools_src/graphical_library/color.hpp \
    ../../../tools_src/graphical_library/gpcircle.hpp \
    ../../../tools_src/graphical_library/gpclosedlines.hpp \
    ../../../tools_src/graphical_library/gpline.hpp \
    ../../../tools_src/graphical_library/gplines.hpp \
    ../../../tools_src/graphical_library/gpopenlines.hpp \
    ../../../tools_src/graphical_library/gpplane.hpp \
    ../../../tools_src/graphical_library/gppoint.hpp \
    ../../../tools_src/graphical_library/gprimitive.hpp \
    ../../../tools_src/graphical_library/gptriangle.hpp

QT   += opengl

unix{
LIBS += -lGL -lGLU -lglut
LIBS += -lglfw
LIBS += -lX11 -lXrandr -lXinerama -lXxf86vm -lXcursor -lpthread -ldl
}

win32{
LIBS += -L$$PWD/../../../external_libs/glfw/lib/ -lglfw3
LIBS += -lgdi32 -L$$PWD/../../../external_libs/glut/lib/ -lglut32
LIBS += -lopengl32
}
