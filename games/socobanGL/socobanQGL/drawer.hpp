#ifndef DRAWER_HPP
#define DRAWER_HPP

#include "level.hpp"
#include <QGLWidget>

struct drawer
{
  drawer();

  void draw(const level&, QGLWidget &);

private:
  void _draw_grid(const level&, QGLWidget &);
  void _draw_objects(const level&, QGLWidget &);
  void _draw_statistic(const level&, QGLWidget &);

private:
  bool mTextureIsLoad{false};
};

#endif // DRAWER_HPP
