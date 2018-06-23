#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;


namespace  example_1
{
  void f_thread(int aI)
  {
    std::cout << aI << std::endl;
  }

  void test()
  {
    std::thread th1(f_thread, 1);
    std::thread th2(f_thread, 2);
    std::thread th3(f_thread, 3);
  }
}

namespace  example_2
{
  void f_thread(int aI)
  {
    std::cout << aI << std::endl;
  }

  void test()
  {
    std::thread th1(f_thread, 1);
    std::thread th2(f_thread, 2);
    std::thread th3(f_thread, 3);

    th1.join();
    th2.join();
    th3.join();
  }
}

namespace  example_3
{
  std::mutex m;

  void f_thread(int aI)
  {
    m.lock();
    std::cout << aI << std::endl;
    m.unlock();
  }

  void test()
  {
    std::thread th1(f_thread, 1);
    std::thread th2(f_thread, 2);
    std::thread th3(f_thread, 3);

    th1.join();
    th2.join();
    th3.join();
  }
}

namespace  example_4
{
  std::mutex m;
  void f_thread(int aI)
  {
    m.lock();
    std::cout << aI << std::endl;
    m.unlock();
  }

  void test()
  {
    std::thread th1(f_thread, 1);
    std::thread th2(f_thread, 2);
    std::thread th3(f_thread, 3);

    th1.detach();
    th2.detach();
    th3.detach();
  }
}

int main()
{
  //example_1::test();
  //example_2::test();
  //example_3::test();
  example_4::test();

  return 0;
}
