#include <iostream>

#include "cpp_string.h"


int main()
{
    cpp_ns::string a;
    {
        cpp_ns::string tmp("Hello world!");
        //cpp_ns::string tmp1(tmp);
        a = tmp;
    }
    std::cout << a.c_str() << std::endl;

    {
        cpp_ns::string tmp("asdfa");
        a = tmp;

        a > tmp;
        tmp > a;
    }
    std::cout << a.c_str() << std::endl;

    {
        cpp_ns::string tmp("world!");
        a = tmp;
    }
    std::cout << a.c_str() << std::endl;


    return 0;
}
