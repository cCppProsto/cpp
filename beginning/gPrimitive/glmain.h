#ifndef GLMAIN_H
#define GLMAIN_H

#include "glfw_engine2D.hpp"

#include "gppoint.hpp"
#include "gpline.hpp"


using namespace cpp_prosto::graphical;

struct glMain : glfw_engine2D
{
    glMain();

    void drawGLFW() override;
    void keyEvent(GLFWwindow *, int, int, int, int) override;
    void mouseKeyEvent(GLFWwindow *, int, int, int) override;

private:
    void init();
    void processing();
    void draw();

private:
    gpPoint point;
    gpLine  l1;
    gpLine  l2;
};

#endif // GLMAIN_H
