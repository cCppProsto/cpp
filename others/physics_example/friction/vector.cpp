#include <cmath>
#include "vector.hpp"

namespace geo2D
{

//------------------------------------------------------------------------------
vector::vector()
  :mValue({0, 0})
  ,mLength(0.f)
{

}
//------------------------------------------------------------------------------
vector::vector(point ap1)
  :mValue({ap1.x(), ap1.y()})
  ,mLength(sqrt(mValue.x()* mValue.x() + mValue.y()*mValue.y()))
{

}
//------------------------------------------------------------------------------
vector::vector(point ap1, point ap2)
  :mValue({ap2.x() - ap1.x(), ap2.y() - ap1.y()})
  ,mLength(sqrt(mValue.x()* mValue.x() + mValue.y()*mValue.y()))
{
}
//------------------------------------------------------------------------------
vector vector::operator +(const vector &aValue)
{
  vector tmp(*this);
  tmp.mValue.mX += aValue.mValue.mX;
  tmp.mValue.mY += aValue.mValue.mY;
  return tmp;
}
//------------------------------------------------------------------------------
vector &vector::operator +=(const vector &aValue)
{
  *this = *this + aValue;
  return *this;
}
//------------------------------------------------------------------------------
vector vector::operator *(float aValue)
{
  point p(mValue.mX, mValue.mY);
  p.mX *= aValue;
  p.mY *= aValue;
  return vector({0,0},p);
}
//------------------------------------------------------------------------------
vector &vector::operator *=(float aValue)
{
  *this = *this * aValue;
  return *this;
}
//------------------------------------------------------------------------------
void vector::invert()
{
  mValue.invert();
}
//------------------------------------------------------------------------------
const float &vector::x()const
{
  return mValue.x();
}
//------------------------------------------------------------------------------
const float &vector::y()const
{
  return mValue.y();
}
//------------------------------------------------------------------------------
const point &vector::value()const
{
  return mValue;
}
//------------------------------------------------------------------------------
const float &vector::length()const
{
  return mLength;
}
}
