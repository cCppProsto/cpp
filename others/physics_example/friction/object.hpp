#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include "gpcircle.hpp"
#include "gpline.hpp"
#include "physicalmodel.hpp"
#include "vector.hpp"
using namespace cpp_prosto::graphical;

struct object
{
  object();
  object(const object&) = delete;
  object &operator=(const object&) = delete;

  void move();
  void draw();

private:
  void _move_draw_objects();

private:

  bool    mIsMoving{false};
  float   mdX{0.0f};
  float   mdY{0.0f};
  gpLine  mLine1;
  gpLine  mLine2;
  gpLine  mLine3;
  gpLine  mLine4;

  physicalModel mModel;
  geo2D::vector mvAcceleration;
  geo2D::vector mvSpeed;
};

#endif // OBJECT_HPP
