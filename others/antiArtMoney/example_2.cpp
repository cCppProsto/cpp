#include "example_2.hpp"

namespace resource_ns_b
{

resource::resource(int aValue)
{
  mValueArray[0] = aValue;
}
//------------------------------------------------------------------------------
int resource::value()
{
  return mValueArray[0] + mValueArray[1];
}
//------------------------------------------------------------------------------
resource &resource::operator+=(int aValue)
{
  mValueArray[0] += mValueArray[1];
  mValueArray[1] = aValue;
  return *this;
}
//------------------------------------------------------------------------------
resource &resource::operator-=(int aValue)
{
  mValueArray[0] += mValueArray[1];
  mValueArray[1] = -aValue;
  return *this;
}


}
