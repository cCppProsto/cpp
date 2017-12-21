#ifndef BUBBLEANIMATE_HPP
#define BUBBLEANIMATE_HPP

struct bubbleAnimate
{
  enum class eType
  {
    UNSORTED,
    SORTED,
    CUSTOM
  };

  bubbleAnimate();

  void init(eType);
  void draw();
};

#endif // BUBBLEANIMATE_HPP
