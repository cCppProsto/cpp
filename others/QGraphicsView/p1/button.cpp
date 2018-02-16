#include "button.hpp"
#include <QPainter>

button::button()
{
}

QRectF button::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeigth);
}

void button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}
