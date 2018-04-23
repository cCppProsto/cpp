#ifndef CIRCLE_H
#define CIRCLE_H

#include <memory>
#include "gpcircle.hpp"
#include "gpline.hpp"
#include "vector2D.h"

using namespace cpp_prosto::graphical;
using namespace cpp_prosto::math;
struct circle final
{
  circle(float aX, float aY);
  circle(const circle&) = delete;
  circle &operator=(const circle&) = delete;

  void move();
  void draw();

  void set_speed(float);
  void set_gravity(float);

  const int &radius()const;
  const int &x()const;
  const int &y()const;
  const float &speed()const;

private:
  void _move_draw_objects();

private:
  float    mX{0.0f};
  float    mY{0.0f};
  float    mXs{0.0f};
  float    mYs{0.0f};
  float    mGravity{0.4f};
  float    mStartSpeed{15.0f};
  float    mStartAngle{45.0f};
  int      mRadius{30};
  gpCircle mCircle;
};

#endif // CIRCLE_H
