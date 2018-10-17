#include <iostream>
#include <cstring>


namespace example_1
{
  void test()
  {
    char *p = 0;

    if( (p!=0) && std::strlen(p) > 10)
    {
    }

    int index = 1;
    int lowerBound = 10;
    int upperBound = 100;
    if( (index < lowerBound) || (index > upperBound) )
    {
    }
  }
}

namespace example_2
{
  bool expression_1()
  {
    std::cout << "expression 1" << std::endl;
    return true;
  }

  bool expression_2()
  {
    std::cout << "expression 2" << std::endl;
    return true;
  }

  bool expression_3()
  {
    std::cout << "expression 3" << std::endl;
    return false;
  }

  bool expression_4()
  {
    std::cout << "expression 4" << std::endl;
    return false;
  }

  void test()
  {
    if(expression_1() || expression_2())
    {

    }

    if(expression_3() && expression_4())
    {

    }

    if(expression_1(),expression_2())
    {
    }
  }
}

namespace example_3
{
  enum eTest
  {
    UNKNOWN
   ,ENUM_1
   ,ENUM_2
  };

  bool operator&& (const eTest &aLhs, const eTest &aRhs)
  {
    return (aLhs != UNKNOWN) && (aRhs != UNKNOWN);
  }

  bool operator|| (const eTest &aLhs, const eTest &aRhs)
  {
    return (aLhs != UNKNOWN) || (aRhs != UNKNOWN);
  }

  eTest operator, (const eTest &aLhs, const eTest &aRhs)
  {
    return aRhs;
  }

  eTest expression_1()
  {
    std::cout << "expression 1" << std::endl;
    return ENUM_1;
  }

  eTest expression_2()
  {
    std::cout << "expression 2" << std::endl;
    return ENUM_2;
  }

  eTest expression_3()
  {
    std::cout << "expression 3" << std::endl;
    return ENUM_1;
  }

  eTest expression_4()
  {
    std::cout << "expression 4" << std::endl;
    return ENUM_2;
  }

  void test()
  {
    eTest e1 = ENUM_1;
    eTest e2 = ENUM_2;
    if(expression_1() || expression_2())
    {
    }

    if(expression_3() && expression_4())
    {
    }

    if(expression_1(),expression_2())
    {
    }
  }
}

int main()
{
  //example_1::test();

  example_2::test();

  std::cout << std::endl;

  example_3::test();
  return 0;
}
