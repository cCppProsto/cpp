#include <iostream>
#include <cstring>

using namespace std;



namespace example_1
{
  class String
  {
  public:
    String(const char *)
    {
      std::cout << "String()" << std::endl;
    }

    String(const String &)
    {
      std::cout << "String(const String &)" << std::endl;
    }

    ~String()
    {
      std::cout << "~String()" << std::endl;
    }
  };

  void func(const String &)
  {
    std::cout << "func_a" << std::endl;
  }

  void test()
  {
    char buffer[] = "buffer";

    String str("");
    std::cout << "--------------------------------------------" << std::endl;
    func(str);
    std::cout << "--------------------------------------------" << std::endl;

    func(buffer);
    std::cout << "--------------------------------------------" << std::endl;
    func("Hello");
    std::cout << "--------------------------------------------" << std::endl;
  }
}

namespace example_2
{
  class String
  {
  public:
    String(const char *)
    {
      std::cout << "String()" << std::endl;
    }

    String(const String &)
    {
      std::cout << "String(const String &)" << std::endl;
    }

    ~String()
    {
      std::cout << "~String()" << std::endl;
    }
  };

  void func_a(const String)
  {
    std::cout << "func_a" << std::endl;
  }

  void test()
  {
    char buffer[] = "buffer";

    String str("");
    std::cout << "--------------------------------------------" << std::endl;
    func_a(str);
    std::cout << "--------------------------------------------" << std::endl;

    func_a(buffer);
    std::cout << "--------------------------------------------" << std::endl;
    func_a("Hello");
    std::cout << "--------------------------------------------" << std::endl;
  }
}

namespace example_3
{
  class String
  {
  public:
    explicit String(const char *)
    {
      std::cout << "String()" << std::endl;
    }

    String(const String &)
    {
      std::cout << "String(const String &)" << std::endl;
    }

    ~String()
    {
      std::cout << "~String()" << std::endl;
    }
  };

  void func_a(const String &)
  {
    std::cout << "func_a" << std::endl;
  }

  void test()
  {
    char buffer[] = "buffer";

    String str("");
    std::cout << "--------------------------------------------" << std::endl;
    func_a(str);
    std::cout << "--------------------------------------------" << std::endl;

    //func_a(buffer);  // compilation error
    std::cout << "--------------------------------------------" << std::endl;
    //func_a("Hello"); // compilation error
    std::cout << "--------------------------------------------" << std::endl;
  }
}

namespace example_4
{
  class String
  {
  public:
    String(const char *)
    {
      std::cout << "String()" << std::endl;
    }

    String(const String &)
    {
      std::cout << "String(const String &)" << std::endl;
    }

    ~String()
    {
      std::cout << "~String()" << std::endl;
    }
  };

  void func_a(String &)
  {
    std::cout << "func_a" << std::endl;
  }

  void test()
  {
    char buffer[] = "buffer";

    String str("");
    std::cout << "--------------------------------------------" << std::endl;
    func_a(str);
    std::cout << "--------------------------------------------" << std::endl;

    // func_a(buffer);  // compilation error
    std::cout << "--------------------------------------------" << std::endl;
    // func_a("Hello"); // compilation error
    std::cout << "--------------------------------------------" << std::endl;
  }
}

int main()
{
  example_1::test();
  std::cout << std::endl << std::endl << std::endl;

  example_2::test();
  std::cout << std::endl << std::endl << std::endl;

  example_3::test();
  std::cout << std::endl << std::endl << std::endl;

  example_4::test();
  std::cout << std::endl << std::endl << std::endl;

  return 0;
}
