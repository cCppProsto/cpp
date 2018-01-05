#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct test
{
  virtual void f_a(){}
  virtual void f_b(){}
  virtual void f_c(){}
  void f_d(){}
  void f_e(){}
  void f_f(){}

private:
  vector<float> mvFloat;
  int           mInt;
  string        mStr;
};

struct testPublic
{
  virtual void f(){}
  vector<float> mvFloat;
  int           mInt;
  string        mStr;
};


int main()
{
  test a;

  ((testPublic*)(&a))->mInt = 10;
  ((testPublic*)(&a))->mStr = "1000";
  ((testPublic*)(&a))->mvFloat.push_back(90.f);

  return 0;
}





