#include <QGraphicsSceneMouseEvent>
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
  mMainField.boundingRectOnSceneCalc();
  addItem(&mMainField);
}
//------------------------------------------------------------------------------
void mainScene::_init_primary_field()
{
  mPrimaryField.setPos(710, 490);
  mPrimaryField.boundingRectOnSceneCalc();
  addItem(&mPrimaryField);
}
//------------------------------------------------------------------------------
void mainScene::mousePressEvent(QGraphicsSceneMouseEvent *)
{
}
//------------------------------------------------------------------------------
void mainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *apEvent)
{
  bool mainHover    = _is_moving_hover_main_field(apEvent->scenePos());
  bool primaryHover = _is_moving_hover_primary_field(apEvent->scenePos());

  if(!mainHover && !primaryHover)
    return;

  if(mainHover)
    mMainField.enableHoverPos(apEvent->scenePos());

  if(primaryHover)
    mPrimaryField.enableHoverPos(apEvent->scenePos());
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_main_field(const QPointF &aPos)
{
  return (aPos.x() >= mMainField.xtl())
      && (aPos.x() <= mMainField.xbr())
      && (aPos.y() >= mMainField.ytl())
      && (aPos.y() <= mMainField.ybr());
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_primary_field(const QPointF &aPos)
{
  return (aPos.x() >= mPrimaryField.xtl())
      && (aPos.x() <= mPrimaryField.xbr())
      && (aPos.y() >= mPrimaryField.ytl())
      && (aPos.y() <= mPrimaryField.ybr());
}
//------------------------------------------------------------------------------
void mainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
}
