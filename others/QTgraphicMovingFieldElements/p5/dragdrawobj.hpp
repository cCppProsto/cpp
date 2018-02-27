#ifndef DRAGDRAWOBJ_HPP
#define DRAGDRAWOBJ_HPP

#include <QGraphicsItem>

class dragDrawObj : public QGraphicsItem
{
public:
  dragDrawObj();
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // DRAGDRAWOBJ_HPP
