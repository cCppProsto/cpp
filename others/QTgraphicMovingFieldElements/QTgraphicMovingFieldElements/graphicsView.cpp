#include "graphicsView.hpp"

#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
//------------------------------------------------------------------------------
graphicViewExample::graphicViewExample()
{
  setRenderHint(QPainter::Antialiasing);
  setCacheMode(QGraphicsView::CacheNone);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWindowTitle("QGraphicsView example");

  setFrameStyle(0);
  setFixedSize(1000, 700);

  setSceneRect(0, 0, 1000, 700);
  setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  setScene(&mScene);
}
