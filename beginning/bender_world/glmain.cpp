#include "glmain.h"

using namespace cpp_prosto::graphical;

//------------------------------------------------------------------------------
glMain::glMain() : glfw_engine2D("Bender world")
{
    init();
}
//------------------------------------------------------------------------------
void glMain::drawGLFW()
{
    processing();

    draw();
}
//------------------------------------------------------------------------------
void glMain::keyEvent(GLFWwindow *, int, int, int, int)
{
}
//------------------------------------------------------------------------------
void glMain::mouseKeyEvent(GLFWwindow *, int, int, int)
{
}
//------------------------------------------------------------------------------
void glMain::init()
{
    mWorld.setScreenHeight(height());

    mWorld.loadMap("D:\\tmp\\codingame\\bender_1.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_2.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_3.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_4.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_5.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_6.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_7.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_8.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_9.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_10.txt");
//    mWorld.loadMap("D:\\tmp\\codingame\\bender_11.txt");
}
//------------------------------------------------------------------------------
void glMain::processing()
{
    static int isMove = 0;
    if(++isMove == 5)
    {
        mWorld.step();
        isMove = 0;
    }
}
//------------------------------------------------------------------------------
void glMain::draw()
{
    mWorld.draw();
}
