#ifndef FIELD_HPP
#define FIELD_HPP

#include <QGraphicsItem>
#include <QVector>
#include <QPointF>
#include "common.h"


class field : public QGraphicsItem
{
public:
  field(int,int,int);
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void hoverMoveEvent(QGraphicsSceneHoverEvent*) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;

  void enableHoverPos(QPointF);
  void disableHover();

  bool fieldIsEmpty(const QPointF&);
  eFieldType getFieldType(const QPointF&);

  eFieldType take_field(QPointF);
  void set_field(QPointF, eFieldType);

  void boundingRectOnSceneCalc();

  qreal xtl();
  qreal ytl();
  qreal xbr();
  qreal ybr();

protected:
  virtual void init_vectors() = 0;
  virtual void _draw_cells(QPainter *);

protected:
  int                 mLines{0};
  int                 mColumns{0};
  int                 mCellWidth{0};
  int                 mFieldWidth{0};
  int                 mFieldHeight{0};
  bool                mHover{false};
  QRectF              mBoundingSceneRect;
  QPointF             mMousePos;
  QVector<eFieldType> mvFields;
};

#endif // FIELD_HPP
