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
    //------------------- INIT POINT ---------
    mPoint.set(point2D{50, 50});
    mPoint.set_point_size(3);
    mPoint.set_color(Color(eColorType::Aqua));

    //------------------- INIT LINE ---------------
    mLine.set_point_size(4);
    mLine.set_color(Color(eColorType::Blue));
    mLine.set(point2D{50, 100}, point2D{50, 200});

    //------------------- INIT LINES --------------------------
    mLines.set_color(Color(eColorType::Fuchsia));
    for(int i = 0; i < 10; ++i)
        mLines.add(gpLine{{250, i*10 + 50}, {450, i*10 + 50}});

    for(int i = 0; i < 21; ++i)
        mLines.add(gpLine{{250 + i*10, 50}, {250 + i*10, 140}});

    //------------------- INIT OPEN LINES --------------------------
    mOpenLines.set_point_size(3);
    mOpenLines.set_color(Color(eColorType::Gray));
    mOpenLines.add(point2D{250, 300});
    mOpenLines.add(point2D{300, 200});
    mOpenLines.add(point2D{350, 300});
    mOpenLines.add(point2D{400, 200});

    //------------------- INIT ClOSED LINES --------------------------
    mClosedLines.set_point_size(1);
    mClosedLines.set_color(Color(eColorType::Lime));
    mClosedLines.add(point2D{450, 300});
    mClosedLines.add(point2D{500, 200});
    mClosedLines.add(point2D{550, 300});
    mClosedLines.add(point2D{600, 200});
}
//------------------------------------------------------------------------------
void glMain::processing()
{
}
//------------------------------------------------------------------------------
void glMain::draw()
{
    drawText(50, 45, "Point");
    mPoint.draw();

    drawText(50, 95, "Line");
    mLine.draw();

    drawText(250, 45, "Lines");
    mLines.draw();

    drawText(250, 195, "Open Lines");
    mOpenLines.draw();

    drawText(450, 195, "Closed Lines");
    mClosedLines.draw();
}
