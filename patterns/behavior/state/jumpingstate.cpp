#include "jumpingstate.hpp"
#include "divingstate.hpp"


namespace sample_7
{

//------------------------------------------------------------------------------
JumpingState::JumpingState()
{
}
//------------------------------------------------------------------------------
JumpingState::~JumpingState()
{
}
//------------------------------------------------------------------------------
HeroineState *JumpingState::handleInput(Heroine& heroine, eInput input)
{
  if (input == eInput::PRESS_DOWN)
  {
    heroine.setGraphics(eImage::IMAGE_DIVE);
    return new DivingState();
  }

  return nullptr;
}
//------------------------------------------------------------------------------
void JumpingState::update(Heroine&)
{
}

}
