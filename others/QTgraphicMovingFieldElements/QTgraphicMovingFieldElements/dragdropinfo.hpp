#ifndef DRAGDROPBUFFER_HPP
#define DRAGDROPBUFFER_HPP

#include <QPointF>
#include <QPair>

#include "common.h"

class dragDropInfo
{
  dragDropInfo();
  ~dragDropInfo();

public:
  static dragDropInfo &instance();

  bool isEmpty();

  void push(sDragData);

  sDragData pop();

  void reset();

  sDragData object()const;

private:
  sDragData mObjectInfo{eDragInfo::Unknown, eFieldType::EMPTY, {0,0}};
};

#endif // DRAGDROPBUFFER_HPP
