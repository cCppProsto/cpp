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
  const int &centerX = mCircle.center().x;
  const int &centerY = mCircle.center().y;
  const int &radius  = mCircle.radius();

  float new_x = mX + mVDir.x();
  float new_y = mY + mVDir.y();

  if((new_x - radius <= 0) || (new_x + radius >= 1024))
    mVDir.revert_x();

  if((new_y - radius <= 0) || (new_y + radius >= 768))
    mVDir.revert_y();

  mX += mVDir.x();
  mY += mVDir.y();

  int tx = mX - centerX;
  int ty = mY - centerY;
  mCircle.move(tx, ty);
  mLineVDir.move(tx, ty);
}
//------------------------------------------------------------------------------
void circle::draw()
{
  mCircle.draw();

  int x = mX + (mVDir.x()/mSpeed) * radius();
  int y = mY + (mVDir.y()/mSpeed) * radius();
  mLineVDir.set_point(point2D{(int)mX, (int)mY}, 0);
  mLineVDir.set_point(point2D{x, y}, 1);

  mLineVDir.draw();
}
//------------------------------------------------------------------------------
void circle::add_point_to_move(float aX, float aY)
{
  mVDir.set_p1_p2(mX, mY, aX, aY);

  int x = mX + mVDir.x() * mCircle.radius();
  int y = mY + mVDir.y() * mCircle.radius();

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
    mCircle.enableFill();

    vector2DNorm v1;
    vector2DNorm v2;

    v1.set_p1_p2(mCircle.center().x, mCircle.center().y,
                 aCircle.mCircle.center().x, aCircle.mCircle.center().y);

    v2 = v1 * -1.f;

    mVDir         += v2;
    aCircle.mVDir += v1;
    std::swap(mSpeed, aCircle.mSpeed);
    mVDir *= mSpeed;
    aCircle.mVDir *= aCircle.mSpeed;
    return true;
  }
  return false;
}
//------------------------------------------------------------------------------
void circle::set_speed(float aSpeed)
{
  if(aSpeed >= 0.0f)
  {
    mSpeed = aSpeed;
    mVDir *= mSpeed;
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

