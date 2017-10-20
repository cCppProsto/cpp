#include <iostream>
#include <memory>

#include <array>
#include <string>
#include <vector>

using namespace std;

namespace creational_builder
{
  struct IBase
  {
    enum class eProperty
    {
      START
     ,MATTACK         // магическая атака
     ,MDEF            // магическая защита
     ,PATTACK         // физическая атака
     ,PDEF            // физическая защита
     ,HEALTH          // количество жизней
     ,PATTACK_RANGE   // дальность физической атаки
     ,MATTACK_RANGE   // дальность магической атаки
     ,END
    };
    using ibase_property = std::pair<eProperty, float>;

    static std::string stringPropertyValue(eProperty aType)
    {
      switch(aType)
      {
        case eProperty::MATTACK:        { return "Magic attack         ";}
        case eProperty::MDEF:           { return "Magic deffence       ";}
        case eProperty::PATTACK:        { return "Physical attack      ";}
        case eProperty::PDEF:           { return "Physical deffence    ";}
        case eProperty::HEALTH:         { return "Health               ";}
        case eProperty::PATTACK_RANGE:  { return "Physical attack range";}
        case eProperty::MATTACK_RANGE:  { return "Magic attack range   ";}

        case eProperty::START:
        case eProperty::END:            { return "unknown";}
      }
      return "unknown";
    }

    protected:
      int index_by_type(eProperty aType)
      {
        switch (aType)
        {
          case eProperty::MATTACK:        { return 1;}
          case eProperty::MDEF:           { return 2;}
          case eProperty::PATTACK:        { return 3;}
          case eProperty::PDEF:           { return 4;}
          case eProperty::HEALTH:         { return 5;}
          case eProperty::PATTACK_RANGE:  { return 6;}
          case eProperty::MATTACK_RANGE:  { return 7;}
          case eProperty::START:
          case eProperty::END:            { return 0;}
        }
      }

      void apply_by_rate(std::pair<IBase::eProperty, float> &aVal)
      {
        for(auto &p : mProperties)
          if(p.first == aVal.first)
            p.second = p.second * aVal.second;
      }

    public:
      IBase(std::initializer_list<ibase_property> aInitList)
      {
        mProperties.reserve(aInitList.size());
        for( auto property : aInitList)
            mProperties.push_back(property);
      }

      void setName(std::string aName)
      {
        mName = aName;
      }

      const std::string &name()
      {
        return mName;
      }

      float propertyValue(eProperty aType)
      {
        for(const auto &p : mProperties)
          if(aType == p.first)
            return p.second;
        return 0.f;
      }

    protected:
      std::vector<ibase_property> mProperties;
      std::string                 mName;
  };

  //----------------------- CAP ------------------------------------------------
  struct Cap : IBase
  {
    Cap(std::initializer_list<ibase_property> aInitList): IBase(aInitList) { }

    void setPDefRate(float aDefRate)
    {
      mPDefRate.second = aDefRate;
      apply_by_rate(mPDefRate);
    }

    private:
      std::pair<IBase::eProperty, float> mPDefRate{IBase::eProperty::PDEF, 1.f};
  };

  //----------------------- SHIRT ----------------------------------------------
  struct Shirt : IBase
  {
      Shirt(std::initializer_list<ibase_property> aInitList): IBase(aInitList) { }

      void setPDefRate(float aRate)
      {
        mPDefRate.second = aRate;
        apply_by_rate(mPDefRate);
      }

      void setMDefRate(float aRate)
      {
        mMDefRate.second = aRate;
        apply_by_rate(mMDefRate);
      }

      void setHealthRate(float aRate)
      {
        mMHealthRate.second = aRate;
        apply_by_rate(mMHealthRate);
      }

    private:
      std::pair<IBase::eProperty, float> mPDefRate{IBase::eProperty::PDEF,      1.f};
      std::pair<IBase::eProperty, float> mMDefRate{IBase::eProperty::MDEF,      1.f};
      std::pair<IBase::eProperty, float> mMHealthRate{IBase::eProperty::HEALTH, 1.f};
  };

  //----------------------- BRIEFS ---------------------------------------------
  struct Briefs : IBase
  {
    Briefs(std::initializer_list<ibase_property> aInitList): IBase(aInitList) { }

