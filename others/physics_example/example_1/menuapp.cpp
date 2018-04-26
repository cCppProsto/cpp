#include "menuapp.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <glfw3.h>
#include <string.h>
#include <cmath>

#include "glut.h"

static unsigned menuStateToU(menuApp::eMenuState aValue)
{
  switch(aValue)
  {
  case menuApp::eMenuState::START:
    return 1;
  case menuApp::eMenuState::ABOUT:
    return 2;
  case menuApp::eMenuState::EXIT:
    return 3;
  case menuApp::eMenuState::START_EASY:
    return 4;
  case menuApp::eMenuState::START_MEDIUM:
    return 5;
  case menuApp::eMenuState::START_HARD:
    return 6;
  case menuApp::eMenuState::START_HARD_NORMAL:
    return 7;
  case menuApp::eMenuState::START_HARD_VERY:
    return 8;
  }
  return 0;
}

static menuApp::eMenuState unsignedToMenuState(unsigned aValue)
{
  switch(aValue)
  {
  case 1:
    return menuApp::eMenuState::START;
  case 2:
    return menuApp::eMenuState::ABOUT;
  case 3:
    return menuApp::eMenuState::EXIT;
  case 4:
    return menuApp::eMenuState::START_EASY;
  case 5:
    return menuApp::eMenuState::START_MEDIUM;
  case 6:
    return menuApp::eMenuState::START_HARD;
  case 7:
    return menuApp::eMenuState::START_HARD_NORMAL;
  case 8:
    return menuApp::eMenuState::START_HARD_VERY;
  }
  return menuApp::eMenuState::START;
}

static void init_menu(Menu &aMenu)
{
  MenuItem &start = aMenu.add(MenuValue{menuStateToU(menuApp::eMenuState::START), "Start"});

  start.add(MenuValue{menuStateToU(menuApp::eMenuState::START_EASY),   "easy"});
  start.add(MenuValue{menuStateToU(menuApp::eMenuState::START_MEDIUM), "medium"});
  MenuItem &hard = start.add(MenuValue{menuStateToU(menuApp::eMenuState::START_HARD), "hard"});
  hard.add(MenuValue{menuStateToU(menuApp::eMenuState::START_HARD_NORMAL), "normal hard"});
  hard.add(MenuValue{menuStateToU(menuApp::eMenuState::START_HARD_VERY), "very hard"});

  aMenu.add(MenuValue{menuStateToU(menuApp::eMenuState::ABOUT), "About"});
  aMenu.add(MenuValue{menuStateToU(menuApp::eMenuState::EXIT),  "Exit"});
}


//------------------------------------------------------------------------------
menuApp::menuApp() : baseAppInst("MenuTest")
{
}
//------------------------------------------------------------------------------
void menuApp::v_init()
{
  init_menu(mMenu);
  mState = eAppState::MENU;

  app_init();
}
//------------------------------------------------------------------------------
void menuApp::v_menu()
{
  draw_menu();
}
void menuApp::draw_menu()
{
  static int   x = 0;
  static int   y = 0;

  auto end     = mMenu.amount();
  auto current = mMenu.currentIndex();

  x = 350;
  y = 180;
  for(auto i = 0u; i < end; ++i)
  {
    std::string text = mMenu.getItem(i).value().text;
    if(current == i)
    {
      glColor3ub(0, 254,0);

      for(size_t j = 0; j < text.size(); ++j)
      {
          glRasterPos2i( x + (j*9), y);
          glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[j]);
      }
    }
    else
    {
      glColor3ub(254, 0, 0);

      for(size_t j = 0; j < text.size(); ++j)
      {
          glRasterPos2i( x + (j*8), y);
          glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[j]);
      }
    }
    y += 50;
  }
}
//------------------------------------------------------------------------------
void menuApp::app_init()
{
  mObj.setGravity(geo2D::force(1.f, 180));
  mObj.setVelocity(geo2D::vector({3,3}));
}
//------------------------------------------------------------------------------
void menuApp::v_application()
{
  app_processing();
  app_draw();
}
//------------------------------------------------------------------------------
void menuApp::app_processing()
{
  mObj.update();
}
//------------------------------------------------------------------------------
void menuApp::app_draw()
{
  mObj.draw();
}
//------------------------------------------------------------------------------
void menuApp::v_exit()
{
  glfw_close();
}
//------------------------------------------------------------------------------
void menuApp::keyEvent(GLFWwindow */*apWindow*/,
                       int aKey,
                       int /*aScanCode*/,
                       int aAction,
                       int /*aMods*/)
{
  switch(mState)
  {
    case eAppState::INIT:
    {
      break;
    }
    case eAppState::MENU:
    {
      menu_key_processing(aKey, aAction);
      break;
    }
    case eAppState::APP:
    {
      app_key_processing(aKey, aAction);
      break;
    }
    case eAppState::EXIT:
    {
      break;
    }
  }
}
//------------------------------------------------------------------------------
void menuApp::app_key_processing(int aKey, int aAction)
{
  if(aAction == GLFW_PRESS || aAction == GLFW_REPEAT)
  {
    switch(aKey)
    {
      case GLFW_KEY_UP:
      {
        break;
      }
      case GLFW_KEY_DOWN:
      {
        break;
      }
      case GLFW_KEY_ENTER:
      {
        break;
      }
      case GLFW_KEY_ESCAPE:
      {
        mState = eAppState::MENU;
        mMenu.goToTop();
        break;
      }
      case GLFW_KEY_SPACE:
      {
        if(mIsPause)
          mIsPause = false;
        else
          mIsPause = true;
        break;
      }
    }
  }
}
//------------------------------------------------------------------------------
void menuApp::menu_key_processing(int aKey, int aAction)
{
  if(aAction == GLFW_PRESS || aAction == GLFW_REPEAT)
  {
    switch(aKey)
    {
      case GLFW_KEY_UP:
      {
        mMenu.up();
        break;
      }
      case GLFW_KEY_DOWN:
      {
        mMenu.down();
        break;
      }
      case GLFW_KEY_ENTER:
      {
        if(!mMenu.enter())
        {
          menuApp::eMenuState state = unsignedToMenuState(mMenu.current().id);
          switch(state)
          {
            case menuApp::eMenuState::START:
            case menuApp::eMenuState::START_EASY:
            case menuApp::eMenuState::START_HARD:
            case menuApp::eMenuState::START_MEDIUM:
            case menuApp::eMenuState::START_HARD_NORMAL:
            case menuApp::eMenuState::START_HARD_VERY:
            {
              mState = eAppState::APP;
              break;
            }
            case menuApp::eMenuState::ABOUT:
            {
              mState = eAppState::APP;
              break;
            }
            case menuApp::eMenuState::EXIT:
            {
              mState = eAppState::EXIT;
              break;
            }
          }
        }
        break;
      }
      case GLFW_KEY_ESCAPE:
      {
        mMenu.leave();
        break;
      }
    }
  }
}
//------------------------------------------------------------------------------
void menuApp::mouseKeyEvent(GLFWwindow *, int, int, int)
{
}
