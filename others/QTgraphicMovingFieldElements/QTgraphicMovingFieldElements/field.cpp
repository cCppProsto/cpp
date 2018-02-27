
#include <QCursor>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
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
void field::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
  for(int l = 0; l <= mLines; ++l)
    painter->drawLine(QLineF(0, l*mCellWidth, mFieldWidth, l*mCellWidth));

  for(int c = 0; c <= mColumns; ++c)
    painter->drawLine(QLineF(c*mCellWidth, 0, c*mCellWidth, mFieldHeight));

  _draw_cells(painter);
  if(mHover)
  {
    int x = mMousePos.x()/mCellWidth;
    int y = mMousePos.y()/mCellWidth;

    painter->setPen(QColor(255, 0, 0));
    painter->drawRoundedRect(x*mCellWidth, y*mCellWidth, mCellWidth, mCellWidth, 2, 2);
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
void field::_draw_cells(QPainter *painter)
{
  for(int l = 0; l < mLines; ++l)
  {
    for(int c = 0; c < mColumns; ++c)
    {
      switch(mvFields[l*mColumns + c])
      {
        case eCellType::EMPTY:
        {
          break;
        }
        case eCellType::TYPE_1:
        {
          painter->drawText(c*mCellWidth + 15, l*mCellWidth + 20,"Type 1");
          break;
        }
        case eCellType::TYPE_2:
        {
          painter->drawText(c*mCellWidth + 15, l*mCellWidth + 20,"Type 2");
          break;
        }
      }
    }
  }
}
//------------------------------------------------------------------------------
bool field::fieldIsEmpty(const QPointF &aPos)
{
  return getFieldType(aPos) == eCellType::EMPTY;
}
//------------------------------------------------------------------------------
eCellType field::getFieldType(const QPointF &aPos)
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  return mvFields[l*mColumns+c];
}
//------------------------------------------------------------------------------
eCellType field::take_field(QPointF aPos)
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  eCellType res = mvFields[l*mColumns+c];
  mvFields[l*mColumns+c] = eCellType::EMPTY;
  return res;
}
//------------------------------------------------------------------------------
void field::set_field(QPointF aPos, eCellType aType)
{
  QPointF pos = mapFromScene(aPos);
  int c = pos.x()/mCellWidth;
  int l = pos.y()/mCellWidth;
  mvFields[l*mColumns+c] = aType;
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
  mMousePos = mapFromScene(aPos);
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void field::disableHover()
{
  mHover = false;
  QGraphicsItem::update();
}

