#include <iostream>
#include <memory>

#include <array>
#include <string>
#include <vector>

using namespace std;

namespace creational_object_pool
{

struct unit
{
  int x       { 0 };
  int y       { 0 };
  int health  { 0 };
  int type    { 0 };
};


// [  ,  ,  ,  , ... ]
// [ t, f, t, t,... ]

class objectPool
{
public:
  static objectPool &instance()
  {
    static objectPool inst;
    return inst;
  }
  //----------------------------------------------------------------------------
  unit *get()
  {
    if(m_objects.size() == m_in_use)
    {
      m_objects.push_back(std::make_pair(true, std::make_unique<unit>()));
      m_in_use++;
      return m_objects[m_objects.size() - 1].second.get();
    }
    else
    {
      for(auto &ref : m_objects)
      {
        if(ref.first == false)
        {
          ref.first = true;
          m_in_use++;
          return ref.second.get();
        }
      }
    }
    return nullptr;
  }
  //----------------------------------------------------------------------------
  void releaseObject(unit *apObject)
  {
    for(auto &ref : m_objects)
    {
      if(ref.second.get() == apObject)
      {
        ref.first = false;
        m_in_use--;
      }
    }
  }

private:
  objectPool()
  {
    m_objects.reserve(100);
  }

private:
  unsigned m_in_use { 0 };

  std::vector<std::pair<bool, std::unique_ptr<unit> > > m_objects;
};

void object_pool_main()
{
  objectPool &pool = objectPool::instance();

  unit *unit_a;
  unit *unit_b;
  unit *unit_c;
  unit *unit_d;

  unit_a = pool.get();
  unit_b = pool.get();
  unit_c = pool.get();

  unit_a->x = 100;
  unit_a->y = 100;
  pool.releaseObject(unit_a);

  unit_d = pool.get();
  unit_d = pool.get();
  unit_d = pool.get();
  unit_d = pool.get();
}

}


