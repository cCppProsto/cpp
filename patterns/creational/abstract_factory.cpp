#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

namespace creational_abstract_factory
{
  //------------------ BREASTPLATE ---------------------------------------------
  struct IBreastplate
  {
    IBreastplate(int aDef) : mPDef{aDef} {}
    int pdef() { return mPDef; }

    virtual void draw() = 0;
  protected:
    int mPDef{0};
  };

  //------------------ GAUNTLETS -----------------------------------------------
  struct IGauntlets
  {
    IGauntlets(int aDef) : mPDef{aDef} {}
    int pdef() { return mPDef; }

    virtual void draw() = 0;
  protected:
    int mPDef{0}; // physical defense
  };

  //------------------ GAITERS -------------------------------------------------
  struct IGaiters
  {
    IGaiters(int aDef) : mPDef{aDef} {}
    int pdef() { return mPDef; }

    virtual void draw() = 0;
  protected:
    int mPDef{0}; // physical defense
  };

  //------------------ BOOTS ---------------------------------------------------
  struct IBoots
  {
    IBoots(int aDef) : mPDef{aDef} {}
    int pdef() { return mPDef; }

    virtual void draw() = 0;
  protected:
    int mPDef{0}; // physical defense
  };

  //------------------ HELMET --------------------------------------------------
  struct IHelmet
  {
    IHelmet(int aDef) : mPDef{aDef} {}
    int pdef() { return mPDef; }

    virtual void draw() = 0;
  protected:
    int mPDef{0}; // physical defense
  };

  //------------------ S80 HEAVY SET -------------------------------------------
  struct BreastplateHeavyS80 : IBreastplate
  {
    BreastplateHeavyS80() : IBreastplate(1000) {}
    void draw() override { std::cout << "S80 Breastplate Heavy" << std::endl; }
  };
  struct GauntletsHeavyS80 : IGauntlets
  {
    GauntletsHeavyS80() : IGauntlets(800) { }
    void draw() override { std::cout << "S80 Gauntlets Heavy" << std::endl; }
  };
  struct GaitersHeavyS80 : IGaiters
  {
    GaitersHeavyS80() : IGaiters(500) { }
    void draw() override { std::cout << "S80 Gaiters Heavy" << std::endl; }
  };
  struct BootsHeavyS80 : IBoots
  {
    BootsHeavyS80() : IBoots(400) {}
    void draw() override { std::cout << "S80 Boots Heavy" << std::endl; }
  };
  struct HelmetHeavyS80 : IHelmet
  {
    HelmetHeavyS80() : IHelmet(300) { }
    void draw() override { std::cout << "S80 Helmet Heavy" << std::endl; }
  };

  //------------------ S80 LIGHT SET -------------------------------------------
  struct BreastplateLightS80 : IBreastplate
  {
    BreastplateLightS80() : IBreastplate(500) {}
    void draw() override { std::cout << "S80 Breastplate Light" << std::endl; }
  };
  struct GauntletsLightS80 : IGauntlets
  {
    GauntletsLightS80() : IGauntlets(400) { }
    void draw() override { std::cout << "S80 Gauntlets Light" << std::endl; }
  };
  struct GaitersLightS80 : IGaiters
  {
    GaitersLightS80() : IGaiters(300) { }
    void draw() override { std::cout << "S80 Gaiters Light" << std::endl; }
  };
  struct BootsLightS80 : IBoots
  {
    BootsLightS80() : IBoots(200) {}
    void draw() override { std::cout << "S80 Boots Light" << std::endl; }
  };
  struct HelmetLightS80 : IHelmet
  {
    HelmetLightS80() : IHelmet(200) { }
    void draw() override { std::cout << "S80 Helmet Light" << std::endl; }
  };

  struct IArmorSetFactory
  {
    virtual std::unique_ptr<IBreastplate> make_Breastplate() = 0;
    virtual std::unique_ptr<IGauntlets>   make_Gauntlets() = 0;
    virtual std::unique_ptr<IGaiters>     make_Gaiters() = 0;
    virtual std::unique_ptr<IBoots>       make_Boots() = 0;
    virtual std::unique_ptr<IHelmet>      make_Helmet() = 0;
  };

  struct HeavyArmorS80Factory : IArmorSetFactory
  {
    std::unique_ptr<IBreastplate> make_Breastplate() override
    {
      return std::make_unique<BreastplateHeavyS80>();
    }
    std::unique_ptr<IGauntlets> make_Gauntlets() override
    {
      return std::make_unique<GauntletsHeavyS80>();
    }
    std::unique_ptr<IGaiters> make_Gaiters() override
    {
      return std::make_unique<GaitersHeavyS80>();
    }
    std::unique_ptr<IBoots> make_Boots() override
    {
      return std::make_unique<BootsHeavyS80>();
    }
    std::unique_ptr<IHelmet> make_Helmet() override
    {
      return std::make_unique<HelmetHeavyS80>();
    }
  };

