#ifndef PRIMARYFIELD_HPP
#define PRIMARYFIELD_HPP

#include "field.hpp"
#include "common.h"

class primaryField : public field
{
public:
  primaryField();

private:
  void init_cells() override;
};

#endif // PRIMARYFIELD_HPP
