#include <QPainter>

#include "zombieattack.hpp"

zombieAttack::zombieAttack()
{
  setAcceptedMouseButtons(Qt::LeftButton);
  setAcceptHoverEvents(true);

  mPixMap.load(":/zombies/pics/zombie_attack.png");

  mWidth  = 45;
  mHeight = 48;
  mFrames = 27;
  mOffset = 49;
  mBorder = 2;

  connect(&mTimer, &QTimer::timeout, this, &zombieAttack::next_frame);
  mTimer.start(100);
}
//------------------------------------------------------------------------------
QRectF zombieAttack::boundingRect() const
{
  return QRectF(0, 0, mWidth, mHeight);
}
//------------------------------------------------------------------------------
void zombieAttack::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawPixmap(0,0, mPixMap, (mOffset*mCurrentFrame + mBorder), 0, mWidth, mHeight);
}
//------------------------------------------------------------------------------
void zombieAttack::next_frame()
{
  ++mCurrentFrame;
  if(mCurrentFrame >= mFrames)
    mCurrentFrame = 0;
  QGraphicsItem::update();
}

