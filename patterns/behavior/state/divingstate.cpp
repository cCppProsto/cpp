#include "divingstate.hpp"

#include "heroine.hpp"
#include "heroinestate.hpp"
#include "jumpingstate.hpp"

namespace sample_7
{

//------------------------------------------------------------------------------
DivingState::DivingState()
{
}
//------------------------------------------------------------------------------
HeroineState *DivingState::handleInput(Heroine& heroine, eInput input)
{
  if (input == eInput::PRESS_DOWN)
  {
    // Other code...
    heroine.setGraphics(eImage::IMAGE_JUMP);
    return new JumpingState();
  }

  return nullptr;
}
//------------------------------------------------------------------------------
void DivingState::update(Heroine& heroine)
{
}

}
