#include <QPainter>
#include <QGraphicsSceneHoverEvent>
#include "field.hpp"

field::field(int aLines, int aColumns, int aCellWidth)
  :mLines(aLines)
  ,mColumns(aColumns)
  ,mCellWidth(aCellWidth)
  ,mFieldWidth(aColumns * aCellWidth)
  ,mFieldHeight(aLines * aCellWidth)
{
  setAcceptHoverEvents(true);
  setAcceptedMouseButtons(Qt::MouseButton::LeftButton);
}
//------------------------------------------------------------------------------
QRectF field::boundingRect() const
{
  return QRectF(0, 0, mFieldWidth, mFieldHeight);
}
//------------------------------------------------------------------------------
void field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  for(int l = 0; l <= mLines; ++l)
    painter->drawLine(QLineF(0, l*mCellWidth, mFieldWidth, l*mCellWidth));

  for(int c = 0; c <= mColumns; ++c)
    painter->drawLine(QLineF(c*mCellWidth, 0, c*mCellWidth, mFieldHeight));

  if(mHover)
  {
    int x = mMousePos.x()/mCellWidth;
    int y = mMousePos.y()/mCellWidth;

    painter->setPen(QColor(255, 0, 0));
    painter->drawRoundedRect(x*mCellWidth,
                             y*mCellWidth,
                             mCellWidth,
                             mCellWidth,
                             2, 2);
  }
}
//------------------------------------------------------------------------------
void field::boundingRectOnSceneCalc()
{
  QPointF pos  = scenePos();
  QRectF  rect = boundingRect();

  QPointF topLeft{pos.x() + rect.x(), pos.y() + rect.y()};
  QPointF bottomRight{topLeft.x() + rect.width(),topLeft.y() + rect.height()};

  mBoundingSceneRect.setTopLeft(topLeft);
  mBoundingSceneRect.setBottomRight(bottomRight);
}
//------------------------------------------------------------------------------
qreal field::xtl()
{
  return mBoundingSceneRect.topLeft().x();
}
//------------------------------------------------------------------------------
qreal field::ytl()
{
  return mBoundingSceneRect.topLeft().y();
}
//------------------------------------------------------------------------------
qreal field::xbr()
{
  return mBoundingSceneRect.bottomRight().x();
}
//------------------------------------------------------------------------------
qreal field::ybr()
{
  return mBoundingSceneRect.bottomRight().y();
}
//------------------------------------------------------------------------------
void field::hoverMoveEvent(QGraphicsSceneHoverEvent *apEvent)
{
  mMousePos = apEvent->pos();
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::enableHoverPos(QPointF aPos)
{
  mHover = true;
  mMousePos = mapFromScene(aPos);
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::disableHover()
{
  mHover = false;
  QGraphicsItem::update();
}


