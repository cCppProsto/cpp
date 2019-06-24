#include <iostream>

using namespace std;

namespace examle_1
{
  class C1
  {
    public:
                    C1(){}
      virtual      ~C1(){}
      virtual void  f1(){}
      virtual int   f2(char)const{ return 0;}
      virtual void  f3(const int&){ }
              void  f4(){}
  };

  /*
    C1 - vtbl [
                C1::~C1
                C1::f1
                C1::f2
                C1::f3
              ]
  */
}

namespace examle_2
{
  class C1
  {
    public:
                    C1(){}
      virtual      ~C1(){}
      virtual void  f1(){}
      virtual int   f2(char)const{ return 0;}
      virtual void  f3(const int&){ }
              void  f4(){}
  };
  /*
    C1 - vtbl [
                C1::~C1
                C1::f1
                C1::f2
                C1::f3
              ]
  */

  class C2 : public C1
  {
    public:
                    C2(){}
      virtual      ~C2(){}
      virtual void  f1(){}
      virtual void  f5(const char*){ }
  };
  /*
    C2 - vtbl [
                C2::~C2
                C2::f1
                C1::f2
                C1::f3
                C2::f5
              ]
  */

  void test()
  {
    C1 *obj = new C1;
    obj->f1();
    delete obj;
    obj = new C2;
    obj->f1();

    //(*obj->vptr[i])(f1);
  }
}

namespace examle_3
{
/*
  object
  [
    data
    vptr
  ]

or

  object
  [
    vptr
    data
  ]

or

  vptr
  object
  [
    data
  ]




obj_1
[
  data
  vptr  ────────────┐
]                   │
                    │
obj_1               │
[                   │  ┌───────┐
  data              └> │ obj_1 │
  vptr  ─────────────> │       │
]                 ┌──> │ vtbl  │
                  │    └───────┘
obj_1             │
[                 │
  data            │
  vptr  ──────────┘
]
*/
}

namespace examle_4
{
  class A {};
  class B : virtual public A {};
  class C : virtual public A {};
  class D : public B, public C {};

/*
            A
           / \
          /   \
         B     C
          \   /
           \ /
            D


D object
    B data
    vptr                   *
    pointer to base class  *
    C data
    vptr                   *
    pointer to base class  *
    D data
    A data
    vptr                   *
*/
}


int main()
{
  return 0;
}
