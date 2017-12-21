#ifndef GAMEAPP_HPP
#define GAMEAPP_HPP

#include "baseappinst.hpp"
#include "mainmenu.hpp"

using namespace cpp_prosto::application;

struct application : baseAppInst
{
  enum class eMenuState : unsigned
  {
    BUBBLE
   ,SELECTION
   ,INSERT
   ,EXIT
  };

  application();

private:
  void v_init() override;
  void v_menu() override;
  void v_application() override;
  void v_exit() override;

  void keyEvent(GLFWwindow *, int, int, int, int) override;
  void mouseKeyEvent(GLFWwindow *, int, int, int) override;

  void menu_key_processing(int, int);
  void draw_menu();

  void app_init();
  void app_key_processing(int, int);
  void app_processing();
  void app_draw();

private:
  Menu        mMenu;
};

#endif // GAMEAPP_HPP
