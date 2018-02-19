#include <QPainter>
#include "zombiestanding.hpp"

zombieStanding::zombieStanding()
{
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptHoverEvents(true);

  mPixMap.load(":/zombies/pics/zombie_standing.png");

  mWidth  = 37;
  mHeight = 48;
  mFrames = 10;
  mOffset = 37;
  mBorder = 0;
  connect(&mTimer, &QTimer::timeout, this, &zombieStanding::next_frame);
  mTimer.start(100);
}
//------------------------------------------------------------------------------
QRectF zombieStanding::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeight);
}
//------------------------------------------------------------------------------
void zombieStanding::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawPixmap(0,0, mPixMap, (mOffset*mCurrentFrame + mBorder), 0, mWidth, mHeight);
}
//------------------------------------------------------------------------------
void zombieStanding::next_frame()
{
  ++mCurrentFrame;
  if(mCurrentFrame >= mFrames)
    mCurrentFrame = 0;
  QGraphicsItem::update();
}
