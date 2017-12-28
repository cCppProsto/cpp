#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <list>
#include <time.h>
#include <thread>
#include <chrono>
#include <utility>

using namespace std;

namespace creational_prototype
{
  constexpr float bearAttack{50.f};
  constexpr float bearDefence{5.f};
  constexpr float bearHeal{200.f};

  constexpr float wolfAttack{15.f};
  constexpr float wolfDefence{2.f};
  constexpr float wolfHeal{50.f};

  constexpr float hareAttack{5.f};
  constexpr float hareDefence{1.f};
  constexpr float hareHeal{20.f};

  struct IAIUnit
  {
    enum class eType
    {
      Unknown
     ,Wolf
     ,Bear
     ,Hare
    };

    enum class eProperty
    {
      Attack
     ,Defence
     ,Health
     ,EndProperty
    };

    virtual std::unique_ptr<IAIUnit> clone() = 0;
    virtual void attack(std::unique_ptr<IAIUnit> &aTarget) = 0;
    virtual ~IAIUnit() {}

    void healing(float aHeal)
    {
      mProperties[(unsigned)eProperty::Health] += aHeal;
    }

    void setDamage(float aDamage)
    {
      float &defence = mProperties[(unsigned)eProperty::Defence];

      mProperties[(unsigned)eProperty::Health] -= aDamage / defence;

      if(mProperties[(unsigned)eProperty::Health] <= 0)
        mIsLive = false;
    }

    unsigned attack()  { return mProperties[(unsigned)eProperty::Attack]; }
    unsigned defence() { return mProperties[(unsigned)eProperty::Defence];}
    bool isLive()      { return mIsLive; }
    eType type()       { return mType; }

  protected:
    IAIUnit(eType aType)
      :mType(aType)
    {
      mProperties.resize((unsigned)eProperty::EndProperty);

      mProperties[(unsigned)eProperty::Attack]      = 1.f;
      mProperties[(unsigned)eProperty::Defence]     = 1.f;
      mProperties[(unsigned)eProperty::Health]      = 10.f;
    }

    bool               mIsLive{true};
    eType              mType{eType::Unknown};
    std::vector<float> mProperties;
  };

  //-------------------- WOLF --------------------------------------------------
  struct Wolf : IAIUnit
  {
    friend class AIUnitsFactory;
    std::unique_ptr<IAIUnit> clone() override
    {
      return std::make_unique<Wolf>(*this);
    }

  private:
    Wolf() : IAIUnit(eType::Wolf)
    {
      mProperties[(unsigned)eProperty::Attack]  = wolfAttack;
      mProperties[(unsigned)eProperty::Defence] = wolfDefence;
      mProperties[(unsigned)eProperty::Health]  = wolfHeal;

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    void attack(std::unique_ptr<IAIUnit> &aTarget) override
    {
      aTarget->setDamage(mProperties[(unsigned)eProperty::Attack]);
    }
  };

  //-------------------- BEAR --------------------------------------------------
  struct Bear : IAIUnit
  {
    friend class AIUnitsFactory;
    std::unique_ptr<IAIUnit> clone() override
    {
      return std::make_unique<Bear>(*this);
    }

  private:
    Bear() : IAIUnit(eType::Bear)
    {
      mProperties[(unsigned)eProperty::Attack]  = bearAttack;
      mProperties[(unsigned)eProperty::Defence] = bearDefence;
      mProperties[(unsigned)eProperty::Health]  = bearHeal;

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void attack(std::unique_ptr<IAIUnit> &aTarget) override
    {
      aTarget->setDamage(mProperties[(unsigned)eProperty::Attack]);
      if(std::rand() % 3 == 1)
        aTarget->setDamage(mProperties[(unsigned)eProperty::Attack]);
    }

  };
  //-------------------- HARE --------------------------------------------------
  struct Hare : IAIUnit
  {
    friend class AIUnitsFactory;
    std::unique_ptr<IAIUnit> clone() override
    {
      return std::make_unique<Hare>(*this);
    }

  private:
    Hare() : IAIUnit(eType::Hare)
    {
      mProperties[(unsigned)eProperty::Attack]  = hareAttack;
      mProperties[(unsigned)eProperty::Defence] = hareDefence;
      mProperties[(unsigned)eProperty::Health]  = hareHeal;

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void attack(std::unique_ptr<IAIUnit> &aTarget) override
    {
      for(unsigned i = 0; i < 10; ++i)
      {
        if(rand() % 3 == 1)
          aTarget->setDamage(mProperties[(unsigned)eProperty::Attack]);
      }
    }
  };

  struct AIUnitsFactory
  {
    std::unique_ptr<IAIUnit> createWolf()
    {
      static Wolf prototype;
      return prototype.clone();
    }
    std::unique_ptr<IAIUnit> createBear()
    {
      static Bear prototype;
      return prototype.clone();
    }
    std::unique_ptr<IAIUnit> createHare()
    {
      static Hare prototype;
      return prototype.clone();
    }
  };

  void prototype_main()
  {
    AIUnitsFactory factory;

    std::unique_ptr<IAIUnit> bear(factory.createBear());
    std::list<std::unique_ptr<IAIUnit>> enemies;

    unsigned wolfKilled{0};
    unsigned hareKilled{0};
    unsigned wolfsCount{0};
    unsigned haresCount{0};

    std::srand(time(0));

    for(unsigned i = 0; i < 40; ++i)
    {
      if(std::rand()%4 == 5)
      {
        enemies.push_back(factory.createWolf());
        ++wolfsCount;
      }
      else
      {
        enemies.push_back(factory.createHare());
        ++haresCount;
      }
    }

    float bearHeal = 50.f;
    for(;;)
    {
      for(auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
      {
        if(!bear->isLive())
          break;

        (*enemy)->attack(bear);

        if(std::rand() % 4 == 2)
        {
          bear->attack((*enemy));

          if(!(*enemy)->isLive())
          {
            switch((*enemy)->type())
            {
              case IAIUnit::eType::Wolf:
              {
                ++wolfKilled;
                break;
              }
              case IAIUnit::eType::Hare:
              {
                ++hareKilled;
                break;
              }
              case IAIUnit::eType::Bear:
              case IAIUnit::eType::Unknown:
                break;
            }
            enemy = enemies.erase(enemy);
          }
        }
      }

      if(bearHeal >= 0.0f)
      {
        bear->healing(bearHeal);
        bearHeal -= 10.f;
      }

      if(enemies.empty())
      {
        std::cout << "Bear is WIN!!" << std::endl;
        break;
      }

      if(!bear->isLive())
      {
        std::cout << "Enemies is win :-(" << std::endl;
        break;
      }
    }

    std::cout << "Wolfs count:" << wolfsCount << std::endl;
    std::cout << "Hares count:" << haresCount << std::endl;
    std::cout << "Wolfs was killed:" << wolfKilled << std::endl;
    std::cout << "Hares was killed:" << hareKilled << std::endl;

  }
}
