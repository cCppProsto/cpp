#ifndef PHYSICALMODEL_HPP
#define PHYSICALMODEL_HPP

#include "angle.hpp"
#include "vector.hpp"

struct physicalModel
{
  physicalModel();
  void setMassa(float);
  void setAngleOfSlope(float);
  bool moveIsPossible();
  void accelerationCalculate();

  const float &gravity_F();
  const float &normal_F();
  const float &friction_F();
  const float &acceleration();
  const angle &angle_slope();

private:
  void _state_recalculation();

private:
  float mMassa{1.f};

  float mGravity;  // = m * g
  float mN;        // = m * g * cos(A)
  float mF;        // = m * g * sin(A)

  float mfs{0.4f};  // static coefficient of friction
  float mfk{0.4f};  // kinetic coefficient of friction

  float mAcceleration{0.f};
  angle mAngleSlope;
  angle mMaxAngleSlope;
};

#endif // PHYSICALMODEL_HPP
