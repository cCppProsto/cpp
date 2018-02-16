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
  button mBtnB;
  button mBtnC;


  QGraphicsScene mScene;
};

#endif // VIEWEXAMPLE_HPP
