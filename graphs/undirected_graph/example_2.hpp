#ifndef EXAMPLE_2_HPP
#define EXAMPLE_2_HPP

#include "common.h"

struct example_2
{
  example_2();
  ~example_2();

  void find(int, int);

  void draw();

private:
  void init();

private:
  unsigned mNodePos{0};
  cpp_prosto::math::undirectedGraph mGraph;

  std::map<unsigned, info> mInfos;
};

#endif // EXAMPLE_2_HPP
