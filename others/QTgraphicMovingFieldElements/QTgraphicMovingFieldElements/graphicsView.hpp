#ifndef STRATEGOVIEW_HPP
#define STRATEGOVIEW_HPP

#include <QGraphicsView>
#include <QGraphicsScene>
#include "mainscene.hpp"

class graphicViewExample : public QGraphicsView
{
public:
  graphicViewExample();

private:
  mainScene mScene;
};

#endif // STRATEGOVIEW_HPP
