#include "glmain.h"

#include <fstream>
#include <limits>
#include <queue>
#include <chrono>
#include <thread>

#include "lee_wave_finder.hpp"

using namespace cpp_prosto::graphical;
using namespace cpp_prosto::alg_way::lee_wave;

using namespace std::chrono_literals;

//------------------------------------------------------------------------------
glMain::glMain() : glfw_engine2D("Algorithm of finding of the shortest way(Lee, Wave, ...)")
{
  init();
}
//------------------------------------------------------------------------------
void glMain::drawGLFW()
{
  processing();
}
//------------------------------------------------------------------------------
void glMain::keyEvent(GLFWwindow *, int, int, int, int)
{
}
//------------------------------------------------------------------------------
void glMain::mouseKeyEvent(GLFWwindow *, int, int, int)
{
}
//------------------------------------------------------------------------------
void glMain::init()
{
  //std::string path = "/home/ioleshko/tmp/way_1.txt";
  //std::string path = "/home/ioleshko/tmp/way_2.txt";
  //std::string path = "/home/ioleshko/tmp/way_3.txt";
  //std::string path = "/home/ioleshko/tmp/way_4.txt";
  std::string path = "/home/ioleshko/tmp/way_5.txt";

  std::ifstream file{path};

  if(file.is_open())
  {
    unsigned lines   = 0;
    unsigned columns = 0;
    file >> lines;
    file >> columns;

    mpMatrix = new WayMatrix(lines, columns);

    for(unsigned l = 0; l < lines; ++l)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(unsigned c = 0; c < columns; ++c)
        {
            switch (file.get())
            {
              case '1':
              {
                mpMatrix->push(eCell::UNFREE);
                break;
              }
              case ' ':
              {
                mpMatrix->push(eCell::FREE);
                break;
              }
              case 'S':
              {
                mpMatrix->push(eCell::START);
                break;
              }
              case 'F':
              {
                mpMatrix->push(eCell::FINISH);
                break;
              }
            }
        }
    }

    mDrawObjSize = height() / columns;
    mGrid.set(point2D{0, 0}, mDrawObjSize, mDrawObjSize, lines, columns);
    mGrid.set_color(Color(eColorType::Green));
  }
}

