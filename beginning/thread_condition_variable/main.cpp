#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include <atomic>

using namespace std;


namespace example_1
{
  struct sData
  {
    size_t id;
    size_t v;
  };

  std::queue<sData> g_queque;
  std::mutex        g_queque_lock;

  std::atomic_bool        cv_notified{false};
  std::mutex              cv_mutex;
  std::condition_variable cv;


  void f_thread(size_t aId)
  {
    size_t thread_id = aId;
    std::unique_lock<std::mutex> mtx(cv_mutex);

    cout << "thread(" << thread_id << ") started" << endl;

    while(1)
    {
      while(!cv_notified)
        cv.wait(mtx);

      cv_notified = false;

      g_queque_lock.lock();
        if(g_queque.size() > 0)
        {
          sData tmp = g_queque.front();

          cout << "thread(" << thread_id << ") "
               << "Data processing ... [" << tmp.id << ", " << tmp.v << "]"
               << endl;

          cout << "thread(" << thread_id << ") "<< "data processing complete!" << endl;

          g_queque.pop();
          std::this_thread::sleep_for(std::chrono::milliseconds(rand()%3000 + 500));
        }
      g_queque_lock.unlock();
    }
  }

  void test()
  {
    size_t thread_count = 10;

    for(size_t i = 0; i < thread_count; ++i)
      std::thread(f_thread, i).detach();

    for(;;)
    {
      g_queque_lock.lock();
      size_t l = g_queque.size();
      g_queque_lock.unlock();

      if(l < thread_count)
      {
        size_t r = rand() % 10;
        if(r == 5)
        {
          static size_t id{0};
          sData tmp {id, rand()%1000};

          g_queque_lock.lock();
          g_queque.push(tmp);
          g_queque_lock.unlock();

          cout << "data was received("<< g_queque.size()<<")" << endl;
          cv_notified = true;
          cv.notify_one();
          ++id;
        }
      }
    }
  }
}


int main()
{
  example_1::test();


  return 0;
}
