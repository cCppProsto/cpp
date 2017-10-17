#include <GL/glut.h>
#include <iostream>
#include "application.hpp"

int main(int argcp, char **argv)
{
  glutInit(&argcp, argv);

  application app;
  app.run();
  return 0;
}
