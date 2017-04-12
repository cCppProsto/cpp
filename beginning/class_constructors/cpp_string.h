#ifndef STRING_H
#define STRING_H

namespace cpp_ns
{

class string
{
public:
    string();
    string(const char *);
    ~string();

    string(const string &) = delete; // !!!

    string &operator=(const string &);

    bool operator > (const string &) { return true;};

    //string(string &&)                   = delete;
    //string &operator=(const string &&)  = delete;

    const char *c_str() const;
private:
    char   *mpStr   = nullptr;
    size_t  mLength = 0;
};

}
#endif // STRING_H
