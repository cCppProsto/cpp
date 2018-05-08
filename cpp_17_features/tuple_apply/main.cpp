#include <iostream>
#include <tuple>
#include <string>

using namespace std;

struct account
{
  account(string a, string b, int c, int d)
    :name(a)
    ,lastName(b)
    ,age(c)
    ,ID(d)
  {
  }

  string name;
  string lastName;
  int    age;
  int    ID;
};

void print_info(string a, string b, int c, int d)
{
  cout << a << ", " << b << ", " << c << "," << d << endl;
}

int main()
{
  auto t    = make_tuple("plus_plus", "gcc_sovi4", 20, 1);
  account a = make_from_tuple<account>(t);

  apply(print_info, t);

  return 0;
}
