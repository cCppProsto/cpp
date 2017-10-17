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

struct info
{
  circle node;
  std::vector<std::pair<unsigned, point>> edges;
};

struct example_1
{
  example_1();
  ~example_1();

  void draw();

  void block_invert(unsigned);

private:
  void init();

private:
  cpp_prosto::math::undirectedGraph mGraph;

  std::map<unsigned, info> mInfos;
};

#endif // EXAMPLE_1_HPP
