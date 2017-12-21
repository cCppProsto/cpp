#include "application.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <glfw3.h>
#include "glut.h"

#include "gpplane.hpp"

static unsigned menuStateToU(application::eMenuState aValue)
{
  switch(aValue)
  {
  case application::eMenuState::BUBBLE:
    return 1;
  case application::eMenuState::SELECTION:
    return 2;
  case application::eMenuState::INSERT:
    return 3;
  case application::eMenuState::EXIT:
    return 4;
  }
  return 0;
}

static application::eMenuState unsignedToMenuState(unsigned aValue)
{
  switch(aValue)
  {
  case 1:
    return application::eMenuState::BUBBLE;
  case 2:
    return application::eMenuState::SELECTION;
  case 3:
    return application::eMenuState::INSERT;
  case 4:
    return application::eMenuState::EXIT;
  }
  return application::eMenuState::BUBBLE;
}

static void init_menu(Menu &aMenu)
{
  aMenu.add(MenuValue{menuStateToU(application::eMenuState::BUBBLE),
            "Bubble sort"});
  aMenu.add(MenuValue{menuStateToU(application::eMenuState::SELECTION),
            "Selection sort"});

  aMenu.add(MenuValue{menuStateToU(application::eMenuState::INSERT),
            "Insertion sort"});
  aMenu.add(MenuValue{menuStateToU(application::eMenuState::EXIT),  "Exit"});
}

application::application()
{
}
//------------------------------------------------------------------------------
void application::v_init()
{
  init_menu(mMenu);
  mState = eAppState::MENU;
  app_init();
}
//------------------------------------------------------------------------------
void application::v_menu()
{
  draw_menu();
}
//------------------------------------------------------------------------------
void application::v_application()
{
  app_processing();
  app_draw();
}
//------------------------------------------------------------------------------
void application::v_exit()
{
  glfw_close();
}
//------------------------------------------------------------------------------
void application::keyEvent(GLFWwindow */*apWindow*/,
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
void application::mouseKeyEvent(GLFWwindow *, int, int, int)
{

}
//------------------------------------------------------------------------------
void application::menu_key_processing(int aKey, int aAction)
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
          application::eMenuState state = unsignedToMenuState(mMenu.current().id);
          switch(state)
          {
            case application::eMenuState::BUBBLE:
            {
              mBubbleAn.init(bubbleAnimate::eType::SORTED);
              mState = eAppState::APP;
              break;
            }
            case application::eMenuState::SELECTION:
            {
              mSelectAn.init(selectanimate::eType::CUSTOM);
              mState = eAppState::APP;
              break;
            }
            case application::eMenuState::INSERT:
            {
              mInsertAn.init(insertanimate::eType::CUSTOM);
              mState = eAppState::APP;
              break;
            }
            case application::eMenuState::EXIT:
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
void application::draw_menu()
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
void application::app_init()
{

}
//------------------------------------------------------------------------------
void application::app_key_processing(int aKey, int aAction)
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
        break;
      }
    }
  }
}
//------------------------------------------------------------------------------
void application::app_processing()
{

}

gpPlane pl{{10,10},100, 100};
//------------------------------------------------------------------------------
void application::app_draw()
{
  application::eMenuState state = unsignedToMenuState(mMenu.current().id);

  switch (state)
  {
    case application::eMenuState::BUBBLE:
    {
      //pl.set_color(Color(eColorType::Green));
      //pl.draw();
      mBubbleAn.draw();
      break;
    }
    case application::eMenuState::SELECTION:
    {
      mSelectAn.draw();
      break;
    }
    case application::eMenuState::INSERT:
    {
      mInsertAn.draw();
      break;
    }
    default:
      break;
  }
}
