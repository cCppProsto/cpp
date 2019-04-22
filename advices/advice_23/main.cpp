#include <iostream>
#include <cmath>
#include <string>
#include <cstring>


using namespace std;


namespace example_1
{
  class String
  {
    public:
      String(const char *initValue = "")
      {
        data = new char[strlen(initValue) + 1];
        strcpy(data, initValue);
      }

      String(const String &rhs)
      {
        data = new char [strlen(rhs.data) + 1];
      }

      String &operator=(const String &rhs)
      {
        if(this == &rhs)
          return *this;

        data = new char[strlen(rhs.data) + 1];
        strcpy(data, rhs.data);
        return *this;
      }

      ~String()
      {
        delete [] data;
      }

    private:
      char *data{nullptr};
  };
  void test()
  {

  }
}

namespace example_2
{
  class String
  {
    struct StringValue
    {
      StringValue(const char *initValue)
        :refCount{1}
      {
        data = new char[strlen(initValue) + 1];
        strcpy(data, initValue);
      }

      ~StringValue()
      {
        delete [] data;
      }

      int refCount{0};
      char *data{nullptr};
    };

    public:
      String(const char *initValue = "")
        :value{new StringValue(initValue)}
      {
      }

      String(const String &rhs)
        :value{rhs.value}
      {
        ++value->refCount;
      }

      String & operator=(const String &rhs)
      {
        if(value == rhs.value)
          return *this;

        if(--value->refCount == 0)
          delete value;

        value = rhs.value;
        ++value->refCount;
        return *this;
      }

      ~String()
      {
        if(--value->refCount == 0)
          delete value;
      }

    private:
      StringValue *value;
  };

  void test()
  {

  }
}

namespace example_3
{
  class String
  {
    struct StringValue
    {
      StringValue(const char *initValue)
        :refCount{1}
      {
        data = new char[strlen(initValue) + 1];
        strcpy(data, initValue);
      }

      ~StringValue()
      {
        delete [] data;
      }

      int refCount{0};
      char *data{nullptr};
    };

    public:
      String(const char *initValue = "")
        :value{new StringValue(initValue)}
      {
      }

      String(const String &rhs)
        :value{rhs.value}
      {
        ++value->refCount;
      }

      String & operator=(const String &rhs)
      {
        if(value == rhs.value)
          return *this;

        if(--value->refCount == 0)
          delete value;

        value = rhs.value;
        ++value->refCount;
        return *this;
      }

      char &operator[](int index)
      {
        if(value->refCount > 1)
        {
          --value->refCount;
          value = new StringValue(value->data);
        }
        return value->data[index];
      }

      const char &operator[](int index)const
      {
        return value->data[index];
      }

      ~String()
      {
        if(--value->refCount == 0)
          delete value;
      }

    private:
      StringValue *value;
  };

  void test()
  {
    String str1("Hello!");
    String str2(str1);
    String str3;
    String str4;
    String str5;
    str5 = str4 = str3 = str2;

    str4[0] = '!';
    std::cout << str5[0] << std::endl;
  }
}

namespace example_4
{
  class String
  {
    struct StringValue
    {
      StringValue(const char *initValue)
        :refCount{1}
      {
        data = new char[strlen(initValue) + 1];
        strcpy(data, initValue);
      }

      ~StringValue()
      {
        delete [] data;
      }

      int refCount{0};
      bool shareable{true};
      char *data{nullptr};
    };

    public:
      String(const char *initValue = "")
        :value{new StringValue(initValue)}
      {
      }

      String(const String &rhs)
      {
        if(rhs.value->shareable)
        {
          value = rhs.value;
          ++value->refCount;
        }
        else
        {
          value = new StringValue{rhs.value->data};
        }
      }

      String & operator=(const String &rhs)
      {
        if(value == rhs.value)
          return *this;

        if(rhs.value->shareable)
        {
          if(--value->refCount == 0)
          {
            delete value;
            value = nullptr;
          }

          value = rhs.value;
          value->refCount++;
        }
        else
        {
          delete value;
          value = new StringValue(value->data);
        }
        return *this;
      }

      char &operator[](int index)
      {
        if(value->refCount > 1)
        {
          value->refCount--;
          value = new StringValue{value->data};
        }
        value->shareable = false;
        return value->data[index];
      }

      const char &operator[](int index)const
      {
        return value->data[index];
      }

      ~String()
      {
        if(--value->refCount == 0)
          delete value;
      }

    private:
      StringValue *value;
  };

  void test()
  {
    String str1("Hello!");

    char *p = &str1[0];

    String str2 = str1;

    *p = '!';
    std::cout << *p << std::endl;
  }
}


int main()
{
  example_1::test();
  example_2::test();
  example_3::test();
  example_4::test();
  return 0;
}
