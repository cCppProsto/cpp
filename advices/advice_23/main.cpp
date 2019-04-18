#include <iostream>
#include <cmath>
#include <string>
#include <cstring>


using namespace std;

class RCString
{
public:
  //----------------------------------------------------------------------------
  RCString(const char *initValue = "")
    :mp_value{new StringValue{initValue}}
  {
  }
  //----------------------------------------------------------------------------
  RCString(const RCString &rhs)
  {
    if(rhs.mp_value->shareable)
    {
      mp_value = rhs.mp_value;
      ++mp_value->refCount;
    }
    else
    {
      mp_value = new StringValue{rhs.mp_value->pdata};
    }
  }
  //----------------------------------------------------------------------------
  RCString &operator=(const RCString &rhs)
  {
    if(mp_value == rhs.mp_value)
      return *this;

    if(rhs.mp_value->shareable)
    {
      if(mp_value->refCount > 0)
        mp_value->refCount--;

      if(mp_value->refCount == 0)
      {
        delete mp_value;
        mp_value = nullptr;
      }

      mp_value = rhs.mp_value;
      mp_value->refCount++;
    }
    else
    {
      delete mp_value;
      mp_value = new StringValue{mp_value->pdata};
    }
    return *this;
  }
  //----------------------------------------------------------------------------
  const char &operator[](int index)const
  {
    return mp_value->pdata[index];
  }
  //----------------------------------------------------------------------------
  char &operator[](int index)
  {
    if(mp_value->refCount > 1)
    {
      mp_value->refCount--;
      mp_value = new StringValue{mp_value->pdata};
    }
    mp_value->shareable = false;
    return mp_value->pdata[index];
  }
  //----------------------------------------------------------------------------
  ~RCString()
  {
    if(mp_value != nullptr)
    {
      if(mp_value->refCount > 0)
        mp_value->refCount--;

      if(mp_value->refCount == 0)
      {
        delete mp_value;
        mp_value = nullptr;
      }
    }
  }

private:
  struct StringValue
  {
    //--------------------------------------------------------------------------
    StringValue(const char *initValue)
      :refCount{1}
    {
      pdata = new char[std::strlen(initValue) + 1];
      std::strcpy(pdata, initValue);
    }
    //--------------------------------------------------------------------------
    ~StringValue()
    {
      delete [] pdata;
    }

    int refCount{0};
    bool shareable{true};
    char *pdata{nullptr};
  };

  StringValue *mp_value{nullptr};
};

int main()
{
  RCString str1("Hello!");
  RCString str2(str1);
  RCString str3;
  str3 = str2;

  char *p = &str3[1];

  RCString str4 = str3;
  *p = '!';
  str3[1] = '1';
  str2[0] = '?';

  return 0;
}
