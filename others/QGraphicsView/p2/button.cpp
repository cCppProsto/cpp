#include "button.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>

#include <QDebug>

button::button()
{
  setAcceptHoverEvents(true);
  setAcceptedMouseButtons(Qt::LeftButton);
}
//------------------------------------------------------------------------------
QRectF button::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeigth);
}
//------------------------------------------------------------------------------
void button::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  if(mHover)
    painter->setPen(QColor(255, 0, 0));

  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}
//------------------------------------------------------------------------------
void button::setGeometry(int aWidth, int aHeight)
{
  mWidth  = aWidth;
  mHeigth = aHeight;
}
//------------------------------------------------------------------------------
void button::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
  qWarning() << "Enter";
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  qWarning() << "Leave";
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::mousePressEvent(QGraphicsSceneMouseEvent *aEvent)
{
  mStartMovePos = aEvent->pos();
  qWarning() << "press : " << mStartMovePos;
}
//------------------------------------------------------------------------------
void button::mouseMoveEvent(QGraphicsSceneMouseEvent *aEvent)
{
  int distance = ((aEvent->pos() - mStartMovePos)).manhattanLength();
  if(distance > QApplication::startDragDistance())
  {
    QPointF np = mapToScene(aEvent->pos() - mStartMovePos);

    if( (np.x() < 0) || (np.y() < 0) )
      return;
    if( (np.x() > 800) || (np.y() > 800) )
      return;

      this->setPos(np);
  }
  qWarning() << "move";
}
//------------------------------------------------------------------------------
void button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
  qWarning() << "release";
}

