#include <iostream>
#include <GL/glut.h>

#include "glmain.h"

using namespace std;



int main(int argcp, char **argv)
{
  /*
    111111
    1   S1
    1  1 1
    1 11 1
    1F   1
    111111
  */
  /*
  std::string path = "/home/ioleshko/tmp/way_1.txt";

  std::ifstream file{path};

  if(file.is_open())
  {
    unsigned lines   = 0;
    unsigned columns = 0;
    file >> lines;
    file >> columns;

    WayMatrix matrix(lines, columns);

    for(unsigned l = 0; l < lines; ++l)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(unsigned c = 0; c < columns; ++c)
        {
            switch (file.get())
            {
              case '1':
              {
                matrix.push(eCell::UNFREE);
                break;
              }
              case ' ':
              {
                matrix.push(eCell::FREE);
                break;
              }
              case 'S':
              {
                matrix.push(eCell::START);
                break;
              }
              case 'F':
              {
                matrix.push(eCell::FINISH);
                break;
              }
            }
        }
    }
  return 0;
  */

  glutInit(&argcp, argv);
  glMain glw;
  glw.run();

  return 0;
}
