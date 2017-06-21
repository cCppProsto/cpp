#include <iostream>

void example_1()
{
  struct A
  {
    virtual void f1() const { std::cout << "A::f1()\n"; }
    virtual void f2(int) { std::cout << "A::f2()\n"; }
    void f3() { std::cout << "A::f3()\n"; }
  };

  struct B : A
  {
    virtual void f1() { std::cout << "B::f1()\n"; }
    virtual void f2(unsigned) { std::cout << "B::f2()\n"; }
    virtual void f3() { std::cout << "B::f3()\n"; }
  };

  A a;
  B b;

  a.f1();                     // call - A::f1()
  a.f2(1);                    // call - A::f1()
  a.f3();                     // call - A::f1()
  std::cout << std::endl << std::endl;

  b.f1();                     // call - B::f1()
  b.f2(1);                    // call - B::f1()
  b.f3();                     // call - B::f1()
  std::cout << std::endl << std::endl;

  A *pb = new B;
  pb->f1();                   // call - A::f1()
  pb->f2(1);                  // call - A::f1()
  pb->f3();                   // call - A::f1()
  std::cout << std::endl << std::endl;
}

void example_2()
{
  struct A
  {
    virtual void f1() const { std::cout << "A::f1()\n"; }
    virtual void f2(int) { std::cout << "A::f2()\n"; }
    virtual void f3() { std::cout << "A::f3()\n"; }
  };

  struct B : A
  {
    virtual void f1() const override { std::cout << "B::f1()\n"; }
    virtual void f2(int) override { std::cout << "B::f2()\n"; }
    virtual void f3() override { std::cout << "B::f3()\n"; }
  };

  A a;
  B b;

  a.f1();                     // call - A::f1()
  a.f2(1);                    // call - A::f1()
  a.f3();                     // call - A::f1()
  std::cout << std::endl << std::endl;

  b.f1();                     // call - B::f1()
  b.f2(1);                    // call - B::f1()
  b.f3();                     // call - B::f1()
  std::cout << std::endl << std::endl;

  A *pb = new B;
  pb->f1();                   // call - B::f1()
  pb->f2(1);                  // call - B::f1()
  pb->f3();                   // call - B::f1()
  std::cout << std::endl << std::endl;
}

void example_3()
{
  struct A
  {
    virtual void f0()final {}
    virtual void f1() { std::cout << "A::f1()\n"; }
  };

  struct B : A
  {
    //void f0(){}
    virtual void f1() override final { std::cout << "B::f1()\n"; }
  };

  // ERROR
  /*
  struct C : B
  {
    virtual void f1() { std::cout << "C::f1()\n"; }
  };
  */
}

void example_4()
{
    struct A final
    {
    };

    // ERROR
    /*
    struct B : A
    {
    };
    */
}

void example_5()
{
    struct A
    {
    };


    struct B final: A
    {
    };

    // ERROR
    /*
    struct C : B
    {
    };
    */
}


int main()
{
  // override
  //example_1();
  //example_2();

  // final
  example_3();
  //example_4();
  //example_5();

  return 0;
}

