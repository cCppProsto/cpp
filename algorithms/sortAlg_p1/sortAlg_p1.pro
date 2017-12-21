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
INCLUDEPATH += ../../../tools_src/math/


SOURCES += main.cpp \
    application.cpp \
    ../../../tools_src/baseappinst.cpp \
    ../../../tools_src/mainmenu.cpp \
    ../../../tools_src/glfw_engine2D.cpp \
    ../../../tools_src/fpstool.cpp \
    ../../../tools_src/graphical_library/color.cpp \
    ../../../tools_src/graphical_library/gpcircle.cpp \
    ../../../tools_src/graphical_library/gpline.cpp \
    ../../../tools_src/graphical_library/gprimitive.cpp \
    bubbleanimate.cpp \
    ../../../tools_src/graphical_library/gpplane.cpp \
    ../../../tools_src/graphical_library/gpnumber.cpp \
    selectanimate.cpp \
    insertanim.cpp

HEADERS += \
    application.hpp \
    ../../../tools_src/baseappinst.hpp \
    ../../../tools_src/mainmenu.hpp \
    ../../../tools_src/glfw_engine2D.hpp \
    ../../../tools_src/fpstool.hpp \
    ../../../tools_src/math/undirectedgraph.hpp \
    ../../../tools_src/graphical_library/color.hpp \
    ../../../tools_src/graphical_library/gpcircle.hpp \
    ../../../tools_src/graphical_library/gpline.hpp \
    ../../../tools_src/graphical_library/gprimitive.hpp \
    bubbleanimate.hpp \
    ../../../tools_src/graphical_library/gpplane.hpp \
    ../../../tools_src/graphical_library/gpnumber.hpp \
    selectanimate.hpp \
    insertanim.hpp
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
