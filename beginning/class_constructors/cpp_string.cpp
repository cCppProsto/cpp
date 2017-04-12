#include <iostream>

#include <string.h>

#include "cpp_string.h"

namespace cpp_ns
{

//------------------------------------------------------------------------------
string::string()
    :mpStr(nullptr)
    ,mLength(0)
{
}
//------------------------------------------------------------------------------
string::string(const char *apStr)
    :mpStr(nullptr)
    ,mLength(0)
{
    if(apStr != nullptr)
    {
        mLength = strlen(apStr);
        mpStr   = new char[mLength + 1];
        memcpy(mpStr, apStr, mLength + 1);
    }
}
//------------------------------------------------------------------------------
const char *string::c_str() const
{
    return mpStr;
}
//string::string(const string &aObj)
//{
//}
//------------------------------------------------------------------------------
string &string::operator=(const string &aObj)
{
    if(this == &aObj)
        return *this;

    if(mpStr != nullptr)
    {
        delete [] mpStr;
        mLength = 0;
    }
    mLength = aObj.mLength;
    mpStr   = new char[mLength + 1];
    memcpy(mpStr, aObj.mpStr, mLength + 1);

    return *this;
}
//------------------------------------------------------------------------------
string::~string()
{
    if(mpStr != nullptr)
    {
        delete [] mpStr;
        mLength = 0;
    }
}

}
