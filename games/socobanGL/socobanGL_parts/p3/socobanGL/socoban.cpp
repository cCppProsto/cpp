#include "socoban.hpp"
#include "appsettings.hpp"

#include<QKeyEvent>

//------------------- ADDITIONAL FUNCTIONS -------------------------------------
//------------------------------------------------------------------------------
socoban::eMenu operator++(socoban::eMenu &aMenu)
{
  aMenu = socoban::eMenu(int(aMenu) + 1);

  if(aMenu == socoban::eMenu::END )
  {
     aMenu = socoban::eMenu::PLAY;
     return aMenu;
  }
  return aMenu;
}
//------------------------------------------------------------------------------
socoban::eMenu operator--(socoban::eMenu &aMenu)
{
  aMenu = socoban::eMenu(int(aMenu) - 1);

  if(aMenu == socoban::eMenu::START )
  {
     aMenu = socoban::eMenu::EXIT;
     return aMenu;
  }
  return aMenu;
}//------------------------------------------------------------------------------
int menuStateToInt(const socoban::eMenu &aMenu)
{
  switch(aMenu)
  {
    case socoban::eMenu::START:       return (int)socoban::eMenu::START;
    case socoban::eMenu::END:         return (int)socoban::eMenu::END;
    case socoban::eMenu::SELECT_LEVEL:return (int)socoban::eMenu::SELECT_LEVEL;
    case socoban::eMenu::PLAY:        return (int)socoban::eMenu::PLAY;
    case socoban::eMenu::PLAYER_STAT: return (int)socoban::eMenu::PLAYER_STAT;
    case socoban::eMenu::EXIT:        return (int)socoban::eMenu::EXIT;
  }
  return -1;
}
//------------------------------------------------------------------------------
socoban::eState menuStateToGameState(const socoban::eMenu &aMenu)
{
  switch(aMenu)
  {
    case socoban::eMenu::START:
    case socoban::eMenu::END:         return socoban::eState::MENU;

    case socoban::eMenu::SELECT_LEVEL:return socoban::eState::SELECT_LEVEL;
    case socoban::eMenu::PLAY:        return socoban::eState::PLAY;
    case socoban::eMenu::PLAYER_STAT: return socoban::eState::PLAYER_STAT;
    case socoban::eMenu::EXIT:        return socoban::eState::EXIT;
  }
  return socoban::eState::MENU;
}


