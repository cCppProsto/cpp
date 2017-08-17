#ifndef MENUAPP_H
#define MENUAPP_H

#include "baseappinst.hpp"
#include "mainmenu.hpp"

using namespace cpp_prosto::application;

struct menuApp : baseAppInst
{
  enum class eMenuState : unsigned
  {
    START
   ,ABOUT
   ,EXIT
   ,START_EASY
   ,START_MEDIUM
   ,START_HARD
   ,START_HARD_NORMAL
   ,START_HARD_VERY
  };

  menuApp();

private:
  void v_init() override;
  void v_menu() override;
  void v_application() override;
  void v_exit() override;

  void keyEvent(GLFWwindow *, int, int, int, int) override;
  void mouseKeyEvent(GLFWwindow *, int, int, int) override;

  void menu_key_processing(int, int);
  void app_key_processing(int, int);
  void draw_menu();

private:
  eMenuState  mMenuState;
  Menu        mMenu;
};

#endif // MENUAPP_H
