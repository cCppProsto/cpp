#include "example_1.hpp"


static color normal_edge_color  = color(colorType::Blue);
static color blocked_edge_color = color(colorType::Red);

static color node_color              = color(colorType::Green);
static color normal_node_fill_color  = color(colorType::Aqua);
static color blocked_node_fill_color = color(colorType::Red);

//------------------------------------------------------------------------------
example_1::example_1()
{
  init();
}
//------------------------------------------------------------------------------
example_1::~example_1()
{
}
//------------------------------------------------------------------------------
void example_1::init()
{
  // 0  0  0  0  *  0
  // 0  *  *  *  *  0
  // 0  0  0  *  0  0
  // 0  *  *  *  0  *
  // 0  *  0  0  0  0
  // 0  *  *  *  *  0
  // 0  0  0  0  0  0

  // 1 -- 2 -- 3    4
  // |              |
  // 5 -- 6    7 -- 8
  // |         |
  // 9    10 - 11 - 12
  // |              |
  // 13 - 14 - 15 - 16

  // 1  - 2, 5
  // 2  - 1, 3
  // 3  - 2
  // 4  - 8
  // 5  - 1, 6, 9
  // 6  - 5,
  // 7  - 8, 11
  // 8  - 4, 7
  // 9  - 5, 13
  // 10 - 11
  // 11 - 7, 10, 12
  // 12 - 11, 16
  // 13 - 9, 14
  // 14 - 13, 15
  // 15 - 14, 16
  // 16 - 15, 12

  // x_start = 80
  // y_start = 80

  // radius = 30
  // width  = 70
  // heigth = 70


  int width  = 200;
  int height = 200;
  int radius = 25;

  int start_pos_x = 200;
  int start_pos_y = 100;
  int x_s = start_pos_x;
  int y_s = start_pos_y;

  point p;
  circle node_info;
  std::pair<unsigned, node_direction_info> edge_info;

  node_info.set_color(node_color);
  node_info.set_fill_color(normal_node_fill_color);
  node_info.set_segments(18);
  node_info.set_radius(radius);

// 1  - 2, 5
  mGraph.connect_nodes(1, 2);
  mGraph.connect_nodes(1, 5);
  {
    x_s = start_pos_x;
    y_s = start_pos_y;

    info _info;
    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 1 - 2
    edge_info.first  = 2;
    edge_info.second._point = {x_s + width, y_s};
    edge_info.second.dir    = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    // line 1 - 5
    edge_info.first  = 5;
    edge_info.second._point = {x_s , y_s + height};
    edge_info.second.dir    = eDirection::DOWN;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(1, _info));
  }
// 2  - 1, 3 -------------------------------------------------------------------
  mGraph.connect_nodes(2, 3);
  {
    info _info;
    x_s = start_pos_x + width;
    y_s = start_pos_y;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 2 - 1
    edge_info.first  = 1;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir    = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    // line 2 - 3
    edge_info.first  = 3;
    edge_info.second._point = {x_s + width , y_s};
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(2, _info));
  }
//------------------------------------------------------------------------------

// 3 - 2
  {
    info _info;
    x_s = start_pos_x + width*2;
    y_s = start_pos_y;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 3 - 2
    edge_info.first  = 2;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(3, _info));
  }
//------------------------------------------------------------------------------

// 4  - 8
  mGraph.connect_nodes(4, 8);
  {
    info _info;
    x_s = start_pos_x + width*3;
    y_s = start_pos_y;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 4 - 8
    edge_info.first  = 8;
    edge_info.second._point = {x_s, y_s + height};
    edge_info.second.dir = eDirection::DOWN;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(4, _info));
  }
//------------------------------------------------------------------------------

// 5  - 1, 6, 9
  mGraph.connect_nodes(5, 6);
  mGraph.connect_nodes(5, 9);
  {
    info _info;
    x_s = start_pos_x;
    y_s = start_pos_y + height;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 5 - 1
    edge_info.first  = 1;
    edge_info.second._point = {x_s, y_s - height};
    edge_info.second.dir = eDirection::UP;
    _info.edges.push_back(edge_info);

    // line 5 - 6
    edge_info.first  = 6;
    edge_info.second._point = {x_s + width, y_s};
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    // line 5 - 9
    edge_info.first  = 9;
    edge_info.second._point = {x_s , y_s + height};
    edge_info.second.dir = eDirection::DOWN;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(5, _info));
  }
//------------------------------------------------------------------------------

// 6  - 5,
  {
    info _info;
    x_s = start_pos_x + width;
    y_s = start_pos_y + height;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 6 - 5
    edge_info.first  = 5;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(6, _info));
  }
