#include <iostream>

using namespace std;

#include "glmain.h"

struct Base
{
    virtual void test()
    {
        std::cout << "Base\n";
    }
    void baseF()
    {
        std::cout << "baseF\n";
    }
};

struct A : Base
{
    void test()
    {
        std::cout << "A\n";
    }
};


struct B : Base
{
    void test()
    {
        std::cout << "B\n";
    }
};

int main()
{
    glMain glw;
    glw.run();
    return 0;

    Base * pobj = nullptr;
    pobj = new Base;
    pobj->test();
    pobj = new A;
    pobj->test();
    pobj = new B;
    pobj->test();

    return 0;
}
