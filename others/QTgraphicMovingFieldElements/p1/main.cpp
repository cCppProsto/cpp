#include <QApplication>
#include <graphicviewexample.hpp>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  graphicViewExample s;
  s.show();

  return a.exec();
}
