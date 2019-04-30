#include <iostream>
#include <chrono>
#include <thread>
#include <GL/glut.h>

//------------------------------------------------------------------------------
static const int g_WinWIDTH{800};
static const int g_WinHEIGHT{800};
static const char *g_WinTitle{"template"};


//------------------------------------------------------------------------------
static void gl_init(void);
static void gl_idle_func(void);
static void gl_draw_func(void);
static void gl_key_func(unsigned char aKey, int aX, int aY);
static void gl_mouse_func(int aButton, int aState, int aX, int aY);
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
int main()
{
  int i{1};
  char *ch = "";

  glutInit(&i, &ch);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(g_WinWIDTH, g_WinHEIGHT);
  glutCreateWindow(g_WinTitle);

  gl_init();

  glutMainLoop();

  return 0;
}
//------------------------------------------------------------------------------
void gl_init(void)
{
  glViewport(0, 0, g_WinWIDTH, g_WinHEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, g_WinWIDTH, g_WinHEIGHT, 0, 0, 1);

  glutKeyboardFunc(gl_key_func);
  glutMouseFunc(gl_mouse_func);
  glutIdleFunc(gl_idle_func);
  glutDisplayFunc(gl_draw_func);
}
//------------------------------------------------------------------------------
void gl_idle_func(void)
{
  glutPostRedisplay();
}
//------------------------------------------------------------------------------
void gl_draw_func(void)
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);


  glutSwapBuffers();

  std::this_thread::sleep_for(std::chrono::milliseconds(33));
}
//------------------------------------------------------------------------------
void gl_key_func(unsigned char aKey, int aX, int aY)
{
  switch (aKey)
  {
    case 27:
    {
      exit(0);
    }
  }
}
//------------------------------------------------------------------------------
void gl_mouse_func(int aButton, int aState, int aX, int aY)
{
  switch(aButton)
  {
    case GLUT_LEFT_BUTTON:
    {
      if(aState == 1) // left btn
      {
        break;
      }
    }
  }
}
