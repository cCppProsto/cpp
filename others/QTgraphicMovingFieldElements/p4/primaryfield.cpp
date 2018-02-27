#include "primaryfield.hpp"

primaryField::primaryField()
  : field(3, 4, 70)
{
  init_cells();
}
//------------------------------------------------------------------------------
void primaryField::init_cells()
{
  mvFields.resize(mLines*mColumns);

  for(int i = 0; i < mLines*mColumns; ++i)
    mvFields[i] = eCellType::EMPTY;
}
