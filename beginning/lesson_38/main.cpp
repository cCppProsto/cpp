#include <iostream>
#include <string>
#include <cstring>
//#include <thread>
//#include <mutex>


int f_1(int value)
{
  std::cout << "f_1" << std::endl;
  return value + 1;
}

int f_2(int value)
{
  std::cout << "f_2" << std::endl;
  return value + 2;
}

int f_3(int value)
{
  std::cout << "f_3" << std::endl;
  return value + 2;
}

void test(int a, int b, int c)
{

}

void test_2(int i, int j)
{
  std::cout << i << "," << j << std::endl;
}

int main()
{
  std::cout << "-----------   UNDEFINED BEHAVIOUR ---------------" << std::endl;
  {
    std::cout << "-----------------  1  ---------------------------" << std::endl;
    int i = 0;
    int arr[3] = {0};
    arr[i] = i++;
    std::cout << arr[0] << ", " << arr[1] << ", " << arr[2] << std::endl;
  }

  int x = 1;
  int y = 2;
  {
    std::cout << "-----------------  2  ---------------------------" << std::endl;
    int summa = ++x + x++;
    std::cout << summa << std::endl;

    summa = summa++ + 1;
    std::cout << summa << std::endl;

    std::cout << summa << ", " << summa++ << std::endl;
  }

  {
    std::cout << "-----------------  3  ---------------------------" << std::endl;
    int summa = f_1(x) + f_2(y) + f_3(x);
  }

  {
    std::cout << "-----------------  4  ---------------------------" << std::endl;
    test(f_1(x), f_2(y), f_3(x));
  }

  {
    std::cout << "-----------------  5  ---------------------------" << std::endl;
    int i = 0;
    test_2(++i, ++i);
  }

  std::cout << "-----------   WELL DEFINED ----------------------" << std::endl;
  {
    std::cout << "-----------------  6  ---------------------------" << std::endl;
    f_1(x), f_2(y), f_3(x);
  }
  {
    std::cout << "-----------------  7  ---------------------------" << std::endl;
    int a = 0;
    int b = 0;
    b = (a=1,a+2);
    std::cout << b << std::endl;
  }

  {
    std::cout << "-----------------  8  ---------------------------" << std::endl;
    if(f_1(x) && f_2(y) && f_3(x))
    {

    }
  }
  {
    std::cout << "-----------------  9  ---------------------------" << std::endl;
    int i = ++i + 1; // c++11
    std::cout << i << std::endl;
  }

  {
    std::cout << "-----------------  10 ---------------------------" << std::endl;
    int i = 0;
    i = ++i + 1;  // c++11
    std::cout << i << std::endl;
  }

  return 0;
}
