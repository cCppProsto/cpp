#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QVector>
#include <QTimer>

class zombie : public QObject, public QGraphicsItem
{
  Q_OBJECT

  enum class eAnimateState
  {
    Standing = 0
   ,Attack
   ,Moving
   ,StateEnd
  };

  struct spriteData
  {
    int mWidth{0};
    int mHeight{0};
    int mCurrentFrame{0};
    int mFrames{0};
    int mOffset{0};
    int mBorder{0};
  };

public:
  zombie();

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void set_left_direction();
  void set_right_direction();
  void move();
  void stop();
  void attack();

private:
  const spriteData &_csd() const;

private slots:
  void next_frame();

private:
  qreal mDx{2.};
  eAnimateState mState{eAnimateState::Standing};

  int mCurrentFrame{0};
  QTimer  mTimer;

  QVector<QPair<QPixmap, spriteData>> mvPixmaps;
};

#endif // ZOMBIE_HPP
