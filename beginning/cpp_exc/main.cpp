#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

vector<int> v;

namespace example_a
{
  void test()
  {
    v[0] = 0;
  }
}

namespace example_b
{
  void test()
  {
    try
    {
      //v.resize(4);
      v.at(0) = 10;
    }
    catch(out_of_range &ex)
    {
      cout << ex.what() << endl;
    }
  }

  void test_a()
  try
  {
    //v.resize(4);
    v.at(0) = 10;
  }
  catch(std::out_of_range &ex)
  {
    cout << ex.what() << endl;
  }
}

namespace example_c
{
  enum class eErrorCode
  {
    NoError
   ,Open
   ,Close
   ,Write
   ,Read
  };

  bool open(bool aVal)  { return aVal; }
  void close()          {  }
  bool write(bool aVal) { return aVal; }
  bool read(bool aVal)  { return aVal; }

  eErrorCode getData()
  {
    if(!open(true))
    {
      close();
      return eErrorCode::Open;
    }

    // ...

    if(!write(true))
    {
      close();
      return eErrorCode::Write;
    }

    // ...

    if(!read(true))
    {
      close();
      return eErrorCode::Read;
    }

    // ...

    return eErrorCode::NoError;
  }

  void test()
  {
    eErrorCode res;
    res = getData();

    if(res != eErrorCode::NoError)
    {
      // log error
    }
  }
}

namespace example_d
{
  enum class eErrorCode
  {
    Open
   ,Close
   ,Write
   ,Read
  };

  void open(bool aVal)  { if(!aVal) throw eErrorCode::Open;  }
  void close()          {  }
  void write(bool aVal) { if(!aVal) throw eErrorCode::Write; }
  void read(bool aVal)  { if(!aVal) throw eErrorCode::Read;  }

  bool getData()
  try
  {
    open(true);

    // ...

    write(true);

    // ...

    read(false);

    // ...

    close();

    return true;
  }
  catch(eErrorCode &ex)
  {
    close();
    switch(ex)
    {
      case eErrorCode::Open:
      {
        cout << "open error" << endl;
        break;
      }
      case eErrorCode::Close:
      {
        cout << "close error" << endl;
        break;
      }
      case eErrorCode::Write:
      {
        cout << "write error" << endl;
        break;
      }
      case eErrorCode::Read:
      {
        cout << "read error" << endl;
        break;
      }
    }
    return false;
  }
  catch(...)
  {
    cout << "unknown exception" << endl;
    return false;
  }

  void test()
  {
    bool get;
    get = getData();

    if(!get)
    {
      // log error
    }
  }
}

namespace example_e
{
  enum class eDoNotForget
  {
    Dealloc
  };

  void test()
  {
    char *pchar = new char[100];

    // ...
    if(1)
    {
      delete [] pchar;
      return;
    }

    // ...

    if(1)
    {
      delete [] pchar;
      return;
    }

    // ...

    if(1)
    {
      delete [] pchar;
      return;
    }

    delete [] pchar;
  }

  void test_a()
  {
    char *pchar = new char[100];
    try
    {
      if(1)
        throw eDoNotForget::Dealloc;

      // ...

      if(1)
        throw eDoNotForget::Dealloc;

      // ...
      if(1)
        throw eDoNotForget::Dealloc;

      // ...
      throw eDoNotForget::Dealloc;
    }
    catch(eDoNotForget &ex)
    {
      if(ex == eDoNotForget::Dealloc)
        delete [] pchar;
    }
  }
}

namespace example_f
{
  void foo_a()
  {
    cout << "enter foo_a" << endl;
    throw 1;
    cout << "leave foo_a" << endl;
  }

  void foo_b()
  {
    cout << "enter foo_b" << endl;
    foo_a();
    cout << "leave foo_b" << endl;
  }

  void foo_c()
  {
    cout << "enter foo_c" << endl;
    foo_b();
    cout << "leave foo_c" << endl;
  }

  void foo_d()
  {
    cout << "enter foo_d" << endl;
    foo_c();
    cout << "leave foo_d" << endl;
  }

  void test()
  {
    try
    {
      foo_d();
    }
    catch(...)
    {
      cout << "catched!" << endl;
    }
  }
}

int main()
{
  try
  {
    throw 1u;
  }
  catch(int &ex)
  {
    cout << "int: " << ex << endl;
  }
  catch(char &ex)
  {
    cout << "char: " << ex << endl;
  }
  catch(const char *ex)
  {
    cout << "str: " << ex << endl;
  }
  catch(...)
  {
    cout << "unknown" << endl;
  }

  //example_a::test();
  //example_b::test();
  //example_b::test_a();
  //example_c::test();
//  example_d::test();
//  example_e::test();
//  example_e::test_a();
  example_f::test();

  return 0;
}
