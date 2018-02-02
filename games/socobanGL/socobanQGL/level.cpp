#include <QString>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>

#include "appsettings.hpp"
#include "level.hpp"

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
void level::load(int aNumber)
{
  const auto &level_path = appSettings::instance().levelsPath();

  QString lvl_path = level_path + QString::number(aNumber) + ".lvl";
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
      bool isIn   = false;
      while(column != end)
      {
        switch (line[column].toLatin1())
        {
          case '#': // Wall
          {
            isIn = isIn ? false : true;
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
    mRoom.swap(tmpRoom);
    mIsLoad = true;
  }
  file.close();
}
//------------------------------------------------------------------------------
void level::load(std::string /*aSaveFilePath*/)
{
  mIsLoad = false;
}
//------------------------------------------------------------------------------
void level::reset()
{
  load(mLevel);
}
//------------------------------------------------------------------------------
bool level::isLoad()
{
  return mIsLoad;
}
//------------------------------------------------------------------------------
bool level::isCompelte()
{
  return mIsComplete;
}
//------------------------------------------------------------------------------
void level::player_up()
{
  _move(-1, 0);
}
//------------------------------------------------------------------------------
void level::player_down()
{
   _move(1, 0);
}
//------------------------------------------------------------------------------
void level::player_left()
{
   _move(0, -1);
}
//------------------------------------------------------------------------------
void level::player_rigth()
{
  _move(0, 1);
}
//------------------------------------------------------------------------------
void level::_move(int aDl, int aDc)
{
  auto &[line, column] = mPlayerPos;

  auto nl  = line + aDl;                  // next line
  auto nc  = column + aDc;                // next column

  auto nnl = nl + aDl;                    // next next line
  auto nnc = nc + aDc;                    // next next column

  auto coff  = mColumns * line + column;  // current offset
  auto noff  = mColumns * nl + nc;        // next offset
  auto nnoff = mColumns * nnl + nnc;      // next next offset

  auto &f   = mRoom[coff];                 // current field
  auto &nf  = mRoom[noff];                 // next field
  auto &nnf = mRoom[nnoff];                // next next field

  bool isMoving = false;
  switch(nf)
  {
    case eField::BOX:
    {
      if(nnf == eField::GOAL)
      {
        f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
        nf  = eField::PLAYER;
        nnf = eField::BOX_ON_GOAL;
        isMoving = true;
        ++mBoxesOnGoal;
        break;
      }
      if(nnf == eField::EMPTY)
      {
        f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
        nf  = eField::PLAYER;
        nnf = eField::BOX;
        isMoving = true;
        break;
      }
      break;
    }
    case eField::BOX_ON_GOAL:
    {
      if(nnf == eField::GOAL)
      {
        f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
        nf  = eField::PLAYER_ON_GOAL;
        nnf = eField::BOX_ON_GOAL;
        isMoving = true;
        break;
      }
      if(nnf == eField::EMPTY)
      {
        f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
        nf  = eField::PLAYER_ON_GOAL;
        nnf = eField::BOX;
        isMoving = true;
        --mBoxesOnGoal;
        break;
      }
      break;
    }
    case eField::GOAL:
    {
      f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
      nf  = eField::PLAYER_ON_GOAL;
      isMoving = true;
      break;
    }
    case eField::EMPTY:
    {
      f  = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
      nf = eField::PLAYER;
      isMoving = true;
      break;
    }
    case eField::WALL:
    case eField::PLAYER:
    case eField::PLAYER_ON_GOAL:
      break;
  }

  if(isMoving)
  {
    line   = nl;
    column = nc;
    ++mSteps;

    if( mBoxesOnGoal == mGoalCount)
      mIsComplete = true;
  }
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


