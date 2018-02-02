#include <QGLWidget>
#include "appsettings.hpp"
#include "drawer.hpp"

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
  auto &app = appSettings::instance();
  static auto sw = app.screenHeight() - 100;

  auto &lines   = aLevel.mLines;
  auto &columns = aLevel.mColumns;

  float fw    = (float)sw / (float)columns;  // field width

  float x{(appSettings::instance().screenWidth() - sw)/ 2.f};
  float y{100.f};

  auto tbox      = app.textureID(appSettings::eTexturesID::Box);
  auto tbox_goal = app.textureID(appSettings::eTexturesID::BoxGoal);
  auto tplayer   = app.textureID(appSettings::eTexturesID::Player);
  auto twall     = app.textureID(appSettings::eTexturesID::Wall);
  auto tgoal     = app.textureID(appSettings::eTexturesID::Goal);

  const auto &map = aLevel.mRoom;

  glEnable(GL_TEXTURE_2D);
  aGLWidget.qglColor(Qt::white);
  for(int l = 0; l < lines; ++l)
    for(int c = 0; c < columns; ++c)
    {
      unsigned int textureID = 0;
      switch(map[l*columns + c])
      {
        case level::eField::BOX:
        {
          textureID = tbox;
          break;
        }
        case level::eField::BOX_ON_GOAL:
        {
          textureID = tbox_goal;
          break;
        }
        case level::eField::PLAYER:
        case level::eField::PLAYER_ON_GOAL:
        {
          textureID = tplayer;
          break;
        }
        case level::eField::WALL:
        {
          textureID = twall;
          break;
        }
        case level::eField::GOAL:
        {
          textureID = tgoal;
          break;
        }
        case level::eField::EMPTY:
        {
          break;
        }
      }
      if(textureID != 0)
        aGLWidget.drawTexture(QRectF{x + c*fw, y + l*fw, fw, fw}, textureID);
    }

  glDisable(GL_TEXTURE_2D);
}
//------------------------------------------------------------------------------
void drawer::_draw_statistic(const level &aLevel, QGLWidget &aGLWidget)
{
  static auto font = QFont("Comic Sans MS", 15);
  aGLWidget.qglColor(Qt::white);

  QString str;

  str = "Steps        : ";
  str += QString::number(aLevel.steps_count());
  aGLWidget.renderText(15, 20, str, font);

  str = "Boxes on goal: ";
  str += QString::number(aLevel.boxes_on_goal());;
  str += "/";
  str += QString::number(aLevel.goals());
  aGLWidget.renderText(15, 40, str, font);
}














