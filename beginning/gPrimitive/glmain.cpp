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

    //------------------- CIRCLE -------------------------------------
    mCircle.set_point_size(1);
    mCircle.set_color(Color(eColorType::Maroon));
    mCircle.set(point2D{600, 100});
    mCircle.set_radius(50);
    mCircle.set_segments(15);

    //------------------- FILLED CIRCLE ------------------------------
    mFilledCircle.set_point_size(2);
    mFilledCircle.set_color(Color(eColorType::Olive));
    mFilledCircle.set_fill_color(Color(eColorType::Navy));
    mFilledCircle.set(point2D{800, 100});
    mFilledCircle.set_radius(40);
    mFilledCircle.set_segments(22);

    //------------------- PLANE -------------------------------------
    mPlane.set_color(Color(eColorType::Purple));
    mPlane.set(point2D{50, 400});
    mPlane.set_width(100);
    mPlane.set_height(60);

    //------------------- FILLED PLANE ------------------------------
    mFilledPlane.set_point_size(3);
    mFilledPlane.set_color(Color(eColorType::Red));
    mFilledPlane.set_fill_color(Color(eColorType::Silver));
    mFilledPlane.set(point2D{250, 400});
    mFilledPlane.set_width(100);
    mFilledPlane.set_height(60);

    //------------------- TRIANGLE ----------------------------------
    mTriangle.set_color(Color(eColorType::Teal));
    mTriangle.set(point2D{550, 400}, point2D{550, 450}, point2D{500, 450});

    //------------------- FILLED TRIANGLE ---------------------------
    mFilledTriangle.set_color(Color(eColorType::Yellow));
    mFilledTriangle.set_fill_color(Color(eColorType::White));
    mFilledTriangle.set(point2D{650, 400}, point2D{650, 450}, point2D{600, 450});
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

    drawText(550, 45, "Circle");
    mCircle.draw();

    drawText(750, 45, "Filled Circle");
    mFilledCircle.draw();

    drawText(50, 395, "Plane");
    mPlane.draw();

    drawText(250, 395, "Fillen Plane");
    mFilledPlane.draw();

    drawText(450, 395, "Triangle");
    mTriangle.draw();

    drawText(600, 395, "Filled Triangle");
    mFilledTriangle.draw();
}
