#include <iostream>

#include "bubblesort.hpp"
#include "selectionsort.hpp"
#include "insertionsort.hpp"

#include <vector>

template<typename T>
void bubble(std::vector<T> aArray)
{
  unsigned end = aArray.size();
  for(unsigned i = 0 ; i < ( end - 1 ); i++)
    for (unsigned j = 0 ; j < end - i - 1; j++)
      if(aArray[j] > aArray[j+1])
        std::swap(aArray[j], aArray[j+1]);
}

template<typename T>
void selection(std::vector<T> aArray)
{
  unsigned end = aArray.size();
  for(unsigned i = 0; i < end - 1; ++i)
  {
    unsigned min = i;
    for(unsigned j = i + 1; j < end; ++j)
      if(aArray[j] < aArray[min])
        min = j;

    std::swap(aArray[i], aArray[min]);
  }
}

template<typename T>
void insertion(std::vector<T> aArray)
{
  unsigned end = aArray.size() - 1;
  for(unsigned i = end; i > 0; --i)
    if(aArray[i-1] > aArray[i])
      std::swap(aArray[i-1], aArray[i]);

  for(unsigned i = 2; i <= end; ++i)
  {
    unsigned j = i;
    unsigned value = aArray[i];

    while(aArray[j-1] > value)
    {
      aArray[j] = aArray[j-1];
      --j;
    }
    aArray[j] = value;
  }
}

/*
BUBBLE ----------------------------------------------------
                 UNSORTED,  size=100000  8452 miliseconds
                 SORTED,    size=100000  3327 miliseconds
  cmp LESS move, UNSORTED,  size=200     4418 miliseconds
  cmp LESS move, SORTED,    size=200     1314 miliseconds
  cmp MORE move, UNSORTED,  size=200     4412 miliseconds
  cmp MORE move, SORTED,    size=200,    3111 miliseconds

SELECTION -------------------------------------------------
                 UNSORTED,  size=100000  4980 miliseconds
                 SORTED,    size=100000  4992 miliseconds
  cmp LESS move, UNSORTED,  size=200     1338 miliseconds
  cmp LESS move, SORTED,    size=200     1337 miliseconds
  cmp MORE move, UNSORTED,  size=200     3129 miliseconds
  cmp MORE move, SORTED,    size=200     3116 miliseconds

INSERTION -----------------------------------------
                 UNSORTED,  size=100000  3376 miliseconds
                 SORTED,    size=100000     0 miliseconds   162 microseconds
  cmp LESS move, UNSORTED,  size=200     4463 miliseconds
  cmp LESS move, SORTED,    size=200       57 miliseconds
  cmp MORE move, UNSORTED,  size=200     2657 miliseconds
  cmp MORE move, SORTED,    size=200       57 miliseconds
*/

int main()
{
  std::cout << "------------ BUBBLE --------------------------------------------"
            << std::endl;
  buble_test_b();
  std::cout << std::endl << std::endl;

  std::cout << "------------ SELECTION -----------------------------------------"
            << std::endl;
  selection_test_b();
  std::cout << std::endl << std::endl;

  std::cout << "------------ INSERTION -----------------------------------------"
            << std::endl;
  insert_test_b();
  return 0;
}
