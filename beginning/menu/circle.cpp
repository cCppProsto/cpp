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
}
//------------------------------------------------------------------------------
void circle::move()
{
  const int &centerX = mCircle.center().x;
  const int &centerY = mCircle.center().y;
  const int &radius  = mCircle.radius();

  float tmp_x = mX + mDx * mSpeed;
  float tmp_y = mY + mDy * mSpeed;

  if(tmp_x - radius <= 0)
    mDx *= -1.0f;
  else if(tmp_x + radius >= 1024)
    mDx *= -1.0f;

  if(tmp_y - radius <= 0)
    mDy *= -1.0f;
  else if(tmp_y + radius >= 768)
    mDy *= -1.0f;

  mX += mDx * mSpeed;
  mY += mDy * mSpeed;

  mCircle.move(mX - centerX, mY - centerY);
}
//------------------------------------------------------------------------------
void circle::draw()
{
  mCircle.draw();
}
//------------------------------------------------------------------------------
void circle::add_point_to_move(float aX, float aY)
{
  mToX = aX;
  mToY = aY;

  float t1 = mToX - mX;
  float t2 = mToY - mY;
  float l = sqrt(t1*t1 + t2*t2);

  mDx = t1/l;
  mDy = t2/l;
}
//------------------------------------------------------------------------------
void circle::clear_fill()
{
  mCircle.disableFill();
}
//------------------------------------------------------------------------------
void circle::check_collision_and_fill(circle &aCircle)
{
  int dist = fast_distance(*this, aCircle);
  int r1 = mCircle.radius();
  int r2 = aCircle.radius();

  dist = dist - r1 - r2;
  if(dist <= 0)
    mCircle.enableFill();
}
//------------------------------------------------------------------------------
void circle::set_speed(float aSpeed)
{
  if(aSpeed >= 0.0f)
    mSpeed = aSpeed;
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

