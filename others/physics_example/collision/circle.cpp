#include "circle.h"

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
}
//------------------------------------------------------------------------------
void circle::collision(circle &aObj)
{
  float v1, v2;

  v1 = (  (2*aObj.mMassa*aObj.mSpeed)
          +
          (mMassa - aObj.mMassa)*mSpeed)
        / (mMassa + aObj.mMassa);

  v2 = (  (2*mMassa*mSpeed)
          +
          (aObj.mMassa - mMassa)*aObj.mSpeed)
        / (mMassa + aObj.mMassa);

  mSpeed      = v1;
  aObj.mSpeed = v2;
}
//------------------------------------------------------------------------------
void circle::move()
{
  mX += mSpeed;
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
  mSpeed = aSpeed;
}
//------------------------------------------------------------------------------
void circle::set_massa(float aMassa)
{
  mMassa = aMassa;
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
  return mSpeed;
}

