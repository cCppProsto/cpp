#include <iostream>
#include <string>

using namespace std;


namespace ns_1
{
  template<typename T> T max(T a, T b)
  {
    return a > b ? a : b;
  }

  /*
  template<> char* max<char*>(char *a, char *b)
  {
    // some code for comparing
    return 0; // return result
  }
  */

  template<typename T, int N> void sort(T (&a)[N])
  {
    for (int i = 0; i < N - 1; i++)
      for (int j = 0; j < N-i-1; j++)
      {
        if (a[j] > a[j+1])
          std::swap(a[j], a[j+1]);
      }
  }

  /*
  template<int N> void sort(char *(&ar)[N])
  {
    char *tmp = ar[0];
    ar[0] = ar[1];
    ar[1] = tmp;
  }
  */

  void test()
  {
    int    i_tmp{0};
    double d_tmp{0.};
    i_tmp = max(1,2);
    d_tmp = max(1.001,1.002);

    char *c_str_a = (char*)"AA";
    char *c_str_b = (char*)"AB";
    char *c_str_c = (char*)"AB";
    char *c_str_d = (char*)"BA";
    char *tmp{nullptr};

    tmp = max(c_str_a, c_str_b);
    tmp = max(c_str_c, c_str_d);

    int i_arr_a[]{4, 3, 2, 1};
    sort(i_arr_a);

    char *c_str_arr_a[] = {(char*)"13", (char*)"12", (char*)"11", (char*)"10"};
    char *c_str_arr_b[] = {(char*)"2000", (char*)"100"};

    sort(c_str_arr_a);
    sort(c_str_arr_b);

    std::string str_arr_a[] = {"2000", "100"};
    sort(str_arr_a);
  }
}


namespace ns_2
{
  // шаблон для функции f и реализация
  template<typename T> void f(T)
  {
    std::cout << "1" << std::endl;
  }

  // перегрузка функции f
  template<typename T> void f(int, T, double)
  {
    std::cout << "2" << std::endl;
  }

  // шаблон для функции f с указателем в качестве параметра
  template<class T> void f(T*)
  {
    std::cout << "3" << std::endl;
  }

  // полная специализация для шаблона template<typename T> void f(T)
  template<> void f<int>(int)
  {
    std::cout << "4" << std::endl;
  }

  // просто функция f с параметром double
  void f(double)
  {
    std::cout << "5" << std::endl;
  }

  void test()
  {
    bool b{false};
    int i{0};
    double d{1.};

    f(b);
    f(i, 1, d);
    f(&i);
    f(i);
    f(d);
  }
}

namespace ns_3
{
  // базовый шаблон
  template<class T> void f( T )
  {
    std::cout << "1" << std::endl;
  }

  // базовый шаблон, перегружает предыдущий шаблон
  template<class T> void f( T* )
  {
    std::cout << "2" << std::endl;
  }

  // явная(полная) специализация
  template<> void f<>(int*)
  {
    std::cout << "3" << std::endl;
  }

  void test()
  {
    int *p{nullptr};
    f(p); // на экране 3
  }
}

namespace ns_4
{
  // базовый шаблон
  template<class T> void f( T )
  {
    std::cout << "1" << std::endl;
  }

  // явная(полная) специализация
  template<> void f<>(int*)
  {
    std::cout << "2" << std::endl;
  }

  // базовый шаблон, перегружает первый шаблон
  template<class T> void f( T* )
  {
    std::cout << "3" << std::endl;
  }

  void test()
  {
    int *p{nullptr};
    f(p); // на экране 3
    // перегрузка игнорирует специализацию, и работает с базовым шаблоном
  }
}

namespace ns_5
{
  void f(int*)
  {
    std::cout << "0" << std::endl;
  }

  // базовый шаблон
  template<class T> void f( T )
  {
    std::cout << "1" << std::endl;
  }

  // явная(полная) специализация
  template<> void f<>(int*)
  {
    std::cout << "2" << std::endl;
  }

  // базовый шаблон, перегружает первый шаблон
  template<class T> void f( T* )
  {
    std::cout << "3" << std::endl;
  }

  void test()
  {
    int *p{nullptr};

    f(p); // на экране 0
          // Не пишите специализацию, если можно решить проблему перегрузкой.
  }
}

int main()
{
  // ns_1::test();
  // ns_2::test();
  // ns_3::test();
  // ns_4::test();
  ns_5::test();

  return 0;
}
