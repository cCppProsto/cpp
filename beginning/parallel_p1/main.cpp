#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <thread>

// http://www.openmp.org/
#include <omp.h>
#include <parallel/algorithm>


using namespace std;

namespace cpp_17_parralel
{
  void test()
  {
    unsigned int size = 100 * 1000 * 1000;
    vector<double> v;

    v.resize(size);

    for(unsigned int i = 0; i < size; ++i)
      v[i] = (double)(size - i);

    cout << "first:" << v[0] << ", last:" << v[size-1] << endl;

    auto start = chrono::steady_clock::now();

    sort(v.begin(), v.end());
    //__gnu_parallel::sort(v.begin(), v.end());

    auto end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
    cout << "first:" << v[0] << ", last:" << v[size-1] << endl;
  }
}

namespace open_mp_1
{
  void test()
  {
    #pragma omp parallel
    {
      cout << omp_get_thread_num() << " Hello!" << endl;
    }
  }
}

namespace open_mp_2
{
  void test()
  {
    #pragma omp parallel //num_threads(1)
    {
      #pragma omp for
      for(int n = 0; n<10; ++n)
      {
        cout << "Thread(" << omp_get_thread_num() << ")" << "i=" << n << endl;
      }
    }
  }
}

int main()
{
  //cpp_17_parralel::test();
  //open_mp_1::test();
  open_mp_2::test();
  return 1;
}


