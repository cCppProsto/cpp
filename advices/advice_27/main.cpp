#include <iostream>

using namespace std;

namespace example_1
{
  class UPInt
  {
    public:
      UPInt()
      {
        std::cout << "UPInt()" << std::endl;
      }
      UPInt(int value)
      {
        std::cout << "UPInt(int)" << std::endl;
      }

      const UPInt &operator=(const UPInt &obj)
      {
        std::cout << "operator=" << std::endl;
        return *this;
      }
      UPInt(const UPInt &obj)
      {
        std::cout << "UPInt(const UPInt &obj)" << std::endl;
      }

      ~UPInt()
      {
        std::cout << "~UPInt()" << std::endl;
      }
  };

  const UPInt operator+(const UPInt &rhs, const UPInt &lhs)
  {
    UPInt res;
    return res;
  }
  void test()
  {
    UPInt i1;
    UPInt i2;
    UPInt i3 = i1 + i2;
  }
}

namespace example_2
{
  class UPInt
  {
    public:
      UPInt()
      {
        std::cout << "UPInt()" << std::endl;
      }
      UPInt(int value)
      {
        std::cout << "UPInt(int)" << std::endl;
      }

      const UPInt &operator=(const UPInt &obj)
      {
        std::cout << "operator=" << std::endl;
        return *this;
      }
      UPInt(const UPInt &obj)
      {
        std::cout << "UPInt(const UPInt &obj)" << std::endl;
      }

      ~UPInt()
      {
        std::cout << "~UPInt()" << std::endl;
      }
  };

  const UPInt operator+(const UPInt &rhs, const UPInt &lhs)
  {
    UPInt res;
    return res;
  }
  void test()
  {
    UPInt i1;
    UPInt i2;
    UPInt i3 = 10 + i2;
  }

}

namespace example_3
{
class UPInt
  {
    public:
      UPInt()
      {
        std::cout << "UPInt()" << std::endl;
      }

      UPInt(int value)
      {
        std::cout << "UPInt(int)" << std::endl;
      }

      const UPInt &operator=(const UPInt &obj)
      {
        std::cout << "operator=" << std::endl;
        return *this;
      }
      UPInt(const UPInt &obj)
      {
        std::cout << "UPInt(const UPInt &obj)" << std::endl;
      }

      ~UPInt()
      {
        std::cout << "~UPInt()" << std::endl;
      }
  };

  const UPInt operator+(const UPInt &rhs, const UPInt &lhs)
  {
    UPInt res;
    return res;
  }

  const UPInt operator+(const int &rhs, const UPInt &lhs)
  {
    UPInt res;
    return res;
  }

  const UPInt operator+(const UPInt &rhs, const int &lhs)
  {
    UPInt res;
    return res;
  }

  void test()
  {
    UPInt i1;
    UPInt i2;
    UPInt i3 = 10 + i2;
  }
}


int main()
{
  example_1::test();
  cout << "-----------------------------------------------------------" << endl;
  example_2::test();
  cout << "-----------------------------------------------------------" << endl;
  example_3::test();
  cout << "-----------------------------------------------------------" << endl;
  return 0;
}
