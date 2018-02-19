#ifndef VIEWEXAMPLE_HPP
#define VIEWEXAMPLE_HPP

#include <QGraphicsView>
#include <QGraphicsScene>

#include "button.hpp"

#include "zombieattack.hpp"
#include "zombiemoving.hpp"
#include "zombiestanding.hpp"

#include "zombie.hpp"

class viewExample : public QGraphicsView
{
public:
  viewExample();

private:
  void _init_view_elements();

private slots:
  void btn_Bomb_clicked(Qt::MouseButton);
  void btn_B_clicked(Qt::MouseButton);
  void btn_C_clicked(Qt::MouseButton);

  void keyReleaseEvent(QKeyEvent*)override;

private:
  button mBtnBomb;
  button mBtnB;
  button mBtnC;

  zombieAttack   mZombieAttack;
  zombieMoving   mZombieMoving;
  zombieStanding mZombieNothing;
  zombie         mZombie;

  QGraphicsScene mScene;
};

#endif // VIEWEXAMPLE_HPP
