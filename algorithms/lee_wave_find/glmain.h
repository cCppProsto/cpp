#ifndef GLMAIN_H
#define GLMAIN_H

#include <vector>
#include "glfw_engine2D.hpp"
#include "gprimitive.hpp"
#include "gpplane.hpp"
#include "gpgrid.hpp"
#include "lee_wave_finder.hpp"

using namespace cpp_prosto::graphical;
using namespace cpp_prosto::alg_way::lee_wave;

void redraw();

struct glMain : glfw_engine2D
{
  friend void redraw();

  glMain();

  void drawGLFW() override;
  void keyEvent(GLFWwindow *, int, int, int, int) override;
  void mouseKeyEvent(GLFWwindow *, int, int, int) override;

private:
  void init();
  void processing();
  void draw();

  void draw_select(unsigned, unsigned);

private:
  unsigned  mDrawObjSize{0};
  unsigned  mMaxCellCost;
  bool      mIsFound{false};
  WayMatrix *mpMatrix{nullptr};
  point      mStart{0,0};
  point      mFinish{0,0};
  gpGrid     mGrid;
  std::vector<unsigned>  mWeigthArray;
};

#endif // GLMAIN_H
