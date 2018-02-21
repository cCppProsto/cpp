#include <QPainter>

#include "dragdrawobj.hpp"

dragDrawObj::dragDrawObj()
{
}
//------------------------------------------------------------------------------
QRectF dragDrawObj::boundingRect() const
{
  return QRectF(0, 0, 70, 70);
}
//------------------------------------------------------------------------------
void dragDrawObj::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
  painter->setBrush(QBrush(QColor(255, 0, 0)));
  painter->drawRoundedRect(0, 0, 70, 70, 2, 2);
}

