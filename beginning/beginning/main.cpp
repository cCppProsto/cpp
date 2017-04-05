#include <iostream>
#include <string>

using namespace std;

int input_i_value()
{
    int i_value = 0;
    for (;;)
    {
        // for error input: asd123
        cin >> i_value;

        if (cin.fail() && !(cin.eof() || cin.bad()))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "input error" << endl;
        }
        else
            break;
    }
    return i_value;
}

void foo(double) = delete;      // from c++11 or c++14
void foo(float)  = delete;      // from c++11 or c++14

void foo(int)
{
    cout << "int" << endl;
}

void fopenFile(string aPath, int fo = 1, int fb = 1)
{
}

void foo_c(void)
{
}

void foo_cpp()
{
}

void foo_cpp_un(...)
{
}

int main()
{
    int   i = 0;
    float f = 0.123f;
    char  ch {i};       // from c++11

    auto un = i;        // from c++11 or c++14

    foo(f);             // error

    foo(i);

    fopenFile("1.txt");

    foo_cpp(1);         // error
    foo_cpp_un(1,2,3);

    return 0;
}
