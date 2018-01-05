#include <iostream>

using namespace std;

struct test
{
  void f_a()
  {
    cout << "f_a" << endl;
  }

  void f_b()
  {
    cout << "f_b : " << mValue_a << endl;
    cout << "f_b : " << mValue_b << endl;
  }

private:
  int mValue_a{0};
  int mValue_b{0};
};

int main()
{
  long a = 0x0000000a00000000;
  ((test*)(&a))->f_b();
  return 0;
}
