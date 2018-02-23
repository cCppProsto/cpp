#include "mainscene.hpp"

mainScene::mainScene()
{
  setItemIndexMethod(QGraphicsScene::NoIndex);

  _init_main_field();
  _init_primary_field();
}
//------------------------------------------------------------------------------
void mainScene::_init_main_field()
{
  addItem(&mMainField);
}
//------------------------------------------------------------------------------
void mainScene::_init_primary_field()
{
  mPrimaryField.setPos(710, 490);
  addItem(&mPrimaryField);
}
//------------------------------------------------------------------------------
void mainScene::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}
//------------------------------------------------------------------------------
void mainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *)
{
}
//------------------------------------------------------------------------------
void mainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
}
