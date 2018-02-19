#include <QPainter>

#include "zombie.hpp"

zombie::zombie()
{
  mvPixmaps.reserve((int)eAnimateState::StateEnd);

  QPair<QPixmap, spriteData> tmp;

  tmp.first.load(":/zombies/pics/zombie_standing.png");
  tmp.second.mWidth         = 37;
  tmp.second.mHeight        = 48;
  tmp.second.mCurrentFrame  = 0;
  tmp.second.mFrames        = 10;
  tmp.second.mOffset        = 37;
  tmp.second.mBorder        = 0;
  mvPixmaps.push_back(tmp);

  tmp.first.load(":/zombies/pics/zombie_attack.png");
  tmp.second.mWidth         = 45;
  tmp.second.mHeight        = 48;
  tmp.second.mCurrentFrame  = 0;
  tmp.second.mFrames        = 27;
  tmp.second.mOffset        = 49;
  tmp.second.mBorder        = 2;
  mvPixmaps.push_back(tmp);

  tmp.first.load(":/zombies/pics/zombie_moving.png");
  tmp.second.mWidth         = 39;
  tmp.second.mHeight        = 48;
  tmp.second.mCurrentFrame  = 0;
  tmp.second.mFrames        = 16;
  tmp.second.mOffset        = 43;
  tmp.second.mBorder        = 2;
  mvPixmaps.push_back(tmp);

  connect(&mTimer, &QTimer::timeout, this, &zombie::next_frame);
  mTimer.start(100);
}
//------------------------------------------------------------------------------
QRectF zombie::boundingRect() const
{
  return QRectF(0, 0, 45, 48);
}
//------------------------------------------------------------------------------
void zombie::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem */*option*/,
                   QWidget */*widget*/)
{
  painter->drawPixmap(0,0, mvPixmaps[(int)mState].first,
      (_csd().mOffset*mCurrentFrame + _csd().mBorder), 0, _csd().mWidth, _csd().mHeight);
}
//------------------------------------------------------------------------------
const zombie::spriteData &zombie::_csd()const
{

  return mvPixmaps[(int)mState].second;
}
//------------------------------------------------------------------------------
void zombie::next_frame()
{
  switch(mState)
  {
    case eAnimateState::Moving:
    {
      move();
      break;
    }
    case eAnimateState::Standing:
    case eAnimateState::Attack:
    case eAnimateState::StateEnd:
    {
      break;
    }
  }

  //mvPixmaps[(int)mState].second.mCurrentFrame++;
  //if(mvPixmaps[(int)mState].second.mCurrentFrame >= mvPixmaps[(int)mState].second.mFrames)
  //  mvPixmaps[(int)mState].second.mCurrentFrame = 0;

  mCurrentFrame++;
  if(mCurrentFrame >= mvPixmaps[(int)mState].second.mFrames)
    mCurrentFrame = 0;

  QGraphicsItem::update();
}
//------------------------------------------------------------------------------
void zombie::stop()
{
  mState = eAnimateState::Standing;
  mCurrentFrame = 0;
}
//------------------------------------------------------------------------------
void zombie::set_left_direction()
{
  //setTransform(QTransform::fromScale(1, 1));
  //mDx = 2.0;
  //return;
  if(mDx < 0.)
  {
    // Get the current position
    QRectF itemRectOld = this->sceneBoundingRect();

    // Get the current transform
    QTransform transform(this->transform());
    qreal m11 = transform.m11(); // Horizontal scaling
    qreal m12 = transform.m12(); // Vertical shearing
    qreal m13 = transform.m13(); // Horizontal Projection
    qreal m21 = transform.m21(); // Horizontal shearing
    qreal m22 = transform.m22(); // vertical scaling
    qreal m23 = transform.m23(); // Vertical Projection
    qreal m31 = transform.m31(); // Horizontal Position (DX)
    qreal m32 = transform.m32(); // Vertical Position (DY)
    qreal m33 = transform.m33(); // Addtional Projection Factor

    // Horizontal flip
    m11 = -m11;

    // Write back to the matrix
    transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    // Set the items transformation
    setTransform(transform);

    // Re-position back to origin
    QRectF itemRectNew = this->sceneBoundingRect();
    qreal dx = itemRectOld.center().x()-itemRectNew.center().x();
    qreal dy = itemRectOld.center().y()-itemRectNew.center().y();
    this->moveBy(dx, dy);

    mDx = 2.;
  }
}
//------------------------------------------------------------------------------
void zombie::set_right_direction()
{
  //setTransform(QTransform::fromScale(-1, 1));
  //mDx = -2.;
  //return;

  if(mDx > 0.)
  {
    //setTransform(QTransform::fromScale(1, 1));
    // Get the current position
    QRectF itemRectOld = this->sceneBoundingRect();

    // Get the current transform
    QTransform transform(this->transform());
    qreal m11 = transform.m11(); // Horizontal scaling
    qreal m12 = transform.m12(); // Vertical shearing
    qreal m13 = transform.m13(); // Horizontal Projection
    qreal m21 = transform.m21(); // Horizontal shearing
    qreal m22 = transform.m22(); // vertical scaling
    qreal m23 = transform.m23(); // Vertical Projection
    qreal m31 = transform.m31(); // Horizontal Position (DX)
    qreal m32 = transform.m32(); // Vertical Position (DY)
    qreal m33 = transform.m33(); // Addtional Projection Factor

    // Horizontal flip
    m11 = -m11;

    // Write back to the matrix
    transform.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);

    // Set the items transformation
    setTransform(transform);

    // Re-position back to origin
    QRectF itemRectNew = this->sceneBoundingRect();
    qreal dx = itemRectOld.center().x()-itemRectNew.center().x();
    qreal dy = itemRectOld.center().y()-itemRectNew.center().y();
    this->moveBy(dx, dy);

    mDx = -2.;
  }

}
//------------------------------------------------------------------------------
void zombie::move()
{
  setPos(pos().x() - mDx, pos().y());
  mState = eAnimateState::Moving;
}
void zombie::attack()
{
  mState = eAnimateState::Attack;
  mCurrentFrame = 0;
}
