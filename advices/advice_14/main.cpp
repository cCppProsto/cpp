#include <iostream>
#include <string>

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 2 - Предпочитайте приведение типов в стиле С++

using namespace std;

namespace example_1
{
  void test()
  {
    int  *pi = new int;
    char *ch;

    //ch = pi;                        // error
    ch = (char*)pi;                   // OK

    //ch = const_cast<char*>(pi);       // error
    //ch = static_cast<char*>(pi);      // error
    //ch = dynamic_cast<char*>(pi);     // error
    ch = reinterpret_cast<char*>(pi); // OK
  }
}

namespace example_const_cast
{
  void func(int *apInt)
  {
    *apInt = 0;
  }

  template <typename T>
  void tmpl_func(T *aPtr)
  {
    *aPtr = 0;
  }

  void test()
  {
    const char c_str_a[] = "Hello";
    char *c_str_b;

    //c_str_b = c_str_a;                                    // error
    c_str_b = const_cast<char*>(c_str_a);                   // OK
    c_str_b[0] = 'A';

    const std::string str_a{"Hello"};
    //std::string &str_b { str_a };                         // error
    std::string &str_b { const_cast<std::string&>(str_a)};  // OK
    str_b[0] = 'A';

    const int i = 0;
    //int *p_i = &i;                                        // error
    int *p_i = const_cast<int*>(&i);                        // OK
    (*p_i) = 10;

    //func(&i);                                             // error
    func(const_cast<int*>(&i));                             // OK
    (*p_i) = 10;

    tmpl_func(p_i);

    (*p_i) = 10;

    //tmpl_func(const_cast<const int*>(p_i));               // error
  }
}

namespace example_static_cast
{
  struct sTest
  {
    operator double() const
    {
      return 1.0;
    }
    operator int() const
    {
      return 1;
    }
    int m_i { 0 };
  };

  void test()
  {
    double d_a { 10 };
    int i_a    { d_a/3 };                                       // warning
    int i_b    {static_cast<int>(d_a/3)};                       // OK

    void *p_v_a  = nullptr;
    int  *p_i_a  = nullptr;
    char *p_ch_a = nullptr;                                   // error
    p_ch_a = static_cast<char*>(p_v_a);                       // OK
    //p_ch_a = static_cast<char*>(p_i_a);                       // error

    sTest test;

    double d_b { 0.0 };
    d_b = (int)test;
    d_b = test;
  }
}

namespace example_dynamic_cast
{
  class Base_A
  {
    public:
      void test(){}
  };

  class Child_A : public Base_A
  {
    public:
      void test(){}
      void test_child(){}
  };

  class Base_B
  {
    public:
      virtual void test(){}
  };

  class Child_B : public Base_B
  {
    public:
      void test(){}
      void test_child(){}
  };

  class Child_C : public Base_B
  {
    public:
      void test(){}
      void test_child(){}
  };


  void test()
  {
    Base_A  *pbase_a = new Child_A;
    //Child_A *pchild_a = dynamic_cast<Child_A*>(pbase_a);    // error
    Child_A *pchild_a = (Child_A*)pbase_a;                  // OK

    Base_B  *pbase_b = new Child_C;
    Child_B *pchild_b = nullptr;
    pchild_b = dynamic_cast<Child_B*>(pbase_b);

    if(dynamic_cast<Child_B*>(pbase_b))
    {
      std::cout << "Child B\n";
    }

    if(dynamic_cast<Child_C*>(pbase_b))
    {
      std::cout << "Child C\n";
    }

  }
}

namespace example_reinterpret_cast
{
  void f_a()
  {
  }

  struct sTest
  {
    void func(float)
    {
    }
    int m_i;
  };

  void test()
  {
    sTest s;

    reinterpret_cast<float *>(&s.m_i);
    reinterpret_cast<int (*) ()>(&f_a);
    reinterpret_cast<double sTest::*>(&sTest::m_i);
  }
}

int main()
{
  example_1::test();

  example_const_cast::test();
  example_static_cast::test();
  example_dynamic_cast::test();
  example_reinterpret_cast::test();

  return 0;
}





















