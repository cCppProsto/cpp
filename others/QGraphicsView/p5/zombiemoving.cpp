#include <QPainter>

#include "zombiemoving.hpp"

zombieMoving::zombieMoving()
{
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptHoverEvents(true);

  mPixMap.load(":/zombies/pics/zombie_moving.png");

  mWidth  = 39;
  mHeight = 48;
  mFrames = 16;
  mOffset = 43;
  mBorder = 2;
  connect(&mTimer, &QTimer::timeout, this, &zombieMoving::next_frame);
  mTimer.start(100);
}
//------------------------------------------------------------------------------
QRectF zombieMoving::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeight);
}
//------------------------------------------------------------------------------
void zombieMoving::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawPixmap(0,0, mPixMap, (mOffset*mCurrentFrame + mBorder), 0, mWidth, mHeight);
}
//------------------------------------------------------------------------------
void zombieMoving::next_frame()
{
  ++mCurrentFrame;
  if(mCurrentFrame >= mFrames)
    mCurrentFrame = 0;
  QGraphicsItem::update();
}
