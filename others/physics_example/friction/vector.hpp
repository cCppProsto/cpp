#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "point.hpp"

namespace geo2D
{

struct vector
{
  vector();
  vector(point);
  vector(point, point);

  const float &x()const;
  const float &y()const;
  const float &length()const;
  const point &value()const;
  void invert();

  vector operator +(const vector &);
  vector &operator +=(const vector &);

  vector operator *(float);
  vector &operator *=(float);

private:
  point mValue;
  float mLength;
};

}
#endif // VECTOR_HPP
