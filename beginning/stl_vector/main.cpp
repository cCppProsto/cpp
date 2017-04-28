#include <iostream>
#include <vector>

using namespace std;

struct A
{
    A()
    {
        cout << "A()" << endl;
    }
    A(const A &)
    {
        cout << "A(const A &)" << endl;
    }
    A &operator=(const A &)
    {
        cout << "A&operator=(const A &)" << endl;
        return *this;
    }
    A(const A &&)
    {
        cout << "A(const A &&)" << endl;
    }
    A &operator=(const A &&)
    {
        cout << "A&operator=(const A &&)" << endl;
        return *this;
    }
    ~A()
    {
        cout << "~A()" << endl;
    }
};

A gA;

void foo_a()
{
    //vector<int> vi;
    //vector<int> vi = {1, 2, 3, 4, 5};
    vector<int> vi = {0};

    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    cout << "vi[0] = " << vi[0] << endl;
    vi[0] = 10;
    cout << "vi[0] = " << vi[0] << endl;


    vi.push_back(1);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(2);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(3);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(4);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(5);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;

    for(size_t i = 0; i < vi.size(); ++i)
        cout << vi[i] << ", ";

    cout << endl;
    cout << endl;

    for(auto i : vi)
        cout << i << ", ";

    cout << endl;

    vi.clear();
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
}

void foo_b()
{
    cout << endl;
    cout << endl;

    vector<int> vi;
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.reserve(100);

    //reserve[0] = 1;   // EXCEPTION
    //reserve.at(0);

    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(0);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(1);
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(2);
    cout << endl;
}

void foo_c()
{
    cout << endl;
    cout << endl;

    vector<int> vi;
    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;

    for(auto i : vi)
        cout << i << ", ";
    cout << endl;

    vi.resize(5);
    vi[0] = 0;
    vi[1] = 1;
    vi[2] = 2;
    for(auto i : vi)
        cout << i << ", ";
    cout << endl;

    cout << "capacity = " << vi.capacity() << ", size = " << vi.size() << endl;
    vi.push_back(1);
    for(auto i : vi)
        cout << i << ", ";

    cout << endl;
}

void foo_d()
{
    vector<double> vd;
    cout << "capacity = " << vd.capacity() << ", size = " << vd.size() << endl;
    vd.reserve(1000 * 1000);
    cout << "capacity = " << vd.capacity() << ", size = " << vd.size() << endl;
    vd.reserve(1);
    cout << "capacity = " << vd.capacity() << ", size = " << vd.size() << endl;
    vd.resize(10);
    cout << "capacity = " << vd.capacity() << ", size = " << vd.size() << endl;

    // reduce (decrease) capacity size
    //vector<double>(vd).swap(vd);
    vd.shrink_to_fit();
    cout << "capacity = " << vd.capacity() << ", size = " << vd.size() << endl;
    cout << endl;
}

void foo_e()
{
    vector<A> a;

    a.push_back(gA);
    cout << endl;
    a.push_back(gA);
    cout << endl;
    a.push_back(gA);
    cout << endl;
    a.push_back(gA);
    cout << endl;

    vector<A> b;
    b = a;
    cout << endl;
}

int main()
{
    //foo_a();
    //foo_b();
    //foo_c();
    //foo_d();
    foo_e();

    A a;
    A b(a);
    A c;
    c = a;
    A *pa = nullptr;
    pa = new A();


    return 0;
}