//------------------------------------------------------------------------------

// 7  - 8, 11
  mGraph.connect_nodes(7, 8);
  mGraph.connect_nodes(7, 11);
  {
    info _info;
    x_s = start_pos_x + width*2;
    y_s = start_pos_y + height;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 7 - 8
    edge_info.first  = 8;
    edge_info.second._point = {x_s + width, y_s };
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    // line 7 - 11
    edge_info.first  = 11;
    edge_info.second._point = {x_s , y_s + height};
    edge_info.second.dir = eDirection::DOWN;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(7, _info));
  }
//------------------------------------------------------------------------------

// 8  - 4, 7
  {
    info _info;
    x_s = start_pos_x + width*3;
    y_s = start_pos_y + height;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 8 - 4
    edge_info.first  = 4;
    edge_info.second._point = {x_s, y_s - height};
    edge_info.second.dir = eDirection::UP;
    _info.edges.push_back(edge_info);

    // line 8 - 7
    edge_info.first  = 7;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(8, _info));
  }
//------------------------------------------------------------------------------

// 9  - 5, 13
  mGraph.connect_nodes(9, 13);
  {
    info _info;
    x_s = start_pos_x;
    y_s = start_pos_y + height*2;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 9 - 5
    edge_info.first  = 5;
    edge_info.second._point = {x_s, y_s - height};
    edge_info.second.dir = eDirection::UP;
    _info.edges.push_back(edge_info);

    // line 9 - 13
    edge_info.first  = 13;
    edge_info.second._point = {x_s , y_s + height};
    edge_info.second.dir = eDirection::DOWN;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(9, _info));
  }
//------------------------------------------------------------------------------

// 10 - 11
  mGraph.connect_nodes(10, 11);
  {
    info _info;
    x_s = start_pos_x + width;
    y_s = start_pos_y + height*2;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 10 - 11
    edge_info.first  = 11;
    edge_info.second._point = {x_s + width, y_s };
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(10, _info));
  }
//------------------------------------------------------------------------------

// 11 - 7, 10, 12
  mGraph.connect_nodes(11, 12);
  {
    info _info;
    x_s = start_pos_x + width*2;
    y_s = start_pos_y + height*2;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 11 - 7
    edge_info.first  = 7;
    edge_info.second._point = {x_s, y_s - height};
    edge_info.second.dir = eDirection::UP;
    _info.edges.push_back(edge_info);

    // line 11 - 10
    edge_info.first  = 10;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    // line 11 - 12
    edge_info.first  = 12;
    edge_info.second._point = {x_s + width, y_s};
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(11, _info));
  }
//------------------------------------------------------------------------------

// 12 - 11, 16
  mGraph.connect_nodes(12, 16);
  {
    info _info;
    x_s = start_pos_x + width*3;
    y_s = start_pos_y + height*2;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 12 - 11
    edge_info.first  = 11;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    // line 12 - 16
    edge_info.first  = 16;
    edge_info.second._point = {x_s , y_s + height};
    edge_info.second.dir = eDirection::DOWN;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(12, _info));
  }
//------------------------------------------------------------------------------

// 13 - 9, 14
  mGraph.connect_nodes(13, 14);
  {
    info _info;
    x_s = start_pos_x;
    y_s = start_pos_y + height*3;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 13 - 9
    edge_info.first  = 9;
    edge_info.second._point = {x_s, y_s - height};
    edge_info.second.dir = eDirection::UP;
    _info.edges.push_back(edge_info);

    // line 13 - 14
    edge_info.first  = 14;
    edge_info.second._point = {x_s + width, y_s};
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(13, _info));
  }
//------------------------------------------------------------------------------

// 14 - 13, 15
  mGraph.connect_nodes(14, 15);
  {
    info _info;
    x_s = start_pos_x + width;
    y_s = start_pos_y + height*3;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 14 - 13
    edge_info.first  = 13;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    // line 14 - 15
    edge_info.first  = 15;
    edge_info.second._point = {x_s + width, y_s};
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(14, _info));
  }
//------------------------------------------------------------------------------

// 15 - 14, 16
  mGraph.connect_nodes(15, 16);
  {
    info _info;
    x_s = start_pos_x + width*2;
    y_s = start_pos_y + height*3;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 15 - 14
    edge_info.first  = 14;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    // line 15 - 16
    edge_info.first  = 16;
    edge_info.second._point = {x_s + width, y_s};
    edge_info.second.dir = eDirection::RIGTH;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(15, _info));
  }
//------------------------------------------------------------------------------

