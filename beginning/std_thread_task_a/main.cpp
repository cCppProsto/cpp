#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include <queue>

using namespace std;

namespace async_example_1
{
  bool f_task(unsigned aTaskID)
  {
    static std::mutex m;
    m.lock();
    std::cout << "(th_id:"
              << this_thread::get_id()
              << ") "
              << "task("
              << aTaskID
              << ") completed" << std::endl;
    m.unlock();

    size_t sleep = std::rand() % 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    return true;
  }

  void test()
  {
    std::cout << "main id: " << this_thread::get_id() << std::endl;

    std::queue<std::future<bool>> queue;

    for(unsigned i = 0; i < 10; ++i)
      queue.push(std::async(f_task, i));

    while(!queue.empty())
    {
      queue.front().wait();
      queue.pop();
    }
    std::cout << "main_id done!" << std::endl;
  }
}

namespace async_example_2
{
  bool f_task(unsigned aTaskID)
  {
    static std::mutex m;
    m.lock();
    std::cout << "(th_id:"
              << this_thread::get_id()
              << ") "
              << "task("
              << aTaskID
              << ") completed" << std::endl;
    m.unlock();

    size_t sleep = std::rand() % 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
    return true;
  }

  void test()
  {
    std::cout << "main id: " << this_thread::get_id() << std::endl;

    std::queue<std::future<bool>> queue;

    for(unsigned i = 0; i < 10; ++i)
      queue.push(std::async(std::launch::async, f_task, i));

    bool res = false;
    while(!queue.empty())
    {
      auto &task = queue.front();
      res = task.get();
      queue.pop();
    }
    std::cout << "main_id done!" << std::endl;
  }
}


namespace packaged_task_example_1
{
  bool f_task(unsigned aTaskID)
  {
    static std::mutex m;
    m.lock();
    std::cout << "("
              << this_thread::get_id()
              << ""
              << "Task "
              << aTaskID
              << " completed" << std::endl;
    m.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    return true;
  }

  void test()
  {
    std::queue<std::packaged_task<bool(unsigned)> > _queue;

    for(unsigned i = 0; i < 1000; ++i)
    {
      std::packaged_task<bool(unsigned)> task(f_task);
      _queue.push(std::move(task));
    }

    for(unsigned i = 0; i < 1000; ++i)
    {
      auto &task = _queue.front();
      auto task_result = task.get_future();
      bool res = false;
      task(i);
      res = task_result.get();
      _queue.pop();
    }

  }
}

int main()
{
  //async_example_1::test();
  async_example_2::test();
  //packaged_task_example_1::test();

  return 0;
}
