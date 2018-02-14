#include <iostream>

#define NDEBUG
#include <cassert>

using namespace std;

namespace example_a
{
  void test(void *aPtr [[maybe_unused]])
  {
    assert(aPtr != nullptr);
  }
}

namespace example_b
{
  [[maybe_unused]] static void foo()
  {
  }
}

namespace example_c
{
  void test()
  {
    [[maybe_unused]] int a = 0;
  }
}

int main()
{
  example_a::test(nullptr);
  return 0;
}
