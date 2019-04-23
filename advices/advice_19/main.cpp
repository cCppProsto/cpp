#include <iostream>
#include <string>

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 8 - Различайте значения операторов new и delete


namespace example_1
{
  struct Test
  {
    Test()
    {
      std::cout << "Test() this = " << this << std::endl;
    }
    ~Test()
    {
      std::cout << "~Test()" << std::endl;
    }
  };

  void test()
  {
    Test *pt = new Test();
    delete pt;
  }
}

namespace example_2
{
  struct Test
  {
    Test()
    {
      std::cout << "Test() this = " << this << std::endl;
    }
    ~Test()
    {
      std::cout << "~Test()" << std::endl;
    }
  };

  void test()
  {
    void *raw_memory = operator new(sizeof(Test));
    std::cout << "raw memory pointer = " << raw_memory << std::endl;

    new(raw_memory)Test();

    static_cast<Test*>(raw_memory)->~Test();

    operator delete(raw_memory);
  }
}


namespace example_3
{
  struct Test
  {
    Test()
    {
      std::cout << "Test() this = " << this << std::endl;
    }
    ~Test()
    {
      std::cout << "~Test()" << std::endl;
    }

    void *operator new(size_t size)
    {
      std::cout << "new operator overloaded" << std::endl;
      void *p = malloc(size);
      return p;
    }

    void operator delete(void *ptr)
    {
      std::cout << "delete operator overloaded" << std::endl;
      free(ptr);
    }
  };

  void test()
  {
    Test *p = new Test();
    delete p;
  }
}


int main()
{
  example_1::test();
  std::cout << std::endl << std::endl;

  example_2::test();
  std::cout << std::endl << std::endl;

  example_3::test();
  std::cout << std::endl << std::endl;

  return 0;
}
