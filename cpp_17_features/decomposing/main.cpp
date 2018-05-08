#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace example_a
{
  void test()
  {
    int pos[3] = {1,2,3};

    auto [x, y, z] = pos;
    x = 10;
    y = 20;
    z = 30;

    auto & [rx, ry, rz] = pos;
    rx = 10;
    ry = 20;
    rz = 30;

    int positions[2][3] =
    {
      {1,2,3},
      {4,5,6}
    };

    for(int i = 0; i < 2; ++i)
    {
      auto [x, y, z] = positions[i];
      cout << x << " : " << y << " : " << z << endl;
    }
  }
}

namespace example_b
{
  struct position
  {
    int x{0};
    int y{0};
    int z{0};
  };

  position get_pos()
  {
    return position{100, 200, 300};
  }

  void test()
  {
    auto [x, y, z] = get_pos();
    cout << x << " : " << y << " : " << z << endl;
  }
}

namespace example_c
{
  struct pos
  {
    int x{0};
    int y{0};
    int z{0};
  };

  void test()
  {
    pos positions[3] =
    {
      {1,2,3}
     ,{4,5,6}
     ,{7,8,9}
    };

    for(auto [x,y,z] : positions)
    {
      cout << x << " : " << y << " : " << z << endl;
    }
  }
}

namespace example_d
{
  map<string, int> get_map()
  {
    return
    {
      { "world 1", 1 },
      { "world 2", 2 },
      { "world 3", 3 },
      { "world 4", 4 },
    };
  }

  void test()
  {
    for (auto [ world, id ] : get_map())
      cout << "world=\"" << world << "\" id=" << id << endl;
  }
}

int main()
{
  //example_a::test();
  //example_b::test();
  //example_c::test();
  example_d::test();

  map<int, int> myMap{ {1, 11}, { 2,22 }, { 3,33 }};
  auto[it, success] = myMap.insert({ 4,44 });

  auto v = (*it);
  cout << success << endl;

  return 0;
}
