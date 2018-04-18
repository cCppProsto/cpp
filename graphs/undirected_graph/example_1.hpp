#ifndef EXAMPLE_1_HPP
#define EXAMPLE_1_HPP

#include "common.h"

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
