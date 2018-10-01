#include "standingstate.hpp"

#include "duckingstate.hpp"
#include "jumpingstate.hpp"

namespace sample_7
{

//------------------------------------------------------------------------------
StandingState::StandingState()
{
}
//------------------------------------------------------------------------------
StandingState::~StandingState()
{
}
//------------------------------------------------------------------------------
HeroineState *StandingState::handleInput(Heroine& heroine, eInput input)
{
  if (input == eInput::PRESS_DOWN)
  {
    // Other code...
    heroine.setGraphics(eImage::IMAGE_DUCK);
    return new DuckingState();
  }
  else if(input == eInput::PRESS_B)
  {
    // Other code...
    heroine.setGraphics(eImage::IMAGE_JUMP);
    return new JumpingState();
  }
  return nullptr;
}
//------------------------------------------------------------------------------
void StandingState::update(Heroine&)
{
}

}
