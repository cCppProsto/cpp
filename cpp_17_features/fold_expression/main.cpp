#include <iostream>
#include <vector>
#include <array>

using namespace std;

/*
+   -   *   /   %   ^   &   |
+=  -=  *=  /=  %=  ^=  &=  |=
~
=   <   >    <<    >>
==  <=  >=   <<=   >>=
!= &&  ||  ,  .*  ->*
*/

//------------------------------------------------------------------------------
namespace example_a
{
  template<typename... T> auto summa(T ... s)
  {
    return (... + s);
  }

  void f()
  {
    cout << summa(1,2,3) << endl;
  }
}
//------------------------------------------------------------------------------
namespace example_b
{
  template<typename Fnc, typename... T>
  void call(Fnc pFunc, T&&... vr)
  {
    (pFunc(vr), ...);
  }

  void f()
  {
    call([](auto v) { cout << v << " "; }, 69 ," <- | -> ", 100);
    cout << endl;
  }
}
//------------------------------------------------------------------------------
namespace example_c
{
  template<typename... Args>
  auto unary_right(Args... args)
  {
    return (args + ...);
  }

  template<typename... Args>
  auto unary_left(Args... args)
  {
      return (... + args);
  }

  template<typename... Args>
  auto binary_right(Args... args)
  {
      return (args + ... + 0);
  }

  template<typename... Args>
  auto binary_left(Args... args)
  {
      return (10 + ... + args);
  }

  void f()
  {
    cout << unary_right(2,2)  << endl;
    cout << unary_left(2,2)   << endl;
    cout << binary_right(2,2) << endl;
    cout << binary_left(2,2)  << endl;
  }
}
//------------------------------------------------------------------------------
namespace example_d
{
  template <class... Args>
  bool containsZero(Args const&... args)
  {
    return ((args == 0) || ...);
  }

  void f()
  {
    cout << (containsZero(1,2,3,4,5) ? "yes" : "no") << endl;
    cout << (containsZero(1,0,3,4,5) ? "yes" : "no") << endl;
  }
}
//------------------------------------------------------------------------------
namespace example_e
{
  template <class... Args> bool isOk(Args ... args)
  {
    return (args() && ...);
  }

  void f()
  {
    // sensors
    auto s1 = []{ return true;};
    auto s2 = []{ return true;};
    auto s3 = []{ return true;};
    auto s4 = []{ return true;};
    auto s5 = []{ return true;};

    cout << (isOk(s1, s2, s3, s4, s5) ? "all Ok. Go! brrrr" : "stop" ) << endl;
  }
}

int main()
{
  //example_a::f();
  //example_b::f();
  //example_c::f();
  //example_d::f();
  example_e::f();
  return 0;
}
