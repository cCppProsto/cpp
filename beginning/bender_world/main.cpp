#include <iostream>
#include <GL/glut.h>

using namespace std;

#include "glmain.h"

int main(int argcp, char **argv)
{
    glutInit(&argcp, argv);

    glMain glw;
    glw.run();

    return 0;
}
