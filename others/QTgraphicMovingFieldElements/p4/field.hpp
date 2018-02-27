#ifndef FIELD_HPP
#define FIELD_HPP

#include <QGraphicsItem>
#include <QVector>
#include "common.h"

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

  bool fieldIsEmpty(const QPointF&);
  eCellType getFieldType(const QPointF&);

  eCellType take_field(QPointF);
  void set_field(QPointF, eCellType);

  void boundingRectOnSceneCalc();
  qreal xtl();
  qreal ytl();
  qreal xbr();
  qreal ybr();

protected:
  virtual void init_cells() = 0;
  virtual void _draw_cells(QPainter *);

protected:
  int     mLines{0};
  int     mColumns{0};
  int     mCellWidth{0};
  int     mFieldWidth{0};
  int     mFieldHeight{0};
  bool    mHover{false};
  QPointF mMousePos;
  QRectF  mBoundingSceneRect;

  QVector<eCellType> mvFields;
};

#endif // FIELD_HPP
