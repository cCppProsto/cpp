#include <GL/glut.h>


using namespace std;

#include "menuapp.h"

int main(int argcp, char **argv)
{
  glutInit(&argcp, argv);

  menuApp app;
  app.run();

  return 0;
}







