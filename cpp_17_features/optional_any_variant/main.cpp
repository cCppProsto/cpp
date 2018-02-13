#include <iostream>
#include <string>

#include <optional>
#include <any>
#include <variant>

using namespace std;

namespace optional_example_a
{
  struct ContactInfo
  {
    ContactInfo()
    {

      // reading database
      // ...
      mHomePhone = "+0123456789";
    }
    string homePhone()
    {
      return mHomePhone.value_or("not present");
    }

    string workPhone()
    {
      return mWorkPhone.value_or("not present");
    }

    string mobilePhone()
    {
      make_optional<int>(1);
      return mMobilePhone.value_or("not present");
    }

  private:
    optional<std::string> mHomePhone{nullopt};
    optional<std::string> mWorkPhone;
    optional<std::string> mMobilePhone;
  };

  void test()
  {
    ContactInfo info;
    cout << info.homePhone() << endl;
    cout << info.workPhone() << endl;
    cout << info.mobilePhone() << endl;
  }
}

namespace optional_example_b
{
  optional<int> strToInt(string aStr)
  {
    if(aStr.empty()) return {};

    // parse string, if Ok return value
    if(true)
      return 1;
    return {};
  }

  void test()
  {
    optional<int> i;
    i = strToInt("");
    if(i)
      cout << "OK: " << *i << endl;

    i = strToInt("123");
    if(i)
      cout << "OK: " << *i << endl;
  }
}

namespace optional_example_c
{
  void test()
  {
    optional<int> i;
    if(i)
      cout << "OK: " << *i << endl;

    i = 90;
    if(i)
      cout << "OK: " << *i << endl;
  }
}

namespace optional_example_d
{
  struct sTest
  {
    sTest()
    {
      cout << "sTest()" << endl;
    }

    sTest(const sTest&)
    {
      cout << "const sTest&" << endl;
    }

    ~sTest()
    {
      cout << "~sTest()" << endl;
    }

  };

  void test()
  {
    sTest t;
    optional<sTest> s1;
    s1.emplace(t);

    optional<sTest> s2(s1);
    s1.reset();
    s2.reset();
  }
}

namespace any_example_a
{
  void test()
  {
    any a;

    a = 100;
    cout << any_cast<int>(a) << endl;

    a = std::string{"Hello"};
    cout << any_cast<std::string>(a) << endl;

    a = 1.1f;
    cout << any_cast<float>(a) << endl;
  }
}

namespace variant_example_a
{
  void test()
  {
    variant<int, char, string> v;

    v = 90;
    cout << get<int>(v) << " " << v.index() << endl;

    v = "Hello!";
    cout << get<string>(v) << " " << v.index() << endl;
  }
}

namespace variant_example_b
{
  struct sData
  {
    int a;
    int b;
    int c;
  };

  void test()
  {
    variant<sData> v;

    sData data_a{1,2,3};
    sData data_b;

    v = data_a;

    data_b = get<sData>(v);
  }
}

namespace variant_example_c
{
  void test()
  {
    variant<int, char> v;
    v = 'a';

    if(get_if<char>(&v) != nullptr)
    {
      cout << get<char>(v) << endl;
    }

    if(get_if<int>(&v) != nullptr)
    {
      cout << get<char>(v) << endl;
    }
  }
}

int main()
{
  optional_example_a::test();
  optional_example_b::test();
  optional_example_c::test();
  optional_example_d::test();

  any_example_a::test();

  variant_example_a::test();
  variant_example_b::test();
  variant_example_c::test();

  return 0;
}



















