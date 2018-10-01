#include "heroine.hpp"

#include "standingstate.hpp"

namespace sample_7
{

//------------------------------------------------------------------------------
Heroine::Heroine()
{
  state_ = new StandingState();
}
//------------------------------------------------------------------------------
void Heroine::handleInput(eInput input)
{
  HeroineState* state = state_->handleInput(*this, input);
  if (state != nullptr)
  {
    delete state_;
    state_ = state;
  }
}
//------------------------------------------------------------------------------
void Heroine::update()
{
  state_->update(*this);
}
//------------------------------------------------------------------------------
void Heroine::setGraphics(eImage image)
{
}
//------------------------------------------------------------------------------
void Heroine::superBomb()
{

}


}
