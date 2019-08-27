#include <iostream>
#include <cstring>
using namespace std;

namespace example_1
{
  class A
  {
    public:
      A()
      {
        cout << "A()" << endl;

        mp_data = new char[100];

        throw 1;
      }
      ~A()
      {
        cout << "~A()" << endl;
        
        delete [] mp_data;
      }
    private:
      char *mp_data{ nullptr };
  };

  void test()
  {
    try
    {
      A a;
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}

namespace example_2
{
  class Base
  {
    public:
      Base()
      {
        cout << "Base" << endl;
        mp_data = new char[100];
        memset(mp_data, 0, 100);
      }
      ~Base()
      {
        cout << "~Base" << endl;
        delete[] mp_data;
      }
    protected:
      char *mp_data{ nullptr };
  };

  class Child : public Base
  {
    public:
      Child()
      {
        cout << "Child" << endl;

        mp_data = new char [strlen(Base::mp_data)] + 1;
        strcpy(mp_data, Base::mp_data);

        throw 1;
      }
      ~Child()
      {
        cout << "~Child" << endl;
        delete[] mp_data;
      }
    private:
      char *mp_data{ nullptr };
  };

  void test()
  {
    try
    {
      Child c;
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}


namespace example_3
{
  class A 
  { 
    public:
      A()  { cout << "A()" << endl; }
      ~A() { cout << "~A()" << endl; }
  };

  class B
  {
  public:
    B()  { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
  };

  class C
  {
  public:
    C()  { cout << "C()" << endl; throw 1;}
    ~C() { cout << "~C()" << endl; }
  };

  class D
  {
  public:
    D()  { cout << "D()" << endl; }
    ~D() { cout << "~D()" << endl; }
  };

  class Unit
  {
    public:
      Unit() 
      //try
      { 
        cout << "Unit()" << endl; 
      }
      ~Unit() 
      { 
        cout << "~Unit()" << endl; 
      }
    private:
      A m_a;
      B m_b;
      C m_c;
      D m_d;
  };

  void test()
  {
    try
    {
      Unit unit;
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}


namespace example_4
{
  void func_throw()
  {
    std::cout << "exception happened!" << endl;
    throw 1;
  }

  class cls_desctructor 
  {
    public:
    ~cls_desctructor() 
    {
      cout << "~cls_desctructor()" << endl;
    }
  };

  class A
  {
    public:
      ~A()
      { 
        try
        {
          func_throw();
        }
        catch(...)
        {
          cout << "~A() exception was caught" << endl;
        }
        cout << "~A()" << endl;
      }
    private:
      cls_desctructor d;
  };

  void test()
  {
    try
    {
      A a;
    }
    catch (int i) 
    {
      cout << "Catched int exception: " << i << "\n";
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}

namespace example_5
{
  void func_throw()noexcept(false)
  {
    std::cout << "exception happened!" << endl;
    throw 1;
  }

  class cls_desctructor
  {
  public:
    ~cls_desctructor()
    {
      cout << "~cls_desctructor()" << endl;
    }
  };

  class A
  {
  public:
    ~A()noexcept(false)
    {
      cout << "~A()" << endl;
      func_throw();
    }
  private:
    cls_desctructor d;
  };

  void test()
  {
    try
    {
      A a;
      throw "123";
    }
    catch (int i)
    {
      cout << "Catched int exception: " << i << "\n";
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}

namespace example_6
{
  void func_throw()noexcept(false)
  {
    std::cout << "exception happened!" << endl;
    throw 1;
  }

  class cls_desctructor
  {
  public:
    ~cls_desctructor()
    {
      cout << "~cls_desctructor()" << endl;
    }
  };

  class A
  {
  public:
    ~A()noexcept(false)
    {
      cout << "~A()" << endl;

      try
      {
        func_throw();
      }
      catch (...)
      {
        cout << "catched exception in ~A()" << endl;
      }
    }
  private:
    cls_desctructor d;
  };

  void test()
  {
    try
    {
      A a;
      throw "123";
    }
    catch (int i)
    {
      cout << "Catched int exception: " << i << "\n";
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}

namespace example_7
{
  void func_throw()
  {
    std::cout << "exception happened!" << endl;
    throw 1;
  }

  class cls_desctructor
  {
  public:
    ~cls_desctructor()
    {
      cout << "~cls_desctructor()" << endl;
    }
  };

  class A
  {
  public:
    ~A()
    try
    {
      cout << "~A()" << endl;

      if (std::uncaught_exception()) 
      {
        std::cerr << "~A() stack unwinding, not throw" << endl;
      }
      else 
      {
        std::cerr << "~A() normal, throw" << endl;
        func_throw();
      }
    }
    catch(...)
    {

    }
  private:
    cls_desctructor d;
  };

  void test()
  {
    try
    {
      A a;
      throw "123";
    }
    catch (int i)
    {
      cout << "Catched int exception: " << i << "\n";
    }
    catch (...)
    {
      cout << "exception was caught" << endl;
    }
  }
}

int main(int, char**) 
{
  //example_1::test();
  //example_2::test();
  //example_3::test();

  //example_4::test();
  //example_5::test();
  //example_6::test();
  example_7::test();
  return 0;
}
