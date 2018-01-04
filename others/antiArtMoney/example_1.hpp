#ifndef EXMPLE_1_HPP
#define EXMPLE_1_HPP

namespace resource_ns_a
{
  struct resource
  {
    resource(int aValue = 0);
    int  value();

    resource &operator+=(int);
    resource &operator-=(int);

  private:
    int mValue;
  };
}

#endif // EXMPLE_1_HPP
