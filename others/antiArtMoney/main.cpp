#include <iostream>

using namespace std;

#include "example_1.hpp"
#include "example_2.hpp"
#include "example_3.hpp"
#include "example_4.hpp"

void example_1()
{
  resource_ns_a::resource oil{0};

  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=10;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=150;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=15;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=18;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=180;
  cout << "Oil = " << oil.value() << endl;
  getchar();
}

void example_2()
{
  resource_ns_b::resource oil{0};

  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=1;
  oil+=1;
  oil+=1;
  oil+=1;
  oil+=6;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=150;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=15;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=18;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=180;
  cout << "Oil = " << oil.value() << endl;
  getchar();
}

void example_3()
{
  resource_ns_c::resource oil{0};

  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=10;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=150;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=15;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=18;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=180;
  cout << "Oil = " << oil.value() << endl;
  getchar();
}

void example_4()
{
  resource_ns_d::resource oil{0};

  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=10;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=150;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=15;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil-=18;
  cout << "Oil = " << oil.value() << endl;
  getchar();

  oil+=180;
  cout << "Oil = " << oil.value() << endl;
  getchar();
}

int main()
{
  cout << "Example 1" << endl;
  example_1();
  cout << "-------------------------------------" << endl;

  cout << endl << "Example 2" << endl;
  example_2();
  cout << "-------------------------------------" << endl;

  cout << endl << "Example 3" << endl;
  example_3();
  cout << "-------------------------------------" << endl;

  cout << endl << "Example 4" << endl;
  example_4();
  return 0;
}




















