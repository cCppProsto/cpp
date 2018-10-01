#ifndef JUMPINGSTATE_HPP
#define JUMPINGSTATE_HPP


#include "heroine.hpp"
#include "heroinestate.hpp"

namespace sample_7
{

class JumpingState : public HeroineState
{
  static constexpr unsigned int FRAMES_COUNT = 15;
public:
  JumpingState();
  ~JumpingState();

  virtual HeroineState *handleInput(Heroine& heroine, eInput input);
  virtual void update(Heroine& heroine);
};

}
#endif // JUMPINGSTATE_HPP
