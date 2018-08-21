#include <iostream>
#include <string>

using namespace std;


// uncomment to disable assert()
// #define NDEBUG
#include <cassert>


struct downloader
{
  void load(std::string aUrl
           ,size_t      aThreadCount
           ,size_t      aChunkSize)
  {
    assert(!aUrl.empty()              && "url is empty");
    assert((aThreadCount > 0)         && "count of thread is 0");

    // defaults = 128KB
    assert((aChunkSize >= 1024 * 128) && "incorrect chunk size");

    std::cout << "loaded" << std::endl;
  }
};


struct manager
{
  void load()
  {
    // get count of cores

    // test speed

    // calc chunk size

    downloader m_d;
    m_d.load("123123", 8, 1024*32);
  }

  downloader m_d;
};



int main()
{
  manager m;
  m.load();

  return 0;
}
