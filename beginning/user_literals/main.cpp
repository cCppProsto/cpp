#include <iostream>

using namespace std;

void integer_literals()
{
  auto a1 = 1;
  auto a2 = 01;
  auto a3 = 0x0a;
  auto a4 = 0X0A;
  auto a5 = 0b101010;                         // C++14

  auto ai  = 0;                             // int
  auto aui = 0U;  // 0u                     // unsigned int
  auto al  = 0l;  // 0L, 0ul, 0UL, 0LU      // long
  auto all = 0ll; // 0LL, 0ull, 0ULL, 0LLU  // long long

  auto l1 = 18446744073709550592ull;          // C++11
  auto l2 = 18'446'744'073'709'550'592llu;    // C++14
  auto l3 = 1844'6744'0737'0955'0592uLL;      // C++14
  auto l4 = 184467'440737'0'95505'92LLU;      // C++14
  auto l5 = 1'440737'1LLU;                    // C++14
}

void floating_literals()
{
  auto f1 = 123.456e-67;  // double
  auto f2 = .1E4f;        // float
  auto f3 = 58.;          // double
  auto f4 = 4e2;
  auto f5 = 1.f; // F     // float
  auto f6 = 1.l; // L     // long double
  auto f7 = 1.23e3;       // 1230.0
  auto f8 = 1.23e+3;       // 1230.0
  auto f9 = 1.23e-3;       // 0.00123
}

void character_literals()
{
  auto c1 = 'a';
  auto c2 = u'a';   // U - UCS-2 character literal char16_t
  auto c3 = U'a';   // U - UCS-4 character literal char32_t
  auto c4 = L'a';   // wide character literal      wchar_t
  auto c5 = 'aAa';

  std::cout << sizeof(c1) << std::endl;
  std::cout << sizeof(c2) << std::endl;
  std::cout << sizeof(c3) << std::endl;
  std::cout << sizeof(c4) << std::endl;
  std::cout << sizeof(c5) << std::endl;
}

void string_literals()
{
  auto s1 = "hello";

  auto s2 = "\nhello\\n\n";       // string
  auto s3 = "hello\nworld";       // string

  auto s4 = R"(
            hello\n
            )";                   // RAW string

  auto s5 = R"(hello
               world)";           // RAW string

  auto s6 = u8"hello";            // UTF-8 string
  auto s7 = u8R"(hello)";         // UTF-8 RAW string
  auto s8 = u"hello";             // UTF-16 string
  auto s9 = uR"(hello)";          // UTF-16 RAW string
  auto s10= U"hello";             // UTF-32 string
  auto s11= UR"(hello)";          // UTF-32 RAW string
}

void boolean_literals()
{
  auto b1 = true;
  auto b2 = false;
}

void pointer_literals()
{
  int *p = nullptr;
}

/*
const char *
unsigned long long int
long double
char
wchar_t
char16_t
char32_t
const char * , std::size_t
const wchar_t * , std::size_t
const char16_t * , std::size_t
const char32_t * , std::size_t
*/

// degree to radian
constexpr long double operator"" _deg ( long double aDeg )
{
    return aDeg*3.141592/180.;
}

// radian to degree
constexpr long double operator"" _rad ( long double aRad )
{
    return aRad*180./3.141592;
}


struct Kilograms
{
  explicit constexpr Kilograms(double wgt) : weight{wgt} {}
  double weight;
};

struct Pounds
{
  explicit constexpr Pounds(double wgt) : weight{wgt} {}
  double weight;
};


constexpr Kilograms operator "" _kgkg( long double wgt )
{
  return Kilograms{static_cast<double>(wgt)};
}
constexpr Kilograms operator "" _kglbs( long double wgt )
{
  return Kilograms{static_cast<double>(wgt * 0.45359237)};
}

constexpr Pounds operator "" _lbkg( long double wgt )
{
  return Pounds{static_cast<double>(wgt*2.2046)};
}
constexpr Pounds operator "" _lblbs( long double wgt )
{
  return Pounds{static_cast<double>(wgt)};
}


int main()
{
  long double rad = 20.0_deg;
  long double deg = 20.0_rad;

  std::cout << rad << std::endl;
  std::cout << deg << std::endl;

  Kilograms kg_1 = 100._kgkg;
  Kilograms kg_2 = 100._kglbs;
  Kilograms kg_3 = Kilograms{100};
  //Kilograms kg_4 = 100; // error

  Pounds lb_1 = 100._lbkg;
  Pounds lb_2 = 100._lblbs;

  // ...
  return 0;
}









