#ifndef VIEWEXAMPLE_HPP
#define VIEWEXAMPLE_HPP

#include <QGraphicsView>
#include <QGraphicsScene>

#include "button.hpp"


class viewExample : public QGraphicsView
{
public:
  viewExample();

private:
  void _init_view_elements();

private:
  button mBtnA;
  QGraphicsScene mScene;
};

#endif // VIEWEXAMPLE_HPP
