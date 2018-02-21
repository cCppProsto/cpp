#ifndef COMMON_H
#define COMMON_H

#include <QPointF>

enum class eFieldType
{
  EMPTY
 ,TYPE_1
 ,TYPE_2
};

enum class eDragInfo
{
  Unknown
 ,MainField
 ,PrimaryField
};

struct sDragData
{
  eDragInfo  from;
  eFieldType type;
  QPointF    drag_pos;
};


#endif // COMMON_H
