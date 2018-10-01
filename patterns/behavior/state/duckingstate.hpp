#ifndef DUCKINGSTATE_HPP
#define DUCKINGSTATE_HPP

#include "heroine.hpp"
#include "heroinestate.hpp"

namespace sample_7
{

class DuckingState : public HeroineState
{
public:
  DuckingState();
  ~DuckingState();

  virtual HeroineState *handleInput(Heroine& heroine, eInput input);
  virtual void update(Heroine& heroine);

private:
  unsigned int chargeTime_;
};

}
#endif // DUCKINGSTATE_HPP
