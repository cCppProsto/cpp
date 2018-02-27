#ifndef DRAGDROPINFO_HPP
#define DRAGDROPINFO_HPP

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
  sDragData mObjectInfo{eDragInfo::Unknown, eCellType::EMPTY, {0,0}};
};

#endif // DRAGDROPINFO_HPP
