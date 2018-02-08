#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>

class level
{
  enum class eField
  {
    EMPTY
   ,WALL
   ,PLAYER
   ,PLAYER_ON_GOAL
   ,BOX
   ,BOX_ON_GOAL
   ,GOAL
  };

public:
  level();

  void reset();
  void load(int);
  void load(std::string);
  bool isComplete();
  bool isLoad();

  void player_up();
  void player_down();
  void player_left();
  void player_rigth();

  int steps_count() const;
  int goals() const;
  int boxes_on_goal() const;

private:
  int mLevel{-1};
  int mColumns{0};
  int mLines{0};

  int mSteps{0};
  int mGoalCount{0};
  int mBoxesOnGoal{0};

  bool mIsComplete{false};
  bool mIsLoad{false};

  std::pair<int,int>  mPlayerPos;
  std::vector<eField> mRoom;
};

#endif // LEVEL_HPP











