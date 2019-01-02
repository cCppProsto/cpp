#include "button.hpp"
#include <QDebug>
#include <QPainter>
#include <QEvent>
#include <QApplication>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

button::button()
{
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptHoverEvents(true);
}
//------------------------------------------------------------------------------
QRectF button::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeight);
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
void button::setImage(QString aPath)
{
  mPixMap.load(aPath);

  mWidth  = mPixMap.width();
  mHeight = mPixMap.height();
}
//------------------------------------------------------------------------------
void button::setGeometry(int aWidth, int aHeight)
{
  mWidth  = aWidth;
  mHeight = aHeight;
}
//------------------------------------------------------------------------------
void button::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  mSceneWidth  = painter->viewport().width();
  mSceneHeight = painter->viewport().width();

  if(mHover)
    painter->setPen(QColor(255,0,0));

  QList<QGraphicsItem *> l = scene()->items();

  foreach (QGraphicsItem *item, l)
  {
    if (item == this)
      continue;

    if(collidesWithItem(item))
    {
      painter->setBrush(QBrush(Qt::green));
      item->update();
    }
  }

  painter->drawPixmap(0,0,mWidth, mHeight, mPixMap);
  painter->drawRoundedRect(0,0,mWidth, mHeight, 5, 5);
}
//------------------------------------------------------------------------------
void button::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
  mHover = true;

  // Планирует перерисовку области этого элемента покрываемой прямоугольником
  // rect. Вы можете вызывать эту функцию когда необходимо перерисовать
  // элемент, например, когда у него изменяется вид или размер.
  // Эта функция не приводит к незамедлительной отрисовке;
  // вместо этого она планирует запрос отрисовки, который будет
  // обработан QGraphicsView после того как управление вернётся в
  // цикл событий. Элемент будет перерисован только в том случае,
  // если он виден в любом связанном виде.
  // Побочным эффектом перерисовки элемента будет то, что элементы,
  // которые перекрывают область rect, могут быть также перерисованы.
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
  mHover = false;
  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void button::mousePressEvent(QGraphicsSceneMouseEvent *aEvent)
{
  mStartMovePos = aEvent->pos();
  mPrevPos = pos();
  mIsMoving = false;
}
//------------------------------------------------------------------------------
void button::mouseMoveEvent(QGraphicsSceneMouseEvent *aEvent)
{
  if(mIsMovable)
  {
    int distance = (aEvent->pos() - mStartMovePos).manhattanLength();
    if(distance > QApplication::startDragDistance())
    {
      // Возвращает точку области просмотра point, переведённую в координаты сцены.
      QPointF np = mapToScene(aEvent->pos() - mStartMovePos);

      if( (np.x() < 0) || (np.y() < 0) )
        return;
      if( (np.x() > mSceneWidth) || (np.y() > mSceneHeight) )
        return;

      mIsMoving = true;
      this->setPos(np);
    }
  }
}
//------------------------------------------------------------------------------
void button::mouseReleaseEvent(QGraphicsSceneMouseEvent *aEvent)
{
  if(!mIsMoving)
    emit btnMouseReleaseEvent(aEvent->button());
  else
  {
    //QPointF p = mapToScene(aEvent->pos());
    //this->setPos(mPrevPos);
  }
}

















/*
bool button::sceneEvent (QEvent * event)
{
  //qWarning() << "PointItem::sceneEvent" << event->type();
  switch (event->type())
  {
    case QEvent::GraphicsSceneHoverEnter:
    {
      qWarning() << "enter";
      break;
    }
    case QEvent::GraphicsSceneHoverLeave:
    {
      qWarning() << "leave";
      break;
    }
    default:
      break;
  }
  return QGraphicsItem::sceneEvent(event);
}

*/


