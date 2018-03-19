#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <cstring>
using namespace std;

namespace example_a
{
  struct data
  {
    data()                        { cout << "data()" << endl; }
    data(const data&)             { cout << "data(const data&)" << endl; }
    data &operator=(const data& ) { cout << "operator =(const data&)" << endl; return *this;}
    data(data&&)                  { cout << "data(data&&)" << endl; }
    data &operator=(data&& )      { cout << "operator =(const data&&)" << endl; return *this;}
    ~data()                       { cout << "~data()" << endl; }
  };

  template <class T>
  void swap_a(T &a, T &b)
  {
    cout << endl << "swap is start" << endl;
    T tmp(a);
    a = b;
    b = tmp;
    cout << "swap is end" << endl << endl;
  }

  void test()
  {
    vector<data> v1{data()};
    vector<data> v2{data()};
    /*
      data()
      data(const data&)
      ~data()
      data()
      data(const data&)
      ~data()
    */

    swap_a(v1, v2);
    /*
      swap is start
      data(const data&)
      operator =(const data&)
      operator =(const data&)
      swap is end
    */

    /*
      ~data()
      ~data()
      ~data()
    */
  }
}

namespace example_b
{
  struct data
  {
    data()                        { cout << "data()" << endl; }
    data(const data&)             { cout << "data(const data&)" << endl; }
    data &operator=(const data& ) { cout << "operator =(const data&)" << endl; return *this;}
    data(data&&)                  { cout << "data(data&&)" << endl; }
    data &operator=(data&& )      { cout << "operator =(const data&&)" << endl; return *this;}
    ~data()                       { cout << "~data()" << endl; }
  };

  template <class T>
  void swap_b(T &a, T &b)
  {
    cout << endl << "swap is start" << endl;
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
    cout << "swap is end" << endl << endl;
  }

  void test()
  {
    vector<data> v1{data()};
    vector<data> v2{data()};
    /*
      data()
      data(const data&)
      ~data()
      data()
      data(const data&)
      ~data()
    */

    swap_b(v1, v2);
    /*
      swap is start
      swap is end
    */

    /*
      ~data()
      ~data()
      ~data()
    */
  }
}

namespace example_c
{
  void test()
  {
    vector<int> a{1,2,3,4,5};
    vector<int> b;

    cout << "a size = " << a.size() << endl;
    cout << "b size = " << b.size() << endl;

    b = move(a);

    cout << "a size = " << a.size() << endl;
    cout << "b size = " << b.size() << endl;
  }
}

namespace example_d
{
  void foo(int&& obj)
  {
    int copy_obj(obj);            // copy constructor
    int move_obj(std::move(obj)); // move constructor
  }

  void test()
  {
    foo(int()); // OK
    int obj{4};
    //foo(obj);   // error, need rValue, pass lValue
    foo(1);     // OK, need rValue, pass rValue
  }
}

namespace example_e
{
  struct data
  {
    data()
    {
      pdata = new int[size];
    }

    data(data &&obj)
    {
      pdata     = obj.pdata;
      size      = obj.size;

      obj.pdata = nullptr;
      obj.size = 0;
    }

    int *pdata{nullptr};
    int size{100};
  };

  void test()
  {
    data a;
    //data b(a); // error
    data b(move(a));
    cout << endl;
  }
}


const int object_count = 30000;

namespace example_f
{
  struct str
  {
    str(int aSize)
    {
      mstr.resize(aSize);
    }

    str(const str& obj)
      :mstr(obj.mstr)
    {
    }

    str& operator=(const str& obj)
    {
      mstr = obj.mstr;
      return *this;
    }

    ~str()
    {
    }

    string mstr;
  };

  struct data
  {
    data(string)
    {
      for(int i = 0; i < object_count; ++i)
        mData.push_back(str(i));
    }

    data(const data &obj)
      :mData(obj.mData)
    {
    }

    data& operator=(const data &obj)
    {
      mData = obj.mData;
      return *this;
    }

    ~data()
    {
    }

    vector<str> mData;
  };

  void test()
  {
    vector<data> v;
    v.reserve(3);

    auto start = chrono::steady_clock::now();

    v.push_back(data("www.11.com"));
    v.push_back(data("www.22.ru"));
    v.push_back(data("www.33.ru"));
    v.push_back(data("www.44.com"));
    v.push_back(data("www.55.ru"));
    v.push_back(data("www.66.ru"));

    auto end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
  }
}

namespace example_g
{
  struct str
  {
    str(int aSize)
    {
      mstr.resize(aSize);
    }

    str(str&& obj)
      :mstr(move(obj.mstr))
    {
    }

    str& operator=(str&& obj)
    {
      mstr = move(obj.mstr);
      return *this;
    }

    str(const str&) = delete;
    str &operator=(const str&) = delete;

    ~str()
    {
    }

    string mstr;
  };

  struct data
  {
    data(string)
    {
      for(int i = 0; i < object_count; ++i)
        mData.push_back(str(i));
    }

    data(data &&obj)
      :mData(move(obj.mData))
    {
    }

    data& operator=(data &&obj)
    {
      mData = move(obj.mData);
      return *this;
    }

    data(const data&) = delete;
    data &operator=(const data&) = delete;

    ~data()
    {
    }

    vector<str> mData;
  };

  void test()
  {
    vector<data> v;
    v.reserve(3);

    auto start = chrono::steady_clock::now();

    v.push_back(data("www.11.com"));
    v.push_back(data("www.22.ru"));
    v.push_back(data("www.33.ru"));
    v.push_back(data("www.44.com"));
    v.push_back(data("www.55.ru"));
    v.push_back(data("www.66.ru"));

    auto end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
  }
}

struct data
{
  int m{2};
};

vector<int> test(int a)
{
  vector<int> v;

  //

  return v;
}

int main()
{
  data d1;
  data d2(d1);
  data d3 = d2;
  data d4;
  d4 = d3;
  data d5(move(d1));
  data d6 = move(d2);
  data d7;
  d7 = move(d3);

//  example_a::test();
//  cout << "-----------------------------" << endl;
//  example_b::test();
//  example_c::test();
//  example_d::test();
//  example_e::test();

  example_f::test();
  example_g::test();

  return 0;
}


