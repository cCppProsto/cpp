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

private slots:
  void btn_Bomb_clicked(Qt::MouseButton);
  void btn_B_clicked(Qt::MouseButton);
  void btn_C_clicked(Qt::MouseButton);

private:
  button mBtnBomb;
  button mBtnB;
  button mBtnC;


  QGraphicsScene mScene;
};

#endif // VIEWEXAMPLE_HPP
