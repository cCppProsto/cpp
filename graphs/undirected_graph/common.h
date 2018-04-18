#ifndef COMMON_H
#define COMMON_H

#include <map>
#include <memory>

#include "undirectedgraph.hpp"
#include "gprimitive.hpp"
#include "gpline.hpp"
#include "gpcircle.hpp"
#include "gpnumber.hpp"

using point  = cpp_prosto::graphical::point2D;
using circle = cpp_prosto::graphical::gpCircle;
using number = cpp_prosto::graphical::gpNumber;

using line      = cpp_prosto::graphical::gpLine;
using color     = cpp_prosto::graphical::Color;
using colorType = cpp_prosto::graphical::eColorType;

enum class eDirection
{
  DOWN
 ,LEFT
 ,UP
 ,RIGTH
};

struct node_direction_info
{
  point       _point;
  eDirection  dir;
};

struct info
{
  circle node;
  std::vector<std::pair<unsigned, node_direction_info>> edges;
};

#endif // COMMON_H
