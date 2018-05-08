#include <iostream>

using namespace std;

namespace example_a
{
  struct Date
  {
    Date(int d, int m, int y)
      :day(d)
      ,month(m)
      ,year(y)
    {
    }

    private:
      int day;
      int month;
      int year;
  };

  void test()
  {
    Date d1(1,2,2018);
    Date d2(2018,2,1); // logical error
  }
}

namespace example_b
{
  struct Day
  {
    explicit Day(int d)
      :day(d)
    {
    }
    private:
      int day;
  };

  struct Month
  {
    explicit Month(int m)
      :month(m)
    {
    }
    private:
      int month;
  };

  struct Year
  {
    explicit Year(int y)
      :year(y)
    {
    }
    private:
      int year;
  };


  struct Date
  {
    Date(Day d, Month m, Year y)
      :day(d)
      ,month(m)
      ,year(y)
    {
    }

    private:
      Day   day;
      Month month;
      Year  year;
  };
  void test()
  {
    //Date d1(1,2,2018);                    // Compilation error
    //Date d2(2018,2,1);                    // Compilation error
    Date d3(Day(1),Month(2),Year(2018));  // OK
  }
}

namespace example_c
{
  struct Day
  {
    explicit Day(int d)
      :day(d)
    {
    }
    private:
      int day;
  };

  struct Month
  {
    static Month Jan() { return Month(1);}
    //...
    static Month Dec() { return Month(12);}

    private:
      explicit Month(int m)
        :month(m)
      {
      }

      int month;
  };

  struct Year
  {
    explicit Year(int y)
      :year(y)
    {
    }
    private:
      int year;
  };


  struct Date
  {
    Date(Day d, Month m, Year y)
      :day(d)
      ,month(m)
      ,year(y)
    {
    }

    private:
      Day   day;
      Month month;
      Year  year;
  };

  void test()
  {
    Date d1(Day(1),Month::Jan(),Year(2018));  // OK
    Date d2(Day(1),Month::Dec(),Year(2018));  // OK
  }
}

namespace example_e
{
  struct Day
  {
    struct invalidDay{};

    explicit Day(int d)
      :day(d)
    {
      if(!isValid())
        throw invalidDay();
    }

    private:
      bool isValid()
      {
        if(day > 0 && day < 32)
          return true;
        return false;
      }

      int day;
  };

  struct Month
  {
    static Month Jan() { return Month(1);}
    //...
    static Month Dec() { return Month(12);}

    private:
      explicit Month(int m)
        :month(m)
      {
      }

      int month;
  };

  struct Year
  {
    explicit Year(int y)
      :year(y)
    {
    }
    private:
      int year;
  };


  struct Date
  {
    Date(Day d, Month m, Year y)
      :day(d)
      ,month(m)
      ,year(y)
    {
    }

    private:
      Day   day;
      Month month;
      Year  year;
  };

  void test()
  {
    try
    {
      Date d1(Day(1),Month::Jan(),Year(2018));  // OK
      Date d2(Day(1),Month::Dec(),Year(2018));  // OK
      Date d3(Day(0),Month::Dec(),Year(2018));  // exception!!
    }
    catch(Day::invalidDay)
    {
      cout << "invalid day!" << endl;
    }
    catch(...)
    {

    }
  }
}

namespace example_f
{
  struct Day
  {
    struct invalidDay{};

    explicit Day(int d)
      :day(d)
    {
      if(!isValid())
        throw invalidDay();
    }

    private:
      bool isValid()
      {
        if(day > 0 && day < 32)
          return true;
        return false;
      }

      int day;
  };

  enum class Month
  {
    jan = 1, feb, mar, apr, may, jun, aug, sep, oct, nov, dec
  };

  struct Year
  {
    explicit Year(int y)
      :year(y)
    {
    }
    private:
      int year;
  };


  struct Date
  {
    Date()
      :day(default_date().day)
      ,month(default_date().month)
      ,year(default_date().year)
    {
    }

    Date(Day d, Month m, Year y)
      :day(d)
      ,month(m)
      ,year(y)
    {
    }

    const Date &default_date()
    {
      static Date d(Day(1), Month::jan, Year(2000));
      return d;
    }

    private:
      Day   day;
      Month month;
      Year  year;
  };

  void test()
  {
    try
    {
      Date d1(Day(1), Month::apr, Year(2018));  // OK
      Date d2(Day(1), Month::feb, Year(2018));  // OK
      Date d3;
    }
    catch(Day::invalidDay)
    {
      cout << "invalid day!" << endl;
    }
    catch(...)
    {
    }
  }
}

int main()
{
  example_a::test();
  example_b::test();
  example_c::test();
  example_e::test();
  example_f::test();
  return 0;
}
