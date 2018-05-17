#include <iostream>

using namespace std;

struct  A
{
  void func()
  {
    cout << "A::func" << endl;
  }
};

struct  B : A
{
  void func()
  {
    cout << "B::func" << endl;
  }
};

namespace example_a
{
  void test()
  {
    A a;
    B b;
    a.func();
    b.func();
  }
}

namespace example_b
{
  void test()
  {
    A *pa;
    B *pb;
    B b;

    //...
    pa = &b;
    pb = &b;

    pa->func();
    pb->func();
  }
}

namespace example_c
{
  void f(A *pa)
  {
    pa->func();
  }

  void test()
  {
    A a;
    B b;

    f(&a);
    f(&b);
  }
}

int main()
{
  //example_a::test();
  //example_b::test();
  example_c::test();
  return 0;
}






















