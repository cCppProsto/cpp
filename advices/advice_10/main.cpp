#include <iostream>
#include <string>
#include <cstring>

using namespace std;

namespace example_a
{
  void test()
  {
    char pstr[] = "Hello!";

    char *p = pstr;

    const char *pc = pstr;
    //pc[0] = '1';        // ERROR
    //pc = nullptr;       // OK

    char * const cp = pstr;
    //cp[0] = '1';        // OK
    //cp = nullptr;       // ERROR

    const char * const cpc = pstr;
    //cpc[0] = '1';        // ERROR
    //cpc = nullptr;       // ERROR
  }
}

namespace example_b
{
  struct data
  {
    operator bool()const
    {
      return true;
    }

  };

  /* const */ data operator*(const data&, const data&)
  {
    data res;
    return res;
  }

  void test()
  {
    data a, b, c;
    (a*b) = c;

    if(a*b = c)
    {
    }
  }
}

namespace example_c
{
  struct data
  {
    data(std::string aStr)
      :text(aStr)
    {
    }

    const char &operator[](std::size_t pos)const
    {
      return text[pos];
    }

    char &operator[](std::size_t pos)
    {
      return text[pos];
    }
    private:
      std::string text;
  };

  void test()
  {
    data d("Hello");
    const data cd("Hello");

    d[0]  = '1';    // OK
    //cd[0] = '2';    // ERROR
  }
}

namespace example_d
{
  struct data
  {
    data()
    {
      pText = (char*)calloc(0, 10);
      strcpy(pText, "Hello!");
    }

    /* const */ char &operator[](std::size_t pos)const
    {
      return pText[pos];
    }

  private:
    char *pText;
  };

  void test()
  {
    const data a;

    char *pc = &a[0];
    pc[0] = '1';
  }
}

namespace example_e
{
  struct data
  {
    data()
    {
      pText = (char*)calloc(0, 10);
      strcpy(pText, "Hello!");
    }

    std::size_t length() const
    {
      if(!lengthIsValid)
      {
        textLength = strlen(pText);
        lengthIsValid = true;
      }

      return textLength;
    }

  private:
    char                *pText;
    mutable bool        lengthIsValid{false};
    mutable std::size_t textLength;
  };

  void test()
  {
  }
}

namespace example_f
{

  void f1(const int value)
  {
    const     int a = value;  // OK
    //constexpr int b = value;  // ERROR
    constexpr int c = 100;    // OK
  }

  constexpr void f2(const int a, const int b)
  {
    int res = a * b;
  }

  void f3(int a)
  {
    f2(a, a);
  }

  void test()
  {
    f2(1, 2);
  }
}

namespace example_g
{
  class data
  {
  public:
    constexpr data(int aV = 0, int bV = 0)
      :a(aV)
      ,b(bV)
    {
    }

    private:
      int a;
      int b;
  };

  constexpr void f1(data a)
  {

  }

  void test()
  {
    data a;
    f1(a);
  }
}

int main()
{
  example_a::test();
  example_b::test();
  example_c::test();
  example_d::test();
  example_e::test();
  example_f::test();
  example_g::test();
  return 0;
}
