#include <QDebug>
#include "viewexample.hpp"

viewExample::viewExample()
{
  setRenderHint(QPainter::Antialiasing);

  setCacheMode(QGraphicsView::CacheNone);

  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


  setWindowTitle("viewExample");

  setFrameStyle(0);
  setSceneRect(0, 0, 800, 800);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  setFixedSize(800, 800);

  mScene.setItemIndexMethod(QGraphicsScene::NoIndex);


  setScene(&mScene);
  _init_view_elements();
}
//------------------------------------------------------------------------------
void viewExample::_init_view_elements()
{
  mBtnBomb.setPos(50, 50);
  mBtnBomb.enableMouseMoving();
  mBtnBomb.setImage(":/pics/pics/bomb_a_64.png");
  connect(&mBtnBomb, &button::btnMouseReleaseEvent,
          this, &viewExample::btn_Bomb_clicked);

  mBtnB.setPos(150, 150);
  mBtnB.setImage(":/pics/pics/soldier_a_64.png");
  connect(&mBtnB, &button::btnMouseReleaseEvent,
          this, &viewExample::btn_B_clicked);

  mBtnC.setPos(250, 250);
  mBtnC.setImage(":/pics/pics/soldier_b_64.png");
  connect(&mBtnC, &button::btnMouseReleaseEvent,
          this, &viewExample::btn_C_clicked);

  mScene.addItem(&mBtnBomb);
  mScene.addItem(&mBtnB);
  mScene.addItem(&mBtnC);
}
//------------------------------------------------------------------------------
void viewExample::btn_B_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "B clicked " << aBtn;
}
//------------------------------------------------------------------------------
void viewExample::btn_C_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "C clicked " << aBtn;
}
//------------------------------------------------------------------------------
void viewExample::btn_Bomb_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "Bomb clicked " << aBtn;
}
