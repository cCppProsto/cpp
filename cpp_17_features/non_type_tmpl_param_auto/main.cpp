#include <iostream>
#include <tuple>
#include <variant>
#include <array>
using namespace std;



/*
A template-argument for a non-type, non-template template-parameter shall be one of:
[...]
a constant expression (5.19) that designates the address of a complete object
with static storage duration and external or internal linkage or a function with
external or internal linkage, including function templates and function
template-ids but excluding non-static class members, expressed
(ignoring parentheses) as & id-expression, where the id-expression is the name
of an object or function, except that the & may be omitted if the name refers to
a function or array and shall be omitted if the corresponding template-parameter
is a reference;
*/

//------------------------------------------------------------------------------
namespace example_a
{
  template<typename T, std::size_t Count>
  struct _array_a
  {
    T buffer[Count];
  };

  template<typename T, auto Count>
  struct _array_b
  {
    T buffer[Count];
  };

  void test()
  {
    _array_a<int, 10>   a_buffer;
    _array_b<int, 10>   b_buffer;
  }
}

namespace example_b
{
  void f_a(auto a)
  {
  }

  template <typename T> void f_b(T a)
  {
  }

  template <auto a> void f_c()
  {
  }

  template <typename T,
            auto start,
            auto end>
  void f_d(T a)
  {
    for(auto i = start; i < end; ++i)
      cout << a[i] << ",";
    cout << endl;
  }

  void test()
  {
    array ar{1,2,3,4,5,6};

    f_a(10);

    f_b<int>(10);

    f_c<10>();

    f_d<decltype(ar), 1, 3>(ar);
  }
}

namespace example_c
{
  template <typename Type, Type value> constexpr Type TConstant = value;

  void test()
  {
    constexpr auto const MySuperConst = TConstant<int, 100>;
  }
}

namespace example_d
{
  template <auto value> constexpr auto TConstant = value;

  void test()
  {
    constexpr auto const MySuperConst = TConstant <100>;
  }
}



template<typename Type, Type a>
void early()
{
  cout << a << endl;
}

template<auto a>
void now()
{
  cout << a << endl;
}

int main()
{
  early<int,  1>();
  early<char, 'a'>();

  now<10>();
  now<'a'>();

  return 0;
}
