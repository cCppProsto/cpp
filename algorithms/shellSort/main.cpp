#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <utility>

#include "../algorithms/sorting_algorithms.hpp"

using namespace std;

auto get_time()
{
  return std::chrono::high_resolution_clock::now();
}

void print_difference(std::chrono::high_resolution_clock::time_point t1,
                      std::chrono::high_resolution_clock::time_point t2)
{
  unsigned nano  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
  unsigned micro = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
  unsigned mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  unsigned sec = std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count();

  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << sec   << " seconds" << std::endl;
  std::cout << mili  << " miliseconds" << std::endl;
  std::cout << micro << " microseconds" << std::endl;
  std::cout << nano  << " nanoseconds" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;
}

int main()
{
  constexpr unsigned size{50000};

  {
    std::vector<unsigned> v;
    v.reserve(10);

    for(unsigned i = 10; i > 0; --i)
      v.push_back(i);
    shell_sort(v);
  }

//  {
//    std::vector<unsigned> v;
//    v.reserve(size);

//    for(unsigned i = size; i > 0; --i)
//      v.push_back(i);

//    auto t1 = get_time();
//    bubble_sort(v);
//    auto t2 = get_time();
//    print_difference(t1, t2);
//  }

  {
    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    insert_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

//  {
//    std::vector<unsigned> v;
//    v.reserve(size);

//    for(unsigned i = size; i > 0; --i)
//      v.push_back(i);

//    auto t1 = get_time();
//    select_sort(v);
//    auto t2 = get_time();
//    print_difference(t1, t2);
//  }

  {
    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    shell_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  return 0;
}
