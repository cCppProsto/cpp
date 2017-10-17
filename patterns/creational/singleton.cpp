#include <memory>
#include <iostream>
using namespace std;

namespace creational_singleton
{

struct appSettings
{
  appSettings(const appSettings &) = delete;
  appSettings & operator=(const appSettings&) = delete;

  static appSettings &instance()
  {
    static appSettings res;
    return res;
  }

  void load()
  {
    // ...
    // ...
    mScreenWidth  = 1024;
    mScreenHeight = 768;
  }

  const unsigned &width()const
  {
    return mScreenWidth;
  }

  const unsigned &height()const
  {
    return mScreenHeight;
  }

private:
  appSettings() = default;

private:
  unsigned mScreenWidth{0};
  unsigned mScreenHeight{0};
};

void some_func_a()
{
  std::cout << "width - " << appSettings::instance().width() << std::endl;
}

void some_func_b()
{
  std::cout << "height - " << appSettings::instance().height() << std::endl;
}

void some_func_c()
{
  auto &w = appSettings::instance().width();
  auto &h = appSettings::instance().height();
  std::cout << "width:" << w << std::endl;
  std::cout << "height:" << h << std::endl;
}


void singleton_main()
{
  // all main objects already created
  appSettings::instance().load();

  some_func_a();
  some_func_b();
  some_func_c();
}

}
