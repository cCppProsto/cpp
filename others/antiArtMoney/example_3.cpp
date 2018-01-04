#include <iostream>
#include "example_3.hpp"

namespace resource_ns_c
{

resource::resource(int aValue)
  :mpValue(new int(aValue))
{
}
//------------------------------------------------------------------------------
int resource::value()
{
  return *mpValue;
}
//------------------------------------------------------------------------------
resource &resource::operator+=(int aValue)
{
  int val = *mpValue + aValue;

  int *tmp = new int(val);
  delete mpValue;

  mpValue = tmp;

  return *this;
}
//------------------------------------------------------------------------------
resource &resource::operator-=(int aValue)
{
  int val = *mpValue - aValue;

  int *tmp = new int(val);
  delete mpValue;

  mpValue = tmp;

  return *this;
}

}
