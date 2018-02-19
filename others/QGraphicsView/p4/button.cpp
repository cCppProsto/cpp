#include "button.hpp"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QGraphicsScene>

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

  QList<QGraphicsItem*> l = scene()->items();
  foreach(QGraphicsItem *item, l)
  {
    if(item == this)
      continue;

    if(collidesWithItem(item))
    {
      painter->setBrush(QBrush(Qt::green));
      item->update();
    }
  }

  painter->drawPixmap(0,0, mWidth, mHeigth, mPixMap);
  painter->drawRoundedRect(0, 0, mWidth, mHeigth, 5, 5);
}
//------------------------------------------------------------------------------
void button::enableMouseMoving()
{
  mIsMovable = true;
}
//------------------------------------------------------------------------------
void button::disableMouseMoving()
{
  mIsMovable = false;
}
//------------------------------------------------------------------------------
void button::setGeometry(int aWidth, int aHeight)
{
  mWidth  = aWidth;
  mHeigth = aHeight;
}
//------------------------------------------------------------------------------
void button::setImage(QString aPath)
{
  mPixMap.load(aPath);
  mWidth  = mPixMap.width();
  mHeigth = mPixMap.height();
}
//------------------------------------------------------------------------------
void button::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
  //qWarning() << "Enter";
  mHover = true;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  //qWarning() << "Leave";
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::mousePressEvent(QGraphicsSceneMouseEvent *aEvent)
{
  mStartMovePos = aEvent->pos();
  mIsMoving = false;
}
//------------------------------------------------------------------------------
void button::mouseMoveEvent(QGraphicsSceneMouseEvent *aEvent)
{
  if(mIsMovable)
  {
    int distance = ((aEvent->pos() - mStartMovePos)).manhattanLength();
    if(distance > QApplication::startDragDistance())
    {
      QPointF np = mapToScene(aEvent->pos() - mStartMovePos);

      if( (np.x() < 0) || (np.y() < 0) )
        return;
      if( (np.x() > 800) || (np.y() > 800) )
        return;

      mIsMoving = true;
      this->setPos(np);
    }
  }
}
//------------------------------------------------------------------------------
void button::mouseReleaseEvent(QGraphicsSceneMouseEvent *apEvent)
{
  if(!mIsMoving)
    emit btnMouseReleaseEvent(apEvent->button());
}

