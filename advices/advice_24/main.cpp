#include <iostream>
#include <vector>

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
    Array2D<int> data_1(10,20);
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
  void test()
  {

  }
}

namespace example_6
{
  void test()
  {

  }
}

namespace example_7
{
  void test()
  {

  }
}

namespace example_8
{
  void test()
  {

  }
}

int main()
{
  example_4::test();
  cout << "Hello World!" << endl;
  return 0;
}
