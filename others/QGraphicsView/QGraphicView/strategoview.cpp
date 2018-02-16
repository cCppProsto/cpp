#include "strategoview.hpp"

#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
//------------------------------------------------------------------------------
graphicViewExample::graphicViewExample()
{
  //указывает, что движок, если это возможно, должен сглаживать грани примитивов.
  setRenderHint(QPainter::Antialiasing);

  // 	Кэшируется фон. Это влияет и на пользовательский фон, и на фон,
  // основанный на свойстве backgroundBrush. Когда этот флаг установлен,
  // QGraphicsView будет выделять одно растровое изображение с размером области просмотра.
  setCacheMode(QGraphicsView::CacheNone);

  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setWindowTitle("QGraphicsView example");

  setFrameStyle(0);
  setSceneRect(0,0,800,800);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  setFixedSize(800, 800);

  //Это свойство содержит метод индексирования элементов.
  // QGraphicsScene применяет алгоритм индексирования сцены для ускорения
  // функций обнаружения элементов, таких как items() и itemAt().
  // Индексирование наиболее эффективно для статичных сцен
  // (т.е., сцен где большинство элементов не перемещается).
  // Для динамических сцен или сцен с большим числом анимированных элементов,
  // расчёт индекса может перевесить ускорение поиска.
  // В общих случаях метод индексирования по-умолчанию BspTreeIndex
  // работает нормально. Если ваша сцена используется много анимации
  // и вы столкнулись с замедлением, вы можете отключить
  // индексирование вызвав setItemIndexMethod(NoIndex).
  mScene.setItemIndexMethod(QGraphicsScene::NoIndex);

  setScene(&mScene);

  _init_view_elements();
}
//------------------------------------------------------------------------------
void graphicViewExample::_init_view_elements()
{
  mBtnA.setPos(0, 0);
  mBtnA.setImage(":/soldiers/pics/soldier_a_64.png");
  mBtnA.enableMouseMoving();
  connect(&mBtnA, &button::btnMouseReleaseEvent,
          this,   &graphicViewExample::btn_A_clicked);

  mBtnB.setPos(0, 100);
  mBtnB.setImage(":/soldiers/pics/soldier_b_64.png");
  mBtnB.enableMouseMoving();
  connect(&mBtnB, &button::btnMouseReleaseEvent,
          this,   &graphicViewExample::btn_B_clicked);

  mBtnBomb.setPos(0,200);
  mBtnBomb.setImage(":/soldiers/pics/bomb_a_64.png");
  mBtnBomb.enableMouseMoving();
  connect(&mBtnBomb, &button::btnMouseReleaseEvent,
          this,   &graphicViewExample::btn_Bomb_clicked);

  mZombieAttack.setPos(100,  100);
  mZombieMoving.setPos(150,  100);
  mZombieNothing.setPos(200, 100);
  mZombie.setPos(300,300);

  mScene.addItem(&mBtnA);
  mScene.addItem(&mBtnB);
  mScene.addItem(&mBtnBomb);
  mScene.addItem(&mZombieAttack);
  mScene.addItem(&mZombieMoving);
  mScene.addItem(&mZombieNothing);
  mScene.addItem(&mZombie);
}
//------------------------------------------------------------------------------
void graphicViewExample::btn_A_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "A clicked " << aBtn;
}
//------------------------------------------------------------------------------
void graphicViewExample::btn_B_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "B clicked " << aBtn;
}
//------------------------------------------------------------------------------
void graphicViewExample::btn_Bomb_clicked(Qt::MouseButton aBtn)
{
  qWarning() << "Bomb clicked " << aBtn;
}
//------------------------------------------------------------------------------
void graphicViewExample::keyReleaseEvent(QKeyEvent *apEvent)
{
  switch(apEvent->key())
  {
    case Qt::Key_Left:
    {
      mZombie.set_left_direction();
      mZombie.move();
      break;
    }
    case Qt::Key_Right:
    {
      mZombie.set_right_direction();
      mZombie.move();
      break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
      mZombie.attack();
      break;
    }
    case Qt::Key_Space:
    {
      mZombie.stop();
      break;
    }
  }
}
