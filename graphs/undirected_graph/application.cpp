#include "application.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <glfw3.h>
#include "glut.h"

static unsigned menuStateToU(application::eMenuState aValue)
{
  switch(aValue)
  {
  case application::eMenuState::EXAMPLE1:
    return 1;
  case application::eMenuState::EXAMPLE2:
    return 2;
  case application::eMenuState::EXIT:
    return 3;
  }
  return 0;
}

static application::eMenuState unsignedToMenuState(unsigned aValue)
{
  switch(aValue)
  {
  case 1:
    return application::eMenuState::EXAMPLE1;
  case 2:
    return application::eMenuState::EXAMPLE2;
  case 3:
    return application::eMenuState::EXIT;
  }
  return application::eMenuState::EXAMPLE1;
}

static void init_menu(Menu &aMenu)
{
  aMenu.add(MenuValue{menuStateToU(application::eMenuState::EXAMPLE1), "Example 1"});
  aMenu.add(MenuValue{menuStateToU(application::eMenuState::EXAMPLE2), "Example 2"});
  aMenu.add(MenuValue{menuStateToU(application::eMenuState::EXIT),     "Exit"});
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
            case application::eMenuState::EXAMPLE1:
            case application::eMenuState::EXAMPLE2:
            {
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
  mExample1.set_start(13);
}
//------------------------------------------------------------------------------
void application::app_key_processing(int aKey, int aAction)
{
  eMenuState app_state = unsignedToMenuState(mMenu.current().id);

  if(aAction == GLFW_PRESS || aAction == GLFW_REPEAT)
  {
    switch(aKey)
    {
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
      default:
      {
        switch(app_state)
        {
          case eMenuState::EXAMPLE1:
          {
            key_pressed_example_1(aKey);
            break;
          }
          case eMenuState::EXAMPLE2:
          {
            break;
          }
          case eMenuState::EXIT:
            break;
        }
        break;
      }
    }
  }
}
//------------------------------------------------------------------------------
void application::key_pressed_example_1(int aKey)
{
  switch(aKey)
  {
    case GLFW_KEY_LEFT:
    {
      mExample1.move_left();
      break;
    }
    case GLFW_KEY_RIGHT:
    {
      mExample1.move_right();
      break;
    }
    case GLFW_KEY_UP:
    {
      mExample1.move_up();
      break;
    }
    case GLFW_KEY_DOWN:
    {
      mExample1.move_down();
      break;
    }
    case GLFW_KEY_ENTER:
    {
      break;
    }
    case GLFW_KEY_0:
    {
      mExample1.block_invert(1);
      break;
    }
    case GLFW_KEY_1:
    {
      mExample1.block_invert(2);
      break;
    }
    case GLFW_KEY_2:
    {
      mExample1.block_invert(3);
      break;
    }
    case GLFW_KEY_3:
    {
      mExample1.block_invert(4);
      break;
    }
    case GLFW_KEY_4:
    {
      mExample1.block_invert(5);
      break;
    }
    case GLFW_KEY_5:
    {
      mExample1.block_invert(6);
      break;
    }
    case GLFW_KEY_6:
    {
      mExample1.block_invert(7);
      break;
    }
    case GLFW_KEY_7:
    {
      mExample1.block_invert(8);
      break;
    }
    case GLFW_KEY_8:
    {
      mExample1.block_invert(9);
      break;
    }
    case GLFW_KEY_9:
    {
      mExample1.block_invert(10);
      break;
    }
    case GLFW_KEY_A:
    {
      mExample1.block_invert(11);
      break;
    }
    case GLFW_KEY_B:
    {
      mExample1.block_invert(12);
      break;
    }
    case GLFW_KEY_C:
    {
      mExample1.block_invert(13);
      break;
    }
    case GLFW_KEY_D:
    {
      mExample1.block_invert(14);
      break;
    }
    case GLFW_KEY_E:
    {
      mExample1.block_invert(15);
      break;
    }
    case GLFW_KEY_F:
    {
      mExample1.block_invert(16);
      break;
    }
  }
}
//------------------------------------------------------------------------------
void application::app_processing()
{
  eMenuState app_state = unsignedToMenuState(mMenu.current().id);

  switch(app_state)
  {
    case eMenuState::EXAMPLE1:
    {
      break;
    }
    case eMenuState::EXAMPLE2:
    {
      break;
    }
    case eMenuState::EXIT:
      break;
  }
}
//------------------------------------------------------------------------------
void application::app_draw()
{
  eMenuState app_state = unsignedToMenuState(mMenu.current().id);

  switch(app_state)
  {
    case eMenuState::EXAMPLE1:
    {
      mExample1.draw();
      break;
    }
    case eMenuState::EXAMPLE2:
    {
      mExample2.draw();
      break;
    }
    case eMenuState::EXIT:
      break;
  }

}
