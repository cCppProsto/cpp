#include <iostream>

using namespace std;


struct Test
{
  Test()
  {
    cout << __FUNCTION__ << endl;
  }
  Test(const Test&)
  {
    cout << __FUNCTION__ << endl;
  }
  Test&operator=(const Test&)
  {
    cout << __FUNCTION__ << endl;
  }
  ~Test()
  {
    cout << __FUNCTION__ << endl;
  }

  int a { 10 };
};


int main()
{
  return 0;
}
