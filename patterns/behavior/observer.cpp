#include <iostream>

namespace behaviour_observer
{

#define MAX_OBSERVERS 10


//-------------------------- eEvent --------------------------------------------
enum class eEvent
{
  EntityFell
};
//-------------------------- EVENT DATA ----------------------------------------
struct EventData
{
  bool isHero { false };
  virtual ~EventData() = default;
};
//-------------------------- PHYSICS BODY --------------------------------------
struct PhysicsBody : EventData
{
  int  gravity    { 1 };
  bool isFalling  { false };

  //----------------------------------------------------------------------------
  void accelerate_gravity()
  {
    gravity = 10;
  }
  //----------------------------------------------------------------------------
  void update()
  {
    if(gravity > 2)
      isFalling = true;
    else
      isFalling = false;
  }
};
//-------------------------- eAchievement --------------------------------------
enum class eAchievement
{
  FellFromHeight
};
//-------------------------- OBSERVER ------------------------------------------
class Observer
{
public:
  virtual ~Observer()
  {
  }
  virtual void onNotify(const EventData&, eEvent ) = 0;
};
//-------------------------- ACHIEVEMENTS --------------------------------------
class Achievements : public Observer
{
public:
  void onNotify(const EventData& aData, eEvent aEvent) override
  {
    switch (aEvent)
    {
      case eEvent::EntityFell:
      {
        if(aData.isHero)
        {
          const PhysicsBody &r_pb = dynamic_cast<const PhysicsBody&>(aData);
          if(r_pb.isFalling)
            unlock(eAchievement::FellFromHeight);
        }
        break;
      }
    }
  }

private:
  void unlock(eAchievement achievement)
  {
    switch(achievement)
    {
      case eAchievement::FellFromHeight:
      {
        if(!m_hero_fell_from_bridge)
        {
          m_hero_fell_from_bridge = true;
          std::cout << "Fell from a height - UNLOCKED!" << std::endl;
        }
        break;
      }
    }
  }

  bool m_hero_fell_from_bridge  { false };
};
//-------------------------- SUBJECT -------------------------------------------
class Subject
{
public:
  void addObserver(Observer* apObserver)
  {
    observers_[numObservers_] = apObserver;
    numObservers_++;
  }
  void removeObserver(Observer* observer)
  {
    // delete from array
  }
protected:
  void notify(const EventData& aData, eEvent aEevent)
  {
    for (int i = 0; i < numObservers_; i++)
    {
      observers_[i]->onNotify(aData, aEevent);
    }
  }

private:
  Observer  *observers_[MAX_OBSERVERS];
  int         numObservers_ { 0 };
};

//-------------------------- PHYSICS -------------------------------------------
class Physics : public Subject
{
public:
  void updateBody(PhysicsBody& aBody)
  {
    aBody.update();

    if (aBody.isFalling)
      notify(aBody, eEvent::EntityFell);
  }
};
//-------------------------- HERO ----------------------------------------------
class Hero
{
public:
  Hero()
  {
    m_physics.addObserver(&m_achievements);
    m_ph_body.isHero = true;
  }
  //----------------------------------------------------------------------------
  void move()
  {
    // check surface
    m_ph_body.accelerate_gravity();

    m_physics.updateBody(m_ph_body);
  }

private:
  Achievements m_achievements;
  PhysicsBody  m_ph_body;
  Physics      m_physics;
};

void observer_main()
{
  Hero h;
  h.move();
}

}
