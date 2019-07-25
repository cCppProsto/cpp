#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <vector>

using namespace std;


namespace example_1
{
  const char * f_a(string &s1, string &s2)
  {
    return (s1 + s2).c_str();
  }

  void f_b(string &s1, string &s2, string &s3)
  {
    const char *cs = (s1 + s2).c_str();
    cout << cs << endl;

    // ...

    const char *pstr {(s3 + s2).c_str()};
    cout << pstr << endl;

    if(cs[0] == '1')
    {
      cout << "Find!!" << endl;
    }

    if(strlen(cs = (s2 + s3).c_str()) < 8 && cs[0] == '1')
    {
      cout << "OK!" << endl;
    }
  }

  void test()
  {
    string s1{"1"};
    string s2{"2"};
    string s3{"3"};

    cout << f_a(s1,s2) << endl;

    f_b(s1, s2, s3);
  }
}


int main()
{
  example_1::test();












  return 0;
}
