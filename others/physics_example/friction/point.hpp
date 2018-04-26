#ifndef POINT_HPP
#define POINT_HPP

namespace geo2D
{

struct  point
{
  friend class vector;
  friend class nVector;

  point();
  point(float, float);

  const float &x()const;
  const float &y()const;

  void move(float, float);
  void move_to(float, float);

  void invert();
  void x_invert();
  void y_invert();

private:
  float mX{0.f};
  float mY{0.f};
};

}
#endif // POINT_HPP
