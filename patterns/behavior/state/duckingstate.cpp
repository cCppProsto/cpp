#include "duckingstate.hpp"
#include "standingstate.hpp"

namespace sample_7
{

//------------------------------------------------------------------------------
DuckingState::DuckingState() : chargeTime_(0)
{
}
//------------------------------------------------------------------------------
DuckingState::~DuckingState()
{
}
//------------------------------------------------------------------------------
HeroineState *DuckingState::handleInput(Heroine& heroine, eInput input)
{
  if (input == eInput::RELEASE_DOWN)
  {
    heroine.setGraphics(eImage::IMAGE_STAND);
    return new StandingState();
  }

  // Other code...
  return nullptr;
}
//------------------------------------------------------------------------------
void DuckingState::update(Heroine& heroine)
{
  chargeTime_++;
  if (chargeTime_ > MAX_CHARGE)
  {
    heroine.superBomb();
  }
}


}
