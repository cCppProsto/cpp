#include <cmath>
#include "physicalmodel.hpp"
#include "world.hpp"

physicalModel::physicalModel()
{
  _state_recalculation();
}
//----------------------------------------------------------------------------
void physicalModel::setMassa(float aMassa)
{
  mMassa = aMassa;
  _state_recalculation();
}
//----------------------------------------------------------------------------
void physicalModel::setAngleOfSlope(float aDegree)
{
  mAngleSlope.setDegree(aDegree);
  _state_recalculation();
}
//----------------------------------------------------------------------------
bool physicalModel::moveIsPossible()
{
  return mF >= mfs*mN;
}
//----------------------------------------------------------------------------
void physicalModel::accelerationCalculate()
{
  const float &ang = mAngleSlope.radian();
  mAcceleration = world::g * (sin(ang) - mfk*cos(ang)); // moving down
}
//----------------------------------------------------------------------------
const float &physicalModel::gravity_F()
{
  return mGravity;
}
//----------------------------------------------------------------------------
const float &physicalModel::normal_F()
{
  return mN;
}
//----------------------------------------------------------------------------
const float &physicalModel::friction_F()
{
  return mF;
}
//----------------------------------------------------------------------------
const float &physicalModel::acceleration()
{
  return mAcceleration;
}
//----------------------------------------------------------------------------
const angle &physicalModel::angle_slope()
{
  return mAngleSlope;
}
//----------------------------------------------------------------------------
void physicalModel::_state_recalculation()
{
  mGravity  = world::g * mMassa;
  mN        = mGravity * cos(mAngleSlope.radian());
  mF        = mGravity * sin(mAngleSlope.radian());

  mMaxAngleSlope.setRadian(atan(mfs));
}
