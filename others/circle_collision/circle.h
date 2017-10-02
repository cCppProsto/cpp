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
  circle(float aX, float aY, float radius);
  circle(const circle&) = delete;
  circle &operator=(const circle&) = delete;

  void move();
  void draw();
  void add_point_to_move(float aX, float aY);

  void clear_fill();
  bool check_collision_and_fill(circle &);

  void set_speed(float);
  void speed_change(float);

  const int &radius()const;
  const int &x()const;
  const int &y()const;
  const float &speed()const;

private:
  float mX{0.0f};
  float mY{0.0f};
  float mSpeed{1.0f};

  gpCircle mCircle;
  gpLine   mLineVDir;
  vector2DNorm mVDir;
};

#endif // CIRCLE_H
