#include <iostream>
using namespace std;

namespace  example_a
{
  struct base_a
  {
    virtual void f() = 0;
    int mA{0x0a0b0c0d};
  };

  struct base_b
  {
    virtual void f() = 0;
    int mA{0x0e0f0fff};
  };

  struct child_a : base_a
  {
    void f()
    {
      cout << "child_a" << endl;
    }
  };

  struct child_b : base_b
  {
    void f()
    {
      cout << "child_b" << endl;
    }
  };

  void example()
  {
    base_a *pa = new child_a;
    base_b *pb = new child_b;

    pa->f();
    pb->f();
    cout << endl;

    /*  Example addres pa = 0xFFFF00
     64x
      FFFF00 - vptr
        [0x00000000000000FF] address of table
      FFFF08 - mA{};
      ...
      0x00000000000000FF
        [0x????????????????] - f_a()
        [0x????????????????] - f_b()
        [...]
    */

    void *pv_a = (void*)pa;       // write address of 'pa' in 'pv_a'
    void *pv_b = *(void**)pa;     // write address vptr of 'pa' in 'pv_b'

    void *vtbl_a = *(void**)pa;   // save address of table virtual functions of 'pa' object
    void *vtbl_b = *(void**)pb;   // save address of table virtual functions of 'pb' object

    *(void**)pa = vtbl_b;
    *(void**)pb = vtbl_a;

    pa->f();
    pb->f();

    delete pa;
    delete pb;
  }
}

namespace  example_b
{
  typedef void (*func_ptr)();
  struct base_a
  {
    virtual void f_a() = 0;
    virtual void f_b() = 0;
  };

  struct child_a : base_a
  {
    void f_a() override
    {
      cout << "f_a" << endl;
    }

    void f_b() override
    {
      cout << "f_b" << endl;
    }
  };

  void example()
  {
    typedef void (*func_ptr)();
    func_ptr pf_a;
    func_ptr pf_b;

    base_a *pa = new child_a;

    void *vtbl = *(void**)pa;

    void *vpf_a = ((void**)vtbl)[0]; // get address of function 'f_a()' of object 'pa'
    void *vpf_b = ((void**)vtbl)[1]; // get address of function 'f_b()' of object 'pa'

    pf_a = (func_ptr)vpf_a;
    pf_b = (func_ptr)vpf_b;

    pf_a();
    pf_b();

    delete pa;
  }
}

namespace  example_c
{
  typedef void (*func_ptr)();
  struct base_a
  {
    virtual void f_a() = 0;
    virtual void f_b() = 0;
  };

  struct child_a : base_a
  {
    void f_a() override
    {
      cout << "f_a" << endl;
    }

    void f_b() override
    {
      cout << "f_b" << endl;
    }
  };

  void example()
  {
    typedef void (*func_ptr)();
    func_ptr pf_a;
    func_ptr pf_b;

    base_a *pa = new child_a;

    void *vtbl = *(void**)pa;

    void *vpf_a = ((void**)vtbl)[0]; // get address of function 'f_a()' of object 'pa'
    void *vpf_b = ((void**)vtbl)[1]; // get address of function 'f_b()' of object 'pa'

    pf_a = (func_ptr)vpf_a;
    pf_b = (func_ptr)vpf_b;

    struct t
    {
      func_ptr f_a;
      func_ptr f_b;
    };

    t vt;
    vt.f_a = pf_b;
    vt.f_b = pf_a;

    // *(void**)vtbl = 0; // !! crash !!

    cout << *(void**)pa << endl;
    *(void**)pa = (void**)(&vt);
    cout << *(void**)pa << endl;

    pa->f_a();
    pa->f_b();

    delete pa;
  }
}

namespace  example_d
{
  typedef void (*func_ptr)();
  struct base_a
  {
    virtual void f_a() = 0;
    virtual void f_b() = 0;
    int mA{0x0a0b0c0d};
  };

  struct child_a : base_a
  {
    void f_a() override
    {
      cout << "f_a" << endl;
    }

    void f_b() override
    {
      cout << "f_b" << endl;
    }
  };

  void example()
  {
    base_a *pa = new child_a;

    auto observer_pa_f_a = []()
    {
      cout << "do dirty deeds AA" << endl;
    };

    auto observer_pa_f_b = []()
    {
      cout << "do dirty deeds BB" << endl;
    };

    struct t
    {
      func_ptr f_a;
      func_ptr f_b;
    };

    t vt;
    vt.f_a = observer_pa_f_a;
    vt.f_b = observer_pa_f_b;

    cout << *(void**)pa << endl;
    *(void**)pa = (void**)(&vt);
    cout << *(void**)pa << endl;

    pa->f_a();
    pa->f_b();

    delete pa;
  }
}

int main()
{
  //example_a::example();
  //example_b::example();
  //example_c::example();
  example_d::example();

  return 0;
}
















