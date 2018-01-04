#ifndef EXAMPLE_3_HPP
#define EXAMPLE_3_HPP

#include <memory>

namespace resource_ns_c
{
  struct resource
  {
    resource(int aValue = 0);
    int  value();

    resource &operator+=(int);
    resource &operator-=(int);

  private:
    int *mpValue{nullptr};
  };
}

#endif // EXAMPLE_3_HPP
