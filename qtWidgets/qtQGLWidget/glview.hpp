#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>


struct glView : QGLWidget
{
  glView();

  void initializeGL() override;
  void resizeGL(int w, int h)override;
  void paintGL()override;

  void mousePressEvent(QMouseEvent*) override;

private:
  float mScaleFactorX;
  float mScaleFactorY;

  QPoint mPosition;
  QTimer mpTimer;

};

#endif // GLVIEW_HPP
