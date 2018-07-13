#include <iostream>

using namespace std;


namespace test_1
{
  void func(int &i)
  {
    std::cout << "lvalue" << std::endl;
  }
  void func(int &&i)
  {
    std::cout << "rvalue" << std::endl;
  }

  void test()
  {
    int i = 0;
    func(i);
    func(1);
  }
}

namespace test_2
{
  void func(const int &i)
  {
    std::cout << "lvalue" << std::endl;
  }
  void func(int &&i)
  {
    std::cout << "rvalue" << std::endl;
  }

  template<typename T>
  void wrapper(T &&aValue)
  {
    func(aValue);                  // always lvalue
    func(std::forward<T>(aValue)); // rvalue if rvalue, else lvalue
  }

  void test()
  {
    int i = 0;
    wrapper(i);

    wrapper(1);
  }
}

namespace test_3
{
  void func(const std::string &aStr)
  {
    std::string str { aStr };
    std::cout << str << std::endl;
  }
  void func(std::string &&aStr)
  {
    std::string str { std::move(aStr) };
    std::cout << str << std::endl;
  }

  template<typename T>
  void wrapper_1(T &&aValue)
  {
    func(aValue);
  }

  template<typename T>
  void wrapper_2(T &&aValue)
  {
    func(std::forward<T>(aValue));
  }

  void test()
  {
    std::string str("Hello!");
    std::cout << "------------------\n";
    wrapper_2(std::move(str));
    wrapper_1(std::move(str));
    wrapper_2(std::move(str));
  }
}

int main()
{
  //test_1::test();
  //std::cout << "---------------------------------------------------------\n";
  //test_2::test();
  //std::cout << "---------------------------------------------------------\n";
  test_3::test();

  return 0;
}
