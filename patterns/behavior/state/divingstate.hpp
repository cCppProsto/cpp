#ifndef DIVINGSTATE_HPP
#define DIVINGSTATE_HPP

#include "heroine.hpp"
#include "heroinestate.hpp"

namespace sample_7
{

class DivingState : public HeroineState
{
public:
  DivingState();

  virtual HeroineState *handleInput(Heroine& heroine, eInput input);
  virtual void update(Heroine& heroine);
};

}
#endif // DIVINGSTATE_HPP
