#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>


class button : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
  button();

  void enableMouseMoving();
  void disableMouseMoving();

  void setGeometry(int, int);
  void setImage(QString);

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *)   override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent*)   override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent*)   override;

signals:
  void btnMouseReleaseEvent(Qt::MouseButton);

private:
  int  mWidth{80};
  int  mHeight{40};
  int  mSceneWidth{0};
  int  mSceneHeight{0};

  bool mIsMovable{false};
  bool mHover{false};
  bool mIsMoving{false};

  QPointF mPrevPos;
  QPointF mStartMovePos;
  QPixmap mPixMap;
};

#endif // BUTTON_HPP


//bool sceneEvent (QEvent * event) override;


