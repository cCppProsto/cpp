#include <iostream>

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 1 - различайте указатели и ссылки

using namespace std;

namespace my_project
{
  class Logger
  {
    Logger(){}

  public:
    static Logger &intance()
    {
      static Logger l;
      return l;
    }

    void logError()
    {

    }

  };
}


void func_a(int *apArray)
{
  auto &log = my_project::Logger::intance();

  //
  log.logError();

}

void func_b(int (&apArray)[5])
{

}

void func_c(int aCountOfSome)
{

  // ...
  {
    int &c = aCountOfSome;
  }

}


int main()
{
  int *p = nullptr;

  if(p != nullptr)
  {
    *p = 100;
  }

  int a = 100;
  int &ra = a;

  a = 90;
  ra = 100;

  char *p_a = new char;
  char &r_a = *p_a;
  char *p_b = &r_a;
  *p_a = 'A';
  r_a  = 'B';
  *p_b = 'C';

  int *pai = new int [5];
  int i[5];
  func_a(pai);
  func_a(i);

  //func_b(pai); // error
  func_b(i);

  return 0;
}
