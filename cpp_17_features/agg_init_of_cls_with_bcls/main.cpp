#include <iostream>

using namespace std;


/*
An aggregate is an array or a class with:
- no user-provided constructors
- no private or protected non-static data members
- no virtual functions
- no virtual, private or protected base classes
*/


// Aggregate initialization of classes with base classes
namespace example_a
{
  struct pos2D
  {
    int x{0};
    int y{0};
  };

  struct pos3D : pos2D
  {
    int z{0};
  };

  void f()
  {
    pos3D pos_a{ {1,2}, 3 };  // x = 1, y = 2, z = 3
    pos3D pos_b{ {}, 3 };     // x = 0, y = 0, z = 3
    pos3D pos_c{ {1}, 3 };    // x = 1, y = 0, z = 3
  }
}

namespace example_b
{
  struct pos2D
  {
    int x{0};
    int y{0};
  };

  struct pos3D : pos2D
  {
    int z{0};
  };

  struct pos4D : pos3D
  {
    int time{0};
  };

  void f()
  {
    pos4D pos_a{ {{1,2}, 3}, 100};  // x = 1, y = 2, z = 3  time = 100
    pos4D pos_b{ {{}, 3}, 200 };     // x = 0, y = 0, z = 3 time = 200
    pos4D pos_c{ {{1}, 3}, 300 };    // x = 1, y = 0, z = 3 time = 300
  }
}

namespace example_c
{
  struct posXY
  {
    int x{0};
    int y{0};
  };

  struct posZ
  {
    int z{0};
  };

  struct pos3D : posXY, posZ
  {
  };

  void f()
  {
    pos3D pos_a{ {1,2}, {3}};  // x = 1, y = 2, z = 3
    pos3D pos_b{ {}, {3} };     // x = 0, y = 0, z = 3
    pos3D pos_c{ {1}, {3} };    // x = 1, y = 0, z = 3
  }
}

namespace example_d
{
  struct base
  {
    int id;
  };

  struct derived : base
  {
    void print()
    {
      cout << id << endl;
    }
    int val;
  };

  void f()
  {
    derived a{1};
    derived b{{1}};
    derived c{{1},2};
    derived d{1,2};
    derived e{{},2};
  }
}

int main()
{
  example_a::f();
  example_b::f();
  example_c::f();
  example_d::f();


  struct base
  {
    base()
    :id(0)
    {

    }
    int id{100};
  };

  struct derived : base
  {
    void print()
    {
      cout << id << endl;
    }
    int val;
  };

  derived d{{}, 2};


  return 0;
}
