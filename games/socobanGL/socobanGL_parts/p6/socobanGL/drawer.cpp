#include "drawer.hpp"
#include "appsettings.hpp"


drawer::drawer()
{

}
//------------------------------------------------------------------------------
void drawer::draw(const level &aLevel, QGLWidget &aGLWidget)
{
  if(!aLevel.mIsLoad)
    return;

  _draw_grid(aLevel, aGLWidget);
  _draw_objects(aLevel, aGLWidget);
  _draw_statistic(aLevel, aGLWidget);
}
//------------------------------------------------------------------------------
void drawer::_draw_grid(const level &aLevel, QGLWidget &aGLWidget)
{
  static auto sw = appSettings::instance().screenHeight() - 100;

  auto &lines   = aLevel.mLines;
  auto &columns = aLevel.mColumns;

  float fw    = (float)sw / (float)columns;  // field width
  float map_w = sw;
  float map_h = fw*lines;

  float x{(appSettings::instance().screenWidth() - sw)/ 2.f};
  float y{100.f};

  aGLWidget.qglColor(Qt::darkGray);
  glBegin(GL_LINES);
    for(int r = 0; r <= lines; ++r)
    {
      glVertex2i(x,         y + fw*r);
      glVertex2i(x + map_w, y + fw*r);
    }

    for(int c = 0.f; c <= columns; ++c)
    {
      glVertex2i(x + fw*c, y );
      glVertex2i(x + fw*c, y + map_h);
    }
  glEnd();
}
//------------------------------------------------------------------------------
void drawer::_draw_objects(const level &aLevel, QGLWidget &aGLWidget)
{

}
//------------------------------------------------------------------------------
void drawer::_draw_statistic(const level &aLevel, QGLWidget &aGLWidget)
{

}
























