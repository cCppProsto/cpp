#ifndef INSERTANIM_HPP
#define INSERTANIM_HPP


struct insertanimate
{
  enum class eType
  {
    UNSORTED,
    SORTED,
    CUSTOM
  };

  insertanimate();

  void init(eType);
  void draw();
};


#endif // INSERTANIM_HPP
