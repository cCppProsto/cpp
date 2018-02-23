#ifndef STRATEGOVIEW_HPP
#define STRATEGOVIEW_HPP

#include <QGraphicsView>
#include <QGraphicsScene>

#include "button.hpp"
#include "zombieattack.hpp"
#include "zombiemoving.hpp"
#include "zombiestanding.hpp"

#include "zombie.hpp"

class graphicViewExample : public QGraphicsView
{
public:
  graphicViewExample();

private:
  void _init_view_elements();

  void keyReleaseEvent(QKeyEvent*)override;

private slots:
  void btn_A_clicked(Qt::MouseButton);
  void btn_B_clicked(Qt::MouseButton);
  void btn_Bomb_clicked(Qt::MouseButton);

private:
  QGraphicsScene mScene;

  button         mBtnA;
  button         mBtnB;
  button         mBtnBomb;
  zombieAttack   mZombieAttack;
  zombieMoving   mZombieMoving;
  zombieStanding mZombieNothing;
  zombie         mZombie;
};

#endif // STRATEGOVIEW_HPP
