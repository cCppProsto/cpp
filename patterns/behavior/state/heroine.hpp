#ifndef HEROINE_HPP
#define HEROINE_HPP

#include "heroinestate.hpp"

namespace sample_7
{

//----------------------------------------------------------------------------
enum class eInput
{
  PRESS_B
 ,PRESS_DOWN
 ,RELEASE_DOWN
};
//----------------------------------------------------------------------------
enum class eState
{
  STATE_STANDING,
  STATE_JUMPING,
  STATE_DUCKING,
  STATE_DIVING
};
//----------------------------------------------------------------------------
enum class eImage
{
  IMAGE_JUMP
 ,IMAGE_DUCK
 ,IMAGE_STAND
 ,IMAGE_DIVE
};

class Heroine
{
public:
  Heroine();
  virtual void handleInput(eInput input);
  virtual void update();
  void setGraphics(eImage image);
  void superBomb();

private:
  HeroineState *state_;
};

}
#endif // HEROINE_HPP
