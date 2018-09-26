#include <algorithm>
#include <random>
#include <vector>
#include <thread>
#include <chrono>
#include <utility>
#include <iostream>

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
  std::cout << nano  << " nanoseconds" << std::endl << std::endl;
  //std::cout << "-------------------------------------------------" << std::endl;
}

void test_1(unsigned size)
{
  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- bubble sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    bubble_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- insert sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    insert_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- select sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    select_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- shell sort ---------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    shell_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v1 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v2 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort_v2(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v3 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort_v3(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v4 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = size; i > 0; --i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort_v4(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }
}

void test_2(unsigned size)
{
  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- bubble sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    bubble_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- insert sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    insert_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- select sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    select_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- shell sort ---------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    shell_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v1 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v2 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort_v2(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v3 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort_v3(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v4 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);

    auto t1 = get_time();
    quicksort_v4(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }
}

void test_3(unsigned size)
{
  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- bubble sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    bubble_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- insert sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    insert_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- select sort --------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    select_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- shell sort ---------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    shell_sort(v);
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v1 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    quicksort(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v2 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    quicksort_v2(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v3 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    quicksort_v3(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }

  {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "---------- quick sort v4 ------------------------" << std::endl;

    std::vector<unsigned> v;
    v.reserve(size);

    for(unsigned i = 0; i < size; ++i)
      v.push_back(i);
    std::shuffle(v.begin(), v.end(), std::default_random_engine());

    auto t1 = get_time();
    quicksort_v4(v.data(), 0, v.size());
    auto t2 = get_time();
    print_difference(t1, t2);
  }
}

int main()
{
/*
  На входе массив a[0]...a[N] и опорный элемент p, по которому будет производиться разделение.

  1) i и j.

  2) В начале алгоритма они указывают, соответственно, на левый и правый конец последовательности.
  Будем двигать i с шагом в 1 элемент по направлению к концу массива,
  пока не будет найден элемент a[i] > p.
  Затем аналогичным образом начнем двигать j от конца массива к началу, пока не будет найден a[j] < p.

  3) Далее, если i < j, меняем a[i] и a[j] местами и продолжаем двигать i,j по тем же правилам...

  4) Повторяем шаг 3, пока i <= j.
*/
  // 7  8  3  19  23  0  14  2  6  15
  // 15
  // i = 0
  // j = 9

  // 7 > 15 ?
  // 8 > 15 ?
  // ...
  // 19 > 15 -> i = 3

  // 6 < 15 ->  j = 8

  // i < j -> swap
  // 7  8  3  6  23  0  14  2  19  15

  // 23 > 15 -> i = 4
  // 2 < 15 -> j = 7
  // i < j -> swap

  // 7  8  3  6  2  0  14  23  19  15

  // Left  - 7  8  3  6  2  0  14
  // Right - 23  19  15

  constexpr unsigned size{50000};

//  std::cout << "Test 1 -----------------------------------------------------------" << std::endl;
//  test_1(size);
//  std::cout << std::endl << std::endl;

//  std::cout << "Test 2 -----------------------------------------------------------" << std::endl;
//  test_2(size);
//  std::cout << std::endl << std::endl;

  std::cout << "Test 3 -----------------------------------------------------------" << std::endl;
  test_3(size);

  return 0;
}