    void setPDefRate(float aRate)
    {
      mPDefRate.second = aRate;
      apply_by_rate(mPDefRate);
    }

    void setMDefRate(float aRate)
    {
      mMDefRate.second = aRate;
      apply_by_rate(mMDefRate);
    }

    private:
      std::pair<IBase::eProperty, float> mPDefRate{IBase::eProperty::PDEF, 1.f};
      std::pair<IBase::eProperty, float> mMDefRate{IBase::eProperty::MDEF, 1.f};
  };

  //----------------------- WEAPON ---------------------------------------------
  struct Weapon : IBase
  {
    Weapon(std::initializer_list<ibase_property> aInitList): IBase(aInitList) { }

    void setPAttackRate(float aRate)
    {
      mPAttackRate.second = aRate;
      apply_by_rate(mPAttackRate);
    }

    void setMAttackRate(float aRate)
    {
      mMAttackRate.second = aRate;
      apply_by_rate(mMAttackRate);
    }

    void setPAttackRangeRate(float aRate)
    {
      mPAttackRangeRate.second = aRate;
      apply_by_rate(mPAttackRangeRate);
    }

    void setMAttackRangeRate(float aRate)
    {
      mMAttackRangeRate.second = aRate;
      apply_by_rate(mMAttackRangeRate);
    }

    private:
      std::pair<IBase::eProperty, float> mPAttackRate{IBase::eProperty::PATTACK, 1.f};
      std::pair<IBase::eProperty, float> mMAttackRate{IBase::eProperty::MATTACK, 1.f};
      std::pair<IBase::eProperty, float> mPAttackRangeRate{IBase::eProperty::PATTACK_RANGE, 1.f};
      std::pair<IBase::eProperty, float> mMAttackRangeRate{IBase::eProperty::MATTACK_RANGE, 1.f};
  };

  //------------------------------- FINAL PRODUCT ------------------------------
  struct Equipment
  {
    float pattack_range()
    {
      float res{0.f};
      auto property = IBase::eProperty::PATTACK_RANGE;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    float mattack_range()
    {
      float res{0.f};
      auto property = IBase::eProperty::MATTACK_RANGE;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    float health()
    {
      float res{0.f};
      auto property = IBase::eProperty::HEALTH;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    float mattack()
    {
      float res{0.f};
      auto property = IBase::eProperty::MATTACK;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    float pattack()
    {
      float res{0.f};
      auto property = IBase::eProperty::PATTACK;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    float pdef()
    {
      float res{0.f};
      auto property = IBase::eProperty::PDEF;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    float mdef()
    {
      float res{0.f};
      auto property = IBase::eProperty::MDEF;
      if(mupCap)      res += mupCap->propertyValue(property);
      if(mupShirt)    res += mupShirt->propertyValue(property);
      if(mupBriefs)   res += mupBriefs->propertyValue(property);
      if(mupWeapon1)  res += mupWeapon1->propertyValue(property);
      if(mupWeapon2)  res += mupWeapon2->propertyValue(property);
      return res;
    }

    void print_info()
    {
      std::cout << mName << ":" << std::endl << std::endl;

      if(mupCap)      std::cout << mupCap->name()     << std::endl;
      if(mupShirt)    std::cout << mupShirt->name()   << std::endl;
      if(mupBriefs)   std::cout << mupBriefs->name()  << std::endl;
      if(mupWeapon1)  std::cout << mupWeapon1->name() << std::endl;
      if(mupWeapon2)  std::cout << mupWeapon2->name() << std::endl;
      std::cout << std::endl;

      std::cout << "All properties:" << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::MATTACK) << " = "
                << mattack() << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::MDEF) << " = "
                << mdef() << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::PATTACK) << " = "
                << pattack() << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::PDEF) << " = "
                << pdef() << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::HEALTH) << " = "
                << health() << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::MATTACK_RANGE) << " = "
                << mattack_range() << std::endl;
      std::cout << IBase::stringPropertyValue(IBase::eProperty::PATTACK_RANGE) << " = "
                << pattack_range() << std::endl;
    }

    std::string             mName;

    std::unique_ptr<Cap>    mupCap;
    std::unique_ptr<Shirt>  mupShirt;
    std::unique_ptr<Briefs> mupBriefs;

