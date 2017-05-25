#include "glmain.h"


using namespace cpp_prosto::graphical;

//------------------------------------------------------------------------------
glMain::glMain()
    :glfw_engine2D("gPrimitive")
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
    point.set(point2D{50, 50});
    point.set_point_size(5);
    point.set_color(Color(eColorType::Maroon));

    l1.set_color(Color(eColorType::Red));
    l1.set(point2D{100, 100}, point2D{150, 150});

    l2.set_point_size(4);
    l2.set_color(Color(eColorType::Green));
    l2.set(point2D{200, 100}, point2D{250, 200});
}
//------------------------------------------------------------------------------
void glMain::processing()
{
}
//------------------------------------------------------------------------------
void glMain::draw()
{
    point.draw();
    l1.draw();
    l2.draw();
}
