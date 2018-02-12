#include <iostream>
#include <optional>
#include <string>
#include <map>

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

int main()
{
  optional_example_a::test();
  optional_example_b::test();
  optional_example_c::test();

  return 0;
}



















