#ifndef GRAPHICVIEWEXAMPLE_HPP
#define GRAPHICVIEWEXAMPLE_HPP

#include <QGraphicsView>
#include "mainscene.hpp"

class graphicViewExample : public QGraphicsView
{
public:
  graphicViewExample();

private:
  mainScene mScene;
};

#endif // GRAPHICVIEWEXAMPLE_HPP
