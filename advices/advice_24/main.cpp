#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


namespace example_1
{
  template<class T> class Array2D
  {
    public:
      Array2D(int dim1, int dim2)
      {
      }
  };

  void test()
  {
    int l, c;
    Array2D<int> data_1(l,c);
    Array2D<float> *data_2 = new Array2D<float>(10,20);
  }
}

namespace example_2
{
  template<class T> class Array2D
  {
    public:
      Array2D(int dim1, int dim2)
      {
      }

      /*
      T &operator[][](int index1, int index2)
      {
        T res;
        return res;
      }

      const T &operator[][](int index1, int index2)const
      {
        T res;
        return res;
      }
      */
  };

  void test()
  {
    Array2D<int> data_1(10,20);
    Array2D<float> *data_2 = new Array2D<float>(10,20);
  }
}

namespace example_3
{
  template<class T> class Array2D
  {
    public:
      Array2D(int dim1, int dim2)
      {
      }

      T &operator()(int index1, int index2)
      {
        T res;
        return res;
      }

      const T &operator()(int index1, int index2)const
      {
        T res;
        return res;
      }
  };

  void test()
  {
    Array2D<int> data_1(10,20);
    Array2D<float> *data_2 = new Array2D<float>(10,20);

    std::cout << data_1(1,2);

    int data_3[10][20];
    std::cout << data_3[1][2];
  }
}

namespace example_4
{
  template<class T> class Array2D
  {
    public:
      class Array1D
      {
      public:
        Array1D(size_t dim)
        {
          data = new T[dim];
        }

        T &operator[](size_t index)
        {
          return data[index];
        }

        const T &operator[](size_t index)const
        {
          return data[index];
        }
        T *data;
      };

      Array2D(size_t dim1, size_t dim2)
      {
        data.resize(dim1, Array1D(dim2));
      }

      Array1D &operator[](size_t index)
      {
        return data[index];
      }

      const Array1D &operator[](size_t index)const
      {
        return data[index];
      }

      std::vector<Array1D> data;
  };

  void test()
  {
    Array2D<int> data(10,20);

    std::cout << data[1][2] << std::endl;
    data[1][2] = 10;
    std::cout << data[1][2] << std::endl;
  }
}

namespace example_5
{
  class String
  {
    struct StringValue
    {
      //------------------------------------------------------------------------
      StringValue(const char *initValue)
        :refCount{1}
      {
        data = new char[strlen(initValue) + 1];
        strcpy(data, initValue);
      }
      //------------------------------------------------------------------------
      ~StringValue()
      {
        delete [] data;
      }

      int refCount{0};
      bool shareable{true};
      char *data{nullptr};
    };

    public:
      class charProxy
      {
        public:
          //--------------------------------------------------------------------
          charProxy(String &str, int index)
            :m_string(str)
            ,m_charIndex(index)
          {
          }
          //--------------------------------------------------------------------
          charProxy(const charProxy &rhs)
            :m_string(rhs.m_string)
            ,m_charIndex(rhs.m_charIndex)
          {
          }
          //--------------------------------------------------------------------
          charProxy & operator=(const charProxy &rhs)
          {
            if(m_string.value->shareable)
            {
              m_string.value = new StringValue(m_string.value->data);
            }

            m_string.value->data[m_charIndex] = rhs.m_string.value->data[rhs.m_charIndex];
            return *this;
          }
          //--------------------------------------------------------------------
          charProxy &operator=(char c)
          {
            if(m_string.value->shareable)
            {
              m_string.value = new StringValue(m_string.value->data);
            }

            m_string.value->data[m_charIndex] = c;
            return *this;
          }
          //--------------------------------------------------------------------
          operator char()const
          {
            return m_string.value->data[m_charIndex];
          }
          //--------------------------------------------------------------------
          char *operator&()
          {
            if(m_string.value->shareable)
            {
              m_string.value = new StringValue(m_string.value->data);
            }
            m_string.value->shareable = false;
            return &(m_string.value->data[m_charIndex]);
          }
          //--------------------------------------------------------------------
          const char *operator&()const
          {
            return &(m_string.value->data[m_charIndex]);
          }
        private:
          String &m_string;
          int     m_charIndex;
      };

    public:
      String(const char *initValue = "")
        :value{new StringValue(initValue)}
      {
      }
      //------------------------------------------------------------------------
      String(const String &rhs)
      {
        if(rhs.value->shareable)
        {
          value = rhs.value;
          ++value->refCount;
        }
        else
        {
          value = new StringValue{rhs.value->data};
        }
      }
      //------------------------------------------------------------------------
      String & operator=(const String &rhs)
      {
        if(value == rhs.value)
          return *this;

        if(rhs.value->shareable)
        {
          if(--value->refCount == 0)
          {
            delete value;
            value = nullptr;
          }

          value = rhs.value;
          value->refCount++;
        }
        else
        {
          delete value;
          value = new StringValue(value->data);
        }
        return *this;
      }
      //------------------------------------------------------------------------
      const charProxy operator[](int index) const
      {
        return charProxy(const_cast<String&>(*this), index);
      }
      //------------------------------------------------------------------------
      charProxy operator[](int index)
      {
        return charProxy(*this, index);
      }
      //------------------------------------------------------------------------
      ~String()
      {
        if(--value->refCount == 0)
          delete value;
      }
      //------------------------------------------------------------------------
      friend class charProxy;
    private:
      StringValue *value;
  };

  void test()
  {
    String str1("Hello!");
    String str2 = str1;
    String str3 = str2;
    String str4 = str3;

    std::cout << str4[0] << std::endl;
    std::cout << str1[0] << std::endl;

    str3[0] = '!';
    str3[2] = '!';

    char *p = &str1[0];

  }
}


int main()
{
  example_4::test();
  example_5::test();
  return 0;
}
