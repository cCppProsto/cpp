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

//---------------------- SHARED PTR --------------------------------------------
void shared_ptr_example_1()
{
  std::shared_ptr<int> sp_a(new int(1));
  {
    std::shared_ptr<int> sp_b;
    sp_b = sp_a;
  }
}
//------------------------------------------------------------------------------
void shared_ptr_example_2()
{
  struct cls
  {
    cls()
    {
      cout << "cls()" << endl;
    }
    ~cls()
    {
      cout << "~cls()" << endl;
    }
  };

  std::shared_ptr<cls> a(new cls);
  std::shared_ptr<cls> b(new cls);
  std::shared_ptr<cls> c(b);

  std::cout << a.get() << ":" << a.use_count() << std::endl;
  std::cout << b.get() << ":" << b.use_count() << std::endl;
  std::cout << c.get() << ":" << c.use_count() << std::endl;

  a = b;
  b = c;

  std::cout << a.get() << ":" << a.use_count() << std::endl;
  std::cout << b.get() << ":" << b.use_count() << std::endl;
  std::cout << c.get() << ":" << c.use_count() << std::endl;
}
//------------------------------------------------------------------------------
void shared_ptr_add_3_a(std::shared_ptr<int> aPtr)
{
  std::cout << "shared_ptr_add_3_a: owners = " << aPtr.use_count() << std::endl;
}
//------------------------------------------------------------------------------
void shared_ptr_add_3_b(const std::shared_ptr<int> &aPtr)
{
  std::cout << "shared_ptr_add_3_b: owners = " << aPtr.use_count() << std::endl;
}
//------------------------------------------------------------------------------
void shared_ptr_example_3()
{
  auto sp = std::make_shared<int>(1);
  shared_ptr_add_3_a(sp);
  shared_ptr_add_3_b(sp);

  std::cout << "shared_ptr_example_3: owners = " << sp.use_count() << std::endl;
}
//------------------------------------------------------------------------------
void shared_ptr_example_4()
{
  {
    // not crash when will an attempt to release of memory
    // BUT it is problem, if allocate for array [], release for array []
    auto spa = std::shared_ptr<int>(new int [3]);
  }

  {
    auto spa = std::shared_ptr<int>(new int [3], default_delete<int[]>());

    spa.get()[0] = 1;
    spa.get()[1] = 2;
    spa.get()[2] = 3;

    std::cout << spa.get()[0]
              << ","
              << spa.get()[1]
              << ","
              << spa.get()[2]
              << std::endl;
  }

  {
    auto spa = std::shared_ptr<int>(new int [3], []( int *p ) { delete[] p; });
  }

  {
    struct IntArrayDeleter
    {
        void operator()(int *aP)
        {
          std::cout <<
                    "deleted is OK"
                    << std::endl;
          delete [] aP;
        }
    };

    auto spa = std::shared_ptr<int>(new int [3], IntArrayDeleter());
  }
}
//------------------------------------------------------------------------------
void shared_ptr_example_5()
{
  struct cls
  {
    cls()  { cout << "cls()" << endl;}
    ~cls() { cout << "~cls()" << endl;}

    static std::shared_ptr<cls> make_shared_array(unsigned aSize)
    {
      return std::shared_ptr<cls>(new cls[aSize], default_delete<cls[]>());
    }
  };

  {
    auto spa = cls::make_shared_array(3);
  }
  {
    auto spa = std::shared_ptr<cls>(new cls [5]); // crash when will an attempt to release of memory
  }
}
//------------------------------------------------------------------------------
void shared_ptr_examples()
{
  //shared_ptr_example_1();
  //shared_ptr_example_2();
  //shared_ptr_example_3();
  //shared_ptr_example_4();
  shared_ptr_example_5();
}
//---------------------- WEAK PTR ----------------------------------------------
void weak_ptr_example_1()
{
  struct sUnit
  {
    sUnit(string name) { cout << "sUnit()" << endl;  }
    ~sUnit()           { cout << "~sUnit()" << endl; }
    shared_ptr<sUnit> target;
  };

  {
    shared_ptr<sUnit> archer  = std::make_shared<sUnit>("archer");  // a - 1 : t - 0
    shared_ptr<sUnit> pikeman = std::make_shared<sUnit>("pikeman"); // p - 1 : t - 0

    archer->target = pikeman; // a - 1 : t - 2
                              // p - 2 : t - 0

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pikeman.use_count() << " : " << pikeman->target.use_count() << endl << endl;
  }
  cout << endl << endl;
}
//------------------------------------------------------------------------------
void weak_ptr_example_2()
{
  struct sUnit
  {
    sUnit(string name) { cout << "sUnit()" << endl;  }
    ~sUnit()           { cout << "~sUnit()" << endl; }
    shared_ptr<sUnit> target;
  };

  {
    shared_ptr<sUnit> archer   = std::make_shared<sUnit>("archer");   // a - 1 : t - 0
    shared_ptr<sUnit> pickeman = std::make_shared<sUnit>("pikeman");  // p - 1 : t - 0

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pickeman.use_count() << " : " << pickeman->target.use_count() << endl << endl;

    archer->target = pickeman;  // a - 1 : t - 2
                                // p - 2 : t - 0

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pickeman.use_count() << " : " << pickeman->target.use_count() << endl << endl;

    pickeman->target = archer;  // p - 2 : t - 2
                                // a - 2 : t - 2

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pickeman.use_count() << " : " << pickeman->target.use_count() << endl << endl;
  }
  cout << endl << endl;
}
//------------------------------------------------------------------------------
void weak_ptr_example_3()
{
  struct sUnit
  {
    sUnit(string name) { cout << "sUnit()" << endl;  }
    ~sUnit()           { cout << "~sUnit()" << endl; }
    weak_ptr<sUnit> target;
  };

  {
    shared_ptr<sUnit> archer   = std::make_shared<sUnit>("archer");   // a - 1 : t - 0
    shared_ptr<sUnit> pickeman = std::make_shared<sUnit>("pikeman");  // p - 1 : t - 0

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pickeman.use_count() << " : " << pickeman->target.use_count() << endl << endl;

    archer->target = pickeman;  // a - 1 : t - 2
                                // p - 2 : t - 0

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pickeman.use_count() << " : " << pickeman->target.use_count() << endl << endl;

    pickeman->target = archer;  // p - 2 : t - 2
                                // a - 2 : t - 2

    cout << archer.use_count() << " : " << archer->target.use_count() << endl;
    cout << pickeman.use_count() << " : " << pickeman->target.use_count() << endl << endl;
  }
  cout << endl << endl;
}
//------------------------------------------------------------------------------
void weak_ptr_example_4()
{
  struct sUnit
  {
    sUnit(string name) { cout << "sUnit()" << endl;  }
    ~sUnit()           { cout << "~sUnit()" << endl; }

    weak_ptr<sUnit> target;
  };

  {
    shared_ptr<sUnit> archer   = std::make_shared<sUnit>("archer");   // a - 1 : t - 0

    // ...

    shared_ptr<sUnit> &some = archer;

    // ...

    archer->target = some;
  }
  cout << endl << endl;
}
//------------------------------------------------------------------------------
void weak_ptr_example_5()
{
  struct sUnit
  {
    sUnit(string name) { cout << "sUnit()" << endl;  }
    ~sUnit()           { cout << "~sUnit()" << endl; }

    void attack()
    {
      // ...

      if((target.lock())->mHealth < 0)
        target.reset();
    }

    int             mHealth{100};
    weak_ptr<sUnit> target;
  };

  {
    shared_ptr<sUnit> archer   = std::make_shared<sUnit>("archer");   // a - 1 : t - 0
    shared_ptr<sUnit> pickeman = std::make_shared<sUnit>("pikeman");  // p - 1 : t - 0

    archer->target = pickeman;

    // ...
    pickeman.reset();

    // ...

    archer->attack();
  }

  cout << endl << endl;
}
//------------------------------------------------------------------------------
void weak_ptr_example_6()
{
  struct sUnit
  {
    sUnit(string name) { cout << "sUnit()" << endl;  }
    ~sUnit()           { cout << "~sUnit()" << endl; }

    void attack()
    {
      // ...

      if(!target.expired())
      {
        if((target.lock())->mHealth < 0)
          target.reset();
      }
    }

    int             mHealth{100};
    weak_ptr<sUnit> target;
  };

  {
    shared_ptr<sUnit> archer   = std::make_shared<sUnit>("archer");   // a - 1 : t - 0
    shared_ptr<sUnit> pickeman = std::make_shared<sUnit>("pikeman");  // p - 1 : t - 0

    archer->target = pickeman;

    // ...
    pickeman.reset();

    // ...

    archer->attack();
  }

  cout << endl << endl;
}
//------------------------------------------------------------------------------
void weak_ptr_examples()
{
  //weak_ptr_example_1();
  //weak_ptr_example_2();
  //weak_ptr_example_3();
  //weak_ptr_example_4();
  //weak_ptr_example_5();
  weak_ptr_example_6();
}

int main()
{
  //unique_ptr_examples();
  //shared_ptr_examples();
  weak_ptr_examples();
  return 0;
}

