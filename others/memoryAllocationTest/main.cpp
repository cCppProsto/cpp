#include <iostream>
#include <chrono>
#include <string>
#include <memory>

using namespace std;
typedef std::chrono::high_resolution_clock::time_point TimeVar;

static constexpr size_t ITERATION_COUNT { 10000000 };

std::chrono::high_resolution_clock::time_point get_time()
{
  return std::chrono::high_resolution_clock::now();
}

unsigned diff_ms(std::chrono::high_resolution_clock::time_point t1,
  std::chrono::high_resolution_clock::time_point t2)
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

unsigned diff_sec(std::chrono::high_resolution_clock::time_point t1,
  std::chrono::high_resolution_clock::time_point t2)
{
  return std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
}

void test_new_a()
{
  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    int *piArray = new int;
    delete piArray;
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_new_b()
{
  struct sTest
  {
    sTest()  { }
    ~sTest() { }
    private:
      int         m_i{0};
      std::string m_str;
      char        m_ch;
  };

  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    sTest *piArray = new sTest;
    delete piArray;
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_unique_ptr_a()
{
  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    std::unique_ptr<int> uniq(new int);
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_unique_ptr_b()
{
  struct sTest
  {
    sTest()  { }
    ~sTest() { }
    private:
      int         m_i{0};
      std::string m_str;
      char        m_ch;
  };

  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    std::unique_ptr<sTest> uniq(new sTest);
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_unique_ptr_c()
{
  struct sTest
  {
    sTest()  { }
    ~sTest() { }
    private:
      int         m_i{0};
      std::string m_str;
      char        m_ch;
  };

  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    std::unique_ptr<sTest> uniq(std::make_unique<sTest>());
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_shared_ptr_a()
{
  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    std::shared_ptr<int> uniq(new int);
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_shared_ptr_b()
{
  struct sTest
  {
    sTest()  { }
    ~sTest() { }
    private:
      int         m_i{0};
      std::string m_str;
      char        m_ch;
  };

  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    std::shared_ptr<sTest> uniq(new sTest);
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

void test_shared_ptr_c()
{
  struct sTest
  {
    sTest()  { }
    ~sTest() { }
    private:
      int         m_i{0};
      std::string m_str;
      char        m_ch;
  };

  TimeVar t1;
  TimeVar t2;
  size_t mili {0};

  t1 = std::chrono::high_resolution_clock::now();
  for(uint32_t i = 0; i < ITERATION_COUNT; ++i)
  {
    std::shared_ptr<sTest> uniq(std::make_shared<sTest>());
  }
  t2 = std::chrono::high_resolution_clock::now();
  mili = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
  std::cout << "    " << mili  << " miliseconds" << std::endl;
}

int main()
{
  std::cout << "new test " << std::endl;
  test_new_a();
  test_new_a();
  test_new_a();
  test_new_a();
  std::cout << std::endl;

  test_new_b();
  test_new_b();
  test_new_b();
  test_new_b();

  std::cout << std::endl << "unique_ptr test " << std::endl;
  test_unique_ptr_a();
  test_unique_ptr_a();
  test_unique_ptr_a();
  test_unique_ptr_a();
  std::cout << std::endl;

  test_unique_ptr_b();
  test_unique_ptr_b();
  test_unique_ptr_b();
  test_unique_ptr_b();
  std::cout << std::endl;

  test_unique_ptr_c();
  test_unique_ptr_c();
  test_unique_ptr_c();
  test_unique_ptr_c();


  std::cout << std::endl << "shared_ptr test " << std::endl;
  test_shared_ptr_a();
  test_shared_ptr_a();
  test_shared_ptr_a();
  test_shared_ptr_a();
  std::cout << std::endl;

  test_shared_ptr_b();
  test_shared_ptr_b();
  test_shared_ptr_b();
  test_shared_ptr_b();
  std::cout << std::endl;

  test_shared_ptr_c();
  test_shared_ptr_c();
  test_shared_ptr_c();
  test_shared_ptr_c();

  return 0;
}


















