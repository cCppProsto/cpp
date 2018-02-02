#include <QApplication>

#include "socoban.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  socoban app;

  app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
  app.setFixedSize(800, 600);
  app.show();

  // or
  //app.showFullScreen();


  return a.exec();
}
