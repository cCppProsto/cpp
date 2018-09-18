#include <iostream>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

namespace structural_flyweight
{


constexpr size_t WIDTH{1000};
constexpr size_t HEIGHT{1000};

/*
class TreeModel
{
private:
  Mesh mesh_;
  Texture bark_;
  Texture leaves_;
};

class Tree
{
private:
  TreeModel* model_;

  Vector position_;
  double height_;
  double thickness_;
  Color barkTint_;
  Color leafTint_;
};
*/

struct Texture{};

Texture GRASS_TEXTURE;
Texture HILL_TEXTURE;
Texture RIVER_TEXTURE;

class Terrain
{
public:
  Terrain(int movementCost, bool isWater,Texture texture)
          :movementCost_(movementCost),
           isWater_(isWater),
           texture_(texture)
  {}

  int   getMovementCost() const     { return movementCost_; }
  bool  isWater() const             { return isWater_; }
  const Texture& getTexture() const { return texture_; }

private:
  int     movementCost_;
  bool    isWater_;
  Texture texture_;
};

class World
{
public:
  World()
  : grassTerrain_(1, false, GRASS_TEXTURE),
    hillTerrain_(3, false, HILL_TEXTURE),
    riverTerrain_(2, true, RIVER_TEXTURE)
  {}

  void generateTerrain()
  {
    // Fill the ground with grass.
    for (int x = 0; x < WIDTH; x++)
    {
      for (int y = 0; y < HEIGHT; y++)
      {
        // Sprinkle some hills.
        if (random() % 10 == 0)
        {
          tiles_[x][y] = &hillTerrain_;
        }
        else
        {
          tiles_[x][y] = &grassTerrain_;
        }
      }
    }

    // Lay a river.
    int x = random() % WIDTH;
    for (int y = 0; y < HEIGHT; y++)
    {
      tiles_[x][y] = &riverTerrain_;
    }
  }

  const Terrain& getTile(int x, int y) const
  {
    return *tiles_[x][y];
  }

private:
  Terrain grassTerrain_;
  Terrain hillTerrain_;
  Terrain riverTerrain_;

  Terrain* tiles_[WIDTH][HEIGHT];
  // Other stuff...
};

void flyweight_main()
{
  World world;
  int cost = world.getTile(2, 3).getMovementCost();
}


}
























