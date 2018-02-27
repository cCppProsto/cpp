#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include <QGraphicsScene>

#include "dragdrawobj.hpp"
#include "mainfield.hpp"
#include "primaryfield.hpp"

class mainScene : public QGraphicsScene
{
public:
  mainScene();

  void mousePressEvent(QGraphicsSceneMouseEvent *)  override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent *)   override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *)override;

private:
  void _init_main_field();
  void _init_primary_field();

  bool _is_moving_hover_main_field(const QPointF&);
  bool _is_moving_hover_primary_field(const QPointF&);

  void _move_from_main_to_primary(sDragData, QPointF);
  void _move_from_primary_to_main(sDragData, QPointF);

private:
  bool  mLeftBtnPressed{false};

  QPointF       mMouseLeftClickPos;
  mainField     mMainField;
  primaryField  mPrimaryField;
  dragDrawObj   mDragDrawObj;
};

#endif // MAINSCENE_HPP
