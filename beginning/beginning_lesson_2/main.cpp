#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define C_PI 3.141231234
constexpr double CPP_PI = 3.141231234;
constexpr double CPP_PI_2 = CPP_PI / 2.;


constexpr int f_cexpr()
{
    return ((CPP_PI_2 * 10.) / 100.) * 2000.;
}


namespace ns_file
{
    int flag = 0;
    void open()
    {
        cout << "file" << endl;
    }
    enum eFileError
    {
        UNKNOWN = 0
       ,NO
       ,OPEN
       ,CLOSE
    };
}

namespace ns_network
{
    int flag = 0;
    void open()
    {
        cout << "network" << endl;
    }
    enum eNetworkError
    {
        UNKNOWN = 0
       ,NO
       ,OPEN
       ,CLOSE
       ,LOST
    };
}

enum class eFileError
{
    UNKNOWN = 0
   ,NO
   ,OPEN
   ,CLOSE
};

enum class eNetworkError
{
    UNKNOWN = 0
   ,NO
   ,OPEN
   ,CLOSE
   ,LOST
};

enum class eCharEnum : char
{
    UNKNOWN = 0
   ,NO
   ,OPEN
   ,CLOSE
   ,LOST
    //,ETEST = 200  // error
};

enum class eUintEnum : unsigned int
{
    UNKNOWN = 0
   ,NO
   ,OPEN
   ,CLOSE
   ,LOST
};

void foo_c(int *pi)
{
    *pi = 90;
}
void foo_cpp(int &pi)
{
    pi = 10;
}

int main()
{
    int i   = 0;
    int &ri = i;
    cout << "addr i = 0x" << hex << &i << endl;
    cout << "ri = 0x"     << hex << &ri << endl;
    foo_c(&i);
    foo_cpp(i);

    ns_file::eFileError       ef_error_a = ns_file::NO;
    ns_network::eNetworkError en_error_a = ns_network::NO;

    eFileError    ef_error_b = eFileError::NO;
    eNetworkError en_error_b = eNetworkError::NO;

    using namespace ns_file;
    flag = 0;
    open();

    cout << dec; // << oct

    int array[5] = {1,2,3,4,5};
    vector<int> vi;

    for(int i; cin >> i;)
        vi.push_back(i);

    for(auto i : array)
        cout << i << ",";
    cout << endl;

    for(auto i : vi)
        cout << i << ",";
    cout << endl;

    for(int i = 0; i < vi.size(); ++i)
    {
        vi[i] = vi[i] * 10;
        cout << vi[i] << ",";
    }
    cout << endl;

    int input = 0;
    cin >> input;

    const int tmp_i = input;
    //constexpr int tmp_i_1 = input;  // error


    return 0;
}