  struct LightArmorS80Factory : IArmorSetFactory
  {
    std::unique_ptr<IBreastplate> make_Breastplate() override
    {
      return std::make_unique<BreastplateLightS80>();
    }
    std::unique_ptr<IGauntlets> make_Gauntlets() override
    {
      return std::make_unique<GauntletsLightS80>();
    }
    std::unique_ptr<IGaiters> make_Gaiters() override
    {
      return std::make_unique<GaitersLightS80>();
    }
    std::unique_ptr<IBoots> make_Boots() override
    {
      return std::make_unique<BootsLightS80>();
    }
    std::unique_ptr<IHelmet> make_Helmet() override
    {
      return std::make_unique<HelmetLightS80>();
    }
  };

  struct Hero
  {
    void draw()
    {
      if(mBreastplate) mBreastplate->draw();
      if(mGaiters)     mGaiters->draw();
      if(mGauntlets)   mGauntlets->draw();
      if(mHelmet)      mHelmet->draw();
      if(mBoots)       mBoots->draw();

      std::cout << "PDef = " << pdef() << std::endl;
    }

    int pdef()
    {
      int res = 0;
      if(mBreastplate) res += mBreastplate->pdef();
      if(mGaiters)     res += mGaiters->pdef();
      if(mGauntlets)   res += mGauntlets->pdef();
      if(mHelmet)      res += mHelmet->pdef();
      if(mBoots)       res += mBoots->pdef();
      return res;
    }

    std::unique_ptr<IBreastplate> mBreastplate;
    std::unique_ptr<IGaiters>     mGaiters;
    std::unique_ptr<IGauntlets>   mGauntlets;
    std::unique_ptr<IHelmet>      mHelmet;
    std::unique_ptr<IBoots>       mBoots;
  };


  void create_hero_type_a(Hero &aObj)
  {
    HeavyArmorS80Factory factory;
    aObj.mBoots       = factory.make_Boots();
    aObj.mBreastplate = factory.make_Breastplate();
    aObj.mGaiters     = factory.make_Gaiters();
    aObj.mGauntlets   = factory.make_Gauntlets();
    aObj.mHelmet      = factory.make_Helmet();
  }

  void create_hero_type_b(Hero &aObj)
  {
    LightArmorS80Factory factory;
    aObj.mBoots       = factory.make_Boots();
    aObj.mBreastplate = factory.make_Breastplate();
    aObj.mGaiters     = factory.make_Gaiters();
    aObj.mGauntlets   = factory.make_Gauntlets();
    aObj.mHelmet      = factory.make_Helmet();
  }

  void create_hero_type_c(Hero &aObj)
  {
    LightArmorS80Factory ligth;
    HeavyArmorS80Factory heavy;
    aObj.mBreastplate = ligth.make_Breastplate();
    aObj.mGaiters     = ligth.make_Gaiters();
    aObj.mGauntlets   = heavy.make_Gauntlets();
    aObj.mHelmet      = heavy.make_Helmet();
  }

  void create_hero_type_d(Hero &aObj, IArmorSetFactory &aFactory)
  {
    aObj.mBoots       = aFactory.make_Boots();
    aObj.mBreastplate = aFactory.make_Breastplate();
    aObj.mGaiters     = aFactory.make_Gaiters();
    aObj.mGauntlets   = aFactory.make_Gauntlets();
    aObj.mHelmet      = aFactory.make_Helmet();
  }


  void abstract_factory_main()
  {
    Hero a;
    Hero b;
    Hero c;

    create_hero_type_a(a);
    create_hero_type_b(b);
    create_hero_type_c(c);


    Hero d;
    Hero e;
    LightArmorS80Factory ligth;
    HeavyArmorS80Factory heavy;

    create_hero_type_d(d, ligth);
    create_hero_type_d(e, heavy);

    std::cout << "Heavy:" << std::endl;
    a.draw();
    std::cout << std::endl;

    std::cout << "Light:" << std::endl;
    b.draw();
    std::cout << std::endl;

    std::cout << "Mix:" << std::endl;
    c.draw();
    std::cout << std::endl;

    std::cout << "Light:" << std::endl;
    d.draw();
    std::cout << std::endl;

    std::cout << "Heavy:" << std::endl;
    e.draw();

  }
}
