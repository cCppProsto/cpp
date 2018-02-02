#ifndef SOCOBAN_HPP
#define SOCOBAN_HPP

#include <QGLWidget>

struct socoban :QGLWidget
{
  socoban();

  void initializeGL()               override;
  void resizeGL(int,int)            override;
  void paintGL()                    override;
  void keyReleaseEvent(QKeyEvent *) override;

};

#endif // SOCOBAN_HPP
