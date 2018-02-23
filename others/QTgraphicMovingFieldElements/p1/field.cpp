#include <QPainter>
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
}

