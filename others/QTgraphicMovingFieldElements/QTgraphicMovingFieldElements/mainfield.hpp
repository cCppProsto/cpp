#ifndef MAINFIELD_HPP
#define MAINFIELD_HPP

#include "field.hpp"
#include "common.h"

class mainField : public field
{
public:
  mainField();

private:
  void init_vectors() override;
};

#endif // MAINFIELD_HPP
