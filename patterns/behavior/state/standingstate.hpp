#ifndef STANDINGSTATE_HPP
#define STANDINGSTATE_HPP

#include "heroine.hpp"
#include "heroinestate.hpp"

namespace sample_7
{

class StandingState : public HeroineState
{
public:
  StandingState();
  ~StandingState();

  virtual HeroineState *handleInput(Heroine& heroine, eInput input);
  virtual void update(Heroine& heroine);
};

}
#endif // STANDINGSTATE_HPP
