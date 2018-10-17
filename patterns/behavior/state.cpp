#include <iostream>

#include "state/heroine.hpp"

namespace behaviour_state
{

// https://martalex.gitbooks.io/gameprogrammingpatterns/content/chapter-2/2.6-state.html

namespace sample_1
{
  //----------------------------------------------------------------------------
  enum class eButtons
  {
    PRESS_B
  };
  //----------------------------------------------------------------------------
  enum class eActivity
  {
    JUMP_VELOCITY
  };
  //----------------------------------------------------------------------------
  enum class eImage
  {
    IMAGE_JUMP
  };

  //----------------------------------------------------------------------------
  struct Heroine
  {
    //--------------------------------------------------------------------------
    void handleInput(eButtons input)
    {
      if (input == eButtons::PRESS_B)
      {
        yVelocity_ = eActivity::JUMP_VELOCITY;
        setGraphics(eImage::IMAGE_JUMP);
      }
    }
    //--------------------------------------------------------------------------
    void setGraphics(eImage image)
    {
    }

    //--------------------------------------------------------------------------
    eActivity yVelocity_;
  };
}

namespace sample_2
{
  //----------------------------------------------------------------------------
  enum class eButtons
  {
    PRESS_B
  };
  //----------------------------------------------------------------------------
  enum class eActivity
  {
    JUMP_VELOCITY
  };
  //----------------------------------------------------------------------------
  enum class eImage
  {
    IMAGE_JUMP
  };

  //----------------------------------------------------------------------------
  struct Heroine
  {
    //--------------------------------------------------------------------------
    void handleInput(eButtons input)
    {
      if (input == eButtons::PRESS_B)
      {
        if (!isJumping_)
        {
          isJumping_ = true;
          yVelocity_ = eActivity::JUMP_VELOCITY;
          setGraphics(eImage::IMAGE_JUMP);
        }
      }
    }
    //--------------------------------------------------------------------------
    void setGraphics(eImage image)
    {
    }

    //--------------------------------------------------------------------------
    eActivity yVelocity_;
    bool isJumping_;
  };
}

namespace sample_3
{
  //----------------------------------------------------------------------------
  enum class eButtons
  {
    PRESS_B
   ,PRESS_DOWN
   ,RELEASE_DOWN
  };
  //----------------------------------------------------------------------------
  enum class eActivity
  {
    JUMP_VELOCITY
  };
  //----------------------------------------------------------------------------
  enum class eImage
  {
    IMAGE_JUMP
   ,IMAGE_DUCK
   ,IMAGE_STAND
  };

  //----------------------------------------------------------------------------
  struct Heroine
  {
    //--------------------------------------------------------------------------
    void handleInput(eButtons input)
    {
      if (input == eButtons::PRESS_B)
      {
        if (!isJumping_)
        {
          isJumping_ = true;
          yVelocity_ = eActivity::JUMP_VELOCITY;
          setGraphics(eImage::IMAGE_JUMP);
        }
      }
      else if (input == eButtons::PRESS_DOWN)
      {
        if (!isJumping_)
        {
          setGraphics(eImage::IMAGE_DUCK);
        }
      }
      else if (input == eButtons::RELEASE_DOWN)
      {
        setGraphics(eImage::IMAGE_STAND);
      }
    }
    //--------------------------------------------------------------------------
    void setGraphics(eImage image)
    {
    }

    //--------------------------------------------------------------------------
    eActivity yVelocity_;
    bool isJumping_;
  };
}

namespace sample_4
{
  //----------------------------------------------------------------------------
  enum class eButtons
  {
    PRESS_B
   ,PRESS_DOWN
   ,RELEASE_DOWN
  };
  //----------------------------------------------------------------------------
  enum class eActivity
  {
    JUMP_VELOCITY
  };
  //----------------------------------------------------------------------------
  enum class eImage
  {
    IMAGE_JUMP
   ,IMAGE_DUCK
   ,IMAGE_STAND
   ,IMAGE_DIVE
  };

