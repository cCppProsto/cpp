#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QGraphicsItem>
#include <QPointF>

class button : public QGraphicsItem
{
public:
  button();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *)   override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;

  void hoverEnterEvent(QGraphicsSceneHoverEvent*)   override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*)   override;

  void setGeometry(int, int);

private:
  int mWidth{0};
  int mHeigth{0};

  bool mHover{false};

  QPointF mStartMovePos;
};

#endif // BUTTON_HPP
