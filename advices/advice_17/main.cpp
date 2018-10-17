#include <iostream>
#include <string>

using namespace std;

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 5 - Опасайтесь определяемых пользователем функций преобразования типа


namespace advice_17_a
{
  class Name                            // описывает имена объектов
  {
    public:
      Name(const std::string &aName)    // преобразование string в Name
      {
      }
  };

  class Rational                        // класс действительных чисел
  {
    public:
      Rational(int aNumerator = 0       // преобразует int в Rational
              ,int aDenominator = 0)
        :m_numerator(aNumerator)
        ,m_denominator(aDenominator)
      {
      }

      operator double() const
      {
        return m_numerator + m_denominator * 0.1;
      }
    private:
      int m_numerator;
      int m_denominator;
  };

  void main()
  {
    Rational a(10, 5);

    double d;
    d = a;
    d = 2 * a;
    std::cout << a << std::endl;
  }
}

namespace advice_17_b
{
  class Name                            // описывает имена объектов
  {
    public:
      Name(const std::string &aName)    // преобразование string в Name
      {
      }
  };

  class Rational                        // класс действительных чисел
  {
    public:
      Rational(int aNumerator = 0       // преобразует int в Rational
              ,int aDenominator = 0)
        :m_numerator(aNumerator)
        ,m_denominator(aDenominator)
      {
      }

      double asDouble() const
      {
        return m_numerator + m_denominator * 0.1;
      }
    private:
      int m_numerator;
      int m_denominator;
  };

  void main()
  {
    Rational a(10, 5);

    double d;
    d = a.asDouble();
    d = 2 * a.asDouble();
    //std::cout << a << std::endl;  // error
    std::cout << a.asDouble() << std::endl;
  }
}

namespace advice_17_c
{
  template<class T>
  class Array
  {
    public:
      Array(int lowBound, int highBound)
      {
        array = new T[highBound - lowBound];
      }
      Array(int size)
      {
        array = new T[size];
      }

      ~Array()
      {
        if(array != nullptr)
          delete [] array;
        array = nullptr;
      }

      T & operator[](int index)
      {
        return array[index];
      }

      T *array { nullptr };
  };

  bool operator==(const Array<int> &lhs, const Array<int> &rhs)
  {
    return true;
  }

  void main()
  {
    Array<int> a(10);
    Array<int> b(10);

    for(int i = 0; i < 10; ++i)
    {
      if(a == b[i])
      //if(a == static_cast<Array<int>>(b[i]))
      {
      }
    }
  }
}

namespace advice_17_d
{
  template<class T>
  class Array
  {
    public:
      Array(int lowBound, int highBound)
      {
        array = new T[highBound - lowBound];
      }
      explicit Array(int size)
      {
        array = new T[size];
      }

      ~Array()
      {
        if(array != nullptr)
          delete [] array;
        array = nullptr;
      }

      T & operator[](int index)
      {
        return array[index];
      }

      T *array { nullptr };
  };

  bool operator==(const Array<int> &lhs, const Array<int> &rhs)
  {
    return true;
  }

  void main()
  {
    Array<int> a(10);
    Array<int> b(10);

    for(int i = 0; i < 10; ++i)
    {
      //if(a == b[i]) // error
      if(a == Array<int>(b[i]))
      //if(a == static_cast<Array<int>>(b[i]))
      //if(a == (Array<int>)(b[i]))
      {
      }
    }
  }
}

int main()
{
  //advice_17_a::main();
  //advice_17_b::main();
  //advice_17_c::main();
  advice_17_d::main();

  return 0;
}
