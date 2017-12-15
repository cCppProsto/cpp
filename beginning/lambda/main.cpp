#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;


void example_1()
{
  auto vprint = [](std::vector<int> &v)
  {
    for(auto i : v)
      std::cout << i << ", ";
    std::cout << std::endl;
  };

  constexpr unsigned size = 20;
  std::vector<int> v;
  v.reserve(size);
  for(unsigned i = 0; i < size; ++i)
    v.push_back(rand()%100 - 50);

  vprint(v);

  std::sort(v.begin(), v.end());
  vprint(v);

  std::sort(v.begin(), v.end(), [](int a, int b) { return a < b; });
  vprint(v);

  std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
  vprint(v);

  std::sort(v.begin(), v.end(), [](int a, int b) { return std::abs(a) < std::abs(b); });
  vprint(v);
}

void example_2()
{
  constexpr unsigned size = 20;
  std::vector<int> v;
  v.reserve(size);
  for(unsigned i = 0; i < size; ++i)
    v.push_back(rand()%100 - 50);

  auto vprint = [&]()
  {
    for(auto i : v)
      std::cout << i << ", ";
    std::cout << std::endl;
  };

  vprint();

  std::sort(v.begin(), v.end());
  vprint();

  std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
  vprint();

  std::sort(v.begin(), v.end(), [](int a, int b) { return std::abs(a) < std::abs(b); });
  vprint();
}

enum class eAction
{
  START
 ,STOP
 ,MOVE
};

struct notifier
{
  void clb_start()
  {
    std::cout << "start is ok" << std::endl;
  }
  void clb_stop()
  {
    std::cout << "stop is ok" << std::endl;
  }
  void clb_move()
  {
    std::cout << "move is ok" << std::endl;
  }
};

void rrr()
{

}

void example_3()
{
  std::queue<std::pair<eAction, std::function<void()>>> q;

  notifier n;

  q.push({eAction::MOVE,  [&]{ n.clb_move(); } });
  q.push({eAction::START, [&]{ n.clb_start();} });
  q.push({eAction::STOP,  [&]{ n.clb_stop(); } });

  for(auto i = 0; i < 100; ++i)
  {
    switch(rand()%100)
    {
      case 0 ... 5:
      {
        auto a = q.front();
        // a.first ->
        a.second();
        q.pop();
        break;
      }
    }
    if(q.empty())
      break;
  }
}

void example_4()
{
  std::queue<std::pair<eAction, std::function<void()>>> q;

  q.push({eAction::MOVE,  []{ std::cout << "move is start" << std::endl; } });
  q.push({eAction::START, []{ std::cout << "start is start" << std::endl; } });
  q.push({eAction::STOP,  []{ std::cout << "stop is start" << std::endl; } });

  for(auto i = 0; i < 100; ++i)
  {
    switch(rand()%100)
    {
      case 0 ... 5:
      {
        auto a = q.front();
        // a.first ->
        a.second();
        q.pop();
        break;
      }
    }
    if(q.empty())
      break;
  }
}

int main()
{
  //example_1();
  //example_2();
  //example_3();
  example_4();
  return 0;
}
