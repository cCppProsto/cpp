#ifndef ALG_SORTS_HPP
#define ALG_SORTS_HPP

#include <vector>

template<typename T>
bool larger(T &aValue1, T &aValue2)
{
  return aValue1 > aValue2;
}

template<typename T>
bool less(T &aValue1, T &aValue2)
{
  return aValue1 < aValue2;
}


template<typename T>
void swap(T &aValue1, T &aValue2)
{
  T tmp;
  tmp = aValue1;
  aValue1 = aValue2;
  aValue2 = tmp;
}

//-------------------- SELECT SORT ---------------------------------------------
template<typename T>
void select_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0; i < end - 1; ++i)
  {
    unsigned min = i;
    for(unsigned j = i + 1; j < end; ++j)
      if(less(aVector[j], aVector[min]))
        min = j;
    swap(aVector[i], aVector[min]);
  }
}
//------------------------------------------------------------------------------

//-------------------- INSERT SORT ---------------------------------------------
template<typename T>
void insert_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size() - 1;
  for(unsigned i = end; i > 0; --i)
    if(larger(aVector[i-1], aVector[i]))
      swap(aVector[i-1], aVector[i]);

  for(unsigned i = 2; i <= end; ++i)
  {
    unsigned j = i;
    unsigned value = aVector[i];

    while(larger(aVector[j-1], value))
    {
      aVector[j] = aVector[j-1];
      --j;
    }
    aVector[j] = value;
  }
}
//------------------------------------------------------------------------------

//-------------------- BUBBLE SORT ---------------------------------------------
template<typename T>
void bubble_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0 ; i < ( end - 1 ); i++)
    for (unsigned j = 0 ; j < end - i - 1; j++)
      if(larger(aVector[j], aVector[j+1]))
        swap(aVector[j], aVector[j+1]);
}
//------------------------------------------------------------------------------

//-------------------- SHELL SORT ----------------------------------------------
template <typename T>
void shell_sort(std::vector<T> &aVector)
{
  unsigned end = aVector.size() - 1;

  unsigned h;
  for(h = 1; h <= end/9; h = 3*h+1)
    ;

  for(; h > 0; h /= 3)
    for(auto i = h; i <= end; i++)
    {
      unsigned j = i;
      T v = aVector[i];
      while(j >= h && v < aVector[j - h])
      {
        aVector[j] = aVector[j - h];
        j -= h;
      }
      aVector[j] = v;
    }
}
//------------------------------------------------------------------------------

#endif // ALG_SORTS_HPP
