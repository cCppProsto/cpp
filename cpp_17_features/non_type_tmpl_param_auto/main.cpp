#include <iostream>
#include <tuple>
#include <variant>
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
  template <auto ... vs> struct HeterogenousValueList { };

  void example()
  {
    using MyList = HeterogenousValueList<'a', 100, 'b'>;
  }
}

int main()
{
  example_a::example();
  return 0;
}
