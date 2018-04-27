#include "object.hpp"

//------------------------------------------------------------------------------
object::object()
{
  mCircle.set_radius(mRadius);
  mCircle.set_point_size(4);
  mCircle.set_segments(20);
  mCircle.set_color(Color(eColorType::Green));
  mCircle.set_fill_color(Color(eColorType::Red));

  mCircle.move(100, 0);
  mModel.setPosition({100,0});
}
//------------------------------------------------------------------------------
void object::setPosition(geo2D::point aPoint)
{
  mCircle.set_point({aPoint.x(), aPoint.y()}, 0);
  mModel.setPosition({aPoint.x(),aPoint.y()});
}
//------------------------------------------------------------------------------
void object::setWind(geo2D::force aWind)
{
  mModel.removeForce(mWind);
  mWind = aWind;
  mModel.addForce(mWind);
}
//------------------------------------------------------------------------------
void object::setGravity(geo2D::force aGravity)
{
  mModel.removeForce(mGravity);
  mGravity = aGravity;
  mModel.addForce(mGravity);
}
//------------------------------------------------------------------------------
void object::removeWind()
{
  mModel.removeForce(mWind);
  mWind.clear();
}
//------------------------------------------------------------------------------
void object::removeGravity()
{
  mModel.removeForce(mGravity);
  mGravity.clear();
}
//------------------------------------------------------------------------------
void object::setVelocity(geo2D::vector aVelocity)
{
  mVelocity = aVelocity;
  mModel.setVelocityV(aVelocity);
}
//------------------------------------------------------------------------------
void object::setFriction(float aFriction)
{
  mModel.setFrictionCoefficient(aFriction);
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
void object::bottom_border_collision()
{
  mModel.bottom_border_collision();
}
//------------------------------------------------------------------------------
const geo2D::point &object::position()const
{
  return mModel.position();
}
//------------------------------------------------------------------------------
void object::draw()
{
  mCircle.draw();
}
//------------------------------------------------------------------------------
void object::_move_draw_objects()
{
  const float &centerX = mCircle.center().x;
  const float &centerY = mCircle.center().y;

  float tx = mX - centerX;
  float ty = mY - centerY;
  mCircle.move(tx, ty);
}
