#ifndef FIELD_HPP
#define FIELD_HPP

#include <QGraphicsItem>

class field : public QGraphicsItem
{
public:
  field(int, int, int);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

  void enableHoverPos(QPointF);
  void disableHover();

  void boundingRectOnSceneCalc();
  qreal xtl();
  qreal ytl();
  qreal xbr();
  qreal ybr();

private:
  int     mLines{0};
  int     mColumns{0};
  int     mCellWidth{0};
  int     mFieldWidth{0};
  int     mFieldHeight{0};
  bool    mHover{false};
  QPointF mMousePos;
  QRectF  mBoundingSceneRect;
};

#endif // FIELD_HPP
