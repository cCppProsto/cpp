#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

unsigned char              gUChar{0};
std::atomic<unsigned char> gaUChar{0};

unsigned short              gShort{0};
std::atomic<unsigned short> gaShort{0};

int                 gInt{0};
std::atomic<int>    gaInt{0};
std::atomic<int>    gfetchInt{0};

long                gLong{0};
std::atomic<long>   gaLong{0};

double              gmDouble{0.};
double              gDouble{0.};
std::atomic<double> gaDouble{0.};

std::mutex gMutex;

std::atomic<size_t> thread_count{0};

void f_thread()
{
  long i = 0;
  thread_count++;
  while(i < 10000)
  {
    gUChar++;
    gShort++;
    gInt++;
    gLong++;
    gDouble = gDouble + 1.;

    gaUChar++;
    gaShort++;
    gaInt++;
    gaLong++;
    atomic_fetch_add(&gfetchInt, 1);

    gaDouble = gaDouble + 1.;
    gMutex.lock();
      gmDouble = gmDouble + 1.;
    gMutex.unlock();

    ++i;
  }
  thread_count--;
}

void test()
{
  gUChar    = 0;
  gaUChar   = 0;
  gShort    = 0;
  gaShort   = 0;
  gInt      = 0;
  gaInt     = 0;
  gfetchInt = 0;
  gLong     = 0;
  gaLong    = 0;
  gmDouble  = 0.;
  gDouble   = 0.;
  gaDouble = 0.;

  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();
  std::thread(f_thread).detach();

  while(thread_count != 0)
    std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "Not atomic uchar  = " << (int)gUChar    << std::endl;
  std::cout << "atomic uchar      = " << (int)gaUChar   << std::endl << std::endl;

  std::cout << "Not atomic short  = " << gShort    << std::endl;
  std::cout << "atomic short      = " << gaShort   << std::endl << std::endl;

  std::cout << "Not atomic int    = " << gInt      << std::endl;
  std::cout << "atomic int        = " << gaInt     << std::endl;
  std::cout << "fetch int         = " << gfetchInt << std::endl << std::endl;

  std::cout << "Not atomic long   = " << gLong    << std::endl;
  std::cout << "atomic long       = " << gaLong   << std::endl << std::endl;

  std::cout << "Not atomic double = " << gDouble  << std::endl;
  std::cout << "atomic double     = " << gaDouble << std::endl;
  std::cout << "mutex double      = " << gmDouble << std::endl << std::endl;
  std::cout << "-----------------------------------------------------------------------------" << std::endl;
}

int main()
{
  test();
  test();
  test();
  test();
  return 0;
}
