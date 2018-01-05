#include "glview.hpp"

//------------------------------------------------------------------------------
glView::glView()
{
  connect(&mpTimer, SIGNAL(timeout()), this, SLOT(repaint()));
  mpTimer.start(33);
}
//------------------------------------------------------------------------------
void glView::initializeGL()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 800, 600, 0, 0, 1);
}
//------------------------------------------------------------------------------
void glView::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);

  mScaleFactorX = 800 / (float)w;
  mScaleFactorY = 600 / (float)h;
}
//------------------------------------------------------------------------------
void glView::paintGL()
{
  qglClearColor(Qt::darkCyan);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  qglColor(Qt::red);
  glBegin(GL_LINE_LOOP);
      glVertex2i(mPosition.x() * mScaleFactorX,      mPosition.y()* mScaleFactorY);
      glVertex2i(mPosition.x() * mScaleFactorX + 100,mPosition.y()* mScaleFactorY + 100);
      glVertex2i(mPosition.x() * mScaleFactorX,      mPosition.y()* mScaleFactorY + 100 );
  glEnd();
}
//------------------------------------------------------------------------------
void glView::mousePressEvent(QMouseEvent *apEvent)
{
  mPosition = apEvent->pos();
}

