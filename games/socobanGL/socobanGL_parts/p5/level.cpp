#include "level.hpp"
#include "appsettings.hpp"

#include <QFile>
#include <QTextStream>


// http://www.sokobano.de/wiki/index.php?title=Level_format
// http://www.sourcecode.se/sokoban/levels
/*
Wall                  #   0x23
Player                @   0x40
Player on goal square +   0x2b
Box                   $   0x24
Box on goal square    *   0x2a
Goal square           .   0x2e
Floor            (Space)  0x20
*/

level::level()
{
}
//------------------------------------------------------------------------------
void level::reset()
{
}
//------------------------------------------------------------------------------
void level::load(int aLevel)
{
  const auto &lp = appSettings::instance().levelsPath();

  QString lvl_path = lp + QString::number(aLevel) + ".lvl";

  QFile   file(lvl_path);

  mIsLoad       = false;
  mIsComplete   = false;
  mGoalCount    = 0;
  mBoxesOnGoal  = 0;
  mSteps        = 0;

  file.open(QIODevice::ReadOnly);

  if(file.isOpen())
  {
    mRoom.clear();

    QTextStream in(&file);
    in >> mLevel;
    in >> mColumns;
    in >> mLines;

    std::vector<eField> tmpRoom(mColumns * mLines, eField::EMPTY);

    in.readLine();

    for(int i = 0; i < mLines; ++i)
    {
      QString line;
      line = in.readLine();

      int  column = 0;
      int  end    = line.size();

      while(column != end)
      {
        switch (line[column].toLatin1())
        {
          case '#': // Wall
          {
            tmpRoom[mColumns * i + column] =  eField::WALL;
            break;
          }
          case '@': // Player
          {
            tmpRoom[mColumns * i + column] =  eField::PLAYER;
            mPlayerPos.first  = i;
            mPlayerPos.second = column;
            break;
          }
          case '+': // Player on goal square
          {
            tmpRoom[mColumns * i + column] =  eField::PLAYER_ON_GOAL;
            break;
          }
          case '$': // Box
          {
            tmpRoom[mColumns * i + column] =  eField::BOX;
            break;
          }
          case '*': // Box on goal square
          {
            tmpRoom[mColumns * i + column] =  eField::BOX_ON_GOAL;
            ++mGoalCount;
            ++mBoxesOnGoal;
            break;
          }
          case '.': // Goal square
          {
            tmpRoom[mColumns * i + column] =  eField::GOAL;
            ++mGoalCount;
            break;
          }
          case ' ': // Floor or Empty
          {
            tmpRoom[mColumns * i + column] = eField::EMPTY;
            break;
          }
      }
      ++column;
    }
  }
  }

  file.close();
}
//------------------------------------------------------------------------------
void level::load(std::string)
{
}
//------------------------------------------------------------------------------
bool level::isComplete()
{
  return mIsComplete;
}
//------------------------------------------------------------------------------
bool level::isLoad()
{
  return mIsLoad;
}
//------------------------------------------------------------------------------
void level::player_up()
{
}
//------------------------------------------------------------------------------
void level::player_down()
{
}
//------------------------------------------------------------------------------
void level::player_left()
{
}
//------------------------------------------------------------------------------
void level::player_rigth()
{
}
//------------------------------------------------------------------------------
int level::steps_count() const
{
  return mSteps;
}
//------------------------------------------------------------------------------
int level::goals() const
{
  return mGoalCount;
}
//------------------------------------------------------------------------------
int level::boxes_on_goal() const
{
  return mBoxesOnGoal;
}
