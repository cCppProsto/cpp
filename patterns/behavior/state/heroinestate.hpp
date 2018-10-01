#ifndef HEROINESTATE_HPP
#define HEROINESTATE_HPP

namespace sample_7
{
enum class eInput;

class Heroine;
class StandingState;
class DuckingState;
class JumpingState;
class DivingState;

class HeroineState
{
public:
  static StandingState standing;
  static DuckingState ducking;
  static JumpingState jumping;
  static DivingState diving;

protected:
  static constexpr unsigned int MAX_CHARGE { 100 };

public:
  HeroineState();
  virtual ~HeroineState();
  virtual void update(Heroine& heroine) = 0;
  virtual HeroineState* handleInput(Heroine& heroine, eInput input) = 0;
};

}
#endif // HEROINESTATE_HPP
