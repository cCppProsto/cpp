#include <iostream>
using namespace std;


template<class T, std::size_t aSize>
struct array
{
  T &operator[](std::size_t aIndex)
  {
    return mData[aIndex];
  }

  const T &operator[](std::size_t aIndex)const
  {
    return mData[aIndex];
  }

  T *data()
  {
    return mData;
  }

  const T *data()const
  {
    return mData;
  }

  std::size_t size()
  {
    return aSize;
  }

  T mData[aSize];
};

int main()
{
  return 0;
}
