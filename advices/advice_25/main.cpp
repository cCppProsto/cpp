#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <numeric>

namespace example_1
{
  template<class NumericalType>
  class dataCollection
  {
    public:
      void push_back(NumericalType aValue)
      {
        m_data.push_back(aValue);

        if(!m_is_inited)
        {
          m_avg = m_max = m_min = aValue;
          m_is_inited = true;
          return;
        }

        if(m_min > aValue)
          m_min = aValue;

        if(m_max <= aValue)
          m_max = aValue;

        int sum = std::accumulate(m_data.begin(), m_data.end(), 0);

        m_avg = sum / m_data.size();
      }
      //------------------------------------------------------------------------
      NumericalType min()const
      {
        return m_avg;
      }
      //------------------------------------------------------------------------
      NumericalType max()const
      {
        return m_avg;
      }
      //------------------------------------------------------------------------
      NumericalType avg()const
      {
        return m_avg;
      }

    private:
      bool m_is_inited{false};
      NumericalType m_min;
      NumericalType m_max;
      NumericalType m_avg;

      std::vector<NumericalType> m_data;
  };

  void test()
  {
    dataCollection<int> data;

    data.push_back(1);
    data.push_back(1);
    data.push_back(1);

    data.push_back(2);
    data.push_back(2);

    data.push_back(100);
    data.push_back(100);

    data.push_back(0);
    data.push_back(0);

    data.push_back(10000);

    data.push_back(1);
    data.push_back(2);

  }
}

namespace example_2
{
  int findCubicleNumber(const std::string &empName)
  {
    static std::map<std::string, int> localCache;

    auto it = localCache.find(empName);
    if(it == localCache.end())
    {
      int num = std::rand() % 10000; // finding in DB

      localCache[empName] = num;

      return num;
    }
    else
    {
      return (*it).second;
    }
  }

  void test()
  {
    int res {0};

    res = findCubicleNumber("Scott");
    res = findCubicleNumber("Anonymous");

    res = findCubicleNumber("Scott");
    res = findCubicleNumber("Anonymous");
  }
}

namespace example_3
{
  void test()
  {
  }
}

namespace example_4
{
  void test()
  {
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


int main()
{
  //example_1::test();
  example_2::test();
  return 0;
}
