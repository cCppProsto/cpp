#include "object.hpp"

//------------------------------------------------------------------------------
object::object()
{
  mLine1.set_point({245, 768 - 195}, 0);
  mLine1.set_point({282, 768 - 267}, 1);

  mLine2.set_point({282, 768 - 267}, 0);
  mLine2.set_point({437, 768 - 196}, 1);

  mLine3.set_point({437, 768 - 196}, 0);
  mLine3.set_point({403, 768 - 127}, 1);

  mLine4.set_point({403, 768 - 127}, 0);
  mLine4.set_point({245, 768 - 195}, 1);

  mLine1.set_color(Color(eColorType::Blue));
  mLine1.set_point_size(2);

  mLine2.set_color(Color(eColorType::Blue));
  mLine2.set_point_size(2);

  mLine3.set_color(Color(eColorType::Blue));
  mLine3.set_point_size(2);

  mLine4.set_color(Color(eColorType::Blue));
  mLine4.set_point_size(2);

  mModel.setAngleOfSlope(23.4);
}
//------------------------------------------------------------------------------
void object::move()
{
  if(!mIsMoving)
  {
    if(mModel.moveIsPossible())
    {
      mModel.accelerationCalculate();
      mIsMoving = true;

      float x = mModel.acceleration() * cos(mModel.angle_slope().radian());
      float y = mModel.acceleration() * sin(mModel.angle_slope().radian());
      mvAcceleration = geo2D::vector({x,y});
    }
  }
  else
  {
    mdX = mvAcceleration.x();
    mdY = mvAcceleration.y();

    //mvSpeed += mvAcceleration;
    //mdX = mvSpeed.x();
    //mdY = mvSpeed.y();

    mLine1.move(mdX, mdY);
    mLine2.move(mdX, mdY);
    mLine3.move(mdX, mdY);
    mLine4.move(mdX, mdY);
  }
}
//------------------------------------------------------------------------------
void object::draw()
{
  mLine1.draw();
  mLine2.draw();
  mLine3.draw();
  mLine4.draw();
}
//------------------------------------------------------------------------------
void object::_move_draw_objects()
{

}
