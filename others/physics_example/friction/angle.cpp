#include <cmath>
#include "angle.hpp"

angle::angle()
{
}
//------------------------------------------------------------------------------
void angle::setDegree(float aDegree)
{
  mDegree = aDegree;
  mRadian = mDegree*M_PI/180.f;
}
//------------------------------------------------------------------------------
void angle::setRadian(float aRadian)
{
  mRadian = aRadian;
  mDegree = mRadian* 180.f/M_PI;
}
//------------------------------------------------------------------------------
const float &angle::radian()const { return mRadian; }
//------------------------------------------------------------------------------
const float &angle::degree()const { return mDegree; }
