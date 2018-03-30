#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

namespace example_a
{
  void example()
  {
    pair   p(2, 4.5);       // deduces to std::pair<int, double> p(2, 4.5);
    vector v_a{1,2,3,4};    // deduces to std::vector<int> v{1,2,3,4};
    auto   v_b = std::vector<int>{};
  }
}

namespace example_b
{
  template <typename T>
  struct S
  {
    S(T const &aVal)
      :mVal(aVal)
    {
    }
    T mVal;
  };

  S(const char *) -> S<string>;
  S(float) -> S<int>;

  void example()
  {
    S i(1);
    S s("hello");
    S f(1.f);
    S d(1.);
  }
}

namespace example_c
{
  template<typename T, typename U>
  struct S
  {
    //S(T t, U u) { }

    T first;
    U second;
  };

  template<typename T, typename U> S(const T &f, const U &s) -> S<T, U>;

  void example()
  {
    S _s = {1, 2};
    S sa = { 42, "hello", };
    S sb = { "hello", "World" };
    //cout << sa.first << sa.second << endl;
    //cout << sb.first << sb.second << endl;
  }
}

int main()
{
  example_a::example();
  example_b::example();
  example_c::example();
  return 0;
}













