#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <utility>

#include "selectionsort.hpp"

template<typename T>
bool less_a(T &aValue1, T &aValue2)
{
  return aValue1 < aValue2;
}

template<typename T>
void swap_a(T &aValue1, T &aValue2)
{
  T tmp;
  tmp = aValue1;
  aValue1 = aValue2;
  aValue2 = tmp;
}

template<typename T>
void select_exampple_a(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0; i < end - 1; ++i)
  {
    unsigned min = i;
    for(unsigned j = i + 1; j < end; ++j)
      if(less_a(aVector[j], aVector[min]))
        min = j;
    swap_a(aVector[i], aVector[min]);
  }
}

void select_a_unsorted(unsigned aTest, unsigned aArrSize)
{
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << " Test: " << aTest
            << ", array is UNSORTED, size=" << aArrSize
            << ", the swap time not important"
            << std::endl;

  std::vector<unsigned> v;
  static bool isInited{false};
  if(!isInited)
  {
    v.resize(aArrSize);
    for(unsigned i = 0; i < aArrSize; ++i)
      v[i] = aArrSize - i;
  }

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  select_exampple_a(v);
  TimeVar t2 = std::chrono::high_resolution_clock::now();

  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}

void select_a_sorted(unsigned aTest, unsigned aArrSize)
{
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << " Test: " << aTest
            << ", array is SORTED, size=" << aArrSize
            << ", the swap time not important"
            << std::endl;

  std::vector<unsigned> v;
  static bool isInited{false};
  if(!isInited)
  {
    v.resize(aArrSize);
    for(unsigned i = 0; i < aArrSize; ++i)
      v[i] = i;
  }

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  select_exampple_a(v);
  TimeVar t2 = std::chrono::high_resolution_clock::now();

  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}

template<typename T>
bool less_b(T &aValue1, T &aValue2)
{
  std::this_thread::sleep_for(std::chrono::microseconds(10));
  return aValue1 < aValue2;
}

template<typename T>
void swap_b(T &aValue1, T &aValue2)
{
  T tmp;
  tmp = aValue1;
  aValue1 = aValue2;
  aValue2 = tmp;
  std::this_thread::sleep_for(std::chrono::microseconds(100));
}

template<typename T>
void select_exampple_b(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0; i < end - 1; ++i)
  {
    unsigned min = i;
    for(unsigned j = i + 1; j < end; ++j)
      if(less_b(aVector[j], aVector[min]))
        min = j;

    swap_b(aVector[i], aVector[min]);
  }
}

void select_b_unsorted(unsigned aTest, unsigned aArrSize)
{
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << " Test: " << aTest
            << ", array is UNSORTED, size=" << aArrSize
            << ", The comparison time is LESS than the moving time"
            << std::endl;

  std::vector<unsigned> v;
  static bool isInited{false};
  if(!isInited)
  {
    v.resize(aArrSize);
    for(unsigned i = 0; i < aArrSize; ++i)
      v[i] = aArrSize - i;
  }

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  select_exampple_b(v);
  TimeVar t2 = std::chrono::high_resolution_clock::now();

  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}

void select_b_sorted(unsigned aTest, unsigned aArrSize)
{
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << " Test: " << aTest
            << ", array is SORTED, size=" << aArrSize
            << ", The comparison time is LESS than the moving time"
            << std::endl;

  std::vector<unsigned> v;
  static bool isInited{false};
  if(!isInited)
  {
    v.resize(aArrSize);
    for(unsigned i = 0; i < aArrSize; ++i)
      v[i] = i;
  }

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  select_exampple_b(v);
  TimeVar t2 = std::chrono::high_resolution_clock::now();

  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}


//------------------------------------------------------------------------------
template<typename T>
bool less_c(T &aValue1, T &aValue2)
{
  std::this_thread::sleep_for(std::chrono::microseconds(100));
  return aValue1 < aValue2;
}

template<typename T>
void swap_c(T &aValue1, T &aValue2)
{
  T tmp;
  tmp = aValue1;
  aValue1 = aValue2;
  aValue2 = tmp;
  std::this_thread::sleep_for(std::chrono::microseconds(10));
}

template<typename T>
void select_exampple_c(std::vector<T> &aVector)
{
  unsigned end = aVector.size();
  for(unsigned i = 0; i < end - 1; ++i)
  {
    unsigned min = i;
    for(unsigned j = i + 1; j < end; ++j)
      if(less_c(aVector[j], aVector[min]))
        min = j;

    swap_c(aVector[i], aVector[min]);
  }
}

void select_c_unsorted(unsigned aTest, unsigned aArrSize)
{
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << " Test: " << aTest
            << ", array is UNSORTED, size=" << aArrSize
            << ", The comparison time is MORE than the moving time"
            << std::endl;

  std::vector<unsigned> v;
  static bool isInited{false};
  if(!isInited)
  {
    v.resize(aArrSize);
    for(unsigned i = 0; i < aArrSize; ++i)
      v[i] = aArrSize - i;
  }

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  select_exampple_c(v);
  TimeVar t2 = std::chrono::high_resolution_clock::now();

  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}

void select_c_sorted(unsigned aTest, unsigned aArrSize)
{
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << " Test: " << aTest
            << ", array is SORTED, size=" << aArrSize
            << ", The comparison time is MORE than the moving time"
            << std::endl;

  std::vector<unsigned> v;
  static bool isInited{false};
  if(!isInited)
  {
    v.resize(aArrSize);
    for(unsigned i = 0; i < aArrSize; ++i)
      v[i] = i;
  }

  typedef std::chrono::high_resolution_clock::time_point TimeVar;

  TimeVar t1 = std::chrono::high_resolution_clock::now();
  select_exampple_c(v);
  TimeVar t2 = std::chrono::high_resolution_clock::now();

  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}


void selection_test_a()
{
  constexpr unsigned arraySize_a{20000};
  select_a_unsorted(1, arraySize_a);
  select_a_unsorted(2, arraySize_a);
  select_a_unsorted(3, arraySize_a);
  select_a_unsorted(4, arraySize_a);

  select_a_sorted(1, arraySize_a);
  select_a_sorted(2, arraySize_a);
  select_a_sorted(3, arraySize_a);
  select_a_sorted(4, arraySize_a);

  constexpr unsigned arraySize_b{50};
  select_b_unsorted(1, arraySize_b);
  select_b_unsorted(2, arraySize_b);
  select_b_unsorted(3, arraySize_b);
  select_b_unsorted(4, arraySize_b);

  select_b_sorted(1, arraySize_b);
  select_b_sorted(2, arraySize_b);
  select_b_sorted(3, arraySize_b);
  select_b_sorted(4, arraySize_b);
}

void selection_test_b()
{
  constexpr unsigned arraySize_a{100000};
  select_a_unsorted(1, arraySize_a);
  select_a_sorted(1, arraySize_a);

  constexpr unsigned arraySize_b{200};
  select_b_unsorted(1, arraySize_b);
  select_b_sorted(1, arraySize_b);

  constexpr unsigned arraySize_c{200};
  select_c_unsorted(1, arraySize_c);
  select_c_sorted(1, arraySize_c);
}
