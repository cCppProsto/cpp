#include <QApplication>

#include "graphicsView.hpp"

#include "mainfield.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  graphicViewExample view;

  view.show();
  //view.showFullScreen();

  return a.exec();
}
