#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QGraphicsItem>

class button : public QGraphicsItem
{
public:
  button();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
  int mWidth{100};
  int mHeigth{100};
};

#endif // BUTTON_HPP
