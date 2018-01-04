#ifndef EXAMPLE_4_HPP
#define EXAMPLE_4_HPP

#include <memory>

namespace resource_ns_d
{
  struct resource
  {
    resource(int aValue = 0);
    int  value();

    resource &operator+=(int);
    resource &operator-=(int);

  private:
    int mKey{std::rand()%100000};
    int mValue{0};
  };
}

#endif // EXAMPLE_4_HPP
