#ifndef SOCOBAN_HPP
#define SOCOBAN_HPP

#include <QGLWidget>
#include <vector>

struct socoban :QGLWidget
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

  void initializeGL()               override;
  void resizeGL(int,int)            override;
  void paintGL()                    override;
  void keyReleaseEvent(QKeyEvent *) override;

private:
  void _proccesing();
  void _draw();

  void _draw_menu();
  void _draw_menu_select_level();
  void _draw_player_stat();
  void _draw_play();

private:
  int mSelectLevelIndex;

  eState  mState{eState::MENU};
  eMenu   mCurrentMenu;

  std::vector<std::pair<eMenu, std::string>> mvMenu;
};

#endif // SOCOBAN_HPP






















