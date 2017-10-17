#ifndef EXAMPLE_1_HPP
#define EXAMPLE_1_HPP

#include <map>
#include <memory>

#include "undirectedgraph.hpp"
#include "gprimitive.hpp"
#include "gpline.hpp"
#include "gpcircle.hpp"

using point  = cpp_prosto::graphical::point2D;
using circle = cpp_prosto::graphical::gpCircle;
using point  = cpp_prosto::graphical::point2D;

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

struct example_1
{
  example_1();
  ~example_1();

  void set_start(unsigned);
  void move_up();
  void move_right();
  void move_down();
  void move_left();

  void draw();

  void block_invert(unsigned);

private:
  void init();

private:
  unsigned mNodePos{0};
  cpp_prosto::math::undirectedGraph mGraph;

  std::map<unsigned, info> mInfos;
};

#endif // EXAMPLE_1_HPP
