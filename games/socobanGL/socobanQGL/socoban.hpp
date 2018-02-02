#ifndef SOCOBAN_HPP
#define SOCOBAN_HPP

#include <vector>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include "level.hpp"
#include "drawer.hpp"

struct socoban : QGLWidget
{
  enum class eState
  {
    MENU
   ,SELECT_LEVEL
   ,PLAYER_STAT
   ,PLAY
   ,EXIT
  };

  enum class eMenu
  {
    START = -1
   ,PLAY
   ,SELECT_LEVEL
   ,PLAYER_STAT
   ,EXIT
   ,END
  };

  socoban();

  void initializeGL()                override;
  void resizeGL(int, int)            override;
  void paintGL()                     override;
  void mousePressEvent(QMouseEvent*) override;
  void keyReleaseEvent(QKeyEvent *)  override;

private:
  void _proccesing();
  void _draw();

  void _draw_menu();
  void _draw_menu_select_level();
  void _draw_player_stat();
  void _draw_play();

  void _key_released_menu(int);
  void _key_released_menu_select_level(int);
  void _key_released_player_stat(int);
  void _key_released_play(int);

private:
  int     mSelectLevelIndex{0};

  level   mLevel;
  drawer  mDrawer;
  eState  mState{eState::MENU};
  eMenu   mCurrentMenu;

  std::vector<std::pair<eMenu, std::string>> mvMenu;
};

#endif // SOCOBAN_HPP
