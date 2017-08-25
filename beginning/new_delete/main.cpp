#include <iostream>
#include <memory>

using namespace std;

void f1()
{
  char   *pch = nullptr;
  double *pd  = nullptr;

  // pch = (char*)malloc(sizeof(char));
  pch = new char;
  delete pch;
  // free(pch);

  // pch = (char*)malloc(sizeof(char) * 20);
  pch = new char[20];
  delete [] pch;
  // free(pch);

  pd  = new double;
  delete pd;

  pd  = new double[20];
  delete [] pd;

  //delete [] pd; // crash
  pd = nullptr;
  delete [] pd;   // ok!
}

void f2()
{
  struct A
  {
    A(){ std::cout << __FUNCTION__ << std::endl;}
    ~A(){ std::cout << __FUNCTION__ << std::endl;}
  };

  A *pa = new A;
  delete pa;
  std::cout << "-------------------------------------\n\n";


  pa = new A[2];
  delete [] pa;
  std::cout << "-------------------------------------\n\n";

  pa = new A[3];
  //delete pa;      // crash
  std::cout << "-------------------------------------\n\n";

  pa = new A;
  //delete [] pa;      // crash
  std::cout << "-------------------------------------\n\n";
}

void f3()
{
  struct A
  {
    A(){ std::cout << __FUNCTION__ << std::endl;}
    ~A(){ std::cout << __FUNCTION__ << std::endl;}
  };

  A *pa = (A*)malloc(sizeof(A));
  free(pa);

  pa = (A*)malloc(sizeof(A));
  delete pa;
}

void f4()
{
  struct A
  {
    A()
    {
      std::cout << __FUNCTION__ << std::endl;
    }

    ~A()
    {
      std::cout << __FUNCTION__ << std::endl;
    }

    void seta(int aVal)
    {
      ma = aVal;
    }

    void setb(int aVal)
    {
      mb = aVal;
    }
    private:
      int ma = 20;
      int mb = 30;
  };

  A *pa = (A*)malloc(sizeof(A));
  *((int*)(pa)) = 100;
  pa->seta(300);
  pa->seta(400);
  delete pa;
}


void f(int)
{
  std::cout << "f_int" << std::endl;
}
void f(bool)
{
  std::cout << "f_bool" << std::endl;
}
void f(void*)
{
  std::cout << "f_ptr" << std::endl;
}


int main()
{
  //f1();
  //f2();
  //f3();
  //f4();

  /*
  f(0);
  f(NULL);
  f(nullptr);
  */


  return 0;
}
