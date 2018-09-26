#include <iostream>

namespace behaviour_command
{

/*
void InputHandler::handleInput()
{
  if (isPressed(BUTTON_X)) jump();
  else if (isPressed(BUTTON_Y)) fireGun();
  else if (isPressed(BUTTON_A)) swapWeapon();
  else if (isPressed(BUTTON_B)) lurchIneffectively();
}
*/


enum eButton
{
  BUTTON_X
 ,BUTTON_Y
 ,BUTTON_A
 ,BUTTON_B
 ,BUTTON_UP
 ,BUTTON_DOWN
};

static bool isPressed(eButton aBtn)
{
  return true;
}

class GameActor
{
public:
  void jump(){}
  void fireGun(){}
};

class Command
{
public:
  virtual ~Command() {}
  virtual void execute(GameActor& actor) = 0;
  virtual void undo() = 0;
};

class JumpCommand : public Command
{
public:
  virtual void execute(GameActor& actor)
  {
    actor.jump();
  }
};

class FireCommand : public Command
{

public:
  virtual void execute(GameActor& actor)
  {
    actor.fireGun();
  }
};


class InputHandler
{
public:
  Command* handleInput()
  {
    if (isPressed(BUTTON_X)) return buttonX_;
    if (isPressed(BUTTON_Y)) return buttonY_;
    if (isPressed(BUTTON_A)) return buttonA_;
    if (isPressed(BUTTON_B)) return buttonB_;

    // Nothing pressed, so do nothing.
    return NULL;
  }

  // Methods to bind commands...

private:
  Command* buttonX_;
  Command* buttonY_;
  Command* buttonA_;
  Command* buttonB_;
};


class Unit
{
public:
  void moveTo(int,int){}
  int x(){return 0;}
  int y(){return 0;}

};

class MoveUnitCommand : public Command
{
public:
  MoveUnitCommand(Unit* unit, int x, int y)
  : unit_(unit),
    xBefore_(0),
    yBefore_(0),
    x_(x),
    y_(y)
  {}

  virtual void execute(GameActor& actor)
  {
    // Remember the unit's position before the move
    // so we can restore it.
    xBefore_ = unit_->x();
    yBefore_ = unit_->y();

    unit_->moveTo(x_, y_);
  }

  virtual void undo()
  {
    unit_->moveTo(xBefore_, yBefore_);
  }

private:
  Unit* unit_;
  int xBefore_, yBefore_;
  int x_, y_;
};

Unit* getSelectedUnit()
{
  return 0;
}

Command* handleInput()
{
  Unit* unit = getSelectedUnit();

  if (isPressed(BUTTON_UP))
  {
    // Move the unit up one.
    int destY = unit->y() - 1;
    return new MoveUnitCommand(unit, unit->x(), destY);
  }

  if (isPressed(BUTTON_DOWN))
  {
    // Move the unit down one.
    int destY = unit->y() + 1;
    return new MoveUnitCommand(unit, unit->x(), destY);
  }

  // Other moves...

  return NULL;
}


void conmand_main()
{
  GameActor    actor;
  InputHandler inputHandler;
  Command     *command = inputHandler.handleInput();

  if (command)
  {
    command->execute(actor);
  }
}

}










