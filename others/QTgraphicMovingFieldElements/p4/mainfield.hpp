#ifndef MAINFIELD_HPP
#define MAINFIELD_HPP

#include "field.hpp"

class mainField : public field
{
public:
  mainField();

private:
  void init_cells() override;

};

#endif // MAINFIELD_HPP