  //----------------------------------------------------------------------------
  struct Heroine
  {
    //--------------------------------------------------------------------------
    void handleInput(eButtons input)
    {
      if (input == eButtons::PRESS_B)
      {
        if (!isJumping_ && !isDucking_)
        {
          isJumping_ = true;
          yVelocity_ = eActivity::JUMP_VELOCITY;
          setGraphics(eImage::IMAGE_JUMP);
        }
      }
      else if (input == eButtons::PRESS_DOWN)
      {
        if (!isJumping_)
        {
          isDucking_ = true;
          setGraphics(eImage::IMAGE_DUCK);
        }
        else
        {
          isJumping_ = false;
          setGraphics(eImage::IMAGE_DIVE);
        }
      }
      else if (input == eButtons::RELEASE_DOWN)
      {
        if(isDucking_)
        {
          setGraphics(eImage::IMAGE_STAND);
        }
      }
    }
    //--------------------------------------------------------------------------
    void setGraphics(eImage image)
    {
    }

    //--------------------------------------------------------------------------
    eActivity yVelocity_;
    bool isJumping_;
    bool isDucking_;
  };
}

namespace sample_5
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
  //----------------------------------------------------------------------------
  enum class eVelocity
  {
    JUMP_VELOCITY
  };

  //----------------------------------------------------------------------------
  struct Heroine
  {
    static constexpr size_t MAX_CHARGE { 100 };

    //--------------------------------------------------------------------------
    void handleInput(eInput input)
    {
      switch (state_)
      {
        case eState::STATE_STANDING:
        {
          if (input == eInput::PRESS_B)
          {
            state_ = eState::STATE_JUMPING;
            yVelocity_ = eVelocity::JUMP_VELOCITY;
            setGraphics(eImage::IMAGE_JUMP);
          }
          else if (input == eInput::PRESS_DOWN)
          {
            state_ = eState::STATE_DUCKING;
            setGraphics(eImage::IMAGE_DUCK);
          }
          break;
        }
        case eState::STATE_JUMPING:
        {
          if (input == eInput::PRESS_DOWN)
          {
            state_ = eState::STATE_DIVING;
            setGraphics(eImage::IMAGE_DIVE);
          }
          break;
        }
        case eState::STATE_DUCKING:
        {
          if (input == eInput::RELEASE_DOWN)
          {
            state_ = eState::STATE_STANDING;
            setGraphics(eImage::IMAGE_STAND);
          }
          break;
        }
      }
    }
    //--------------------------------------------------------------------------
    void setGraphics(eImage image)
    {
    }

    //--------------------------------------------------------------------------
    size_t    chargeTime_;
    eState    state_;
    eVelocity yVelocity_;
  };
}

namespace sample_6
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
  //----------------------------------------------------------------------------
  enum class eVelocity
  {
    JUMP_VELOCITY
  };


  //----------------------------------------------------------------------------
  struct Heroine
  {
    static constexpr size_t MAX_CHARGE { 100 };

    //--------------------------------------------------------------------------
    void handleInput(eInput input)
    {
      switch (state_)
      {
        case eState::STATE_STANDING:
        {
          if (input == eInput::PRESS_DOWN)
          {
            state_ = eState::STATE_DUCKING;
            chargeTime_ = 0;
            setGraphics(eImage::IMAGE_DUCK);
          }
          // Обработка оставшегося ввода...
          break;
        }

        // Другие состояния...
      }
    }
    //--------------------------------------------------------------------------
    void update()
    {
      if (state_ == eState::STATE_DUCKING)
      {
        chargeTime_++;
        if (chargeTime_ > MAX_CHARGE)
        {
          superBomb();
        }
      }
    }
    //--------------------------------------------------------------------------
    void superBomb()
    {
    }
    //--------------------------------------------------------------------------
    void setGraphics(eImage image)
    {
    }

    //--------------------------------------------------------------------------
    size_t    chargeTime_;
    eState    state_;
    eVelocity yVelocity_;
  };
}


void state_main()
{
  sample_7::Heroine hero;

  hero.handleInput(sample_7::eInput::PRESS_B);
  hero.handleInput(sample_7::eInput::RELEASE_DOWN);
}


}
