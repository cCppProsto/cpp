#include "example_1.hpp"

namespace resource_ns_a
{

resource::resource(int aValue)
  :mValue{aValue}
{
}
//------------------------------------------------------------------------------
int resource::value()
{
  return mValue;
}
//------------------------------------------------------------------------------
resource &resource::operator+=(int aValue)
{
  mValue += aValue;
  return *this;
}
//------------------------------------------------------------------------------
resource &resource::operator-=(int aValue)
{
  mValue -= aValue;
  return *this;
}

}
