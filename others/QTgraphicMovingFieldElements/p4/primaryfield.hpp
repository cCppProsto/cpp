#ifndef PRIMARYFIELD_HPP
#define PRIMARYFIELD_HPP

#include "field.hpp"

class primaryField : public field
{
public:
  primaryField();

private:
  void init_cells() override;
};

#endif // PRIMARYFIELD_HPP
