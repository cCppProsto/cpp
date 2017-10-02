#include "circle.h"

// 3.5% error
int fast_distance(const circle &ac1, const circle &ac2)
{
  int x1 = ac1.x();
  int x2 = ac2.x();
  int y1 = ac1.y();
  int y2 = ac2.y();

  int x = abs(x1 - x2);
  int y = abs(y1 - y2);

  int min = x > y ? y : x;
  return(x + y -(min >> 1) - (min >> 2) + (min>>4));
}

circle::circle(float aX, float aY, float radius)
  :mX(aX)
  ,mY(aY)
{
  mCircle.set_radius(radius);
  mCircle.move(mX, mY);
  mCircle.set_segments(20);
  mCircle.set_color(Color(eColorType::Green));

  mCircle.set_fill_color(Color(eColorType::Red));
  mCircle.disableFill();

  mLineVDir.set(point2D{0,0}, point2D{0,0});
  mLineVDir.set_color(Color(eColorType::Red));
}
//------------------------------------------------------------------------------
void circle::move()
{
  _screen_borders_proc();

  mX += mSpeedVector.x();
  mY += mSpeedVector.y();

  _move_draw_objects();
}
//------------------------------------------------------------------------------
void circle::_screen_borders_proc()
{
  const int &radius  = mCircle.radius();

  float new_x = mX + mSpeedVector.x();
  float new_y = mY + mSpeedVector.y();

  if((new_x - radius <= 0) || (new_x + radius >= 1024))
  {
    mSpeedVector.revert_x();
    mDirVector.revert_x();
  }

  if((new_y - radius <= 0) || (new_y + radius >= 768))
  {
    mSpeedVector.revert_y();
    mDirVector.revert_y();
  }
}
//------------------------------------------------------------------------------
void circle::_move_draw_objects()
{
  const int &centerX = mCircle.center().x;
  const int &centerY = mCircle.center().y;

  int tx = mX - centerX;
  int ty = mY - centerY;
  mCircle.move(tx, ty);
  mLineVDir.move(tx, ty);
}
//------------------------------------------------------------------------------
void circle::draw()
{
  mCircle.draw();

  int x = mX + (mDirVector.x()) * radius();
  int y = mY + (mDirVector.y()) * radius();
  mLineVDir.set_point(point2D{(int)mX, (int)mY}, 0);
  mLineVDir.set_point(point2D{x, y}, 1);

  mLineVDir.draw();
}
//------------------------------------------------------------------------------
void circle::add_point_to_move(float aX, float aY)
{
  mDirVector.set_p1_p2(mX, mY, aX, aY);
  mSpeedVector = mDirVector;

  int x = mX + mDirVector.x() * mCircle.radius();
  int y = mY + mDirVector.y() * mCircle.radius();

  mLineVDir.set_point(point2D{(int)mX, (int)mY}, 0);
  mLineVDir.set_point(point2D{x, y}, 1);
}
//------------------------------------------------------------------------------
void circle::clear_fill()
{
  mCircle.disableFill();
}
//------------------------------------------------------------------------------
bool circle::check_collision_and_fill(circle &aCircle)
{
  int dist = fast_distance(*this, aCircle);
  int r1 = mCircle.radius();
  int r2 = aCircle.radius();

  dist = dist - r1 - r2;
  if(dist <= 0)
  {
    _collision_proc(aCircle);
    return true;
  }
  return false;
}
//------------------------------------------------------------------------------
void circle::_collision_proc(circle &aCircle)
{
  mCircle.enableFill();

  vector2DNorm v1;
  vector2DNorm v2;

  const int &this_x  = mCircle.center().x;
  const int &this_y  = mCircle.center().y;
  const int &other_x = aCircle.mCircle.center().x;
  const int &other_y = aCircle.mCircle.center().y;

  v1.set_p1_p2(this_x, this_y, other_x, other_y);

  v2 = v1 * -1.f;

  mDirVector         += v2;
  aCircle.mDirVector += v1;

  std::swap(mSpeed, aCircle.mSpeed);

  mSpeedVector         = mDirVector * mSpeed;
  aCircle.mSpeedVector = aCircle.mDirVector * aCircle.mSpeed;
}
//------------------------------------------------------------------------------
void circle::set_speed(float aSpeed)
{
  if(aSpeed >= 0.0f)
  {
    mSpeed        = aSpeed;
    mSpeedVector *= mSpeed;
  }
}
//------------------------------------------------------------------------------
void circle::speed_change(float aChangeValue)
{
  if((mSpeed + aChangeValue) >= 0.0f)
    mSpeed += aChangeValue;
}
//------------------------------------------------------------------------------
const int &circle::radius()const
{
  const int &res = mCircle.radius();
  return res;
}
//------------------------------------------------------------------------------
const int &circle::x()const
{
  const int &res = mCircle.point(0).x;
  return res;
}
//------------------------------------------------------------------------------
const int &circle::y()const
{
  const int &res = mCircle.point(0).y;
  return res;
}
//------------------------------------------------------------------------------
const float &circle::speed()const
{
  return mSpeed;
}

