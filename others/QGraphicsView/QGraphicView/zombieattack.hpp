#ifndef ZOMBIEATTACK_HPP
#define ZOMBIEATTACK_HPP

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>

class zombieAttack : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  zombieAttack();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private slots:
  void next_frame();

private:
  int mWidth{0};
  int mHeight{0};
  int mCurrentFrame{0};
  int mFrames{0};
  int mOffset{0};
  int mBorder{0};

  QPixmap mPixMap;
  QTimer  mTimer;
};

#endif // ZOMBIEATTACK_HPP
