#ifndef EXAMPLE_2_HPP
#define EXAMPLE_2_HPP


namespace resource_ns_b
{
  struct resource
  {
    resource(int aValue = 0);
    int  value();

    resource &operator+=(int);
    resource &operator-=(int);

  private:
    int  mValueArray[2] = {0};
  };
}

#endif // EXAMPLE_2_HPP
