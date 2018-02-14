#include <iostream>

using namespace std;

namespace example_a
{
  enum class eCodeResult
  {
    Ok
   ,Error
   ,ErrorConnect
   ,ErrorRead
   ,ErrorWrite
  };

  void close_connection()
  {
    cout << "connection close" << endl;
  }

  void error_log()
  {
    cout << "Error" << endl << endl;
  }

  void eResultAnalize(eCodeResult aRes)
  {
    switch(aRes)
    {
      case eCodeResult::Ok:
      {
        break;
      }
      case eCodeResult::ErrorConnect:
      case eCodeResult::ErrorRead:
      case eCodeResult::ErrorWrite:
      {
        close_connection();
      }
      case eCodeResult::Error:
      {
        error_log();
        break;
      }
    }
  }

  void test()
  {
    eResultAnalize(eCodeResult::Ok);
    eResultAnalize(eCodeResult::ErrorConnect);
    eResultAnalize(eCodeResult::ErrorRead);
    eResultAnalize(eCodeResult::ErrorWrite);
    eResultAnalize(eCodeResult::Error);
  }
}

namespace example_b
{
  enum class eCodeResult
  {
    Ok
   ,Error
   ,ErrorConnect
   ,ErrorRead
   ,ErrorWrite
  };

  void close_connection()
  {
    cout << "connection close" << endl;
  }

  void error_log()
  {
    cout << "Error" << endl << endl;
  }

  void eResultAnalize(eCodeResult aRes)
  {
    switch(aRes)
    {
      case eCodeResult::Ok:
      {
        break;
      }
      case eCodeResult::ErrorConnect:
      case eCodeResult::ErrorRead:
      case eCodeResult::ErrorWrite:
      {
        close_connection();
        [[fallthrough]];
      }
      case eCodeResult::Error:
      {
        error_log();
        break;
      }
    }
  }

  void test()
  {
    eResultAnalize(eCodeResult::Ok);
    eResultAnalize(eCodeResult::ErrorConnect);
    eResultAnalize(eCodeResult::ErrorRead);
    eResultAnalize(eCodeResult::ErrorWrite);
    eResultAnalize(eCodeResult::Error);
  }
}

namespace example_c
{
  void enable_sensors(unsigned char aFlag)
  {
    unsigned char val = aFlag;
    switch(val)
    {
      case 8:
        cout << "enable sensor 8" << endl;
      case 7:
        cout << "enable sensor 7" << endl;
      case 6:
        cout << "enable sensor 6" << endl;
      case 5:
        cout << "enable sensor 5" << endl;
      case 4:
        cout << "enable sensor 4" << endl;
      case 3:
        cout << "enable sensor 3" << endl;
      case 2:
        cout << "enable sensor 2" << endl;
      case 1:
        cout << "enable sensor 1" << endl;
    }
    cout << endl;
  }

  void test()
  {
    enable_sensors(8);
    enable_sensors(2);
    enable_sensors(5);
  }
}

namespace example_d
{
  void enable_sensors(unsigned char aFlag)
  {
    unsigned char val = aFlag;
    switch(val)
    {
      case 8:
        cout << "enable sensor 8" << endl;
        [[fallthrough]];
      case 7:
        cout << "enable sensor 7" << endl;
        [[fallthrough]];
      case 6:
        cout << "enable sensor 6" << endl;
        [[fallthrough]];
      case 5:
        cout << "enable sensor 5" << endl;
        [[fallthrough]];
      case 4:
        cout << "enable sensor 4" << endl;
        [[fallthrough]];
      case 3:
        cout << "enable sensor 3" << endl;
        [[fallthrough]];
      case 2:
        cout << "enable sensor 2" << endl;
        [[fallthrough]];
      case 1:
        cout << "enable sensor 1" << endl;
        [[fallthrough]];
    }
    cout << endl;
  }

  void test()
  {
    enable_sensors(8);
    enable_sensors(2);
    enable_sensors(5);
  }
}

namespace example_e
{
  enum class eAlert
  {
    Red
   ,Orange
   ,Yellow
   ,Green
  };

  void test()
  {
    eAlert alert{eAlert::Red};
    switch (alert)
    {
      case eAlert::Red:
        cout << "ALERT EVACUATE!!" << endl;
        [[fallthrough]];

      case eAlert::Orange:
        cout << "ALERT SOUND" << endl;
        [[fallthrough]];

      case eAlert::Yellow:
        cout << "ATTENTION SOUND" << endl;
        return;

      case eAlert::Green:
        return;
    }
  }
}


int main()
{
  example_a::test();
  example_b::test();
  example_c::test();
  example_d::test();
  example_e::test();
  return 0;
}
