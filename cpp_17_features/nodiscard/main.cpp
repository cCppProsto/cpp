#include <iostream>
#include <memory>

using namespace std;

namespace example_a
{
  [[nodiscard]] int *value()
  {
    return new int;
  }
  [[nodiscard]] unique_ptr<int> createIntValue(int aVal)
  {
    return make_unique<int>(aVal);
  }

  void test()
  {
    //createIntValue(1);
    //value();
  }
}

namespace example_b
{
  struct [[nodiscard]] sData
  {
    char ch;
    int i;
  };

  sData foo_a()
  {
    return {'A', 65};
  }

  sData foo_b()
  {
    return {'A', 65};
  }


  void test()
  {
    foo_a();
    foo_b();
  }
}

int main()
{
  example_a::test();
  example_b::test();
  return 0;
}
