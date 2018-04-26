#ifndef ANGLE_HPP
#define ANGLE_HPP


struct angle
{
  angle();

  void setDegree(float aDegree);

  void setRadian(float aRadian);

  const float &radian()const;
  const float &degree()const;

private:
  float mDegree{0};
  float mRadian{0};
};

#endif // ANGLE_HPP