socoban::socoban()
{
  mvMenu.push_back({eMenu::PLAY,        "Play"});
  mvMenu.push_back({eMenu::SELECT_LEVEL,"Select level"});
  mvMenu.push_back({eMenu::PLAYER_STAT, "Statistic"});
  mvMenu.push_back({eMenu::EXIT,        "Exit"});
}
//------------------------------------------------------------------------------
void socoban::initializeGL()
{
  static auto w = appSettings::instance().screenWidth();
  static auto h = appSettings::instance().screenHeight();
  glOrtho(0, w, h, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
}
//------------------------------------------------------------------------------
void socoban::resizeGL(int aW, int aH)
{
  static auto w = appSettings::instance().screenWidth();
  static auto h = appSettings::instance().screenHeight();

  glLoadIdentity();
  glViewport(0, 0, (GLint)aW, (GLint)aH);
  glOrtho(0, w, h, 0, 0, 1);
}
//------------------------------------------------------------------------------
void socoban::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  qglClearColor(Qt::darkCyan);

  _proccesing();

  _draw();
}
//------------------------------------------------------------------------------
void socoban::keyReleaseEvent(QKeyEvent *apKeyEvent)
{
  switch (mState)
  {
    case eState::MENU:
    {
      _key_released_menu(apKeyEvent->key());
      break;
    }
    case eState::SELECT_LEVEL:
    {
      _key_released_menu_select_level(apKeyEvent->key());
      break;
    }
    case eState::PLAYER_STAT:
    {
      _key_released_player_stat(apKeyEvent->key());
      break;
    }
    case eState::PLAY:
    {
      _key_released_play(apKeyEvent->key());
      break;
    }
    case eState::EXIT:
    {
      break;
    }
  }
  //if(apKeyEvent->key() == Qt::Key_Escape)
  //  close();
}
//------------------------------------------------------------------------------
void socoban::_proccesing()
{
  switch (mState)
  {
    case eState::MENU:
    {
      break;
    }
    case eState::SELECT_LEVEL:
    {
      break;
    }
    case eState::PLAYER_STAT:
    {
      break;
    }
    case eState::PLAY:
    {
      break;
    }
    case eState::EXIT:
    {
      close();
      break;
    }
  }
}
//------------------------------------------------------------------------------
void socoban::_draw()
{
  switch (mState)
  {
    case eState::MENU:
    {
      _draw_menu();
      break;
    }
    case eState::SELECT_LEVEL:
    {
      _draw_menu_select_level();
      break;
    }
    case eState::PLAYER_STAT:
    {
      _draw_player_stat();
      break;
    }
    case eState::PLAY:
    {
      _draw_play();
      break;
    }
    case eState::EXIT:
    {
      break;
    }
  }
}
//------------------------------------------------------------------------------
void socoban::_draw_menu()
{
  static auto app_w = appSettings::instance().screenWidth() / 2.f;
  static auto app_h = appSettings::instance().screenHeight() / 3.f;

  static auto font          = QFont("Sans", 25);
  static auto font_selected = QFont("Sans", 30);
  font_selected.setBold(true);

  auto x   = app_w - 100;
  auto y   = app_h;
  auto dy  = 55.f;
  int  end = mvMenu.size();

  for(int i = 0; i < end; ++i)
  {
    if(i == menuStateToInt(mCurrentMenu))
    {
      qglColor(Qt::red);
      renderText(x, y, mvMenu[i].second.c_str(), font_selected);
    }
    else
    {
      qglColor(Qt::white);
      renderText(x, y, mvMenu[i].second.c_str(), font);
    }
    y += dy;
  }
}
//------------------------------------------------------------------------------
void socoban::_draw_menu_select_level()
{
}
//------------------------------------------------------------------------------
void socoban::_draw_player_stat()
{
}
//------------------------------------------------------------------------------
void socoban::_draw_play()
{
}
//------------------------------------------------------------------------------
void socoban::_key_released_menu(int aKey)
{
  switch (aKey)
  {
    case Qt::Key_Up:
    {
      --mCurrentMenu;
      break;
    }
    case Qt::Key_Down:
    {
      ++mCurrentMenu;
      break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
      mState = menuStateToGameState(mCurrentMenu);
      break;
    }
  }
  updateGL();
}
//------------------------------------------------------------------------------
void socoban::_key_released_menu_select_level(int aKey)
{
  switch(aKey)
  {
    case Qt::Key_Up:
    {
      break;
    }
    case Qt::Key_Down:
    {
      break;
    }
    case Qt::Key_Enter:
    case Qt::Key_Return:
    {
      break;
    }
    case Qt::Key_Escape:
    {
      mState = eState::MENU;
      break;
    }
  }
  updateGL();
}
//------------------------------------------------------------------------------
void socoban::_key_released_player_stat(int aKey)
{
  switch(aKey)
  {
    case Qt::Key_Escape:
    {
      mState = eState::MENU;
      break;
    }
  }
  updateGL();
}
//------------------------------------------------------------------------------
void socoban::_key_released_play(int aKey)
{
  switch(aKey)
  {
    case Qt::Key_Up:
    {
      break;
    }
    case Qt::Key_Down:
    {
      break;
    }
    case Qt::Key_Left:
    {
      break;
    }
    case Qt::Key_Right:
    {
      break;
    }
    case Qt::Key_Escape:
    {
      mState = eState::MENU;
      break;
    }
    case Qt::Key_R:
    {
      break;
    }
  }
  updateGL();
}

