// 16 - 15, 12
  {
    info _info;
    x_s = start_pos_x + width*3;
    y_s = start_pos_y + height*3;

    node_info.set_point({x_s, y_s}, 0);
    _info.node = node_info;

    // line 16 - 15
    edge_info.first  = 15;
    edge_info.second._point = {x_s - width, y_s};
    edge_info.second.dir = eDirection::LEFT;
    _info.edges.push_back(edge_info);

    // line 16 - 12
    edge_info.first  = 12;
    edge_info.second._point = {x_s, y_s - height};
    edge_info.second.dir = eDirection::UP;
    _info.edges.push_back(edge_info);

    mInfos.insert(std::make_pair(16, _info));
  }
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
void example_1::draw()
{
  static line   tmp_line;
  static circle tmp_circle;

  tmp_circle.set_radius(25);
  tmp_circle.set_segments(18);
  tmp_circle.set_point_size(3);
  tmp_circle.set_color(color(colorType::Green));
  tmp_circle.set_fill_color(color(colorType::Fuchsia));

  tmp_line.set_color(normal_edge_color);
  tmp_line.set_point_size(5);

  for(auto const &node : mInfos)
  {
    auto &x_s = node.second.node.center().x;
    auto &y_s = node.second.node.center().y;

    tmp_line.set_point({x_s, y_s} , 0);

    for(auto const &lpoint : node.second.edges)
    {
      const auto &x_e = lpoint.second._point.x;
      const auto &y_e = lpoint.second._point.y;
      tmp_line.set_point({x_e, y_e} , 1);

      if(mGraph.is_blocked(node.first) || mGraph.is_blocked(lpoint.first))
        tmp_line.set_color(blocked_edge_color);
      else
        tmp_line.set_color(normal_edge_color);
      tmp_line.draw();
    }
  }

  for(auto &node : mInfos)
  {
    if(mGraph.is_blocked(node.first))
      node.second.node.set_fill_color(blocked_node_fill_color);
    else
      node.second.node.set_fill_color(normal_node_fill_color);
    node.second.node.draw();
  }

  if(mInfos.find(mNodePos) == mInfos.end())
    return;

  const auto &x = mInfos[mNodePos].node.point(0).x;
  const auto &y = mInfos[mNodePos].node.point(0).y;

  tmp_circle.set_point({x, y}, 0);
  tmp_circle.draw();
}
//------------------------------------------------------------------------------
void example_1::block_invert(unsigned aNode)
{
  if(mGraph.is_blocked(aNode))
    mGraph.unblock(aNode);
  else
    mGraph.block(aNode);
}
//------------------------------------------------------------------------------
void example_1::set_start(unsigned aNode)
{
  mNodePos = aNode;
}
//------------------------------------------------------------------------------
void example_1::move_up()
{
  if(mInfos.find(mNodePos) == mInfos.end())
    return;

  const auto &info = mInfos[mNodePos];
  for(const auto & vi : info.edges)
  {
    if((vi.second.dir == eDirection::UP) && (!mGraph.is_blocked(vi.first)) )
    {
      mGraph.unblock(mNodePos);
      mNodePos = vi.first;
      mGraph.block(mNodePos);
      break;
    }
  }
}
//------------------------------------------------------------------------------
void example_1::move_right()
{
  if(mInfos.find(mNodePos) == mInfos.end())
    return;

  const auto &info = mInfos[mNodePos];
  for(const auto & vi : info.edges)
  {
    if((vi.second.dir == eDirection::RIGTH) && (!mGraph.is_blocked(vi.first)) )
    {
      mGraph.unblock(mNodePos);
      mNodePos = vi.first;
      mGraph.block(mNodePos);
      break;
    }
  }
}
//------------------------------------------------------------------------------
void example_1::move_down()
{
  if(mInfos.find(mNodePos) == mInfos.end())
    return;

  const auto &info = mInfos[mNodePos];
  for(const auto & vi : info.edges)
  {
    if((vi.second.dir == eDirection::DOWN) && (!mGraph.is_blocked(vi.first)) )
    {
      mGraph.unblock(mNodePos);
      mNodePos = vi.first;
      mGraph.block(mNodePos);
      break;
    }
  }
}
//------------------------------------------------------------------------------
void example_1::move_left()
{
  if(mInfos.find(mNodePos) == mInfos.end())
    return;

  const auto &info = mInfos[mNodePos];
  for(const auto & vi : info.edges)
  {
    if((vi.second.dir == eDirection::LEFT) && (!mGraph.is_blocked(vi.first)) )
    {
      mGraph.unblock(mNodePos);
      mNodePos = vi.first;
      mGraph.block(mNodePos);
      break;
    }
  }
}
