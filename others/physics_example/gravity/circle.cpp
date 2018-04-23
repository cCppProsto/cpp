#include "circle.h"


/*
  vix = vi*cos(ang)
  viy = vi*sin(ang)

  vy(t) = viy - g*t

  y(t) = viy - (g*t*t)/2

  0
  t = viy/g = vi*sin(ang)/g
  t_all = 2*t

  x_all = (2*vix*viy)/g
        = (2*vi * cos(ang) * vi * sin(ang)) / g
        = ((vi*vi)/g) sin(2*ang)
*/

circle::circle(float aX, float aY)
  :mX(aX)
  ,mY(aY)
{
  mCircle.set_radius(mRadius);
  mCircle.move(mX, mY);
  mCircle.set_point_size(4);
  mCircle.set_segments(20);
  mCircle.set_color(Color(eColorType::Green));
  mCircle.set_fill_color(Color(eColorType::Red));

  // convert angle to radians
  float angle = (float)mStartAngle*M_PI/(float)180;
  mXs =  mStartSpeed * cos(angle);
  mYs = -mStartSpeed * sin(angle);
}
//------------------------------------------------------------------------------
void circle::move()
{
  mX  += mXs;
  mY  += mYs;
  mYs += mGravity;
  mXs += 0.1;// wind
  _move_draw_objects();
}
//------------------------------------------------------------------------------
void circle::_move_draw_objects()
{
  const int &centerX = mCircle.center().x;
  const int &centerY = mCircle.center().y;

  int tx = mX - centerX;
  int ty = mY - centerY;
  mCircle.move(tx, ty);
}
//------------------------------------------------------------------------------
void circle::draw()
{
  mCircle.draw();
}
//------------------------------------------------------------------------------
void circle::set_speed(float aSpeed)
{
  mYs = aSpeed;
}
//------------------------------------------------------------------------------
void circle::set_gravity(float aGravity)
{
  mGravity = aGravity;
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
const int &circle::radius()const
{
  return mRadius;
}
//------------------------------------------------------------------------------
const float &circle::speed()const
{
  return mYs;
}

