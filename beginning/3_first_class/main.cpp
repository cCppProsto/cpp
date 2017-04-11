#include <iostream>

using namespace std;

namespace cpp_ns
{
    class string
    {
    public:
        string()
            :mpStr(nullptr)
            ,mSize(0)
        {
            cout << "string" << endl;
            resize(100);
        }

        ~string()
        {
            cout << "~string" << endl;
            free();
        }

    private:
        void resize(size_t aNewSize)
        {
            free();
            mSize = aNewSize;
            mpStr = new char[aNewSize];
        }

        void free()
        {
            if(mpStr != nullptr)
                delete [] mpStr;
        }

        char   *mpStr;
        size_t mSize;

        //void init()
        //{
        //    mpStr = nullptr;    //*((this) + offset) = nullptr;
        //    mSize = 0;          //*((this) + offset);
        //    //*(this + 0) = nullptr;
        //}
    };
}

int main()
{
    /*
    cpp_ns::string str;
    cpp_ns::string str1;
    cout << hex;
    cout << &str << ":" << &str.mpStr << ":" << &str.mSize << endl;
    cout << &str1 << ":" << &str1.mpStr << ":" << &str1.mSize << endl;
    cout << dec;
    */

    {
        cpp_ns::string str;
        //str.mSize = 90;       // error
    }

    {
        cpp_ns::string str;
        //str.free(); // another
    }

    return 0;
}

