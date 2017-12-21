#ifndef SELECTANIMATE_HPP
#define SELECTANIMATE_HPP

struct selectanimate
{
  enum class eType
  {
    UNSORTED,
    SORTED,
    CUSTOM
  };

  selectanimate();

  void init(eType);
  void draw();
};

#endif // SELECTANIMATE_HPP
