#include "example_4.hpp"

namespace resource_ns_d
{
resource::resource(int aValue)
  :mValue(aValue ^ mKey)
{
}
//------------------------------------------------------------------------------
int resource::value()
{
  return mValue ^ mKey;
}
//------------------------------------------------------------------------------
resource &resource::operator+=(int aValue)
{
  int val = mValue ^ mKey;
  val += aValue;
  mValue = val ^ mKey;
  return *this;
}
//------------------------------------------------------------------------------
resource &resource::operator-=(int aValue)
{
  int val = mValue ^ mKey;
  val -= aValue;
  mValue = val ^ mKey;
  return *this;
}

}
