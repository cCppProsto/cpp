#ifndef GLMAIN_H
#define GLMAIN_H

#include "glfw_engine2D.hpp"
#include "benderword.h"

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
    benderWord mWorld;
};

#endif // GLMAIN_H
