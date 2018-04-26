#include "object.hpp"

//------------------------------------------------------------------------------
object::object()
{
  mCircle.set_radius(mRadius);
  mCircle.move(100, 0);
  mCircle.set_point_size(4);
  mCircle.set_segments(20);
  mCircle.set_color(Color(eColorType::Green));
  mCircle.set_fill_color(Color(eColorType::Red));

  mModel.setPosition({100,0});
}
//------------------------------------------------------------------------------
void object::setWind(geo2D::force aWind)
{
  mWind = aWind;
  mModel.addForce(mWind);
}
//------------------------------------------------------------------------------
void object::setGravity(geo2D::force aGravity)
{
  mGravity = aGravity;
  mModel.addForce(mGravity);
}
//------------------------------------------------------------------------------
void object::setVelocity(geo2D::vector aVelocity)
{
  mVelocity = aVelocity;
  mModel.setVelocityV(aVelocity);
}
//------------------------------------------------------------------------------
void object::update()
{
  mModel.tick();
  mX = mModel.position().x();
  mY = mModel.position().y();

  _move_draw_objects();
}
//------------------------------------------------------------------------------
void object::draw()
{
  mCircle.draw();
}
//------------------------------------------------------------------------------
void object::_move_draw_objects()
{
  const int &centerX = mCircle.center().x;
  const int &centerY = mCircle.center().y;

  float tx = mX - centerX;
  float ty = mY - centerY;
  mCircle.move(tx, ty);
}
