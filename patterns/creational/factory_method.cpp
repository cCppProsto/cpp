#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <time.h>

using namespace std;

namespace creational_factory_method
{
  namespace wihout_fm // without factory method
  {
    struct IHelmet
    {
      virtual void draw() = 0;
    };

    struct HeavyHelmet : IHelmet
    {
      void draw() override { std::cout << "Helmet Heavy" << std::endl; }
    };

    struct LightHelmet : IHelmet
    {
      void draw() override { std::cout << "Light Heavy" << std::endl; }
    };

    void example()
    {
      std::srand(time(0));

      using uptr = std::unique_ptr<IHelmet>;

      std::vector<uptr> helmets;

      int size = (std::rand() % 10) + 1;
      for(int i = 0; i < size; ++i)
      {
        int rval = std::rand() % 2;
        switch(rval)
        {
          case 0:
          {
            helmets.push_back(std::make_unique<HeavyHelmet>());
            break;
          }
          case 1:
          {
            helmets.push_back(std::make_unique<LightHelmet>());
            break;
          }
        }
      }

      for(int i = 0; i < size; ++i)
      {
        auto &obj = helmets[i];
        obj.get()->draw();
      }
    }
  }

  namespace fm_param // factory method parametrized
  {
    enum class eHelmetType
    {
      HEAVY
     ,LIGHT
    };

    struct IHelmet
    {
      virtual void draw() = 0;

      // fabric method
      static std::unique_ptr<IHelmet> make_helmet(eHelmetType aType);
    };

    struct HeavyHelmet : IHelmet
    {
      void draw() override { std::cout << "Helmet Heavy" << std::endl; }
    };

    struct LightHelmet : IHelmet
    {
      void draw() override { std::cout << "Light Heavy" << std::endl; }
    };


    std::unique_ptr<IHelmet> IHelmet::make_helmet(eHelmetType aType)
    {
      switch(aType)
      {
        case eHelmetType::HEAVY:
          return std::make_unique<HeavyHelmet>();
        case eHelmetType::LIGHT:
          return std::make_unique<LightHelmet>();
      }
    }

    void example()
    {
      std::srand(time(0));

      using uptr = std::unique_ptr<IHelmet>;

      std::vector<uptr> helmets;

      int size = (std::rand() % 10) + 1;
      for(int i = 0; i < size; ++i)
      {
        int rval = std::rand() % 2;
        switch(rval)
        {
          case 0:
          {
            helmets.push_back(IHelmet::make_helmet(eHelmetType::HEAVY));
            break;
          }
          case 1:
          {
            helmets.push_back(IHelmet::make_helmet(eHelmetType::LIGHT));
            break;
          }
        }
      }

      for(int i = 0; i < size; ++i)
      {
        auto &obj = helmets[i];
        obj.get()->draw();
      }
    }
  }

  namespace fm_classic // factory method classic
  {
    struct IHelmet
    {
      virtual void draw() = 0;
    };

    struct HeavyHelmet : IHelmet
    {
      void draw() override { std::cout << "Helmet Heavy" << std::endl; }
    };

    struct LightHelmet : IHelmet
    {
      void draw() override { std::cout << "Light Heavy" << std::endl; }
    };

    struct IHelmetFactory
    {
      virtual std::unique_ptr<IHelmet> make_helmet() = 0;
    };

    struct LightHelmetFactory : IHelmetFactory
    {
      std::unique_ptr<IHelmet> make_helmet()
      {
        return std::make_unique<LightHelmet>();
      }
    };

    struct HeavyHelmetFactory : IHelmetFactory
    {
      std::unique_ptr<IHelmet> make_helmet()
      {
        return std::make_unique<HeavyHelmet>();
      }
    };

    void example()
    {
      std::srand(time(0));

      using uptr = std::unique_ptr<IHelmet>;
      std::vector<uptr> helmets;

      int size = (std::rand() % 10) + 1;
      for(int i = 0; i < size; ++i)
      {
        int rval = std::rand() % 2;
        switch(rval)
        {
          case 0:
          {
            static LightHelmetFactory factory;
            helmets.push_back(factory.make_helmet());
            break;
          }
          case 1:
          {
            static HeavyHelmetFactory factory;
            helmets.push_back(factory.make_helmet());
            break;
          }
        }
      }

      for(int i = 0; i < size; ++i)
      {
        auto &obj = helmets[i];
        obj.get()->draw();
      }
    }
  }

  void factory_method_main()
  {
    wihout_fm::example();
    std::cout << std::endl;

    fm_param::example();
    std::cout << std::endl;

    fm_classic::example();
    std::cout << std::endl;
  }
}
