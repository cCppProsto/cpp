#include <QApplication>

#include "viewexample.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  viewExample v;
  v.show();

  //QGraphicsView -> QGraphicsScene -> QGraphicsItem
  return a.exec();
}