    std::unique_ptr<Weapon> mupWeapon1;
    std::unique_ptr<Weapon> mupWeapon2;
  };

  //------------------------------- IBUILDER -----------------------------------
  struct IBuilder
  {
    virtual std::unique_ptr<Cap>    make_cap() = 0;
    virtual std::unique_ptr<Shirt>  make_shirt() = 0;
    virtual std::unique_ptr<Briefs> make_briefs() = 0;

    virtual std::unique_ptr<Weapon> make_weapon_1() = 0;
    virtual std::unique_ptr<Weapon> make_weapon_2() = 0;

    std::string mName;
  };

  //------------------------------- DIRECTOR -----------------------------------
  struct Director
  {
    void setBuilder(std::unique_ptr<IBuilder> apBuilder)
    {
      mBuilder = std::move(apBuilder);
    }

    std::unique_ptr<Equipment> make_equipment()
    {
      std::unique_ptr<Equipment> res = std::make_unique<Equipment>();

      res->mName      = mBuilder->mName;
      res->mupCap     = mBuilder->make_cap();
      res->mupShirt   = mBuilder->make_shirt();
      res->mupBriefs  = mBuilder->make_briefs();
      res->mupWeapon1 = mBuilder->make_weapon_1();
      res->mupWeapon2 = mBuilder->make_weapon_2();
      return res;
    }

    std::unique_ptr<IBuilder> mBuilder;
  };

  //------------------------------- MAGIC BUILDER ------------------------------
  struct MagicDirtyAnt : IBuilder
  {
    MagicDirtyAnt()
    {
      mName = "Magic dirty ant";
    }
    std::unique_ptr<Cap> make_cap()
    {
      using property_list = std::initializer_list<IBase::ibase_property>;
      property_list list{
                          {IBase::eProperty::MDEF, 40}
                         ,{IBase::eProperty::PDEF, 10}
                        };

      std::unique_ptr<Cap> cap = std::make_unique<Cap>(list);
      cap->setName("Torn cap");
      return cap;
    }

    std::unique_ptr<Shirt> make_shirt()
    {
      using property_list = std::initializer_list<IBase::ibase_property>;
      property_list list{
                          {IBase::eProperty::MDEF,   230}
                         ,{IBase::eProperty::PDEF,   20}
                         ,{IBase::eProperty::HEALTH, 200}
                        };

      std::unique_ptr<Shirt> shirt = std::make_unique<Shirt>(list);
      shirt->setName("Vest of an ant");
      return shirt;
    }

    std::unique_ptr<Briefs> make_briefs()
    {
      using property_list = std::initializer_list<IBase::ibase_property>;
      property_list list{
                          {IBase::eProperty::MDEF,   350}
                         ,{IBase::eProperty::PDEF,   30}
                         ,{IBase::eProperty::HEALTH, 150}
                        };

      std::unique_ptr<Briefs> briefs = std::make_unique<Briefs>(list);
      briefs->setName("Red briefs");
      return briefs;
    }

    std::unique_ptr<Weapon> make_weapon_1()
    {
      using property_list = std::initializer_list<IBase::ibase_property>;
      property_list list{
                          {IBase::eProperty::PATTACK,       50}
                         ,{IBase::eProperty::MATTACK,       500}
                         ,{IBase::eProperty::MATTACK_RANGE, 50}
                         ,{IBase::eProperty::PATTACK_RANGE, 5}
                        };

      std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(list);
      weapon->setName("Left eye");
      return weapon;
    }

    std::unique_ptr<Weapon> make_weapon_2()
    {
      using property_list = std::initializer_list<IBase::ibase_property>;
      property_list list{
                           {IBase::eProperty::MDEF,           500}
                          ,{IBase::eProperty::HEALTH,         100}
                          ,{IBase::eProperty::MATTACK_RANGE,  250}
                        };

      std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(list);
      weapon->setName("Right eye");
      return weapon;
    }

  };

  void builder_main()
  {
    Director dir;

    dir.setBuilder(std::make_unique<MagicDirtyAnt>());

    std::unique_ptr<Equipment> dirty_ant(std::make_unique<Equipment>());
    dirty_ant = dir.make_equipment();
    dirty_ant->print_info();
  }
}
