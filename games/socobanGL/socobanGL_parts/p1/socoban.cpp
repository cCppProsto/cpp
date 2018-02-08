#include "socoban.hpp"
#include "appsettings.hpp"

#include<QKeyEvent>

socoban::socoban()
{
}
//------------------------------------------------------------------------------
void socoban::initializeGL()
{
  static auto w = appSettings::instance().screenWidth();
  static auto h = appSettings::instance().screenHeight();
  glOrtho(0, w, h, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
}
//------------------------------------------------------------------------------
void socoban::resizeGL(int aW, int aH)
{
  static auto w = appSettings::instance().screenWidth();
  static auto h = appSettings::instance().screenHeight();

  glLoadIdentity();
  glViewport(0, 0, (GLint)aW, (GLint)aH);
  glOrtho(0, w, h, 0, 0, 1);
}
//------------------------------------------------------------------------------
void socoban::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  qglClearColor(Qt::darkCyan);
}
//------------------------------------------------------------------------------
void socoban::keyReleaseEvent(QKeyEvent *apKeyEvent)
{
  if(apKeyEvent->key() == Qt::Key_Escape)
    close();
}

