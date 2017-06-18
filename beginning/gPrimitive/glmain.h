#ifndef GLMAIN_H
#define GLMAIN_H

#include "glfw_engine2D.hpp"

#include "gppoint.hpp"
#include "gpline.hpp"
#include "gplines.hpp"
#include "gpopenlines.hpp"
#include "gpclosedlines.hpp"
#include "gpcircle.hpp"
#include "gpplane.hpp"
#include "gptriangle.hpp"
#include "gpgrid.hpp"

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
    gpPoint       mPoint;
    gpLine        mLine;
    gpLines       mLines;
    gpOpenLines   mOpenLines;
    gpClosedLines mClosedLines;
    gpCircle      mCircle;
    gpCircle      mFilledCircle;
    gpPlane       mPlane;
    gpPlane       mFilledPlane;
    gpTriangle    mTriangle;
    gpTriangle    mFilledTriangle;
    gpGrid        mGrid;
    gpGrid        mFilledGrid;
};

#endif // GLMAIN_H
