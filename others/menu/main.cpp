#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include <cmath>
#include <memory>

using namespace std;

#include "menuapp.h"

struct vec
{
  float x;
  float y;
};

struct obj
{
  obj(float aX, float aY)
    :x(aX)
    ,y(aY)
  {
  }
  void move()
  {
    x += dx * speed;
    y += dy * speed;
  }

  void add_point_to_move(float aX, float aY)
  {
    float t1 = aX - x;
    float t2 = aY - y;
    float l = sqrt(t1*t1 + t2*t2);

    dx = t1/l;
    dy = t2/l;
  }

private:
  float x;
  float y;
  float speed{1.0f};

  float dx;
  float dy;
};

int main(int argcp, char **argv)
{
  /*
  std::unique_ptr<obj> pp;
  pp = std::make_unique<obj>(1,2);
  pp = std::make_unique<obj>(2,1);

  obj o(100, 100);

  o.add_point_to_move(200, 200);
  o.move();
  o.move();

  o.add_point_to_move(200, 100);
  o.move();
  o.move();

  o.add_point_to_move(100, 200);
  o.move();
  o.move();

  o.add_point_to_move(0, 0);
  o.move();
  o.move();
  */

  glutInit(&argcp, argv);

  menuApp app;
  app.run();

  return 0;
}







