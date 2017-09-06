#include <iostream>
#include <memory>

using namespace std;

int foo_a(int i)
{
  int res = 0;
  int *p = new int{i};

  if(i > 100)
  {
    // ...
    // calculate res
    return res;
  }

  for(int j = 0; j < i; ++i)
  {
    if(1) // some expression
    {
      // calculate res
      return res;
    }
  }

  delete p;
  return res;
}

//---------------------- UNIQUE PTR --------------------------------------------
void unique_ptr_example_1()
{
  auto *pi = new int(20);
  cout << "size = "    << sizeof(pi)
       << ", addr = "  << pi
       << ", value = " << *pi << endl;

  auto upi = unique_ptr<int>(new int(10));
  cout << "size = "    << sizeof(upi)
       << ", addr = "  << upi.get()
       << ", value = " << *upi
       << ", value = " << *(upi.get())  << endl;
}
//------------------------------------------------------------------------------
void unique_ptr_example_2()
{
  struct cls
  {
    cls() { cout << "cls()" << endl;}
    ~cls() { cout << "~cls()" << endl;}

    int  a{0};
    int  b{1};
    char c{'A'};
  };

  auto pcls = unique_ptr<cls>(new cls);
  cout << "size = "   << sizeof(pcls)
       << ", addr = " << pcls.get()
       << ", a = "    << pcls->a
       << ", b = "    << pcls->b
       << ", c = "    << pcls->c << endl;
}
//------------------------------------------------------------------------------
void unique_ptr_example_3()
{
  struct cls
  {
    cls()  { cout << "cls()" << endl;}
    ~cls() { cout << "~cls()" << endl;}

    int  a{0};
    int  b{1};
    char c{'A'};
  };

  auto pcls = make_unique<cls>();
  cout << "size = "   << sizeof(pcls)
       << ", addr = " << pcls.get()
       << ", a = "    << pcls->a
       << ", b = "    << pcls->b
       << ", c = "    << pcls->c  << endl;
}
//------------------------------------------------------------------------------
void unique_ptr_example_4()
{
  auto p = new int{10};
  {
    auto up = unique_ptr<int>(p);             // PROBLEM
  }
  delete p;                                   // CRASH!
}
//------------------------------------------------------------------------------
void unique_ptr_example_5()
{
  auto p = new int{10};
  {
    auto up = unique_ptr<int>(new int(*p));   // OK
  }
  delete p;                                   // OK
}
//------------------------------------------------------------------------------
void unique_ptr_example_6()
{
  auto up_a = unique_ptr<int>(new int{2});
  //auto up_b = unique_ptr<int>(up_a);          // compilation error
  auto up_b = unique_ptr<int>(up_a.release());

  //if(up_a)
  //{
  //}
  cout << (up_a ? "up_a is not null" : "up_a is null")  << endl;
  cout << (up_b ? "up_b is not null" : "up_b is null")  << endl;

  int *pi = up_b.release();
  cout << (up_b ? "up_b is not null" : "up_b is null")  << endl;

  delete pi;
  pi = nullptr;
}
//------------------------------------------------------------------------------
void unique_ptr_example_7()
{
  struct cls
  {
    cls()  { cout << "cls()" << endl;}
    ~cls() { cout << "~cls()" << endl;}
  };

  auto p_a = make_unique<cls>();
  p_a.reset();

  auto p_b = make_unique<cls>();
  unique_ptr<cls> p_c;

  //p_c.reset(p_b.get());       // PROBLEM
  p_c.reset(p_b.release());     // NOT PROBLEM

  auto p_d = make_unique<cls>();
  p_d = nullptr;
}
//------------------------------------------------------------------------------
void unique_ptr_example_8_a(unique_ptr<int> ap)
{
  *ap = 100;
}
//------------------------------------------------------------------------------
void unique_ptr_example_8_b(unique_ptr<int> &ap)
{
  *ap = 100;
}//------------------------------------------------------------------------------
void unique_ptr_example_8()
{
  unique_ptr<int> ap(new int(1));
  //unique_ptr_example_8_a(ap);     // compilation error

  unique_ptr_example_8_a(move(ap)); // OK, but after call, ap is nullptr

  unique_ptr<int> bp(new int(1));
  unique_ptr_example_8_b(bp); // OK
  *bp = 0;
}


void unique_ptr_examples()
{
  //unique_ptr_example_1();
  //unique_ptr_example_2();
  //unique_ptr_example_3();
  //unique_ptr_example_4();
  //unique_ptr_example_5();
  //unique_ptr_example_6();
  //unique_ptr_example_7();
  unique_ptr_example_8();
}

int main()
{
  unique_ptr_examples();
  return 0;
}