std::pair<point, point> find_start_finish(const WayMatrix &aMatrix)
{
  std::pair<point, point> res{{0,0},{0,0}};

  for(unsigned l = 0; l < aMatrix.lines();++l)
    for(unsigned c = 0; c < aMatrix.columns(); ++c)
    {
      if(aMatrix.get(l, c) == eCell::START)
        res.first = {l,c};
      if(aMatrix.get(l, c) == eCell::FINISH)
        res.second = {l,c};
    }
  return res;
}
//------------------------------------------------------------------------------
void glMain::processing()
{
  mMaxCellCost = mpMatrix->lines() * mpMatrix->columns();
  mWeigthArray.resize(mpMatrix->lines() * mpMatrix->columns(), mMaxCellCost);

  draw();

  std::pair<point, point> res;
  res     = find_start_finish(*mpMatrix);
  mStart  = res.first;
  mFinish = res.second;

  mMaxCellCost = mpMatrix->columns() * mpMatrix->lines();
  mWeigthArray[mStart.first * mpMatrix->columns() + mStart.second] = 0;
  mIsFound = false;

  std::queue<point> _queque;
  _queque.push({mStart.first, mStart.second});

  std::pair<bool, point> points_pair;

  while(_queque.size() > 0)
  {
    point tmp = _queque.front();
    _queque.pop();

    {
      points_pair = {false,{0,0}};
      auto aL  = tmp.first;
      auto aC  = tmp.second;
      auto l   = aL - 1;
      auto val = mWeigthArray[aL*mpMatrix->columns() + aC] + 1;

      if(mpMatrix->get(l, aC) == eCell::FINISH)
        mIsFound = true;

      if(mpMatrix->get(l, aC) == eCell::FREE)
      {
        if(mWeigthArray[l*mpMatrix->columns() + aC] == mMaxCellCost)
        {
          points_pair.first         = true;
          points_pair.second.first  = l;
          points_pair.second.second = aC;
          mWeigthArray[l*mpMatrix->columns() + aC] = val;
          draw_select(l, aC);
        }
      }
    }

    if(points_pair.first == true)
      _queque.push(points_pair.second);

    {
      points_pair = {false,{0,0}};
      auto aL  = tmp.first;
      auto aC  = tmp.second;
      auto c   = aC + 1;
      auto val = mWeigthArray[aL*mpMatrix->columns() + aC] + 1;

      if(mpMatrix->get(aL, c) == eCell::FINISH)
        mIsFound = true;

      if(mpMatrix->get(aL, c) == eCell::FREE)
      {
        if(mWeigthArray[aL*mpMatrix->columns() + c] == mMaxCellCost)
        {
          points_pair.first         = true;
          points_pair.second.first  = aL;
          points_pair.second.second = c;
          mWeigthArray[aL*mpMatrix->columns() + c] = val;
          draw_select(aL, c);
        }
      }
    }
    if(points_pair.first == true)
      _queque.push(points_pair.second);

    {
      points_pair = {false,{0,0}};
      auto aL  = tmp.first;
      auto aC  = tmp.second;
      auto l   = aL + 1;
      auto val = mWeigthArray[aL*mpMatrix->columns() + aC] + 1;

      if(mpMatrix->get(l, aC) == eCell::FINISH)
        mIsFound = true;

      if(mpMatrix->get(l, aC) == eCell::FREE)
      {
        if(mWeigthArray[l*mpMatrix->columns() + aC] == mMaxCellCost)
        {
          points_pair.first         = true;
          points_pair.second.first  = l;
          points_pair.second.second = aC;
          mWeigthArray[l*mpMatrix->columns() + aC] = val;
          draw_select(l, aC);
        }
      }
    }

    if(points_pair.first == true)
      _queque.push(points_pair.second);

    {
      points_pair = {false,{0,0}};
      auto aL  = tmp.first;
      auto aC  = tmp.second;
      auto c   = aC - 1;
      auto val = mWeigthArray[aL*mpMatrix->columns() + aC] + 1;

      if(mpMatrix->get(aL, c) == eCell::FINISH)
        mIsFound = true;

      if(mpMatrix->get(aL, c) == eCell::FREE)
      {
        if(mWeigthArray[aL*mpMatrix->columns() + c] == mMaxCellCost)
        {
          points_pair.first         = true;
          points_pair.second.first  = aL;
          points_pair.second.second = c;
          mWeigthArray[aL*mpMatrix->columns() + c] = val;
          draw_select(aL, c);
        }
      }
    }

    if(points_pair.first == true)
      _queque.push(points_pair.second);
  }

  if(mIsFound)
  {
    finder f(*mpMatrix);
    f.find(eFindType::NEUMANN);
    std::stack<eDirection> path = f.get();

    auto l = mStart.first;
    auto c = mStart.second;
    while(!path.empty())
    {
      eDirection dir = path.top();

      draw_select(l, c);
      std::this_thread::sleep_for(250ms);
      switch(dir)
      {
        case eDirection::UP:
        {
          l--;
          break;
        }

        case eDirection::RIGHT:
        {
          c++;
          break;
        }

        case eDirection::LEFT:
        {
          c--;
          break;
        }

        case eDirection::DOWN:
        {
          l++;
          break;
        }

        case eDirection::UP_RIGHT:
        case eDirection::DOWN_RIGHT:
        case eDirection::DOWN_LEFT:
        case eDirection::UP_LEFT:
        {
          break;
        }
      }

      path.pop();
    }
  }

  std::this_thread::sleep_for(2s);
  glfwTerminate();
}
//------------------------------------------------------------------------------
void glMain::draw_select(unsigned aL, unsigned aC)
{
  unsigned x = 0;
  unsigned y = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  mGrid.draw();
  for(unsigned l = 0; l < mpMatrix->lines(); ++l)
  {
    y = (mDrawObjSize * l) + 20;
    for(unsigned c = 0; c < mpMatrix->columns(); ++c)
    {
      x = mDrawObjSize * c + 5;

      if(mpMatrix->get(l, c) == eCell::FREE)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width, width};
        plane.set_color(Color(eColorType::Gray));
        plane.set_fill_color(Color(eColorType::Gray));
        plane.draw();
      }

      if(mpMatrix->get(l, c) == eCell::FINISH)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width, width};
        plane.set_color(Color(eColorType::Red));
        plane.set_fill_color(Color(eColorType::Red));
        plane.draw();
      }

      if(mWeigthArray[l*mpMatrix->columns() + c] != mMaxCellCost)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width, width};
        plane.set_color(Color(eColorType::Green));
        plane.set_fill_color(Color(eColorType::Green));
        plane.draw();
      }

      drawText(x, y, std::to_string(mWeigthArray[l*mpMatrix->columns() + c]));

      if(aL == l && aC == c)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width - 3, width - 3};
        plane.set_point_size(4);
        plane.set_color(Color(eColorType::Red));
        plane.draw();
      }
    }
  }

  std::this_thread::sleep_for(250ms);

  glfwSwapBuffers(mpGLFWWin);             // Swap front and back buffers
  glfwPollEvents();                       // Poll for and process events
}
//------------------------------------------------------------------------------
void glMain::draw()
{
  unsigned x = 0;
  unsigned y = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  mGrid.draw();
  for(unsigned l = 0; l < mpMatrix->lines(); ++l)
  {
    y = (mDrawObjSize * l) + 20;
    for(unsigned c = 0; c < mpMatrix->columns(); ++c)
    {
      x = mDrawObjSize * c + 5;

      if(mpMatrix->get(l, c) == eCell::FREE)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width, width};
        plane.set_color(Color(eColorType::Gray));
        plane.set_fill_color(Color(eColorType::Gray));
        plane.draw();
      }

      if(mpMatrix->get(l, c) == eCell::FINISH)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width, width};
        plane.set_color(Color(eColorType::Red));
        plane.set_fill_color(Color(eColorType::Red));
        plane.draw();
      }

      if(mWeigthArray[l*mpMatrix->columns() + c] != mMaxCellCost)
      {
        int pos_x = mDrawObjSize * c;
        int pos_y = mDrawObjSize * l;
        int width = mDrawObjSize;
        gpPlane plane{{pos_x, pos_y}, width, width};
        plane.set_color(Color(eColorType::Green));
        plane.set_fill_color(Color(eColorType::Green));
        plane.draw();
      }

      drawText(x, y, std::to_string(mWeigthArray[l*mpMatrix->columns() + c]));
    }
  }

  std::this_thread::sleep_for(500ms);

  glfwSwapBuffers(mpGLFWWin);             // Swap front and back buffers
  glfwPollEvents();                       // Poll for and process events
}






